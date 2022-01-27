#pragma once
#include <thread>
#include <vector>
#include <future>
#include <mutex>
#include <algorithm>
#include <iostream>
#include <string>
#include <thread>
#include <condition_variable>

#include "Node.h"
#include "Floor.h"
#include "MoveableObject.h"
#include "Person.h"
#include "Threat.h"
#include "InputParser.h"
#include "UserInput.h"

class Simulate
{
public:
	Simulate(ModelInputs& inputs, UserInput&& userInput);

private:
	ModelInputs& _modelInputs;
	UserInput _userInput;
};

