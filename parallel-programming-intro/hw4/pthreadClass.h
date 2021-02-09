#pragma once
#include<pthread.h>
class Mutex
{
	
public:
	pthread_mutex_t mutex;
	Mutex()
	{
		pthread_mutex_init(&mutex, nullptr);
	}
	void lock()
	{
		pthread_mutex_lock(&mutex);
	}
	void unlock()
	{
		pthread_mutex_unlock(&mutex);
	}
	~Mutex()
	{
		pthread_mutex_destroy(&mutex);
	}
};

class Cond
{
public:
	pthread_cond_t cond;
	Cond()
	{
		pthread_cond_init(&cond, nullptr);
	}
	int wait(Mutex& condMutex)
	{
		return pthread_cond_wait(&cond, &(condMutex.mutex));
	}
	void signal()
	{
		pthread_cond_signal(&cond);
	}
	void bcast()
	{
		pthread_cond_broadcast(&cond);
	}
	~Cond()
	{
		pthread_cond_destroy(&cond);
	}
};