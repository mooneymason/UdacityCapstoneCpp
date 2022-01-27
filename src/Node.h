#pragma once
#include <vector>
#include <memory>
#include <string>


enum class BuildingState
{
	Empty,
	Wall,
	Stairwell,
	Alarm,
	Exit,
	Invalid
};

enum class AlarmState
{
	Inactive, // only nodes with BuildingState::Alarm can be Inactive
	Active, // Active applies to all nodes as everyone in the building can hear the alarms
	NoAlarm 
};

enum class ThreatState
{
	NoThreat,
	Fire
};

enum class PersonState
{
	Unoccupied,
	Occupied
};


class Node
{
public:
	//Constructors
	Node();

	// Setters
	void SetAllDistances(std::pair<int, int> positionOfNode, std::vector<std::pair<int, int>> positionOfAlarms, std::vector<std::pair<int, int>> positionOfStairwells, std::vector<std::pair<int, int>> positionOfExits);
	void SetDistanceToAlarm(std::pair<int, int> positionOfNode, std::vector<std::pair<int, int>> positionOfAlarms);
	void SetDistanceToStairwell(std::pair<int, int> positionOfNode, std::vector<std::pair<int, int>> positionOfStairwells);
	void SetDistanceToExit(std::pair<int, int> positionOfNode, std::vector<std::pair<int, int>> positionOfExits);
	void SetAlarmState(AlarmState newAlarmState);
	void SetBuildingState(BuildingState newBuildingState);
	void SetPersonState(PersonState newPersonState);
	void SetThreatState(ThreatState newThreatState);
	void SetNeighbors(std::vector<std::shared_ptr<Node>> neighbors);
	
	void AddNeighbor(std::shared_ptr<Node> neighbor);
	
	// Getters
	AlarmState GetAlarmState();
	BuildingState GetBuildingState();
	PersonState GetPersonState();
	ThreatState GetThreatState();
	std::vector<std::shared_ptr<Node>> GetNeighbors();
	int GetDistanceToAlarm();
	int GetDistanceToStairwell();
	int GetDistanceToExit();
	
	std::string NodeString(); // used to print the various states of the node to console

private:
	BuildingState _buildingState = BuildingState::Empty;
	AlarmState _alarmState = AlarmState::NoAlarm;
	PersonState _personState = PersonState::Unoccupied;
	ThreatState _threatState = ThreatState::NoThreat;
	
	std::vector<std::shared_ptr<Node>> _neighbors;

	int _distanceToAlarm;
	int _distanceToStairwell;
	int _distanceToExit;
};

