#include "MoveableObject.h"
#include <algorithm>
#include <iostream>
#include <chrono>

// init static variables
int MoveableObject::_idCount = 0;
std::mutex MoveableObject::_mutex1;

MoveableObject::MoveableObject()
{
	_type = MoveableObjectType::NoObj;
	_id = _idCount++;
	_level = -1;
	_floorsToPrint = true; // default print all floors
}

MoveableObject::~MoveableObject()
{
	// Simulate.cpp calls join() on all threads from MoveableObjects so no need for custom destructor
	// Keeping in case I choose to change Simulate or MoveableObjects in the future

	// thread barrier before this object is destroyed
	/*
	std::for_each(threads.begin(), threads.end(), [](std::thread& t) {
		t.join();
		});
	*/
}

void MoveableObject::SetMoveCounter(std::shared_ptr<int> counter)
{
	_moveCounter = counter;
}

void MoveableObject::SetFloorsToPrint(bool printAllFloors)
{
	_floorsToPrint = printAllFloors;
}

void MoveableObject::SetLevel(int lvl)
{
	_level = lvl;
}

void MoveableObject::SetType(MoveableObjectType type)
{
	_type = type;
}

void MoveableObject::SetNode(std::shared_ptr<Node> n)
{
	_currentNode = n;
}

void MoveableObject::SetFloor(std::shared_ptr<Floor> f)
{
	_currentFloor = f;
}

void MoveableObject::SetBuilding(std::vector<std::shared_ptr<Floor>> b)
{
	_building = b;
}


void MoveableObject::UpdateMoveCounter()
{
	*_moveCounter += 1;
}

bool MoveableObject::GetWhichFloorsToPrint()
{
	return _floorsToPrint;
}

int MoveableObject::GetMoveCounterValue()
{
	return *_moveCounter;
}

std::shared_ptr<Node> MoveableObject::GetCurrentNode()
{
	return _currentNode;
}

std::vector<std::shared_ptr<Floor>> MoveableObject::GetBuilding()
{
	return _building;
}

int MoveableObject::GetLevel()
{
	return _level;
}

std::shared_ptr<Floor> MoveableObject::GetFloor()
{
	return _currentFloor;
}
