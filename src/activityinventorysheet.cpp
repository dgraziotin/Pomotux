#include "pomotuxdatabase.hpp"
#include "litesql.hpp"

using namespace litesql;
using namespace pomotuxdatabase;

void pomotuxdatabase::ActivityInventorySheet::InsertActivity(const litesql::Database& database, Activity& newActivity, ActivityInventorySheet& currentAIS)
{
	ActivityAIS::link(database,newActivity,currentAIS);
}
