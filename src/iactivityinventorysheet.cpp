#include "iactivityinventorysheet.hpp"
#include "litesql.hpp"
#include "pomotuxdatabase.hpp"
//using namespace std;
using namespace litesql;
using namespace pomotuxdatabase;

IActivityInventorySheet::IActivityInventorySheet(const litesql::Database& db) : ActivityInventorySheet(db)
{
}

IActivityInventorySheet::~IActivityInventorySheet()
{
}
