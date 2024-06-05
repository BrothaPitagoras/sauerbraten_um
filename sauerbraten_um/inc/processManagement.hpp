#pragma once
#include "includes.h"
#include "structs/Matrix.hpp"
	
// changes:
//	Virtualprotect shouldnt be needed when calling WriteProcessMemory - humbter
//	dont need to use windows typedef since they are for retro compatibility. - humbter

class ProcessManagement {
public:

	HANDLE handleProcess;

	uintptr_t moduleBaseAddress;

	DWORD GetProcessId(const wchar_t* procName);

	const uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* procName);

	template <typename T> bool WriteMemory(uintptr_t addr, const T& data) {

		// I dont need bytes written rn, maybe some other time, get Write result
		uint64_t bytes_written = 0;
		bool result = WriteProcessMemory(handleProcess, reinterpret_cast<void*>(addr), &data, sizeof(T), &bytes_written);

		return result;
	};

	template <typename T> T ReadMemory(uintptr_t address) {
		T value;
		uint64_t bytesRead = 0;

		ReadProcessMemory(handleProcess, reinterpret_cast<void*>(address), &value, sizeof(T), &bytesRead);
		return value;
	};

	bool AttachAndFillModuleBaseAddress(const wchar_t* procName);
};