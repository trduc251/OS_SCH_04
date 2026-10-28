#include "Process.h"
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>

using namespace std;

static int readInteger(const string& prompt, int minValue, int maxValue) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.eof()) exit(1);

        if (cin.fail()) {
            cin.clear();
            cout << "  [Loi] Vui long nhap mot so nguyen.\n";
        }
        else if (value < minValue || value > maxValue) {
            cout << "  [Loi] Gia tri phai tu " << minValue << " den " << maxValue << ".\n";
        }
        else {
            cin.ignore(1000, '\n');
            return value;
        }
        cin.ignore(1000, '\n');
    }
}

static bool isIdExisted(const string& id, const vector<Process>& processes) {
    for (const Process& process : processes) {
        if (process.id == id) return true;
    }
    return false;
}

int inputNumberOfProcesses() {
    return readInteger("Nhap so luong tien trinh: ", 1, MAX_PROCESSES);
}

Process inputProcess(int index, const vector<Process>& existingProcesses) {
    cout << "\n Tien trinh thu " << index << " \n";

    string id;
    while (true) {
        cout << "Ma tien trinh (vi du P" << index << "): ";
        cin >> id;
        if (cin.eof()) exit(1);
        cin.ignore(1000, '\n');

        if (!isIdExisted(id, existingProcesses)) break;
        cout << "  [Loi] Ma '" << id << "' da ton tai, hay nhap ma khac.\n";
    }

    int arrivalTime = readInteger("Arrival Time (AT): ", 0, 1000000);
    int burstTime = readInteger("CPU Burst (BT): ", 1, 1000000);

    return createProcess(id, arrivalTime, burstTime);
}

vector<Process> inputProcessList() {
    int numberOfProcesses = inputNumberOfProcesses();

    vector<Process> processes;
    for (int i = 1; i <= numberOfProcesses; i++) {
        processes.push_back(inputProcess(i, processes));
    }
    return processes;
}

Process createProcess(const string& id, int arrivalTime, int burstTime) {
    Process process;
    process.id = id;
    process.arrivalTime = arrivalTime;
    process.burstTime = burstTime;
    process.remainingTime = burstTime;
    process.firstRunTime = NOT_STARTED;
    process.completionTime = 0;
    process.turnaroundTime = 0;
    process.waitingTime = 0;
    process.responseTime = 0;
    return process;
}

void resetProcesses(vector<Process>& processes) {
    for (Process& process : processes) {
        process = createProcess(process.id, process.arrivalTime, process.burstTime);
    }
}

void sortByArrivalTime(vector<Process>& processes) {
    stable_sort(processes.begin(), processes.end(),
        [](const Process& a, const Process& b) {
            return a.arrivalTime < b.arrivalTime;
        });
}

void printProcessList(const vector<Process>& processes) {
    cout << "\n DANH SACH TIEN TRINH \n";
    cout << left << setw(10) << "Ma TT" << setw(15) << "Arrival Time" << "CPU Burst\n";
    cout << string(35, '-') << "\n";

    for (const Process& process : processes) {
        cout << left << setw(10) << process.id
            << setw(15) << process.arrivalTime
            << process.burstTime << "\n";
    }
}