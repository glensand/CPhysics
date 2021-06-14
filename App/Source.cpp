#include <iostream>
#include <vector>

#include "RuntimePlotExample.h"
#include "RuntimeMultiPlotExample.h"
#include "PlotterTest/SinglePlotTest.h"
#include "PlotterTest/DoubleRowTestBase.h"
#include "PlotterTest/DoubleDoubleTest.h"
//#include "ViveExploration/ViveExplore.h"

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
		std::make_shared<RuntimePlotExample>(),
		std::make_shared<RuntimeMultiPlotExample>(),
		std::make_shared<SinglePlotTest1>(),
		std::make_shared<SinglePlotTest2>(),
		std::make_shared<SinglePlotTest3>(),
		std::make_shared<SinglePlotTest4>(),
	    std::make_shared<DoubleRowTest1>(),
		std::make_shared<DoubleRowTest2>(),
		std::make_shared<DoubleRowTest3>(),
		std::make_shared<DoubleRowTest4>(),
	    std::make_shared<DoubleDoubleTest1>(),
		std::make_shared<DoubleDoubleTest2>(),
		std::make_shared<DoubleDoubleTest3>(),
		std::make_shared<DoubleDoubleTest4>(),
		//std::make_shared<ViveExplore>(PlotStyle::AdaptiveRange),
		//std::make_shared<ViveExplore>(PlotStyle::AllTimeFixed),
		//std::make_shared<ViveExplore>(PlotStyle::MinMaxFixed),
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
	}
}
