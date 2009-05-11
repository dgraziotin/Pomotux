#include "pomotuxdatabase.hpp"
#include "litesql.hpp"
#include <time.h>
using namespace std;
using namespace litesql;
using namespace pomotuxdatabase;

string pomotuxdatabase::Activity::HumanizeDate(string unixDate){
    int startYear = 1900;   // C dates in tm structure are represented as the number of years from 1900
    int startMonth = 1;     // C months in tm structure are represented as the number of months since january [0-11]

    int unixDateToInteger = atoi(unixDate);
    time_t unixDatetime = ((time_t) unixDateToInteger); // simple casting to time_t

    struct tm* timeStructure = localtime( &unixDatetime );  // converts a time_t to a struct tm
    int day = timeStructure->tm_mday;
    int month = timeStructure->tm_mon + startMonth;
    int year = timeStructure->tm_year + startYear;

    stringstream humanizedDate;                             // necessary to convert integers to string again
    humanizedDate << year << "-" << month << "-" << day;    // ISO 8601:2004 date format
    return humanizedDate.str();
}

string pomotuxdatabase::Activity::GetInsertionDate(){
    return HumanizeDate(this->mInsertionDate);
}
string pomotuxdatabase::Activity::GetDeadline(){
    return HumanizeDate(this->mDeadline);
}
void pomotuxdatabase::Activity::Delete(const litesql::Database& rDatabase,  Activity& delActivity,  ActivityInventorySheet& rAIS, TodoTodaySheet& rTTS)
{
    vector<Activity> activityAis= ActivityInAIS::get<Activity>(rDatabase,Activity::Id == delActivity.id,ActivityInAIS::ActivityInventorySheet == rAIS.id).all();

    for (vector<Activity>::iterator i = activityAis.begin(); i != activityAis.end(); i++)
        ActivityInAIS::unlink(rDatabase,(*i),rAIS);

    ActivityInTTS::del(rDatabase,ActivityInTTS::Activity == delActivity.id);
    delActivity.del();
    rTTS.MakeConsistent(rDatabase, rTTS);
    rDatabase.commit();
}

void pomotuxdatabase::Activity::Modify(const litesql::Database& rDatabase, Activity& rCurrentActivity,  int newDeadline, string newDescription)
{
    if (newDeadline != 0)
        rCurrentActivity.mDeadline = newDeadline;
    if (!newDescription.empty())
        rCurrentActivity.mDescription = newDescription;

    rCurrentActivity.update();
    rDatabase.commit();
}
