
// GetImagePartDlg.h : 헤더 파일
//

#pragma once


// CGetImagePartDlg 대화 상자
class CGetImagePartDlg : public CDialogEx
{
// 생성입니다.
public:
	CGetImagePartDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_GETIMAGEPART_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_strRect;

	
	CDC m_dcMem2;
	CBitmap	m_bitmapMem2;
	CBitmap	*m_bitmapOld2;
	
	CDC m_dcMem;
	CBitmap	m_bitmapMem;
	CBitmap	*m_bitmapOld;
	
	void InitMemDC( int nWidth, int nHeight );
	void UnloadMemDC();
	
	void InitMemDC2( int nWidth, int nHeight );
	void UnloadMemDC2();
	afx_msg void OnDestroy();
};
