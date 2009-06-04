
#include "insertnewactivity.hpp"
#include "ui_insertnewactivity.h"
#include <string>
#include <time.h>
#include "pomotuxexception.hpp"
#include <QMessageBox>

InsertNewActivity::InsertNewActivity(QWidget *parent, PomotuxDatabase& database) :
        QDialog(parent),
        m_ui(new Ui::InsertNewActivity)
{
    mpDatabase = &database;
    m_ui->setupUi(this);
    this->mNow=time(NULL);
    try {
        this->mpAis = new ActivityInventorySheet(select<ActivityInventorySheet>(*(mpDatabase), ActivityInventorySheet::Id == 1).one());
    } catch (NotFound e) {
        this->mpAis = new ActivityInventorySheet(*(mpDatabase));
        this->mpAis->update();
    }
    this->mpDatabase->commit();
}

InsertNewActivity::~InsertNewActivity()
{
    this->mpAis->~Persistent();
    delete this->mpAis;
    this->mpAis = NULL;
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

void InsertNewActivity::on_ButtonBox_accepted()
{
    try {
        this->mpAis = new ActivityInventorySheet(select<ActivityInventorySheet>(*(mpDatabase), ActivityInventorySheet::Id == 1).one());
    } catch (NotFound e) {
        this->mpAis = new ActivityInventorySheet(*(mpDatabase));
        this->mpAis->update();
    }

    try{
    QString description = this->m_ui->iaDescriptionLineEdit->text();
    if (description=="")throw PomotuxException("For Every Activity must be provided a Description");
    time_t deadline= mNow + (this->m_ui->iaDeadlineSpinBox->text().toInt())*(86400);

    Activity current(*(this->mpDatabase));
    current.mDescription= description.toStdString();
    current.mInsertionDate= (int) mNow;
    current.mDeadline= (int) deadline;
    current.update();

    this->mpAis->InsertActivity(*(this->mpDatabase),current,*(this->mpAis));
    this->mpDatabase->commit();
    emit DatabaseUpdated();
    this->m_ui->iaDescriptionLineEdit->setText("");
    this->m_ui->iaDeadlineSpinBox->setValue(0);
    this->hide();
    } catch (Except e) {
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

void InsertNewActivity::on_ButtonBox_rejected()
{
    this->hide();
}
