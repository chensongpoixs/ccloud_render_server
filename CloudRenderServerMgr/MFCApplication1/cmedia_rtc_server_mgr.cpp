/***********************************************************************************************
				created: 		2019-05-01

				author:			chensong

				purpose:		ccfg
************************************************************************************************/
#include "cmedia_rtc_server_mgr.h"
#include "cutil.h"
//#include "pch.h"
//
#include <Windows.h>
#include <tchar.h>
#include <ShlObj_core.h>
#include <Shlwapi.h>
#include <Windows.h>
#pragma comment( lib, "ShLwApi.Lib" ) //PathRemoveFileSpecA


#define ARRAY_SIZE (2048)
 namespace chen {
	//cmedia_rtc_server_mgr g_media_rtc_server_mgr;

	 
	cmedia_rtc_server_mgr::~cmedia_rtc_server_mgr()
	{
	}
	bool cmedia_rtc_server_mgr::update()
	{
		return false;
	}
	bool cmedia_rtc_server_mgr::startup()
	{
		std::string app_path_name = "D:/Work/cabroad_server/Server/cmedia_rtc_server/Server/bin/x64/Debug/media_rtc_server.exe";
		//std::string app_path_name = "D:/Work/UE/builder_V4.2_Release_76_202304042038/builderexe/Rte.exe";
		std::string app_path_param =   " ../../server.cfg  ../../log";
		std::string app_work_path = get_workdir(app_path_name);
		/*{
			STARTUPINFO si;
			memset(&si, 0, sizeof(si));
			si.cb = sizeof(si);

			PROCESS_INFORMATION pi;
			memset(&pi, 0, sizeof(pi));

			CString commandLine     (app_path_name.c_str()) ;

			BOOL ret = CreateProcess(NULL, commandLine.GetBuffer(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
			if (ret) {
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
			}
		}
		return true;*/
		TCHAR szAppName[ARRAY_SIZE] = { 0 };
		//Get the application full path, so that it can be launch into the switching desktop.
		//GetModuleFileName(GetModuleHandle(NULL), szAppName, ARRAY_SIZE - 1);
		/*ACCESS_MASK desired_access = DESKTOP_CREATEMENU | DESKTOP_CREATEWINDOW |
			DESKTOP_ENUMERATE | DESKTOP_HOOKCONTROL |
			DESKTOP_WRITEOBJECTS | DESKTOP_READOBJECTS |
			DESKTOP_SWITCHDESKTOP | GENERIC_WRITE;

*/
		//system(app_path_name.c_str());
		CString commandLine(app_path_name.c_str());
		CString path_work(app_path_param.c_str());
		//ShellExecute(NULL, _T("open"), LPCWSTR(app_path_name.c_str()), NULL, NULL, SW_SHOW);
		STARTUPINFO si;
		memset(&si, 0, sizeof(si));
		si.cb = sizeof(si);
		//si.wShowWindow = SW_SHOW;
		bool ret = ::CreateProcess(NULL, commandLine.GetBuffer(), NULL, NULL, FALSE, HIGH_PRIORITY_CLASS, NULL, NULL, &si, &m_app_info);
		if (ret)
		{
			// TODO@chensong 2022-07-27  创建线程关闭  -----后期优化 
			CloseHandle(m_app_info.hThread);
			m_app_info.hThread = NULL;
			CloseHandle(m_app_info.hProcess);
			m_app_info.hProcess = NULL;

			//process_info.hProcess = virtual_desktop.dwProcessId;
			//process_info.hThread = virtual_desktop.dwThreadId;

		}
		return true;
	}
	void cmedia_rtc_server_mgr::destroy()
	{
	}
	EProcessStateType cmedia_rtc_server_mgr::get_media_server_status()
	{
		update();
		return m_process_type;
	}
 }