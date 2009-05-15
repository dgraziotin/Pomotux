#include "preferencesdialog.hpp"
#include "ui_preferencesdialog.h"
#include <iostream>
#include <QFileDialog>
#include <QDir>

using namespace litesql;
using namespace pomotuxdatabase;
using namespace std;

PreferencesDialog::PreferencesDialog(QWidget *parent,PomotuxDatabase& database) :
        QDialog(parent),
        m_ui(new Ui::PreferencesDialog)
{
    this->mpDatabase= &database;
    this->mpDatabase->begin();
    this->m_ui->setupUi(this);

    try {
        Settings length= select<Settings>(*(this->mpDatabase), Settings::MName=="length").one();
        this->m_ui->minutes->setValue(atoi(length.mValue));
    } catch (NotFound e) {
        Settings length(*(this->mpDatabase));
        length.mName= "length";
        length.mValue = "25";
        length.update();
    } catch (Except e) {
        ostringstream errorMsg;
        errorMsg <<"liteSQL ERROR :"<< e;
        QMessageBox msgBox;
        msgBox.setText(errorMsg.str().c_str());
        msgBox.exec();
    }
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
    //this->m_ui->LibraryPath->text();
    //this->m_ui->SoundFile->currentText();
    try {
        Settings length = select<Settings>(*(this->mpDatabase), Settings::MName=="length").one();
        if (length.mValue!= this->m_ui->minutes->text().toStdString()) length.mValue=this->m_ui->minutes->text().toStdString();
        length.update();
    } catch (NotFound e) {
        Settings length(*(this->mpDatabase));
        length.mName= "length";
        length.mValue = "25";
        length.update();
    } catch (Except e) {
        ostringstream errorMsg;
        errorMsg <<"liteSQL ERROR :"<< e;
        QMessageBox msgBox;
        msgBox.setText(errorMsg.str().c_str());
        msgBox.exec();
    } catch (PomotuxException e) {
        QMessageBox msgBox;
        msgBox.setText(e.getMessage());
        msgBox.exec();
    }
    emit DatabaseUpdated();
    this->mpDatabase->commit();
    this->hide();
}

void PreferencesDialog::on_buttonBox_rejected()
{
    this->hide();
}

void PreferencesDialog::on_SearchLibrary_clicked()
{
    QFileDialog test(this,Qt::Dialog); // Here is Just some testing
    test.setWindowTitle("Open");
    test.setDirectory(QDir::root());
    test.setViewMode(QFileDialog::Detail);

    QStringList filters;
    filters << "Audio files (*.wav)";
    test.setNameFilters(filters);

    test.show();
    test.exec();

}
