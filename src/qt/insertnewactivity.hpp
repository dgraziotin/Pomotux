/*
 * TODO: Doxygen comments!
 */

#ifndef INSERTNEWACTIVITY_H
#define INSERTNEWACTIVITY_H

#include <QtGui/QDialog>
#include "litesql.hpp"
#include "../pomotuxdatabase.hpp"

using namespace litesql;
using namespace pomotuxdatabase;
using namespace std;

namespace Ui {
class InsertNewActivity;
}

class InsertNewActivity : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(InsertNewActivity)
public:
    explicit InsertNewActivity(QWidget *parent, PomotuxDatabase& database);
    virtual ~InsertNewActivity();
    QString text;           // put it prive; Coding Standards, should be mText but you should use a better name,like mDescription
    float dayToDeadline;    // put it private, CS
    float controller;   // put it private, CS
    PomotuxDatabase *db;    // put it private; CS: PomotuxDatabase* mpDatabase

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::InsertNewActivity *m_ui;    // what does this mean? Choose a better name and respect CS

private slots:
    void on_buttonBox_rejected();   // if possible, on_ButtonBox_rejected()
    void on_buttonBox_accepted();   // etc.
};

#endif // INSERTNEWACTIVITY_H
