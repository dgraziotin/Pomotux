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

class PreferencesDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(PreferencesDialog)
public:
    explicit PreferencesDialog(QWidget *parent,PomotuxDatabase& database);
    virtual ~PreferencesDialog();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::PreferencesDialog *m_ui;
    PomotuxDatabase *mpDatabase;

private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();
signals:
    void DatabaseUpdated();
};

#endif // PREFERENCESDIALOG_HPP
