#include "processManagement.hpp"

DWORD ProcessManagement::GetProcessId(const wchar_t* procName) {
	DWORD procId = 0;

	// Get a snapshot of all processes
	HANDLE handleSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	// error check handle
	if (handleSnapshot != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);
		// get first process of snapshot into pe32
		if (Process32First(handleSnapshot, &pe32))
		{
			do {
				//verify if the process name is equal to given process name
				if (_wcsicmp(pe32.szExeFile, procName) == 0) {
					procId = pe32.th32ProcessID;
					break;
				}
				// loop to the next process inside snapshot
			} while (Process32Next(handleSnapshot, &pe32));
		}
	}
	// cleanup close snapshot's handle
	CloseHandle(handleSnapshot);
	return procId;
}

const uintptr_t ProcessManagement::GetModuleBaseAddress(DWORD dwProcID, const wchar_t* szModuleName)
{
	uintptr_t dwModuleBaseAddress = 0;
	HANDLE hndlSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcID);
	if (hndlSnapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 ModuleEntry32;
		ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(hndlSnapshot, &ModuleEntry32))
		{
			do
			{
				if (_wcsicmp(ModuleEntry32.szModule, szModuleName) == 0)
				{
					dwModuleBaseAddress = (uintptr_t)ModuleEntry32.modBaseAddr;
					break;
				}
			} while (Module32Next(hndlSnapshot, &ModuleEntry32));
		}
		CloseHandle(hndlSnapshot);
	}


	return dwModuleBaseAddress;
}

bool ProcessManagement::AttachAndFillModuleBaseAddress(const wchar_t* procName) {
	auto pid = GetProcessId(procName);
	moduleBaseAddress = GetModuleBaseAddress(pid, procName);
	handleProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	return handleProcess != nullptr;
}