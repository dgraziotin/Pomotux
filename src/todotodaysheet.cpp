#include "pomotuxdatabase.hpp"
#include "litesql.hpp"

using namespace litesql;
using namespace pomotuxdatabase;
using namespace std;

void pomotuxdatabase::TodoTodaySheet::PickUpActivity(const litesql::Database& database, Activity& newActivity, ActivityInventorySheet& currentAIS,  TodoTodaySheet& currentTDTS)
{
try{
	Activity searchActivity = ActivityAIS::get<Activity>(database, 
                                         Activity::Id == newActivity.id,
                                         ActivityAIS::ActivityInventorySheet==currentAIS.id).one();

	
	}catch(NotFound e){
		cout << "Fatal. The tables are not consistent." << endl;
		//exit (-1);
	}
	ActivityTDTS::link(database,newActivity,currentTDTS);
}
