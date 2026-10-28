#pragma once
#include "Process.h"
#include "Roundrobin.h"
#include <vector>
using namespace std;
void displayGanttChart(const vector<ExecutionSeg>& history);
void displayResults(const vector<Process>& processes);
int countContextSwitches(const vector<ExecutionSeg>& history);
void displayAll(const vector<ExecutionSeg>& history, const vector <Process>& processes);
