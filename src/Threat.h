#pragma once
#include "MoveableObject.h"
#include <future>
class Threat :
    public MoveableObject 
{
public:
    Threat(int level, std::vector<std::shared_ptr<Floor>> building, std::shared_ptr<Floor> startFloor, std::shared_ptr<Node> startNode);

    void Travel() override;
    std::thread StartSim(std::promise<std::string>&& prms) override;
    
private:
   
};

