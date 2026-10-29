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
		cout <<"Mo phong Ready Queue va Context Switch" << endl;
		cout <<"1.Nhap danh sach tien trinh va mo phong" << endl;
		cout <<"2.Chay test Case so sanh Quantum (1,2,4) va phan tich OverHead" << endl;
		cout <<"3.Thoat" << endl;
		cout << "Nhap lua chon : ";
		if (!(cin >> luachon)) {
			cout << "Vui long nhap so nguyen." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		switch(luachon)
	}
}