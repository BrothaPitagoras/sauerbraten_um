#pragma once
#include "includes.h"
#include "structs/Matrix.hpp"

namespace ProcessManagement {

	inline HANDLE handleProcess;

	inline uintptr_t moduleBaseAddress;

	DWORD GetProcessId(const wchar_t* procName);

	uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* procName);

	template <typename T> bool WriteMemory(uintptr_t addr, const T& data) {

		// Create a byte buffer with the data
		byte* buffer = new byte[sizeof(T)];

		memcpy(buffer, &data, sizeof(T));

		// Get permissions to write in Page Numbers containing the bytes of addr + sizeof(T)
		DWORD oldPermissions;
		VirtualProtectEx(ProcessManagement::handleProcess, reinterpret_cast<LPVOID>(addr), sizeof(T), PAGE_READWRITE, &oldPermissions);

		// I dont need bytes written rn, maybe some other time, get Write result
		SIZE_T bytes_written = NULL;
		bool result = WriteProcessMemory(ProcessManagement::handleProcess, reinterpret_cast<LPVOID>(addr), buffer, sizeof(T), &bytes_written);

		// Cleanup, delete buffer and restore old permissions
		delete[] buffer;
		VirtualProtectEx(ProcessManagement::handleProcess, reinterpret_cast<LPVOID>(addr), sizeof(T), oldPermissions, NULL);

		return result;
	}

	template <typename T> T ReadMemory(uintptr_t address) {
		T value;
		SIZE_T* bytesRead = NULL;

		ReadProcessMemory(ProcessManagement::handleProcess, reinterpret_cast<LPCVOID>(address), &value, sizeof(T), bytesRead);
		return value;
	}

	Matrix* ReadMatrix(uintptr_t address);

	bool AttachAndFillModuleBaseAddress(const wchar_t* procName);
}