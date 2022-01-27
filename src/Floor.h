#pragma once

#include <memory>
#include <iostream>

#include "Node.h"

class Floor
{
public:
	// Constructor
	Floor(
		int level,
		int length,
		int width,
		std::vector<std::pair<int,int>> locExits,
		std::vector<std::pair<int, int>> locStairwells,
		std::vector<std::pair<int, int>> locAlarms,
		std::vector<std::pair<int, int>> locThreats,
		std::vector<std::pair<int, int>> locPersons
	);

	// Getters
	std::vector<std::vector<std::shared_ptr<Node>>> getGrid();
	int getWidth();
	int getLength();
	int getLevel();
	std::vector<std::pair<int, int>> getExitLocations();
	std::vector<std::pair<int, int>> getAlarmLocations();
	std::vector<std::pair<int, int>> getStairwellLocations();

	void PrintFloor();

	// Setters
	void setInitialGrid();
	void setWidth(int width);
	void setLength(int length);
	void setLevel(int level);
	void setExitLocations(std::vector<std::pair<int, int>> locExits);
	void setAlarmLocations(std::vector<std::pair<int, int>> locAlarms);
	void setStairwellLocations(std::vector<std::pair<int, int>> locStairwells);
	void setThreatLocations(std::vector<std::pair<int, int>> locThreats);
	void setPersonLocations(std::vector<std::pair<int, int>> locPersons);
	
	void setAllNodesToAlarmStateActive();

private:
	std::vector<std::vector<std::shared_ptr<Node>>> _grid;

	int _length; // (always first) 
	int _width; // (alsways second)
	int _level;


	std::vector<std::pair<int, int>> _locExits; 
	std::vector<std::pair<int, int>> _locStairwells;
	std::vector<std::pair<int, int>> _locAlarms;
	std::vector<std::pair<int, int>> _locThreats;
	std::vector<std::pair<int, int>> _locPersons;
};

