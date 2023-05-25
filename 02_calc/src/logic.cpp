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

        std::string per = "";

        if (input_ss.find("g") != std::string::npos){
            input_ss.replace(input_ss.find("g"), 1, "9.8");//м/с^2
        }
        if (input_ss.find("Eo") != std::string::npos){
            input_ss.replace(input_ss.find("Eo"), 2, "8.85");// ф/м
            per = "*10^-12";
        }
        if (input_ss.find("c") != std::string::npos){
            input_ss.replace(input_ss.find("c"), 1, "299792458");//м/с
        }
        if (input_ss.find("el") != std::string::npos){
            input_ss.replace(input_ss.find("el"), 2, "1,6");// кл
            per = "*10^-19";
        }
        if (input_ss.find("h") != std::string::npos){
            input_ss.replace(input_ss.find("h"), 1, "6,63");// дж*с
            per = "*10^-34";
        }
        if (input_ss.find("k") != std::string::npos){
            input_ss.replace(input_ss.find("k"), 1, "1,38");// дж/к
            per = "*10^-23";
        }
        if (input_ss.find("R") != std::string::npos){
            input_ss.replace(input_ss.find("R"), 1, "8,31");// дж/(моль*к)
        }
        if (input_ss.find("Na") != std::string::npos){
            input_ss.replace(input_ss.find("Na"), 2, "6,02");// моль^-1
            per = "*10^23";
        }
        
        double a = te_interp(input_ss.c_str(), 0);

        output_ss = std::to_string(a) + per;
        output_ss.erase(output_ss.find_last_not_of('0') + 1, std::string::npos);

         if (output_ss.back() == '.')
         output_ss.replace(output_ss.find('.'), output_ss.find('.') + 1, "");

        return output_ss;
        
    }
}