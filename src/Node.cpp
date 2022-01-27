#include "Node.h"

// Constructor
Node::Node()
{
	BuildingState::Invalid;
	_distanceToAlarm = -1;
	_distanceToExit = -1;
	_distanceToStairwell = -1;
}

// Setters
void Node::SetBuildingState(BuildingState newBuildingState) { _buildingState = newBuildingState; }
void Node::SetPersonState(PersonState newPersonState) { _personState = newPersonState; }
void Node::SetThreatState(ThreatState newThreatState) { _threatState = newThreatState; }
void Node::SetAlarmState(AlarmState newAlarmState) { _alarmState = newAlarmState; }


void Node::SetDistanceToAlarm(std::pair<int, int> positionOfNode, std::vector<std::pair<int, int>> positionOfAlarms)
{
	int count = 0;
	int tempDistance = 0;
	for (std::pair<int, int> goal : positionOfAlarms)
	{
		tempDistance = std::abs(goal.first - positionOfNode.first) + std::abs(goal.second - positionOfNode.second);
		if (count == 0 or tempDistance < _distanceToAlarm)
		{
			_distanceToAlarm = tempDistance;
		}
		count += 1;
	}
}

void Node::SetDistanceToStairwell(std::pair<int, int> positionOfNode, std::vector<std::pair<int, int>> positionOfStairwells)
{
	int count = 0;
	int tempDistance = 0;
	for (std::pair<int, int> goal : positionOfStairwells)
	{
		tempDistance = std::abs(goal.first - positionOfNode.first) + std::abs(goal.second - positionOfNode.second);
		if (count == 0 or tempDistance < _distanceToStairwell)
		{
			_distanceToStairwell = tempDistance;
		}
		count += 1;
	}
}

void Node::SetDistanceToExit(std::pair<int, int> positionOfNode, std::vector<std::pair<int, int>> positionOfExits)
{
	int count = 0;
	int tempDistance = 0;
	for (std::pair<int, int> goal : positionOfExits)
	{
		tempDistance = std::abs(goal.first - positionOfNode.first) + std::abs(goal.second - positionOfNode.second);
		if (count == 0 or tempDistance < _distanceToExit)
		{
			_distanceToExit = tempDistance;
		}
		count += 1;
	}
}

void Node::SetAllDistances(std::pair<int, int> positionOfNode, std::vector<std::pair<int, int>> positionOfAlarms, std::vector<std::pair<int, int>> positionOfStairwells, std::vector<std::pair<int, int>> positionOfExits)
{
	SetDistanceToAlarm(positionOfNode, positionOfAlarms);
	SetDistanceToStairwell(positionOfNode, positionOfStairwells);
	SetDistanceToExit(positionOfNode, positionOfExits);
}

void Node::SetNeighbors(std::vector<std::shared_ptr<Node>> neighbors)
{
	_neighbors = neighbors;
}

void Node::AddNeighbor(std::shared_ptr<Node> neighbor)
{
	_neighbors.emplace_back(neighbor);
}

// Getters
std::string Node::NodeString()
{
	std::string temp;
	if (GetBuildingState() == BuildingState::Empty)
	{
		if (GetThreatState() == ThreatState::NoThreat && GetPersonState() == PersonState::Unoccupied)
		{
			temp = "0  ";
		}
		else if (GetThreatState() == ThreatState::Fire && GetPersonState() == PersonState::Unoccupied)
		{
			temp = "F  ";
		}
		else if (GetThreatState() == ThreatState::NoThreat && GetPersonState() == PersonState::Occupied)
		{
			temp = "P  ";
		}
		else if (GetThreatState() == ThreatState::Fire && GetPersonState() == PersonState::Occupied)
		{
			temp = "PF ";
		}
	}
	else if (GetBuildingState() == BuildingState::Stairwell)
	{
		if (GetThreatState() == ThreatState::NoThreat && GetPersonState() == PersonState::Unoccupied)
		{
			temp = "S  ";
		}
		else if (GetThreatState() == ThreatState::Fire && GetPersonState() == PersonState::Unoccupied)
		{
			temp = "SF ";
		}
		else if (GetThreatState() == ThreatState::NoThreat && GetPersonState() == PersonState::Occupied)
		{
			temp = "SP ";
		}
		else if (GetThreatState() == ThreatState::Fire && GetPersonState() == PersonState::Occupied)
		{
			temp = "SPF";
		}
	}
	else if (GetBuildingState() == BuildingState::Alarm)
	{
		if (GetAlarmState() == AlarmState::Active)
		{
			if (GetThreatState() == ThreatState::NoThreat && GetPersonState() == PersonState::Unoccupied)
			{
				temp = "A  ";
			}
			else if (GetThreatState() == ThreatState::Fire && GetPersonState() == PersonState::Unoccupied)
			{
				temp = "AF ";
			}
			else if (GetThreatState() == ThreatState::NoThreat && GetPersonState() == PersonState::Occupied)
			{
				temp = "AP ";
			}
			else if (GetThreatState() == ThreatState::Fire && GetPersonState() == PersonState::Occupied)
			{
				temp = "APF";
			}
		}
		else
		{
			if (GetThreatState() == ThreatState::NoThreat && GetPersonState() == PersonState::Unoccupied)
			{
				temp = "a  ";
			}
			else if (GetThreatState() == ThreatState::Fire && GetPersonState() == PersonState::Unoccupied)
			{
				temp = "aF ";
			}
			else if (GetThreatState() == ThreatState::NoThreat && GetPersonState() == PersonState::Occupied)
			{
				temp = "aP ";
			}
			else if (GetThreatState() == ThreatState::Fire && GetPersonState() == PersonState::Occupied)
			{
				temp = "aPF";
			}
		}
	}
	else if (GetBuildingState() == BuildingState::Exit)
	{
		if (GetThreatState() == ThreatState::NoThreat && GetPersonState() == PersonState::Unoccupied)
		{
			temp = "E  ";
		}
		else if (GetThreatState() == ThreatState::Fire && GetPersonState() == PersonState::Unoccupied)
		{
			temp = "EF ";
		}
		else if (GetThreatState() == ThreatState::NoThreat && GetPersonState() == PersonState::Occupied)
		{
			temp = "EP ";
		}
		else if (GetThreatState() == ThreatState::Fire && GetPersonState() == PersonState::Occupied)
		{
			temp = "EPF";
		}
	}
	else if (GetBuildingState() == BuildingState::Wall)
	{
		temp = "W  ";
	}

	return temp;
}

std::vector<std::shared_ptr<Node>> Node::GetNeighbors()
{
	return _neighbors;
}

int Node::GetDistanceToAlarm()
{
	return _distanceToAlarm;
}
int Node::GetDistanceToStairwell()
{
	return _distanceToStairwell;
}
int Node::GetDistanceToExit()
{
	return _distanceToExit;
}


AlarmState Node::GetAlarmState() { return _alarmState; }
BuildingState Node::GetBuildingState() { return _buildingState; }
PersonState Node::GetPersonState() { return _personState; }
ThreatState Node::GetThreatState() { return _threatState; }