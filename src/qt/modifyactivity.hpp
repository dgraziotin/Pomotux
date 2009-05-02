/*
 * TODO: doxygen comments!
 */
#ifndef MODIFYANACTIVITY_H
#define MODIFYANACTIVITY_H

#include <QtGui/QDialog>
#include "litesql.hpp"
#include "../pomotuxdatabase.hpp"

using namespace litesql;
using namespace pomotuxdatabase;
using namespace std;

namespace Ui {

class ModifyAnActivity;
}

class ModifyAnActivity : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(ModifyAnActivity)
public:
    explicit ModifyAnActivity(QWidget *parent, PomotuxDatabase& database);
    virtual ~ModifyAnActivity();
    PomotuxDatabase *db;    // make private, Coding Standards: PomotuxDatabase* mpDatabase
    QString text;           // make private, use mDescription
    float dayToDeadline;    // make private, CS

protected:
    virtual void changeEvent(QEvent *e);    // ChangeEvent()

private:
    Ui::ModifyAnActivity *m_ui;     // choose a better name, CS

private slots:
    void on_buttonBox_rejected();   // if possible, use on_ButtonBox_rejected()
    void on_buttonBox_accepted();   // auch hier, ja
};

#endif // MODIFYANACTIVITY_H
