#pragma once
#include "afxdialogex.h"


// MyRegDialog 대화 상자
#include "EndDialogEventHandler.h"
class MyRegDialog : public CDialogEx
{
	EndDialogEventHandler* eeh;
	DECLARE_DYNAMIC(MyRegDialog)

public:
	MyRegDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MyRegDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_REG };
#endif
public:
	void AddEndedEventHandler(EndDialogEventHandler *eeh);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
public:
	CDateTimeCtrl dtp;
	CMonthCalCtrl mc;	
	CString title;
	CString content;
	int bno;
	CString image;
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMcnSelchangeMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult);
	COleDateTime date1;
	COleDateTime date2;
	afx_msg void OnBnClickedButtonImg();
	CStatic pic_con;
	afx_msg void OnBnClickedButtonSub();
private:
	void InitControls();
public:
	virtual BOOL OnInitDialog();
	//afx_msg void OnEnChangeEditContent();
	CString paddr;
	//afx_msg void OnStnClickedStaticImg();
};
