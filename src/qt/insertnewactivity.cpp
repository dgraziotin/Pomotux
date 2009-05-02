/*
 * TODO: read hpp file and change methods and attributes names!
 */
#include "insertnewactivity.hpp"
#include "ui_insertnewactivity.h"
#include <string>
#include <time.h>

InsertNewActivity::InsertNewActivity(QWidget *parent, PomotuxDatabase& database) :
        QDialog(parent),
        m_ui(new Ui::InsertNewActivity)
{
    db = &database;
    m_ui->setupUi(this);
}

InsertNewActivity::~InsertNewActivity()
{
    delete m_ui;
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

void InsertNewActivity::on_buttonBox_accepted()
{
    text = this->m_ui->iaDescriptionLineEdit->text();
    dayToDeadline = this->m_ui->iaDeadlineSpinBox->value();
    controller = 1;
    this->close();
}

void InsertNewActivity::on_buttonBox_rejected()
{
    controller = 0;
    this->close();
}
