/*****
 * file: semantics.cpp
 * author: Peter Lukac xlukac11
 * */

#include "semantics.h"
#include <iostream>



int Semantics::computeData( const std::vector<double> &value,
                 const std::vector<std::string> &type,
                            const std::string &opcode){
    std::string mainType = type.at(0);
    for( unsigned i = 0; i < type.size(); i++ ){
        if( type.at(i) != mainType ){
            std::cerr << "incopatible types!" << std::endl;
            return -1;
        }
    }

    double returnValue = 0;

    if( opcode == "add" ){
        for( unsigned i = 0; i < value.size(); i++)
            returnValue += value.at(i);
    } else if( opcode == "sub" ){
        returnValue = value.at(0);
        for( unsigned i = 1; i < value.size(); i++)
            returnValue -= value.at(i);
    } else if( opcode == "mul" ){
        returnValue = 1;
        for( unsigned i = 0; i < value.size(); i++)
            returnValue *= value.at(i);
    } else if( opcode == "div" ){
        returnValue = value.at(0);
        for( unsigned i = 1; i < value.size(); i++)
            returnValue /= value.at(i);
    }


    return returnValue;
}
