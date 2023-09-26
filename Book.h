#pragma once
class Book:public CObject
{
	int no;
	CString title;
	CString content;
	CString paddr;
	CString image;
	COleDateTime pubdate;
public:
	Book(int no, CString title, CString content, CString paddr,CString image, COleDateTime pubdate);
	Book(CArchive& ar);
	int GetNo();
	CString GetTitle();
	CString GetContent();
	CString GetPAddr();
	CString GetImage();
	COleDateTime GetPubdate();
	void SetTitle(CString title);
	void SetContent(CString content);
	void SetPAddr(CString paddr);
	void SetImage(CString image);
	void SetPubdate(COleDateTime pubdate);
	virtual void Serialize(CArchive& ar);
};

