#define HAVE_STRUCT_TIMESPEC
#include<pthread.h>
#include<cstdlib>
#include<iostream>
#include<ctime>
#include<thread>
#include<chrono>
#include<list>
#include<algorithm>
#include<vector>
#include<atomic>
#include"pthreadClass.h"

using namespace std;

int threadCnt, taskCount;
list<int> serialList, parallelList;
Cond condVar;
Mutex mutex, listMutex;
atomic<bool> noMoreTask;
struct Task
{
	int type;	//0: insert; 1: delete; 2:member; 3:print
	int targetVal;
};
struct queue
{
	vector<Task> taskVec;
	int headIndex = 0;
	void enqueue(const Task& task)
	{
		taskVec.push_back(task);
	}
	bool empty()
	{
		return taskVec.size() == headIndex;
	}
	Task dequeue()
	{
		headIndex++;
		return taskVec[headIndex - 1];
	}
};
queue taskQueue;

Task genTask()
{
	Task task;
	task.targetVal = rand() % 10;
	int random = rand();
	if (random % 15 < 4)
	{
		task.type = 0;
		cout << "Insert " << task.targetVal << endl;
	}
	else if (random % 15 < 6)
	{
		task.type = 1;
		cout << "Delete " << task.targetVal << endl;
	}
	else if (random % 15 < 14)
	{
		task.type = 2;
		cout << "Member " << task.targetVal << endl;
	}
	else
	{
		task.type = 3;
		cout << "Print" << endl;
	}
	return task;
}

void execTask(list<int>& ls, const Task& task)
{
	listMutex.lock();
	int value = task.targetVal;
	switch (task.type)
	{
	case 0:
	{
		auto pos = lower_bound(ls.begin(), ls.end(), value);
		ls.insert(pos, value);
		cout << value << " inserted." << endl;
		break;
	}
	case 1:
	{
		auto pos = find(ls.begin(), ls.end(), value);
		if (pos == ls.end())
		{
			cout << value << " not in the list. Can't delete." << endl;
		}
		else
		{
			ls.erase(pos);
			cout << value << " deleted." << endl;
		}
		break;
	}
	case 2:
	{
		auto pos = find(ls.begin(), ls.end(), value);
		if (pos == ls.end())
		{
			cout << value << " not in the list" << endl;
		}
		else
		{
			cout << value << " in the list." << endl;
		}
		break;
	}
	case 3:
	{
		for (int i : ls)
		{
			cout << i << " ";
		}
		cout << endl;
		break;
	}
	default:
		break;
	}
	listMutex.unlock();
}

void* parallelOpr(void* rank)
{
	long myRank = (long)rank;
	while (true)
	{
		mutex.lock();
		while (taskQueue.empty() && !noMoreTask)
		{
			while(condVar.wait(mutex) != 0);
		}
		if (taskQueue.empty())
		{
			mutex.unlock();
			break;
		}
		execTask(parallelList, taskQueue.dequeue());
		mutex.unlock();
		this_thread::sleep_for(chrono::seconds(1));
	}
	return nullptr;
}

void serialOpr(const Task& task)
{
	execTask(serialList, task);
}

int main(int argc, char** argv)
{
	srand(time(nullptr));
	if (argc != 3)
	{
		return 1;
	}
	threadCnt = atoi(argv[1]);
	taskCount = atoi(argv[2]);
	noMoreTask = false;
	pthread_t* threads = new pthread_t[threadCnt];
	for (long i = 0; i < threadCnt; i++)
	{
		pthread_create(&threads[i], nullptr, parallelOpr, (void*)i);
	}
	for (int i = 0; i < taskCount; i++)
	{
		mutex.lock();
		taskQueue.enqueue(genTask());
		condVar.signal();
		mutex.unlock();
		this_thread::sleep_for(chrono::milliseconds(100));
	}
	cout << "finish" << endl;
	noMoreTask = true;
	condVar.bcast();
	for (long i = 0; i < threadCnt; i++)
	{
		pthread_join(threads[i], nullptr);
	}

	//serial
	for (auto i : taskQueue.taskVec)
	{
		serialOpr(i);
	}
	//check result
	Task print; print.type = 3;
	execTask(serialList, print);
	execTask(parallelList, print);
	if (serialList == parallelList)
	{
		cout << "Correct!" << endl;
	}
	else
	{
		cout << "Wrong" << endl;
	}
	return 0;
}