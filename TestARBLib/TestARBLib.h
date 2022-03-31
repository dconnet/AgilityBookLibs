#pragma once

/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Library for testing framework
 * @author David Connet
 *
 * Revision History
 * 2022-03-29 Separated from TestARB
 */

#pragma warning(disable : 4868) // compiler may not enforce left-to-right evaluation order in braced initializer list

#include "ARBCommon/ARBTypes.h"
#if defined(USING_CATCH3)
#include "catch2/catch_all.hpp"
#elif defined(USING_CATCH2)
#include "catch2/catch.hpp"
#else
#error Unknown test framework
#endif
