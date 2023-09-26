// SignInDialog.cpp: 구현 파일
//

#include "pch.h"
#include "도서 관리 프로그램.h"
#include "afxdialogex.h"
#include "SignInDialog.h"
#include <afxdb.h>



// SignInDialog 대화 상자

IMPLEMENT_DYNAMIC(SignInDialog, CDialogEx)

SignInDialog::SignInDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SIGNIN, pParent)
	, login_email(_T(""))
	, login_password(_T(""))
{
	eeh = 0;
}

SignInDialog::~SignInDialog()
{
}

void SignInDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_EMAIL, login_email);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, login_password);
}


BEGIN_MESSAGE_MAP(SignInDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LOGINOK, &SignInDialog::OnBnClickedButtonLoginok)
END_MESSAGE_MAP()


// SignInDialog 메시지 처리기

void SignInDialog::AddEndedEventHandler(EndDialogEventHandler* eeh)
{
	this->eeh = eeh;
}
void SignInDialog::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (eeh)
	{
		eeh->EndedDialog();//나 죽음을 통보한다.
	}
	CDialogEx::OnCancel();
}

void SignInDialog::OnBnClickedButtonLoginok()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(); // 컨트롤->  변수 edit_control -> 값
	CDatabase db;
	bool re = db.OpenEx(TEXT("DSN=LocalSQL; uid=scott;PWD=tiger"));
	if (re == FALSE)
	{
		return;
	}
	CString sqlQuery;
	sqlQuery.Format(_T("SELECT * FROM accounttest WHERE acc_email='%s' AND acc_password='%s'"), login_email, login_password);// query_str에 저장
	CRecordset recordset(&db);
	if (recordset.Open(CRecordset::forwardOnly, sqlQuery)) {
		if (!recordset.IsEOF()) {
			CString name, phoneNumber, photo, birthdate;

			recordset.GetFieldValue(_T("acc_name"), name);
			recordset.GetFieldValue(_T("acc_birthdate"), birthdate);
			recordset.GetFieldValue(_T("acc_phone"), phoneNumber);
			recordset.GetFieldValue(_T("acc_image"), photo);
			COleDateTime parsedBirthdate;
			//CString birthdate -> COleDateTime parsedBirthdate
			parsedBirthdate.ParseDateTime(birthdate);
			AccountManager& am = AccountManager::GetAccountManager();
			if (am.AddAccount(0, login_email, login_password, name, parsedBirthdate, phoneNumber, photo) == TRUE)
			{
				MessageBox(TEXT("로그인 성공"));
				OnCancel();
			}
			else
			{
				MessageBox(TEXT("로그인 실패"));
			}
		}
	}
}