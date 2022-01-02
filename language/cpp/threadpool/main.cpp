#include "print.h"
#include "thread_pool.h"

int main()
{
	ThreadPool task_pool(9);

	task_pool.Abort();
	return 0;
}