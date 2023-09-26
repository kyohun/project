#pragma once
#include "afxdialogex.h"


// SVCENTER 대화 상자

class SVCENTER : public CDialogEx
{
	DECLARE_DYNAMIC(SVCENTER)

public:
	SVCENTER(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SVCENTER();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
