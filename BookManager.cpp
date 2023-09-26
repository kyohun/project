#include "pch.h"
#include "BookManager.h"
#include <afxdb.h>
#include "DBControl.h"
BookManager BookManager::bm;
BookManager& BookManager::GetBookManager()
{	


	return bm;
}
BookManager::BookManager()
{

	last_bno = 0;
}
int BookManager::GetNextBookNo()
{

	return last_bno+1;
}
bool BookManager::AddBook(CString title, CString content, CString paddr,CString image, COleDateTime pubdate)
{

	last_bno++;
	Book* book = new Book(last_bno, title, content, paddr,image, pubdate);
	book_map[last_bno] = book;
	/*
	* 도서 추가한 정보를 알고자 하는 이들에게 통보하는 코드가 필요할 듯
	*/
	ABIter seek = abhandlers.begin();
	ABIter end = abhandlers.end();
	for (; seek != end; ++seek)
	{
		(*seek)->AddedBook(book);//도서 추가 사실을 통보한다.
	}
	return true;
}
void BookManager::GetBookNoList(NList* bno_list)
{

	Book* book = 0;
	BIter seek = book_map.begin();
	BIter end = book_map.end();
	for (; seek != end; ++seek)
	{
		book = (*seek).second;//값
		if (book)//값이 유효하다면
		{
			bno_list->push_back((*seek).first);//book->GetNo()
		}		
	}
}
Book* BookManager::GetBook(int no)
{

	return book_map[no];	
}
bool BookManager::ModifyBook(int bno, CString content, CString paddr,CString image, COleDateTime pubdate)
{

	Book* book = book_map[bno];
	if (book)
	{		
		book->SetContent(content);
		book->SetPAddr(paddr);
		book->SetImage(image);
		book->SetPubdate(pubdate);
		MBIter seek = mbhandlers.begin();
		MBIter end = mbhandlers.end();
		for (; seek != end; ++seek)
		{
			(*seek)->ModifiedBook(book);
		}
		return true;
	}
	return false;
}
bool BookManager::RemoveBook(int bno)
{

	Book* book = book_map[bno];
	if (book)
	{
		delete book;
		book_map[bno] = 0;
		RBIter seek = rbhandlers.begin();
		RBIter end = rbhandlers.end();
		for (; seek != end; ++seek)
		{
			(*seek)->RemovedBook(bno);
		}
		return true;
	}
	return false;
}
void BookManager::AddABEventHandler(AddBookEventHandler* abeh)
{

	abhandlers.push_back(abeh);
}
void BookManager::AddRBEventHandler(RemoveBookEventHandler* rbeh)
{

	rbhandlers.push_back(rbeh);
}
void BookManager::AddMBEventHandler(ModifyBookEventHandler* mbeh)
{

	mbhandlers.push_back(mbeh);
}
void BookManager::AddRegBEventHandler(RegisterBookEventHandler* regbeh)
{
	regbhandlers.push_back(regbeh);
}
void BookManager::Save()
{

	CFile cf(TEXT("data.abc"), CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&cf, CArchive::store);

	BIter seek = book_map.begin();
	BIter end = book_map.end();
	Book* book = 0;
	for (; seek != end; ++seek)
	{
		book = (*seek).second;
		if (book)
		{
			book->Serialize(ar);
		}
	}
	ar.Close();
	cf.Close();
}
void BookManager::Load()
{

	CFile* pcf;
	try
	{
		pcf =new CFile(TEXT("data.abc"), CFile::modeRead);
	}
	catch (...)
	{
		return;
	}
	CArchive ar(pcf, CArchive::load);	
	while (true)
	{
		try
		{
			Book* book = new Book(ar);
			book_map[book->GetNo()] = book;

			ABIter seek = abhandlers.begin();
			ABIter end = abhandlers.end();
			for (; seek != end; ++seek)
			{
				(*seek)->AddedBook(book);//도서 추가 사실을 통보한다.
			}			
		}
		catch (...)
		{
			break;
		}
	}

	ar.Close();
	pcf->Close();
	delete pcf;
}