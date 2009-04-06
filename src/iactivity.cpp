#include "iactivity.hpp"
#include "litesql.hpp"
#include "pomotuxdatabase.hpp"
//using namespace std;
using namespace litesql;
using namespace pomotuxdatabase;

IActivity::IActivity(const litesql::Database& db) : Activity(db)
{
	
}

void IActivity::set_mDescription (string description)
{
	mDescription = description;
}

void IActivity::set_mInsertionDate (int date)
{
}

void IActivity::set_mDeadline (int date)
{
}

void IActivity::set_mNumPomodoro (int numPomodoro)
{
}

void IActivity::set_mIsFinished (bool isFinished)
{
}

string IActivity::get_mDescription()
{
}

int IActivity::get_mInsertionDate()
{
}

int IActivity::get_mDeadline()
{
}

int IActivity::get_mNumPomodoro()
{
}

bool IActivity::get_mIsFinished()
{
}

IActivity::~IActivity()
{
}
