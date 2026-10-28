#include "Display.h"
#include <iostream>
#include <iomanip>
using namespace std;

void displayGanttChart(const vector<ExecutionSeg>& history)
{
	cout << "==========Gantt Chart ==========" << endl;
	if (history.empty())
	{
		cout << "Khong co du lieu de hien thi " << endl;
	}
	cout << history[0].startTime;
	for (const ExecutionSeg& seg : history)
	{
		cout << " | " << seg.processID << " | " << seg.endTime;
	}
};
void displayResults(const vector<Process>& processes)
{
	cout << "==========Ket Qua==========" << endl;
	cout << left << setw(10) << "PID" << setw(8) << "AT" << setw(8) << "BT" << setw(8) << "CT" << setw(8) << "TAT" << setw(8) << "WT" << setw(8) << "RT" << endl;
	double sumWT = 0;
	double sumTAT = 0;
	double sumRT = 0;
	for (const Process& p : processes)
	{
		cout << left << setw(10) << p.id << setw(8) << p.arrivalTime << setw(8) << p.burstTime << setw(8) << p.completionTime << setw(8) << p.turnaroundTime << setw(8) << p.waitingTime << setw(8) << p.responseTime << "\n";
	
		sumWT += p.waitingTime; 
		sumTAT += p.turnaroundTime;
		sumRT += p.responseTime;

	}
	if (!processes.empty())
	{
		cout << fixed << setprecision(2);	
		cout << "Waiting Time Trung Binh: " << sumWT / processes.size() << endl;
		cout << "Responese Time Trung Binh: " << sumRT / processes.size() << endl;
		cout << "Turnaround Time Trung Binh: " << sumTAT / processes.size() << endl;

	}

}
int countContextSwitches(const vector<ExecutionSeg>& history)
{
	int count = 0;
	string previousProcess = "";
	for (const ExecutionSeg& seg : history)
	{
		if (seg.processID == "IDLE")
		{
			continue;

		}
		if (previousProcess != "" && seg.processID != previousProcess)
		{
			count++;

		}
		previousProcess = seg.processID;
	}
	return count;

	
}
void displayAll(const vector<ExecutionSeg>& history, const vector<Process>& processes)
{
	displayGanttChart(history);
	displayResults(processes);
	cout << "\nContext Switch: " << countContextSwitches(history) << endl;
}
