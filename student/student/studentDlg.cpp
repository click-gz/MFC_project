
// studentDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "student.h"
#include "studentDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <fstream>
#include <string>
#include <sstream>
#include<algorithm>
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


// CstudentDlg 对话框



CstudentDlg::CstudentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STUDENT_DIALOG, pParent)
	, m_numb(0)
	, m_score1(0)
	, m_score2(0)
	, m_score3(0)
	, m_score4(0)
	, m_score5(0)
	, m_score6(0)
	, m_course(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CstudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_numb);
	DDX_Text(pDX, IDC_EDIT2, m_score1);
	DDX_Text(pDX, IDC_EDIT3, m_score2);
	DDX_Text(pDX, IDC_EDIT4, m_score3);
	DDX_Text(pDX, IDC_EDIT5, m_score4);
	DDX_Text(pDX, IDC_EDIT6, m_score5);
	DDX_Text(pDX, IDC_EDIT7, m_score6);
	DDX_Control(pDX, IDC_LIST1, score_avg_sum);
	DDX_Control(pDX, IDC_LIST2, m_list);
	DDX_Control(pDX, IDC_LIST4, m_sortlist);
	DDX_Text(pDX, IDC_EDIT8, m_course);
	DDX_Control(pDX, IDC_LIST5, m_courselist);
}

BEGIN_MESSAGE_MAP(CstudentDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CstudentDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CstudentDlg::OnBnClickedButton2)
	
	ON_BN_CLICKED(IDC_BUTTON3, &CstudentDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CstudentDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CstudentDlg 消息处理程序

BOOL CstudentDlg::OnInitDialog()
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
		struct student inf = { atof(lineArray[0].c_str()), atof(lineArray[1].c_str()),
			atof(lineArray[2].c_str()),
			atof(lineArray[3].c_str()), atof(lineArray[4].c_str()) };
		studentlist.push_back(inf);
	}

	CString str[] = { TEXT("学号"), TEXT("总分"), TEXT("平均分") };

	for (int i = 0; i < 3; i++)
	{

		//设置表头  参数：1.索引 2.内容 3.对齐方式 4.列宽度
		m_list.InsertColumn(i, str[i], LVCFMT_LEFT, 73);
	}
	m_list.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CString str1[] = { TEXT("学号"), TEXT("科目一"), TEXT("科目二"), TEXT("科目三"), 
		TEXT("科目四"), TEXT("科目五"), TEXT("科目六"), TEXT("总分"), TEXT("平均分") };
	for (int i = 0; i < 9; i++)
	{

		//设置表头  参数：1.索引 2.内容 3.对齐方式 4.列宽度
		m_sortlist.InsertColumn(i, str1[i], LVCFMT_LEFT, 65.6);
	}
	m_sortlist.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT);
	m_sortlist.SetExtendedStyle(m_sortlist.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CString str2[] = { TEXT("学号"), TEXT("科目一"), TEXT("科目二"), TEXT("科目三"),
		TEXT("科目四"), TEXT("科目五"), TEXT("科目六"), TEXT("总分"), TEXT("平均分") };
	for (int i = 0; i < 9; i++)
	{

		//设置表头  参数：1.索引 2.内容 3.对齐方式 4.列宽度
		m_courselist.InsertColumn(i, str2[i], LVCFMT_LEFT, 75);
	}
	m_courselist.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT);
	m_courselist.SetExtendedStyle(m_sortlist.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CstudentDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CstudentDlg::OnPaint()
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
HCURSOR CstudentDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CstudentDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	struct student s = { m_numb, m_score1, m_score2, m_score3, m_score4, m_score5, m_score6 };
	studentlist.push_back(s);
	UpdateData(FALSE);
}


void CstudentDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_list.DeleteAllItems();
	for (int i = 0; i < studentlist.size(); i++)
	{
		double sum = 0;
		double avg = 0;
		CString code;
		code.Format(_T("%d"), studentlist[i].code);
		m_list.InsertItem(i, code);
		sum += (studentlist[i].score1 + studentlist[i].score2
			+ studentlist[i].score3 + studentlist[i].score4
			+ studentlist[i].score5 + studentlist[i].score6);
		CString score1;
		score1.Format(_T("%f"), sum);
		m_list.SetItemText(i, 1, score1);
		avg = sum / 6;
		CString avg1;
		avg1.Format(_T("%f"), avg);
		m_list.SetItemText(i, 2, avg1);

	}
	UpdateData(FALSE);
}



struct pro
{
	struct student s;
	double sum;
	double avg;
};
bool comp(const pro& a, const pro& b)
{
	return a.sum > b.sum;
}
void CstudentDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_sortlist.DeleteAllItems();
	
	std::vector<pro> prolist;
	for (int i = 0; i < studentlist.size(); i++)
	{
		double sum = 0;
		double avg = 0;
		sum += (studentlist[i].score1 + studentlist[i].score2
			+ studentlist[i].score3 + studentlist[i].score4
			+ studentlist[i].score5 + studentlist[i].score6);
		avg = sum / 6;
		struct pro p = {
			studentlist[i],
			sum,
			avg
		};
		prolist.push_back(p);
		
	}
	sort(prolist.begin(), prolist.end(), comp);

	for (int i = 0; i < prolist.size(); i++)
	{
		CString code;
		code.Format(_T("%d"), prolist[i].s.code);
		m_sortlist.InsertItem(i, code);
		
		CString score1;
		score1.Format(_T("%f"), prolist[i].s.score1);
		m_sortlist.SetItemText(i, 1, score1);
		CString score2;
		score2.Format(_T("%f"), prolist[i].s.score2);
		m_sortlist.SetItemText(i, 2, score2);
		CString score3;
		score3.Format(_T("%f"), prolist[i].s.score3);
		m_sortlist.SetItemText(i, 3, score3);
		CString score4;
		score4.Format(_T("%f"), prolist[i].s.score4);
		m_sortlist.SetItemText(i, 4, score4);
		CString score5;
		score5.Format(_T("%f"), prolist[i].s.score5);
		m_sortlist.SetItemText(i, 5, score5);
		CString score6;
		score6.Format(_T("%f"), prolist[i].s.score6);
		m_sortlist.SetItemText(i, 6, score6);
		CString score7;
		score7.Format(_T("%f"), prolist[i].sum);
		m_sortlist.SetItemText(i, 7, score7);
		CString score8;
		score8.Format(_T("%f"), prolist[i].avg);
		m_sortlist.SetItemText(i, 8, score8);
	}
	UpdateData(FALSE);
}


void CstudentDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	
	UpdateData(TRUE);
	m_courselist.DeleteAllItems();

	std::vector<pro> prolist;
	for (int i = 0; i < studentlist.size(); i++)
	{
		double sum = 0;
		double avg = 0;
		bool index = false;
		if (!m_course.Compare(_T("科目一")))
		{
			if (studentlist[i].score1 >= 90)
			{
				index = true;
			}
		}
		else if (!m_course.Compare(_T("科目二")))
		{
			if (studentlist[i].score2 >= 90)
			{
				index = true;
			}
		}
		else if (!m_course.Compare(_T("科目三")))
		{
			if (studentlist[i].score3 >= 90)
			{
				index = true;
			}
		}
		else if (!m_course.Compare(_T("科目四")))
		{
			if (studentlist[i].score4 >= 90)
			{
				index = true;
			}
		}
		else if (!m_course.Compare(_T("科目五")))
		{
			if (studentlist[i].score5 >= 90)
			{
				index = true;
			}
		}
		else if (!m_course.Compare(_T("科目六")))
		{
			if (studentlist[i].score6 >= 90)
			{
				index = true;
			}
		}
		else {
			continue;
		}
		if (index) {
			sum += (studentlist[i].score1 + studentlist[i].score2
				+ studentlist[i].score3 + studentlist[i].score4
				+ studentlist[i].score5 + studentlist[i].score6);
			avg = sum / 6;
			struct pro p = {
				studentlist[i],
				sum,
				avg
			};
			prolist.push_back(p);
		}
	}
		
	sort(prolist.begin(), prolist.end(), comp);

	for (int i = 0; i < prolist.size() && i < 5; i++)
	{
		CString code;
		code.Format(_T("%d"), prolist[i].s.code);
		m_courselist.InsertItem(i, code);

		CString score1;
		score1.Format(_T("%f"), prolist[i].s.score1);
		m_courselist.SetItemText(i, 1, score1);
		CString score2;
		score2.Format(_T("%f"), prolist[i].s.score2);
		m_courselist.SetItemText(i, 2, score2);
		CString score3;
		score3.Format(_T("%f"), prolist[i].s.score3);
		m_courselist.SetItemText(i, 3, score3);
		CString score4;
		score4.Format(_T("%f"), prolist[i].s.score4);
		m_courselist.SetItemText(i, 4, score4);
		CString score5;
		score5.Format(_T("%f"), prolist[i].s.score5);
		m_courselist.SetItemText(i, 5, score5);
		CString score6;
		score6.Format(_T("%f"), prolist[i].s.score6);
		m_courselist.SetItemText(i, 6, score6);
		CString score7;
		score7.Format(_T("%f"), prolist[i].sum);
		m_courselist.SetItemText(i, 7, score7);
		CString score8;
		score8.Format(_T("%f"), prolist[i].avg);
		m_courselist.SetItemText(i, 8, score8);
	}
	UpdateData(FALSE);
}
