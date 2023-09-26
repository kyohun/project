
// 도서 관리 프로그램Dlg.h: 헤더 파일
//

#pragma once
#include "MyRegDialog.h"
#include "ModifyDialog.h"
#include "VerifyDilaog.h"
#include "EndDialogEventHandler.h"
#include "AddBookEventHandler.h"
#include "BookManager.h"
#include "Book.h"

// C도서관리프로그램Dlg 대화 상자
class C도서관리프로그램Dlg : public CDialogEx,
	public EndDialogEventHandler,
	public AddBookEventHandler,
	public ModifyBookEventHandler
{
	MyRegDialog* mrd;

	// 생성입니다.
public:
	C도서관리프로그램Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MAIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


	// 구현입니다.
protected:
	//HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	//afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//afx_msg void OnPaint();
	//afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonReg();
	virtual void EndedDialog();
	afx_msg LRESULT OnEndedReg(WPARAM, LPARAM);

	virtual void AddedBook(Book* book);
	afx_msg void OnBnClickedButtonVerify();
	afx_msg void OnLvnItemchangedListBook(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void OnBnClickedButtonRemove();
	afx_msg void OnBnClickedButtonModify();
	virtual void ModifiedBook(Book* book);
	virtual BOOL DestroyWindow();

	CListCtrl blist;
	CButton btn_remove;
	CButton btn_modify;
	CString pname;
	CString pprice;
	CString desc;
	afx_msg void OnDestroy();
	CString pgender;
	CString pphone;
	CString peducation;
	CString pintroduce;
};
