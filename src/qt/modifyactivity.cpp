/*
    see hpp file for change needed to attribute and method names.
    Watch the Coding Standards everywhere also here!
*/

#include "modifyactivity.hpp"
#include "ui_modifyactivity.h"
#include <QMessageBox>
#include "pomotuxexception.hpp"

ModifyAnActivity::ModifyAnActivity(QWidget *parent, PomotuxDatabase& database, int& id) :
        QDialog(parent),
        m_ui(new Ui::ModifyAnActivity)
{
    mpDatabase = &database;
    this->mNow = time(NULL);
    this->mrSelectedActivity = &id;
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


void ModifyAnActivity::on_ButtonBox_accepted()
{
    try{
    Activity current = select<Activity>(*(mpDatabase), Activity::Id == *(this->mrSelectedActivity)).one();
    QString newDescription = this->m_ui->mADescriptionLineEdit->text();
    time_t deadline= mNow + (this->m_ui->mADeadlineSpinBox->text().toInt())*(86400);
    current.Modify(*(mpDatabase), current, (int)deadline , newDescription.toStdString());
    emit DatabaseUpdated();
    this->hide();
    } catch(Except e){
        ostringstream errorMsg;
        errorMsg <<"liteSQL ERROR :"<< e;
        QMessageBox msgBox;
        msgBox.setText(errorMsg.str().c_str());
        msgBox.exec();
    } catch(PomotuxException e){
        QMessageBox msgBox;
        msgBox.setText(e.getMessage());
        msgBox.exec();
    }
}

void ModifyAnActivity::on_ButtonBox_rejected()
{
    this->hide();
}
