#ifndef GUIACTIVITYINVENTORYSHEET_H
#define GUIACTIVITYINVENTORYSHEET_H

#include <QtGui/QMainWindow>
#include <QTableWidget>
#include "insertnewactivity.hpp"
#include "modifyactivity.hpp"
#include <litesql.hpp>
#include "../pomotuxdatabase.hpp"
#include <time.h>
#include "preferencesdialog.hpp"
#include "aboutwindow.h"
#include "gui_todotodaysheet.hpp"
#include "pomotuxexception.hpp"

using namespace litesql;
using namespace pomotuxdatabase;
using namespace std;

namespace Ui {
class GuiActivityInventorySheet;
}

/**
 *  A class for Activity Inventory Sheet graphical user interface object. Contains all the operations regarding the interaction
 *  among the final user and Activity Inventory Sheet object in the database.
 *  It exchange signals within itself in order to maintain an high average of consistency with the database; internal signals
 *  can also be intercepted from the outside the class in case become necessary a synchronization(i.e. multiple windows inquiring the database)
 *  This class depends on several libraries and external files such as the QtGui/QMainWindow  and litesql libraries(i.e. the framework
 *  libraries used to access the sqlite database)
 *
 *  @see http://apps.sourceforge.net/trac/litesql/
 *  @see http://doc.trolltech.com/4.5/index.html
 */
class GuiActivityInventorySheet : public QMainWindow {
    Q_OBJECT

public:

    /**
     * Constructor of an Activity Inventory Sheet Graphical User Interface window.
     * @param parent a pointer to the parent widget (0 if we want a new window)
     * @param a reference to a litesql3 database
     */
    GuiActivityInventorySheet(QWidget *parent,PomotuxDatabase& database);

    /**
     * Default Destructor
     */
    ~GuiActivityInventorySheet();

private:
    /**
     * Default pointer created by qtCreator
     */
    Ui::GuiActivityInventorySheet* ui;

    /**
     * A pointer to the Todo Today Window
     */
    TodoTodaySheetGui *wTTS;

    PreferencesDialog *wPreferences;

    /**
     * A pointer to the litesql database in use
     */
    PomotuxDatabase* mpDatabase;

    /**
     * A pointer to the Activity Inventory Sheet in use
     */
    ActivityInventorySheet* mpAis;

    /**
     * A pointer to the Todo Today Sheet in use
     */
    TodoTodaySheet* mpTts;

   /**
     * A pointer to the About Window
     */
    AboutWindow* wAbout;

    /**
     * A float for memorizing the row selected by the user
     */
    float mRow;

    /**
     * A variable for saving the current date
     */
    time_t mNow;

    /**
     * Cleans the ui::ais whenever the database is updated
     */
    void Cleaner();


private slots:

    /**
     * Insert the selected Activity into the Todo Today Sheet
     */
    void on_wTtsButton_clicked();
    void on_InsertInTTSButton_clicked();

    /**
     *  Give the possibility to the user to change the description and the deadline to a selected Activity
     */
    void on_ModifyActivityButton_clicked();

    /**
     * Set a variable with the row value selected by the user
     */
    void on_ais_itemClicked(QTableWidgetItem* item);

    /**
     * Delete from the database an activity selected by the user
     */
    void on_DeleteActivityButton_clicked();

    /**
     * Creates in the database a new activity. The user can insert a description and a deadline
     */
    void on_NewActivityButton_clicked();

    /**
      * Prompt the Preference Window
      */
    void Preferences();

    /**
      * Prompt the About Window
      */
    void About();
    /**
     * Handles the signal of DatabaseUpdated() received whenever the database is modified and refreshes the window
     * @see DatabaseUpdated()
     */
    void RefreshTable();

signals:

    /**
     * Signal launched when the database is updated
     */
    void DatabaseUpdated();
};

#endif // GUIACTIVITYINVENTORYSHEET_H
