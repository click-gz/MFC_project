
// studentDlg.h: 头文件
//

#pragma once
#include <vector>
struct student
{
	int code;
	double score1;
	double score2;
	double score3;
	double score4;
	double score5;
	double score6;
};
// CstudentDlg 对话框
class CstudentDlg : public CDialogEx
{
// 构造
public:
	CstudentDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDENT_DIALOG };
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
	int m_numb;
	double m_score1;
	double m_score2;
	double m_score3;
	double m_score4;
	double m_score5;
	double m_score6;
	afx_msg void OnBnClickedButton1();
	std::vector<student> studentlist;
	afx_msg void OnBnClickedButton2();
	CListCtrl score_avg_sum;
	CListCtrl m_list;
	CListCtrl m_sortlist;
	afx_msg void OnBnClickedButton3();
	CString m_course;
	CListCtrl m_courselist;
	afx_msg void OnBnClickedButton4();
};
