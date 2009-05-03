
#include "insertnewactivity.hpp"
#include "ui_insertnewactivity.h"
#include <string>
#include <time.h>

InsertNewActivity::InsertNewActivity(QWidget *parent, PomotuxDatabase& database) :
        QDialog(parent),
        m_ui(new Ui::InsertNewActivity)
{
    mpDatabase = &database;
    m_ui->setupUi(this);
}

InsertNewActivity::~InsertNewActivity()
{
    delete m_ui;
}

float InsertNewActivity::getDayToDeadline()
{
    return mDayToDeadline;
}

float InsertNewActivity::getController()
{
    return mController;
}

QString InsertNewActivity::getDescription()
{
    return mDescription;
}

void InsertNewActivity::changeEvent(QEvent *e)
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

void InsertNewActivity::on_ButtonBox_accepted()
{
    mDescription = this->m_ui->iaDescriptionLineEdit->text();
    mDayToDeadline = this->m_ui->iaDeadlineSpinBox->value();
    mController = 1;
    this->close();
}

void InsertNewActivity::on_ButtonBox_rejected()
{
    mController = 0;
    this->close();
}
