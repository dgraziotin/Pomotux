#include "pomotuxdatabase.hpp"
#include "litesql.hpp"

using namespace litesql;
using namespace pomotuxdatabase;

void pomotuxdatabase::Activity::Delete(const litesql::Database& database,  Activity& delActivity,  ActivityInventorySheet& currentAIS, TodoTodaySheet& currentTDTS)
{
	vector<Activity> activityAis= ActivityAIS::get<Activity>(database,Activity::Id == delActivity.id,ActivityAIS::ActivityInventorySheet == currentAIS.id).all();
	
        for (vector<Activity>::iterator i = activityAis.begin(); 
		i != activityAis.end(); 
		i++
	)
		ActivityAIS::unlink(database,(*i),currentAIS);


        /*
	vector<Activity> activityTdts = ActivityTDTS::get<Activity>(database,Activity::Id == delActivity.id,ActivityTDTS::TodoTodaySheet == currentTDTS.id).all();
	
        for (
		vector<Activity>::iterator f = activityTdts.begin();
		f != activityTdts.end();
		f++
	)
		ActivityTDTS::unlink(database,(*f),currentTDTS);
	*/
	delActivity.del();
	
}
