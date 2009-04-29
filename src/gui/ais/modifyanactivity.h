#ifndef MODIFYANACTIVITY_H
#define MODIFYANACTIVITY_H

#include <QtGui/QDialog>
#include "litesql.hpp"
#include "../sep/src/pomotuxdatabase.hpp"

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
    PomotuxDatabase *db;
    QString text;
    float dayToDeadline;

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::ModifyAnActivity *m_ui;

private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();
};

#endif // MODIFYANACTIVITY_H
