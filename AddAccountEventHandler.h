#pragma once
class Account;
class AddAccountEventHandler
{
public:
	virtual void AddedAccount(Account* account) = 0;
};

class RemoveAccountEventHandler
{
public:
	virtual void RemovedAccount(int acc_no) = 0;
};

class ModifyAccountEventHandler
{
public:
	virtual void ModifiedAccount(Account* account) = 0;
};

