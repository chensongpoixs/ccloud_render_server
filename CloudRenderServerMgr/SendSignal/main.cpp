#include <windows.h>
#include <iostream>
//
//int main(int argc, char* argv[])
//{
//	if (argc != 2) 
//	{
//		std::cerr << "Usage: " << argv[0] << " process_id\n";
//		return 1;
//	}
//
//	int pid = atoi(argv[1]);
//
//	if (!AttachConsole(pid)) {
//		//std::cerr << "Failed to attach console to process " << pid << "\n";
//		DWORD err = GetLastError();
//		std::cerr << "Failed to attach console to process " << pid
//			<< ", error code: " << err << "\n";
//		return 1;
//	}
//
//	if (!GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0)) {
//		std::cerr << "Failed to send Ctrl+C signal to process " << pid << "\n";
//		return 1;
//	}
//
//	std::cout << "Sent Ctrl+C signal to process " << pid << "\n";
//
//	return 0;
//}

typedef void(*callback)(uint32_t p);

__declspec(dllexport)
BOOL APIENTRY DllMain(HINSTANCE hinst, DWORD reason, LPVOID unused1)
{


	callback  ptr = NULL;
	
	if (reason == DLL_PROCESS_ATTACH) 
	{
		
	}
	else if (reason == DLL_PROCESS_DETACH) 
	{

		 
	}
	GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0);
		 
	ptr(9);
	::free(ptr);
	
	//abort();
	(void)unused1;
	return true;
}