
// MFCApplication1Dlg.h: 头文件
//

#pragma once
//#include <gdiplusbitmap.h>
//#include <gdiplusheaders.h>
#include <stdio.h>
#include <afxwin.h>
#include "afxwin.h"
#include "cmedia_rtc_server_mgr.h"

//class Bitmap;
// CMFCApplication1Dlg 对话框
class CMFCApplication1Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	CBitmap  m_bitmap;
 
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRenderserverstart();
	//afx_msg void OnEnChangelocalhost();
	//afx_msg void OnStnClickedserverstatus();
	afx_msg void OnBnClickedrtcserverstart();
	//afx_msg void OnBnClickedRenderserverstart2();
	afx_msg void OnBnClickedMediartcserverstart();
private:
	chen::cmedia_rtc_server_mgr		m_media_rtc_mgr;
};
