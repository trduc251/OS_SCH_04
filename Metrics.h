#pragma once
#include "Process.h"
#include <vector>
using namespace std;

struct AverageMetrics {
	double averageWT;
	double averageTAT;
	double averageRT;
};

void calculateMetrics(vector<Process>& processes);
AverageMetrics calculateAverageMetrics(const vector<Process>& processes);

void printAverageMetrics(const AverageMetrics& avg);
