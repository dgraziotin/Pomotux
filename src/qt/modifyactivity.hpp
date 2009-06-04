/**
 * A class for Modify Activity window.
 * It allows the user to modify the description and the deadline for a selected activity.
 * It is studied for re-use, as it is completely isolated from the rest of the project.
 * The user can confirm or reject the operation.
 *
 *  @include <QtGui/QDialog>
 *  @include <litesql.hpp>
 *  @include "../pomotuxdatabase.hpp"
 *
 *  @see http://apps.sourceforge.net/trac/litesql/
 *  @see http://doc.trolltech.com/4.5/index.html
 */

#ifndef MODIFYANACTIVITY_H
#define MODIFYANACTIVITY_H

#include <QtGui/QDialog>
#include <litesql.hpp>
#include "../pomotuxdatabase.hpp"
#include <time.h>

using namespace litesql;
using namespace pomotuxdatabase;
using namespace std;

namespace Ui {
class ModifyAnActivity;
}

/**
 * A class for Modify Activity window.
 * It allows the user to modify the description and the deadline for a selected activity.
 * It is studied for re-use, as it is completely isolated from the rest of the project.
 * The user can confirm or reject the operation.
 *
 *  @see http://apps.sourceforge.net/trac/litesql/
 *  @see http://doc.trolltech.com/4.5/index.html
 */
class ModifyAnActivity : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(ModifyAnActivity)

public:
    /**
     * Constructor of a Modify Activity Graphical User Interface window.
     * @param parent a pointer to the parent widget (0 if we want a new window)
     * @param a reference to a litesql3 database
     */
    explicit ModifyAnActivity(QWidget *parent, PomotuxDatabase& database,int& id);

    /**
     * Default destructor
     */
    virtual ~ModifyAnActivity();

protected:
    virtual void changeEvent(QEvent *e);

private:
    /**
     * Default pointer created by qtCreator
     */
    Ui::ModifyAnActivity* m_ui;

    /**
     * A pointer to the litesql database in use
     */
    PomotuxDatabase* mpDatabase;

    /**
     * A reference to the selected activity
     */
    int* mrSelectedActivity;

    /**
      * A variable for storing the current time
      */
    time_t mNow;


private slots:

    /**
     * Close the window and set the control variable
     */
    void on_ButtonBox_rejected();

    /**
     * Close the window and save the values inserted by the user into the correct variables
     */
    void on_ButtonBox_accepted();

signals:

    /**
     * Signal launched when the database is updated
     */
    void DatabaseUpdated();
};

#endif // MODIFYANACTIVITY_H
