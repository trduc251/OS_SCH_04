#include "RoundRobin.h"
#include<queue>
#include<algorithm>
#include<iostream>
using namespace std;
void displayReadyQueue(queue<int> readyQueue,
	const vector<Process>& processes) {
	cout << "ready queue: ";
	if (readyQueue.empty()) {
		cout << "rong";
	}
	else {
		while (!readyQueue.empty()) {
			int idx = readyQueue.front();
			readyQueue.pop();
			cout << processes[idx].id;
			if (!readyQueue.empty()) {
				cout << " -> ";
			}
		}
	}
	cout << endl;
}
vector<ExecutionSeg>
runRoundRobin(vector<Process>& processes, int timeQuantum) {
	vector<ExecutionSeg> history;
	if (processes.empty() || timeQuantum <= 0){
		return history;
	}
	resetProcesses(processes);
	sortByArrivalTime(processes);
}