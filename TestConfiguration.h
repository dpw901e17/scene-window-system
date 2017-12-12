#pragma once

struct TestConfiguration
{
	bool reuseCommandBuffers = true;
	size_t probeInterval = 0;	//make probes every frame. Interval is given in ms.
	size_t seconds = 0;	//run until program is closed by user
	bool exportCsv = false;
	bool pipelineStatistics = false;
	bool openHardwareMonitorData = false;
	bool rotateCubes = false;
	size_t drawThreadCount = 1;
	size_t cubeDimension = 2;
	int cubePadding = 1;

	//TODO: use better pattern than singleton?
	static TestConfiguration& GetInstance() 
	{ 
		return instance; 
	}

private:
	TestConfiguration() {};
	static TestConfiguration instance;
};