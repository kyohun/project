﻿#pragma once
#include "afxdialogex.h"


// SALE 대화 상자

class SALE : public CDialogEx
{
	DECLARE_DYNAMIC(SALE)

public:
	SALE(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SALE();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SALE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
