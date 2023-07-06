#pragma once
#include "afxdialogex.h"


// search 对话框

class search : public CDialogEx
{
	DECLARE_DYNAMIC(search)

public:
	search(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~search();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString zname;
	int smonth;
	afx_msg void OnBnClickedButton1();
	CListCtrl alist;
};
