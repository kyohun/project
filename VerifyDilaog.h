#pragma once
#include "afxdialogex.h"
#include "AddBookEventHandler.h"

// VerifyDilaog 대화 상자

class VerifyDilaog : public CDialogEx,
	public AddBookEventHandler,
	public RemoveBookEventHandler
{
	DECLARE_DYNAMIC(VerifyDilaog)

public:
	VerifyDilaog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~VerifyDilaog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_VERIFY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	CComboBox cbox_no;
	CString title;
	CString content;
	CStatic pbox_img;
	COleDateTime pubdate;
public:
	virtual BOOL OnInitDialog();
	virtual void AddedBook(Book* book);
	afx_msg void OnCbnSelchangeComboBno();
	virtual void RemovedBook(int bno);
	CString paddr;
	afx_msg void OnStnClickedStaticImg();
};
