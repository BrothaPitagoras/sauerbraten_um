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

uintptr_t ProcessManagement::GetModuleBaseAddress(DWORD dwProcID, const wchar_t* szModuleName)
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

	if (hndlSnapshot == INVALID_HANDLE_VALUE) {

		std::cout << "INVALID_HANDLE_VALUE RIP   \n";
	}

	return dwModuleBaseAddress;
}

Matrix* ProcessManagement::ReadMatrix(uintptr_t baseAddress) {
	//float matrix[16]; 16-value array laid out contiguously in memory       
	float* matrixBuffer = new float[16];

	//read memory into buffer
	SIZE_T* bytesRead = NULL;
	ReadProcessMemory(ProcessManagement::handleProcess, (LPCVOID)baseAddress, matrixBuffer, sizeof(float[16]), bytesRead);

	//convert bytes to floats
	Matrix* mat = new Matrix();
	mat->m11 = matrixBuffer[0];
	mat->m12 = matrixBuffer[1];
	mat->m13 = matrixBuffer[2];
	mat->m14 = matrixBuffer[3];

	mat->m21 = matrixBuffer[4];
	mat->m22 = matrixBuffer[5];
	mat->m23 = matrixBuffer[6];
	mat->m24 = matrixBuffer[7];

	mat->m31 = matrixBuffer[8];
	mat->m32 = matrixBuffer[9];
	mat->m33 = matrixBuffer[10];
	mat->m34 = matrixBuffer[11];

	mat->m41 = matrixBuffer[12];
	mat->m42 = matrixBuffer[13];
	mat->m43 = matrixBuffer[14];
	mat->m44 = matrixBuffer[15];

	return mat;
}


bool ProcessManagement::AttachAndFillModuleBaseAddress(const wchar_t* procName) {
	DWORD pid = ProcessManagement::GetProcessId(procName);
	ProcessManagement::moduleBaseAddress = ProcessManagement::GetModuleBaseAddress(pid, procName);
	ProcessManagement::handleProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	return ProcessManagement::handleProcess != NULL;
}