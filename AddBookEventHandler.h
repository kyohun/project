#pragma once
class Book;
class AddBookEventHandler
{
public:
	virtual void AddedBook(Book *book) = 0;
};

class RemoveBookEventHandler
{
public:
	virtual void RemovedBook(int bno) = 0;
};

class ModifyBookEventHandler
{
public:
	virtual void ModifiedBook(Book *book) = 0;
};

class RegisterBookEventHandler
{
public:
	virtual void RegisteredBook(Book* book) = 0;
};
