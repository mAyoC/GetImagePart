
// GetImagePartDlg.h : ��� ����
//

#pragma once


// CGetImagePartDlg ��ȭ ����
class CGetImagePartDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CGetImagePartDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GETIMAGEPART_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
