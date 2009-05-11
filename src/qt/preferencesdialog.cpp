#include "preferencesdialog.hpp"
#include "ui_preferencesdialog.h"


using namespace litesql;
using namespace pomotuxdatabase;
using namespace std;

PreferencesDialog::PreferencesDialog(QWidget *parent,PomotuxDatabase& database) :
    QDialog(parent),
    m_ui(new Ui::PreferencesDialog)
{
    m_ui->setupUi(this);
}

PreferencesDialog::~PreferencesDialog()
{
    delete m_ui;
}

void PreferencesDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void PreferencesDialog::on_buttonBox_accepted()
{

}

void PreferencesDialog::on_buttonBox_rejected()
{
    this->close();
}
