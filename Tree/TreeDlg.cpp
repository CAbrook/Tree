
// TreeDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Tree.h"
#include "TreeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define PI 3.1415926
using namespace std;

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


// CTreeDlg 对话框



CTreeDlg::CTreeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TREE_DIALOG, pParent)
	, test(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTreeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTreeDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTreeDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CTreeDlg 消息处理程序

BOOL CTreeDlg::OnInitDialog()
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
	CEdit* FirstStr = (CEdit*)GetDlgItem(IDC_EDIT1);
	CEdit* MidStr = (CEdit*)GetDlgItem(IDC_EDIT2);
	FirstStr->SetWindowTextW(L"ABDECF");
	MidStr->SetWindowTextW(L"DBEAFC");
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTreeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTreeDlg::OnPaint()
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
HCURSOR CTreeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Repeat(char* c1,char* c2,int len)
{
	
}

void CreateBinaryTree(BTree &tree, CString First, CString Mid)
{
	if (First.GetLength() == 0)
	{
		tree = NULL;
		return;
	}
	char root = First.GetAt(0);
	CString LMstr = Mid.Left(Mid.Find(root));
	CString RMstr = Mid.Right(Mid.Find(root));
	CString LFstr = First.Mid(1, LMstr.GetLength());
	CString RFstr = First.Mid(1+LMstr.GetLength());
	tree = (BTree)malloc(sizeof(BNode));

	if (tree != NULL)
	{
		tree->data = root;
		CreateBinaryTree(tree->lchild, LFstr, LMstr);
		CreateBinaryTree(tree->rchild, RFstr, RMstr);
	}
}

static int j = 0;
int i = 0;
int p;

void CTreeDlg::BinaryTree(BTree &t, int px, int py)
{
	CStatic *test = (CStatic*)GetDlgItem(IDC_STATIC1);
	if (t != NULL)
	{
		CRect rect(px, py, px + 80, py + 20);
		CStatic *showRoot = new CStatic();
		showRoot->Create((CString)t->data, WS_CHILD, rect, this, 7000 + j);
		showRoot->ShowWindow(SW_SHOW);
		UpdateWindow();
		j++;
		if (t->lchild != NULL)
		{
			i++;
			HDC hdc;
			hdc = ::GetDC(m_hWnd);
			MoveToEx(hdc, px, py + 20, NULL);
			for (int t = 1; t < 10; t++)
			{
				p = (350 - 100 * i) / 10;
				LineTo(hdc, px - p * t, py + 20 + 15 * t);
				Sleep(100);
			}
			::ReleaseDC(m_hWnd, hdc);
			BinaryTree(t->lchild, px - 350 + 100 * i, py+150);
			i--;
		}

		if (t->rchild != NULL )
		{
			i++;
			HDC hdc;
			hdc = ::GetDC(m_hWnd);
			MoveToEx(hdc, px, py+20, NULL);
			for (int t = 1; t < 10; t++)
			{
				p = (350 - 100 * i) / 10;
				LineTo(hdc, px + p * t, py + 20 + 15 * t);
				Sleep(100);
			}
			::ReleaseDC(m_hWnd, hdc);
			BinaryTree(t->rchild, px+350 - 100 * i, py+150);
			i--;
		}
	}
}

void CTreeDlg::OnBnClickedButton1()
{
	CString mid, first;
	CEdit* FirstStr = (CEdit*)GetDlgItem(IDC_EDIT1);
	CEdit* MidStr = (CEdit*)GetDlgItem(IDC_EDIT2);
	FirstStr->GetWindowText(first);
	MidStr->GetWindowText(mid);
	BTree B;
	CreateBinaryTree(B, first, mid);
	BinaryTree(B,750,100);
	if (first.GetLength() != mid.GetLength() || first.IsEmpty() || mid.IsEmpty())
	{
		MessageBox(_T("输入序列不正确！"));
	}

}


void CTreeDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	Invalidate();
	CStatic *move = new CStatic;
	for (int i = 0; i < j; i++)
	{
		GetDlgItem(7000 + i)->DestroyWindow();
	}
	j = 0;
}
