#ifndef INSERTNEWACTIVITY_H
#define INSERTNEWACTIVITY_H

#include <QtGui/QDialog>
#include "litesql.hpp"
#include "../sep/src/pomotuxdatabase.hpp"

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
    QString text;
    float dayToDeadline;
    float controller;
    PomotuxDatabase *db;

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::InsertNewActivity *m_ui;

private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();
};

#endif // INSERTNEWACTIVITY_H
