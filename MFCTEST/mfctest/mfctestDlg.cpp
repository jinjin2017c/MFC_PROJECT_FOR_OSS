
// mfctestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Python.h"
#include "mfctest.h"
#include "mfctestDlg.h"
#include "afxdialogex.h"

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


// CmfctestDlg 对话框



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


// CmfctestDlg 消息处理程序

BOOL CmfctestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	(CButton *)GetDlgItem(IDC_BUTTON3)->ShowWindow(FALSE);
	(CButton *)GetDlgItem(IDC_BUTTON4)->ShowWindow(FALSE);
	(CButton *)GetDlgItem(IDC_BUTTON5)->ShowWindow(FALSE);
	(CButton *)GetDlgItem(IDC_MFCEDITBROWSE1)->ShowWindow(FALSE);
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetClientRect(&m_rect);

	m_pConnection.CreateInstance(__uuidof(Connection));
	try
	{
		// 打开本地Access库Database1.mdb
		m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=db.mdb", "", "", adModeUnknown);

	}
	catch (_com_error e)
	{
		AfxMessageBox("数据库连接失败，确认数据库demo.mdb是否在当前路径下!");
		//		return FALSE;
	}
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	try
	{

		m_pRecordset->Open("SELECT name,mima FROM test",                // 查询Demo表中所有字段
			_variant_t((IDispatch*)m_pConnection, true),	            // 获取库接库的IDispatch指针
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch (_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmfctestDlg::OnPaint()
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
HCURSOR CmfctestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmfctestDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
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
					MessageBox("恭喜你成功登陆");
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
			MessageBox("请输入正确的用户名和密码。也可以点击注册");
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
	// TODO: 在此添加控件通知处理程序代码
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
					MessageBox("请输入正确的用户名和密码。也可以点击注册");
				}

				m_pRecordset->MoveNext();
			}
			//	MessageBox("请输入正确的用户名和密码。也可以点击注册");
		}

	}

	catch (_com_error &e)
	{
		AfxMessageBox(e.Description());
	}

	//UpdateData(TRUE);

	if ((m_show2 == "") && (m_show1 == ""))
	{
		AfxMessageBox("姓名和密码不能为空");
		return;
	}

	else
	{
		try
		{
			// 写入各字段值
			m_pRecordset->AddNew();
			m_pRecordset->PutCollect("name", _variant_t(m_show1));
			m_pRecordset->PutCollect("mima", _variant_t(m_show2));

			m_pRecordset->Update();

			AfxMessageBox("注册成功!");
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
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmfctestDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmfctestDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	Py_Initialize();

	PyObject *obj = Py_BuildValue("s", "bucket_put_object.py");

	FILE *fp = _Py_fopen_obj(obj, "r+");

	if (fp == NULL)

		return;

	PyRun_SimpleFile(fp, "bucket_put_object.py");
	Py_Finalize();
	MessageBox("上传成功");
	return;
}


void CmfctestDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	Py_Initialize();

	PyObject *obj = Py_BuildValue("s", "bucket_get_object_to_file.py");

	FILE *fp = _Py_fopen_obj(obj, "r+");

	if (fp == NULL)

		return;

	PyRun_SimpleFile(fp, "bucket_get_object_to_file.py");
	Py_Finalize();
	MessageBox("下载成功");
	return;
}


void CmfctestDlg::OnEnChangeMfceditbrowse1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
