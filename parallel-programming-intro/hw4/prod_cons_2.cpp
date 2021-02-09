#include<pthread.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>

using namespace std;

const long COSUMER = 0;
const long PRODUCER = 1;
pthread_mutex_t mutex;
struct
{
	char message[100];
	bool messageAvailable = false;
}messageBox;


void* hello(void* rank)
{
	long myRank = (long)rank;
	while (true)
	{
		pthread_mutex_lock(&mutex);
		if (myRank == COSUMER)
		{
			if (messageBox.messageAvailable)
			{
				cout << messageBox.message << endl;
				pthread_mutex_unlock(&mutex);
				break;
			}
		}
		else
		{
			strcpy(messageBox.message, "Hello from producer");
			messageBox.messageAvailable = true;
			pthread_mutex_unlock(&mutex);
			break;
		}
    pthread_mutex_unlock(&mutex);
	}
	return nullptr;
}

int main(int argc, char** argv)
{
	int n = 2;
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