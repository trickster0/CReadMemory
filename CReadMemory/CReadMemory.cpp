#include <Windows.h>
#include <stdio.h>

using pRtlFirstEntrySList = DWORD(NTAPI*)(DWORD* pValue);

DWORD ReadMemory()
{
	pRtlFirstEntrySList RtlFirstEntrySList = (pRtlFirstEntrySList)GetProcAddress(GetModuleHandleA("ntdll.dll"), "RtlFirstEntrySList");
	SIZE_T writtenBytes = 0;
	WriteProcessMemory(GetCurrentProcess(), (char*)RtlFirstEntrySList + 4, "\x90\x90", 2, &writtenBytes);
	printf("RtlFirstEntrySList address at : %p\n", RtlFirstEntrySList);
	DWORD dwDataLength = 8;
	DWORD returnValue = 0;
	for (DWORD i = 0; i < dwDataLength; i++)
	{
		returnValue = RtlFirstEntrySList((DWORD*)((BYTE*)&RtlFirstEntrySList - 8 + i));
		printf("%x", (BYTE)returnValue);
	}
	return 0;
}

int main()
{
	ReadMemory();
}