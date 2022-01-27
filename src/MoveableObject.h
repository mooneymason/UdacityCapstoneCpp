#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <mutex>
#include <iostream>
#include <chrono>
#include <future>

#include "Node.h"
#include "Floor.h"


enum class MoveableObjectType
{
	NoObj,
	Person,
	Threat
};

class MoveableObject
{
public:
	// constructor and destructor
	MoveableObject();
	~MoveableObject();

	// pure virtual methods
	virtual void Travel() = 0;
	virtual std::thread StartSim(std::promise<std::string>&& prms) = 0;

	// Setters
	void SetLevel(int lvl);
	void SetType(MoveableObjectType type);
	void SetNode(std::shared_ptr<Node> n);
	void SetFloor(std::shared_ptr<Floor> f);
	void SetBuilding(std::vector<std::shared_ptr<Floor>> b);
	void SetMoveCounter(std::shared_ptr<int> counter);
	void SetFloorsToPrint(bool printAllFloors);

	void UpdateMoveCounter();

	
	// Getters
	bool GetWhichFloorsToPrint();
	int GetMoveCounterValue();
	int GetLevel();
	std::shared_ptr<Node> GetCurrentNode();
	std::shared_ptr<Floor> GetFloor();
	std::vector<std::shared_ptr<Floor>> GetBuilding();
	
	
protected:
	int _id; // Unique for each MoveableObject obj (including obj of children classes)
	MoveableObjectType _type; // identifies which child class the obj is
	int _level; // current level (another way to see what floor the Obj is on)
	
	std::shared_ptr<Node> _currentNode; // current node
	std::shared_ptr<Floor> _currentFloor; // current floor
	std::vector<std::shared_ptr<Floor>> _building; // the building all objects share
	static std::mutex _mutex1; // mutex to ensure MoveableObjects can read and change the nodes of the building one at a time
	std::shared_ptr<int> _moveCounter; // used to determine when to print - keeps track of moves by all Person objects
	bool _floorsToPrint; // True to print all floors. False to print first floor only.

private:
	static int _idCount; // global variable for counting object ids
	
};
