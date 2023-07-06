// shengfen.cpp: 实现文件
//
#pragma once
#include "pch.h"
#include "project.h"
#include "afxdialogex.h"
#include "shengfen.h"
#include "projectDlg.h"
#include <fstream>
#include <sstream>
#include <string>

// shengfen 对话框

IMPLEMENT_DYNAMIC(shengfen, CDialogEx)

shengfen::shengfen(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

shengfen::~shengfen()
{
}

void shengfen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_sflist);
}


BEGIN_MESSAGE_MAP(shengfen, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &shengfen::OnBnClickedButton1)
END_MESSAGE_MAP()


// shengfen 消息处理程序

struct sfpaper
{
	CString name;
	int num;
};

void shengfen::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str[] = { TEXT("省份"), TEXT("总发表数") };

	for (int i = 0; i < 2; i++)
	{

		//设置表头  参数：1.索引 2.内容 3.对齐方式 4.列宽度
		m_sflist.InsertColumn(i, str[i], LVCFMT_LEFT, 150);
	}
	m_sflist.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT);
	m_sflist.SetExtendedStyle(m_sflist.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_sflist.DeleteAllItems();
	std::vector<sfpaper> sp;
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
		CString name(lineArray[0].c_str());
		CString pname(lineArray[1].c_str());
		CString city(lineArray[4].c_str());
		struct paper inf = { name, pname, atoi(lineArray[2].c_str()),
			atoi(lineArray[3].c_str()), city };
		sfp.push_back(inf);
	}
	inFile.close();


	for (int i = 0; i < sfp.size(); i++)
	{
		bool t = true;
		for (int j = 0; j < sp.size(); j++)
		{
			if (sp[j].name == sfp[i].city)
			{
				sp[j].num += 1;
				t = false;
				break;
			}
		}
		if (t)
		{
			sfpaper p = { sfp[i].city, 1 };
			sp.push_back(p);
		}
	}
	for (int i = 0; i < sp.size(); i++)
	{
		m_sflist.InsertItem(i, sp[i].name);
		CString code;
		code.Format(_T("%d"), sp[i].num);
		m_sflist.SetItemText(i, 1, code);
	}
	UpdateData(FALSE);
}
