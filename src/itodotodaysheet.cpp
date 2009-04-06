#include "itodotodaysheet.hpp"
#include "litesql.hpp"
#include "pomotuxdatabase.hpp"
//using namespace std;
using namespace litesql;
using namespace pomotuxdatabase;

ITodoTodaySheet::ITodoTodaySheet(const litesql::Database& db) : TodoTodaySheet(db)
{
}

void ITodoTodaySheet::set_mActivityOrder(int activityOrder)
{
	mActivityOrder=activityOrder;
}

int ITodoTodaySheet::get_mActivityOrder()
{
	return mActivityOrder;
}

ITodoTodaySheet::~ITodoTodaySheet()
{
}
