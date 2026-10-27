#pragma once
#include <string>
#include <vector>
	constexpr int MAX_PROCESSES = 100;
	constexpr int NOT_STARTED = -1;

	struct Process {
		std::string id = "";
		
		// Du lieu dau vao 
		int arrivalTime = 0; 
		int burstTime = 0;   

		// Du lieu trong luc mo phong 
		int remainingTime = 0;
		int firstRunTime = -1;

		// Ket qua 
		int completionTime = 0; 
		int turnaroundTime = 0; 
		int waitingTime = 0;    
		int responseTime = 0;   
	};

	// Cac ham nhap du lieu
	int nhapSoLuongTienTrinh();

	Process nhapTienTrinh(int stt, const std::vector<Process>& danhSachDaNhap);
	std::vector<Process> nhapDanhSachTienTrinh();

	// Cac ham tien ich cho nhom
	Process taoTienTrinh(const std::string& id, int arrivalTime, int burstTime);
	void datLaiTienTrinh(std::vector<Process>& danhSach);
	void sapXepTheoArrivalTime(std::vector<Process>& danhSach);
	void inDanhSachTienTrinh(const std::vector<Process>& danhSach);
