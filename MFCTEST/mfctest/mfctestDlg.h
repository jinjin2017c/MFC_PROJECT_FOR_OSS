
// mfctestDlg.h : 头文件
//

#pragma once


// CmfctestDlg 对话框
class CmfctestDlg : public CDialogEx
{
// 构造
public:
	CRect m_rect;
	_RecordsetPtr m_pRecordset;
	_ConnectionPtr m_pConnection;
	CmfctestDlg(CWnd* pParent = NULL);	// 标准构造函数
	POINT Old;

// 对话框数据
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTEST_DIALOG };
	CString m_show1;
	CString m_show2;
	CString m_browse1;
	CString m_browse2;
//#endif

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
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnEnChangeMfceditbrowse1();
};
