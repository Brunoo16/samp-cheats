#include <Windows.h>

static void Thread()
{
	while (!*reinterpret_cast<int*>(0xB6F5F0)) Sleep(50);

	DWORD OldProtect = NULL;

	const BYTE byte_array[] = { 0xC6, 0x5, 0x8C, 0x91, 0x96, 0x0, 0x1 };

	VirtualProtect(reinterpret_cast<void*>(0x438576), 7, PAGE_EXECUTE_READWRITE, &OldProtect);

	memcpy(reinterpret_cast<void*>(0x438576), byte_array, 7);

	VirtualProtect(reinterpret_cast<void*>(0x588BE0), 1, PAGE_EXECUTE_READWRITE, &OldProtect);

	*reinterpret_cast<BYTE*>(0x588BE0) = 0xA0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Thread), 0, 0, 0);
	}
	return 1;
}