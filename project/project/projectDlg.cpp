
// projectDlg.cpp: 实现文件
//
#pragma once
#include "pch.h"
#include "framework.h"
#include "project.h"
#include "projectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "addlg.h"
#include "shengfen.h"
#include <fstream>
#include <sstream>
#include "yijian.h"
#include "search.h"
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CprojectDlg 对话框



CprojectDlg::CprojectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CprojectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CprojectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CprojectDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CprojectDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CprojectDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CprojectDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CprojectDlg 消息处理程序

BOOL CprojectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CFont font;
	font.CreatePointFont(400, L"行楷"); //120表示12号字体
		
	GetDlgItem(IDC_STATIC)->SetFont(&font);

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
		CString yj(lineArray[5].c_str());
		struct paper inf = { name, pname, atoi(lineArray[2].c_str()),
			atoi(lineArray[3].c_str()), city , yj};
		paperlist.push_back(inf);
	}
	inFile.close();

	// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CprojectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CprojectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CprojectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CprojectDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	addlg addw;
	addw.DoModal();
	struct paper p = { addw.m_name, addw.m_pname, addw.m_year, addw.m_month, addw.m_city };
	paperlist.push_back(p);
	std::string fname = "data.csv";

	std::ofstream outFile(fname, std::ios::out);


	// ********写入两行数据*********
	setlocale(LC_ALL, "chs");

	for (int i = 0; i < paperlist.size(); i++)
	{
		std::string str = CT2A(paperlist[i].name.GetBuffer());
		std::string str1 = CT2A(paperlist[i].pname.GetBuffer());
		std::string str2 = CT2A(paperlist[i].city.GetBuffer());
		std::string str3 = CT2A(paperlist[i].yj.GetBuffer());
		if (str3.length() == 0)
		{
			str3 = " ";
		}
		outFile << str << ','
			<< str1 << ','
			<< paperlist[i].year << ','
			<< paperlist[i].month << ','
			<< str2 << ','
			<< str3 << std::endl;
	}

	//数字需转为字符串进行写入,csv文件结束一行写入需要"\n"或者endl进行换行

	outFile.close();
}


void CprojectDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	shengfen sfw;
	sfw.DoModal();

}


void CprojectDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	yijian yj;
	yj.DoModal();
}


void CprojectDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	search sc;
	sc.DoModal();
}
