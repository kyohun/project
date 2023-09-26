#pragma once
#include "afxdialogex.h"
#include "AddAccountEventHandler.h"
#include "EndDialogEventHandler.h"
#include "SignInDialog.h"
#include "SignUpDialog.h"
#include "ModifyMemInfoDialog.h"
#include "AccountManager.h"
#include "Account.h"


// LoginPageDialog 대화 상자

class LoginPageDialog : public CDialogEx,
	public AddAccountEventHandler,
	public ModifyAccountEventHandler,
	public RemoveAccountEventHandler,
	public EndDialogEventHandler
{
	DECLARE_DYNAMIC(LoginPageDialog)
	//로그인 창 단 하나로 유지시키기 위해서
	SignInDialog* sid;
public:
	LoginPageDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~LoginPageDialog();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOGINPAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButtonSignin();
	afx_msg void OnBnClickedButtonSignup();
	afx_msg void OnBnClickedButtonModmeminfo();
	afx_msg void OnBnClickedButtonDelmeminfo();
	afx_msg void OnLvnItemchangedListMeminfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnEndedSignin(WPARAM, LPARAM);

	//
	virtual void AddedAccount(Account* account);
	virtual void ModifiedAccount(Account* account);
	virtual void RemovedAccount(int bno);
	virtual void EndedDialog();

	// 멤버리스트
	CListCtrl mem_list;
	// 로그인 페이지 회원정보 수정 버튼
	CButton mod_button;
	// 로그인 페이지 회원정보 삭제 버튼
	CButton del_button;
	// 사인인으로 보내는 버튼
	CButton signin_button;
	// "**님 반가워요"
	CString loginpage_message;
	afx_msg void OnBnClickedButtonSignout();
	CButton signout_button;
};
