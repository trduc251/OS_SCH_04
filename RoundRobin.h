#pragma once
#include"Process.h"
#include<string>
#include<vector>
using namespace std;
struct ExecutionSeg
{
	string processID;
	int startTime;
	int endTime;
};
vector<ExecutionSeg>
runRoundRobin(vector<Process>& processes, int timeQuantum);

