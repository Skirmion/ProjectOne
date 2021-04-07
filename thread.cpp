#include <thread>
#include <iostream> 
#include <ctime>
#include <mutex>

void F(int *i, std::mutex *m)
{
	while (*i < 10000000)
	{
		m->lock();
		*i += 1;
		m->unlock();
	}
}

void S(int *i, unsigned int *start_time, std::mutex* m)
{
	while (*i < 10000000)
	{
		m->lock();
		*i += 1;
		///std::cout << *i << std::endl;
		m->unlock();
	}

	unsigned int end_time1 = clock();
	unsigned int search_time1 = end_time1 - *start_time;

	std::cout << *i << std::endl;
	std::cout << "i:" << search_time1 << std::endl;
}

void A(int* g, unsigned int* start_time)
{
	while (*g < 10000000)
	{
		*g += 1;
		///std::cout << *g << std::endl;
	}

	unsigned int end_time2 = clock();
	unsigned int search_time2 = end_time2 - *start_time;

	std::cout << *g << std::endl;
	std::cout << "g:" << search_time2 << std::endl;

}


int main()
{
	unsigned int start_time = clock();

	std::mutex m;

	int i = 0;
	int g = 0;

	std::thread tf(F, &i, &m);
	std::thread ts(S, &i, &start_time, &m);
	std::thread ta(A, &g, &start_time);

	///std::atomic<int> x;
	
	ta.join();
	tf.join();
	ts.join();
}
