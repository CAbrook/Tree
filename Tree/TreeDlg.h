
// TreeDlg.h: 头文件
//

#pragma once


// CTreeDlg 对话框
class CTreeDlg : public CDialogEx
{
// 构造
public:
	CTreeDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TREE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg
		void BinaryTree(BTree &t,int px,int py);
	void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CString test;
};
