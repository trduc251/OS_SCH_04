#include "Process.h"

#include <sstream> 
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>

using namespace std;

const int MAX_TIME = 1000000; // Gioi han tren cua AT va BT

static int docSoNguyen(const string& prompt, int minValue, int maxValue) {
	while (true) {
		cout << prompt;

		string line;
		if (!getline(cin, line)) exit(1); // Het du lieu dau vao thi thoat

		istringstream input(line);
		int value;
		char extra;

		if (!(input >> value) || (input >> extra)) {
			cout << " [Loi] Vui long nhap mot so nguyen. \n";
		}
		else if (value < minValue || value > maxValue) {
			cout << " [Loi] Gia tri phai tu " << minValue << " den " << maxValue << ".\n";
		}
		else {
			return value;
		}
	}
}
static bool maDaTonTai(const string& id, const vector<Process>& danhSach) {
	for (const Process& tienTrinh : danhSach) {
		if (tienTrinh.id == id) return true;
	}
	return false;
}

int nhapSoLuongTienTrinh() {
	return docSoNguyen("Nhap so luong tien trinh: ", 1, MAX_PROCESSES);
}

Process nhapTienTrinh(int stt, const vector<Process>& danhSachDaNhap) {
	cout << "\nTien trinh thu " << stt << "\n";

	string id;
	while (true) {
		cout << "Ma tien trinh (vi du P" << stt << "): ";
		if (!getline(cin, id)) exit(1);

		if (id.empty() || id.find(' ') != string::npos) {
			cout << " [Loi] Ma tien trinh khong duoc de trong hoac chua khoang trong. \n";
		}
		else if (maDaTonTai(id, danhSachDaNhap)) {
			cout << " [Loi] Ma ' " << id << " ' da ton tai, vui long nhap ma khac.\n";
		}
		else {
			break;
		}
	}

	int arrivalTime = docSoNguyen("Arrival Time (AT): ", 0, MAX_TIME);
	int burstTime = docSoNguyen("CPU Burst (BT): ", 1, MAX_TIME);

	return taoTienTrinh(id, arrivalTime, burstTime);
}
vector<Process> nhapDanhSachTienTrinh() {
	int soLuong = nhapSoLuongTienTrinh();

	vector<Process> danhSach;
	for (int i = 1; i <= soLuong; i++) {
		danhSach.push_back(nhapTienTrinh(i, danhSach));
	}
	return danhSach;
 }

Process taoTienTrinh(const string& id, int arrivalTime, int burstTime) {
	Process tienTrinh;
	tienTrinh.id = id;
	tienTrinh.arrivalTime = arrivalTime;
	tienTrinh.burstTime = burstTime;
	tienTrinh.remainingTime = burstTime;
	tienTrinh.firstRunTime = NOT_STARTED;
	tienTrinh.completionTime = 0;
	tienTrinh.turnaroundTime = 0;
	tienTrinh.waitingTime = 0;
	tienTrinh.responseTime = 0;
	return  tienTrinh;
}

void datLaiTienTrinh(vector<Process>& danhSach) {
	for (Process& tienTrinh : danhSach) {
		tienTrinh = taoTienTrinh(tienTrinh.id, tienTrinh.arrivalTime, tienTrinh.burstTime);
    }
}

void sapXepTheoArrivalTime(vector<Process>& danhSach) {
	stable_sort(danhSach.begin(), danhSach.end(),
		[](const Process& a, const Process& b) {
			return a.arrivalTime < b.arrivalTime;
		});
}

void inDanhSachTienTrinh(const vector<Process>& danhSach) {
	cout << "\nDANH SACH TIEN TRINH\n";
	cout << left << setw(10) << "Ma TT" << setw(15) << "Arrival Time" << "CPU Burst\n";
	cout << string(35, '-') << "\n";

	for (const Process& tienTrinh : danhSach) {
		cout << left << setw(10) << tienTrinh.id
			<< setw(15) << tienTrinh.arrivalTime << tienTrinh.burstTime << "\n";
	}
}