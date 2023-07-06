// paixuzhanshi.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication.h"
#include "afxdialogex.h"
#include "paixuzhanshi.h"


// paixuzhanshi 对话框

IMPLEMENT_DYNAMIC(paixuzhanshi, CDialogEx)

paixuzhanshi::paixuzhanshi(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{
	

}

paixuzhanshi::~paixuzhanshi()
{
}

void paixuzhanshi::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, paixu);

}


BEGIN_MESSAGE_MAP(paixuzhanshi, CDialogEx)
	ON_COMMAND(IDD_DIALOG2, &paixuzhanshi::OnIddDialog2)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// paixuzhanshi 消息处理程序


void paixuzhanshi::OnIddDialog2()
{
	// TODO: 在此添加命令处理程序代码
	CString str[] = { TEXT("用户名"), TEXT("抄表日期-月"), TEXT("电表总数") };

	for (int i = 0; i < 3; i++)
	{

		//设置表头  参数：1.索引 2.内容 3.对齐方式 4.列宽度
		paixu.InsertColumn(i, str[i], LVCFMT_LEFT, 10);
	}
}
void paixuzhanshi::updatelist()
{
	// TODO: 在此添加命令处理程序代码
	
	CString str[] = { TEXT("用户名"), TEXT("抄表日期-月"), TEXT("电表总数") };

	for (int i = 0; i < 3; i++)
	{

	//	//设置表头  参数：1.索引 2.内容 3.对齐方式 4.列宽度
		paixu.InsertColumn(i, str[i], LVCFMT_LEFT, 10);
	}
	
}



int paixuzhanshi::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CString str[] = { TEXT("用户名"), TEXT("抄表日期-月"), TEXT("电表总数") };

	for (int i = 0; i < 3; i++)
	{

		//	//设置表头  参数：1.索引 2.内容 3.对齐方式 4.列宽度
		paixu.InsertColumn(i, str[i], LVCFMT_LEFT, 10);
	}

	return 0;
}
