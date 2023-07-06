#pragma once
#include "afxdialogex.h"
#include<vector>
#include"MFCApplicationDlg.h"

// paixuzhanshi 对话框

class paixuzhanshi : public CDialogEx
{
	DECLARE_DYNAMIC(paixuzhanshi)

public:
	paixuzhanshi(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~paixuzhanshi();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl paixu;
	std::vector<Inform> infollist;
	afx_msg void OnIddDialog2();
	void updatelist();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
