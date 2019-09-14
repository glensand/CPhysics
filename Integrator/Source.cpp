#include "Task4.h"
#include "Task3.h"

int main()
{
	const auto task = std::make_shared<Task3>();
	//const auto task = std::make_shared<Task4>();

	task->Run();
	
	return 0;
}