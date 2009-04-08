#include "pomotuxdatabase.hpp"
#include "litesql.hpp"

using namespace litesql;
using namespace pomotuxdatabase;

void pomotuxdatabase::Activity::Delete(const litesql::Database& database,  Activity& delActivity,  ActivityInventorySheet& currentAIS, TodoTodaySheet& currentTDTS)
{
	vector<Activity> activityAis= ActivityAIS::get<Activity>(database,Activity::Id == delActivity.id,ActivityAIS::ActivityInventorySheet == currentAIS.id).all();
	
        for (
		vector<Activity>::iterator i = activityAis.begin(); 
		i != activityAis.end(); 
		i++
	)
		ActivityAIS::unlink(database,(*i),currentAIS);
		ActivityTDTS::del(database,ActivityTDTS::Activity == delActivity.id);
		delActivity.del();
	
}
