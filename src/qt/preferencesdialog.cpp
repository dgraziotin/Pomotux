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

    connect(this,SIGNAL(DatabaseUpdated()),this,SLOT(RefreshSettings()));
    emit DatabaseUpdated();
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

       try {
        if(!QDir(this->m_ui->LibraryPath->text()).exists())throw PomotuxException("the chosen directory doesn't exist");
        if(!QDir(this->m_ui->LibraryPath->text()).isReadable())throw PomotuxException("the chosen directory cannot be read check your permissions");
        Settings SoundLib = select<Settings>(*(this->mpDatabase), Settings::MName=="SoundLib").one();
        if (SoundLib.mValue!= this->m_ui->LibraryPath->text().toStdString()) SoundLib.mValue=this->m_ui->LibraryPath->text().toStdString();
        SoundLib.update();
    } catch (NotFound e) {
        Settings SoundLib(*(this->mpDatabase));
        SoundLib.mName="SoundLib";
        SoundLib.mValue="";
        SoundLib.update();
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

       try {
        QString filepath=this->m_ui->LibraryPath->text() +"/" +this->m_ui->SoundFile->currentText() ;
        if(!QFileInfo(filepath).exists())throw PomotuxException("the chosen file doesn't exist");
        if(!QFileInfo(filepath).isReadable())throw PomotuxException("the chosen file cannot be read check your permissions");
        Settings SoundFile = select<Settings>(*(this->mpDatabase), Settings::MName=="SoundFile").one();
        if (SoundFile.mValue!= this->m_ui->SoundFile->currentText().toStdString()) SoundFile.mValue=this->m_ui->SoundFile->currentText().toStdString();
        SoundFile.update();
    } catch (NotFound e) {
        Settings SoundFile(*(this->mpDatabase));
        SoundFile.mName="SoundFile";
        SoundFile.mValue="";
        SoundFile.update();
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
    this->mpDatabase->commit();

    emit DatabaseUpdated();

    this->hide();
}

void PreferencesDialog::on_buttonBox_rejected()
{
    this->hide();
}

void PreferencesDialog::on_SearchLibrary_clicked()
{
    QFileDialog test(this,Qt::Dialog);

    test.setDirectory(QDir::home());
    test.setViewMode(QFileDialog::Detail);
    test.setAcceptMode(QFileDialog::AcceptOpen);
    test.setFileMode(QFileDialog::ExistingFile);

    QStringList filters;
    filters << "Audio files (*.wav)";
    test.setNameFilters(filters);
    connect (&test,SIGNAL(fileSelected ( const QString &)),this,SLOT(RefreshFile(const QString &)));

    test.show();
    test.exec();
}

void  PreferencesDialog::RefreshFile(const QString &file)
{
        try{
             if(file=="")throw NotFound("First Start");
             QFileInfo myFile(file);
             QDir myPath= myFile.absoluteDir();
             this->m_ui->LibraryPath->setText(myPath.path());

             QStringList filters;
             filters <<"*.wav";
             QList<QString> files = myPath.entryList(filters,QDir::AllEntries,QDir::Name);

             if(files.empty())throw PomotuxException("No Entries Found");
             this->m_ui->SoundFile->clear();
             this->m_ui->SoundFile->addItem(myFile.fileName());
             for(QList<QString>::iterator it= files.begin();it<files.end();it++)
                 if((*it)!=myFile.fileName())this->m_ui->SoundFile->addItem((*it));
        }catch(NotFound e){
            this->m_ui->LibraryPath->setText("");
            this->m_ui->SoundFile->clear();
        }catch(PomotuxException e){
            QMessageBox msgBox;
            msgBox.setText(e.getMessage());
            msgBox.exec();
        }
}


void PreferencesDialog::RefreshSettings()
{
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

    QString filePath="";

    try{
        Settings SoundLib= select<Settings>(*(this->mpDatabase), Settings::MName=="SoundLib").one();
        this->m_ui->LibraryPath->setText(QString((toString(SoundLib.mValue)).c_str()));
        filePath += QString((toString(SoundLib.mValue)).c_str());
    } catch (NotFound e) {
        Settings SoundLib(*(this->mpDatabase));
        SoundLib.mName= "SoundLib";
        SoundLib.mValue = "";
        SoundLib.update();
    } catch (Except e) {
        ostringstream errorMsg;
        errorMsg <<"liteSQL ERROR :"<< e;
        QMessageBox msgBox;
        msgBox.setText(errorMsg.str().c_str());
        msgBox.exec();
    }
    filePath+="/";
        try{
        Settings SoundFile= select<Settings>(*(this->mpDatabase), Settings::MName=="SoundFile").one();
        filePath += QString((toString(SoundFile.mValue)).c_str());
    } catch (NotFound e) {
        Settings SoundFile(*(this->mpDatabase));
        SoundFile.mName= "SoundFile";
        SoundFile.mValue = "";
        SoundFile.update();
    } catch (Except e) {
        ostringstream errorMsg;
        errorMsg <<"liteSQL ERROR :"<< e;
        QMessageBox msgBox;
        msgBox.setText(errorMsg.str().c_str());
        msgBox.exec();
    } catch (PomotuxException e){
        QMessageBox msgBox;
        msgBox.setText(e.getMessage());
        msgBox.exec();
    }
    RefreshFile(filePath);
}
