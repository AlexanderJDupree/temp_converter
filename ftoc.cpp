/* File: ftoc.cpp
 *
 * Brief: Command-Line applcation that converts temperatures to specified units
 *
 * Author: Alexander DuPree
 *
 * Date: 1/9/2019
*/

#include "converter_app.h"

int main(int argc, char ** argv) 
{
    int return_code = 0;
    try
    {
        Converter_App app(argc, argv);

        return_code = app.run();
    }
    catch(const clara::detail::InternalParseResult& err)
    {
        std::cerr << "Parser Error: " << err.errorMessage() << std::endl;
        return_code = 1;
    }
    catch(const unknown_units& err)
    {
        std::cerr << err.what() << std::endl;
        return_code = 1;
    }
    return return_code;
}

