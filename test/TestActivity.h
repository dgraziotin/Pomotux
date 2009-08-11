// MyTestSuite.h
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

class ActivityTest : public CxxTest::TestSuite {
public:
    PomotuxDatabase* db;
    ActivityInventorySheet* ais;
    TodoTodaySheet* tts;
    time_t seconds;

    void setUp() {
        try {
            db = new PomotuxDatabase("sqlite3", "database=testpomotux.db");
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

    void testCreateOneActivity() {
        cout << "\n-------------------------------------------------\n";
        cout << "TEST 1 - Activity Creation and retrieve\n";
        Activity at1(*(db));
        at1.mDescription = "A Description for Activity";
        at1.mInsertionDate = (int) seconds;
        at1.mDeadline = (int) seconds + (int) 90000;
        at1.mIsFinished = false;
        at1.mNumPomodoro = 5;
        at1.mOrder = 98;
        at1.update();
        ais->InsertActivity(*(db),at1,*(ais));		// insert the activity automatically in the AIS
        db->commit();


        Activity at2 = select<Activity>(*db, Activity::Id == at1.id).one();

        TS_ASSERT( at1.mDescription == at2.mDescription );
        TS_ASSERT( at1.mInsertionDate == at2.mInsertionDate );
        TS_ASSERT( at1.mDeadline == at2.mDeadline );
        TS_ASSERT( at1.mIsFinished == at2.mIsFinished );
        TS_ASSERT( at1.mNumPomodoro == at2.mNumPomodoro );

    } catch (Except e) {
        cerr << e << endl;
    }


    void testModifyActivity() {
        cout << "\n-------------------------------------------------\n";
        cout << "TEST 2 - Modify a random activity of 10 created \n";
        string newDescription = "A new Description";
		
        /* initialize random seed: */
        srand ( time(NULL) );

        /* generate secret number: */
        int rNumber = rand() % 10 + 1;


        Activity at = select<Activity>(*db, Activity::Id == rNumber).one();
        at.Modify(*(db), at, 0, newDescription);
        at.update();

        Activity at2 = select<Activity>(*db, Activity::Id == rNumber).one();
        TS_ASSERT_EQUALS( at.mDescription,at2.mDescription );
    }

    void testDeleteActivity() {
        cout << "\n-------------------------------------------------\n";
        cout << "TEST 3 - Delete a random Activity of 10 created\n";

        /* initialize random seed: */
        srand ( time(NULL) );

        /* generate secret number: */
        int rNumber = rand() % 10 + 1;

        Activity at = select<Activity>(*db, Activity::Id == rNumber).one();
        at.Delete(*db, at, *ais, *tts);
        try {
            Activity at2 = select<Activity>(*db, Activity::Id == rNumber).one();
        } catch (NotFound e) {
            TS_ASSERT_EQUALS( 0,0 );
        }
    }

};
