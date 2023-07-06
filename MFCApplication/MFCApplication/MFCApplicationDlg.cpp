
// MFCApplicationDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication.h"
#include "MFCApplicationDlg.h"
#include "afxdialogex.h"
#include "Caddtip.h"
#include "paixuzhanshi.h"

#include<algorithm>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>


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


// CMFCApplicationDlg 对话框



CMFCApplicationDlg::CMFCApplicationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION_DIALOG, pParent)
	, m_pname(_T("未知"))
	, m_lou(0)
	, m_year(0)
	, m_month(0)
	, m_num(0)
	, m_askname(_T("未知"))
	, m_askmonth(0)
	, m_ansnum(0)
	, m_askyear(0)
	, m_asklou(0)
	, m_asklou_year(0)
	, m_asklou_smonth(0)
	, m_asklou_emonth(0)
	, m_reslou_num(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_pname);
	DDX_Text(pDX, IDC_EDIT2, m_lou);
	DDX_Text(pDX, IDC_EDIT3, m_year);
	DDX_Text(pDX, IDC_EDIT4, m_month);
	DDX_Text(pDX, IDC_EDIT5, m_num);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT6, m_askname);
	DDX_Text(pDX, IDC_EDIT7, m_askmonth);
	DDX_Text(pDX, IDC_EDIT8, m_ansnum);
	DDX_Text(pDX, IDC_EDIT13, m_askyear);
	DDX_Text(pDX, IDC_EDIT9, m_asklou);
	DDX_Text(pDX, IDC_EDIT14, m_asklou_year);
	DDX_Text(pDX, IDC_EDIT10, m_asklou_smonth);
	DDX_Text(pDX, IDC_EDIT11, m_asklou_emonth);
	DDX_Text(pDX, IDC_EDIT12, m_reslou_num);
}

BEGIN_MESSAGE_MAP(CMFCApplicationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT2, &CMFCApplicationDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplicationDlg::OnBnClickedButton1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CMFCApplicationDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplicationDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT13, &CMFCApplicationDlg::OnEnChangeEdit13)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplicationDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplicationDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CMFCApplicationDlg 消息处理程序

BOOL CMFCApplicationDlg::OnInitDialog()
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
	//列表控件使用
	CString str[] = { TEXT("用户名"), TEXT("楼栋号"), TEXT("抄表日期-年"), TEXT("抄表日期-月"), TEXT("电表数") };

	for (int i = 0; i < 5; i++)
	{
		
		//设置表头  参数：1.索引 2.内容 3.对齐方式 4.列宽度
		m_list.InsertColumn(i, str[i], LVCFMT_LEFT, 150);
	}

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
		CString pname(lineArray[0].c_str());
		std::cout << pname << std::endl;
		struct Inform inf = { pname, atoi(lineArray[1].c_str()),atoi(lineArray[2].c_str()), 
			atoi(lineArray[3].c_str()), atoi(lineArray[4].c_str()) };
		infolist.push_back(inf); 
	}
	for (int i = 0; i < infolist.size(); i++)
	{
		m_list.InsertItem(i, infolist[i].m_pname);
		CString lou;
		lou.Format(_T("%d"), infolist[i].m_lou);
		m_list.SetItemText(i, 1, lou);
		CString nian;
		nian.Format(_T("%d"), infolist[i].m_year);
		m_list.SetItemText(i, 2, nian);
		CString yue;
		yue.Format(_T("%d"), infolist[i].m_month);
		m_list.SetItemText(i, 3, yue);
		CString dian;
		dian.Format(_T("%lf"), infolist[i].m_num);
		m_list.SetItemText(i, 4, dian);
	}
	//设置列表网格线
	//LVS_EX_FULLROWSELECT整行选中
	//LVS_EX_GRIDLINES显示网格线
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplicationDlg::OnPaint()
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
HCURSOR CMFCApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplicationDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplicationDlg::OnBnClickedButton1()
{
	INT_PTR nRes; // 用于保存DoModal函数的返回值


	Caddtip tipDlg; // 构造对话框类CTipDlg的实例

	nRes = tipDlg.DoModal(); // 弹出对话框

	//if (IDCANCEL == nRes) // 判断对话框退出后返回值是否为IDCANCEL，如果是则return，否则继续向下执行

	//	return;


	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	// 将被加数和加数的加和赋值给m_editSum
	infolist.push_back({ m_pname, m_lou, m_year, m_month, m_num});

	CString str[] = { TEXT("用户名"), TEXT("楼栋号"), TEXT("抄表日期-年"), TEXT("抄表日期-月"), TEXT("电表数") };

	for (int i = 0; i < 5; i++)
	{

		//设置表头  参数：1.索引 2.内容 3.对齐方式 4.列宽度
		m_list.InsertColumn(i, str[i], LVCFMT_LEFT, 150);
	}
	
	/*m_list.InsertItem(infolist.size()-1, infolist[infolist.size() - 1].m_pname);
	CString lou;
	lou.Format(_T("%d"), infolist[infolist.size() - 1].m_lou);
	m_list.SetItemText(infolist.size() - 1, 1, lou);
	CString nian;
	nian.Format(_T("%d"), infolist[infolist.size() - 1].m_year);
	m_list.SetItemText(infolist.size() - 1, 2, nian);
	CString yue;
	yue.Format(_T("%d"), infolist[infolist.size() - 1].m_month);
	m_list.SetItemText(infolist.size() - 1, 3, yue);
	CString dian;
	dian.Format(_T("%lf"), infolist[infolist.size() - 1].m_num);
	m_list.SetItemText(infolist.size() - 1, 4, dian);*/
	m_list.DeleteAllItems();
	for (int i = 0; i < infolist.size(); i++)
	{
		m_list.InsertItem(i, infolist[i].m_pname);
		CString lou;
		lou.Format(_T("%d"), infolist[i].m_lou);
		m_list.SetItemText(i, 1, lou);
		CString nian;
		nian.Format(_T("%d"), infolist[i].m_year);
		m_list.SetItemText(i, 2, nian);
		CString yue;
		yue.Format(_T("%d"), infolist[i].m_month);
		m_list.SetItemText(i, 3, yue);
		CString dian;
		dian.Format(_T("%lf"), infolist[i].m_num);
		m_list.SetItemText(i, 4, dian);
	}


	// 根据各变量的值更新相应的控件。和的编辑框会显示m_editSum的值

	UpdateData(FALSE);
}


void CMFCApplicationDlg::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CMFCApplicationDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_ansnum = 0;
	for (int i = 0; i < infolist.size(); i++)
	{
		if (infolist[i].m_pname == m_askname && infolist[i].m_month == m_askmonth &&
			infolist[i].m_year == m_askyear)
		{
			m_ansnum += infolist[i].m_num;
		}
	}
	UpdateData(FALSE);
}


void CMFCApplicationDlg::OnEnChangeEdit13()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplicationDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_reslou_num = 0;
	for (int i = 0; i < infolist.size(); i++)
	{
		if (infolist[i].m_lou == m_asklou && infolist[i].m_year == m_asklou_year
			&& (infolist[i].m_month >= m_asklou_smonth && infolist[i].m_month <= m_asklou_emonth))
		{
			m_reslou_num += infolist[i].m_num;
		}
	}
	UpdateData(FALSE);
}
struct px
{
	CString name;
	double num ;
};
bool comp(const px& a, const px& b)
{
	return a.num > b.num;
}
void CMFCApplicationDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	
	CString str[] = { TEXT("用户名"),TEXT("电表总数"), TEXT(""),
		TEXT(""),  TEXT("") };

	for (int i = 0; i < 5; i++)
	{

		//	//设置表头  参数：1.索引 2.内容 3.对齐方式 4.列宽度
		m_list.InsertColumn(i, str[i], LVCFMT_LEFT, 150);
	}
	
	std::vector<px> pxlist;
	
	for (int i = 0; i < infolist.size(); i++)
	{
		bool flag = false;
		for (int j = 0; j < pxlist.size(); j++)
		{
			if (pxlist[j].name == infolist[i].m_pname)
			{
				pxlist[j].num += infolist[i].m_num;
				flag = true;
			}
		}
		if (!flag)
		{
			struct px pxd = { infolist[i].m_pname , infolist[i].m_num };
			pxlist.push_back(pxd);
		}
	};
	
	sort(pxlist.begin(), pxlist.end(), comp);
	m_list.DeleteAllItems();
	for (int i = 0; i < pxlist.size(); i++)
	{
		m_list.InsertItem(i, pxlist[i].name);
		CString lou;
		lou.Format(_T("%lf"), pxlist[i].num);
		m_list.SetItemText(i, 1, lou);
	}
	
	UpdateData(FALSE);
}
