/*******************************************************************************
** fileName: helperFunctions.cpp
** Author: Jordan K Bartos
** Date: April 10, 2018
** Description: These are the input validation functions necessary for this
** project
*******************************************************************************/
#include "helperFunctions.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <climits>
#include <algorithm>


/*******************************************************************************
*						bool isAnInt(string&)
* Description: this function takes a reference to a string as input and checks
* if it could be a valid integer. If the string can successfully be converted
* to an int, it retruns true. If the string cannot be successfully converted to
* an int, it returns false.
*******************************************************************************/
bool isAnInt(const std::string &INPUT_STRING)
{

	//If the string contains a hyphen ('-'), it must contain only one hyphen
	//and it must be at the very beginning of the string. If it contains
	//multiple hyphens or it contains one not at the beginning of the string,
	//return false
	
	if(((INPUT_STRING.find_first_of("-") == INPUT_STRING.find_last_of("-")) &&
		(INPUT_STRING.find_last_of("-") == 0) ) ||
		(INPUT_STRING.find_first_of("-") == std::string::npos))
	{
		//The following code was modified from an answer to a question found
		//on stackoverflow
		//reference: https://stackoverflow.com/questions/18728754/checking-
		//input-value-is-an-integer
		return (INPUT_STRING.find_first_not_of("0123456789-") ==
			std::string::npos) && !INPUT_STRING.empty();

	}
	//else, it either contains multiple hyphens or a hyphen at a position
	//other than [0]
	else
	{
		return false;
	}
}


/*******************************************************************************
**				bool convertStringtoInt(string&,int&,int,int)
** Description: Takes a reference to a string, a reference to an int (this
** will take the value of the converted int), an int for the minimum allowable
** value, and an int for the maximum allowable value. It returns true on a 
** successful conversion and false on an unsuccessful conversion. It uses the
** isAnInt() function also found in this file.
*******************************************************************************/
bool convertStringToInt(const std::string &INPUT_STRING,int &convertedInt,
	 int min, int max)
{
	int tempInt;

	if(isAnInt(INPUT_STRING))	//make sure string can be made an int
	{
		tempInt = std::atoi(INPUT_STRING.c_str());	//convert string to an
											//int
											
		//if the string contained an integer larger than INT_MAX, it will
		//overflow. So, comparing the original string to the tempInt will
		//indicate if the input was too large/too small to be an int
		if((std::to_string(tempInt)).compare(INPUT_STRING) == 0)
		{
			//is int in specified range?
			if(tempInt >= min && tempInt <= max)
			{
				convertedInt = tempInt;
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	
}


/*******************************************************************************
 *						void pause()
 * Description: pauses the progress of the program until the user pushes enter.
*******************************************************************************/
void pause()
{
	std::cout << "\n\nPress [Enter] to continue.\n" << std::endl;
	std::string dummyString;
	std::getline(std::cin, dummyString);
}


/*******************************************************************************
 *					void clearTheScreen()
 * Description: clears the screen.
*******************************************************************************/
void clearTheScreen()
{
	//this was found at http://stackoverflow.com/questions/17335816/clear-scren
	//-using-c
	std::cout << "\033[2J\033[1;1H";
}


/*******************************************************************************
 *					int getIntFromUser(int min, int max)
 * description: takes two ints as argumetns, min and max. Prompts the user for
 * an int between min and max, validates the input, reprompts if necessary.
 * Returns the validated int.
*******************************************************************************/
int getIntFromUser(int min, int max)
{
	std::string userInput = "";
	bool gotGoodInt = false;
	int returnInt;
	
	do
	{
		std::getline(std::cin,userInput);
		
		if(convertStringToInt(userInput,returnInt,min,max))
		{
			gotGoodInt = true;
		}
		else
		{
			std::cout << "Invalid input. Re-enter value ->" << std::flush;
		}

	} while (!gotGoodInt);

	return returnInt;
}


/*******************************************************************************
 * 					void printFileContents(ifstream&)
 * Description: takes a reference to an ifstream object, prints the contents of
 * the .txt file the ifstream object is associated with if it can. otherwise
 * it does nothing. It also resets the file
*******************************************************************************/
void printFileContents(std::ifstream &inputFile)
{
	std::string outputString;
	if(inputFile)	
	{
		while(std::getline(inputFile,outputString))
		{
			std::cout << outputString << std::endl;
		}
	}
	inputFile.seekg(0);
	inputFile.clear();
}


/*******************************************************************************
 * 					string getStringFromUser(int minLength, int maxLength)
*******************************************************************************/
std::string getStringFromUser(int minLength, int maxLength){
    std::string inputString;
    bool goodInput = false;

    //get user input and make sure it is correct length
    do{
        getline(std::cin, inputString);
        if(inputString.length() >= maxLength){
            std::cout << "Input is too too long. Re-enter ->" << std::flush;
        }
        else if(inputString.length() <= minLength){

            std::cout << "Input is too too short. Re-enter->" << std::flush;
        }
        else{
            goodInput = true;
        }

    }while(!goodInput);
    
    return inputString;
}

