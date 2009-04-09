#include "pomotuxdatabase.hpp"
#include "litesql.hpp"

using namespace litesql;
using namespace pomotuxdatabase;
using namespace std;

void pomotuxdatabase::TodoTodaySheet::ScheduleActivity(const litesql::Database& database, Activity& newActivity, ActivityInventorySheet& currentAIS,  TodoTodaySheet& currentTDTS)
{
	currentTDTS.MakeConsistent(database,currentTDTS);
try{
	Activity searchActivity = ActivityAIS::get<Activity>(database, 
                                         Activity::Id == newActivity.id,
                                         ActivityAIS::ActivityInventorySheet==currentAIS.id).one();

	
	}catch(NotFound e){
		cout << "Fatal. The tables are not consistent." << endl;
		//exit (-1);
	}
	newActivity.mOrder = GetMaxmActivityOrder(database, currentTDTS) + 1;
	newActivity.update();
	ActivityTDTS::link(database,newActivity,currentTDTS);
}

void pomotuxdatabase::TodoTodaySheet::FinishActivity(const litesql::Database& database, Activity& currentActivity,TodoTodaySheet& currentTDTS)
{
	currentActivity.mIsFinished = true;
	currentActivity.update();
	ActivityTDTS::unlink(database, currentActivity, currentTDTS);
	currentTDTS.MakeConsistent(database,currentTDTS);
}

void pomotuxdatabase::TodoTodaySheet::Push(const litesql::Database& database, Activity& currentActivity,TodoTodaySheet& currentTDTS, int direction)
{
	currentTDTS.MakeConsistent(database,currentTDTS);
	try{
		Activity targetActivity = ActivityTDTS::get<Activity>(database, 
                                         Activity::MOrder == currentActivity.mOrder + direction,
                                         ActivityTDTS::TodoTodaySheet==currentTDTS.id).one();
		targetActivity.mOrder = currentActivity.mOrder;
		currentActivity.mOrder = currentActivity.mOrder + direction;
	
		targetActivity.update();
		currentActivity.update();
	}catch(NotFound e){
		cout << "Fatal: you are either trying to push up the first Activity or to push down the last Activity!" << endl;
		return;
	}
}

void pomotuxdatabase::TodoTodaySheet::MakeConsistent(const litesql::Database& database, TodoTodaySheet& currentTDTS)
{
	vector<Activity> currentTDTSActivities = ActivityTDTS::get<Activity>(database,Expr(), 
                                         ActivityTDTS::TodoTodaySheet==currentTDTS.id).orderBy(Activity::MOrder).all();
	int order = 0;
	for (vector<Activity>::iterator i = currentTDTSActivities.begin(); i != currentTDTSActivities.end(); i++){
		(*i).mOrder = order++; 
		(*i).update();
	}
}
int pomotuxdatabase::TodoTodaySheet::GetMaxmActivityOrder(const litesql::Database& database, TodoTodaySheet& currentTDTS)
{
	
	vector<Activity> currentTDTSActivities = ActivityTDTS::get<Activity>(database,Expr(), 
                                         ActivityTDTS::TodoTodaySheet==currentTDTS.id).all();
	int maxOrder = -1;			 
	for (vector<Activity>::iterator i = currentTDTSActivities.begin(); i != currentTDTSActivities.end(); i++){
		if ((*i).mOrder > maxOrder)
			maxOrder = (*i).mOrder;
	}
	
	return maxOrder;
}
