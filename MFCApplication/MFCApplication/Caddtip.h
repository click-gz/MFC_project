#pragma once
#include "afxdialogex.h"


// Caddtip 对话框

class Caddtip : public CDialogEx
{
	DECLARE_DYNAMIC(Caddtip)

public:
	Caddtip(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Caddtip();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
