/*******************************************************************************
** File: inputValidation.hpp, header file for the inputValidation helper
** 		functions
** Author: Jordan K Bartos
** Date: April 10, 2018
** Description: contains function headers for inputValidation functions
*******************************************************************************/

#ifndef HELPERFUNCTIONS_HPP
#define HELPERFUNCTIONS_HPP

#include <string>
#include <fstream>

bool isAnInt(const std::string&);
bool convertStringToInt(const std::string&,int&,int,int);
void pause();
void clearTheScreen();
int getIntFromUser(int,int);
void printFileContents(std::ifstream&);
std::string getStringFromUser(int minLength, int maxLength);


#endif
