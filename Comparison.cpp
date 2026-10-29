#include "Comparison.h"
#include "RoundRobin.h"
#include "Metrics.h"
#include <iostream>
#include <iomanip>

using namespace std;

const double CS_COST = 0.1;

void Comparison::runAllTestCases() {
	vector<int> quantums = { 1,2,4 };

	vector<pair<string, vector<Process>>> testCases = {
		{ "1. Chi co 1 tien trinh",{ createProcess("P1",0,6) } },
		{ "2. Tien trinh den muon",{ createProcess("P1",0,5), createProcess("P2",2,4),createProcess("P3",4,2) } },
		{ "3. CPU Burst bang nhau",{ createProcess("P1",0,4), createProcess("P2",0,4), createProcess("P3",0,4) } }
	};

	cout << "\n BANG SO SANH HIEU SUAT ROUND ROBIN (CS Cost = " << CS_COST << ")\n";

	for (const auto& tc : testCases) {
		cout << "\n[Test Case] " << tc.first << "\n";
		cout << left << setw(10) << "Quantum" << setw(12) << "Avg WT" << setw(12) << "Avg RT" << setw(10) << "CS" << setw(12) << "Overhead" << "\n";
		cout << "------------------------------------------------------------\n";

		for (int q : quantums) {
			vector<Process> procs = tc.second;
			vector<ExecutionSeg> history = runRoundRobin(procs, q);
			calculateMetrics(procs);
			int csCount = 0;
			string lastProc = "";
			for (const auto& seg : history) {
				if (seg.processID != "IDLE") {
					if (!lastProc.empty() && lastProc != seg.processID) csCount++;
					lastProc = seg.processID;
				}
			}
			AverageMetrics avg = calculateAverageMetrics(procs);
			cout << left << setw(10) << q
				<< setw(12) << fixed << setprecision(2) << avg.averageWT
				<< setw(12) << fixed << setprecision(2) << avg.averageRT
				<< setw(10) << csCount
				<< setw(12) << fixed << setprecision(2) << csCount * CS_COST << "/n";
		}
	}
	cout << " \n=== NHAN XET KHAI NIEM HE DIEU HANH ===\n";
	cout << "1. Quantum nho (Q=1): RT tot nhat (phan hoi nhanh), nhung Context Switch nhieu -> Overhead cao.\n";
	cout << "2. Quantum lon (Q=4): Giam Context Switch & Overhead, nhung RT tang; khi Q rat lon RR -> FCFS.\n";
	cout << "3. Ketluan : Can chon Quantum phu hop de can bang giua thoi gian phan hoi va chi phi Ovehead.\n";

}
