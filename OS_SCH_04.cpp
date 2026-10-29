#include<iostream>
#include<limits>
#include"Process.h"
#include"RoundRobin.h"
#include"Metrics.h"
#include"Display.h"
#include"Comparison.h"
using namespace std;
int main() {
	int luachon;
	do {
		cout << "Mo phong Ready Queue va Context Switch" << endl;
		cout << "1.Nhap danh sach tien trinh va mo phong" << endl;
		cout << "2.Chay test Case so sanh Quantum (1,2,4) va phan tich OverHead" << endl;
		cout << "3.Thoat" << endl;
		cout << "Nhap lua chon : ";
		if (!(cin >> luachon)) {
			cout << "Vui long nhap so nguyen." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		switch (luachon)
		{
		case 1:
		{
			vector<Process> processes = inputProcessList();
			cout << "\n DANH SACH TIEN TRINH \n";
			printProcessList(processes);
			int timeQuantum;
			do
			{
				cout << "Nhap thoi gian quantum (Q > 0): ";
				if (!(cin >> timeQuantum))
				{
					cout << "Vui long nhap so nguyen" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				else if (timeQuantum <= 0)
				{
					cout << "Time Quantum phai lon hon 0! \n";
				}
			} while (timeQuantum <= 0);
			vector<ExecutionSeg> history = runRoundRobin(processes, timeQuantum); calculateMetrics(processes);
			cout << "\n KET QUA MO PHONG \n";
			displayAll(history, processes);
			break;
		}
	case2:
		{
			Comparison comparison;
			comparison.runAllTestCases();
			break;
		}
		case 3:
			cout << "\nDa thoat chuongw trinh!\n";
			break;
		defailt:
			cout << "Lua chon khong hop le! Hay chonj 1,2 hoac 3.\n";
		}
	} while (luachon != 3);
	return 0;
}
