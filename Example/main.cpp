#include <iostream>
#include <Windows.h>

#define ReadReq CTL_CODE(FILE_DEVICE_UNKNOWN, 0x701, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define WriteReq CTL_CODE(FILE_DEVICE_UNKNOWN, 0x702, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define ModuleReq CTL_CODE(FILE_DEVICE_UNKNOWN, 0x703, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)


typedef struct _REQUEST
{
	DWORD Address;
	DWORD Size;
	DWORD ProcessId;
	DWORD Value;
}REQUEST, *PREQUEST;

typedef struct _REQUESTMODULE
{
	DWORD ModuleBase;
	DWORD ProcessId;
}REQUESTMODULE, *PREQUESTMODULE;


template <typename Type>
Type KernelRead(DWORD ReadAddress, DWORD ProcessID)
{
	HANDLE hDriver = CreateFile("\\\\.\\AsmDriver", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
	if (hDriver)
	{
		DWORD dwReturn;
		REQUEST lel;
		lel.Address = ReadAddress;
		lel.ProcessId = ProcessID;
		lel.Size = sizeof(Type);
		
		DeviceIoControl(hDriver, ReadReq, &lel, sizeof(lel), &lel, sizeof(lel), &dwReturn, 0);
		CloseHandle(hDriver);
		return (Type)lel.Value;
	}

	return (Type)0;
}

template <typename Type>
bool KernelWrite(DWORD WriteAddress, Type WriteVal, DWORD ProcessID)
{
	HANDLE hDriver = CreateFile("\\\\.\\AsmDriver", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
	if (hDriver)
	{
		DWORD dwReturn;
		REQUEST lel;
		lel.Address = WriteAddress;
		lel.ProcessId = ProcessID;
		lel.Size = sizeof(WriteVal);
		lel.Value = WriteVal;
		DeviceIoControl(hDriver, WriteReq, &lel, sizeof(lel), &lel, sizeof(lel), &dwReturn, 0);
		CloseHandle(hDriver);
		return 1;
	}

	return 0;
}

bool InitProc(DWORD& ModuleBase, DWORD& ProcessId)
{
	DWORD dwReturn;
	HANDLE hDriver = CreateFile("\\\\.\\AsmDriver", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
	if (hDriver)
	{
		printf("Driver Opened\n");
		REQUESTMODULE lawl;

		DeviceIoControl(hDriver, ModuleReq, NULL, NULL, &lawl, sizeof(lawl), &dwReturn, 0);
		CloseHandle(hDriver);
		ModuleBase = lawl.ModuleBase;
		ProcessId = lawl.ProcessId;
		return 1;
	}
	return 0;
}

int main()
{
	DWORD ModuleBase, ProcessId;
	InitProc(ModuleBase, ProcessId);

	DWORD lawlz = 0x22;
	
	printf("%X \n", KernelRead<DWORD>((DWORD)&lawlz, GetCurrentProcessId()));

	return 0;
}