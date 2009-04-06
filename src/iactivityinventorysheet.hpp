#ifndef _IACTIVITYINVENTORYSHEET_HPP_
#define _IACTIVITYINVENTORYSHEET_HPP_
#include "litesql.hpp"
#include "pomotuxdatabase.hpp"
#include <iostream>
#include <string>

//using namespace std;
using namespace litesql;
using namespace pomotuxdatabase;

class IActivityInventorySheet : public ActivityInventorySheet
{
	public:
	IActivityInventorySheet(const litesql::Database& db);
	~IActivityInventorySheet();
};

#endif
