#include "Simulate.h"

Simulate::Simulate(ModelInputs& modelInputs, UserInput&& userInputs): _modelInputs(modelInputs), _userInput(userInputs)
{

	std::vector<std::shared_ptr<Floor>> building{};
	std::vector<Person> people{};
	std::vector<Threat> threats{};

	std::vector<std::promise<std::string>> prms{}; // for Person
	std::vector<std::future<std::string>> futures{}; // for Person
	std::vector<std::promise<std::string>> prmsThreat{};
	std::vector<std::future<std::string>> futuresThreat{};

	for (int i = 0; i < modelInputs.numFloors; i++)
	{
		Floor f = Floor(
			i+1,
			modelInputs.lengthFloor,
			modelInputs.widthFloor,
			modelInputs.locExits,
			modelInputs.locStairwells,
			modelInputs.locAlarms,
			modelInputs.locThreats[i],
			modelInputs.locOccupants[i]
		);
		
		building.push_back(std::make_shared<Floor>(f));
	}

	bool printAllFloors;
	if (userInputs.GetFloorsToPrint() == "all")
	{
		printAllFloors = true;
	}
	else
	{
		printAllFloors = false;
	}

	// Initialize all Moveable Objects
	std::shared_ptr<int> moveCounter = std::make_shared<int>(0);
	for (int i = 0; i < modelInputs.numFloors; i++)
	{
		for (int j = 0; j < modelInputs.locOccupants[i].size(); j++)
		{
			std::pair<int, int> pLoc = modelInputs.locOccupants[i][j];
			Person p = Person(i + 1, building, building[i], building[i]->getGrid()[pLoc.first][pLoc.second]);
			p.SetMoveCounter(moveCounter);
			p.SetFloorsToPrint(printAllFloors);
			people.push_back(p);
		}

		for (int j = 0; j < modelInputs.locThreats[i].size(); j++)
		{
			std::pair<int, int> tLoc = modelInputs.locThreats[i][j];
			if (tLoc.first != -1 && tLoc.second != -1)
			{
				Threat t = Threat(i + 1, building, building[i], building[i]->getGrid()[tLoc.first][tLoc.second]);
				t.SetMoveCounter(moveCounter);
				threats.push_back(t);
			}
		}
	}

	// promises and futures to ensure Person threads are started
	prms.resize(people.size());
	futures.resize(people.size());
	prmsThreat.resize(threats.size());
	futuresThreat.resize(threats.size());
	std::vector<std::thread> thrds;
	for (int i = 0; i < people.size(); i++)
	{
		thrds.emplace_back(std::move(people[i].StartSim(std::move(prms[i]))));
		futures[i] = prms[i].get_future();
		std::cout << futures[i].get();
	}

	for (int i = 0; i < threats.size(); i++)
	{
		thrds.emplace_back(std::move(threats[i].StartSim(std::move(prmsThreat[i]))));
		futuresThreat[i] = prmsThreat[i].get_future();
		std::cout << futuresThreat[i].get();
	}

	std::for_each(thrds.begin(), thrds.end(), [](std::thread& t){
		t.join();
		});

}

