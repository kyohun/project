#include "pch.h"
#include "Account.h"
Account::Account(int acc_no, CString acc_email, CString acc_password, CString acc_name, COleDateTime acc_birthdate, CString acc_phone, CString acc_image) :
	acc_no(acc_no)
{
	this->acc_email = acc_email;
	this->acc_password = acc_password;
	this->acc_name = acc_name;
	this->acc_birthdate = acc_birthdate;
	this->acc_phone = acc_phone;
	this->acc_image = acc_image;
}
int Account::GetAccNo()
{
	return acc_no;
}
CString Account::GetAccEmail()
{
	return acc_email;
}
CString Account::GetAccPassword()
{
	return acc_password;
}
CString Account::GetAccName()
{
	return acc_name;
}
COleDateTime Account::GetAccBirthdate()
{
	return acc_birthdate;
}
CString Account::GetAccPhone()
{
	return acc_phone;
}
CString Account::GetAccImage()
{
	return acc_image;
}
void Account::SetAccEmail(CString acc_email)
{
	this->acc_email = acc_email;
}
void Account::SetAccPassword(CString acc_password)
{
	this->acc_password = acc_password;
}
void Account::SetAccName(CString acc_name)
{
	this->acc_name = acc_name;
}
void Account::SetAccBirthdate(COleDateTime acc_birthdate)
{
	this->acc_birthdate = acc_birthdate;
}
void Account::SetAccPhone(CString acc_phone)
{
	this->acc_phone = acc_phone;
}
void Account::SetAccImage(CString acc_image)
{
	this->acc_image = acc_image;
}