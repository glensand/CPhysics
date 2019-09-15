#include "Task2.h"
#include "Task3.h"
#include "Task4.h"

int main()
{
	//const auto task = std::make_shared<Task2>();
	const auto task = std::make_shared<Task3>();
	//const auto task = std::make_shared<Task4>();

	task->Run();
	
	return 0;
}