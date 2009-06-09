#include "pomotuxdatabase.hpp"
#include "litesql.hpp"

using namespace litesql;
using namespace pomotuxdatabase;

void pomotuxdatabase::ActivityInventorySheet::InsertActivity(const litesql::Database& rDatabase, Activity& rNewActivity, ActivityInventorySheet& rAIS)
{
    try {
        ActivityInAIS::link(rDatabase,rNewActivity,rAIS);
    } catch (Except e) {
        cerr << e << endl;

    }
}
