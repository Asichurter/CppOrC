
// CalculatorMFCDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "CalculatorMFC.h"
#include "CalculatorMFCDlg.h"
#include "afxdialogex.h"
#include "Calculate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CCalculatorMFCDlg 对话框



CCalculatorMFCDlg::CCalculatorMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATORMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCalculatorMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCalculatorMFCDlg::Calculate)
END_MESSAGE_MAP()


// CCalculatorMFCDlg 消息处理程序

BOOL CCalculatorMFCDlg::OnInitDialog()
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
	GetDlgItem(IDC_TEXT1)->SetWindowText("输入你想要计算的等式");
	GetDlgItem(IDC_TEXT2)->SetWindowText("");
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCalculatorMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCalculatorMFCDlg::OnPaint()
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
HCURSOR CCalculatorMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCalculatorMFCDlg::Calculate()
{
	BOOL a=true;
	CEdit* pBoxOne;
	pBoxOne = (CEdit*)GetDlgItem(IDC_EDIT1);
	CString str;
	pBoxOne->GetWindowText(str);
	double t = 0;
	try
	{
		t = makeCalclute(str.GetBuffer());
	}
	catch (int t)
	{
	if (t == 0)
		GetDlgItem(IDC_TEXT2)->SetWindowText("符号多余！");
	if (t == 1)
		GetDlgItem(IDC_TEXT2)->SetWindowText("数多余！");
	if (t == 2)
		GetDlgItem(IDC_TEXT2)->SetWindowText("除0错误！");
	if (t == 3)
		GetDlgItem(IDC_TEXT2)->SetWindowText("字符括号错误!");
		a = FALSE;
	}

	str.Format(_T("%f"), t);
	if(a)
	GetDlgItem(IDC_TEXT2)->SetWindowText(str);
	str.ReleaseBuffer();
	// TODO: 在此添加控件通知处理程序代码
}
