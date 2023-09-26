// SignUpDialog.cpp: 구현 파일
//

#include "pch.h"
#include "도서 관리 프로그램.h"
#include "afxdialogex.h"
#include "SignUpDialog.h"
#include <afxdb.h>


// SignUpDialog 대화 상자

IMPLEMENT_DYNAMIC(SignUpDialog, CDialogEx)

SignUpDialog::SignUpDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SIGNUP, pParent)
	, memno(0)
	, reg_email(_T(""))
	, reg_password(_T(""))
	, reg_passwordcheck(_T(""))
	, reg_name(_T(""))
	, reg_phone(_T(""))
	, reg_birthdate(COleDateTime::GetCurrentTime())
{

}

SignUpDialog::~SignUpDialog()
{
}

void SignUpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_MEMNO, memno);
	DDX_Text(pDX, IDC_EDIT_EMAIL, reg_email);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, reg_password);
	DDX_Text(pDX, IDC_EDIT_PASSWORDCHECK, reg_passwordcheck);
	DDX_Text(pDX, IDC_EDIT_NAME, reg_name);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BIRTHDATE, reg_birthdate);
	DDX_Text(pDX, IDC_EDIT_PHONE, reg_phone);
	DDX_Control(pDX, IDC_STATIC_SIGNUPIMG, reg_img);
}


BEGIN_MESSAGE_MAP(SignUpDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SIGNUPOK, &SignUpDialog::OnBnClickedButtonSignupok)
	ON_BN_CLICKED(IDC_BUTTON_SIGNUPCANCEL, &SignUpDialog::OnBnClickedButtonSignupcancel)
	ON_BN_CLICKED(IDC_BUTTON_GETIMAGE, &SignUpDialog::OnBnClickedButtonGetimage)
END_MESSAGE_MAP()


// SignUpDialog 메시지 처리기


void SignUpDialog::OnBnClickedButtonSignupok()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(); // 컨트롤->  변수 edit_control -> 값
	//비번 체크
	if (reg_password != reg_passwordcheck)
	{
		MessageBox(TEXT("비밀번호가 달라!"));
		return;
	}
	CDatabase db;
	bool re = db.OpenEx(TEXT("DSN=LocalSQL; uid=scott;PWD=tiger"));
	if (re == FALSE)
	{
		return;
	}
	wchar_t query_str[512] = TEXT("");
	//CString pid;

	CString formattedBirthdate;
	formattedBirthdate = reg_birthdate.Format(_T("%Y-%m-%d")); // 날짜 형식에 따라 포맷 변경

	// 이메일 중복 확인
	CString checkDuplicateEmailQuery;
	checkDuplicateEmailQuery.Format(_T("SELECT COUNT(*) FROM accounttest WHERE acc_email = '%s'"), reg_email);


	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, checkDuplicateEmailQuery);

	CString emailCount = nullptr;
	if (!rs.IsEOF())
	{
		rs.GetFieldValue((short)0, emailCount);
	}

	rs.Close();

	if (!emailCount)
	{
		MessageBox(TEXT("이미 사용 중인 이메일입니다."));
		return;
	}
	//
	wsprintf(query_str, TEXT("insert into accounttest (acc_email ,acc_password ,acc_name,acc_birthdate,acc_phone,acc_image  ) values ('%s','%s','%s','%s','%s','%s') "),
		reg_email, reg_password, reg_name, formattedBirthdate, reg_phone, image); // query_str에 저장

	db.ExecuteSQL(query_str); // 이걸 실행
	////////////////////////////////
	MessageBox(TEXT("저장했습니다"));
	OnCancel();


	//CRecordset rs(&db);
	//rs.Open(CRecordset::forwardOnly, TEXT("select max(pid) from product"));
	//int index = list_pro.GetItemCount();

	//if (!rs.IsEOF()) //end of file 검색할 내용이 없을때 까지
	//{

	//	rs.GetFieldValue((short)0, pid);

	//	list_pro.InsertItem(index, pid);

	//	list_pro.SetItemText(index, 1, pname);
	//	list_pro.SetItemText(index, 2, price);
	//	list_pro.SetItemText(index, 3, desc);

	//}
}


void SignUpDialog::OnBnClickedButtonSignupcancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}


void SignUpDialog::OnBnClickedButtonGetimage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog* fod = new CFileDialog(TRUE, 0);
	int re = fod->DoModal();
	if (re != IDOK)
	{
		return;
	}
	image = fod->GetPathName();
	CImage cimg;
	cimg.Load(image);

	CDC* cdc = reg_img.GetDC();
	RECT rt;
	reg_img.GetClientRect(&rt);
	cimg.StretchBlt(*cdc, 0, 0, rt.right, rt.bottom, SRCCOPY);
}
