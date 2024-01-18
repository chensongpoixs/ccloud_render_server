/***********************************************************************************************
				created: 		2019-05-01

				author:			chensong

				purpose:		ccfg
				输赢不重要，答案对你们有什么意义才重要。

光阴者，百代之过客也，唯有奋力奔跑，方能生风起时，是时代造英雄，英雄存在于时代。或许世人道你轻狂，可你本就年少啊。 看护好，自己的理想和激情。


我可能会遇到很多的人，听他们讲好2多的故事，我来写成故事或编成歌，用我学来的各种乐器演奏它。
然后还可能在一个国家遇到一个心仪我的姑娘，她可能会被我帅气的外表捕获，又会被我深邃的内涵吸引，在某个下雨的夜晚，她会全身淋透然后要在我狭小的住处换身上的湿衣服。
3小时候后她告诉我她其实是这个国家的公主，她愿意向父皇求婚。我不得已告诉她我是穿越而来的男主角，我始终要回到自己的世界。
然后我的身影慢慢消失，我看到她眼里的泪水，心里却没有任何痛苦，我才知道，原来我的心被丢掉了，我游历全世界的原因，就是要找回自己的本心。
于是我开始有意寻找各种各样失去心的人，我变成一块砖头，一颗树，一滴水，一朵白云，去听大家为什么会失去自己的本心。
我发现，刚出生的宝宝，本心还在，慢慢的，他们的本心就会消失，收到了各种黑暗之光的侵蚀。
从一次争论，到嫉妒和悲愤，还有委屈和痛苦，我看到一只只无形的手，把他们的本心扯碎，蒙蔽，偷走，再也回不到主人都身边。
我叫他本心猎手。他可能是和宇宙同在的级别 但是我并不害怕，我仔细回忆自己平淡的一生 寻找本心猎手的痕迹。
沿着自己的回忆，一个个的场景忽闪而过，最后发现，我的本心，在我写代码的时候，会回来。
安静，淡然，代码就是我的一切，写代码就是我本心回归的最好方式，我还没找到本心猎手，但我相信，顺着这个线索，我一定能顺藤摸瓜，把他揪出来。


************************************************************************************************/

// MFCApplication1.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "csocket_util.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "cregistry.h"
#include "clog.h"
#include "clog.h"
#include "ccfg.h"
#include <stdio.h>
#include "crandom.h"
#include "cutil.h"
#include "clib_util.h"
#include "cnet_adapter_test.h"
// CMFCApplication1App


std::string g_render_server_name;
std::vector<std::string> g_render_server_ips;

BEGIN_MESSAGE_MAP(CMFCApplication1App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCApplication1App 构造

CMFCApplication1App::CMFCApplication1App()
	: m_application_wnd(NULL)
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CMFCApplication1App 对象

CMFCApplication1App theApp;
#include <iostream>
using namespace chen;
// CMFCApplication1App 初始化
static void check_file(const char* file_name)
{
	//access
	//if (::_access(file_name, 0) != 0)
	{
		FILE* fp = ::fopen(file_name, "r");
		if (!fp)
		{
			FILE* fp = ::fopen(file_name, "wb+");
		}
		if (fp)
		{
			::fclose(fp);
			fp = NULL;
		}
	}
}

bool create_virtual_desktop(const std::string& desktop_name, PROCESS_INFORMATION& pinfo)
{
#define ARRAY_SIZE  (2048 * 10)
	if (desktop_name.size() < 1)
	{
		WARNING_EX_LOG("create desktop  [desktop_name= %s] failed !!!", desktop_name.c_str());
		return false;
	}
	//GetCurrentThreadId();
	HDESK hDesk = OpenDesktop(LPCWSTR(desktop_name.c_str()), DF_ALLOWOTHERACCOUNTHOOK, TRUE, GENERIC_ALL);
	pinfo = { 0 };
	if (!hDesk)
	{
		SECURITY_ATTRIBUTES sAttribute = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
		hDesk = ::CreateDesktop(LPCWSTR(desktop_name.c_str()), NULL, NULL, DF_ALLOWOTHERACCOUNTHOOK, GENERIC_ALL, &sAttribute);
		if (!hDesk)
		{
			ERROR_EX_LOG("create desktop failed !!!");
			return false;
		}

		//TODO@chensong 20220723   virtual desktop  mouse keydown 
		TCHAR szExplorerFile[ARRAY_SIZE] = { 0 };

		GetWindowsDirectory(szExplorerFile, ARRAY_SIZE - 1);
		_tcscat_s(szExplorerFile, ARRAY_SIZE - 1, _T("\\Explorer.Exe"));


		TCHAR szDirectoryName[ARRAY_SIZE] = { 0 };
		//TCHAR szExplorerFile[ARRAY_SIZE] = { 0 };

		_tcscpy_s(szDirectoryName, _tcslen(szExplorerFile) + 1, szExplorerFile);

		//PathIsExe(szExplorerFile);


		PathRemoveFileSpec(szDirectoryName);

		STARTUPINFO sInfo = { 0 };
		//PROCESS_INFORMATION pInfo = { 0 };
		GetStartupInfo(&sInfo);
		sInfo.cb = sizeof(sInfo);
		sInfo.lpDesktop = (LPWSTR)desktop_name.c_str();;

		//Lanuching a application into dekstop
		BOOL bCreateProcessReturn = CreateProcess(szExplorerFile,
			NULL,
			NULL,
			NULL,
			TRUE,
			NORMAL_PRIORITY_CLASS,
			NULL,
			szDirectoryName,
			&sInfo,
			&pinfo);
		if (bCreateProcessReturn)
		{
			CloseHandle(pinfo.hThread);
			pinfo.hThread = NULL;
			CloseHandle(pinfo.hProcess);
			pinfo.hProcess = NULL;
		}
		/*TCHAR *pszError = NULL;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), 0, (LPWSTR)&pszError, 0, NULL);
		OutputDebugString(_T("\n\t\t"));
		OutputDebugString(pszError);*/
	}
	// TODO@chensong 2022-12-26  清理 virtual desktop 资源
	if (hDesk)
	{
		CloseDesktop(hDesk);
		hDesk = NULL;
	}
	return true;
}
BOOL CMFCApplication1App::InitInstance()
{

	
	LOG::init("./log", "CloudRenderServerMgr");
	const char * config_file = "./CloudRenderServerMgr.cfg";
	check_file(config_file);
	if (!g_cfg.init(config_file))
	{
		using namespace chen;
		 ERROR_EX_LOG("not find CloudRenderServerMgr.cfg failed !!!");
		LOG::destroy();
	}
	 
	//if (!chen::readfromregistry(g_cfg.get_string(ECI_AppSystemRegedit).c_str(), g_cfg.get_string(ECI_AppSystemRegeditValue).c_str(), g_render_server_name))
	//{
	//	WARNING_EX_LOG("  render server name  failed !!!");
	//	static const int key_len = 10;
	//	unsigned char encrypt_key[key_len * 2] = { 0 }; 
	//	;
	//	cutil::rand_bytes(encrypt_key, sizeof(encrypt_key), c_rand);
	//	
	//	//g_render_server_name = encrypt_key;
	//	if (!chen::writetoregistry(g_cfg.get_string(ECI_AppSystemRegedit).c_str(), g_cfg.get_string(ECI_AppSystemRegeditValue).c_str(), g_render_server_name))
	//	{
	//		WARNING_EX_LOG("wirte render name = [%s]config failed !!!", g_render_server_name.c_str());
	//	}
	//}
	//g_render_server_name = cutil::get_hex_str(g_render_server_name.c_str(), g_render_server_name.length());
	


	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

//<<<<<<< HEAD
	// 创建一个不可见的主窗口
	//CWnd* pWnd = new CWnd;
	//pWnd.CreateEx(0, AfxRegisterWndClass(0), _T("MyHiddenWindow"), 0, 0, 0, 0, NULL, 0);

	// 将主窗口设置为不可见
	//m_pMainWnd = pWnd;
	//m_pMainWnd->ShowWindow(SW_HIDE);
//=======
	AfxEnableControlContainer();
//>>>>>>> f38aee4805b86dbb97b273854ffbf429cca47d7e
	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	//CShellManager *pShellManager = new CShellManager;

	//// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	//CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("@CloudRenderServerMgr"));

	bool AlreadyRunning = false;

	Sleep(1000);
	HANDLE hMutexOneInstance = ::CreateMutex(NULL, FALSE, _T("CloudRenderServerMgr_{44D28BCA-7F46-4af2-A1FF-36EE0DAC7CD2}"));

	AlreadyRunning = (::GetLastError() == ERROR_ALREADY_EXISTS ||
		::GetLastError() == ERROR_ACCESS_DENIED);

	if (AlreadyRunning)
	{
		MessageBox(NULL, _T("云渲染管理程序已经启动！！！"), _T("CloudRenderServerMgr"), 0);
		/*g_cfg.destroy();
		using namespace chen;
		LOG::destroy();*/
		return FALSE;
	}
	NORMAL_EX_LOG("[render_server_name = %s]", g_cfg.get_string(ECI_RenderServerName).c_str());
	if (g_cfg.get_string(ECI_RenderServerName).length() < 3)
	{
		static const int key_len = 4;
		unsigned char encrypt_key[key_len * 2] = { 0 };
		cutil::rand_bytes(encrypt_key, sizeof(encrypt_key), c_rand);
		g_render_server_name = cutil::get_hex_str(encrypt_key, key_len * 2);
		g_cfg.set_string(ECI_RenderServerName, "render_server_name", g_render_server_name);
	}
	else
	{
		g_render_server_name = g_cfg.get_string(ECI_RenderServerName);
	}

	NORMAL_EX_LOG("[render_server_name = %s]", g_render_server_name.c_str());
	 
	std::set<std::string> ips;
	chen::get_network_ips(ips);
	for (const std::string& ip : ips)
	{
		g_render_server_ips.push_back(ip);
	}
	//chen::net_adapter_test();
	if (g_cfg.get_string(ECI_RenderServerIp).length() < 2)
	{

		 	g_cfg.set_string(ECI_RenderServerIp, "render_server_ip", g_render_server_ips.size()>0 ?g_render_server_ips[0] : "127.0.0.1");
	}
	m_application_wnd = new CMFCApplication1Dlg();
	//m_application_wnd->SetBackgroundColor(RGB(255, 255, 255));;
	m_pMainWnd = m_application_wnd;
	m_application_wnd->Create(IDD_MFCAPPLICATION1_DIALOG);
	
	ShowWindow(m_pMainWnd->GetSafeHwnd(), SW_SHOW);
	 
	return TRUE;
	CMFCApplication1Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}
	dlg.destroy();
	g_cfg.destroy();
	using namespace chen;
	LOG::destroy();
	// 删除上面创建的 shell 管理器。
	/*if (pShellManager != nullptr)
	{
		delete pShellManager;
	}*/

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

int CMFCApplication1App::ExitInstance()
{
	if(m_application_wnd)
	{
		SYSTEM_LOG("app destroy ...");
		m_application_wnd->destroy();
		m_application_wnd->DestroyWindow();
		
	}
	SYSTEM_LOG("Exit gconfig ..");
	g_cfg.destroy();
	using namespace chen;
	LOG::destroy();
	m_application_wnd = NULL;
	return  CWinApp::ExitInstance();
}

