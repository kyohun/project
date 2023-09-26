

#pragma once
#include "afxdialogex.h"
#include "AddBookEventHandler.h"

// CertificationDialog 대화 상자

class CertificationDialog : public CDialogEx,
	public AddBookEventHandler,
	public RemoveBookEventHandler
{
	DECLARE_DYNAMIC(CertificationDialog)

public:
	CertificationDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CertificationDialog();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CERTIFICATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:

public:
	virtual BOOL OnInitDialog();
	virtual void AddedBook(Book* book);
	
	virtual void RemovedBook(int bno);
	CString birth;
	afx_msg void OnBnClickedCheck();
	CComboBox cbox_no;
	afx_msg void OnCbnSelchangeComboBno();
};