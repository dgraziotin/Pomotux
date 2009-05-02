#include "pomotuxdatabase.hpp"
#include "litesql.hpp"

using namespace litesql;
using namespace pomotuxdatabase;
using namespace std;

void pomotuxdatabase::TodoTodaySheet::ScheduleActivity(const litesql::Database& rDatabase, Activity& rNewActivity, ActivityInventorySheet& rAIS,  TodoTodaySheet& rTTS)
{
    rTTS.MakeConsistent(rDatabase,rTTS);
    try {
        Activity searchActivity = ActivityInAIS::get<Activity>(rDatabase,
                                  Activity::Id == rNewActivity.id,
                                  ActivityInAIS::ActivityInventorySheet==rAIS.id).one();


    } catch (NotFound e) {
        cout << "Fatal. The tables are not consistent." << endl;
        //exit (-1);
    }
    rNewActivity.mOrder = GetMaxActivityOrder(rDatabase, rTTS) + 1;
    rNewActivity.mIsFinished = false;
    rNewActivity.update();
    ActivityInTTS::link(rDatabase,rNewActivity,rTTS);
	rDatabase.commit();
}

void pomotuxdatabase::TodoTodaySheet::FinishActivity(const litesql::Database& rDatabase, Activity& rCurrentActivity,TodoTodaySheet& rTTS)
{
    rCurrentActivity.mIsFinished = true;
    rCurrentActivity.update();
    ActivityInTTS::unlink(rDatabase, rCurrentActivity, rTTS);
    rTTS.MakeConsistent(rDatabase,rTTS);
	rDatabase.commit();
}

void pomotuxdatabase::TodoTodaySheet::PostponeActivity(const litesql::Database& rDatabase, Activity& rCurrentActivity,TodoTodaySheet& rTTS)
{
    rCurrentActivity.mOrder = 0;
    rCurrentActivity.update();
    ActivityInTTS::unlink(rDatabase, rCurrentActivity, rTTS);
    rTTS.MakeConsistent(rDatabase,rTTS);
    rDatabase.commit();
}

void pomotuxdatabase::TodoTodaySheet::MoveActivity(const litesql::Database& rDatabase, Activity& rCurrentActivity,TodoTodaySheet& rTTS, int direction)
{
    rTTS.MakeConsistent(rDatabase,rTTS);
        Activity targetActivity = ActivityInTTS::get<Activity>(rDatabase,
                                  Activity::MOrder == rCurrentActivity.mOrder + direction,
                                  ActivityInTTS::TodoTodaySheet==rTTS.id).one();
       
	    int currentActivityOrder = rCurrentActivity.mOrder;
		
		targetActivity.mOrder = currentActivityOrder;
        rCurrentActivity.mOrder = (currentActivityOrder + direction);
		
        targetActivity.update();
        rCurrentActivity.update();
		rDatabase.commit();
}

void pomotuxdatabase::TodoTodaySheet::MakeConsistent(const litesql::Database& rDatabase, TodoTodaySheet& rTTS)
{
    vector<Activity> currentTDTSActivities = ActivityInTTS::get<Activity>(rDatabase,Expr(),
            ActivityInTTS::TodoTodaySheet==rTTS.id).orderBy(Activity::MOrder).all();
    int order = 1;
    for (vector<Activity>::iterator i = currentTDTSActivities.begin(); i != currentTDTSActivities.end(); i++) {
        (*i).mOrder = order++;
        (*i).update();
    }
	rDatabase.commit();
}

int pomotuxdatabase::TodoTodaySheet::GetMaxActivityOrder(const litesql::Database& rDatabase, TodoTodaySheet& rTTS)
{

    vector<Activity> currentTDTSActivities = ActivityInTTS::get<Activity>(rDatabase,Expr(),
            ActivityInTTS::TodoTodaySheet==rTTS.id).all();
    int maxOrder = 0;
    for (vector<Activity>::iterator i = currentTDTSActivities.begin(); i != currentTDTSActivities.end(); i++) {
        if ((*i).mOrder > maxOrder)
            maxOrder = (*i).mOrder;
    }

    return maxOrder;
}
