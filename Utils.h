//
// Created by Noam on 6/9/2017.
//

#ifndef CS236360_HW2_UTILS_H
#define CS236360_HW2_UTILS_H
#include "Contracts.hpp"

bool areEqualTypes(varData a,varData b);
bool isBoolean(varData a);
bool isNumeric(varData a);
bool isString(varData a);
bool isInt(varData a);
bool isByte(varData a);
bool validateFunc(std::vector<varType,string> argV,std::vector<varType> expV);

#endif //CS236360_HW2_UTILS_H
