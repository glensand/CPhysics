#include "Task2.h"
#include "Task3.h"
#include "Task4.h"
#include "Task5.h"
#include "Task6.h"
#include "task7.h"
#include "Task8.h"
#include "Task9.h"
#include "Task10.h"
#include "Task11.h"
#include "Task12.h"
#include "Task13.h"
#include  "Steering.h"
#include "bigtask17.h"

#include "CVPlotExamples.h"

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
		std::make_shared<Task2>(),
		std::make_shared<Task3>(),
		std::make_shared<Task4>(),
		std::make_shared<Task5>(),
		std::make_shared<Task6>(),
		std::make_shared<Task7>(),
		std::make_shared<Task8>(),
		std::make_shared<Task9>(),
		std::make_shared<Task10>(),
		std::make_shared<Task11>(),
		std::make_shared<Task12>(),
		std::make_shared<Task13>(),
		std::make_shared<bigtask17>() // executed with number 14
	};
	
	for(;;)
	{
		help();
		
		size_t task;
		std::cin >> task;
		std::cout << std::endl;
		
		if (task == 0) break;
		if (task > tasks.size() || tasks[task - 1] == nullptr) continue;
		
		tasks[task - 1]->Run();
	}
}
