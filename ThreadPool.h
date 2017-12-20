#pragma once
#include <mutex>
#include <queue>
#include <thread>

#define TEST_THREAD_JOB_WAIT_TIME 5

class ThreadHandler
{
private:
	std::thread* thread;
public:
	//TODO: make diz private?
	volatile bool isWorking = false;
	
	ThreadHandler(std::thread* thread) : thread(thread) {};
	ThreadHandler() = default;

	~ThreadHandler() {
		delete thread;
	}

	void Detach()
	{
		thread->detach();
	}

	void SetThread(std::thread* t) {
		thread = t;
	}
};

template<typename ArgT>
class ThreadJob
{
private:
	void (*job)(ArgT&);
	ArgT arg;	
public:
	ThreadJob<ArgT>(void (*job)(ArgT&), ArgT& arg) : job(job), arg(arg) {}

	void Execute() {
		job(arg);
	}
};

template<typename ArgT>
struct ThreadArg
{
	std::queue<ThreadJob<ArgT>>& jobs;
	std::mutex* joblock;
	bool& keepThreadsAlive = true;
	volatile bool& isWorking;
	volatile size_t& terminatedThreads = 0;
};

template<typename ArgT>
class ThreadPool
{
private:
	std::vector<ThreadHandler*> threadHandlers;
	std::queue<ThreadJob<ArgT>> jobs;
	std::mutex joblock;
	bool keepThreadsAlive = true;
	volatile size_t terminatedThreads = 0;

public:
	ThreadPool<ArgT>(size_t threadCount) {

		threadHandlers.resize(threadCount);
		for (auto i = 0; i < threadCount; ++i) {

			//temp handler (we don't have the thread yet)
			auto threadHandler = new ThreadHandler(nullptr);

			//create the thread (with a member from threadHandler as an argument)
			ThreadArg<ArgT> arg = { jobs, &joblock, keepThreadsAlive, threadHandler->isWorking, terminatedThreads };
			std::thread* thread = new std::thread(ThreadMain<ArgT>, arg);

			threadHandler->SetThread(thread);

			threadHandlers[i] = threadHandler;
		}


		for (auto& thread : threadHandlers) {
			thread->Detach();
		}
	}
	
	~ThreadPool() {
		Stop();

		//make sure all spawned threads have terminated before detructing fields (as spawned threads have references to them)
		while (terminatedThreads < threadHandlers.size()) {
			std::this_thread::sleep_for(std::chrono::milliseconds(TEST_THREAD_JOB_WAIT_TIME));
		}

		for (auto& handler : threadHandlers) {
			delete handler;
		}
	}

	void AddThreadJob(ThreadJob<ArgT> job) {
		joblock.lock();
		jobs.push(job);
		joblock.unlock();
	}

	bool Idle()
	{
		joblock.lock();
		bool noJobs = jobs.empty();
		joblock.unlock();

		bool threadsDone = noJobs;
		for (auto& handler : threadHandlers) {
			threadsDone = threadsDone && !handler->isWorking;
		}
		
		return threadsDone;
	}

	void Stop()
	{
		keepThreadsAlive = false;
	}
};

template<typename ArgT>
void ThreadMain(ThreadArg<ArgT>& arg) {
	auto& jobs = arg.jobs;
	auto& joblock = *arg.joblock;
	auto& keepAlive = arg.keepThreadsAlive;
	auto& terminatedThreads = arg.terminatedThreads;

	while (keepAlive) {
		joblock.lock();
		if (jobs.size() > 0) {
			auto threadJob = jobs.front();
			jobs.pop();
			joblock.unlock();

			arg.isWorking = true;
			threadJob.Execute();
			arg.isWorking = false;
		}
		else {
			joblock.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(TEST_THREAD_JOB_WAIT_TIME));
		}
	}

	++terminatedThreads;
}