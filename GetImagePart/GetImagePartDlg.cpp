
// GetImagePartDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "GetImagePart.h"
#include "GetImagePartDlg.h"
#include "afxdialogex.h"
#include "ximage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CGetImagePartDlg 대화 상자



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


// CGetImagePartDlg 메시지 처리기

BOOL CGetImagePartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGetImagePartDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGetImagePartDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGetImagePartDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
	
	// 메모리 DC 언로드
	UnloadMemDC();
	UnloadMemDC2();


	// 파일 선택.
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

	MessageBox( L"완료" );
}


void CGetImagePartDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	UnloadMemDC();
	UnloadMemDC2();
}
