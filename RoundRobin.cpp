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
	int n = processes.size();
	queue<int> readyQueue;
	int currentTime = 0;
	int completedCount = 0;
	vector<bool> inQueue(n, false);
	for (int i = 0; i< n; i++) {
		if (processes[i].arrivalTime <= currentTime) {
			readyQueue.push(i);
			inQueue[i] = true;
		}
	}
	cout << "Mo phong Round Robin" << endl;
	cout << "time quantum = " << timeQuantum << endl;
	displayReadyQueue(readyQueue, processes);
	while (completedCount < n) {
		if (readyQueue.empty()) {
			int nextArrivalTime = -1;
			for (int i = 0; i<n; i++) {
				if (processes[i].remainingTime > 0 && processes[i].arrivalTime > currentTime) {
					if (nextArrivalTime == -1 || processes[i].arrivalTime < nextArrivalTime) {
						nextArrivalTime = processes[i].arrivalTime;
					}
				}
			}
			if (nextArrivalTime == -1) {
				break;
			}
			cout << "\n CPU idle tu " << currentTime << " den " << nextArrivalTime << endl;
			history.push_back({"IDLE", currentTime, nextArrivalTime});
			currentTime = nextArrivalTime;
			for (int i = 0; i < n; i++) {
				if (!inQueue[i] && processes[i].arrivalTime <= currentTime) {
					readyQueue.push(i);
					inQueue[i] = true;
				}
			}
			displayReadyQueue(readyQueue, processes);
			continue;
		}
		int idx = readyQueue.front();
		readyQueue.pop();
		if (processes[idx].firstRunTime == NOT_STARTED) {
			processes[idx].firstRunTime = currentTime;
		}
		int runTime = min(timeQuantum, processes[idx].remainingTime);
		int startTime = currentTime;
		currentTime += runTime;
		processes[idx].remainingTime -= runTime;
		history.push_back({processes[idx].id, startTime, currentTime});
		cout << "\nCPU chay tien trinh : " << processes[idx].id << endl;
		cout << "Thoi gian : " << startTime << " -> " << currentTime << endl;
		cout << "Thoi gian CPU da chay : " << runTime << endl;
		cout << "Thoi gian con lai cua " << processes[idx].id << ": " << processes[idx].remainingTime << endl;
		for (int i = 0; i < n; i++) {
			if (!inQueue[i] && processes[i].arrivalTime <= currentTime) {
				readyQueue.push(i);
				inQueue[i]= true;
			}
		}
		if (processes[idx].remainingTime > 0) {
			readyQueue.push(idx);
		}
		else {
			processes[idx].completionTime = currentTime;
			completedCount++;
			cout << processes[idx].id << "da hoan thanh tai thoi diem " << currentTime << endl;
		}
		displayReadyQueue(readyQueue, processes);
	}
	return history;
}