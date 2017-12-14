#pragma once
#include <string>
#include <sstream>

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

	std::string MakeString(std::string separator) {
		std::stringstream ss;
		//header
		ss << "Setting" << separator << "Value" << "\n";
		
		//data
		ss << "Reuse CommandBuffers"	<< separator << force_string(reuseCommandBuffers)		<< "\n";
		ss << "Probe Interval"			<< separator << force_string(probeInterval)				<< "\n";
		ss << "Seconds"					<< separator << force_string(seconds)					<< "\n";
		ss << "Export CSV"				<< separator << force_string(exportCsv)					<< "\n";
		ss << "Pipeline Statistics"		<< separator << force_string(pipelineStatistics)		<< "\n";
		ss << "Open Hardware Monitor"	<< separator << force_string(openHardwareMonitorData)	<< "\n";
		ss << "Rotate Cubes"			<< separator << force_string(rotateCubes)				<< "\n";
		ss << "Draw Thread Count"		<< separator << force_string(drawThreadCount)			<< "\n";
		ss << "Cube Dimension"			<< separator << force_string(cubeDimension)				<< "\n";
		ss << "Cube Padding"			<< separator << force_string(cubePadding)				<< "\n";

		return ss.str();
	}

private:
	TestConfiguration() {};
	static TestConfiguration instance;

	template<typename T>
	std::string force_string(T arg)
	{
		std::stringstream ss;
		ss << arg;
		return ss.str();
	}

	template<>
	std::string force_string(bool arg) {
		return arg ? "true" : "false";
	}
};