// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

namespace Microsoft::Resources
{

struct DefChecksum
{
protected:
    DEF_CHECKSUM m_cs;

public:
    typedef DEF_CHECKSUM Checksum;

    DefChecksum() : m_cs(0) {}

    Checksum GetChecksum() const { return m_cs; }

    /*! 
     * Adds a supplied data blob to a DEF checksum.
     *
     * Adding a data blob to a DEF checksum updates the partial
     * checksum twice:
     * - first, with a four-byte buffer containing the little-endian unsigned representation
     *   of the length of the buffer, in bytes.
     * - next, with the contents of the buffer
     * 
     * A non-NULL buffer of length 0 adds just the buffer length to the checksum as described above.
     * A NULL buffer adds buffer length 0 followed by a four zero-bytes.
     * 
     * \param partialChecksum
     * A partially calculated checksum.
     * 
     * \param data
     * The buffer to be added to the checksum
     *
     * \param dataSizeInBytes
     * The size of data, in bytes.
     *
     * \param status
     * If present, reports extended status when an error occurs:
     * - If status is non-NULL, reports INVALID_ARG if data is NULL and dataSizeInBytes is greater than 0.
     *
     * \return Checksum
     * Returns the updated checksum
     */
    static Checksum ComputeChecksum(
        _In_ Checksum partialChecksum,
        _In_reads_bytes_opt_(dataSizeInBytes) const BYTE* data,
        _In_ UINT32 dataSizeInBytes);

    /*! 
     * Adds an unsigned 32-bit value to a DEF checksum, as a 4-byte buffer containing the little-endian
     * representation of the value.
     * 
     * \param partialChecksum
     * A partially calculated checksum.
     *
     * \param value
     * The value to be added
     * 
     * \return Checksum
     * Returns the updated checksum
     */
    static Checksum ComputeUInt32Checksum(_In_ Checksum partialChecksum, _In_ UINT32 value);

    /*! 
     * Adds a supplied string to a DEF checksum.
     *
     * Adding a string to a DEF checksum effectively adds the string as
     * byte data _including the terminating NULL_, as described by
     * ComputeChecksum.   A NULL string is added as a NULL data buffer.
     *
     * If caseInsensitive is true, the string is added as if it were lower-case.
     *
     * \param partialChecksum
     * A partially calculated checksum.
     * 
     * \param caseInsensitive
     * Indicates whether the checksum is case-insensitive.  If true, the string is
     * added to the checksum as if it were lower-case.
     *
     * \param stringToAdd
     * The string to be added.
     * 
     * \param checksum
     * Returns the updated checksum.
     * 
     * \return HRESULT
     * - Can report OUT_OF_MEMORY if an allocation fails.
     */
    static HRESULT ComputeStringChecksum(
        _In_ Checksum partialChecksum,
        _In_ bool caseInsensitive,
        _In_opt_ PCWSTR stringToAdd,
        _Out_ Checksum* checksum);

    /*! 
     * Adds a supplied atom pool to a DEF checksum.  Adding an atom pool:
     * - Adds the description of the atom pool as a case-insensitive, NULL-terminated
     *   string using ComputeStringChecksum
     * - Adds UInt32 indicating case-sensitivity of the atom pool (1 if the pool is case-insensitive, 0 otherwise)
     * - Adds the number of atoms in the pool as a UInt32
     * - Adds the strings that represent each of the atoms using ComputeStringChecksum
     *
     * A NULL atom pool is added as if it were NULL data blob using ComputeChecksum.
     *
     * \param partialChecksum
     * A partially calculated checksum.
     *
     * \param pool
     * The atom pool to be added to the checksum
     *
     * \param checksum
     * Returns the updated checksum.
     *
     * \return HRESULT
     */
    static HRESULT ComputeAtomPoolChecksum(_In_ Checksum partialChecksum, _In_opt_ const IAtomPool* pool, _Out_ Checksum* checksum);

    /*! 
     * Adds a previous version atom pool to a DEF checksum.  A previous version
     * is added exactly as a complete pool except that only the first 'numAtoms'
     * atoms are added to the checksum.
     *
     * \param partialChecksum
     * A partially calculated checksum.
     *
     * \param pool
     * The atom pool to be added to the checksum
     *
     * \param checksum
     * Returns the updated checksum.
     *
     * \return HRESULT
     * - INVALID_ARG if pool is NULL and numAtoms is non-zero
     * - SIZE_MISMATCH if numAtoms is greater than the number of
     *   atoms in pool.
     */
    static HRESULT ComputeAtomPoolChecksum(
        _In_ Checksum partialChecksum,
        _In_opt_ const IAtomPool* pool,
        _In_ UINT32 numAtoms,
        _Out_ Checksum* checksum);

    /*! 
     * Adds an atom to a DEF checksum.  An atom is added as:
     * 1) The fully-qualified name of the pool that contains it, as a 
     *    case-insensitive string
     * 2) The index of the atom, as a UInt32
     * 
     * The NULL atom is always added as a 32-bit zero.
     *
     * \param partialChecksum
     * A partially calculated checksum
     *
     * \param atom
     * The atom to be added
     *
     * \param atoms
     * The AtomPoolGroup used to determine the fully-qualified name of the 
     * pool that contains the atom.
     *
     * \param checksum
     * Returns the updated checksum.
     *
     * \return HRESULT
     */
    static HRESULT ComputeAtomChecksum(
        _In_ Checksum partialChecksum,
        _In_ Atom atom,
        _In_ const AtomPoolGroup* atoms,
        _Out_ Checksum* checksum);

    enum ChecksumFlags
    {
        Checksum_Default = 0x0000,
        Checksum_CaseInsensitive = 0x0000,
        Checksum_CaseSensitive = 0x0001,
        Checksum_CaseSensitivityMask = 0x0001,
        Checksum_Sorted = 0x0000,
        Checksum_Unsorted = 0x0002,
        Checksum_SortMask = 0x0002
    };

    static HRESULT ComputeStringArrayChecksum(
        _In_ Checksum partialChecksum,
        _In_ ChecksumFlags flags,
        _In_ size_t numStrings,
        _In_reads_(numStrings) const PCWSTR* strings,
        _Out_ Checksum* checksum);

    Checksum ComputeChecksum(_In_reads_bytes_(dataSizeInBytes) const BYTE* data, _In_ UINT32 dataSizeInBytes)
    {
        return m_cs = ComputeChecksum(m_cs, data, dataSizeInBytes);
    }

    Checksum ComputeUInt32Checksum(_In_ UINT32 value) { return m_cs = ComputeUInt32Checksum(m_cs, value); }

    HRESULT ComputeStringChecksum(_In_ bool caseInsensitive, _In_opt_ PCWSTR str, _Out_ Checksum* checksum)
    {
        RETURN_IF_FAILED(ComputeStringChecksum(m_cs, caseInsensitive, str, checksum));
        m_cs = *checksum;
        return S_OK;
    }

    HRESULT ComputeAtomPoolChecksum(_In_ const IAtomPool* pool, _Out_ Checksum* checksum)
    {
        RETURN_IF_FAILED(ComputeAtomPoolChecksum(m_cs, pool, checksum));
        m_cs = *checksum;
        return S_OK;
    }

    HRESULT ComputeAtomPoolChecksum(_In_ const IAtomPool* pool, _In_ int numAtoms, _Out_ Checksum* checksum)
    {
        RETURN_IF_FAILED(ComputeAtomPoolChecksum(m_cs, pool, numAtoms, checksum));
        m_cs = *checksum;
        return S_OK;
    }

    HRESULT ComputeAtomChecksum(_In_ Atom atom, _In_ const AtomPoolGroup* atoms, _Out_ Checksum* checksum)
    {
        RETURN_IF_FAILED(ComputeAtomChecksum(m_cs, atom, atoms, checksum));
        m_cs = *checksum;
        return S_OK;
    }

    HRESULT ComputeStringArrayChecksum(
        _In_ ChecksumFlags flags,
        _In_ size_t numStrings,
        _In_reads_(numStrings) const PCWSTR* strings,
        _Out_ Checksum* checksum)
    {
        return ComputeStringArrayChecksum(m_cs, flags, numStrings, strings, checksum);
    }

    static HRESULT ComputeFileChecksum(_In_ Checksum partialChecksum, _In_ PCWSTR fileToAdd, _Out_ Checksum* checksum);
};

DEFINE_ENUM_FLAG_OPERATORS(DefChecksum::ChecksumFlags);

} // namespace Microsoft::Resources