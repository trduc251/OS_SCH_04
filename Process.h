#pragma once  
#include <string>
#include <vector>

using namespace std;

const int MAX_PROCESSES = 100;
const int NOT_STARTED = -1;


struct Process {

    string id;
    int arrivalTime = 0;
    int burstTime = 0;


    int remainingTime = 0;
    int firstRunTime = -1;

    int completionTime = 0;
    int turnaroundTime = 0;
    int waitingTime = 0;
    int responseTime = 0;
};
int inputNumberOfProcesses();
Process inputProcess(int index, const vector<Process>& existingProcesses);
vector<Process> inputProcessList();
Process createProcess(const string& id, int arrivalTime, int burstTime);
void resetProcesses(vector<Process>& processes);
void sortByArrivalTime(vector<Process>& processes);
void printProcessList(const vector<Process>& processes);