#include "Process.h"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unordered_set>
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
vector<Process> loadProcessesFromFile(const string& filename) {
    ifstream file(filename);
    vector<Process> processes;

    if (!file.is_open()) {
        cout << "  [Loi] Khong the mo file: " << filename << "\n";
        return processes;
    }

    processes.reserve(MAX_PROCESSES);
    unordered_set<string> seenIds;
    seenIds.reserve(MAX_PROCESSES);
    string line;
    int skippedCount = 0;

    while (getline(file, line)) {
        size_t firstChar = line.find_first_not_of(" \t\r\n");
        if (firstChar == string::npos || line[firstChar] == '#' ||
            (line[firstChar] == '/' && firstChar + 1 < line.size() && line[firstChar + 1] == '/')) {
            continue;
        }
        for (char& c : line) {
            if (c == ',') c = ' ';
        }
        stringstream ss(line);
        string id;
        int arrivalTime, burstTime;

        if (processes.empty() && skippedCount == 0) {
            stringstream checkHeader(line);
            int declaredCount;
            string extra;
            if ((checkHeader >> declaredCount) && !(checkHeader >> extra)) {
                if (declaredCount > 0) {
                    int cap = min(declaredCount, MAX_PROCESSES);
                    processes.reserve(cap);
                    seenIds.reserve(cap);
                }
                continue;
            }
        }

        if (!(ss >> id >> arrivalTime >> burstTime)) {
            skippedCount++;
            continue;
        }

        if (arrivalTime < 0 || burstTime < 1) {
            skippedCount++;
            continue;
        }

        if (seenIds.find(id) != seenIds.end()) {
            skippedCount++;
            continue;
        }

        seenIds.insert(id);
        processes.push_back(createProcess(id, arrivalTime, burstTime));

        if ((int)processes.size() >= MAX_PROCESSES) {
            cout << "  [Canh bao] Da dat gioi han toi da " << MAX_PROCESSES << " tien trinh.\n";
            break;
        }
    }

    file.close();

    cout << "\n Da doc thanh cong " << processes.size() << " tien trinh tu file '" << filename << "'.\n";
    if (skippedCount > 0) {
        cout << "  [Canh bao] Da bo qua " << skippedCount << " dong loi hoac trung ma.\n";
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