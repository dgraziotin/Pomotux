#ifndef TODOTODAYSHEETGUI_H
#define TODOTODAYSHEETGUI_H

#include <QtGui/QMainWindow>
#include <litesql.hpp>
#include "../pomotuxdatabase.hpp"
#include "pomodoro.hpp"
#include "pomotuxexception.hpp"
#include "insertnewactivity.hpp"
#include <time.h>

using namespace litesql;
using namespace pomotuxdatabase;
using namespace std;

namespace Ui {
class TodoTodaySheetGuiClass;
}

/**
 *  A class for Todo Today Sheet graphical user interface object.
 *  Contains all the operations regarding the interaction
 *  among the final user and Todo Today Sheet object in the database.
 *  It has been implemented on the purpose but it grants a lot of elasticity for re-use thanks to QT libraries contribution.
 *  It exchange signals within itself in order to maintain an high average of consistency with the database; internal signals
 *  can also be intercepted from the outside the class in case it becomes necessary synchronization(i.e. multiple windows inquiring the database)
 *  This class depends on several libraries and external files such as the QtGui/QMainWindow  and litesql libraries(i.e. the framework
 *  libraries used to access the sqlite database)
 *  @see http://apps.sourceforge.net/trac/litesql/
 *  @see http://doc.trolltech.com/4.5/index.html
 *
 */
class TodoTodaySheetGui : public QMainWindow {
    Q_OBJECT

public:
    /**
     * Constructor of a Todo Today Sheet Graphical User Interface window.
     * @param parent a pointer to the parent widget (0 if we want a new window)
     * @param database a reference to a litesql3 database
     */
    TodoTodaySheetGui(QWidget *parent,PomotuxDatabase& database);

    /**
      * Default Destructor
      */
    ~TodoTodaySheetGui();

private:
    /**
    * A pointer to the litesql database in use
    */
    PomotuxDatabase *mpDatabase;

    /**
    * A pointer to a Pomodoro which is Shown and Set either when an Activty is Started/Stopped or when the Pomodoro finishes
    */
    Pomodoro *mpPomodoro;

    /**
    * A variable for counting the interruption during the session
    */
    int mNumInterruption;

    /**
    * A pointer to the Activity that is at the momenent under a Pomodoro
    */
    Activity *mpCurrentActivity;

    /**
    * A pointer to the Todo Today Sheet in use
    */
    TodoTodaySheet *mpTts;

    /**
     * A pointer to the Activity Inventory Sheet in use
     */
    ActivityInventorySheet* mpAis;

    /**
       * An integer to store the number of consecutive pomodoro taken by the user in order to inform him when to take a longer break
       */
    int mConsecutivePomodoro;

    /**
     * A variable for saving the current date
     */
    time_t mNow;

    Ui::TodoTodaySheetGuiClass *ui;
    /**
    * Cleans the ui::tableWidget whenever the database is updated
    */
    void Cleaner();

    /**
    * Processes the change of priority once all prelimary controls are made. It is called from the SLOT assigned to the click of MoveActivityButton
    *
    * @param magnitude a positive integer representing the number of position of the change
    * @param direction an integer representing the direction of the change (i.e. -1 upshift +1 downshift)
    * @param activityToMove a reference to an Activity obj representing the activity to move
    * @see on_MoveActivityButton_clicked()
    */
    void ChangeActivityPriority(int magnitude,int direction,Activity& activityToMove);

private slots:
    /**
    * Reads the input from ui::MoveMagnitudeBox and ui::MoveDirectionBox checks all the preliminary controls and then call the ChangeActivityPriority()
    * function
    *
    * @see ChangeActivityPriority(int magnitude,int direction,Activity& activityToMove)
    */
    void on_newActivityButton_clicked();
    void on_MoveActivityButton_clicked();

    /**
       * Breaks the Pomodoro of the current activity
       */
    void on_StopActivityButton_clicked();

    /**
    * Throws out all the selected Activities from the Todo Today Sheet
    */
    void on_PostponeActivityButton_clicked();

    /**
    * Starts the pomodoro of the activity placed in the top of the Todo Today Sheet
    */
    void on_StartActivityButton_clicked();

    /**
    * Finishes the selected Activity by throwing it out of the Todo Today Sheet and setting the activity flag mIsFinished to true
    */
    void on_FinishActivityButton_clicked();

    /**
    * Handles the signal of PomodoroFinished() received from mpPomodoro sending an alert to the user and incrementing the activity
    * attribute mNumPomodoro by one.
    * @see pomodoro.hpp
    */
    void PomodoroFinished();

    /**
    * Handles the signal of PomodoroBroken() received from mpPomodoro prompting the user an alert message
    * @see pomodoro.hpp
    */
    void PomodoroBroken();

    /**
    * Handles the signal of DatabaseUpdated() received whenever the database is modified and refreshes the window
    * @see DatabaseUpdated()
    */
    void RefreshTable();

    /**
    * Handles the signal of DatabaseUpdated() received whever the preferences are changed and starts using the new parameters
    * @see DatabaseUpdated()
    */
    RefreshPreferences();

signals:
    /**
      * Signal launched when the database is updated
      */
    void DatabaseUpdated();
};

#endif // TODOTODAYSHEETGUI_H
