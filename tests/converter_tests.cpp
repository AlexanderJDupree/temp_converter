/*
File: converter_tests.cpp

Brief: unit tests for teh Converter_App

Author: Alexander DuPree

Date: 1/9/2019
*/

#include <catch.hpp>
#include "converter_app.h"

TEST_CASE("Converting temperatures")
{
    const char* default_argv[2] = { "ftoc", "72" };

    SECTION("Default, no options")
    {
        Converter_App app(2, default_argv);
        Approx target = Approx(22.222).margin(.0001);

        REQUIRE(app.conversion() == target);
    }
}

