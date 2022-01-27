#include "Threat.h"

Threat::Threat(int level, std::vector<std::shared_ptr<Floor>> building, std::shared_ptr<Floor> startFloor, std::shared_ptr<Node> startNode)
{
    SetLevel(level);
    SetBuilding(building);
    SetFloor(startFloor);
    SetNode(startNode);

    _currentNode->SetThreatState(ThreatState::Fire);
}

void Threat::Travel()
{
    double cycleDuration = 4;
    std::chrono::time_point<std::chrono::system_clock> lastUpdate;
    long timeSinceLastUpdate;

    int positionInNeighVec;
    int numNeighbors;
    bool foundValidRandPos;
    int randomCount;
    int numPeopleInBuilding = 1; // initialize to any positive value

    // init stop watch
    lastUpdate = std::chrono::system_clock::now();

    
    while (GetMoveCounterValue() < 1000 && numPeopleInBuilding > 0)
    {
        // sleep at every iteration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        // compute time difference to stop watch
        timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
        if (timeSinceLastUpdate >= cycleDuration)
        {
            std::unique_lock<std::mutex> lck(_mutex1);
            positionInNeighVec = -1000;
            numNeighbors = _currentNode->GetNeighbors().size();
            foundValidRandPos = false;
            randomCount = 0;
            numPeopleInBuilding = 0;
            while (!foundValidRandPos)
            {
                positionInNeighVec = rand() % numNeighbors;
                if (_currentNode->GetNeighbors()[positionInNeighVec]->GetBuildingState() != BuildingState::Wall && _currentNode->GetNeighbors()[positionInNeighVec]->GetThreatState() != ThreatState::Fire)
                {
                    foundValidRandPos = true;
                }
                else
                {
                    randomCount++;
                }

                if (randomCount >= 2)
                {
                    // Fire does not spread.
                    return;
                }

            }
            if (positionInNeighVec != -1000) // fire does not spread if there is no valid position to spread to 
            {
                _currentNode = _currentNode->GetNeighbors()[positionInNeighVec];
                _currentNode->SetThreatState(ThreatState::Fire);
                std::cout << "MoveableObject #" << _id << " (Threat) spread to a neighbor." << std::endl;
            }

            for (int i = 0; i < GetBuilding().size(); i++)
            {
                for (int j = 0; j < GetBuilding()[i]->getLength(); j++)
                {
                    for (int k = 0; k < GetBuilding()[i]->getWidth(); k++)
                    {
                        if (GetBuilding()[i]->getGrid()[j][k]->GetPersonState() == PersonState::Occupied)
                        {
                            numPeopleInBuilding += 1;
                        }
                    }
                }
            }

            lck.unlock();
        }
        lastUpdate = std::chrono::system_clock::now();
    } // end of simulation loop

    return;
}

std::thread Threat::StartSim(std::promise<std::string>&& prms)
{
    std::string message = "MoveableObject thread #" + std::to_string(_id) + " started. (Threat)\n";
    prms.set_value(message);
    return std::thread(&Threat::Travel, this);
}