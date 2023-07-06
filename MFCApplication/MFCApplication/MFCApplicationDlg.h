﻿
// MFCApplicationDlg.h: 头文件
//

#pragma once
#include <vector>


struct Inform
{
public:
	CString m_pname;
	int m_lou;
	int m_year;
	int m_month;
	double m_num;
};

// CMFCApplicationDlg 对话框
class CMFCApplicationDlg : public CDialogEx
{
// 构造
public:
	CMFCApplicationDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit2();
	CString m_pname;
	int m_lou;
	int m_year;
	int m_month;
	double m_num;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_list;
	std::vector<Inform> infolist;
	CString m_askname;
	int m_askmonth;
	double m_ansnum;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeEdit13();
	int m_askyear;
	int m_asklou;
	int m_asklou_year;
	int m_asklou_smonth;
	int m_asklou_emonth;
	double m_reslou_num;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
