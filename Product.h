#pragma once
#include "afxdialogex.h"


// Product 대화 상자

class Product : public CDialogEx
{
	DECLARE_DYNAMIC(Product)

public:
	Product(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Product();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PRODUCT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
