
// MFCApplication1Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include <string>
#include <WinUser.h>


#define _CRT_SECURE_NO_WARNINGS

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


	
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(RenderServerStart, &CMFCApplication1Dlg::OnBnClickedRenderserverstart)
	//ON_EN_CHANGE(localhost, &CMFCApplication1Dlg::OnEnChangelocalhost)
END_MESSAGE_MAP()

// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	//return TRUE;
	CDialogEx::OnInitDialog();

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
	
	
	SetBackgroundColor(RGB(255, 255, 255)); // 将白色设置为透明色



	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	CWnd* pWnd = AfxGetMainWnd(); // 获取主窗口指针
	pWnd->SetWindowText(_T("RenderServer")); // 设置窗口标题
	 GetDlgItem(localhost_IP)->SetWindowText(_T("127.0.0.1"));
	GetDlgItem(wan_address)->SetWindowText(_T("127.0.0.1"));
	GetDlgItem(render_server_port)->SetWindowText(_T("9300"));

	GetDlgItem(signal_server_port)->SetWindowText(_T("9500"));

	GetDlgItem(min_port)->SetWindowText(_T("20000"));
	GetDlgItem(max_port)->SetWindowText(_T("30000"));

	GetDlgItem(rtc_time_out)->SetWindowText(_T("10000"));
	GetDlgItem(render_server_status)->SetWindowText(_T("未启动")); 
	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
	/*if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}*/
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
		CDialogEx::OnPaint();
	}


}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
#define  _CRT_SECURE_NO_WARNINGS
static FILE  * out_file_ptr = ::fopen("./mfc.log", "wb+");
void CMFCApplication1Dlg::OnBnClickedRenderserverstart()
{
	// TODO: 在此添加控件通知处理程序代码
	fprintf(out_file_ptr, "[%s][%d]\n", __FUNCTION__, __LINE__);
	fflush(out_file_ptr);
	CString str;
	GetDlgItem(localhost_IP)->GetWindowText(str);
	std::string pp = CT2A(str.GetString());
	fprintf(out_file_ptr, "[%s][%d][%s]\n", __FUNCTION__, __LINE__, pp.c_str());
	fflush(out_file_ptr);
	//GetDlgItem(wan_address)->SetWindowTextW(str);
	//GetDlgItem(render_server_status)->(_T(""));
	//将按钮修改为BS_OWNERDRAW风格，允许button采用自绘模式
	GetDlgItem(render_server_status)->SetWindowText(_T("启动..."));
	//GetDlgItem(RenderServerStart)->SetTextColor(RGB(255, 0, 0));
	//GetDlgItem(render_server_status)->SetTextColor(RGB(255, 0, 0));
	GetDlgItem(RenderServerStart)->SetWindowTextW(L"停止"); // 改变button上显示的文字
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
