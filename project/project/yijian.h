#pragma once
#include "afxdialogex.h"


// yijian 对话框

class yijian : public CDialogEx
{
	DECLARE_DYNAMIC(yijian)

public:
	yijian(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~yijian();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString yjcon;
	afx_msg void OnBnClickedButton1();
	CString yjname;
};
