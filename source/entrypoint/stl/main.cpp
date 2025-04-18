/*!
 *
 * Copyright (c) 2021 Kambiz Asadzadeh
 * Copyright (c) 2023 Genyleap
 */

#include "utilities/featuretest.hpp"
#include <iostream>


//! Examples
#include "examples/compilertest.hpp"
#include "examples/configtest.hpp"
#include "examples/languagetest.hpp"
#include "examples/librarytest.hpp"
#include "examples/platformtest.hpp"


// #include <openssl/asn1.h>

//! JSon [Non-STL] Features
#if defined(USE_JSON) && !defined(USE_BOOST)
#include <json/json.h>
#else
// #include <boost/json.hpp>
#endif
//! Google Test
#ifdef USE_GOOGLE_TEST
#include <gtest/gtest.h>

class Counter
{
public:
    // Returns the current counter value, and increments it.
    int Increment()
    {
        return m_counter++;
    }

    // Returns the current counter value, and decrements it.
    // counter can not be less than 0, return 0 in this case
    int Decrement()
    {
        if (m_counter == 0) {
            return m_counter;
        } else {
            return m_counter--;
        }
    }

    // Prints the current counter value to STDOUT.
    void Print() const
    {
        printf("%d", m_counter);
    }

private:
    int m_counter;
};

// TEST UNIT
TEST(Counter, Increment)
{
    Counter c;

    // Test that counter 0 returns 0
    EXPECT_EQ(0, c.Decrement());

    // EXPECT_EQ() evaluates its arguments exactly once, so they
    // can have side effects.

    EXPECT_EQ(0, c.Increment());
    EXPECT_EQ(1, c.Increment());
    EXPECT_EQ(2, c.Increment());

    EXPECT_EQ(3, c.Decrement());
}

#endif

//! Catch2
#ifdef USE_CATCH2
#include <catch2/catch_all.hpp>

#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file

unsigned int Factorial(unsigned int number)
{
    return number <= 1 ? number : Factorial(number - 1) * number;
}

TEST_CASE("Factorials are computed", "[factorial]")
{
    REQUIRE(Factorial(1) == 1);
    REQUIRE(Factorial(2) == 2);
    REQUIRE(Factorial(3) == 6);
    REQUIRE(Factorial(10) == 3628800);
}

#endif

// ThirdParty libs
#include "examples/thirdpartytest.hpp"

#ifdef USE_OPENMESH
#include <OpenMesh/Core/IO/MeshIO.hh>
#endif


#include <config.hpp> //Project Config

#include <iostream>
#include <memory>

using namespace std;

int main()
{
    std::unique_ptr<int[]> arr = std::make_unique<int[]>(5); // Allocate an array of integers on the heap

    // Access elements of the array
    for (int i = 0; i < 5; ++i) {
        arr[i] = i;
    }

    // Memory is automatically freed when arr goes out of scope
    // No need for explicit delete[]

    // Try to access the freed memory
    std::cout << "Array elements after deletion: ";
    for (int i = 0; i < 5; ++i) {
        // The following line is safe, as memory is managed by unique_ptr
        std::cout << arr[i] << " ";
    }

    return 0;
}
