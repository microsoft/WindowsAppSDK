// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "mrm/common/file/FileBase.h"

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

    /*! \defgroup MrmFile_Base MrmFile_Base: 
     * Create or manipulate base MRM files
     */
    /*@{*/

    /*
      * NOTE:   Unless otherwise noted, these structures are all intended to be mapped
      * directly into memory.  Always use types with fixed sizes (e.g. INT32 instead of
      * INT) and be careful to maintain natural alignment across all architectures (i.e.
      * insert padding if necessary).
      */

    //! Magic numbers used to identify MRM files
    __declspec(selectany) extern const DEFFILE_MAGIC gWin8PriFileMagic = {'m', 'r', 'm', '_', 'p', 'r', 'i', '0'};

    __declspec(selectany) extern const DEFFILE_MAGIC gWinBluePriFileMagic = {'m', 'r', 'm', '_', 'p', 'r', 'i', '1'};

    __declspec(selectany) extern const DEFFILE_MAGIC gWindowsPhoneBluePriFileMagic = {'m', 'r', 'm', '_', 'p', 'r', 'i', 'f'};

    __declspec(selectany) extern const DEFFILE_MAGIC gUniversalPriFileMagic = {'m', 'r', 'm', '_', 'p', 'r', 'i', '2'};

    __declspec(selectany) extern const DEFFILE_MAGIC gUniversalRS4PriFileMagic = {'m', 'r', 'm', '_', 'p', 'r', 'i', '3'};

    __declspec(selectany) extern const DEFFILE_MAGIC gUniversalVNextPriFileMagic = {'m', 'r', 'm', '_', 'v', 'n', 'x', 't'};

    __declspec(selectany) extern const DEFFILE_MAGIC gTestPriFileMagic = {'m', 'r', 'm', '_', 't', 'e', 's', 't'};

    __declspec(selectany) extern const DEFFILE_SECTION_TYPEID gEnvironmentMappingSectionType = {
        '[',
        'm',
        'r',
        'm',
        '_',
        'e',
        'n',
        'v',
        '_',
        'm',
        'a',
        'p',
        ']',
        ' ',
        ' ',
    };

    //! Section type for the decision info section.
    __declspec(selectany) extern const DEFFILE_SECTION_TYPEID gDecisionInfoSectionType = {
        '[',
        'm',
        'r',
        'm',
        '_',
        'd',
        'e',
        'c',
        'n',
        '_',
        'i',
        'n',
        'f',
        'o',
        ']',
    };

    __declspec(selectany) extern const DEFFILE_SECTION_TYPEID gPriDescriptorSectionType = {
        '[',
        'm',
        'r',
        'm',
        '_',
        'p',
        'r',
        'i',
        '_',
        'd',
        'e',
        's',
        'c',
        ' ',
        ']',
    };

    __declspec(selectany) extern const DEFFILE_SECTION_TYPEID gPriDescriptorExSectionType = {
        '[',
        'm',
        'r',
        'm',
        '_',
        'p',
        'r',
        'i',
        'd',
        'e',
        's',
        'c',
        'e',
        'x',
        ']',
    };

    __declspec(selectany) extern const DEFFILE_SECTION_TYPEID gReverseFileMapSectionType = {
        '[',
        'm',
        'r',
        'm',
        '_',
        'r',
        'e',
        'v',
        '_',
        'm',
        'a',
        'p',
        ']',
        ' ',
        ' ',
    };

// need to use macro because C compiler complains if we use a const in an array spec
#define MRM_UNIQUE_NAME_LENGTH 256

    /*!
	 * Version info for an MRM Environment header
     * NOTE: There is a copy of this struct in mrm\common\MrmProfile.data.h -- ENVIRONMENT_VERSION_INFO
     * Please make sure they are in sync!
	 */
    typedef struct _MRMFILE_ENVIRONMENT_VERSION_INFO
    {
        UINT16 major;
        UINT16 minor;
        DEF_CHECKSUM checksum;
        DEF_ATOM_COUNT_SMALL numQualifierTypes;
        DEF_ATOM_COUNT_SMALL numQualifiers;
        DEF_ATOM_COUNT_SMALL numItemTypes;
        DEF_ATOM_COUNT_SMALL numResourceValueTypes;
        DEF_ATOM_COUNT_SMALL numResourceValueLocators;
        DEF_ATOM_COUNT_SMALL numConditionOperators;
    } MRMFILE_ENVIRONMENT_VERSION_INFO, *PMRMFILE_ENVIRONMENT_VERSION_INFO;

    // reference to a specific version of an MRM Environment
    typedef struct _MRMFILE_ENVIRONMENT_REF
    {
        WCHAR uniqueName[MRM_UNIQUE_NAME_LENGTH];
        MRMFILE_ENVIRONMENT_VERSION_INFO version;
        DEF_ATOM_POOL_INDEX qualifierTypesPoolIndex;
        DEF_ATOM_POOL_INDEX qualifiersPoolIndex;
        DEF_ATOM_POOL_INDEX itemTypesPoolIndex;
        DEF_ATOM_POOL_INDEX resourceValueTypesPoolIndex;
        DEF_ATOM_POOL_INDEX resourceValueLocatorsPoolIndex;
        DEF_ATOM_POOL_INDEX conditionOperatorsPoolIndex;
    } MRMFILE_ENVIRONMENT_REF;

    /*!
     * Describes a single attribute
     */
    typedef UINT16 MRM_ATTR_WEIGHT;
    __declspec(selectany) extern const MRM_ATTR_WEIGHT MRM_MIN_ATTRIBUTE_WEIGHT = 0;
    __declspec(selectany) extern const MRM_ATTR_WEIGHT MRM_MAX_ATTRIBUTE_WEIGHT = 1000;

    typedef struct _MRMFILE_ATTR_DESC
    {
        DEF_ATOM_SMALL type;
        MRM_ATTR_WEIGHT weight;
    } MRMFILE_ATTR_DESC, *PMRMFILE_ATTR_DESC;

    /*!
     * Header for an MRM Environment Mapping section. File layout is:
     *      ENVIRONMENT_MAPPING_HEADER hdr
     *      UINT16                          nameOffsets[hdr.numNewQualifiers]
     *      WCHAR                           namesPool[hdr.namesPoolSizeInChars]
     *      BYTE                            pad[] as necessary
     */
    typedef struct _MRMFILE_ENVIRONMENT_MAPPING_HEADER
    {
        DEF_CHECKSUM baseEnvironmentChecksum;
        DEF_CHECKSUM currentEnvironmentChecksum;
        UINT16 currentMinorVersion;
        UINT16 numNewQualifiers;
        UINT16 namesPoolSizeInChars;
        UINT16 pad;
    } MRMFILE_ENVIRONMENT_MAPPING_HEADER;

    /*!
     * Header for an MRM Environment Mapping section. File layout is:
     *      ENVIRONMENT_CORE_MAPPING_HEADER hdr
     *      UINT16                          coreMapping[hdr.version.numQualifiers]
     *      UINT16                          nameOffsets[hdr.version.numQualifiers]
     *      WCHAR                           namesPool[hdr.cchNamesPool]
     *      BYTE                            pad[] (as necessary)
     */
    typedef struct _MRMFILE_ENVIRONMENT_CORE_MAPPING_HEADER
    {
        MRMFILE_ENVIRONMENT_VERSION_INFO version;
        UINT16 cchUniqueName;
        UINT16 cchNamesPool;
    } MRMFILE_ENVIRONMENT_CORE_MAPPING_HEADER;

    typedef UINT16 MRM_QUALIFIER_PRIORITY;
    __declspec(selectany) extern const MRM_QUALIFIER_PRIORITY MRM_MIN_QUALIFIER_PRIORITY = 0;
    __declspec(selectany) extern const MRM_QUALIFIER_PRIORITY MRM_MAX_QUALIFIER_PRIORITY = 1000;

    /*!
     * Description of a single hierarchical schema version.
     */
    typedef struct _MRMFILE_HSCHEMA_VERSION_INFO
    {
        UINT16 major;
        UINT16 minor;
        UINT32 csType;
        DEF_CHECKSUM checksum;
        UINT32 numScopes;
        UINT32 numItems;
    } MRMFILE_HSCHEMA_VERSION_INFO, *PMRMFILE_HSCHEMA_VERSION_INFO;

    /*!
     * Global reference to a hierarchical schema at a specific version.  Layout in memory is:
     *      HSCHEMA_REF                 hdr
     *      WCHAR                       uniqueId[hdr.cchUniqueId]
     * A block of multiple schema references consists of an array of MRMFILE_HSCHEMA_REF 
     * followed by an array of WCHAR containing all names.
     */
    typedef struct _MRMFILE_HSCHEMA_REF
    {
        MRMFILE_HSCHEMA_VERSION_INFO version;
        UINT16 cchUniqueId;
        UINT16 flags;
        DEF_ATOM_POOL_INDEX scopesPoolIndex;
        DEF_ATOM_POOL_INDEX itemsPoolIndex;
    } MRMFILE_HSCHEMA_REF, *PMRMFILE_HSCHEMA_REF;

    __declspec(selectany) extern const DEFFILE_SECTION_TYPEID gHierarchicalSchemaSectionReferenceType = {
        '[',
        'm',
        'r',
        'm',
        '_',
        'h',
        's',
        'c',
        'h',
        'e',
        'm',
        'a',
        'r',
        'f',
        ']',
    };

    // supported values for csType in a schema version info
    __declspec(selectany) extern const UINT32 MRMFILE_HSCHEMA_CSTYPE_DEFAULT = 0;

    /*!
     * Header for an MRM Hierarchical Schema section.
     * Layout in memory is:
     *      HSCHEMA_HEADER              hdr
     *      HSCHEMA_VERSION             versions[hdr.numVersions]
     *      WCHAR*                      uniqueId[hdr.cchUniqueId]
     *      WCHAR*                      simpleId[hdr.cchSimpleId]
     *      BYTE*                       pad[] (as necessary)
     *      DEFFILES_HNAMES             Hierarchichal names header & data
     */
    typedef struct _MRMFILE_HSCHEMA_HEADER
    {
        UINT16 numVersions;
        UINT16 cchUniqueId;
        UINT16 cchSimpleId;
        UINT16 pad;
    } MRMFILE_HSCHEMA_HEADER, *PMRMFILE_HSCHEMA_HEADER;

    __declspec(selectany) extern const DEFFILE_SECTION_TYPEID gHierarchicalSchemaSectionType = {
        '[',
        'm',
        'r',
        'm',
        '_',
        'h',
        's',
        'c',
        'h',
        'e',
        'm',
        'a',
        ']',
        ' ',
        ' ',
    };

    /*!
     * Header for an MRM Extended Hierarchical Schema section.
     * Layout in memory is:
     *      HSCHEMA_HEADER_EX           hdr
     *      HSCHEMA_VERSION             versions[hdr.numVersions]
     *      WCHAR*                      uniqueId[hdr.cchUniqueId]
     *      WCHAR*                      simpleId[hdr.cchSimpleId]
     *      BYTE*                       pad[] (as necessary)
     *      DEFFILES_HNAMES             Hierarchichal names header & data
     */
    typedef struct _MRMFILE_HSCHEMA_HEADER_EX
    {
        UINT16 numVersions;
        UINT16 cchUniqueId;
        UINT16 cchSimpleId;
        UINT16 pad;
        DEFFILE_SECTION_TYPEID hnamesTypeId;
    } MRMFILE_HSCHEMA_HEADER_EX, *PMRMFILE_HSCHEMA_HEADER_EX;

    __declspec(selectany) extern const DEFFILE_SECTION_TYPEID gHierarchicalSchemaExSectionType = {
        '[',
        'm',
        'r',
        'm',
        '_',
        'h',
        's',
        'c',
        'h',
        'e',
        'm',
        'a',
        'e',
        'x',
        ']',
        ' ',
    };

    /*!
     * Header for an MRM resource map section.  File layout is:
     *      RESOURCE_MAP_HEADER         hdr
     *      BYTE                        environments[hdr.cbEnvironmentRefs]
     *      BYTE                        schemaRefData[hdr.cbSchemaRef]
     *      DEF_ATOM                    instanceTypes[hdr.numInstanceTypes]
     *      MAP_DIR_ENTRY               dir[hdr.numDirEntries]
     *      MAP_RANGE                   ranges[hdr.numRanges]
     *      MAP_ITEM                    items[hdr.numItems]
     *      BYTE                        largeData[hdr.cbLargeItemData]
     *      MAP_VALUE                   resourceCandidates[hdr.numResourceValues]
     *      BYTE                        data[PAD(hdr.cbInstanceData)]
     *
     * If present, largeData has the layout:
     *      RESOURCE_MAP_HEADER         lhdr;
     *      MAP_DIR_ENTRY_LARGE         largeDir[lhdr.numLargeDirEntries]
     *      MAP_RANGE_LARGE             largeRanges[lhdr.numLargeRanges]
     *      MAP_ITEM_LARGE              largeItems[lhdr.numLargeItems]
     */

    typedef struct _MRMFILE_MAP_DIR_ENTRY
    {
        UINT16 itemIndex;
        UINT16 rangeOrItemOffset;
    } MRMFILE_MAP_DIR_ENTRY, *PMRMFILE_MAP_DIR_ENTRY;

    typedef struct _MRMFILE_MAP_RANGE
    {
        UINT16 numItems;
        UINT16 firstItemOffset;
    } MRMFILE_MAP_RANGE, *PMRMFILE_MAP_RANGE;

    typedef struct _MRMFILE_MAP_ITEM
    {
        UINT16 decisionIndex;
        UINT16 firstCandidateValueOffset;
    } MRMFILE_MAP_ITEM, *PMRMFILE_MAP_ITEM;

    typedef struct _MRMFILE_MAP_VALUE
    {
        UINT8 valueLocatorType; //!< locator type for this candidate
        UINT8 resourceValueTypeOffset; //!< Index in the resource vaulue types array of the type for this candidate
        UINT16 detail; //!< Resource value data, interpretation depends on locator type
        union
        {
            UINT32 ui32;
            UINT16 ui16[2];
            BYTE b[4];
        } data; //!< Resource value data, interpretation depends on locator type
    } MRMFILE_MAP_VALUE, *PMRMFILE_MAP_VALUE;

    typedef struct _MRMFILE_MAP_VALUE_LARGE
    {
        UINT8 valueLocatorType; //!< locator type for this candidate
        UINT8 resourceValueTypeOffset; //!< Index in the resource vaulue types array of the type for this candidate
        UINT16 detail; //!< Resource value data, interpretation depends on locator type
        UINT16 data1; //!< Resource value data, interpretation depends on locator type
        UINT16 data2;
        UINT16 data3;
    } MRMFILE_MAP_VALUE_LARGE, *PMRMFILE_MAP_VALUE_LARGE;

    const UINT16 MRMFILE_RESOURCE_MAP_BUILD_LARGE_VALUE = 0x1;

    typedef struct _MRMFILE_RESOURCE_MAP_HEADER
    {
        UINT16 cbEnvironmentRefs; //!< Total size of environments referenced by this map
        UINT16 numEnvironmentRefs; //!< Number of environments referenced by this map
        DEFFILE_SECTION_INDEX schemaSectionIndex; //!< Section index of schema used to build this map
        UINT16 cbSchemaRef; //!< Size of reference to external schema used to build this map
        DEFFILE_SECTION_INDEX decisionInfoSectionIndex; //!< Section index of the decision info for this map
        UINT16 numResourceValueTypes; //!< Number of resource value types used for candidates in this map
        UINT16 numDirEntries; //!< Number of DIR_ENTRYs in this map
        UINT16 numRanges; //!< Number of MAP_RANGEs in this map
        UINT16 numItems; //!< Number of MAP_ITEMs in this map
        UINT16 flags; //!< flags
        UINT32 numValues; //!< Total number of values across all resources in this map
        UINT32 cbInternalValueData; //!< Total size of internal resource value data, in bytes
        UINT32 cbLargeItemData; //!< Total size of additional large item data in bytes
    } MRMFILE_RESOURCE_MAP_HEADER, *PRMRFILE_RESOURCE_MAP_HEADER;

    const int MRMFILE_MAP_MAX_STANDARD_VALUE = 0xffff;

    typedef UINT8 MRMFILE_MAP_VALUE_LOCATOR;

    const MRMFILE_MAP_VALUE_LOCATOR MRMFILE_MAP_VALUE_LOCATOR_INTERNAL = 0x00;
    const MRMFILE_MAP_VALUE_LOCATOR MRMFILE_MAP_VALUE_LOCATOR_DATA_ITEM = 0x01;
    const MRMFILE_MAP_VALUE_LOCATOR MRMFILE_MAP_VALUE_LOCATOR_FILE_ITEM = 0x02;

    typedef struct _MRMFILE_MAP_DIR_ENTRY_LARGE
    {
        UINT32 itemIndex;
        UINT32 rangeOrItemOffset;
    } MRMFILE_MAP_DIR_ENTRY_LARGE, *PMRMFILE_MAP_DIR_ENTRY_LARGE;

    typedef struct _MRMFILE_MAP_RANGE_LARGE
    {
        UINT32 numItems;
        UINT32 firstItemOffset;
    } MRMFILE_MAP_RANGE_LARGE, *PMRMFILE_MAP_RANGE_LARGE;

    typedef struct _MRMFILE_MAP_ITEM_LARGE
    {
        UINT16 decisionIndex;
        UINT16 pad;
        UINT32 firstCandidateValueOffset;
    } MRMFILE_MAP_ITEM_LARGE, *PMRMFILE_MAP_ITEM_LARGE;

    typedef struct _MRMFILE_RESOURCE_MAP_HEADER_LARGE
    {
        UINT32 numDirEntries;
        UINT32 numRanges;
        UINT32 numItems;
    } MRMFILE_RESOURCE_MAP_HEADER_LARGE;

    __declspec(selectany) extern const DEFFILE_SECTION_TYPEID gResourceMapSectionType = {
        '[',
        'm',
        'r',
        'm',
        '_',
        'r',
        'e',
        's',
        '_',
        'm',
        'a',
        'p',
        '_',
        '_',
        ']',
    };

    __declspec(selectany) extern const DEFFILE_SECTION_TYPEID gResourceMap2SectionType = {
        '[',
        'm',
        'r',
        'm',
        '_',
        'r',
        'e',
        's',
        '_',
        'm',
        'a',
        'p',
        '2',
        '_',
        ']',
    };

    __declspec(selectany) extern const DEFFILE_SECTION_TYPEID gResourceMap3SectionType = {
        '[',
        'm',
        'r',
        'm',
        '_',
        'r',
        'e',
        's',
        '_',
        'm',
        'a',
        'p',
        '3',
        '_',
        ']',
    };

    typedef struct _MRMFILE_INDEX_INSTANCE
    {
        UINT16 conditionSetIndex; //!< Condition set that applies for the instance
        UINT8 instanceTypeOffset; //!< Index in the instance types array of the type for this instance
        UINT8 instanceLocatorTypeOffset; //!< Index in the instance locator types array of the locator type for this instance
        UINT16 detail; //!< Instance data, interpretation depends on locator type
        UINT16 data1; //!< Instance data, interpretation depends on locator type
        UINT16 data2;
        UINT16 data3;
    } MRMFILE_INDEX_INSTANCE, *PMRMFILE_INDEX_INSTANCE;

    __declspec(selectany) extern const int MRMFILE_MIN_QUALIFIER_SCORE = 0;
    __declspec(selectany) extern const int MRMFILE_MAX_QUALIFIER_SCORE = 1000;

    __declspec(selectany) extern const int MRMFILE_MIN_QUALIFIER_PRIORITY = 0;
    __declspec(selectany) extern const int MRMFILE_MAX_QUALIFIER_PRIORITY = 1000;

    __declspec(selectany) extern const int MRMFILE_ALWAYS_TRUE_QUALIFIER_INDEX = 0;
    __declspec(selectany) extern const int MRMFILE_UNCONDITIONAL_QUALIFIER_SET_INDEX = 0;
    __declspec(selectany) extern const int MRMFILE_EMPTY_DECISION_INDEX = 0;
    __declspec(selectany) extern const int MRMFILE_NEUTRAL_ONLY_DECISION_INDEX = 1;

    /*
     * Header for an MRM resource link section.  File layout is:
     *      RESOURCE_LINK_HEADER        hdr
     *      LINK_SCHEMA_MAP             schemaMap[hdr.numSchemas]
     *      BYTE                        schemaData[hdr.schemaDataSizeInBytes]
     *      BYTE                        pad[asNeeded]
     *      UINT16                      internalLinks[hdr.firstLargeInternalLink]
     *      UINT16                      pad[asNeeded]
     *      UINT32                      largeInternalLinks[hdr.numInternalLinks - hdr.firstLargeInternalLink]
     *      FULL_LINK                   fullLinks[hdr.firstLargeFullLink]
     *      LARGE_FULL_LINK             largeFullLinks[hdr.numFullLinks - hdr.firstLargeFullLink]
     *      LINK_BY_ID                  linksById[hdr.numLinksById]
     *      LARGE_LINK_BY_ID            largeLinksById[hdr.numFullLinks - hdr.firstLargeLinkById]
     */

    typedef struct _MRMFILE_LINK_SCHEMA_MAP
    {
        UINT16 offsetOrSectionIndex; //!< Offset into data section or index of schema section in the current file
        UINT16 dataSizeInBytes; //!< Size of schema reference data or 0 if offsetOrSectionIndex is a section index.
    } MRMFILE_LINK_SCHEMA_MAP, *PMRMFILE_LINK_SCHEMA_MAP;

    typedef struct _MRMFILE_FULL_LINK
    {
        UINT16 schemaIndex; //!< Index of schema map for schema which contains the linked resource
        UINT16 resourceIndex; //!< Linked resource index
    } MRMFILE_FULL_LINK, *PMRMFILE_FULL_LINK;

    typedef struct _MRMFILE_LARGE_FULL_LINK
    {
        UINT16 schemaIndex; //!< Index of schema map for schema which contains the linked resource
        UINT16 pad; //!< Reserved, must be 0
        UINT32 resourceIndex; //!< Linked resource index
    } MRMFILE_LARGE_FULL_LINK, *PMRMFILE_LARGE_FULL_LINK;

    typedef struct _MRMFILE_LINK_BY_ID
    {
        UINT16 myResourceIndex;
        UINT16 linkIndexInTable;
    } MRMFILE_LINK_BY_ID, *PMRMFILE_LINK_BY_ID;

    typedef struct _MRMFILE_LARGE_LINK_BY_ID
    {
        UINT32 myResourceIndex;
        UINT16 pad;
        UINT16 linkIndexInTable;
    } MRMFILE_LARGE_LINK_BY_ID, PMRMFILE_LARGE_LINK_BY_ID;

    typedef struct _MRMFILE_RESOURCE_LINK_HEADER
    {
        UINT16 numSchemas; //!< Number of schemas referenced by this map.  Referenced schema 0 is the schema of the map.
        UINT16 schemaDataSizeInBytes; //!< Size in bytes of the data that describes referenced schemas
        UINT16 numInternalLinks; //!< Total number of internal links
        UINT16 firstLargeInternalLink; //!< Index of the first internal link that is large
        UINT16 numFullLinks; //!< Total number of full links
        UINT16 firstLargeFullLink; //!< Index of the first full link that is large
        UINT16 numLinksById; //!< Total number of links by id
        UINT16 firstLargeLinkById; //!< Index of the first link by ide that is large
    } MRMFILE_RESOURCE_LINK_HEADER, *PRMRFILE_RESOURCE_LINK_HEADER;

    __declspec(selectany) extern const UINT32 MRMFILE_LINK_NONE = 0;
    __declspec(selectany) extern const UINT32 MRMFILE_LINK_INTERNAL = 1;
    __declspec(selectany) extern const UINT32 MRMFILE_LINK_FULL = 2;

    __declspec(selectany) extern const DEFFILE_SECTION_TYPEID
        gResourceLinkSectionType = {'[', 'm', 'r', 'm', '_', 'r', 'e', 's', '_', 'l', 'i', 'n', 'k', ']', ' '};

    /*!
     * Header for a decision info section of an MRM file.
     * File layout is:
     *      DECISION_INFO_HEADER        hdr
     *      DECISION                    decisions[hdr.numDecisions]
     *      QUALIFIER_SET               sets[hdr.numQualifierSets]
     *      QUALIFIER                   qualifiers[hdr.numQualifiers]
     *      BASE_QUALIFIER              baseQualifiers[hdr.numBaseQualifiers]
     *      UINT16                      refs[hdr.numReferences]
     *      BYTE                        PAD(data[hdr.cbData])
     */
    typedef struct _MRMFILE_BASE_QUALIFIER
    {
        DEF_ATOM_SMALL attribute;
        DEF_ATOM_SMALL op;
        UINT32 valueOffset;
    } MRMFILE_BASE_QUALIFIER, *PMRMFILE_BASE_QUALIFIER;

    typedef struct _MRMFILE_QUALIFIER
    {
        UINT16 baseQualifierIndex;
        UINT16 priority;
        UINT16 fallbackScore;
        UINT16 pad;
    } MRMFILE_QUALIFIER, *PMRMFILE_QUALIFIER;

    typedef struct _MRMFILE_QUALIFIER_SET
    {
        UINT16 firstQualifierRef;
        UINT16 numQualifierRefs;
    } MRMFILE_QUALIFIER_SET, *PMRMFILE_QUALIFIER_SET;

    typedef struct _MRMFILE_DECISION
    {
        UINT16 firstQualifierSetRef;
        UINT16 numQualifierSetRefs;
    } MRMFILE_DECISION, *PMRMFILE_DECISION;

    typedef struct _MRMFILE_DECISION_INFO_HEADER
    {
        UINT16 numBaseQualifiers;
        UINT16 numQualifiers;
        UINT16 numQualifierSets;
        UINT16 numDecisions;
        UINT16 numReferences;
        UINT16 cchLiterals;
    } MRMFILE_DECISION_INFO_HEADER, *PMRMFILE_DECISION_INFO_HEADER;

    /*!
     * Structured description of the contents of an MRM Package Resource Index (PRI) file.
     * File layout is:
     *      PRI_DESCRIPTOR              hdr
     *      DEFFILE_SECTION_INDEX       environments[hdr.numEnvironments]
     *      DEFFILE_SECTION_INDEX       schemas[hdr.numSchemas]
     *      DEFFILE_SECTION_INDEX       conditionInfos[hdr.numConditionInfos]
     *      DEFFILE_SECTION_INDEX       indexes[hdr.numIndexes]     
     *      UINT16                      defaultResourceIndex  
     *      WCHAR                       literals[hdr.cchLiterals];
     *      BYTE                        pad[*]
     */
    typedef struct _MRMFILE_PRI_DESCRIPTOR
    {
        UINT32 flags; //!< MRMFILE_PRI_FLAGS_AUTO_MERGE indicates auto merge.
        UINT16 numEnvironments; //!< Number of Environments defined in this file
        UINT16 numSchemas; //!< Number of Schemas defined in this file
        UINT16 numConditionInfos; //!< Number of Condition Info sections defined in this file
        UINT16 numIndexes; //!< Number of Indexes defined in this file
        UINT16 defaultResourceIndex; //!< Index of the default resource index in indexes[hdr.numIndexes]
        UINT16 pad;
    } MRMFILE_PRI_DESCRIPTOR, *PMRMFILE_PRI_DESCRIPTOR;

    /*!
     * Structured description of extended contents of an MRM package resource index (PRI) file.
     * File layout is:
     *      PRI_DESCRIPTOR_EX           hdr;
     *      DEFFILE_SECTION_INDEX       environments[hdr.numEnvironments]
     *      DEFFILE_SECTION_INDEX       schemas[hdr.numSchemas]
     *      DEFFILE_SECTION_INDEX       decisionInfos[hdr.numDecisionInfos]
     *      DEFFILE_SECTION_INDEX       resourceMaps[hdr.numMaps]
     *      DEFFILE_SECTION_INDEX       referencedFileSections[hdr.numReferencedFileSections]
     *      DEFFILE_SECTION_INDEX       dataItemsSections[hdr.numDataItemSections]
     *      BYTE                        pad[*]
     */
    typedef struct _MRMFILE_PRI_DESCRIPTOR_EX
    {
        UINT16 flags; //!< MRMFILE_PRI_FLAGS_AUTO_MERGE indicates automerge
        DEFFILE_SECTION_INDEX includedFilesSectionIndex; //!< Index of a file info section describing the files used to build this PRI
        UINT16 numEnvironments; //!< Number of environments defined in this file
        UINT16 numSchemas; //!< Number of hierarchical schemas defined in this file
        UINT16 numDecisionInfos; //!< Number of decision infos defined in this file
        UINT16 numResourceMaps; //!< Number of resource maps defined in this file
        DEFFILE_SECTION_INDEX primaryResourceMap; //!< Section indexof the default resource map for this file
        UINT16 numReferencedFileSections; //!< Number of sections listing files referenced by this PRI
        UINT16 numDataItemSections; //!< Number of data item sections with resource values referenced by this PRI
        UINT16 pad; //!< Reserved, must be 0
    } MRMFILE_PRI_DESCRIPTOR_EX, *PMRMFILE_PRI_DESCRIPTOR_EX;

    /*!
     * Header for a Reverse File Map Section.
     * File layout is:
     *      Header                          hdr
     *      MRMFILE_REVERSEFILEMAP_ENTRY    entries[hdr.numFiles]
     *      DEFFILES_HNAMES                 Hierarchichal names header & data
     *      UINT16                          pad
     */
    typedef struct _MRMFILE_REVERSEFILEMAP_HEADER
    {
        UINT32 numFiles; //!< Number of files in the file info section
        UINT32 cbTotal; //!< Total size of the data in bytes.
    } MRMFILE_REVERSEFILEMAP_HEADER;

    /*!
     * Structured description of Reverse File Map Entry.
     */
    typedef struct _MRMFILE_REVERSEFILEMAP_ENTRY
    {
        UINT16 namedResourceIndex; //!< Named Resource Index
        UINT16 qualifierSetIndex; //!< Qualifier set index
    } MRMFILE_REVERSEFILEMAP_ENTRY;

    __declspec(selectany) extern const UINT32 MRMFILE_PRI_FLAGS_DEFAULT = 0x0;
    __declspec(selectany) extern const UINT32 MRMFILE_PRI_FLAGS_AUTO_MERGE = 0x1; // Inbox apps that allow auto merge
    __declspec(selectany) extern const UINT32 MRMFILE_PRI_FLAGS_DEPLOYMENT_MERGABLE =
        0x2; // Resource Pack merge-able file, post-Blue format, but not include inbox apps.
    __declspec(selectany) extern const UINT32 MRMFILE_PRI_FLAGS_DEPLOYMENT_MERGEABLE =
        0x2; // Resource Pack merge-able file, post-Blue format, but not include inbox apps.
    __declspec(selectany) extern const UINT32 MRMFILE_PRI_FLAGS_IS_DEPLOYMENT_MERGE_RESULT =
        0x4; // Merged file by Resource Pack Merge API during DEH
    __declspec(selectany) extern const UINT32 MRMFILE_PRI_FLAGS_IS_AUTOMERGE_MERGE_RESULT =
        0x8; // Merged file by Resource Pack Merge API during DEH

    /*@}*/

#ifdef __cplusplus
}
#endif
