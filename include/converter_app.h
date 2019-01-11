/*
File: converter_app.h

Brief: Converter_App is a simple temperature conversion application. 
       This application was designed to test out functional programming 
       concepts as well as to learn the wonderful command line parser Clara. 

       Clara - https://github.com/catchorg/Clara

Author: Alexander DuPree

Date: 1/9/2019
*/

#ifndef CONVERTER_APP_H
#define CONVERTER_APP_H

#define FTOC_VERSION "ftoc v1.0.1"

#include <iostream>
#include <exception>
#include <clara.hpp>
#include <functional>
#include <unordered_map>

class Converter_App 
{
  public:
     
    typedef std::unordered_map<std::string, std::function<float(float)>> Converter;

    Converter_App(int argc, char** argv);

    // Overloaded constructor is used for unit tests and isn't needed in production
    Converter_App(int argc, const char** argv);

    int run() const;

    float conversion() const;

    void usage() const;

    void version() const;

    void display_temp_conversion() const;

  private:

    static float degrees;
    static bool show_help;
    static bool version_request;
    static std::string input_units;
    static std::string output_units;

    static const clara::Parser parser;
    static const Converter input_converter;
    static const Converter output_converter;

};

class unknown_units
{
  public:

    unknown_units(std::string input, std::string output)
        : input_units(input), output_units(output) {}

    std::string what() const throw()
    {
        return "One or more unknown units.\nInput: " 
                + input_units + " Output:" + output_units;
    }

  private:

    std::string input_units;
    std::string output_units;

};

#endif // CONVERTER_APP_H

