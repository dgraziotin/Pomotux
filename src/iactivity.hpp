#ifndef _IACTIVITY_HPP_
#define _IACTIVITY_HPP_
#include "litesql.hpp"
#include "pomotuxdatabase.hpp"
#include <iostream>
#include <string>

//using namespace std;
using namespace litesql;
using namespace pomotuxdatabase;

class IActivity : public Activity
{
	public:
	IActivity(const litesql::Database& db);
	
  /** Copy constructor.
	* 
	* @param from The value to copy to this object.
	*/

	IActivity(const litesql::Database& db,string description,int insertionDate,int deadlineDate);
	void set_mDescription (string description);
	void set_mInsertionDate (int date);
	void set_mDeadline (int date);
	void set_mNumPomodoro (int numPomodoro);
	void set_mIsFinished (bool isFinished);
	string get_mDescription();
	litesql::Field<litesql::Date> get_mInsertionDate();
	litesql::Field<litesql::Date> get_mDeadline();
	int get_mNumPomodoro();
	bool get_mIsFinished();
	~IActivity();
};
#endif
