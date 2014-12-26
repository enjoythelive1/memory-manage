#include <iostream>

#include "../../src/memory-manage/DynamicArray.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;
using namespace MemoryManage_Arrays;


SCENARIO("A Dynamic array can store items"){
    GIVEN("A DynamicArray counstructed with default constructor"){
        DynamicArray<int> darr;

            WHEN("An item is assigned to an index") {
                darr[0] = 9;
                darr[1] = 10;
                darr[2] = 11;
                darr[3] = 14;
                darr[4] = 70;

                THEN("The value from this same index is equal to the item assigned"){
                    REQUIRE(darr[0] == 9);
                    REQUIRE(darr[1] == 10);
                    REQUIRE(darr[2] == 11);
                    REQUIRE(darr[3] == 14);
                    REQUIRE(darr[4] == 70);
                }
            }
    }
}
