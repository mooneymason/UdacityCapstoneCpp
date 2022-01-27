#include "InputParser.h"

InputParser::InputParser()
{
    // Sets to default input cfg file
    //setPath("/home/workspace/UdacityCapstone/capstone_cmake/src/DefaultInputParameters.cfg");
    setPath("../src/DefaultInputParameters.cfg");
    ReadValues();
}

InputParser::InputParser(std::string path)
{
    // Use to specify input cfg file
    setPath(path);
    ReadValues();
}

void InputParser::setPath(std::string path)
{
    _path = path;
}

std::string InputParser::getPath()
{
    return _path;
}

std::pair<int, int> InputParser::stringToPair(std::string line)
{
    std::pair<int, int> pair;

    // isolate [x,y] by removing everything else
    auto lastRightBracePos = line.find_last_of(']');
    auto firstLeftBracePos = line.find_first_of("[");
    line = line.substr(firstLeftBracePos, lastRightBracePos+1);

    // Remove braces [ ]
    auto start = line.find_first_of('[');
    auto end = line.find_last_of(']');
    line.erase(start, 1);
    line.erase(end - 1,1);

    // Get x and y
    auto cPos = line.find(",");
    int x = std::stoi(line.substr(0, cPos));
    int y = std::stoi(line.substr(cPos + 1, line.length()));
    
    pair = { x, y };

    return pair;
}

std::vector<std::pair<int, int>> InputParser::stringToVectorPairs(std::string line)
{
    std::vector<std::pair<int, int>> vecOfPairs;
    
    //strip off extra [ ] then go one by one until all pairs are parsed
    auto firstLeftBracePos = line.find_first_of("[");
    auto lastRightBracePos = line.find_last_of("]");
    line = line.substr(firstLeftBracePos + 1, lastRightBracePos);

    // count number of [ to determine # of pairs
    int n = std::count(line.begin(), line.end(), '[');
    std::string temp;

    
    for (int i = 0; i < n; i++)
    {
        auto firstLeftBracePos = line.find_first_of("[");
        auto firstRightBracePos = line.find_first_of("]");
        temp = line.substr(firstLeftBracePos, firstRightBracePos+1); // [x,y]
        vecOfPairs.emplace_back(stringToPair(temp));
        line = line.substr(firstRightBracePos + 1, line.length()); // + 1 should remove comma
    }
    
    return vecOfPairs;
}

std::vector<std::vector<std::pair<int, int>>> InputParser::stringToVectorVectorPairs(std::string line)
{
    std::vector<std::vector<std::pair<int, int>>> vecVecPairs;

    auto firstLeftBracePos = line.find_first_of("[");
    auto lastRightBracePos = line.find_last_of("]");
    line = line.substr(firstLeftBracePos + 1, lastRightBracePos - 1);

    while ((line.find("[[")) != std::string::npos)
    {
        int posLeftDoubleBrace = line.find("[[");
        int posRightDoubleBrace = line.find("]]");
        std::string subLine = line.substr(posLeftDoubleBrace, posRightDoubleBrace + 2);
        vecVecPairs.push_back(stringToVectorPairs(subLine));
        line = line.substr(subLine.length());
    }
    return vecVecPairs;
}

void InputParser::ReadValues()
{

    std::ifstream cfgFile(_path);

    if (cfgFile.is_open())
    {
        std::string line;
        while (getline(cfgFile, line))
        {
            line.erase(std::remove_if(line.begin(), line.end(), isspace),
                line.end());
           
            // Remove comments
            if (line.find("//") != std::string::npos)
            {
                auto commentPos = line.find("//");
                line = line.substr(0, commentPos);
            }
            if (line.find("/*") != std::string::npos)
            {
                while (line.find("*/") == std::string::npos)
                    getline(cfgFile, line);
            }

            if (line.empty())
            {
                continue;
            }
            if (line.find("NumberOfRuns") != std::string::npos)
            {
                auto delimiterPos = line.find("=");
                _input.numRuns = std::stoi(line.substr(delimiterPos + 1));
            }
            else if (line.find("Seed1") != std::string::npos)
            {
                auto delimiterPos = line.find("=");
                _input.seed1 = std::stoi(line.substr(delimiterPos + 1));
            }
            else if (line.find("Seed2") != std::string::npos)
            {
                auto delimiterPos = line.find("=");
                _input.seed2 = std::stoi(line.substr(delimiterPos + 1));
            }
            else if (line.find("NumberOfFloors") != std::string::npos)
            {
                auto delimiterPos = line.find("=");
                _input.numFloors = std::stoi(line.substr(delimiterPos + 1));
            }
            else if (line.find("LengthOfFloors") != std::string::npos)
            {
                auto delimiterPos = line.find("=");
                _input.lengthFloor = std::stoi(line.substr(delimiterPos + 1));
            }
            else if (line.find("WidthOfFloors") != std::string::npos)
            {
                auto delimiterPos = line.find("=");
                _input.widthFloor = std::stoi(line.substr(delimiterPos + 1));
            }
            else if (line.find("LocationOfOccupants") != std::string::npos)
            {
                auto delimiterPos = line.find("=");
                std::string vectorToParse = line.substr(delimiterPos + 1);
                _input.locOccupants = stringToVectorVectorPairs(vectorToParse);
            }
            else if (line.find("LocationOfThreats") != std::string::npos)
            {
                auto delimiterPos = line.find("=");
                std::string vectorToParse = line.substr(delimiterPos + 1);
                _input.locThreats = stringToVectorVectorPairs(vectorToParse);
            }
            else if (line.find("LocationOfExits") != std::string::npos)
            {
                auto delimiterPos = line.find("=");
                std::string vectorToParse = line.substr(delimiterPos + 1);
                _input.locExits = stringToVectorPairs(vectorToParse);
            }
            else if (line.find("LocationOfStairwells") != std::string::npos)
            {
                auto delimiterPos = line.find("=");
                std::string vectorToParse = line.substr(delimiterPos + 1);
                _input.locStairwells = stringToVectorPairs(vectorToParse);
            }
            else if (line.find("LocationOfAlarms") != std::string::npos)
            {
                auto delimiterPos = line.find("=");
                std::string vectorToParse = line.substr(delimiterPos + 1);
                _input.locAlarms = stringToVectorPairs(vectorToParse);
            }
        }
    }
    else
    {
        std::cerr << "Couldn't open config file for reading.\n";
    }
}

ModelInputs InputParser::getModelInputs()
{
    return _input;
}