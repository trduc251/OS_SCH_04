#include "Metrics.h"

void calculatemetrics(vector<Process>& processes) {
	for (Process& p : processes)
	{
		p.turnaroundTime = p.completionTime - p.arrivalTime;
		p.waitingTime = p.turnaroundTime - p.burstTime;
		p.responseTime = p.firstRunTime - p.arrivalTime;
	}
}

double averageWT(const vector<Process>& processes) {
	if (processes.empty())
		return 0;
	double sum = 0;
	for (const Process& p : processes) {
		sum += p.waitingTime;
	}
	return sum / processes.size();
}

double averageRT(const vector<Process>& processes) {
	if (processes.empty())
		return 0;
	double sum = 0;
	for (const Process& p : processes)
	{
		sum += p.responseTime;
	}
	return sum / processes.size();
}
double averageTAT(const vector<Process>& processes) {
	if (processes.empty())
		return 0;
	double sum = 0;
	for (const Process& p : processes) {
		sum += p.turnaroundTime;
	}
	return sum / processes.size();
}
AverageMetrics calculateAverageMetrics(const vector<Process>& processes) {
	AverageMetrics avg;
	avg.averageWT = averageWT(processes);
	avg.averageTAT =averageTAT(processes);
	avg.averageRT = averageRT(processes);
	return avg;
}