
// mfctestDlg.h : ͷ�ļ�
//

#pragma once


// CmfctestDlg �Ի���
class CmfctestDlg : public CDialogEx
{
// ����
public:
	CRect m_rect;
	_RecordsetPtr m_pRecordset;
	_ConnectionPtr m_pConnection;
	CmfctestDlg(CWnd* pParent = NULL);	// ��׼���캯��
	POINT Old;

// �Ի�������
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTEST_DIALOG };
	CString m_show1;
	CString m_show2;
	CString m_browse1;
	CString m_browse2;
//#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
