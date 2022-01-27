// capstone.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <algorithm>
#include <stdlib.h>


#include "InputParser.h"
#include "Simulate.h"

#include "UserInput.h"


int main()
{
  
    InputParser input = InputParser(); // Use InputParser input("YourConfigFilePath.cfg") to specify a cfg other than the default cfg
	ModelInputs modelInputs = input.getModelInputs();

	UserInput userInput = UserInput();

	Simulate sim = Simulate(modelInputs, std::move(userInput));
    
	std::cout << std::endl << "End of program." << std::endl;
}
