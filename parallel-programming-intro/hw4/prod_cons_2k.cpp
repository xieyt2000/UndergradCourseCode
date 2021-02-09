#include<pthread.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include<string>

using namespace std;

pthread_mutex_t mutex;
struct
{
	string message;
	bool messageAvailable = false;
}messageBox;


void* hello(void* rank)
{
	long myRank = (long)rank;
	while (true)
	{
		pthread_mutex_lock(&mutex);
		if (myRank % 2 ==1)
		{
			if (messageBox.messageAvailable)
			{
				cout << "Thread " << myRank << " gets " << messageBox.message << endl;
				messageBox.messageAvailable = false;
				pthread_mutex_unlock(&mutex);
				break;
			}
		}
		else
		{
            if(!messageBox.messageAvailable)
			{
                messageBox.message = "Hello from thread " + to_string(myRank);
			    messageBox.messageAvailable = true;
			    pthread_mutex_unlock(&mutex);
			    break;
            }
		}
        pthread_mutex_unlock(&mutex);
	}
	return nullptr;
}

int main(int argc, char** argv)
{
	int n = atoi(argv[1]);
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
}