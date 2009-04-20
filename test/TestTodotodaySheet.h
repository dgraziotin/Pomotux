// TestTodoTodaySheet.h
#include <cxxtest/TestSuite.h>
#include <iostream>
#include <stdlib.h>
#include "litesql.hpp"
#include "../src/pomotuxdatabase.hpp"
#include <time.h>
#include <string>

using namespace std;
using namespace litesql;
using namespace pomotuxdatabase;

class TestTodoTodaySheet : public CxxTest::TestSuite {
public:
    PomotuxDatabase* db;
    ActivityInventorySheet* ais;
    TodoTodaySheet* tts;
    time_t seconds;

    void setUp() {
        try {
            db = new PomotuxDatabase("sqlite3", "database=pomotuxTEST.db");
            db->verbose = false;
            db->create();
            db->begin();
            ais = new ActivityInventorySheet(*(db));
            tts = new TodoTodaySheet(*(db));
            ais->update();
            tts->update();
            seconds = time (NULL);
            int i;
            for (i = 0; i < 10; i++) {
                /* initialize random seed: */
                srand ( time(NULL) );

                /* generate secret number: */
                int rNumber = rand() % 10 + 1;

                Activity at(*(db));
                at.mDescription = "Activity no. " + i;
                at.mInsertionDate = (int) seconds;
                at.mDeadline = (int) seconds + (int) (90000 * rNumber);
                at.mIsFinished = false;
                at.mNumPomodoro = rNumber;
                at.mOrder = 0;
                at.update();
                ais->InsertActivity(*(db),at,*(ais));
                db->commit();
            }
            for (i = 1; i < 11; i++) {
                if (i%2 != 0) {	// we schedule the even-numbered activities just, so there must be 5 at every test
                    Activity at = select<Activity>(*db, Activity::Id == i).one();
                    tts->ScheduleActivity(*db, at, *ais, *tts);

                }
            }

        } catch (Except e) {
            cerr << e << endl;
        }
    }
    void tearDown() {
        db->drop();
        delete(db);
        delete(ais);
        delete(tts);
        db = NULL;
        ais = NULL;
        tts = NULL;

    }

    void testScheduleActivity() {
        cout << "\n-------------------------------------------------\n";
        cout << "TEST 4 - Check of the number of activity scheduled\n";
        int i;
        try {
            vector<Activity> currentTTSActivities = ActivityInTTS::get<Activity>(*db,Expr(),
                                                    ActivityInTTS::TodoTodaySheet==1).orderBy(Activity::MOrder).all();
            TS_ASSERT_EQUALS( currentTTSActivities.size(), 5 );	// test against the number of activities
            for (vector<Activity>::iterator i = currentTTSActivities.begin(); i != currentTTSActivities.end(); i++)
                if ((*i).id %2 == 0)
                    TS_FAIL( "There are activities scheduled that should not be!" );
        } catch (NotFound e) {
            TS_FAIL( "There is a problem in the insertion of the 10 test-activities!" );
        }
    }


    void testDeleteActivityAfterSchedule() {
        cout << "\n-------------------------------------------------\n";
        cout << "TEST 5 - Delete a random Activity after Schedule\n";

        /* initialize random seed: */
        srand ( time(NULL) );

        /* generate secret number: */
        int rNumber = rand() % 10 + 1;
        while (rNumber%2 == 0)
            rNumber = rand() % 10 + 1;	// make sure we select an odd number

        Activity at = select<Activity>(*db, Activity::Id == rNumber).one();
        at.Delete(*db, at, *ais, *tts);

        vector<Activity> currentTTSActivities = ActivityInTTS::get<Activity>(*db,Expr(),
                                                ActivityInTTS::TodoTodaySheet==1).orderBy(Activity::MOrder).all();
        TS_ASSERT_EQUALS( currentTTSActivities.size(), 4 );	// test against the number of activities
    }

    void testTTSConsistency() {
        cout << "\n-------------------------------------------------\n";
        cout << "TEST 6 - Check of the consistency of the TTS after mOrder entropia\n";
        int i;

		// the activities in TTS
        vector<Activity> currentTTSActivities = ActivityInTTS::get<Activity>(*db,Expr(),
                                                ActivityInTTS::TodoTodaySheet==1).orderBy(Activity::MOrder).all();
		
		// mOrder entropia section
        int f = 1;
        for (vector<Activity>::iterator i = currentTTSActivities.begin(); i != currentTTSActivities.end(); i++) {
            srand ( time(NULL) );
            int anotherRandom = rand() % 100 + 1;
            (*i).mOrder = anotherRandom;
            (*i).update();
        }

		// we ask the tts to make consistent itself
        tts->MakeConsistent(*db, *tts);

		// we get the activities again to see
        currentTTSActivities = ActivityInTTS::get<Activity>(*db,Expr(),
                               ActivityInTTS::TodoTodaySheet==1).orderBy(Activity::MOrder).all();

        f = 1;
        for (vector<Activity>::iterator i = currentTTSActivities.begin(); i != currentTTSActivities.end(); i++) {
            TS_ASSERT_EQUALS( (*i).mOrder, f );		// this checks if at every cicle, "order = order.previous + 1"
            f++;
        }
    }

    void testPostponeActivity() {
        cout << "\n-------------------------------------------------\n";
        cout << "TEST 7 - Check of the postpone of an activity\n";

        vector<Activity> currentTTSActivities = ActivityInTTS::get<Activity>(*db,Expr(),
                                                ActivityInTTS::TodoTodaySheet==1).orderBy(Activity::MOrder).all();
        int f = 1;
        for (vector<Activity>::iterator i = currentTTSActivities.begin(); i != currentTTSActivities.end(); i++) {
            if (f==2) {
                tts->PostponeActivity(*db, (*i), *tts);	// we post-pone the second activity scheduled
                break;
            }
            f++;
        }
        currentTTSActivities = ActivityInTTS::get<Activity>(*db,Expr(),
                               ActivityInTTS::TodoTodaySheet==1).orderBy(Activity::MOrder).all();
        TS_ASSERT_EQUALS( currentTTSActivities.size(), 4 );	// test against the number of activities
    }


};
