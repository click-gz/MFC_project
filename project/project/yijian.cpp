// yijian.cpp: 实现文件
//

#include "pch.h"
#include "project.h"
#include "afxdialogex.h"
#include "yijian.h"
#include "projectDlg.h"
#include <string>
#include <fstream>
#include <vector>
#include <sstream>


// yijian 对话框

IMPLEMENT_DYNAMIC(yijian, CDialogEx)

yijian::yijian(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, yjcon(_T(""))
	, yjname(_T(""))
{

}

yijian::~yijian()
{
}

void yijian::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
	DDX_Text(pDX, IDC_EDIT2, yjcon);
	DDX_Text(pDX, IDC_EDIT3, yjname);
}


BEGIN_MESSAGE_MAP(yijian, CDialogEx)
	ON_BN_CLICKED(IDOK, &yijian::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &yijian::OnBnClickedButton1)
END_MESSAGE_MAP()


// yijian 消息处理程序


void yijian::OnBnClickedOk()
{
	
}


void yijian::OnBnClickedButton1()
{
	UpdateData(TRUE);
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
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
			atoi(lineArray[3].c_str()), city , yjc};
		sfp.push_back(inf);
	}
	inFile.close();

	for (int i = 0; i < sfp.size(); i++)
	{
		
		if (!sfp[i].pname.Compare(yjname))
		{
			sfp[i].yj = yjcon;
			break;
		}
	}
	std::string fname = "data.csv";

	std::ofstream outFile(fname, std::ios::out);


	// ********写入两行数据*********
	setlocale(LC_ALL, "chs");

	for (int i = 0; i < sfp.size(); i++)
	{
		std::string str = CT2A(sfp[i].name.GetBuffer());
		std::string str1 = CT2A(sfp[i].pname.GetBuffer());
		std::string str2 = CT2A(sfp[i].city.GetBuffer());
		std::string str3 = CT2A(sfp[i].yj.GetBuffer());
		if (str3.length() == 0)
		{
			str3 = " ";
		}
		outFile << str << ','
			<< str1 << ','
			<< sfp[i].year << ','
			<< sfp[i].month << ','
			<< str2 << ','
			<< str3 << std::endl;
	}

	//数字需转为字符串进行写入,csv文件结束一行写入需要"\n"或者endl进行换行

	outFile.close();
	EndDialog(0);
}
