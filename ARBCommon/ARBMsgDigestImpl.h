/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief File hashing algorithms
 *
 * Revision History
 * 2013-10-29 Added more hash algorithms
 */

#include <istream>


namespace dconSoft
{
namespace ARBCommon
{

extern wxString ARBMsgDigestComputeMD5(std::istream& inFile, size_t* outSize);

extern wxString ARBMsgDigestComputeSHA1(std::istream& inFile, size_t* outSize);

extern wxString ARBMsgDigestComputeSHA256(std::istream& inFile, size_t* outSize);

} // namespace ARBCommon
} // namespace dconSoft
