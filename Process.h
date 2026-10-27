#pragma once
class Process
{
#include <string>
#include <vector>
	constexpr int MAX_PROCESSES = 100;
	constexpr int NOT_STARTED = -1;

	struct Process {
		std::string id;
		// Du lieu dau vao 
		int arrivalTime; 
		int burstTime;   

		// Du lieu trong luc mo phong 
		int remainingTime;
		int firstRunTime;

		// Ket qua 
		int completionTime; 
		int turnaroundTime; 
		int waitingTime;    
		int responseTime;   
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
