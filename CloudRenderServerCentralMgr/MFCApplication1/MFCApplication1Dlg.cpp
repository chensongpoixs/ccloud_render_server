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

// MFCApplication1Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include <string>
#include <WinUser.h>
#include "ccfg.h"
#include "clog.h"
const UINT WM_TRAYICON_NOTIFY_MESSAGE = RegisterWindowMessage(_T("WM_TRAYICON_NOTIFY_MESSAGE-{8DDBE93E-DFE8-4279-934E-05C39902F37D}"));
#define _CRT_SECURE_NO_WARNINGS

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

//class CAboutDlg : public CDialogEx
//{
//public:
//	CAboutDlg();
//
//// 对话框数据
//#ifdef AFX_DESIGN_TIME
//	enum { IDD = IDD_ABOUTBOX };
//#endif
//
//	protected:
//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
//
//// 实现
//protected:
//	DECLARE_MESSAGE_MAP()
//};
//
//CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
//{
//}
//
//void CAboutDlg::DoDataExchange(CDataExchange* pDX)
//{
//	CDialogEx::DoDataExchange(pDX);
//}
//
//BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//END_MESSAGE_MAP()

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

														// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()
// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(CMFCApplication1Dlg::IDD, pParent)
	, m_ip_list()
	 
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	
	
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_REGISTERED_MESSAGE(WM_TRAYICON_NOTIFY_MESSAGE, OnTrayMessage)
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(RenderServerStart, &CMFCApplication1Dlg::OnBnClickedCloudrenderstart)
	//ON_EN_CHANGE(localhost, &CMFCApplication1Dlg::OnEnChangelocalhost)
	//ON_STN_CLICKED(render_server_status, &CMFCApplication1Dlg::OnStnClickedserverstatus)
	//ON_BN_CLICKED(media_rtc_server_start, &CMFCApplication1Dlg::OnBnClickedrtcserverstart)
	//ON_BN_CLICKED(RenderServerStart2, &CMFCApplication1Dlg::OnBnClickedRenderserverstart2)
	//ON_BN_CLICKED(MediaRtcServerStart, &CMFCApplication1Dlg::OnBnClickedMediartcserverstart)
	//ON_MESSAGE(WM_TASKBAR_CREATED, OnTaskbarCreated)
	//ON_NOTIFY(NIN_SELECT, 1, OnTrayIconClick)
	//ON_BN_CLICKED(CloudRenderStart, &CMFCApplication1Dlg::OnBnClickedCloudrenderstart)
	ON_STN_CLICKED(IDB_BITMAP1, &CMFCApplication1Dlg::OnStnClickedBitmap1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CMFCApplication1Dlg 消息处理程序
  std::thread	 					m_thread;
static bool							m_stoped = false;
BOOL CMFCApplication1Dlg::OnInitDialog()
{
	//return TRUE;
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
		//	pSysMenu->AppendMenu(MF_SEPARATOR);
			//pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	 //m_bitmap.LoadBitmap(IDB_BITMAP2);

	 //CWnd * pWnd = GetDlgItem(IDD_MFCAPPLICATION1_DIALOG);
	 //// 设置静态控件的位图为背景图片
	 //((CStatic*)pWnd)->SetBitmap(m_bitmap);


	//HBITMAP hBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2),
	//	IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	//m_bitmap.Attach(hBitmap); // 加载图片

	/*CRect rect;
	GetClientRect(&rect);*/

	// 设置控件对话框背景
	//m_brush.CreatePatternBrush(&m_bitmap);
	
	
	 // 将白色设置为透明色



	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	NOTIFYICONDATA nData;
	nData.cbSize = sizeof(NOTIFYICONDATA);
	nData.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	nData.hWnd = m_hWnd;
	 nData.uCallbackMessage = WM_TRAYICON_NOTIFY_MESSAGE;
	nData.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	nData.uID = 1;
	_tcscpy_s(nData.szTip, 127, _T("CloudRenderSreverMgr"));
	if (!Shell_NotifyIcon(NIM_ADD, &nData))
	{
		MessageBox(_T("Failed to set tray icon."), _T("CloudRenderServerMgr"), MB_ICONINFORMATION | MB_TOPMOST | MB_TASKMODAL);
		throw false;
	}

	CWnd* pWnd = AfxGetMainWnd(); // 获取主窗口指针
	pWnd->SetWindowText(_T("CloudRenderServerMgr")); // 设置窗口标题

	/*
	
	wchar_t * char2wchar(const char* cchar) 
{     
    wchar_t *m_wchar;    
    int len = MultiByteToWideChar( CP_ACP, 0, cchar, strlen(cchar), NULL, 0);     
    m_wchar= new wchar_t[len+1];     
    MultiByteToWideChar( CP_ACP, 0, cchar, strlen( cchar), m_wchar, len);     
    m_wchar[len]= '\0' ;    
    return m_wchar; 
} 
 
	*/

	 

	// GetDlgItem(localhost_IP)->SetWindowText(_T("0"));
	{
		std::string wan  =  chen::g_cfg.get_string(chen::ECI_RenderServerIp);
		int len = MultiByteToWideChar(CP_ACP, 0, wan .c_str(), wan .length(), NULL, 0);
		std::wstring wwan;
		wwan.resize(len);
		MultiByteToWideChar(CP_ACP, 0, wan.c_str(), wan.length(), (LPWSTR)wwan.data(), len);
	//	GetDlgItem(Render_Server_Wan)->SetWindowText(wwan.c_str());

		CComboBox* list = (CComboBox*)GetDlgItem(Render_Server_Wan);
		size_t index = 0;
		for (size_t i = 0; i < g_render_server_ips.size(); ++i)
		{

			std::string ip = g_render_server_ips[i];
			if (chen::g_cfg.get_string(chen::ECI_RenderServerIp) == ip)
			{
				index = i;
			}
			int len = MultiByteToWideChar(CP_ACP, 0, ip.c_str(), ip.length(), NULL, 0);
			std::wstring wcentral_ip;
			wcentral_ip.resize(len);
			MultiByteToWideChar(CP_ACP, 0, ip.c_str(), ip.length(), (LPWSTR)wcentral_ip.data(), len);
			if (list)
			{
				list->InsertString(i, wcentral_ip.c_str());
			}
		}
		list->SetCurSel(index);
		//list->GetCurSel();
	}
	{
		std::string wan_port = std::to_string(chen::g_cfg.get_uint32(chen::ECI_WanPort));
		int len = MultiByteToWideChar(CP_ACP, 0, wan_port.c_str(), wan_port.length(), NULL, 0);
		std::wstring wwan_port;
		wwan_port.resize(len);
		MultiByteToWideChar(CP_ACP, 0, wan_port.c_str(), wan_port.length(), (LPWSTR)wwan_port.data(), len);
		GetDlgItem(render_server_port)->SetWindowText(wwan_port.c_str());
		
		
	}
	{
		std::string central_ip =  chen::g_cfg.get_string(chen::ECI_CentralIp);

		int len = MultiByteToWideChar(CP_ACP, 0, central_ip.c_str(), central_ip.length(), NULL, 0);
		std::wstring wcentral_ip;
		wcentral_ip.resize(len);
		MultiByteToWideChar(CP_ACP, 0,  central_ip.c_str(),  central_ip.length(), (LPWSTR)wcentral_ip.data(), len);
		GetDlgItem(wan_address)->SetWindowText(wcentral_ip.c_str());
	}
	{
		std::string central_port = std::to_string(chen::g_cfg.get_uint32(chen::ECI_CentralPort));
		int len = MultiByteToWideChar(CP_ACP, 0, central_port.c_str(), central_port.length(), NULL, 0);
		std::wstring wcentral_port;
		wcentral_port.resize(len);
		MultiByteToWideChar(CP_ACP, 0,  central_port.c_str(),  central_port.length(), (LPWSTR)wcentral_port.data(), len);
		GetDlgItem(signal_server_port)->SetWindowText(wcentral_port.c_str());

	}
	//GetDlgItem(min_port)->SetWindowText(_T("20000"));
	//GetDlgItem(max_port)->SetWindowText(_T("30000"));

	//GetDlgItem(rtc_time_out)->SetWindowText(_T("10000"));
	//GetDlgItem(MediaRtcServerStart)->SetWindowText(_T("未启动"));
	GetDlgItem(CloudRenderStart)->SetWindowText(_T("未启动"));


	WINDOWPLACEMENT wp;
	GetWindowPlacement(&wp);  //再次获取尺寸等信息，要不然会溢出(win10上崩溃)
	wp.length = sizeof(WINDOWPLACEMENT);
	wp.flags = WPF_RESTORETOMAXIMIZED;
	wp.showCmd = SW_HIDE;
	SetWindowPlacement(&wp);
	CRect rect;

	/*GetDlgItem(IDC_STATIC)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	GetDlgItem(IDC_STATIC)->MoveWindow(rect.left, rect.top, 250, 250, true);*/
	m_stoped = false;
	/*if (m_thread.joinable())
	{
		m_thread.join();
	}*/
	/*std::thread([&] {
		if (!m_stoped)
		{

			_work_ptread();
		}
	}).detach();*/
	/*if (m_thread && m_thread->joinable())
	{

		m_thread->join();


	}*/
	/*delete m_thread;
	m_thread = NULL;*/
	if (!m_stoped)
	{
		std::thread 	ff(std::thread(&CMFCApplication1Dlg::_work_ptread, this));
		m_thread.swap(ff);
	}
	// m_thread .swap( std::thread(&CMFCApplication1Dlg::_work_ptread, this)); 
	 
//	GetDlgItem(render_server_status)->SetWindowText(_T("未启动")); 
	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	//CDialog::OnSysCommand(nID, lParam);
	
	
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	memDC.SelectObject(&m_bitmap);

	{
		CRect rect;
		GetClientRect(&rect);
		dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	}
	if (IsIconic())
	{
		

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		STILL_ACTIVE;
		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);

		//// 创建内存DC
		//CDC dcMem;
		//dcMem.CreateCompatibleDC(&dc);
		//// 将背景图片选入内存DC
		//CBitmap* pOldBitmap = dcMem.SelectObject(&m_bitmap);

		//// 绘制背景图片
		//BITMAP bm;
		//m_bitmap.GetBitmap(&bm);
		//dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

		//// 恢复原来的位图
		//dcMem.SelectObject(pOldBitmap);
			}
	else
	{
		CDialog::OnPaint();
	}


}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#define MANAGE_DESKTOP_MENU_ID		500
#define EXIT_MENU_ID				503
LRESULT CMFCApplication1Dlg::OnTrayMessage(WPARAM wParam, LPARAM lParam)
{
	UINT uMsg = (UINT)lParam; 
	if (uMsg == WM_RBUTTONDOWN || uMsg == WM_CONTEXTMENU /*|| WM_LBUTTONDOWN*/)
	{
		// 显示主窗口
		/*ShowWindow(SW_RESTORE);*/
		POINT pt;
		GetCursorPos(&pt);

		HMENU hContextMenu = CreatePopupMenu(); 
		AppendMenu(hContextMenu, MF_ENABLED | MF_STRING, EXIT_MENU_ID, _T("&退出"));
		SetForegroundWindow();

		//Display the context menu.
		int iSelectedIndex = TrackPopupMenu(hContextMenu, TPM_TOPALIGN | TPM_VERPOSANIMATION | TPM_RETURNCMD, pt.x, pt.y, 0, m_hWnd, NULL);
		switch (iSelectedIndex)
		{
		case EXIT_MENU_ID:
			 
			PostQuitMessage(0);
			break; 
		default:
			break;
		}
	}
	else if (uMsg == WM_LBUTTONDOWN)
	{
		ShowWindow(SW_SHOW);
	}
	return LRESULT();
}

void CMFCApplication1Dlg::OnDestroy()
{
	CDialog::OnDestroy();
	NOTIFYICONDATA nData;
	nData.cbSize = sizeof(NOTIFYICONDATA);
	nData.hWnd = m_hWnd;
	nData.uID = 1;

	if (!Shell_NotifyIcon(NIM_DELETE, &nData)) {}
	 
}



void CMFCApplication1Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}
#define  _CRT_SECURE_NO_WARNINGS
//static FILE  * out_file_ptr = ::fopen("./mfc.log", "wb+");
void CMFCApplication1Dlg::OnBnClickedRenderserverstart()
{
	// TODO: 在此添加控件通知处理程序代码
	/*fprintf(out_file_ptr, "[%s][%d]\n", __FUNCTION__, __LINE__);
	fflush(out_file_ptr);*/
	CString str;
	//GetDlgItem(localhost_IP)->GetWindowText(str);
	GetDlgItem(wan_address)->GetWindowText(str);
	std::string pp = CT2A(str.GetString());
	/*fprintf(out_file_ptr, "[%s][%d][%s]\n", __FUNCTION__, __LINE__, pp.c_str());
	fflush(out_file_ptr);*/
	//GetDlgItem(wan_address)->SetWindowTextW(str);
	//GetDlgItem(render_server_status)->(_T(""));
	//将按钮修改为BS_OWNERDRAW风格，允许button采用自绘模式
	//GetDlgItem(render_server_status)->SetWindowText(_T(" "));
	//SendMessage( , WM_SETTEXT, 0, _T("")); // 将控件文本内容设置为空字符串
	//GetDlgItem(render_server_status)->SetWindowText(_T("启动..."));
	//GetDlgItem(render_server_status)->SetWindowText(_T(" "));
	//SetWindowText(GetDlgItem(render_server_status), _T(""));
	//SetWindowText(GetDlgItem(render_server_status), _T(""));
	//SetDlgItemText(render_server_status, _T(""), _T(""));
	//GetDlgItem(RenderServerStart)->SetTextColor(RGB(255, 0, 0));
	//GetDlgItem(render_server_status)->SetTextColor(RGB(255, 0, 0));
	//GetDlgItem(RenderServerStart)->SetWindowTextW(L"停止"); // 改变button上显示的文字
	//GetDlgItem(RenderServerStart)->ModifyStyle(0, BS_OWNERDRAW, 0);
}


//void CMFCApplication1Dlg::OnEnChangelocalhost()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//	printf("[%s][%d]\n", __FUNCTION__, __LINE__);
//	fprintf(out_file_ptr, "[%s][%d]\n", __FUNCTION__, __LINE__);
//	fflush(out_file_ptr);
//	// TODO:  在此添加控件通知处理程序代码
//}

//
//void CMFCApplication1Dlg::OnStnClickedserverstatus()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}


void CMFCApplication1Dlg::OnBnClickedrtcserverstart()
{
	// TODO: 在此添加控件通知处理程序代码
}


//void CMFCApplication1Dlg::OnBnClickedRenderserverstart2()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}


//void CMFCApplication1Dlg::OnBnClickedMediartcserverstart()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	/*chen::EProcessStateType status_type = m_media_rtc_mgr.get_media_server_status();
//
//	if (status_type == chen::EProcessActive || status_type == chen::EProcessStart)
//	{
//		GetDlgItem(MediaRtcServerStart)->SetWindowText(_T("停止中..."));
//		m_media_rtc_mgr.close_app();
//		return;
//	}
//	GetDlgItem(MediaRtcServerStart)->SetWindowText(_T("启动中..."));
//*/
//	
//	CString str;
//	//GetDlgItem(localhost_IP)->GetWindowText(str);
//	GetDlgItem(wan_address)->GetWindowText(str);
//	std::string wan_ip = CT2A(str.GetString());
//	GetDlgItem(signal_server_port)->GetWindowText(str);
//	std::string media_wan_port = CT2A(str.GetString());
//	GetDlgItem(min_port)->GetWindowText(str);
//	std::string media_min_port = CT2A(str.GetString());
//	GetDlgItem(max_port)->GetWindowText(str);
//	std::string media_max_port = CT2A(str.GetString());
//	GetDlgItem(rtc_time_out)->GetWindowText(str);
//	std::string media_timeouts = CT2A(str.GetString());
//	/*if (!m_media_rtc_mgr.startup(wan_ip, media_wan_port, media_min_port, media_max_port, media_timeouts))
//	{
//		GetDlgItem(MediaRtcServerStart)->SetWindowText(_T("启动失败!!!"));
//		return;
//	}*/
//	
//	//GetDlgItem(media_rtc_server_status)->SetWindowText(_T("启动..."));
//	//GetDlgItem(render_server_status)->SetWindowText(_T(" "));
//	//SetWindowText(GetDlgItem(render_server_status), _T(""));
//	//SetWindowText(GetDlgItem(render_server_status), _T(""));
//	//SetDlgItemText(render_server_status, _T(""), _T(""));
//	//GetDlgItem(RenderServerStart)->SetTextColor(RGB(255, 0, 0));
//	//GetDlgItem(render_server_status)->SetTextColor(RGB(255, 0, 0));
//	//GetDlgItem(MediaRtcServerStart)->SetWindowTextW(L"停止"); // 改变button上显示的文字
//}

void CMFCApplication1Dlg::destroy()
{
	using namespace chen;
		SYSTEM_LOG("render server exit ...");
		m_render_mgr.destroy();
		SYSTEM_LOG("media rtc  server exit ...");
		//m_media_rtc_mgr.destroy();
		m_stoped = true;
		SYSTEM_LOG(" app thread   exit ...");
		if (m_thread.joinable())
		{
			m_thread.join();

		}
		SYSTEM_LOG(" app thread   exit OK !!!");
}

void CMFCApplication1Dlg::_work_ptread()
{
	 
	chen::EProcessStateType render_type = chen::EProcessNone;
	while (!m_stoped)
	{
		chen::EProcessStateType  status_type = m_render_mgr.get_render_server_status();
		 if (status_type != render_type)
		 {
			 render_type = status_type;
			 if (!m_stoped &&status_type == chen::EProcessActive)
			 {
				 GetDlgItem(CloudRenderStart)->SetWindowText(_T("停止"));
			 }
			 else if (!m_stoped &&status_type == chen::EProcessStart)
			 {
				 GetDlgItem(CloudRenderStart)->SetWindowText(_T("启动中..."));
			 }
			 else if (!m_stoped)
			 {
				 GetDlgItem(CloudRenderStart)->SetWindowText(_T("未启动"));
			 }
		 }
		
	//	::Sleep(1);
		 std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
	//m_thread.join();
}


void CMFCApplication1Dlg::OnBnClickedCloudrenderstart()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	chen::EProcessStateType status_type = m_render_mgr.get_render_server_status();

	if (status_type == chen::EProcessActive || status_type == chen::EProcessStart)
	{
		GetDlgItem(CloudRenderStart)->SetWindowText(_T("停止中..."));
		m_render_mgr.close_app();
		return;
	}

	GetDlgItem(CloudRenderStart)->SetWindowText(_T("启动中..."));
	

	 

	CString str;
	//GetDlgItem(localhost_IP)->GetWindowText(str);
	std::string render_server_id = CT2A(str.GetString());
	GetDlgItem(render_server_port)->GetWindowText(str);
	std::string render_wan_port = CT2A(str.GetString());
	GetDlgItem(Render_Server_Wan)->GetWindowText(str);
	std::string render_server_wan = CT2A(str.GetString());
	GetDlgItem(wan_address)->GetWindowText(str);
	std::string centreal_ip = CT2A(str.GetString());
	GetDlgItem(signal_server_port)->GetWindowText(str);
	std::string centreal_port = CT2A(str.GetString());
	
	if (!m_render_mgr.startup(render_server_id, render_server_wan, render_wan_port, centreal_ip, centreal_port))
	{
		GetDlgItem(CloudRenderStart)->SetWindowText(_T("启动失败!!!"));
		return;
	}

}


void CMFCApplication1Dlg::OnStnClickedBitmap1()
{
	// TODO: 在此添加控件通知处理程序代码
}


HBRUSH CMFCApplication1Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
	{
		HBRUSH h;
		h = CreateSolidBrush(RGB(255, 255, 255));
		hbr = h;
		break;
	}
	default:
		break;
	}


	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
