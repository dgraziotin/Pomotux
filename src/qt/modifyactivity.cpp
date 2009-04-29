#include "modifyactivity.hpp"
#include "ui_modifyanactivity.h"

ModifyAnActivity::ModifyAnActivity(QWidget *parent, PomotuxDatabase& database) :
    QDialog(parent),
    m_ui(new Ui::ModifyAnActivity)
{
    db = &database;
    m_ui->setupUi(this);
}

ModifyAnActivity::~ModifyAnActivity()
{
    delete m_ui;
}

void ModifyAnActivity::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ModifyAnActivity::on_buttonBox_accepted()
{
text = this->m_ui->mADescriptionLineEdit->text();
dayToDeadline = this->m_ui->mADeadlineSpinBox->value();
this->close();
}

void ModifyAnActivity::on_buttonBox_rejected()
{
    this->close();
}
