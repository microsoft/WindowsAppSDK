// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

//------------------------------------------------------------------
// File: Atom.cpp
//
// The methods declared in Atom struct are defined here.
//------------------------------------------------------------------

#include "StdAfx.h"

namespace Microsoft::Resources
{

const PCWSTR Atom::NullString = L"";
const Atom Atom::NullAtom(0, 0);

#define DefAtom_Compare(A1, A2) \
    (((A1).s.poolIndex == (A2).s.poolIndex) ? (((A1).s.index == (A2).s.index) ? DEF_ATOMS_EQUAL : DEF_ATOMS_UNEQUAL) : \
                                              DEF_ATOMS_INDETERMINATE)

DEF_ATOM_HASH
DefAtom_HashString(__in PCWSTR pString, DEF_ATOM_HASH_METHOD hashMethod)
{
    DEF_ATOM_HASH rtrn = 0x3482;

    //! \todo really basic hash function.  Do something better someday.
    //! \todo Repeated hashMethod tests should be factored out if they
    //!       aren't optimized away (which they almost certainly are).
    for (; *pString; pString++)
    {
        rtrn = (rtrn << 1) ^ ((hashMethod & DEF_HASH_CASE_INSENSITIVE) ? towlower(*pString) : *pString);
    }

    return rtrn;
}

/// <summary>
///        Compares 2 atoms.
/// </summary>
/// <param name="atom">
///        The atom to be compared with.
/// </param>
/// <returns>
///        None.
/// </returns>
Atom::Comparison Atom::Compare(__in Atom atom) const { return DefAtom_Compare(m_defAtom, atom.GetAtom()); }

/// <summary>
///        returns the hash value for a string using the specified hash method.
/// </summary>
/// <param name="pString">
///        String whose hash needs to be retreived.
/// </param>
/// <param name="hashType">
///        Specifies a method used to hash a string.
/// </param>
/// <returns>
///        None.
/// </returns>
Atom::Hash Atom::HashString(__in PCWSTR pString, __in Atom::HashMethod hashType) { return DefAtom_HashString(pString, hashType); }

} // namespace Microsoft::Resources
