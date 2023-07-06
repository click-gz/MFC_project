// search.cpp: 实现文件
//

#include "pch.h"
#include "project.h"
#include "afxdialogex.h"
#include "search.h"
#include "projectDlg.h"
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

// search 对话框

IMPLEMENT_DYNAMIC(search, CDialogEx)

search::search(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, zname(_T(""))
	, smonth(0)
{

}

search::~search()
{
}

void search::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, zname);
	DDX_Text(pDX, IDC_EDIT2, smonth);
	DDX_Control(pDX, IDC_LIST1, alist);
}


BEGIN_MESSAGE_MAP(search, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &search::OnBnClickedButton1)
END_MESSAGE_MAP()


// search 消息处理程序


void search::OnBnClickedButton1()
{
	UpdateData(TRUE);
	for (int i = 0; i < 6; i++)
	{
		alist.DeleteColumn(0);
	}
	// TODO: 在此添加控件通知处理程序代码
	CString str[] = { TEXT("作者名"), TEXT("稿件名"), TEXT("年份"), TEXT("月份"), TEXT("省份"), TEXT("审稿意见") };

	for (int i = 0; i < 6; i++)
	{

		//设置表头  参数：1.索引 2.内容 3.对齐方式 4.列宽度
		alist.InsertColumn(i, str[i], LVCFMT_LEFT, 150);
	}
	alist.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT);
	alist.SetExtendedStyle(alist.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	std::vector<paper> sfp;
	std::ifstream inFile("data.csv");
	std::string lineStr;
	while (getline(inFile, lineStr)) //这里的循环是每次读取一整行的数据,把结果保存在lineStr中，lineStr是用逗号分割开的
	{
		//打印整行字符串
		/*cout << lineStr << endl;*/
		//将结果保存为二维表结构
		std::stringstream ss(lineStr); //这里stringstream是一个字符串流类型，用lineStr来初始化变量 ss
		std::string str;
		std::vector<std::string> lineArray;
		//按照逗号进行分割
		while (getline(ss, str, ',')) //getline每次把按照逗号分割之后的每一个字符串都保存在str中
		{
			lineArray.push_back(str); //这里将str保存在lineArray中
		}
		CString lname(lineArray[0].c_str());
		CString pname(lineArray[1].c_str());
		CString city(lineArray[4].c_str());
		CString yjc(lineArray[5].c_str());
		struct paper inf = { lname, pname, atoi(lineArray[2].c_str()),
			atoi(lineArray[3].c_str()), city , yjc };
		sfp.push_back(inf);
	}
	inFile.close();
	alist.DeleteAllItems();
	for (int i = 0, idx = 0; i < sfp.size(); i++)
	{

		if (!sfp[i].name.Compare(zname) && sfp[i].month == smonth)
		{
			alist.InsertItem(idx, sfp[i].pname);
			alist.SetItemText(idx, 1, sfp[i].pname);
			CString yy;
			yy.Format(_T("%d"), sfp[i].year);
			alist.SetItemText(idx, 2, yy);
			CString mm;
			mm.Format(_T("%d"), sfp[i].month);
			alist.SetItemText(idx, 3, mm);
			alist.SetItemText(idx, 4, sfp[i].city);
			alist.SetItemText(idx, 5, sfp[i].yj);

		}
	}
	UpdateData(FALSE);

}
