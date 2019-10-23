#include "Task2.h"
#include "Task3.h"
#include "Task4.h"
#include "Task5.h"
#include "Task6.h"
#include "task7.h"
#include "Task8.h"
#include "Task13.h"
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
	const auto task = std::make_unique<Task13>();
	
	task->Run();
	
	return 0;
}