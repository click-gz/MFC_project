// Caddtip.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication.h"
#include "afxdialogex.h"
#include "Caddtip.h"


// Caddtip 对话框

IMPLEMENT_DYNAMIC(Caddtip, CDialogEx)

Caddtip::Caddtip(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

Caddtip::~Caddtip()
{
}

void Caddtip::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Caddtip, CDialogEx)
END_MESSAGE_MAP()


// Caddtip 消息处理程序
