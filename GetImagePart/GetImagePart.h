
// GetImagePart.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CGetImagePartApp:
// �� Ŭ������ ������ ���ؼ��� GetImagePart.cpp�� �����Ͻʽÿ�.
//

class CGetImagePartApp : public CWinApp
{
public:
	CGetImagePartApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CGetImagePartApp theApp;