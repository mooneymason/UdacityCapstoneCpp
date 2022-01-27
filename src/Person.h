#pragma once

#include <vector>
#include <algorithm>
#include <future>

#include "MoveableObject.h"

enum class GoalState
{
    None,
    Alarm,
    Stairwell,
    Exit
};


class Person :
    public MoveableObject 
{
public:
    // Constructor
    Person(int level, std::vector<std::shared_ptr<Floor>> building, std::shared_ptr<Floor> startFloor, std::shared_ptr<Node> startNode);

    void Travel() override;
    std::thread StartSim(std::promise<std::string>&& prms) override;

    GoalState GetGoalState();
    void SetGoalState(GoalState state);
    bool CheckIfExited();

private:
    bool _hasExited = false;
    GoalState _goalState = GoalState::None;
   
};

