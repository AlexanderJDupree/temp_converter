/*
File: converter_app.cpp

Brief: 

Author: Alexander DuPree

Date: 1/9/2019
*/

#include "converter_app.h"

using namespace clara;

/****** Static Definitions ******/

// Conversion Formulas
const auto ftof = [](float degrees){ return degrees; };
const auto ftoc = [](float degrees){ return (degrees - 32) * (5.0/9); };
const auto ctof = [](float degrees){ return (degrees * (9/5.0) + 32); };

float Converter_App::degrees         = 0;
bool  Converter_App::show_help       = false;
bool  Converter_App::version_request = false;

// Default Units
std::string Converter_App::input_units  = "fahrenheit";
std::string Converter_App::output_units = "celsius";

const Converter_App::Converter Converter_App::input_converter {

        { "f", ftof },
        { "fahrenheit", ftof },
        { "Fahrenheit", ftof },

        { "c", ctof },
        { "celsius", ctof },
        { "Celsius", ctof }
};

const Converter_App::Converter Converter_App::output_converter {

        { "f", ftof },
        { "fahrenheit", ftof },
        { "Fahrenheit", ftof },

        { "c", ftoc },
        { "celsius", ftoc },
        { "Celsius", ftoc }
};

const Parser Converter_App::parser = 
         Opt(version_request)
            ["-V"]["--version"]("Show version and quit") |
         Opt(input_units, "input units")
            ["-i"]["--input"]("Sets the input units") |
         Opt(output_units, "output units")
            ["-o"]["--output"]("Sets the output units") |
         Arg(degrees, "temperature")("The temperature value to be converted") |
         Help(show_help);

/********************************/

Converter_App::Converter_App(int argc, char** argv)
{
    auto result = parser.parse(Args(argc, argv));

    // Options failed to parse
    if(!result)
    {
        throw result;
    }
}

Converter_App::Converter_App(int argc, const char** argv)
    : Converter_App(argc, const_cast<char**>(argv)) {}

int Converter_App::run() const
{
    if(show_help)
    {
        usage();
    }
    else if(version_request)
    {
        version();
    }
    else
    {
        display_temp_conversion();
    }
    return 0;
}

void Converter_App::usage() const
{
    parser.writeToStream(std::cout);
    std::cout << "\nAvailable units:";

    Converter::const_iterator it = input_converter.begin();
    for ( ;it != input_converter.end(); ++it)
    {
        if(std::isupper((*it).first[0]))
        {
            std::cout << "\n  " << (*it).first;
        }
    }
    std::cout << '\n' << std::endl;
    return;
}

void Converter_App::version() const
{
    std::cout << FTOC_VERSION << std::endl;
    return;
}

float Converter_App::conversion() const
{
    // Grabs the correct conversion formulas from the conversion tables
    Converter::const_iterator input = input_converter.find(input_units);
    Converter::const_iterator output = output_converter.find(output_units);

    if(input == input_converter.end() || output == output_converter.end())
    {
        throw unknown_units(input_units, output_units);
    }
    else
    {
        auto  internal = (*input).second;
        auto  external = (*output).second;

        // internal functor converts the input units to fahrenheit, then the 
        // external functor converts fahrenheit to the output units.
        return external(internal(degrees));
    }
}

void Converter_App::display_temp_conversion() const
{
    std::cout << degrees << " " << input_units << " is " << conversion() 
              << " " << output_units << std::endl;
    return;
}

