
// GetImagePartDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "GetImagePart.h"
#include "GetImagePartDlg.h"
#include "afxdialogex.h"
#include "ximage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGetImagePartDlg ��ȭ ����



CGetImagePartDlg::CGetImagePartDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGetImagePartDlg::IDD, pParent)
	, m_strRect(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGetImagePartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strRect);
}

BEGIN_MESSAGE_MAP(CGetImagePartDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CGetImagePartDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGetImagePartDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CGetImagePartDlg �޽��� ó����

BOOL CGetImagePartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CGetImagePartDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CGetImagePartDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CGetImagePartDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGetImagePartDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialogEx::OnOK();
	
	// �޸� DC ��ε�
	UnloadMemDC();
	UnloadMemDC2();


	// ���� ����.
	CFileDialog dlg( TRUE, NULL, NULL, OFN_HIDEREADONLY, NULL, NULL );
	CString strSrc;

	if ( dlg.DoModal() == IDOK )
	{
		POSITION pos = dlg.GetStartPosition();

		strSrc = dlg.GetNextPathName( pos );
		
		CxImage image;
		image.Load( strSrc, 0 );

		InitMemDC( image.GetWidth(), image.GetHeight() );
		CRect rtImage( 0, 0, image.GetWidth(), image.GetHeight() );
		image.Draw( m_dcMem.GetSafeHdc(), rtImage );
	}
	else return;

	UpdateData(TRUE);
//	MessageBox( m_strRect );

	int nX = -1, nY = -1, nWidth = -1, nHeight = -1;
	CString strTemp;

	::AfxExtractSubString( strTemp, m_strRect.GetBuffer(), 0, L',' );
	if ( strTemp != L"" )
		nX = _wtoi( strTemp.GetBuffer() );
	::AfxExtractSubString( strTemp, m_strRect.GetBuffer(), 1, L',' );
	if ( strTemp != L"" )
		nY = _wtoi( strTemp.GetBuffer() );
	::AfxExtractSubString( strTemp, m_strRect.GetBuffer(), 2, L',' );
	if ( strTemp != L"" )
		nWidth = _wtoi( strTemp.GetBuffer() );
	::AfxExtractSubString( strTemp, m_strRect.GetBuffer(), 3, L',' );
	if ( strTemp != L"" )
		nHeight = _wtoi( strTemp.GetBuffer() );
	
	if ( nX == -1 || nY == -1 || nWidth == -1 || nHeight == -1 )
		return;
	
	InitMemDC2( nWidth, nHeight );
	m_dcMem2.BitBlt( 0, 0, nWidth, nHeight, &m_dcMem, nX, nY, SRCCOPY );

	CxImage image;

	image.CreateFromHBITMAP( (HBITMAP)m_dcMem2.GetCurrentBitmap()->GetSafeHandle() );
	CString strWindowText;
	GetWindowText( strWindowText );
	
	
	CString strTarget = strSrc.Right( strSrc.GetLength() - strSrc.ReverseFind( L'\\' ) -1 );
	strTarget = strTarget.Left( strTarget.ReverseFind( L'.' ) );

	image.Save( strTarget + "_Part.png", CXIMAGE_FORMAT_PNG );

	MessageBox( L"�Ϸ�" );
}


void CGetImagePartDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}


void CGetImagePartDlg::InitMemDC( int nWidth, int nHeight )
{
	CClientDC dc( this );

	m_dcMem.CreateCompatibleDC(&dc);
	m_bitmapMem.CreateCompatibleBitmap( &dc, nWidth, nHeight );
	m_bitmapOld = m_dcMem.SelectObject( &m_bitmapMem );
}

void CGetImagePartDlg::UnloadMemDC()
{
	if ( m_dcMem.GetSafeHdc() )
	{
		m_dcMem.SelectObject( m_bitmapOld );
		m_bitmapMem.DeleteObject();
		m_dcMem.DeleteDC();
	}
}

void CGetImagePartDlg::InitMemDC2( int nWidth, int nHeight )
{
	CClientDC dc( this );

	m_dcMem2.CreateCompatibleDC(&dc);
	m_bitmapMem2.CreateCompatibleBitmap( &dc, nWidth, nHeight );
	m_bitmapOld2 = m_dcMem2.SelectObject( &m_bitmapMem2 );
}

void CGetImagePartDlg::UnloadMemDC2()
{
	if ( m_dcMem2.GetSafeHdc() )
	{
		m_dcMem2.SelectObject( m_bitmapOld2 );
		m_bitmapMem2.DeleteObject();
		m_dcMem2.DeleteDC();
	}
}


void CGetImagePartDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	UnloadMemDC();
	UnloadMemDC2();
}
