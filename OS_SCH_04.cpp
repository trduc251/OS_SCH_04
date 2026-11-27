#include <iostream>
#include <limits>
#include <string>
#include "Process.h"
#include "RoundRobin.h"
#include "Metrics.h"
#include "Display.h"
#include "Comparison.h"
using namespace std;
static int inputTimeQuantum() {
    int timeQuantum;
    do {
        cout << "Nhap thoi gian quantum (Q > 0): ";
        if (!(cin >> timeQuantum)) {
            cout << "Vui long nhap so nguyen.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            timeQuantum = 0;
        }
        else if (timeQuantum <= 0) {
            cout << "Time Quantum phai lon hon 0!\n";
        }
    } while (timeQuantum <= 0);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return timeQuantum;
}
int main() {
    int luachon;
    do {
        cout << "  Mo phong Ready Queue va Context Switch\n";
        cout << "1. Nhap danh sach tien trinh tu ban phim va mo phong\n";
        cout << "2. Doc danh sach tien trinh tu file (.txt) va mo phong\n";
        cout << "3. Chay test Case so sanh Quantum va phan tich OverHead\n";
        cout << "4. Thoat\n";
        cout << "Nhap lua chon: ";
        if (!(cin >> luachon)) {
            cout << "Vui long nhap so nguyen.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (luachon) {
        case 1: {
            vector<Process> processes = inputProcessList();
            printProcessList(processes);

            int timeQuantum = inputTimeQuantum();
            vector<ExecutionSeg> history = runRoundRobin(processes, timeQuantum);
            calculateMetrics(processes);

            cout << "\n KET QUA MO PHONG \n";
            displayAll(history, processes);
            break;
        }
        case 2: {
            string filename;
            cout << "Nhap ten file du lieu (.txt):  ";
            getline(cin, filename);

            vector<Process> processes = loadProcessesFromFile(filename);
            if (processes.empty()) {
                cout << "Khong co du lieu hop le de mo phong.\n";
                break;
            }

            if (processes.size() <= 50) {
                printProcessList(processes);
            }

            int timeQuantum = inputTimeQuantum();
            vector<ExecutionSeg> history = runRoundRobin(processes, timeQuantum);
            calculateMetrics(processes);

            cout << "\n KET QUA MO PHONG \n";
            if (processes.size() <= 50) {
                displayAll(history, processes);
            }
            else {
                cout << "Da hoan thanh mo phong " << processes.size()
                    << " tien trinh (tong " << history.size() << " phan doan thuc thi).\n";
                char showDetail;
                cout << "Du lieu lon (> 50 tien trinh). Ban co muon in toan bo ra man hinh khong? (y/n): ";
                cin >> showDetail;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (showDetail == 'y' || showDetail == 'Y') {
                    displayAll(history, processes);
                }
            }
            break;
        }
        case 3: {
            Comparison comparison;
            comparison.runAllTestCases();
            break;
        }
        case 4:
            cout << "\nDa thoat chuong trinh!\n";
            break;
        default:
            cout << "Lua chon khong hop le! Hay chon 1, 2, 3 hoac 4.\n";
            break;
        }
    } while (luachon != 4);
    return 0;
}