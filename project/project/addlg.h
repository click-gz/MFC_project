#pragma once
#include "afxdialogex.h"


// addlg 对话框

class addlg : public CDialogEx
{
	DECLARE_DYNAMIC(addlg)

public:
	addlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~addlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedButton1();
	CString m_name;
	CString m_pname;
	int m_year;
	int m_month;
	CString m_city;
};
