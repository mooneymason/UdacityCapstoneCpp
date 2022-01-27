#include "Person.h"


Person::Person(int level, std::vector<std::shared_ptr<Floor>> building, std::shared_ptr<Floor> startFloor, std::shared_ptr<Node> startNode)
{
    SetType(MoveableObjectType::Person);
    SetLevel(level);
    SetBuilding(building);
    SetFloor(startFloor);
    SetNode(startNode);

    // could check if BuildState is a wall or if PersonState is occupied but isn't necessary with current program
    startNode->SetPersonState(PersonState::Occupied);
}

GoalState Person::GetGoalState()
{
    return _goalState;
}

void Person::SetGoalState(GoalState state)
{
    _goalState = state;
}

std::thread Person::StartSim(std::promise<std::string>&& prms)
{
   std::string message = "MoveableObject thread #" + std::to_string(_id) + " started. (Person)\n";
   prms.set_value(message);
   return std::thread(&Person::Travel, this);
}

void Person::Travel()
{
    double cycleDuration = 1;
    std::chrono::time_point<std::chrono::system_clock> lastUpdate;
    long timeSinceLastUpdate;
    int distToGoal;
    int positionInNeighVec;
    int tempDist;
    int numNeighbors;
    bool foundValidRandPos;
    int randomCount;

    // init stop watch
    lastUpdate = std::chrono::system_clock::now();

    while (!_hasExited)
    {
        // sleep at every iteration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
       
        // compute time difference to stop watch
        timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
        if (timeSinceLastUpdate >= cycleDuration)
        {
            std::unique_lock<std::mutex> lck(_mutex1);
            distToGoal = -1000;
            positionInNeighVec = -1000;
            numNeighbors = _currentNode->GetNeighbors().size();
            foundValidRandPos = false;
            randomCount = 0;
            if (_currentNode->GetAlarmState() == AlarmState::Active)
            {
                if (_level == 1)
                {
                    SetGoalState(GoalState::Exit);
                }
                else
                {
                    SetGoalState(GoalState::Stairwell);
                }
            }

            if (GetGoalState() == GoalState::None)
            {
                for (int i = 0; i < _currentNode->GetNeighbors().size(); i++)
                {
                    if (_currentNode->GetNeighbors()[i]->GetThreatState() == ThreatState::Fire)
                    {
                        //lck.lock();
                        std::cout << "MoveableObject #" << _id << " (Person) has discovered the fire." << std::endl;
                        //lck.unlock();
                        this->SetGoalState(GoalState::Alarm);
                    }
                }
            }

            if (GetGoalState() == GoalState::None)
            {

                while (!foundValidRandPos)
                {
                    positionInNeighVec = rand() % numNeighbors;
                    if (_currentNode->GetNeighbors()[positionInNeighVec]->GetBuildingState() != BuildingState::Wall && _currentNode->GetNeighbors()[positionInNeighVec]->GetPersonState() != PersonState::Occupied)
                    {
                        foundValidRandPos = true;
                    }
                    else
                    {
                        randomCount++;
                    }

                    if (randomCount >= 6)
                    {
                        // Person does not move.
                        return;
                    }

                }
            }
            else if (GetGoalState() == GoalState::Alarm)
            {
                for (int i = 0; i < _currentNode->GetNeighbors().size(); i++)
                {
                    if (_currentNode->GetNeighbors()[i]->GetBuildingState() != BuildingState::Wall && _currentNode->GetNeighbors()[i]->GetPersonState() != PersonState::Occupied)
                    {

                        tempDist = _currentNode->GetNeighbors()[i]->GetDistanceToAlarm();
                        if (positionInNeighVec == -1000 || tempDist < distToGoal)
                        {
                            distToGoal = tempDist;
                            positionInNeighVec = i;
                        }
                    }
                }
                if (distToGoal == 0)
                {
                    // pull the alarm
                    std::cout << "MoveableObject #" << _id << " (Person) has activated the alarms." << std::endl;
                    for (int indx = 0; indx < _building.size(); indx++)
                    {
                        _building[indx]->setAllNodesToAlarmStateActive();
                    }

                    if (_level == 1)
                    {
                        SetGoalState(GoalState::Exit);
                    }
                    else
                    {
                        SetGoalState(GoalState::Stairwell);
                    }
                }
            }
            else if (GetGoalState() == GoalState::Stairwell)
            {
                for (int i = 0; i < _currentNode->GetNeighbors().size(); i++)
                {
                    if (_currentNode->GetNeighbors()[i]->GetBuildingState() != BuildingState::Wall && _currentNode->GetNeighbors()[i]->GetPersonState() != PersonState::Occupied)
                    {
                        tempDist = _currentNode->GetNeighbors()[i]->GetDistanceToStairwell();
                        if (positionInNeighVec == -1000 || tempDist < distToGoal)
                        {
                            distToGoal = tempDist;
                            positionInNeighVec = i;
                        }
                    }
                }
                if (distToGoal == 0)
                {
                    // go down the stairs
                    // find loc of _currentNode
                    // loop through floor -- To do: having node store position would be more efficient
                    for (int l = 0; l < _currentFloor->getLength(); l++)
                    {
                        for (int w = 0; w < _currentFloor->getWidth(); w++)
                        {
                            if (_building[_level - 1]->getGrid()[l][w] == _currentNode)
                            {
                                if (_building[0]->getGrid()[l][w]->GetPersonState() == PersonState::Unoccupied) // goes immediately to first floor
                                {
                                    std::cout << "MoveableObject #" << _id << " (Person) used the stairs." << std::endl;
                                    _currentNode->SetPersonState(PersonState::Unoccupied);
                                    _currentNode = _building[0]->getGrid()[l][w];
                                    _currentFloor = _building[0];
                                    _level = 1;
                                    _currentNode->SetPersonState(PersonState::Occupied);
                                    SetGoalState(GoalState::Exit);
                                    continue;
                                }
                                else
                                {
                                    continue;
                                    // person does not move - basically waits until stairwell is unoccupied on next call to Travel()
                                }
                            }
                        }
                    }

                }
            }
            else if (GetGoalState() == GoalState::Exit)
            {
                for (int i = 0; i < _currentNode->GetNeighbors().size(); i++)
                {
                    if (_currentNode->GetNeighbors()[i]->GetBuildingState() != BuildingState::Wall && _currentNode->GetNeighbors()[i]->GetPersonState() != PersonState::Occupied)
                    {
                        tempDist = _currentNode->GetNeighbors()[i]->GetDistanceToExit();
                        if (positionInNeighVec == -1000 || tempDist < distToGoal)
                        {
                            distToGoal = tempDist;
                            positionInNeighVec = i;
                        }
                    }
                }
                if (distToGoal == 0)
                {
                    // exit the building
                    std::cout << "MoveableObject #" << _id << " (Person) has exited the building." << std::endl;
                    _hasExited = true;
                    _currentNode->SetPersonState(PersonState::Unoccupied);
                    _currentNode = nullptr; 
                }
            }
            if (positionInNeighVec != -1000 && !_hasExited) // person does not move if there is no valid position to move to 
            {
                _currentNode->SetPersonState(PersonState::Unoccupied);
                _currentNode = _currentNode->GetNeighbors()[positionInNeighVec];
                _currentNode->SetPersonState(PersonState::Occupied);
                std::cout << "MoveableObject #" << _id << " (Person) moved to a neighbor." << std::endl;
            }

            if (GetMoveCounterValue() % 5 == 0)
            {
                std::cout << std::endl;
                std::cout << "Move number: " << std::to_string(GetMoveCounterValue());
                if (GetWhichFloorsToPrint())
                {
                    for (int i = 0; i < GetBuilding().size(); i++)
                    {
                        std::cout << std::endl;
                        std::cout << "Floor number: " << std::to_string(i + 1) << std::endl;;
                            GetBuilding()[i]->PrintFloor();
                    }
                    std::cout << std::endl;
                }
                else
                {
                    std::cout << std::endl;
                    std::cout << "Floor number: 1" << std::endl;
                    GetBuilding()[0]->PrintFloor();
                    std::cout << std::endl;
                }
            }
            UpdateMoveCounter();

            lck.unlock();
        }
        lastUpdate = std::chrono::system_clock::now();
    } // end of simulation loop
    
}

bool Person::CheckIfExited()
{
    return _hasExited;
}



