#pragma once
#include "afxdialogex.h"


// ModifyMemInfoDialog 대화 상자

class ModifyMemInfoDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ModifyMemInfoDialog)

public:
	ModifyMemInfoDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ModifyMemInfoDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MODMEMINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
