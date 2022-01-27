#pragma once
#include <memory>
#include <iostream>
#include <string>

/*
    This class was made to address criteria in the memory management section of the rubric.
    
    Requirement: The project uses destructors appropriately.
    Criteria: At least one class that uses unmanaged dynamically allocated memory,
        along with any class that otherwise needs to modify state upon the termination
        of an object, uses a destructor.

    However another requirement+criteria calls for not using raw pointers. By encapsulating the raw pointer with the rule of 5, it is safe to use the raw pointer.
*/

class UserInput
{
public:
	// constructor
    UserInput()
    {
        std::string tempFloorsToPrint;
        bool validEntryFloorsToPrint = false;

        while (!validEntryFloorsToPrint)
        {
            std::cout << "Input 'first' if you would like to display only the first floor.\nInput 'all' if you would like to display all floors: ";
            std::cin >> tempFloorsToPrint;

            if (tempFloorsToPrint == "first" || tempFloorsToPrint == "all")
            {
                *floorsToPrint = tempFloorsToPrint;
                validEntryFloorsToPrint = true;
            }
            else
            {
                std::cout << "\nError. Must floorsToPrint either 'first' or 'all'\n";
            }
        }
    }

	// destructor
	~UserInput()
    {
        if (!floorsToPrint)
        {
            delete floorsToPrint;
        }
    }

	//copy constructor
	UserInput(const UserInput& other)
    {
        floorsToPrint = other.floorsToPrint;
    }
	
	//copy assignment operator
	UserInput& operator=(const UserInput& other)
    {
        floorsToPrint = other.floorsToPrint;
        return *this;
    }
    
	//move constructor
	UserInput(UserInput&& other)
    {
        floorsToPrint = other.floorsToPrint;
        other.floorsToPrint = nullptr;
    }
	
	//move assignment operator
	UserInput& operator=(UserInput&& other) {
        if (this != &other)
        {
            if (floorsToPrint)
            {
                delete floorsToPrint;
            }
            floorsToPrint = other.floorsToPrint;
            other.floorsToPrint = nullptr;
        }
        return *this;
    }

    std::string GetFloorsToPrint() { return *floorsToPrint; }


private:
    std::string* floorsToPrint = new std::string;
};

