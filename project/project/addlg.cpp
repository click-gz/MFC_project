// addlg.cpp: 实现文件
//
#pragma once
#include "pch.h"
#include "project.h"
#include "afxdialogex.h"
#include "addlg.h"


// addlg 对话框

IMPLEMENT_DYNAMIC(addlg, CDialogEx)

addlg::addlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_name(_T(""))
	, m_pname(_T(""))
	, m_year(0)
	, m_month(0)
	, m_city(_T(""))
{

}

addlg::~addlg()
{
}

void addlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_pname);
	DDX_Text(pDX, IDC_EDIT3, m_year);
	DDX_Text(pDX, IDC_EDIT4, m_month);
	DDX_Text(pDX, IDC_EDIT5, m_city);
}


BEGIN_MESSAGE_MAP(addlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &addlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// addlg 消息处理程序


void addlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	EndDialog(0);
}
