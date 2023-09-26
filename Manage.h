#pragma once
#include "afxdialogex.h"


// Manage 대화 상자

class Manage : public CDialogEx
{
	DECLARE_DYNAMIC(Manage)

public:
	Manage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Manage();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MANAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
