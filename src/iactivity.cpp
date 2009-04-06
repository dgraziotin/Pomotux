#include "iactivity.hpp"
#include "litesql.hpp"
#include "pomotuxdatabase.hpp"
//using namespace std;
using namespace litesql;
using namespace pomotuxdatabase;

IActivity::IActivity(const litesql::Database& db) : Activity(db)
{
}

IActivity::IActivity(const litesql::Database& db,string description,int insertionDate,int deadlineDate) : Activity(db)
{
	mDescription = description;
	mInsertionDate = insertionDate;
	mDeadLine = deadlineDate;
}

void IActivity::set_mDescription (string description)
{
	mDescription = description;
}

void IActivity::set_mInsertionDate (int date)
{
	mInsertionDate = date;
}

void IActivity::set_mDeadline (int date)
{
	mDeadLine = date;
}

void IActivity::set_mNumPomodoro (int numPomodoro)
{
	mNumPomodoro = numPomodoro;
}

void IActivity::set_mIsFinished (bool isFinished)
{
	mIsFinished = isFinished;
}

string IActivity::get_mDescription()
{
	return mDescription;
}

litesql::Field<litesql::Date> IActivity::get_mInsertionDate()
{
	return mInsertionDate;
}

litesql::Field<litesql::Date> IActivity::get_mDeadline()
{
	return mDeadLine;
}

int IActivity::get_mNumPomodoro()
{
	return mNumPomodoro;
}

bool IActivity::get_mIsFinished()
{
	return mIsFinished;
}

IActivity::~IActivity()
{
}
