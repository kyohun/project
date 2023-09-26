#pragma once
#include "afxdialogex.h"


// DEV 대화 상자

class DEV : public CDialogEx
{
	DECLARE_DYNAMIC(DEV)

public:
	DEV(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DEV();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DEV };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
