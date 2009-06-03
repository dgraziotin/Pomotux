#include "gui_activityinventorysheet.hpp"
#include "ui_gui_activityinventorysheet.h"

#include <string>
#include <time.h>
#include <QMessageBox>

GuiActivityInventorySheet::GuiActivityInventorySheet(QWidget *parent, PomotuxDatabase& database)
        : QMainWindow(parent), ui(new Ui::GuiActivityInventorySheet)
{
    mpDatabase = &database;
    mNow = time(NULL);
    wAbout = new AboutWindow(this);
    ui->setupUi(this);

    try {
        mpAis = new ActivityInventorySheet(select<ActivityInventorySheet>(*(mpDatabase), ActivityInventorySheet::Id == 1).one());
    } catch (NotFound e) {
        mpAis = new ActivityInventorySheet(*(mpDatabase));
        mpAis->update();
    }

    wTTS = new TodoTodaySheetGui(this,*(this->mpDatabase));
    wPreferences = new PreferencesDialog (this,*(this->mpDatabase));


    // connection of signal required to refresh preferences
    connect(this->wPreferences,SIGNAL(DatabaseUpdated()),this->wTTS,SLOT(RefreshPreferences()));

    // connection of signals for refreshing tables
    connect(this->wTTS,SIGNAL(DatabaseUpdated()),this,SLOT(RefreshTable()));
    connect(this,SIGNAL(DatabaseUpdated()),this->wTTS,SLOT(RefreshTable()));
    connect(this,SIGNAL(DatabaseUpdated()),this,SLOT(RefreshTable()));

    // connection of menu bar actions
    connect(this->ui->actionExit,SIGNAL(triggered()),this,SLOT(close()));
    connect(this->ui->actionPreferences,SIGNAL(triggered()),this,SLOT(Preferences()));
    connect(this->ui->actionAbout,SIGNAL(triggered()),this,SLOT(About()));

    emit DatabaseUpdated();
    this->RefreshTable();
    this->ui->ais->setColumnWidth(0, 0);
    this->ui->ais->setColumnWidth(1, 440);
}

GuiActivityInventorySheet::~GuiActivityInventorySheet()
{
    this->mpDatabase->commit();
    this->wPreferences->~PreferencesDialog();
    this->wAbout->~AboutWindow();
    this->wTTS->~TodoTodaySheetGui();
    this->mpTts->~Persistent();
    this->mpAis->~Persistent();
    delete ui;
}

void GuiActivityInventorySheet::on_NewActivityButton_clicked()
{
    try {
        /*Calling the window for creating a new Activity*/
        InsertNewActivity *dialog = new InsertNewActivity(0, *(mpDatabase));
        dialog->show();
        dialog->exec();

        /*Control if the user pressed ok or cancel*/
        float mainController = dialog->getController();
        if (mainController > 0) {
            QString description = dialog->getDescription();
            string sDescription = description.toStdString();

            float value = dialog->getDayToDeadline();
            time_t deadlineInt = mNow + value*(86400);

            Activity at(*(mpDatabase));
            at.mDescription = sDescription;
            at.mInsertionDate = (int) mNow;
            at.mDeadline = (int)deadlineInt;
            if (at.mDescription=="")throw PomotuxException("For Every Activity must be provided a Description");
            at.update();

            ActivityInventorySheet &cAis = *(mpAis);
            cAis.InsertActivity(*(mpDatabase),at,cAis);
            mpDatabase->commit();
        }
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
    ui->DeleteActivityButton->setEnabled(false);
    ui->ModifyActivityButton->setEnabled(false);
    ui->InsertInTTSButton->setEnabled(false);
    ui->DeleteActivityButton->setEnabled(false);
}

void GuiActivityInventorySheet::on_DeleteActivityButton_clicked()
{
    QString idString = this->ui->ais->item(mRow, 0)->text();
    int id = idString.toInt();

    try {
        Activity at = select<Activity>(*(mpDatabase), Activity::Id == id).one();
        mpTts = new TodoTodaySheet(select<TodoTodaySheet>(*(mpDatabase), TodoTodaySheet::Id == 1).one());
        ActivityInventorySheet &cAis = *(mpAis);
        TodoTodaySheet &cTts = *(mpTts);
        at.Delete(*(mpDatabase), at, cAis, cTts);
        emit DatabaseUpdated();
    } catch (NotFound e) {
        mpTts = new TodoTodaySheet(*(mpDatabase));
        mpTts->update();
    }
    ui->DeleteActivityButton->setEnabled(false);
    ui->ModifyActivityButton->setEnabled(false);
    ui->InsertInTTSButton->setEnabled(false);
}


void GuiActivityInventorySheet::on_ais_itemClicked(QTableWidgetItem* item)
{
    mRow = item->row();
    ui->DeleteActivityButton->setEnabled(true);
    ui->ModifyActivityButton->setEnabled(true);
    ui->InsertInTTSButton->setEnabled(true);
}

void GuiActivityInventorySheet::on_ModifyActivityButton_clicked()
{
    ModifyAnActivity *dialog = new ModifyAnActivity(0, *(mpDatabase));
    dialog->show();
    dialog->exec();

    float mainController = dialog->getController();
    if (mainController > 0) {
        QString description = dialog->getDescription();
        float value = this->mNow+(dialog->getDayToDeadline())*(86400);
        QString idString = this->ui->ais->item(mRow, 0)->text();
        int id = idString.toInt();
        Activity at = select<Activity>(*(mpDatabase), Activity::Id == id).one();
        string newDescription = description.toStdString();
        at.Modify(*(mpDatabase), at, value, newDescription);
        ui->DeleteActivityButton->setEnabled(false);
        emit DatabaseUpdated();
    }
    ui->DeleteActivityButton->setEnabled(false);
    ui->ModifyActivityButton->setEnabled(false);
    ui->InsertInTTSButton->setEnabled(false);
}

void GuiActivityInventorySheet::on_InsertInTTSButton_clicked()
{
    QString idString = this->ui->ais->item(mRow, 0)->text();
    int id = idString.toInt();
    Activity at = select<Activity>(*(mpDatabase), Activity::Id == id).one();
    try {
        mpTts = new TodoTodaySheet(select<TodoTodaySheet>(*(mpDatabase), TodoTodaySheet::Id == 1).one());
    } catch (NotFound e) {
        mpTts = new TodoTodaySheet(*(mpDatabase));
        mpTts->update();
    }

    vector<Activity> currentTDTSActivities = ActivityInTTS::get<Activity>(*(mpDatabase),Expr(),
            ActivityInTTS::TodoTodaySheet==mpTts->id).all();
    int check = 0;
    for (vector<Activity>::iterator i = currentTDTSActivities.begin(); i != currentTDTSActivities.end(); i++) {
        if ((*i).id == id) check = 1;
    }
    if (check == 0 ) {
        ActivityInventorySheet &cAis = *(mpAis);
        TodoTodaySheet &cTts = *(mpTts);
        cTts.ScheduleActivity(*(mpDatabase), at, cAis, cTts);
        mpDatabase->commit();
        emit DatabaseUpdated();
    } else {
        QMessageBox msgBox;
        msgBox.setText("Activity already present in the TTS");
        msgBox.exec();
    }
    ui->DeleteActivityButton->setEnabled(false);
    ui->ModifyActivityButton->setEnabled(false);
    ui->InsertInTTSButton->setEnabled(false);

}

void  GuiActivityInventorySheet::Cleaner()
{
    for (int i=0 ; i < this->ui->ais->rowCount(); i++)
        for (int j=0 ; j<7; j++)
            (*(ui->ais->item(i,j))).~QTableWidgetItem();
    this->ui->ais->setRowCount(0);
}

void GuiActivityInventorySheet::RefreshTable()
{
    Cleaner();

    vector<Activity> currentAISActivities = ActivityInAIS::get<Activity>(*(mpDatabase),Expr(),
                                            ActivityInAIS::ActivityInventorySheet==mpAis->id).all();

    for (vector<Activity>::iterator i = currentAISActivities.begin(); i != currentAISActivities.end(); i++) {
        int tablePosition= ui->ais->rowCount();
        this->ui->ais->insertRow(tablePosition);
        this->ui->ais->setColumnWidth(0, 0);
        this->ui->ais->setColumnWidth(1, 440);
        QTableWidgetItem *currentActivity=new QTableWidgetItem[7];
        currentActivity[0].setText(QString((toString((*i).id)).c_str()));
        currentActivity[1].setText(QString((toString((*i).mDescription)).c_str()));
        currentActivity[2].setText(QString(((*i).GetInsertionDate()).c_str()));
        currentActivity[3].setText(QString(((*i).GetDeadline()).c_str()));
        currentActivity[4].setText(QString((toString((*i).mOrder)).c_str()));
        currentActivity[5].setText(QString((toString((*i).mNumPomodoro)).c_str()));
        currentActivity[6].setText(((*i).mIsFinished)?"finished":"not finished");

        currentActivity[0].setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        currentActivity[1].setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        currentActivity[2].setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        currentActivity[3].setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        currentActivity[4].setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        currentActivity[5].setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        currentActivity[6].setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        for (int k=0; k<7; k++)
            ui->ais->setItem(tablePosition,k,&currentActivity[k]);
    }
}

void GuiActivityInventorySheet::Preferences()
{
    this->wPreferences->show();
}

void GuiActivityInventorySheet::About()
{
    this->wAbout->show();
}
void GuiActivityInventorySheet::on_wTtsButton_clicked()
{
    this->wTTS->show();
}
