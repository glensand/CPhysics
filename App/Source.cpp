#include "Task2.h"
#include "Task3.h"
#include "Task4.h"
#include "Task5.h"
#include "Task6.h"
#include "task7.h"
#include "Task8.h"
#include "Task9.h"
#include "Task12.h"
#include "Task13.h"
#include  "Steering.h"

#include "CVPlotExamples.h"


int main()
{
	//const auto task = std::make_unique<Task2>();
	//const auto task = std::make_unique<Task3>();
	//const auto task = std::make_unique<Task4>();
	//const auto task = std::make_unique<Task5>();
	//const auto task = std::make_unique<Task6>();
	//const auto task = std::make_unique<Task7>();
	//const auto task = std::make_unique<CVPlotExamples>();
	//const auto task = std::make_unique<Task8>();
	//const auto task = std::make_unique<Task9>();
	const auto task = std::make_unique<Task12>();
	//const auto task = std::make_unique<Task13>();
	
	//const auto task = std::make_unique<Steering>();

	task->Run();
	
	return 0;
}
