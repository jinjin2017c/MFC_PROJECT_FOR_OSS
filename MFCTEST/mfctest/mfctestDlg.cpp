
// mfctestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Python.h"
#include "mfctest.h"
#include "mfctestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CmfctestDlg �Ի���



CmfctestDlg::CmfctestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCTEST_DIALOG, pParent)
{
	m_show1 = _T("");
	m_show2 = _T("");
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfctestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_show1);
	DDX_Text(pDX, IDC_EDIT2, m_show2);
}

BEGIN_MESSAGE_MAP(CmfctestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CmfctestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CmfctestDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CmfctestDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CmfctestDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON3, &CmfctestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CmfctestDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CmfctestDlg::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE1, &CmfctestDlg::OnEnChangeMfceditbrowse1)
END_MESSAGE_MAP()


// CmfctestDlg ��Ϣ�������

BOOL CmfctestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	(CButton *)GetDlgItem(IDC_BUTTON3)->ShowWindow(FALSE);
	(CButton *)GetDlgItem(IDC_BUTTON4)->ShowWindow(FALSE);
	(CButton *)GetDlgItem(IDC_BUTTON5)->ShowWindow(FALSE);
	(CButton *)GetDlgItem(IDC_MFCEDITBROWSE1)->ShowWindow(FALSE);
	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	GetClientRect(&m_rect);

	m_pConnection.CreateInstance(__uuidof(Connection));
	try
	{
		// �򿪱���Access��Database1.mdb
		m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=db.mdb", "", "", adModeUnknown);

	}
	catch (_com_error e)
	{
		AfxMessageBox("���ݿ�����ʧ�ܣ�ȷ�����ݿ�demo.mdb�Ƿ��ڵ�ǰ·����!");
		//		return FALSE;
	}
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	try
	{

		m_pRecordset->Open("SELECT name,mima FROM test",                // ��ѯDemo���������ֶ�
			_variant_t((IDispatch*)m_pConnection, true),	            // ��ȡ��ӿ��IDispatchָ��
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch (_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CmfctestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmfctestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CmfctestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmfctestDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	_variant_t vName, vAge;
	CString sname, smima;
	//HWND hwnd;


	try
	{
		m_pRecordset->MoveFirst();
		//	UpdateData(TRUE);
		if (!m_pRecordset->adoEOF)
		{
			//UpdateData(TRUE);
			//			m_pRecordset->MoveFirst();
			while (!m_pRecordset->adoEOF)
			{
				UpdateData(TRUE);
				vName = m_pRecordset->GetCollect("name");
				vAge = m_pRecordset->GetCollect("mima");

				sname = (LPCTSTR)(_bstr_t)vName;
				smima = (LPCTSTR)(_bstr_t)vAge;
				//	UpdateData(TRUE);
				if ((_tcscmp(sname, m_show1) == 0) && (_tcscmp(smima, m_show2) == 0))
				{
					MessageBox("��ϲ��ɹ���½");
					(CButton *)GetDlgItem(IDC_BUTTON1)->ShowWindow(FALSE);
					(CButton *)GetDlgItem(IDC_BUTTON2)->ShowWindow(FALSE);
					(CButton *)GetDlgItem(IDC_EDIT1)->ShowWindow(FALSE);
					(CButton *)GetDlgItem(IDC_EDIT2)->ShowWindow(FALSE);
					(CButton *)GetDlgItem(IDC_STATIC1)->ShowWindow(FALSE);
					(CButton *)GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
					(CButton *)GetDlgItem(IDC_BUTTON3)->ShowWindow(TRUE);
					(CButton *)GetDlgItem(IDC_BUTTON4)->ShowWindow(TRUE);
					(CButton *)GetDlgItem(IDC_BUTTON5)->ShowWindow(TRUE);
					(CButton *)GetDlgItem(IDC_MFCEDITBROWSE1)->ShowWindow(TRUE);
					return;
				}

				m_pRecordset->MoveNext();
			}
			MessageBox("��������ȷ���û��������롣Ҳ���Ե��ע��");
			return;
		}

	}

	catch (_com_error &e)
	{
		AfxMessageBox(e.Description());
	}
}


void CmfctestDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	variant_t vName, vAge;
	CString sname, smima;


	try
	{
		//UpdateData(TRUE);
		if (!m_pRecordset->adoEOF)
		{
			//UpdateData(TRUE);
			m_pRecordset->MoveFirst();
			while (!m_pRecordset->adoEOF)
			{
				UpdateData(TRUE);
				vName = m_pRecordset->GetCollect("name");
				vAge = m_pRecordset->GetCollect("mima");

				sname = (LPCTSTR)(_bstr_t)vName;
				smima = (LPCTSTR)(_bstr_t)vAge;
				if ((_tcscmp(sname, m_show1) == 0) && (_tcscmp(smima, m_show2) == 0))
				{
					MessageBox("��������ȷ���û��������롣Ҳ���Ե��ע��");
				}

				m_pRecordset->MoveNext();
			}
			//	MessageBox("��������ȷ���û��������롣Ҳ���Ե��ע��");
		}

	}

	catch (_com_error &e)
	{
		AfxMessageBox(e.Description());
	}

	//UpdateData(TRUE);

	if ((m_show2 == "") && (m_show1 == ""))
	{
		AfxMessageBox("���������벻��Ϊ��");
		return;
	}

	else
	{
		try
		{
			// д����ֶ�ֵ
			m_pRecordset->AddNew();
			m_pRecordset->PutCollect("name", _variant_t(m_show1));
			m_pRecordset->PutCollect("mima", _variant_t(m_show2));

			m_pRecordset->Update();

			AfxMessageBox("ע��ɹ�!");
			m_show1 = "";
			m_show2 = "";
			UpdateData(FALSE);

		}
		catch (_com_error *e)
		{
			AfxMessageBox(e->ErrorMessage());
		}
	}
}


void CmfctestDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmfctestDlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmfctestDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Py_Initialize();

	PyObject *obj = Py_BuildValue("s", "list_object.py");

	FILE *fp = _Py_fopen_obj(obj, "r+");

	if (fp == NULL)

		return;

	PyRun_SimpleFile(fp, "list_object.py");
	Py_Finalize();
	return;
}


void CmfctestDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Py_Initialize();

	PyObject *obj = Py_BuildValue("s", "bucket_put_object.py");

	FILE *fp = _Py_fopen_obj(obj, "r+");

	if (fp == NULL)

		return;

	PyRun_SimpleFile(fp, "bucket_put_object.py");
	Py_Finalize();
	MessageBox("�ϴ��ɹ�");
	return;
}


void CmfctestDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Py_Initialize();

	PyObject *obj = Py_BuildValue("s", "bucket_get_object_to_file.py");

	FILE *fp = _Py_fopen_obj(obj, "r+");

	if (fp == NULL)

		return;

	PyRun_SimpleFile(fp, "bucket_get_object_to_file.py");
	Py_Finalize();
	MessageBox("���سɹ�");
	return;
}


void CmfctestDlg::OnEnChangeMfceditbrowse1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
