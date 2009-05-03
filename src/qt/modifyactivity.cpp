/*
    see hpp file for change needed to attribute and method names.
    Watch the Coding Standards everywhere also here!
*/

#include "modifyactivity.hpp"
#include "ui_modifyactivity.h"

ModifyAnActivity::ModifyAnActivity(QWidget *parent, PomotuxDatabase& database) :
        QDialog(parent),
        m_ui(new Ui::ModifyAnActivity)
{
    mpDatabase = &database;
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

float ModifyAnActivity::getDayToDeadline()
{
    return mDayToDeadline;
}

float ModifyAnActivity::getController()
{
    return mController;
}

QString ModifyAnActivity::getDescription()
{
    return mDescription;
}

void ModifyAnActivity::on_ButtonBox_accepted()
{
    mDescription = this->m_ui->mADescriptionLineEdit->text();
    mDayToDeadline = this->m_ui->mADeadlineSpinBox->value();
    mController = 1;
    this->close();
}

void ModifyAnActivity::on_ButtonBox_rejected()
{
    mController = 0;
    this->close();
}
