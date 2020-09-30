// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "stdafx.h"

namespace Microsoft::Resources
{

class PerThreadQualifier : public DefObject
{
public:
    static HRESULT CreateInstance(
        _In_ const CoreProfile* pProfile,
        _In_ const UnifiedEnvironment* pEnvironment,
        _In_ const IResolver* pParentResolver,
        _Outptr_ PerThreadQualifier** result)
    {
        *result = nullptr;

        RETURN_HR_IF(E_INVALIDARG, (pProfile == nullptr) || (pEnvironment == nullptr) || (pParentResolver == nullptr));

        AutoDeletePtr<PerThreadQualifier> pRtrn = new PerThreadQualifier();
        RETURN_IF_NULL_ALLOC(pRtrn);
        RETURN_IF_FAILED(pRtrn->Init(pProfile, pEnvironment, pParentResolver));

        *result = pRtrn.Detach();
        return S_OK;
    }

    ~PerThreadQualifier()
    {
        for (int i = 0; i < m_qualifierCaches->Count(); i++)
        {
            StringResult* pStrResult;
            if (SUCCEEDED(m_qualifierCaches->Get(i, &pStrResult)))
            {
                delete pStrResult;
            }
        }

        delete m_qualifierCaches;
        m_qualifierCaches = nullptr;
    }

    int GetNumPerThreadQualifiers() const { return m_pProfile->GetNumThreadAwareQualifiers(); }

    HRESULT GetQualifierPerThread(_In_ int index, _Out_ Atom* pAtom)
    {
        RETURN_HR_IF(E_INVALIDARG, index >= GetNumPerThreadQualifiers());

        StringResult strQualiferName;
        RETURN_IF_FAILED(m_pProfile->GetThreadAwareQualifierName(index, &strQualiferName));

        RETURN_IF_FAILED(m_Environment->GetQualifierNameAtom(strQualiferName.GetRef(), pAtom, nullptr));

        return S_OK;
    }

    HRESULT GetProvider(_In_ Atom name, _Out_ IQualifierValueProvider** ppQualifierProvider)
    {
        return m_pProfile->GetProviderForQualifier(m_Environment->GetDefaultEnvironment(), name, ppQualifierProvider);
    }

    HRESULT GetQualifierValue(_In_ int index, _Inout_ StringResult* pStringResult)
    {
        RETURN_HR_IF(E_INVALIDARG, index >= GetNumPerThreadQualifiers());

        StringResult* pStrValue = nullptr;
        if (!m_qualifierCaches->TryGet(index, &pStrValue))
        {
            Atom name;
            AutoDeletePtr<IQualifierValueProvider> pProvider;
            RETURN_IF_FAILED(GetQualifierPerThread(index, &name));
            RETURN_IF_FAILED(GetProvider(name, &pProvider));

            AutoDeletePtr<StringResult> strValue = new StringResult();
            RETURN_IF_NULL_ALLOC(strValue);

            RETURN_IF_FAILED(pProvider->GetQualifierValue(name, nullptr, strValue));

            RETURN_IF_FAILED(m_qualifierCaches->SetExtent(index));
            RETURN_IF_FAILED(m_qualifierCaches->Insert(strValue, index));

            pStrValue = strValue.Detach();
        }

        RETURN_IF_FAILED(pStringResult->SetRef(pStrValue->GetRef()));

        return S_OK;
    }

    HRESULT GetQualifierValue(_In_ Atom name, _Inout_ StringResult* pStringResult)
    {
        Atom localName;
        for (int i = 0; i < GetNumPerThreadQualifiers(); i++)
        {
            if (SUCCEEDED(GetQualifierPerThread(i, &localName)) && (localName == name))
            {
                return GetQualifierValue(i, pStringResult);
            }
        }

        return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
    }

    HRESULT ValueIsSameAsParent(_In_ int index, _Out_ bool* pbSameValue)
    {
        RETURN_HR_IF(E_INVALIDARG, index >= GetNumPerThreadQualifiers());

        Atom name;
        StringResult strParentValue;

        RETURN_IF_FAILED(GetQualifierPerThread(index, &name));
        RETURN_IF_FAILED(m_pParentResolver->GetQualifierValue(name, &strParentValue));

        StringResult strValue;
        RETURN_IF_FAILED(GetQualifierValue(index, &strValue));

        DEFCOMPARISON result;
        RETURN_IF_FAILED(strParentValue.ICompare(&strValue, &result));

        if (result == Def_Equal)
        {
            *pbSameValue = true;
        }
        else
        {
            *pbSameValue = false;
        }

        return S_OK;
    }

    void ResetCache()
    {
        if (m_qualifierCaches)
        {
            for (int i = 0; i < m_qualifierCaches->Count(); i++)
            {
                StringResult* pStrResult;
                m_qualifierCaches->Get(i, &pStrResult);
                if (pStrResult)
                {
                    delete pStrResult;
                }
            }
            m_qualifierCaches->Reset();
        }
    }

    void ResetCache(_In_ Atom qualifierToReset)
    {
        if (m_qualifierCaches)
        {
            Atom localName;
            int numThreadQualifiers = GetNumPerThreadQualifiers();
            for (int i = 0; i < numThreadQualifiers; i++)
            {
                if (SUCCEEDED(GetQualifierPerThread(i, &localName)) && (localName == qualifierToReset))
                {

                    StringResult* pStrResult;
                    m_qualifierCaches->Get(i, &pStrResult);
                    if (pStrResult)
                    {
                        delete pStrResult;
                        m_qualifierCaches->Delete(i);
                    }
                }
            }
        }
    }

private:
    PerThreadQualifier() : m_qualifierCaches(nullptr) {}

    HRESULT Init(_In_ const CoreProfile* pProfile, _In_ const UnifiedEnvironment* pEnvironment, _In_ const IResolver* pParentResolver)
    {
        m_pProfile = pProfile;
        m_Environment = pEnvironment;
        m_pParentResolver = pParentResolver;

        DEF_ASSERT(pProfile->GetNumThreadAwareQualifiers() != 0); // the class shoud not be created for 0 thread aware qualifiers

        RETURN_IF_FAILED(DynamicArray<StringResult*>::CreateInstance(pProfile->GetNumThreadAwareQualifiers(), &m_qualifierCaches));

        return S_OK;
    }

    const UnifiedEnvironment* m_Environment;
    const CoreProfile* m_pProfile;
    const IResolver* m_pParentResolver;
    DynamicArray<StringResult*>* m_qualifierCaches;
};

class ResolverBase::DecisionInfoCache : public DefObject
{
public:
    static HRESULT CreateInstance(
        _In_ const IDecisionInfo* pDecisions,
        _In_ const UnifiedEnvironment* pEnvironment,
        _Outptr_ DecisionInfoCache** result)
    {
        *result = nullptr;

        RETURN_HR_IF_NULL(E_INVALIDARG, pDecisions);

        DecisionInfoCache* pRtrn = new DecisionInfoCache(pDecisions, pEnvironment);
        RETURN_IF_NULL_ALLOC(pRtrn);

        *result = pRtrn;
        return S_OK;
    }

    ~DecisionInfoCache() {}

    const IDecisionInfo* GetDecisionInfo() const { return m_pDecisions; }

    typedef struct _QualifierCacheEntry
    {
        UINT32 priority : 10;
        UINT32 score : 10;
        UINT32 fallbackScore : 10;
        UINT32 bAttempted : 1;
        UINT32 pad1 : 1;
    } QualifierCacheEntry;

    typedef struct _QualifierSetCacheEntry
    {
        UINT32 attempted : 1;
        UINT32 isMatch : 1;
        UINT32 isDefault : 1;
        UINT32 isMatchOrDefault : 1;
        UINT32 requireComplexResolution : 1;
        UINT32 bestMatchPriority : 10;
        UINT32 bestMatchScore : 10;
        UINT32 pad : 7;
    } QualifierSetCacheEntry;

    static const UINT16 kDecisionAttemptedMask = 0x8000;

    class QualifierSetComparer
    {
    public:
        void SetScore(_In_ UINT16 priority, _In_ UINT16 matchScore, _In_ UINT16 fallbackScore)
        {
            DEF_ASSERT(priority <= 1000);
            DEF_ASSERT(matchScore <= 1000);
            DEF_ASSERT(fallbackScore <= 1000);

            if (_nextFreeEntry >= ARRAYSIZE(_entries))
            {
                // This should never happen, but in case someone constructs a file that does hit it, just ignore gracefully.
                return;
            }

            // Add entry to the end of the list.
            _entries[_nextFreeEntry].priority = priority;
            _entries[_nextFreeEntry].matchScore = matchScore;
            _entries[_nextFreeEntry].fallbackScore = fallbackScore;

            // Now move entry to the proper position in the list.
            UINT16 currentPosition = _nextFreeEntry;
            while (currentPosition > 0 && _entries[currentPosition].IsStrongerMatch(&_entries[currentPosition - 1]))
            {
                MoveUp(currentPosition);
                currentPosition--;
            }

            _nextFreeEntry++;
        }

        // > 0 this wins
        // < 0 other wins
        // == 0 both are equal
        int Compare(QualifierSetComparer* other)
        {
            // The qualifier set variables are cached but the individual qualifier ones are not.
            // The reason for that is that the set ones are more expensive to compute since we have to walk the list.
            bool thisIsMatch = IsMatch();

            if (thisIsMatch != other->IsMatch())
            {
                return thisIsMatch ? 1 : -1;
            }

            if (!thisIsMatch)
            {
                bool thisIsMatchOrDefault = IsMatchOrDefault();

                if (thisIsMatchOrDefault != other->IsMatchOrDefault())
                {
                    return thisIsMatchOrDefault ? 1 : -1;
                }
            }

            UINT16 jointQualifiers =
                GetNumberOfQualifiers() < other->GetNumberOfQualifiers() ? GetNumberOfQualifiers() : other->GetNumberOfQualifiers();

            // First we compare the match status of a qualifier. If the priority is equal and matches and the other doesn't, the match wins.
            // If match status is equal we check the match score and then fallback score of each qualifier.
            // The higher priority qualifier always takes precendence.
            for (UINT16 i = 0; i < jointQualifiers; i++)
            {
                if (GetPriority(i) > other->GetPriority(i))
                {
                    return IsMatch(i) ? 1 : -1;
                }
                else if (GetPriority(i) < other->GetPriority(i))
                {
                    return other->IsMatch(i) ? -1 : 1;
                }

                if (IsMatch(i) != other->IsMatch(i))
                {
                    return IsMatch(i) ? 1 : -1;
                }

                if (IsMatch(i))
                {
                    int diff = GetMatchScore(i) - other->GetMatchScore(i);

                    if (diff != 0)
                    {
                        return diff;
                    }
                }
                else
                {
                    int diff = GetFallbackScore(i) - other->GetFallbackScore(i);

                    if (diff != 0)
                    {
                        return diff;
                    }
                }
            }

            // If the number of qualifiers is unequal, then there must be extra qualifiers at the end for us to get here.
            // See if the first one of those matches. If so that asset wins else it loses.
            // Why check the first one only, and only for a match? The asset that doesn't have the qualifier is considered neutral.
            // Match > neutral > default. So if the first asset matches, it beats the neutral. But if it doesn't match the neutral wins
            // regardless of the status of any subsequent qualifiers.
            if (GetNumberOfQualifiers() != other->GetNumberOfQualifiers())
            {
                if (GetNumberOfQualifiers() > other->GetNumberOfQualifiers())
                {
                    return IsMatch(jointQualifiers) ? 1 : -1;
                }
                else
                {
                    return other->IsMatch(jointQualifiers) ? -1 : 1;
                }
            }

            return 0;
        }

        // See if the qualifier set is a match, meaning all qualifiers that are present match.
        // All neutral (which has no qualifiers at all) IS considered a match.
        bool IsMatch()
        {
            for (UINT16 i = 0; i < _nextFreeEntry; i++)
            {
                if (!IsMatch(i))
                {
                    return false;
                }
            }

            return true;
        }

        // See if the qualifier set is either a match or default, meaning no qualifier is a non-match.
        // This is not the same as isMatch | isDefault, because you could have an asset where one qualifier matches and one
        // is the default, and another qualifier where the reverse is true.
        // That asset would neither be a match nor a default, but it would qualify here.
        bool IsMatchOrDefault()
        {
            for (UINT16 i = 0; i < _nextFreeEntry; i++)
            {
                if (!IsDefault(i) && !IsMatch(i))
                {
                    return false;
                }
            }

            return true;
        }

        UINT16 GetNumberOfQualifiers() { return _nextFreeEntry; }

    private:
        bool IsMatch(UINT16 entry) { return (_entries[entry].matchScore > 0); }

        bool IsDefault(UINT16 entry) { return (_entries[entry].fallbackScore > 0); }

        UINT16 GetMatchScore(UINT16 entry) { return _entries[entry].matchScore; }

        UINT16 GetFallbackScore(UINT16 entry) { return _entries[entry].fallbackScore; }

        UINT16 GetPriority(UINT16 entry) { return _entries[entry].priority; }

        void MoveUp(UINT16 entryToMove)
        {
            DEF_ASSERT(entryToMove > 0);

            QualifierEntry temp = _entries[entryToMove - 1];
            _entries[entryToMove - 1] = _entries[entryToMove];
            _entries[entryToMove] = temp;
        }

        typedef struct _QualifierEntry
        {
            UINT32 priority : 10;
            UINT32 matchScore : 10;
            UINT32 fallbackScore : 10;
            UINT32 pad : 2;

            bool IsStrongerMatch(struct _QualifierEntry* other)
            {
                if (priority != other->priority)
                {
                    return (priority > other->priority);
                }

                if (matchScore != other->matchScore)
                {
                    return (matchScore > other->matchScore);
                }

                if (fallbackScore != other->fallbackScore)
                {
                    return (fallbackScore > other->fallbackScore);
                }

                // If two qualifiers are exactly identical, return false to reduce the sorting cost.
                return false;
            }
        } QualifierEntry;

        // An arbitrary but high limit. We want it to be high enough to never hit it
        // but also low enough to ensure we don't use too much stack space.
        QualifierEntry _entries[50];
        UINT16 _nextFreeEntry = 0;
    };

    void Reset()
    {
        // using UNREFERENCED_PARAMETER because prefast complains about inconsisten
        // annotation if I comment out pStatus.
        AutoReaderWriterLock autoLock(&m_srwLock);

        _QualifierCacheEntry* pCachedQualifiers = m_qualifierCache.GetAll();
        for (unsigned int i = 0; i < m_qualifierCache.Count(); ++i)
        {
            (pCachedQualifiers + i)->bAttempted = 0;
        }
        m_qualifierCache.Reset();

        QualifierSetCacheEntry* pCachedQualifierSets = m_qualifierSetCache.GetAll();
        for (unsigned int i = 0; i < m_qualifierSetCache.Count(); ++i)
        {
            (pCachedQualifierSets + i)->attempted = 0;
        }
        m_qualifierSetCache.Reset();

        UINT16* pCachedDecision = m_decisionCache.GetAll();
        for (unsigned int i = 0; i < m_decisionCache.Count(); ++i)
        {
            *(pCachedDecision + i) &= ~kDecisionAttemptedMask;
        }
        m_decisionCache.Reset();

        m_decisionPerSetInfo.Reset();
    }

    void Reset(_In_ Atom)
    {
        // TODO: qualifier based reset instead of All.
        return Reset();
    }

    HRESULT GetQualifierScores(_In_ const IQualifier* pQualifier, _Out_ UINT16* pScoreOut, _Out_ UINT16* pFallbackScoreOut)
    {
        int index;
        RETURN_IF_FAILED(pQualifier->GetQualifierIndex(&index));

        AutoReaderWriterLock autoLock(&m_srwLock, true);
        QualifierCacheEntry* pEntries = m_qualifierCache.GetAll();
        if ((index < 0) || (index >= m_qualifierCache.Count()) || (!pEntries[index].bAttempted))
        {
            *pScoreOut = 0;
            *pFallbackScoreOut = 0;
            return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
        }

        *pScoreOut = pEntries[index].score;
        *pFallbackScoreOut = pEntries[index].fallbackScore;
        return S_OK;
    }

    HRESULT SetQualifierScores(_In_ const IQualifier* pQualifier, _In_ int priority, _In_ UINT16 score, _In_ UINT16 fallbackScore)
    {
        int index;
        RETURN_IF_FAILED(pQualifier->GetQualifierIndex(&index));

        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), (index < 0) || (index > m_pDecisions->GetNumQualifiers() - 1));
        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), (priority < 0) || (priority > ResourceQualifier::MaxPriority));
        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), (score < 0) || (score > IQualifier::MaxFallbackScore));
        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), (fallbackScore < 0) || (fallbackScore > IQualifier::MaxFallbackScore));

        AutoReaderWriterLock autoLock(&m_srwLock);
        if (index >= m_qualifierCache.Count())
        {
            // decision info has grown since we were initialized
            // but we weren't able to grow our cache.
            RETURN_IF_FAILED(m_qualifierCache.SetExtent(m_pDecisions->GetNumQualifiers()));
        }

        QualifierCacheEntry entry;
        entry.bAttempted = 1;
        entry.priority = priority;
        entry.score = score;
        entry.fallbackScore = fallbackScore;
        RETURN_IF_FAILED(m_qualifierCache.Set(index, entry));

        return S_OK;
    }

    HRESULT GetQualifierSetResults(
        _In_ const IQualifierSet* pQualifierSet,
        _Out_ bool* pbIsMatchOut,
        _Out_ bool* pbIsDefaultOut,
        _Out_ bool* pbIsMatchOrDefaultOut,
        _Out_opt_ UINT16* pBestActualMatchScoreOut = NULL,
        _Out_opt_ UINT16* pBestActualMatchPriorityOut = NULL)
    {
        int index;
        RETURN_IF_FAILED(pQualifierSet->GetIndex(&index));

        AutoReaderWriterLock autoLock(&m_srwLock, true);

        QualifierSetCacheEntry* pEntries = m_qualifierSetCache.GetAll();
        if ((index < 0) || (index >= m_qualifierSetCache.Count()) || (!pEntries[index].attempted))
        {
            *pbIsMatchOut = *pbIsDefaultOut = *pbIsMatchOrDefaultOut = false;
            if (pBestActualMatchScoreOut)
            {
                *pBestActualMatchScoreOut = 0;
            }
            if (pBestActualMatchPriorityOut)
            {
                *pBestActualMatchPriorityOut = 0;
            }
            return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
        }

        *pbIsMatchOut = (pEntries[index].isMatch != 0);
        *pbIsDefaultOut = (pEntries[index].isDefault != 0);
        *pbIsMatchOrDefaultOut = (pEntries[index].isMatchOrDefault != 0);

        if (pBestActualMatchScoreOut)
        {
            *pBestActualMatchScoreOut = pEntries[index].bestMatchScore;
        }
        if (pBestActualMatchPriorityOut)
        {
            *pBestActualMatchPriorityOut = pEntries[index].bestMatchPriority;
        }

        return S_OK;
    }

    HRESULT GetQualifierSetCacheEntry(_In_ int index, _Out_ const QualifierSetCacheEntry** ppQualifierSetResult)
    {
        AutoReaderWriterLock autoLock(&m_srwLock, true);

        QualifierSetCacheEntry* pEntries = m_qualifierSetCache.GetAll();
        if ((index < 0) || (index >= m_qualifierSetCache.Count()) || (!pEntries[index].attempted))
        {
            *ppQualifierSetResult = NULL;
            return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
        }

        *ppQualifierSetResult = &pEntries[index];
        return S_OK;
    }

    HRESULT SetQualifierSetResults(
        _In_ const IQualifierSet* pQualifierSet,
        _In_ bool isMatch,
        _In_ bool isDefaultMatch,
        _In_ bool isMatchOrDefault,
        _In_ bool requireComplexResolution,
        _In_ UINT16 bestActualMatchPriority,
        _In_ UINT16 bestActualMatchScore)
    {
        int index;
        RETURN_IF_FAILED(pQualifierSet->GetIndex(&index));

        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), (index < 0) || (index > m_pDecisions->GetNumQualifierSets() - 1));
        RETURN_HR_IF(
            HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND),
            (bestActualMatchPriority < 0) || (bestActualMatchPriority > IQualifier::MaxFallbackScore));
        RETURN_HR_IF(
            HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), (bestActualMatchScore < 0) || (bestActualMatchScore > IQualifier::MaxFallbackScore));

        AutoReaderWriterLock autoLock(&m_srwLock);
        if (index >= m_qualifierSetCache.Count())
        {
            // decision info has grown since we were initialized
            // but we weren't able to grow our cache.
            RETURN_IF_FAILED(m_qualifierSetCache.SetExtent(m_pDecisions->GetNumQualifierSets()));
        }

        QualifierSetCacheEntry entry;
        entry.attempted = 1;
        entry.isMatch = (isMatch ? 1 : 0);
        entry.isDefault = (isDefaultMatch ? 1 : 0);
        entry.isMatchOrDefault = (isMatchOrDefault ? 1 : 0);
        entry.requireComplexResolution = (requireComplexResolution ? 1 : 0);
        entry.bestMatchPriority = bestActualMatchPriority;
        entry.bestMatchScore = bestActualMatchScore;

        RETURN_IF_FAILED(m_qualifierSetCache.Set(index, entry));

        return S_OK;
    }

    typedef struct _DecisionPerSetInfo
    {
        UINT16 setIndexInDecision;
        UINT16 setIndexInPool;
    } DecisionPerSetInfo;

    HRESULT GetDecisionResults(
        _In_ const IDecision* pDecision,
        _In_ int numResults,
        _Out_writes_(numResults) int* pSetIndexesInDecisionOut,
        _Out_writes_(numResults) int* pSetIndexesInPoolOut)
    {
        int index;
        RETURN_IF_FAILED(pDecision->GetIndex(&index));

        UINT16 offset = 0;

        AutoReaderWriterLock autoLock(&m_srwLock, true);
        if ((index < 0) || (index >= m_decisionCache.Count()) || (!m_decisionCache.TryGet(index, &offset)) ||
            ((offset & kDecisionAttemptedMask) == 0))
        {
            // out of range or not attempted
            return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
        }

        // mask off the bit that indicates that the decision was cached
        offset &= ~kDecisionAttemptedMask;

        int numDecisionResults = pDecision->GetNumQualifierSets();
        numResults = min(numResults, numDecisionResults);

        DEF_ASSERT((offset + numResults) <= m_decisionPerSetInfo.Count());

        const DecisionPerSetInfo* pSets = &m_decisionPerSetInfo.GetAll()[offset];
        for (int i = 0; (i < numResults); i++)
        {
            pSetIndexesInDecisionOut[i] = pSets[i].setIndexInDecision;
            pSetIndexesInPoolOut[i] = pSets[i].setIndexInPool;
        }
        return S_OK;
    }

    HRESULT
    BeginSetDecisionResults(_In_ const IDecision* pDecision, _Out_writes_(*pNumSetsOut) DecisionPerSetInfo** result, _Out_ int* pNumSetsOut)
    {
        *result = nullptr;
        *pNumSetsOut = 0;

        int index;
        RETURN_IF_FAILED(pDecision->GetIndex(&index));

        AutoReaderWriterLock autoLock(&m_srwLock);
        DEF_ASSERT((index >= 0) && (index < m_pDecisions->GetNumDecisions()));

        if (index >= m_decisionCache.Count())
        {
            // couldn't extend the cache
            RETURN_IF_FAILED(m_decisionCache.SetExtent(m_pDecisions->GetNumDecisions()));
        }

        UINT16* pCachedDecision = &m_decisionCache.GetAll()[index];

        // We have our entry in the decision cache, now we need to figure
        // out where the qualifier set data will go.
        int offset = m_decisionPerSetInfo.Count();
        int numSets = pDecision->GetNumQualifierSets();

        // If there are no qualifier sets, return with MRM_NO_MATCHING_CANDIDATE
        // If we can't extend, SetExtent reports the error.
        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_NO_MATCH_OR_DEFAULT_CANDIDATE), numSets == 0);
        RETURN_IF_FAILED(m_decisionPerSetInfo.SetExtent(offset + numSets));

        DecisionPerSetInfo* pSets = &m_decisionPerSetInfo.GetAll()[offset];
        SecureZeroMemory(pSets, numSets * sizeof(DecisionPerSetInfo));

        // Set the offset in the cached decisions, but don't set the attempted bit
        // until EndDecisionResults
        *pCachedDecision = static_cast<UINT16>(offset);
        *pNumSetsOut = numSets;
        *result = pSets;

        return S_OK;
    }

    HRESULT EndSetDecisionResults(_In_ const IDecision* pDecision)
    {
        int index;
        RETURN_IF_FAILED(pDecision->GetIndex(&index));

        AutoReaderWriterLock autoLock(&m_srwLock);
        DEF_ASSERT((index >= 0) && (index < m_pDecisions->GetNumDecisions()) && (index < m_decisionCache.Count()));

        UINT16* pCachedDecision = &m_decisionCache.GetAll()[index];

        (*pCachedDecision) |= kDecisionAttemptedMask;

        return S_OK;
    }

    // Comments out below lock held as OACR can't understand ReadWriterLock.
    // _Requires_lock_held_(ResolverBase::m_srwLock)
    // _Requires_lock_held_(ResolverBase::m_srwQualifierSetLock)
    int CompareQualifierSetResults(_In_ int setIndexInPool1, _In_ int setIndexInPool2, _Inout_ const IResolver* pResolver)
    {
        if ((setIndexInPool1 < 0) || (setIndexInPool1 > m_qualifierSetCache.Count() - 1))
        {
            return 0;
        }

        if ((setIndexInPool2 < 0) || (setIndexInPool2 > m_qualifierSetCache.Count() - 1))
        {
            return 0;
        }

        QualifierSetCacheEntry* pEntries = m_qualifierSetCache.GetAll();
        const DecisionInfoCache::QualifierSetCacheEntry* pEntry1 = &pEntries[setIndexInPool1];
        const DecisionInfoCache::QualifierSetCacheEntry* pEntry2 = &pEntries[setIndexInPool2];

        int diff = 0;

        // Entries that haven't been attempted yet come last.
        if (pEntry1->attempted != pEntry2->attempted)
        {
            return (pEntry1->attempted ? 1 : -1);
        }
        else if (!pEntry1->attempted)
        {
            return 0;
        }

        if (pEntry1->isMatch && pEntry2->isMatch)
        {
            // sorting the matches
            diff = pEntry1->bestMatchPriority - pEntry2->bestMatchPriority; // highest priority wins
            if (diff == 0)
            {
                diff = pEntry1->bestMatchScore - pEntry2->bestMatchScore;
                if (diff == 0)
                {
                    diff = (pEntry1->requireComplexResolution == 1 || pEntry2->requireComplexResolution == 1) ?
                               CompareQualifierSetResultComplex(setIndexInPool1, setIndexInPool2, pResolver) :
                               CompareQualifierSetResultDetails(setIndexInPool1, setIndexInPool2, pResolver);
                }
            }
        }
        else if (!pEntry1->isMatch && !pEntry2->isMatch)
        {
            // sorting the not matches (looking for fallback candidates)
            if (pEntry1->isMatchOrDefault != pEntry2->isMatchOrDefault)
            {
                diff = (pEntry1->isMatchOrDefault ? 1 : -1);
            }
            // Do not test default here.  If both are !isMatchOrDefault, then both are also !isDefault by definition.
            // If both are isMatchOrDefault, then any non-default qualifiers match, so we don't care that they're non-default.
            else
            {
                diff = (pEntry1->requireComplexResolution == 1 || pEntry2->requireComplexResolution == 1) ?
                           CompareQualifierSetResultComplex(setIndexInPool1, setIndexInPool2, pResolver) :
                           CompareQualifierSetResultDetails(setIndexInPool1, setIndexInPool2, pResolver);
            }
        }
        else
        {
            diff = pEntry1->isMatch ? 1 : -1;
        }

        return diff;
    }

    typedef struct _DecisionSortingInfo
    {
        DecisionInfoCache* pCache;
        const IResolver* pResolver;
    } _DecisionSortingInfo;

    // helper function for decision results
    static int __cdecl _DecisionSortingHelper(
        _DecisionSortingInfo* pSortingContextInfo,
        const _DecisionPerSetInfo* pResult1,
        const _DecisionPerSetInfo* pResult2)
    {
        int diff = pSortingContextInfo->pCache->CompareQualifierSetResults(
            pResult1->setIndexInPool, pResult2->setIndexInPool, pSortingContextInfo->pResolver);
        // If the two decision results compare identically, position in the decision is the final tie breaker.
        if (diff != 0)
        {
            return -diff;
        }

        // qsort sorts in ascending order, so invert the sense of the comparison
        if (pResult1->setIndexInDecision < pResult2->setIndexInDecision)
        {
            return 1;
        }
        else if (pResult1->setIndexInDecision > pResult2->setIndexInDecision)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }

protected:
    const IDecisionInfo* m_pDecisions;
    const UnifiedEnvironment* m_pEnvironment;

    DynamicArray<QualifierCacheEntry> m_qualifierCache;
    DynamicArray<QualifierSetCacheEntry> m_qualifierSetCache;
    DynamicArray<DecisionPerSetInfo> m_decisionPerSetInfo;
    DynamicArray<UINT16> m_decisionCache;

    DecisionInfoCache(_In_ const IDecisionInfo* pDecisions, _In_ const UnifiedEnvironment* pEnvironment) :
        m_pDecisions(pDecisions),
        m_pEnvironment(pEnvironment),
        m_qualifierCache(),
        m_qualifierSetCache(),
        m_decisionPerSetInfo(),
        m_decisionCache()
    {
        ::InitializeSRWLock(&m_srwLock);
    }

    int CompareQualifierSetResultDetails(_In_ int setIndexInPool1, _In_ int setIndexInPool2, _In_ const IResolver* pResolver)
    {
        QualifierSetResult set1;
        QualifierSetResult set2;

        if (FAILED(m_pDecisions->GetQualifierSet(setIndexInPool1, &set1)) || FAILED(m_pDecisions->GetQualifierSet(setIndexInPool2, &set2)))
        {
            return 0;
        }

        int q1;
        int q2;
        _QualifierCacheEntry* pQualifiers = m_qualifierCache.GetAll();
        _QualifierCacheEntry* pQ1;
        _QualifierCacheEntry* pQ2;

        for (int i = 0; i < set1.GetNumQualifiers(); i++)
        {
            // Get the next qualifier from set 1
            if (FAILED(set1.GetQualifierIndexInPool(i, &q1)) || (q1 < 0) || (q1 > m_qualifierCache.Count() - 1))
            {
                // error, can't continue.
                return 0;
            }
            pQ1 = &pQualifiers[q1];

            // See if set 2 also has a qualifier
            if (i >= set2.GetNumQualifiers())
            {
                // Nope.  See who wins - neutral beats fallback or failure to match,
                return ((pQ1->score > 0) ? 1 : -1);
            }

            // Get the qualifier from set 2
            if (FAILED(set2.GetQualifierIndexInPool(i, &q2)) || (q2 < 0) || (q2 > m_qualifierCache.Count() - 1))
            {
                // error, can't continue.
                return 0;
            }
            pQ2 = &pQualifiers[q2];

            if (pQ2->priority > pQ1->priority)
            {
                // The qualifier in set 2 is higher priority than the qualifier in
                // set 1, which means that set 1 is effectively neutral in that
                // dimension.  If set 2 is an actual match, it wins.  If set 2
                // is a fallback or not a match at all, it loses.
                return ((pQ2->score > 0) ? -1 : 1);
            }
            else if (pQ1->priority > pQ2->priority)
            {
                // set 2 is neutral relative to the dimension in set 1.
                return ((pQ1->score > 0) ? 1 : -1);
            }

            // Priorities match.

            // qualifiers that haven't been attempted yet lose
            if (pQ1->bAttempted != pQ2->bAttempted)
            {
                return (pQ1->bAttempted ? 1 : -1);
            }
            else if (!pQ1->bAttempted)
            {
                return -1;
            }

            if (pQ1->score > 0)
            {
                // first qualifier matched
                if (pQ2->score < 1)
                {
                    // second qualifier didn't match, first wins.
                    return 1;
                }

                // both matched.  Priority comes next, then score.
                int diff = ((pQ1->priority == pQ2->priority) ? (pQ1->score - pQ2->score) : (pQ1->priority - pQ2->priority));

                if (diff != 0)
                {
                    // priority or score differs, we have a winner.
                    return diff;
                }

                // keep looking
            }
            else if (pQ2->score > 0)
            {
                // second qualifier matched, first didn't.  Second wins.
                return -1;
            }
            else if (pQ1->fallbackScore > 0)
            {
                // Nobody matched but first qualifier is a fallback
                if (pQ2->fallbackScore < 1)
                {
                    // Second qualifier isn't a fallback, first wins.
                    return 1;
                }

                // both are fallbacks.  Try priority, then fallback score.
                int diff = ((pQ1->priority == pQ2->priority) ? (pQ1->fallbackScore - pQ2->fallbackScore) : (pQ1->priority - pQ2->priority));

                if (diff != 0)
                {
                    // priority or fallback score differs, we have a winner.
                    return diff;
                }

                // keep looking
            }
            else if (pQ2->fallbackScore > 0)
            {
                // second qualifier is a fallback, first isn't.  Second wins.
                return -1;
            }

            // Everything matches.  Qualifier type gets to break the tie.
            int diff = CompareQualiferType(q1, q2, pResolver);
            if (diff != 0)
            {
                return diff;
            }
        }

        if (set2.GetNumQualifiers() > set1.GetNumQualifiers())
        {
            // Set 2 is more specific.  See who wins.
            if (FAILED(set2.GetQualifierIndexInPool(set1.GetNumQualifiers(), &q2)) || (q2 < 0) || (q2 > m_qualifierCache.Count() - 1))
            {
                // error, can't continue.
                return 0;
            }
            pQ2 = &pQualifiers[q2];
            return ((pQ2->score > 0) ? -1 : 1);
        }

        // Identical
        return 0;
    }

    int CompareQualifierSetResultComplex(_In_ int setIndexInPool1, _In_ int setIndexInPool2, _In_ const IResolver* resolver)
    {
        QualifierSetResult set1;
        QualifierSetResult set2;

        if (FAILED(m_pDecisions->GetQualifierSet(setIndexInPool1, &set1)) || FAILED(m_pDecisions->GetQualifierSet(setIndexInPool2, &set2)))
        {
            return 0;
        }

        int q1;
        int q2;
        _QualifierCacheEntry* pQualifiers = m_qualifierCache.GetAll();
        _QualifierCacheEntry* pQ1;
        _QualifierCacheEntry* pQ2;

        QualifierSetComparer comparer1;
        QualifierSetComparer comparer2;

        for (int i = 0; i < set1.GetNumQualifiers(); i++)
        {
            if (FAILED(set1.GetQualifierIndexInPool(i, &q1)) || (q1 < 0) || (q1 > m_qualifierCache.Count() - 1))
            {
                return 0;
            }

            pQ1 = &pQualifiers[q1];

            comparer1.SetScore(pQ1->priority, pQ1->score, pQ1->fallbackScore);
        }

        for (int i = 0; i < set2.GetNumQualifiers(); i++)
        {
            if (FAILED(set2.GetQualifierIndexInPool(i, &q2)) || (q2 < 0) || (q2 > m_qualifierCache.Count() - 1))
            {
                return 0;
            }

            pQ2 = &pQualifiers[q2];

            comparer2.SetScore(pQ2->priority, pQ2->score, pQ2->fallbackScore);
        }

        int diff = comparer1.Compare(&comparer2);
        if (diff != 0)
        {
            return diff;
        }

        // Everything matches. Qualifier type gets to break the tie.
        for (int i = 0; i < set1.GetNumQualifiers() && i < set2.GetNumQualifiers(); i++)
        {
            // We already checked for range correctness above so no need to do it again.
            if (FAILED(set1.GetQualifierIndexInPool(i, &q1)))
            {
                return 0;
            }

            if (FAILED(set2.GetQualifierIndexInPool(i, &q2)))
            {
                return 0;
            }

            // Everything matches. Qualifier type gets to break the tie.
            diff = CompareQualiferType(q1, q2, resolver);
            if (diff != 0)
            {
                return diff;
            }
        }

        // Identical.
        return 0;
    }

    int CompareQualiferType(_In_ int qualifier1, _In_ int qualifier2, _In_ const IResolver* resolver)
    {
        QualifierResult qr1;
        QualifierResult qr2;
        Atom qa1;
        Atom qa2;
        const IBuildQualifierType* type;
        StringResult value;

        if (SUCCEEDED(m_pDecisions->GetQualifier(qualifier1, &qr1)) && SUCCEEDED(m_pDecisions->GetQualifier(qualifier2, &qr2)) &&
            SUCCEEDED(qr1.GetOperand1Qualifier(&qa1)) && SUCCEEDED(qr2.GetOperand1Qualifier(&qa2)) && (qa1 == qa2) &&
            SUCCEEDED(m_pEnvironment->GetTypeOfQualifier(qa1, &type)) && SUCCEEDED(resolver->GetQualifierValue(qa1, &value)))
        {
            // Qualifier type can only break the tie if both qualifiers use the same attribute.
            DEFCOMPARISON result;
            type->CompareForValue(&qr1, &qr2, value.GetRef(), &result);
            return static_cast<int>(result);
        }

        return 0;
    }

private:
    SRWLOCK m_srwLock;
};

ResolverBase::ResolverBase(_In_ const UnifiedEnvironment* pEnvironment, _In_ const IDecisionInfo* pDecisions) :
    m_pEnvironment(pEnvironment), m_pDecisions(pDecisions), m_pCache(NULL)
{
    ::InitializeSRWLock(&m_srwLock);
    ::InitializeSRWLock(&m_srwQualifierSetLock);
    ::InitializeSRWLock(&m_srwQualifierLock);
}

ResolverBase::~ResolverBase() { delete m_pCache; }

HRESULT ResolverBase::Init()
{
    RETURN_IF_FAILED(DecisionInfoCache::CreateInstance(m_pDecisions, m_pEnvironment, &m_pCache));

    return S_OK;
}

void ResolverBase::Reset()
{
    // Frequent reset during evalueDecision can corrupt the cache.
    // Order is important here, m_srwLock -> m_srwQualifierSetLock -> m_srwQualifierLock.
    // We consider to have separate scope for respective m_srwLock and m_srwQualifierSetLock in future.
    AutoReaderWriterLock autoLock(&m_srwLock);
    {
        AutoReaderWriterLock autoQualifierSetLock(&m_srwQualifierSetLock); // protect pResults object for potential race condition
        {
            AutoReaderWriterLock autoQualifierLock(&m_srwQualifierLock); // protect pResults object for potential race condit
            {
                // the cache doesn't do anythnig interesting with per-qualifier reset yet so just reset the whole thing.
                m_pCache->Reset();
            }
        }
    }
}

HRESULT ResolverBase::Reset(__in_ecount(numQualifierNames) Atom* pQualifierNames, _In_ int numQualifierNames)
{
    RETURN_HR_IF(
        E_INVALIDARG, (pQualifierNames == nullptr) || (numQualifierNames < 1) || (numQualifierNames > m_pDecisions->GetNumQualifiers()));

    // Frequent reset during evalueDecision can corrupt the cache.
    // Order is important here, m_srwLock -> m_srwQualifierSetLock -> m_srwQualifierLock.
    // We consider to have separate scope for respective m_srwLock and m_srwQualifierSetLock in future.
    AutoReaderWriterLock autoLock(&m_srwLock);
    {
        AutoReaderWriterLock autoQualifierSetLock(&m_srwQualifierSetLock); // protect pResults object for potential race condition
        {
            AutoReaderWriterLock autoQualifierLock(&m_srwQualifierLock); // protect pResults object for potential race condit
            {
                // the cache doesn't do anythnig interesting with per-qualifier reset yet so just reset the whole thing.
                m_pCache->Reset();
            }
        }
    }

    return S_OK;
}

HRESULT ResolverBase::EvaluateQualifier(_In_ const IQualifier* pQualifier, _Out_ double* pScoreOut, _Out_ double* pFallbackScoreOut) const
{
    UINT16 score = 0;
    UINT16 fallbackScore = 0;

    RETURN_IF_FAILED(EvaluateQualifier(pQualifier, &score, &fallbackScore));

    RETURN_IF_FAILED(IQualifier::ToDoubleScore(score, pScoreOut));
    RETURN_IF_FAILED(IQualifier::ToDoubleScore(fallbackScore, pFallbackScoreOut));
    return S_OK;
}

HRESULT ResolverBase::EvaluateQualifier(_In_ const IQualifier* pQualifier, _Out_ UINT16* pScoreOut, _Out_ UINT16* pFallbackScoreOut) const
{
    // Have we seen this qualifier before?
    if (SUCCEEDED(m_pCache->GetQualifierScores(pQualifier, pScoreOut, pFallbackScoreOut)))
    {
        return S_OK;
    }

    double score = 0.0;
    double fallbackScore;
    RETURN_IF_FAILED(pQualifier->GetFallbackScore(&fallbackScore));

    // Nope. Try to evaluate it.
    Atom qualifierName;
    const IBuildQualifierType* pType = NULL;
    StringResult value;

    // The method can be called by (1) under m_srwLock and m_srwQualifierSetLock exclusive lock, or (2) no lock
    AutoReaderWriterLock autoLock(&m_srwQualifierLock);

    HRESULT hr = pQualifier->GetOperand1Attribute(&qualifierName);
    if (SUCCEEDED(hr))
    {
        hr = m_pEnvironment->GetTypeOfQualifier(qualifierName, &pType);
    }

    if (SUCCEEDED(hr))
    {
        hr = GetQualifierValue(qualifierName, &value);
    }

    if (SUCCEEDED(hr))
    {
        // looks good, get a score
        (void)pType->Evaluate(pQualifier, value.GetRef(), &score);
    }

    if (hr == HRESULT_FROM_WIN32(ERROR_MRM_UNKNOWN_QUALIFIER))
    {
        // treat invalid qualifiers as if they're just unknown
        hr = S_OK;
        score = 0.0;
    }

    // Get score even if failed. EvaluateQualifierSet() will ignore the error
    // from this function, and still use fallbackScore for evaluation.
    RETURN_IF_FAILED(IQualifier::ToUint16Score(score, pScoreOut));
    RETURN_IF_FAILED(IQualifier::ToUint16Score(fallbackScore, pFallbackScoreOut));
    RETURN_IF_FAILED(m_pCache->SetQualifierScores(pQualifier, pQualifier->GetPriority(), *pScoreOut, *pFallbackScoreOut));
    return hr;
}

HRESULT ResolverBase::EvaluateQualifierSet(
    _In_ const IQualifierSet* pQualifierSet,
    _Out_ bool* pbIsMatchOut,
    _Out_ bool* pbIsDefaultOut,
    _Out_ bool* pbIsMatchOrDefaultOut,
    _Out_opt_ UINT16* pScoreOut = NULL) const
{
    // Have we seen this qualifier set before
    if (SUCCEEDED(m_pCache->GetQualifierSetResults(pQualifierSet, pbIsMatchOut, pbIsDefaultOut, pbIsMatchOrDefaultOut, pScoreOut)))
    {
        return S_OK;
    }

    // Nope.  Try to evaluate it.
    bool bIsMatch = true;
    bool bIsDefault = true;
    bool bIsMatchOrDefault = true;
    bool bMultipleOfSameQualifier = false;
    UINT16 bestActualMatchPriority = 0;
    UINT16 bestActualMatchScore = 0;
    UINT16 score;
    UINT16 fallbackScore;
    int lastQualifierPriority = 0;

    // The method can be called by (1) under m_srwLock exclusive lock, or (2) no lock
    AutoReaderWriterLock autoLock(&m_srwQualifierSetLock);

    int numQualifiers = pQualifierSet->GetNumQualifiers();
    if (numQualifiers > 0)
    {
        QualifierResult qualifier;
        for (int i = 0; (i < numQualifiers) && (bIsMatch || bIsDefault || bIsMatchOrDefault); i++)
        {
            score = fallbackScore = 0;
            if (FAILED(pQualifierSet->GetQualifier(i, &qualifier)) || FAILED(EvaluateQualifier(&qualifier, &score, &fallbackScore)))
            {
                // some kind of error occurred.  Just treat it as if it's no match.
                bIsMatch = false;
            }
            else
            {
                // This, like the rest of the code, relies on the fact that the qualifiers are sorted in priority order.
                if (qualifier.GetPriority() == lastQualifierPriority)
                {
                    bMultipleOfSameQualifier = true;
                }

                lastQualifierPriority = qualifier.GetPriority();
            }

            bIsMatch = bIsMatch && (score > 0);
            bIsDefault = bIsDefault && (fallbackScore > 0);
            bIsMatchOrDefault = bIsMatchOrDefault && ((fallbackScore > 0) || (score > 0));

            if ((score > 0) && (qualifier.GetPriority() >= bestActualMatchPriority))
            {
                bestActualMatchPriority = static_cast<UINT16>(qualifier.GetPriority());
                bestActualMatchScore = max(bestActualMatchScore, score);
            }
        }
    }
    else
    {
        // neutral is not default
        bIsDefault = false;
        bestActualMatchScore = IQualifier::MaxFallbackScore;
    }

    *pbIsMatchOut = bIsMatch;
    *pbIsDefaultOut = bIsDefault;
    *pbIsMatchOrDefaultOut = bIsMatchOrDefault;

    if (pScoreOut != nullptr)
    {
        *pScoreOut = bestActualMatchScore;
    }

    RETURN_IF_FAILED(m_pCache->SetQualifierSetResults(
        pQualifierSet, bIsMatch, bIsDefault, bIsMatchOrDefault, bMultipleOfSameQualifier, bestActualMatchPriority, bestActualMatchScore));

    return S_OK;
}

HRESULT
ResolverBase::EvaluateDecision(_In_ const IDecision* pDecision, _Out_ int* pResultIndexOut, _Inout_ QualifierSetResult* pResultSetOut) const
{
    int setIndexInPool = 0;

    RETURN_IF_FAILED(EvaluateDecision(pDecision, 1, pResultIndexOut, &setIndexInPool));
    RETURN_IF_FAILED(m_pDecisions->GetQualifierSet(setIndexInPool, pResultSetOut));

    return S_OK;
}

HRESULT ResolverBase::EvaluateDecision(
    _In_ const IDecision* pDecision,
    _In_ int numResults,
    _Out_writes_(numResults) int* pResultIndexesOut,
    _Out_writes_(numResults) int* pResultSetIndexesOut) const
{
    AutoReaderWriterLock autoLock(&m_srwLock); // protect pResults object for potential race condition

    if (SUCCEEDED(m_pCache->GetDecisionResults(pDecision, numResults, pResultIndexesOut, pResultSetIndexesOut)))
    {
        return S_OK;
    }
    int numSets = 0;
    DecisionInfoCache::DecisionPerSetInfo* pResults;
    RETURN_IF_FAILED(m_pCache->BeginSetDecisionResults(pDecision, &pResults, &numSets));
    DEF_ASSERT(numSets == pDecision->GetNumQualifierSets());

    QualifierSetResult qualifierSet;
    int indexInPool;
    bool bIsMatch;
    bool bIsFallbackMatch;
    bool bIsMatchOrDefault;
    const DecisionInfoCache::QualifierSetCacheEntry* pEntry;

    // We'll put matches at the head and non-matches at the tail
    int nextMatch = 0;
    int nextFailed = numSets - 1;
    for (int i = 0; i < numSets; i++)
    {
        if (FAILED(pDecision->GetQualifierSet(i, &qualifierSet, &indexInPool)) ||
            FAILED(EvaluateQualifierSet(&qualifierSet, &bIsMatch, &bIsFallbackMatch, &bIsMatchOrDefault)) ||
            FAILED(m_pCache->GetQualifierSetCacheEntry(indexInPool, &pEntry)))
        {
            // something went badly wrong.  Count this set as a failure.
            bIsMatch = bIsFallbackMatch = bIsMatchOrDefault = false;
        }

        // Okay, we now have our qualifier set, our index in the global pool and our cache entry.
        if (bIsMatch)
        {
            pResults[nextMatch].setIndexInDecision = static_cast<UINT16>(i);
            pResults[nextMatch].setIndexInPool = static_cast<UINT16>(indexInPool);
            nextMatch++;
        }
        else
        {
            pResults[nextFailed].setIndexInDecision = static_cast<UINT16>(i);
            pResults[nextFailed].setIndexInPool = static_cast<UINT16>(indexInPool);
            nextFailed--;
        }
    }

    // Sort the results so that the matches are prioritized ahead of the fallbacks, ahead of the non-matches
    DEF_ASSERT(nextFailed + 1 == nextMatch);
    DecisionInfoCache::_DecisionSortingInfo sortingContextInfo = {m_pCache, this};

    AutoReaderWriterLock autoQualifierSetLock(&m_srwQualifierSetLock);
    qsort_s(
        pResults,
        numSets,
        sizeof(*pResults),
        (int(__cdecl*)(void*, const void*, const void*))DecisionInfoCache::_DecisionSortingHelper,
        &sortingContextInfo);
    RETURN_IF_FAILED(m_pCache->EndSetDecisionResults(pDecision));

    RETURN_IF_FAILED(m_pCache->GetDecisionResults(pDecision, numResults, pResultIndexesOut, pResultSetIndexesOut));

    return S_OK;
}

class ProviderResolver::PerQualifierPoolInfo : public DefObject
{
public:
    static HRESULT CreateInstance(_In_ const IAtomPool* pPool, _Outptr_ PerQualifierPoolInfo** result)
    {
        *result = nullptr;
        RETURN_HR_IF_NULL(E_INVALIDARG, pPool);

        AutoDeletePtr<PerQualifierPoolInfo> pRtrn = new PerQualifierPoolInfo(pPool);
        RETURN_IF_NULL_ALLOC(pRtrn);
        RETURN_IF_FAILED(pRtrn->Init());

        *result = pRtrn.Detach();
        return S_OK;
        ;
    }

    ~PerQualifierPoolInfo()
    {
        if (m_pProviders != NULL)
        {
            for (unsigned i = 0; i < m_pProviders->Count(); i++)
            {
                if ((m_ownedProviders & (1 << i)) != 0)
                {
                    IQualifierValueProvider* pProvider;
                    if (SUCCEEDED(m_pProviders->Get(i, &pProvider)))
                    {
                        delete pProvider;
                    }
                }
            }
        }
        delete m_pProviders;
        m_pProviders = NULL;

        delete[] m_pCachedValues;
        m_pCachedValues = NULL;
    }

    Atom::PoolIndex GetPoolIndex() const { return m_pPool->GetPoolIndex(); }

    HRESULT GetProvider(_In_ Atom atom, _Out_ const IQualifierValueProvider** result) const
    {
        DEF_ASSERT((atom.GetPoolIndex() == m_pPool->GetPoolIndex()) && (atom.GetIndex() < m_cacheSize));
        return m_pProviders->Get(atom.GetIndex(), (IQualifierValueProvider**)result);
    }

    HRESULT SetProvider(_In_ Atom atom, _In_ IQualifierValueProvider* pProvider, _In_ bool bTakeOwnership)
    {
        DEF_ASSERT((atom.GetPoolIndex() == m_pPool->GetPoolIndex()) && (atom.GetIndex() < m_cacheSize));
        DEF_ASSERT(atom.GetIndex() < 32); // don't overflow m_ownedProviders

        UINT32 maskbit = (1 << atom.GetIndex());

        if ((m_ownedProviders & maskbit) != 0)
        {
            IQualifierValueProvider* pOldProvider;
            if (SUCCEEDED(m_pProviders->Get(atom.GetIndex(), &pOldProvider)))
            {
                delete pOldProvider;
            }
            m_ownedProviders &= ~maskbit;
        }

        RETURN_IF_FAILED(m_pProviders->Set(atom.GetIndex(), pProvider));
        if (bTakeOwnership)
        {
            m_ownedProviders |= maskbit;
        }

        return S_OK;
    }

    bool IsCacheReset()
    {
        AutoReaderWriterLock autoLock(&m_srwLock, true);
        return m_attemptedValues == 0;
    }

    void ResetCache()
    {
        AutoReaderWriterLock autoLock(&m_srwLock, false);
        m_attemptedValues = m_presentValues = 0;
    }

    void ResetCache(_In_ Atom atom)
    {
        AutoReaderWriterLock autoLock(&m_srwLock, false);
        DEF_ASSERT((atom.GetPoolIndex() == m_pPool->GetPoolIndex()) && (atom.GetIndex() < m_cacheSize));
        DEF_ASSERT(atom.GetIndex() < 32); // don't overflow m_ownedProviders
        UINT32 maskbit = (1 << atom.GetIndex());

        m_attemptedValues &= ~maskbit;
        m_presentValues &= ~maskbit;
    }

    HRESULT GetQualifierValue(_In_ Atom atom, _In_ const IProviderDataSources* pData, _Inout_ StringResult* pRtrn)
    {
        AutoReaderWriterLock autoLock(&m_srwLock, true);

        UINT32 atomIx =
            atom.GetIndex(); // OACR doesn't like using atom.GetIndex() as an index on m_pCachedValues below (wasn't mollified with "__analysis_assume(atom.GetIndex() < m_cacheSize)")
        if ((atom.GetPoolIndex() != m_pPool->GetPoolIndex()) || (atomIx >= m_cacheSize))
        {
            return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
        }

        if (atomIx >= 32)
        {
            return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
        }

        UINT32 maskbit = (1 << atomIx);

        if (((m_attemptedValues & maskbit) == 0) && ((m_presentValues & maskbit) == 0))
        {
            //  Nothing in the cache.  Try to get the value.
            m_attemptedValues |= maskbit;
            IQualifierValueProvider* pProvider;
            RETURN_IF_FAILED(m_pProviders->Get(atomIx, &pProvider));
            DEF_ASSERT(pProvider != NULL);
            RETURN_IF_FAILED(pProvider->GetQualifierValue(atom, pData, &m_pCachedValues[atomIx]));

            m_presentValues |= maskbit;
        }

        if ((m_presentValues & maskbit) != 0)
        {
            // we have a cached value, return that
            RETURN_IF_FAILED(pRtrn->SetRef(m_pCachedValues[atomIx].GetRef()));
            return S_OK;
        }
        // Couldn't get a value
        return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
    }

    HRESULT SetQualifierValue(_In_ Atom atom, _In_ PCWSTR pValue, _In_ bool bCopy)
    {
        AutoReaderWriterLock autoLock(&m_srwLock, false);

        DEF_ASSERT((atom.GetPoolIndex() == m_pPool->GetPoolIndex()) && (atom.GetIndex() < m_cacheSize));
        DEF_ASSERT(atom.GetIndex() < 32); // don't overflow m_ownedProviders

        if (bCopy)
        {
            RETURN_IF_FAILED(m_pCachedValues[atom.GetIndex()].SetCopy(pValue));
        }
        else
        {
            RETURN_IF_FAILED(m_pCachedValues[atom.GetIndex()].SetRef(pValue));
        }
        m_presentValues |= (1 << atom.GetIndex());
        return S_OK;
    }

protected:
    const IAtomPool* m_pPool;

    mutable DynamicArray<IQualifierValueProvider*>* m_pProviders;
    UINT32 m_ownedProviders;

    int m_cacheSize;
    __ecount(m_cacheSize) mutable StringResult* m_pCachedValues;
    UINT32 m_attemptedValues;
    UINT32 m_presentValues;
    SRWLOCK m_srwLock;

    PerQualifierPoolInfo(_In_ const IAtomPool* pPool) :
        m_pPool(pPool),
        m_pProviders(NULL),
        m_ownedProviders(0),
        m_cacheSize(pPool->GetNumAtoms()),
        m_pCachedValues(NULL),
        m_attemptedValues(0),
        m_presentValues(0)
    {
        ::InitializeSRWLock(&m_srwLock);
    }

    HRESULT Init()
    {
        RETURN_IF_FAILED(DynamicArray<IQualifierValueProvider*>::CreateInstance(m_pPool->GetNumAtoms(), &m_pProviders));
        m_pCachedValues = new StringResult[m_cacheSize];
        RETURN_IF_NULL_ALLOC(m_pCachedValues);

        RETURN_IF_FAILED(m_pProviders->SetExtent(m_pPool->GetNumAtoms()));
        return S_OK;
    }
};

HRESULT ProviderResolver::CreateInstance(
    _In_ CoreProfile* pProfile,
    _In_ const UnifiedEnvironment* pEnvironment,
    _In_ const IDecisionInfo* pDecisions,
    _Outptr_ ProviderResolver** result)
{
    *result = nullptr;

    RETURN_HR_IF(E_INVALIDARG, (pProfile == nullptr) || (pEnvironment == nullptr) || (pDecisions == nullptr));

    AutoDeletePtr<ProviderResolver> pRtrn = new ProviderResolver(pEnvironment, pDecisions);
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init());

    RETURN_IF_FAILED(pRtrn->InitAllQualifierProviders(pProfile));

    *result = pRtrn.Detach();

    return S_OK;
}

ProviderResolver::ProviderResolver(_In_ const UnifiedEnvironment* pEnvironment, _In_ const IDecisionInfo* pDecisions) :
    ResolverBase(pEnvironment, pDecisions), m_pQualifiers(NULL), m_pDataSources(NULL)
{}

ProviderResolver::~ProviderResolver() { delete m_pQualifiers; }

HRESULT ProviderResolver::Init()
{
    RETURN_IF_FAILED(ResolverBase::Init());
    RETURN_IF_FAILED(PerQualifierPoolInfo::CreateInstance(m_pEnvironment->GetDefaultEnvironment()->GetQualifierNames(), &m_pQualifiers));

    return S_OK;
}

HRESULT ProviderResolver::SetProvider(_In_ PCWSTR pQualifier, __in_opt IQualifierValueProvider* pProvider, _In_ bool bTakeOwnership)
{
    Atom name;
    RETURN_IF_FAILED(m_pEnvironment->GetQualifierNameAtom(pQualifier, &name));
    RETURN_IF_FAILED(SetProvider(name, pProvider, bTakeOwnership));

    return S_OK;
}

HRESULT ProviderResolver::SetProvider(_In_ Atom qualifierName, __in_opt IQualifierValueProvider* pProvider, _In_ bool bTakeOwnership)
{
    if (qualifierName.GetPoolIndex() != m_pQualifiers->GetPoolIndex())
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_FILE_TYPE);
    }

    RETURN_IF_FAILED(m_pQualifiers->SetProvider(qualifierName, pProvider, bTakeOwnership));
    if (!m_pQualifiers->IsCacheReset()) // no need to reset if already reset
    {
        Reset();
    }

    return S_OK;
}

HRESULT ProviderResolver::InitAllQualifierProviders(_In_ CoreProfile* pProfile)
{
    for (int iEnv = 0; iEnv < m_pEnvironment->GetNumEnvironments(); iEnv++)
    {
        const IEnvironment* pEnvironment;
        RETURN_IF_FAILED(m_pEnvironment->GetEnvironment(iEnv, &pEnvironment));

        Atom qualifierName;
        for (int iQual = 0; iQual < pEnvironment->GetQualifierNames()->GetNumAtoms(); iQual++)
        {
            if (!pEnvironment->GetQualifierNames()->TryGetAtom(iQual, &qualifierName))
            {
                return E_ABORT;
            }

            IQualifierValueProvider* pProvider = NULL;

            RETURN_IF_FAILED(pProfile->GetProviderForQualifier(pEnvironment, qualifierName, &pProvider));
            RETURN_IF_FAILED(SetProvider(qualifierName, pProvider, true));
        }
    }

    return S_OK;
}

void ProviderResolver::Reset()
{
    ResolverBase::Reset();
    m_pQualifiers->ResetCache();
}

HRESULT ProviderResolver::Reset(__in_ecount(numQualifierNames) Atom* pQualifierNames, _In_ int numQualifierNames)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pQualifierNames);

    RETURN_IF_FAILED(ResolverBase::Reset(pQualifierNames, numQualifierNames));

    bool badPool = false;

    Atom qualifier;
    for (int i = 0; i < numQualifierNames; i++)
    {
        qualifier = pQualifierNames[i];
        if (qualifier.GetPoolIndex() != m_pQualifiers->GetPoolIndex())
        {
            badPool = true;
        }
        else
        {
            m_pQualifiers->ResetCache(qualifier);
        }
    }

    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_FILE_TYPE), badPool);

    return S_OK;
}

HRESULT ProviderResolver::GetQualifierValue(_In_ PCWSTR pQualifierName, _Inout_ StringResult* pValueOut) const
{
    Atom qualifier;
    RETURN_IF_FAILED(m_pEnvironment->GetQualifierNameAtom(pQualifierName, &qualifier));

    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_FILE_TYPE), qualifier.GetPoolIndex() != m_pQualifiers->GetPoolIndex());

    RETURN_IF_FAILED_WITH_EXPECTED(
        m_pQualifiers->GetQualifierValue(qualifier, m_pDataSources, pValueOut), HRESULT_FROM_WIN32(ERROR_NOT_FOUND));

    return S_OK;
}

HRESULT ProviderResolver::GetQualifierValue(_In_ Atom qualifier, _Inout_ StringResult* pValueOut) const
{
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_FILE_TYPE), qualifier.GetPoolIndex() != m_pQualifiers->GetPoolIndex());

    RETURN_IF_FAILED_WITH_EXPECTED(
        m_pQualifiers->GetQualifierValue(qualifier, m_pDataSources, pValueOut), HRESULT_FROM_WIN32(ERROR_NOT_FOUND));

    return S_OK;
}

HRESULT ProviderResolver::SetQualifier(_In_ PCWSTR pQualifierName, _In_ PCWSTR pNewValue)
{
    Atom qualifier;
    RETURN_IF_FAILED(m_pEnvironment->GetQualifierNameAtom(pQualifierName, &qualifier));
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_FILE_TYPE), qualifier.GetPoolIndex() != m_pQualifiers->GetPoolIndex());

    RETURN_IF_FAILED(SetQualifier(qualifier, pNewValue));

    return S_OK;
}

HRESULT ProviderResolver::SetQualifier(_In_ Atom qualifier, _In_ PCWSTR pNewValue)
{
    (void)Reset(&qualifier, 1);

    RETURN_IF_FAILED(m_pQualifiers->SetQualifierValue(qualifier, pNewValue, true));

    return S_OK;
}

HRESULT ProviderResolver::GetQualifierProvider(_In_ PCWSTR qualifierName, _Out_ const IQualifierValueProvider** provider) const
{
    Atom qualifierAtom;
    RETURN_IF_FAILED(m_pEnvironment->GetQualifierNameAtom(qualifierName, &qualifierAtom));

    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_FILE_TYPE), qualifierAtom.GetPoolIndex() != m_pQualifiers->GetPoolIndex());

    const IQualifierValueProvider* providerForAtom;
    RETURN_IF_FAILED(m_pQualifiers->GetProvider(qualifierAtom, &providerForAtom));

    RETURN_HR_IF_NULL(E_DEF_NOT_READY, providerForAtom);

    *provider = providerForAtom;

    return S_OK;
}

class OverrideResolver::PerQualifierPoolInfo : public DefObject
{
public:
    static HRESULT CreateInstance(
        _In_ const IAtomPool* pPool,
        _In_opt_ PerThreadQualifier* pPerThreadQualifier,
        _Outptr_ PerQualifierPoolInfo** result)
    {
        *result = nullptr;
        RETURN_HR_IF_NULL(E_INVALIDARG, pPool);

        AutoDeletePtr<PerQualifierPoolInfo> pRtrn = new PerQualifierPoolInfo(pPool, pPerThreadQualifier);
        RETURN_IF_NULL_ALLOC(pRtrn);
        RETURN_IF_FAILED(pRtrn->Init());

        *result = pRtrn.Detach();
        return S_OK;
    }

    ~PerQualifierPoolInfo()
    {
        delete[] m_pCachedValues;
        m_pCachedValues = NULL;
    }

    Atom::PoolIndex GetPoolIndex() const { return m_pPool->GetPoolIndex(); }

    void ResetCache()
    {
        AutoReaderWriterLock autoLock(&m_srwLock, false);
        m_presentValues = 0;

        if (m_pPerThreadQualifier)
        {
            m_pPerThreadQualifier->ResetCache();
        }
    }

    void ResetCache(_In_ Atom atom)
    {
        AutoReaderWriterLock autoLock(&m_srwLock, false);
        DEF_ASSERT((atom.GetPoolIndex() == m_pPool->GetPoolIndex()) && (atom.GetIndex() < m_cacheSize));
        DEF_ASSERT(atom.GetIndex() < 32); // don't overflow m_ownedProviders

        m_presentValues &= ~(1 << atom.GetIndex());

        if (m_pPerThreadQualifier)
        {
            m_pPerThreadQualifier->ResetCache(atom);
        }
    }

    HRESULT GetQualifierValue(_In_ Atom atom, _Inout_ StringResult* pRtrn)
    {
        AutoReaderWriterLock autoLock(&m_srwLock, true);
        DEF_ASSERT((atom.GetPoolIndex() == m_pPool->GetPoolIndex()) && (atom.GetIndex() < m_cacheSize));
        DEF_ASSERT(atom.GetIndex() < 32); // don't overflow m_ownedProviders

        UINT32 maskbit = (1 << atom.GetIndex());

        if ((m_presentValues & maskbit) != 0)
        {
            // we have a cached value, return that
            RETURN_IF_FAILED(pRtrn->SetRef(m_pCachedValues[atom.GetIndex()].GetRef()));
            return S_OK;
        }

        if (m_pPerThreadQualifier)
        {
            RETURN_IF_FAILED_WITH_EXPECTED(m_pPerThreadQualifier->GetQualifierValue(atom, pRtrn), HRESULT_FROM_WIN32(ERROR_NOT_FOUND));
            return S_OK;
        }

        // Couldn't get a value
        return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
    }

    HRESULT SetQualifierValue(_In_ Atom atom, _In_ PCWSTR pValue, _In_ bool bCopy)
    {
        AutoReaderWriterLock autoLock(&m_srwLock, false);

        DEF_ASSERT((atom.GetPoolIndex() == m_pPool->GetPoolIndex()) && (atom.GetIndex() < m_cacheSize));
        DEF_ASSERT(atom.GetIndex() < 32); // don't overflow m_ownedProviders

        if (bCopy)
        {
            RETURN_IF_FAILED(m_pCachedValues[atom.GetIndex()].SetCopy(pValue));
        }
        else
        {
            RETURN_IF_FAILED(m_pCachedValues[atom.GetIndex()].SetRef(pValue));
        }
        m_presentValues |= (1 << atom.GetIndex());
        return S_OK;
    }

protected:
    const IAtomPool* m_pPool;

    int m_cacheSize;
    __ecount(m_cacheSize) mutable StringResult* m_pCachedValues;
    UINT32 m_presentValues;
    SRWLOCK m_srwLock;
    mutable DynamicArray<IQualifierValueProvider*>* m_pProviders;
    UINT32 m_ownedProviders;
    UINT32 m_attemptedValues;
    PerThreadQualifier* m_pPerThreadQualifier;
    PerQualifierPoolInfo(_In_ const IAtomPool* pPool, _In_opt_ PerThreadQualifier* pPerThreadQualifier) :
        m_pPool(pPool),
        m_cacheSize(pPool->GetNumAtoms()),
        m_pCachedValues(NULL),
        m_presentValues(0),
        m_pPerThreadQualifier(pPerThreadQualifier)
    {
        ::InitializeSRWLock(&m_srwLock);
    }

    HRESULT Init()
    {
        m_pCachedValues = new StringResult[m_cacheSize];
        RETURN_IF_NULL_ALLOC(m_pCachedValues);

        return S_OK;
    }
};

HRESULT OverrideResolver::CreateInstance(_In_ const IResolver* pParent, _Outptr_ OverrideResolver** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, pParent);

    AutoDeletePtr<OverrideResolver> pRtrn = new OverrideResolver(pParent);
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init());

    *result = pRtrn.Detach();

    return S_OK;
}

HRESULT OverrideResolver::CreateInstance(
    _In_ CoreProfile* pProfile,
    _In_ const UnifiedEnvironment* pEnvironment,
    _In_ const IResolver* pParent,
    _In_ bool bCloned,
    _Outptr_ OverrideResolver** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, pParent);

    AutoDeletePtr<OverrideResolver> pRtrn = new OverrideResolver(pParent, bCloned);
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pProfile, pEnvironment));

    *result = pRtrn.Detach();

    return S_OK;
}

OverrideResolver::OverrideResolver(_In_ const IResolver* pParent) :
    ResolverBase(pParent->GetEnvironment(), pParent->GetDecisions()),
    m_pParent(pParent),
    m_bHasScoreCache(true),
    m_bIsDifferentQualifierValueFromParent(true)
{}

OverrideResolver::OverrideResolver(_In_ const IResolver* pParent, _In_ bool bCloned) :
    ResolverBase(pParent->GetEnvironment(), pParent->GetDecisions()),
    m_pParent(pParent),
    m_bClonedResolver(bCloned),
    m_bHasScoreCache(false),
    m_bIsDifferentQualifierValueFromParent(false)
{}

HRESULT OverrideResolver::Init()
{
    RETURN_IF_FAILED(ResolverBase::Init());

    // Windows8 behavior where OverrideResolver is per global resolver that has score cache
    RETURN_IF_FAILED(PerQualifierPoolInfo::CreateInstance(
        m_pParent->GetEnvironment()->GetDefaultEnvironment()->GetQualifierNames(), nullptr, &m_pQualifiers));
    return S_OK;
}

HRESULT OverrideResolver::Init(_In_ CoreProfile* pProfile, _In_ const UnifiedEnvironment* pEnvironment)
{
    RETURN_IF_FAILED(ResolverBase::Init());

    int numThreadAwareQualifiers = pProfile->GetNumThreadAwareQualifiers();

    if (numThreadAwareQualifiers != 0)
    {
        // When OverrideResolver is created from ProviderResolver based, then it become per App OverrideResolver.
        // Other per view OverrideResolver will have OverrideResolver as its parent resolver (win8 behavior and keep consistence here).
        RETURN_IF_FAILED(PerThreadQualifier::CreateInstance(pProfile, pEnvironment, m_pParent, &m_pPerThreadQualifier));
    }
    else
    {
        m_bHasScoreCache = true;
        m_bIsDifferentQualifierValueFromParent = true;
    }

    // If the bFromPrividerResolver is true, OverrideResolver should not have its own provider for thread specific, but it has its own score like windows8.
    RETURN_IF_FAILED(PerQualifierPoolInfo::CreateInstance(
        m_pParent->GetEnvironment()->GetDefaultEnvironment()->GetQualifierNames(), m_pPerThreadQualifier, &m_pQualifiers));

    bool bSameValue = true;
    if (!m_bIsDifferentQualifierValueFromParent)
    {
        for (int i = 0; i < m_pPerThreadQualifier->GetNumPerThreadQualifiers(); i++)
        {
            if (FAILED(m_pPerThreadQualifier->ValueIsSameAsParent(i, &bSameValue)))
            {
                return S_OK;
            }

            if (!bSameValue)
            {
                // If one of per thread qualifiers value is different from parent value, it will have its own score cache
                m_bHasScoreCache = true;
                m_bIsDifferentQualifierValueFromParent = true;
                break;
            }
        }
    }

    return S_OK;
}

OverrideResolver::~OverrideResolver()
{
    delete m_pQualifiers;
    m_pQualifiers = NULL;

    delete m_pPerThreadQualifier;
    m_pPerThreadQualifier = nullptr;
}

HRESULT OverrideResolver::SetQualifier(_In_ PCWSTR pQualifierName, _In_ PCWSTR pNewValue)
{
    Atom qualifier;
    RETURN_IF_FAILED(m_pEnvironment->GetQualifierNameAtom(pQualifierName, &qualifier));

    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_FILE_TYPE), qualifier.GetPoolIndex() != m_pQualifiers->GetPoolIndex());
    RETURN_IF_FAILED(SetQualifier(qualifier, pNewValue));

    return S_OK;
}

HRESULT OverrideResolver::SetQualifier(_In_ Atom qualifier, _In_ PCWSTR pNewValue)
{
    (void)Reset(&qualifier, 1);

    // Once Resolver has its unique value, it will have its own score cache.
    m_bHasScoreCache = true;
    RETURN_IF_FAILED(m_pQualifiers->SetQualifierValue(qualifier, pNewValue, true));

    return S_OK;
}

HRESULT OverrideResolver::OverrideToMatch(_In_ const IQualifierSet* /*pQualifiers*/) { return E_NOTIMPL; }

void OverrideResolver::Reset()
{
    AutoReaderWriterLock autoLock(&m_srwQualifierValuesLock);
    ResolverBase::Reset();
    if (!m_bIsDifferentQualifierValueFromParent)
    {
        m_bHasScoreCache =
            false; // once per thread resolver is reset, it can share the same score cache with process as long as scale value is same
    }

    m_pQualifiers->ResetCache();
}

HRESULT OverrideResolver::Reset(_In_reads_(numQualifierNames) Atom* pQualifierNames, _In_ int numQualifierNames)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pQualifierNames);

    AutoReaderWriterLock autoLock(&m_srwQualifierValuesLock);
    RETURN_IF_FAILED(ResolverBase::Reset(pQualifierNames, numQualifierNames));

    bool badPool = false;

    Atom qualifier;
    for (int i = 0; i < numQualifierNames; i++)
    {
        qualifier = pQualifierNames[i];
        if (qualifier.GetPoolIndex() != m_pQualifiers->GetPoolIndex())
        {
            badPool = true;
        }

        if (!badPool)
        {
            m_pQualifiers->ResetCache(qualifier);
        }
        else
        {
            break;
        }
    }

    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_FILE_TYPE), badPool);

    return S_OK;
}

HRESULT OverrideResolver::GetQualifierValue(_In_ PCWSTR pQualifierName, _Inout_ StringResult* pValueOut) const
{
    Atom qualifier;
    RETURN_IF_FAILED(m_pEnvironment->GetQualifierNameAtom(pQualifierName, &qualifier));

    RETURN_IF_FAILED_WITH_EXPECTED(GetQualifierValue(qualifier, pValueOut), HRESULT_FROM_WIN32(ERROR_NOT_FOUND));

    return S_OK;
}

HRESULT OverrideResolver::GetQualifierValue(_In_ Atom qualifier, _Inout_ StringResult* pValueOut) const
{
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_FILE_TYPE), qualifier.GetPoolIndex() != m_pQualifiers->GetPoolIndex());

    // we have a local value
    if (SUCCEEDED(m_pQualifiers->GetQualifierValue(qualifier, pValueOut)))
    {
        return S_OK;
    }

    RETURN_IF_FAILED_WITH_EXPECTED(m_pParent->GetQualifierValue(qualifier, pValueOut), HRESULT_FROM_WIN32(ERROR_NOT_FOUND));

    return S_OK;
}

bool OverrideResolver::IsQualifierValueOverriden(_In_ PCWSTR pQualifierName) const
{
    Atom qualifier;
    if (FAILED(m_pEnvironment->GetQualifierNameAtom(pQualifierName, &qualifier)))
    {
        return false;
    }

    return IsQualifierValueOverriden(qualifier);
}

bool OverrideResolver::IsQualifierValueOverriden(_In_ Atom qualifier) const
{
    StringResult strValue;
    if (SUCCEEDED(m_pQualifiers->GetQualifierValue(qualifier, &strValue)))
    {
        return true;
    }

    return false;
}

HRESULT OverrideResolver::EvaluateDecision(
    _In_ const IDecision* pDecision,
    _Out_ int* pResultIndexOut,
    _Inout_ QualifierSetResult* pResultSetOut) const
{
    if (m_bHasScoreCache)
    {
        return ResolverBase::EvaluateDecision(pDecision, pResultIndexOut, pResultSetOut);
    }
    // OverrideResolver has ProviderResolver as parent all the time
    return m_pParent->EvaluateDecision(pDecision, pResultIndexOut, pResultSetOut);
}

HRESULT OverrideResolver::EvaluateDecision(
    _In_ const IDecision* pDecision,
    _In_ int numResults,
    _Out_writes_(numResults) int* pResultIndexesOut,
    _Out_writes_(numResults) int* pResultSetIndexesOut) const
{
    if (m_bHasScoreCache)
    {
        return ResolverBase::EvaluateDecision(pDecision, numResults, pResultIndexesOut, pResultSetIndexesOut);
    }
    // OverrideResolver has ProviderResolver as parent all the time
    return m_pParent->EvaluateDecision(pDecision, numResults, pResultIndexesOut, pResultSetIndexesOut);
}

HRESULT OverrideResolver::EvaluateQualifierSet(
    _In_ const IQualifierSet* pQualifierSet,
    _Out_ bool* pbIsMatchOut,
    _Out_ bool* pbIsDefaultOut,
    _Out_ bool* pbIsMatchOrDefaultOut,
    _Out_opt_ UINT16* pScoreOut) const
{
    if (m_bHasScoreCache)
    {
        return ResolverBase::EvaluateQualifierSet(pQualifierSet, pbIsMatchOut, pbIsDefaultOut, pbIsMatchOrDefaultOut, pScoreOut);
    }

    return m_pParent->EvaluateQualifierSet(pQualifierSet, pbIsMatchOut, pbIsDefaultOut, pbIsMatchOrDefaultOut, pScoreOut);
}

HRESULT
OverrideResolver::EvaluateQualifier(_In_ const IQualifier* pQualifier, _Out_ double* pScoreOut, _Out_ double* pFallbackScoreOut) const
{
    if (m_bHasScoreCache)
    {
        return ResolverBase::EvaluateQualifier(pQualifier, pScoreOut, pFallbackScoreOut);
    }

    return m_pParent->EvaluateQualifier(pQualifier, pScoreOut, pFallbackScoreOut);
}

HRESULT OverrideResolver::EvaluateDecisionForQualiferSetResult(
    _In_ const IDecision* pDecision,
    _In_ bool bMultiInstances,
    _Out_ int* pResultIndexOut,
    _Out_ bool* pbIsMatchOut,
    _Out_ bool* pbIsDefaultOut,
    _Out_ bool* pbIsMatchOrDefaultOut,
    _Out_opt_ UINT16* pScoreOut) const
{
    AutoReaderWriterLock autoLock(&m_srwQualifierValuesLock, true); // shared lock

    QualifierSetResult qsResult;
    RETURN_IF_FAILED(EvaluateDecision(pDecision, pResultIndexOut, &qsResult));

    if (!bMultiInstances)
    {
        // ResolveAll (multiInstance) should not check its individual candidate result by calling EvaluateQualifierSet
        RETURN_IF_FAILED(EvaluateQualifierSet(&qsResult, pbIsMatchOut, pbIsDefaultOut, pbIsMatchOrDefaultOut, pScoreOut));
    }
    else
    {
        *pbIsMatchOut = *pbIsDefaultOut = *pbIsMatchOrDefaultOut = false;
        if (pScoreOut != nullptr)
        {
            *pScoreOut = 0;
        }
    }

    return S_OK;
}

HRESULT OverrideResolver::GetQualifierProvider(_In_ PCWSTR qualifierName, _Out_ const IQualifierValueProvider** provider) const
{
    return m_pParent->GetQualifierProvider(qualifierName, provider);
}

} // namespace Microsoft::Resources
