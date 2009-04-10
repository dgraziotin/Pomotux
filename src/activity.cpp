#include "pomotuxdatabase.hpp"
#include "litesql.hpp"


using namespace std;
using namespace litesql;
using namespace pomotuxdatabase;

void pomotuxdatabase::Activity::Delete(const litesql::Database& rDatabase,  Activity& delActivity,  ActivityInventorySheet& rAIS, TodoTodaySheet& rTTS)
{
    vector<Activity> activityAis= ActivityInAIS::get<Activity>(rDatabase,Activity::Id == delActivity.id,ActivityInAIS::ActivityInventorySheet == rAIS.id).all();

    for (vector<Activity>::iterator i = activityAis.begin(); i != activityAis.end(); i++)
        ActivityInAIS::unlink(rDatabase,(*i),rAIS);

    ActivityInTTS::del(rDatabase,ActivityInTTS::Activity == delActivity.id);
    delActivity.del();

}

void pomotuxdatabase::Activity::Modify(Activity& rCurrentActivity,  int newDeadline, string newDescription)
{
    if (newDeadline != 0)
        rCurrentActivity.mDeadline = newDeadline;
    if (!newDescription.empty())
        rCurrentActivity.mDescription = newDescription;

    rCurrentActivity.update();
}
