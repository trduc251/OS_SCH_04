#pragma once
class Process
{
#include <string>
#include <vector>
	constexpr int MAX_PROCESSES = 100;
	constexpr int NOT_STARTED = -1;

	struct Process {
		std::string id;
		// Du lieu dau vao (Nguoi 1)
		int arrivalTime; // AT
		int burstTime;   // BT

		// Du lieu trong luc mo phong (Nguoi 2)
		int remainingTime;
		int firstRunTime;

		// Ket qua (Nguoi 3)
		int completionTime; // CT
		int turnaroundTime; // TAT = CT - AT
		int waitingTime;    // WT = TAT - BT
		int responseTime;   // RT = firstRunTime - AT
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
