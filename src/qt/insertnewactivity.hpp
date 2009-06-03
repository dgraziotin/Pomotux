/**
 * A class for New Activity window.
 * It allows the user to insert a description and a deadline for the newer Activity
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

#ifndef INSERTNEWACTIVITY_H
#define INSERTNEWACTIVITY_H

#include <QtGui/QDialog>
#include <litesql.hpp>
#include "../pomotuxdatabase.hpp"

using namespace litesql;
using namespace pomotuxdatabase;
using namespace std;

namespace Ui {
class InsertNewActivity;
}

/**
 * A class for New Activity window.
 * It allows the user to insert a description and a deadline for the newer Activity
 * It is studied for re-use, as it is completely isolated from the rest of the project.
 * The user can confirm or reject the operation.
 *
 *  @see http://apps.sourceforge.net/trac/litesql/
 *  @see http://doc.trolltech.com/4.5/index.html
 */
class InsertNewActivity : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(InsertNewActivity)

public:
    /**
     * Constructor of a New Activity Graphical User Interface window.
     * @param parent a pointer to the parent widget (0 if we want a new window)
     * @param a reference to a litesql3 database
     */
    explicit InsertNewActivity(QWidget *parent, PomotuxDatabase& database);

    /**
     * Default Destructor
     */
    virtual ~InsertNewActivity();

protected:
    virtual void changeEvent(QEvent *e);

private:
    /**
     * Default pointer created by qtCreator
     */
    Ui::InsertNewActivity *m_ui;

    /**
     * A pointer to the litesql database in use
     */
    PomotuxDatabase* mpDatabase;

    /**
      * A pointer to the ActivityInventorySheet in use
      */
    ActivityInventorySheet *mpAis;

    /**
     * A variable for saving the current date
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

#endif // INSERTNEWACTIVITY_H
