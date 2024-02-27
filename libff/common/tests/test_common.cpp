/**
 *****************************************************************************
 Some tests for the functions in this directory.
 *****************************************************************************
 * @author     This file is part of libff, developed by SCIPR Lab
 *             and contributors (see AUTHORS).
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/

#include <cstdint>
#include <gtest/gtest.h>

#include "libff/common/utils.hpp"
#include "libff/algebra/fields/binary/gf32.hpp"
#include "libff/algebra/fields/binary/gf64.hpp"

using namespace libff;

TEST(Log2Test, SimpleTest) {
    // There seems to be a second log2 function that operates on floats so we added libff::.
    EXPECT_EQ(libff::log2(0), 0ULL);
    EXPECT_EQ(libff::log2(1), 0ULL);
    EXPECT_EQ(libff::log2(2), 1ULL);
    EXPECT_EQ(libff::log2(3), 2ULL);
    EXPECT_EQ(libff::log2(4), 2ULL);
    EXPECT_EQ(libff::log2(5), 3ULL);
    EXPECT_EQ(libff::log2(6), 3ULL);
    EXPECT_EQ(libff::log2(7), 3ULL);
    EXPECT_EQ(libff::log2(8), 3ULL);
    EXPECT_EQ(libff::log2(9), 4ULL);
}

TEST(Log2Test, PowersOfTwo) {
    for (std::size_t i = 10; i < 20; ++i)
    {
        const std::size_t k = (1ULL<<i);
        EXPECT_EQ(libff::log2(k-1), i);
        EXPECT_EQ(libff::log2(k), i);
        EXPECT_EQ(libff::log2(k+1), i+1);
    }
}

template<typename FieldT>
void test_random_element()
{
    FieldT x = random_element_non_zero_one<FieldT>();
    EXPECT_NE(x, FieldT::zero());
    EXPECT_NE(x, FieldT::one());

    x = random_element_non_zero<FieldT>();
    EXPECT_NE(x, FieldT::zero());

    FieldT y = random_element_exclude(x);
    EXPECT_NE(x, y);
}

TEST(UtilsTest, RandomElementTest)
{
    test_random_element<gf32>();
    test_random_element<gf64>();
}

