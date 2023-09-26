#pragma once
#include "afxdialogex.h"


// CS 대화 상자

class CS : public CDialogEx
{
	DECLARE_DYNAMIC(CS)

public:
	CS(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CS();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
