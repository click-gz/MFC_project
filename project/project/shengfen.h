#pragma once
#include "afxdialogex.h"


// shengfen 对话框

class shengfen : public CDialogEx
{
	DECLARE_DYNAMIC(shengfen)

public:
	shengfen(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~shengfen();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_sflist;
	afx_msg void OnBnClickedButton1();
};
