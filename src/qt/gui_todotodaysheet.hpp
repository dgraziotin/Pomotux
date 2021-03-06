#ifndef TODOTODAYSHEETGUI_H
#define TODOTODAYSHEETGUI_H

#include <QtGui/QMainWindow>
#include <litesql.hpp>
#include "../pomotuxdatabase.hpp"
#include "pomodoro.hpp"
#include "pomotuxexception.hpp"
#include "insertnewactivity.hpp"
#include <QProcess>

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

    /**
      * Getter for the InsertActivity Window in use. This method returns a pointer to a InsertNewActivity Object.
      * It is used to synchronize the Activity Invetory Sheet table
      * @return a pointer to the current InsertActivity Window
      */
    InsertNewActivity* getInsertActivity();

    /**
      * Returns true if there is a Pomodoro running, false elsewhere.
      * @return true
      */
    bool IsPomodoroRunning();

    /**
      *  Returns the current Pomodoro
      * @return a pointer to the current Pomodoro.
      */
    Pomodoro* GetPomodoro();
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
    * A variable for storing the pomodoro length preference in minutes
    */
    int mMinutesPomodoroLength;

    /**
    * A variable for storing the path of the sound alert in QString data type
    */
    QString SoundFile;

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
     * A pointer to the Insert Activity Window
     */
    InsertNewActivity* wInsertActivity;

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
    void on_MoveActivityButton_clicked();

    /**
      * Inserts a new Activity Directly in the Activity Inventory Sheet
      */
    void on_newActivityButton_clicked();

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
    * Handles the signal of DatabaseUpdated() received from the preferences dialog everytime preferences are changed
    */
    void RefreshPreferences();

    /**
     * Tries to play a Bell file called mysound.wav in the src/qt directory.<br/>
     * First tries to use QSound, which is badly supported by distro maintainers. <br/>
     * If this fails, it forks and calls aplay to play the wav file. <br/>
     * If this also fails, it continues silenty. <br/>
     */
    void PlaySound();

    /**
     * Increments the Interruption counter everytime the user is interrupted during a pomodoro
     */
    void HandleInterruption();

signals:
    /**
      * Signal launched when the database is updated
      */
    void DatabaseUpdated();
    /**
      * Signal launched when it is necessary to play a sound
      */
    void SoundAlert();
    /**
      *
      */
    void Interruption();
};

#endif // TODOTODAYSHEETGUI_H
