#include "pch.h"
#include "Book.h"
Book::Book(int no, CString title, CString content, CString paddr,CString image, COleDateTime pubdate):
	no(no)
{
	this->title = title;//이름
	this->content = content;//생년월일
	this->paddr = paddr;//주소
	this->image = image;//이미지
	this->pubdate = pubdate;//제출일
}
int Book::GetNo()
{
	return no;
}
CString Book::GetTitle()
{
	return title;
}
CString Book::GetContent()
{
	return content;
}
CString Book::GetPAddr()
{
	return paddr;
}
CString Book::GetImage()
{
	return image;
}
COleDateTime Book::GetPubdate()
{
	return pubdate;
}
void Book::SetTitle(CString title)
{
	this->title = title;
}
void Book::SetContent(CString content)
{
	this->content = content;
}
void Book::SetPAddr(CString paddr)
{
	this->paddr = paddr;
}
void Book::SetImage(CString image)
{
	this->image = image;
}
void Book::SetPubdate(COleDateTime pubdate)
{
	this->pubdate = pubdate;
}
Book::Book(CArchive& ar)
{
	Serialize(ar);
}
void Book::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar<<no;
		ar<<title;
		ar<<content;
		ar<<paddr;
		ar<<image;
		ar<<pubdate;
	}
	else
	{
		ar >> no;
		ar >> title;
		ar >> content;
		ar >> paddr;
		ar >> image;
		ar >> pubdate;
	}
}
