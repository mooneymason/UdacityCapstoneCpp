#include "Floor.h"
#include "Person.h"

// Main floor with threat
Floor::Floor(
	int level,
	int length,
	int width,
	std::vector<std::pair<int, int>> locExits,
	std::vector<std::pair<int, int>> locStairwells,
	std::vector<std::pair<int, int>> locAlarms,
	std::vector<std::pair<int, int>> locThreats,
	std::vector<std::pair<int,int>> locPersons
	) : 
	_level(level), 
	_length(length), 
	_width(width),
	_locExits(locExits),
	_locStairwells(locStairwells),
	_locAlarms(locAlarms),
	_locThreats(locThreats),
	_locPersons(locPersons)
{
	setInitialGrid();
}

std::vector<std::vector<std::shared_ptr<Node>>> Floor::getGrid()
{
	return _grid;
}

int Floor::getWidth()
{
	return _width;
}

int Floor::getLength()
{
	return _length;
}

int Floor::getLevel()
{
	return _level;
}

std::vector<std::pair<int, int>> Floor::getExitLocations()
{
	return _locExits;
}

std::vector<std::pair<int, int>> Floor::getAlarmLocations()
{
	return _locAlarms;
}

std::vector<std::pair<int, int>> Floor::getStairwellLocations()
{
	return _locStairwells;
}


void Floor::PrintFloor()
{
	for (int i = 0; i < _grid.size(); i++) {
		for (int j = 0; j < _grid[i].size(); j++)
		{
			std::cout << _grid[i][j]->NodeString();
		}
		std::cout << "\n";
	}
}

void Floor::setInitialGrid()
{
	_grid.resize(_length);
	for (int i = 0; i < _length; i++)
	{
		_grid[i].resize(_width);
		for (int j = 0; j < _width; j++)
		{
			_grid[i][j] = std::make_shared<Node>();
		}
	}

	// These set location could be done with a template class
	setStairwellLocations(_locStairwells);
	setAlarmLocations(_locAlarms);
	setThreatLocations(_locThreats);
	setPersonLocations(_locPersons); // sets the unique_ptr _occupants for the node too

	if (_level == 1)
	{
		setExitLocations(_locExits);
	}

	for (int i = 0; i < _length; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			
			_grid[i][j]->SetAllDistances({ i, j }, _locAlarms, _locStairwells, _locExits);

			if (i > 0 && i < _length - 1 && j > 0 && j < _width - 1)
			{
				// directional deltas
				int delta[4][2]{ {-1, 0}, {0, -1}, {1, 0}, {0, 1} };

				// Loop through current node's potential neighbors.
				for (int n = 0; n < 4; n++)
				{
					_grid[i][j]->AddNeighbor(_grid[i + delta[n][0]][j + delta[n][1]]);
				}
			}
			if ((i == 0 || i == _length - 1 || j == 0 || j == _width - 1) && _grid[i][j]->GetBuildingState() != BuildingState::Exit)
			{
				_grid[i][j]->SetBuildingState(BuildingState::Wall);
			}
		}
	}
}

void Floor::setWidth(int width)
{
	_width = width;
}

void Floor::setLength(int length)
{
	_length = length;
}

void Floor::setLevel(int level)
{
	_level = level;
}

void Floor::setExitLocations(std::vector<std::pair<int, int>> locExits)
{
	_locExits = locExits;

	for (auto exit : _locExits)
	{
		// check that the current state is a wall so that an exit isn't in the middle of a the floor
		if (_grid[exit.first][exit.second]->GetBuildingState() != BuildingState::Alarm && _grid[exit.first][exit.second]->GetBuildingState() != BuildingState::Stairwell)
		{
			_grid[exit.first][exit.second]->SetBuildingState(BuildingState::Exit);
		}
		else
		{
			std::cout << "\nInvalid exit location: " << exit.first << ", " << exit.second << std::endl;
			std::cout << "That exit location was not created. Program continued." << std::endl;
		}
	}
}

void Floor::setAlarmLocations(std::vector<std::pair<int, int>> locAlarms)
{
	_locAlarms = locAlarms;

	for (auto alarm : _locAlarms)
	{
		_grid[alarm.first][alarm.second]->SetBuildingState(BuildingState::Alarm);
		_grid[alarm.first][alarm.second]->SetAlarmState(AlarmState::Inactive);
	}
}

void Floor::setStairwellLocations(std::vector<std::pair<int, int>> locStairwells)
{
	_locStairwells = locStairwells;

	for (auto stair : _locStairwells)
	{
		_grid[stair.first][stair.second]->SetBuildingState(BuildingState::Stairwell);
	}
}

void Floor::setThreatLocations(std::vector<std::pair<int, int>> locThreats)
{
	_locThreats = locThreats;

	for (auto threat : _locThreats)
	{
		if (threat.first != -1 && threat.second != -1)
		{
			_grid[threat.first][threat.second]->SetThreatState(ThreatState::Fire);
		}
	}
}

void Floor::setPersonLocations(std::vector<std::pair<int, int>> locPersons)
{
	_locPersons = locPersons;

	for (auto personPos : _locPersons)
	{
		if (personPos.first != -1 && personPos.second != -1)
		{
			_grid[personPos.first][personPos.second]->SetPersonState(PersonState::Occupied);
		}
	}
}

void Floor::setAllNodesToAlarmStateActive()
{
	for (int i = 0; i < _length; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			_grid[i][j]->SetAlarmState(AlarmState::Active);
		}
	}
}

