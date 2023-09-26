#pragma once
#include "afxdialogex.h"


// SignUpDialog 대화 상자

class SignUpDialog : public CDialogEx
{
	DECLARE_DYNAMIC(SignUpDialog)

public:
	SignUpDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SignUpDialog();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SIGNUP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// 자동 부여되는 멤버 넘버
	int memno;
	// 등록할 이메일
	CString reg_email;
	// 등록할려는 비밀번호
	CString reg_password;
	// 등록할려는 비밀번호 재확인
	CString reg_passwordcheck;
	// 등록할 이름
	CString reg_name;
	// 등록할 생년월일
	COleDateTime reg_birthdate;
	// 등록할 전화번호
	CString reg_phone;
	// 등록할 이미지
	CStatic reg_img;
	CString image;
	COleDateTime date;


	afx_msg void OnBnClickedButtonSignupok();
	afx_msg void OnBnClickedButtonSignupcancel();
	afx_msg void OnBnClickedButtonGetimage();
};
