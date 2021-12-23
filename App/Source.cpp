#include <iostream>
#include <vector>

#include "ViveExploration/ViveExplore.h"
#include "ViveExploration/ViveExploreFilter.h"
#include "PolhemusExplore/PolhemusExplore.h"

namespace
{
void help()
{
	std::cout << std::endl << 
		"//==============================================================================" << std::endl;
	std::cout << "0 - exit" << std::endl;
	std::cout << "task << ";
}
}

int main()
{
	// tasks
	const std::vector<std::shared_ptr<ITask>> tasks
	{	nullptr, // Task 1
		std::make_shared<ViveExploreFilter>(),
		std::make_shared<ViveExplore>(PlotStyle::AdaptiveRange),
		std::make_shared<ViveExplore>(PlotStyle::AllTimeFixed),
		std::make_shared<ViveExplore>(PlotStyle::MinMaxFixed),
		std::make_shared<ViveExplore>(PlotStyle::SlippingAverage),
		std::make_shared<PolhemusExplore>(),
	};
	
	for(;;)
	{
		help();
		
		size_t task;
		std::cin >> task;
		std::cout << std::endl;
		
		if (task == 0) 
			break;
		if (task > tasks.size() || tasks[task - 1] == nullptr) 
			continue;
		
		tasks[task - 1]->Run();
		tasks[task - 1]->Clear();
	}
}
