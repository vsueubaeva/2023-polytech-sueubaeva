#include "logic.h"
#include <sstream>
#include <cmath>
#include "tinyexpr.h"
#include <string>
#include <vector>
#include <iostream>

namespace calc
{

    std::string Logic::process_math()
    {
        if (expression.empty())
        {
            return "";
        }
        std::string input_ss(expression);
        std::string output_ss;

        if (input_ss == "g"){
            input_ss.replace(input_ss.find("g"), 1, "9.8");
        }

        double a = te_interp(input_ss.c_str(), 0);

        output_ss = std::to_string(a);
        output_ss.erase(output_ss.find_last_not_of('0') + 1, std::string::npos);

        if (output_ss.back() == '.')
            output_ss.replace(output_ss.find('.'), output_ss.find('.') + 1, "");

        return output_ss;
        
    }
}