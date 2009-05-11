#ifndef PREFERENCESDIALOG_HPP
#define PREFERENCESDIALOG_HPP

#include <QtGui/QDialog>
#include <litesql.hpp>
#include "../pomotuxdatabase.hpp"

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

private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();
};

#endif // PREFERENCESDIALOG_HPP
