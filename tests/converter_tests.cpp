/*
File: converter_tests.cpp

Brief: unit tests for the Converter_App

Author: Alexander DuPree

Date: 1/9/2019
*/

#include <catch.hpp>
#include "converter_app.h"

TEST_CASE("Converting temperatures")
{
    const char* default_opt[2] = { "ftoc", "72" };
    const char* option_1[4] = { "ftoc", "22.222", "-i Celsius", "-o Fahrenheit" };
    const char* option_2[4] = { "ftoc", "7","-i Fahrenheit", "-o Fahrenheit" };
    const char* option_3[4] = { "ftoc", "72","-i Fahrenheit", "-o Kelvin" };

    SECTION("Default, no options")
    {
        Converter_App app(2, default_opt);
        Approx target = Approx(22.222).margin(.0001);

        REQUIRE(app.conversion() == target);
    }
    SECTION("Input=Celsius, Output=Fahrenheit")
    {
        Converter_App app(4, option_1);
        Approx target = Approx(72.00).margin(.0001);

        REQUIRE(app.conversion() == target);
    }
    SECTION("Output is the same as input")
    {
        Converter_App app(4, option_2);

        REQUIRE(app.conversion() == 7);
    }
    SECTION("Input=Fahrenheit, Output=Kelvin")
    {
        Converter_App app(4, option_3);
        Approx target = Approx(295.372).margin(.0001);

        REQUIRE(app.conversion() == target);
    }
}

