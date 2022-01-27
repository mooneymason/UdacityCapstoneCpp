#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <algorithm>
#include <map>

struct ModelInputs
{
    //InputParameters RunConfig
    int numRuns;
    int seed1;
    int seed2;

    //InputParameters Building
    int numFloors;
    int lengthFloor;
    int widthFloor;

    //InputParameters Building MainFloor
    std::vector<std::pair<int, int>> locExits; // Exits are only placed on the first floor
    
    //InputParameters Building Occupants
    std::vector<std::vector<std::pair<int, int>>> locOccupants;

    //InputParameters Building Threat
    std::vector<std::vector<std::pair<int, int>>> locThreats; // { {} , {} , {} } give threat locations on each floor

    //InputParameters Building Stairwells
    std::vector<std::pair<int, int>> locStairwells; // Stairwells are at the same location on every floor

    //InputParameters Building Alarms
    std::vector<std::pair<int, int>> locAlarms; // Alarms are at the same location on every floor

};

class InputParser
{
public:

    // Constructors
    InputParser();
    InputParser(std::string path);

    // Help to read in locations in [x,y] or [[x1,y1], [x2,y2]] forms
    std::pair<int, int> stringToPair(std::string line);
    std::vector<std::pair<int, int>> stringToVectorPairs(std::string line);
    std::vector<std::vector<std::pair<int, int>>> stringToVectorVectorPairs(std::string line);

    // Read all values from the cfg file
    void ReadValues();

    // Getters and Setters for cfg file path
    void setPath(std::string path);
    std::string getPath();

    // Get ModelInputs
    ModelInputs getModelInputs();
   
private:
    std::string _path;
    ModelInputs _input;

};

