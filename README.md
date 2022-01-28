Creator: M. Mooney
Program: Udacity's C++ Nanodegree
Project: Capstone
Date of Submission: 1/25/21


Instructions for building/running the project:
*** In VSCode in Udacity's workspace open the capstone_cmake folder
*** Before starting to build, ensure that the InputParser.cpp's SetPath() method has the proper path for your set up for DefaultInputParameters.cfg. If it does not, you will get a segmentation fault and the console will say near the top "Could not open cfg file to read"
*** In the terminal enter: mkdir build
*** In the terminal enter: cd build
*** In the terminal enter: cmake ..
*** In the terminal enter: make
*** In the terminal enter: ./Capstone


Additional libraries needed to run the project:  
(these are indicated with cross-platform installation instructions)
*** No additional libraries are needed.



Project Description:
***This project takes input from the console and a cfg file to generate a building composed of floors. Each floor is made of a grid of nodes. Nodes hold information such as how close it is located to the exit or it is occupied by a person and/or threat. The user specifies where to place exits, alarms, stairwells, people, and threats in the building. Currently, all threats are representative of a fire. People move randomly until someone gets within one node of a fire. The person that spots the fire then goes to an alarm and activates it. Once activated, all people evacuate the building. The simulation ends once everyone evacuates. 

***Any time a threat or person moves, it is written to the console. Every 5 moves by people either the first floor or the entire building is printed to the console. Each person and threat is run on its own thread.

File and class structure:
***The main() is found in capstone.cpp. Capstone.cpp reads in the cfg and console input (with InputParser.cpp, ModelInputs struct within InputParser.h, and UserInput.h) then calls Simulate.cpp. InputParser.cpp reads either DefaultInputParameters.cfg or the user can specify a different cfg as long as it follows the same structure. Within the cfg, the user can specify number of floors, number and location of people, threats, exits, stairwells, and alarms. All buildings are rectangular in shape with the borders being set to a BuildingState::Wall. Stairwells and alarms are located on the same Nodes for each floor. Exits are only on the first floor. Peopel and Threats can be placed on any non-Wall Node in the building. Note: Seeds in the cfg file have not yet been implemented in the program. ModelInputs.cpp is used to store all of the parsed inputs from the cfg. UserInput.h takes input from the user from the console.

***Simulate.cpp does all the heavy lifting. Uses the inputs to generate a building and places threats and people into the building. Simulate.cpp then starts all threads then calls join on all threads to complete the program.

***Floor.cpp is a a 2-dimensional matrix of Node.cpp. Each Node stores information about its current state (is a Person on it?, is it a wall?, is it an exit?, is it on fire?, etc.). Person.cpp and Threat.cpp are child classes of MoveableObject.cpp. MoveableObject contains virtual functions to start threads and start the simulation along with storing the objects current node, floor, and building. A Person moves by first checking what its current goalState is (no goal, get to stairwell, get to alarm, or get to exit). Once that is determined it goes for the shortest path to its goal Node. A Threat moves randomly to a neighboring Node, but at a slower rater (cycle duration is much shorter for a Person object than a Threat object).

Expected behavior or output of the program:
***The program will print to the console what each MoveableObject is doing. Every 5 total moves made by the combination of all Person objects will cause either the first floor or the entire building to be printed to the console based on what the user input. The program will end once everyone has exited the building.


How/Where rubric points are addressed: 
(The README also indicates where in the code (i.e. files and line numbers) that the rubric points are addressed.)
The submission must compile and run.

Criteria: README
- All criteria for the README is within this file.
*** Complete - Note lines were excluded when the criteria was filled by a whole file rather than a specific line


Criteria: Compiling and Testing
- The program compiles and runs using cmake and make as described in the Instructions for building/running
  the project in this file above without errors.
*** Complete


Criteria: Loops, Functions, I/O
- The project demonstrates an understanding of C++ functions and control structures.
-- A variety of control structures are used in the project.
*** There are many examples of if, else if, and while loop structures in Simulate.cpp (line 32) and in Person.cpp in Person::Travel() (lines 48 to end).

-- The project code is clearly organized into functions.
*** Project utilizes functions in Node.cpp to help with getting and setting Node states. Floor.cpp, InputParser.cpp, MoveableState.cpp, and others utilze many functions. Admittedly, Person::Travel() and Simulate() could have been broken into more, smaller functions

- The project reads data from a file and process the data, or the program writes data to a file.
-- The project reads data from an external file or writes data to a file as part of the necessary operation of the program.
*** The project reads in DefaultParameters.cfg (or a user made cfg) and processes its data using InputParser.cpp. The program does not write to a new file, but it does write to the console.

- The project accepts user input and processes the input.
-- The project accepts input from a user as part of the necessary operation of the program.
*** The project accepts input from the user via the console as a necessary part by utilizing UserInput.h. In Capstone.cpp (line 25) the user is prompted for input. 

Criteria: Object Oriented Programming
- The project uses Object Oriented Programming techniques.
-- The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks.
*** Seen in all classes especially Node.h/Node.cpp, MoveableObject.h/MoveableObject.cpp

- Classes use appropriate access specifiers for class members.
-- All class data members are explicitly specified as public, protected, or private.
*** Seen in all classes especially Node.h/Node.cpp, MoveableObject.h/MoveableObject.cpp

- Class constructors utilize member initialization lists.
-- All class members that are set to argument values are initialized through member initialization lists.
*** The constructor for Simulate.cpp utilizing an initialization list (line 3)

- Classes abstract implementation details from their interfaces.
-- All class member functions document their effects, either through function names, comments, or formal documentation. Member functions do not change program state in undocumented ways.
*** All classes except for UserInput.h and Capstone.cpp use a header (.h) and source (.cpp) file to adhere to abstraction. Function names are clear.

- Classes encapsulate behavior.
-- Appropriate data and functions are grouped into classes. Member data that is subject to an invariant is hidden from the user. State is accessed via member functions.
*** Node.h/Node.cpp is a good example with getters and setters. Data is split appropriately amongst many classes (Node, MoveableObject, Floor, etc.)

- Classes follow an appropriate inheritance hierarchy.
-- Inheritance hierarchies are logical. Composition is used instead of inheritance when appropriate. Abstract classes are composed of pure virtual functions. Override functions are specified.
*** MoveableObject.cpp is an abstract class that is the parent of Threat.cpp and Person.cpp. Threat and Person override pure virtual functions StartSim() and Travel() (Person.h line 25 and 26 contain overide declarations. Implementations for Person.cpp is between lines 26 - ~260 for example) and utilize the data in MoveableObject.cpp.

- Overloaded functions allow the same function to operate on different parameters.
-- One function is overloaded with different signatures for the same function name.
*** No functions are overloaded with different signatures. 

- Derived class functions override virtual base class functions.
-- One member function in an inherited class overrides a virtual base class member function.
*** Person.h line 25 and 26 contain overide declarations to its parent MoveableObject. Implementations for Person.cpp is between lines 26 - ~260. Threat also overrides MoveableObject functions.

- Templates generalize functions in the project.
-- One function is declared with a template that allows it to accept a generic parameter.
*** No templates were used.

Criteria: Memory Management
- The project makes use of references in function declarations.
-- At least two variables are defined as references, or two functions use pass-by-reference in the project code.
*** Simulate constructor uses a variable by reference and variable by R-value reference (Simulate.cpp line 3)

- The project uses destructors appropriately.
-- At least one class that uses unmanaged dynamically allocated memory, along with any class that otherwise needs to modify state upon the termination of an object, uses a destructor.
*** UserInput.h uses a destructor (lines 43-50)

- The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
-- The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction.
*** Simulate.cpp uses RAII to intialize variables and uses its scope to ensure their automatic destruction For example line 17 Floor objects are declared and initalized, and they are destroyed when Simulate::Simulate() goes out of scope.

- The project follows the Rule of 5.
-- For all classes, if any one of the copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined, then all of these functions are defined.
*** UserInput.h implements the rule of 5.

- The project uses move semantics to move data, instead of copying it, where possible.
-- For classes with move constructors, the project returns objects of that class by value, and relies on the move constructor, instead of copying the object.
*** Capstone.cpp passes UserInput object by moving it (Capstone.cpp line 27)

- The project uses smart pointers instead of raw pointers.
-- The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr. The project does not use raw pointers.
*** Shared pointers are used throughout the project: See MovableObject line 58. The only non-smart pointers are in UserInput.h which utilizes the Rule of 5 to ensure proper use of the pointer.

Criteria: Concurrency
- The project uses multithreading.
-- The project uses multiple threads in the execution.
*** Threat::StartSim() and Person::StartSim() start threads. They are called in Simulate.cpp lines 74 and 81.

- A promise and future is used in the project.
-- A promise and future is used to pass data from a worker thread to a parent thread in the project code.
*** Promise and future are used to ensure threads start in Simulate lines 74-76 and 81-83.

- A mutex or lock is used in the project.
-- A mutex or lock (e.g. std::lock_guard or `std::unique_lock) is used to protect data that is shared across multiple threads in the project code.
*** Threat::Travel() and Person::Travel() (person.cpp line 57) utilize a unique lock.

- A condition variable is used in the project.
-- A std::condition_variable is used in the project code to synchronize thread execution.
*** No condition variable is used in the project.
