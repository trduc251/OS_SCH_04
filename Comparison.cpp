#include "Comparison.h"
#include "RoundRobin.h"
#include "Metrics.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <utility>
#include <limits>
#include <sstream>

using namespace std;
const double CS_COST = 0.1;
const size_t MAX_DISPLAY_PROCESSES = 30000;
static int readPositiveInt(const string& prompt) {
	int value;
	while (true) {
		cout << prompt;
		if (cin >> value && value > 0) {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return value;
		}
		cout << "Gia tri khong hop le! Vui long nhap so nguyen duong.\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}
static int chooseSource() {
	while (true) {
		cout << "Chon nguon du lieu:\n";
		cout << "  1. Nhap tu ban phim\n";
		cout << "  2. Doc tu file (.txt)\n";
		cout << "Nhap lua chon: ";
		int choice;
		if (cin >> choice && (choice == 1 || choice == 2)) {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return choice;
		}
		cout << "Lua chon khong hop le! Hay chon 1 hoac 2.\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}
static vector<Process> inputFromFile(string& filenameOut) {
	while (true) {
		cout << "Nhap ten file du lieu (.txt): ";
		string filename;
		getline(cin, filename);
		vector<Process> procs = loadProcessesFromFile(filename);
		if (!procs.empty()) {
			filenameOut = filename;
			return procs;
		}
		cout << "Khong co du lieu hop le trong file. Vui long thu lai.\n";
	}
}

void Comparison::runAllTestCases() {
	int numQuantums = readPositiveInt("Nhap so luong gia tri Quantum (q) muon kiem tra: ");
	vector<int> quantums;
	for (int i = 0; i < numQuantums; i++) {
		quantums.push_back(readPositiveInt("Nhap Quantum thu " + to_string(i + 1) + ": "));
	}
	int numCases = readPositiveInt("\nNhap so luong test case muon tao: ");
	vector<pair<string, vector<Process>>> testCases;
	for (int i = 1; i <= numCases; i++) {
		cout << "\n===== TEST CASE " << i << " =====\n";
		int source = chooseSource();
		vector<Process> procs;
		string label = "Test case " + to_string(i);
		if (source == 1) {
			procs = inputProcessList();
			label += " (ban phim)";
		}
		else {
			string filename;
			procs = inputFromFile(filename);
			label += " (file: " + filename + ")";
		}
		testCases.push_back({ label, procs });
	}
	cout << "\n BANG SO SANH HIEU SUAT ROUND ROBIN (CS Cost = " << CS_COST << ")\n";
	cout << fixed << setprecision(2);

	for (const auto& tc : testCases) {
		cout << "\n[" << tc.first << "] - " << tc.second.size() << " tien trinh\n";
		if (tc.second.size() <= MAX_DISPLAY_PROCESSES) {
			printProcessList(tc.second);
		}
		cout << "\n";
		cout << left << setw(10) << "Quantum" << setw(12) << "Avg WT"
			<< setw(12) << "Avg RT" << setw(10) << "CS" << setw(12) << "Overhead" << "\n";
		cout << "------------------------------------------------------------\n";

		for (int q : quantums) {
			vector<Process> procs = tc.second;
			ostringstream sink;
			streambuf* oldBuf = cout.rdbuf(sink.rdbuf());
			vector<ExecutionSeg> history = runRoundRobin(procs, q);
			cout.rdbuf(oldBuf);
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
				<< setw(12) << avg.averageWT
				<< setw(12) << avg.averageRT
				<< setw(10) << csCount
				<< setw(12) << csCount * CS_COST << "\n";
		}
	}
}