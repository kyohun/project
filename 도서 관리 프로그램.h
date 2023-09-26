
// 도서 관리 프로그램.h: PROJECT_NAME 애플리케이션에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'pch.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.
//로그인 페이지 헤더
#include "LoginPageDialog.h"
//로그인 페이지의 상세 페이지 헤더
#include "SignInDialog.h"
#include "SignUpDialog.h"
#include "ModifyMemInfoDialog.h"
//회원 정보
#include "Account.h"


// C도서관리프로그램App:
// 이 클래스의 구현에 대해서는 도서 관리 프로그램.cpp을(를) 참조하세요.
//

class C도서관리프로그램App : public CWinApp
{
public:
	C도서관리프로그램App();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.

	DECLARE_MESSAGE_MAP()
};

extern C도서관리프로그램App theApp;
