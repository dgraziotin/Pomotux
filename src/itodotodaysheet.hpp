#ifndef _ITODOTODAYSHEET_HPP_
#define _ITODOTODAYSHEET_HPP_
#include "litesql.hpp"
#include "pomotuxdatabase.hpp"
#include <iostream>
#include <string>

//using namespace std;
using namespace litesql;
using namespace pomotuxdatabase;
class ITodoTodaySheet : public TodoTodaySheet
{
	public:
	ITodoTodaySheet(const litesql::Database& db);
	void set_mActivityOrder(int activityOrder);
	int get_mActivityOrder();
	~ITodoTodaySheet();
};
#endif
