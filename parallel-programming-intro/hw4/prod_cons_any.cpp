#include<pthread.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include<string>

using namespace std;

int n;
pthread_mutex_t mutex;
struct
{
	string message;
	int target = -1;
}messageBox;


void* hello(void* rank)
{
	long myRank = (long)rank;
	bool haveSent = false, haveReceived = false;
	while (true)
	{
		pthread_mutex_lock(&mutex);
		if (!haveSent && messageBox.target == -1)
		{
			messageBox.message = "Hello from thread " + to_string(myRank);
			messageBox.target = (myRank + 1) % n;
            haveSent = true;
		}
		if (!haveReceived && messageBox.target == myRank)
		{
			cout << "Thread " << myRank << " gets " << messageBox.message << endl;
			messageBox.target = -1;
            haveReceived = true;
		}
		pthread_mutex_unlock(&mutex);
		if (haveSent && haveReceived)
		{
			break;
		}
	}
	return nullptr;
}

int main(int argc, char** argv)
{
	n = atoi(argv[1]);
	pthread_t* threads = new pthread_t[n];
	pthread_mutex_init(&mutex, nullptr);
	for (long i = 0; i < n; i++)
	{
		pthread_create(&threads[i], nullptr, hello, (void*)i);
	}
	for (long i = 0; i < n; i++)
	{
		pthread_join(threads[i], nullptr);
	}
	pthread_mutex_destroy(&mutex);
	return 0;
}