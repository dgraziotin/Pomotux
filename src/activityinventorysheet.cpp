#include "pomotuxdatabase.hpp"
#include "litesql.hpp"

using namespace litesql;
using namespace pomotuxdatabase;

void pomotuxdatabase::ActivityInventorySheet::InsertActivity(const litesql::Database& rDatabase, Activity& rNewActivity, ActivityInventorySheet& rAIS)
{
    ActivityInAIS::link(rDatabase,rNewActivity,rAIS);
	rDatabase.commit();
}
