#ifndef PREFERENCESDIALOG_HPP
#define PREFERENCESDIALOG_HPP

#include <QtGui/QDialog>
#include <QMessageBox>
#include <cstring>
#include <litesql.hpp>
#include "../pomotuxdatabase.hpp"
#include "pomotuxexception.hpp"

using namespace litesql;
using namespace pomotuxdatabase;
using namespace std;

namespace Ui {
class PreferencesDialog;
}

/**
  * A class for Preference Dialog Graphical User Interface
  * It Contains all the operations and representations of data necessary to let the final user sets the program settings.
  * Preference dialog exanchanges signals with the Todo Today Sheet Window in order to maintain the consistency with user choices
  * and how tasks are actually carried out.
  * This class depends on several libraries: QtGui/QDialog and litesql libraries.
  * This class uses the taylor-made class PomotuxException to handle internal Exceptions whenever it become necessary
  *
  * @see PomotuxExcetion.hpp
  * @see PomotuxDatabase.hpp
  * @see http://apps.sourceforge.net/trac/litesql/
  */
class PreferencesDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(PreferencesDialog)
public:

    /**
      * Window Constructor
      * @param parent a pointer to the parent widget
      * @param database a reference to the PomotuxDatabase database in use
      */
    explicit PreferencesDialog(QWidget *parent,PomotuxDatabase& database);

    /**
      * Default Destructor
      */
    virtual ~PreferencesDialog();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::PreferencesDialog *m_ui;

    /**
      * A pointer to the litesql Database in use
      */
    PomotuxDatabase *mpDatabase;

private slots:

    /**
      * Rejects all the changes made to Settings it simply hide the window and nothing will be sent to the database
      */
    void on_buttonBox_rejected();

    /**
      * Confirms the changes made to Settings and sends the new settings to the database
      */
    void on_buttonBox_accepted();
signals:

    /**
      * Signal Emitted everytime preferences are updated
      */
    void DatabaseUpdated();
};

#endif // PREFERENCESDIALOG_HPP
