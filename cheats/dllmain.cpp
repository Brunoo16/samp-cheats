#include <Windows.h>

void Thread()
{
	while (!*(int*)0xB6F5F0) Sleep(50);

	DWORD OldProtect;

	VirtualProtect((unsigned char*)0x438576, 6, PAGE_EXECUTE_READWRITE, &OldProtect);

	*(unsigned char*)0x438576 = 198;
	*(unsigned char*)0x438577 = 5;
	*(unsigned char*)0x438578 = 140;
	*(unsigned char*)0x438579 = 145;
	*(unsigned char*)0x43857A = 150;
	*(unsigned char*)0x43857B = 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Thread, 0, 0, 0);
	}
	return 1;
}