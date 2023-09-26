#pragma once
#include "afxdialogex.h"


// SignInDialog 대화 상자
#include "EndDialogEventHandler.h"

class SignInDialog : public CDialogEx
{
	EndDialogEventHandler* eeh;
	DECLARE_DYNAMIC(SignInDialog)

public:
	SignInDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SignInDialog();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SIGNIN };
#endif
	void AddEndedEventHandler(EndDialogEventHandler* eeh);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();

public:
	afx_msg void OnBnClickedButtonLoginok();
	// 로그인 이메일
	CString login_email;
	// 로그인 패스워드
	CString login_password;
};
