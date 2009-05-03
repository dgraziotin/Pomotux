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
    ui->setupUi(this);

    try {
        mpAis = new ActivityInventorySheet(select<ActivityInventorySheet>(*(mpDatabase), ActivityInventorySheet::Id == 1).one());
    } catch (NotFound e) {
        mpAis = new ActivityInventorySheet(*(mpDatabase));
        mpAis->update();
    }

    connect(this,SIGNAL(DatabaseUpdated()),this,SLOT(RefreshTable()));
    emit DatabaseUpdated();
}

GuiActivityInventorySheet::~GuiActivityInventorySheet()
{
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
        if (mainController > 0)
        {
            QString description = dialog->getDescription();
            string sDescription = description.toStdString();

            float value = dialog->getDayToDeadline();
            time_t deadlineInt = mNow + value*(86400);

            Activity at(*(mpDatabase));
            at.mDescription = sDescription;
            at.mInsertionDate = (int) mNow;
            at.mDeadline = (int)deadlineInt;
            at.update();

            ActivityInventorySheet &cAis = *(mpAis);
            cAis.InsertActivity(*(mpDatabase),at,cAis);
            mpDatabase->commit();
        }
    } catch (Except e) {
        cerr << e << endl;
    }

    emit DatabaseUpdated();
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
    if (mainController > 0)
    {
        QString description = dialog->getDescription();
        float value = dialog->getDayToDeadline();
        QString idString = this->ui->ais->item(mRow, 0)->text();
        bool ok;
        int id = idString.toInt(&ok, 16);
        Activity at = select<Activity>(*(mpDatabase), Activity::Id == id).one();
        string newDescription = description.toStdString();
        at.Modify(*(mpDatabase), at, value, newDescription);
        emit DatabaseUpdated();
    }
}

void GuiActivityInventorySheet::on_InsertInTTSButton_clicked()
{
    QString idString = this->ui->ais->item(mRow, 0)->text();
    bool ok;
    int id = idString.toInt(&ok, 16);
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
    for (vector<Activity>::iterator i = currentTDTSActivities.begin(); i != currentTDTSActivities.end(); i++)
    {
        if ((*i).id == id) check = 1;
    }
    if (check == 0 )
    {
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
        QTableWidgetItem *currentActivity=new QTableWidgetItem[7];
        currentActivity[0].setText(QString((toString((*i).id)).c_str()));
        currentActivity[1].setText(QString((toString((*i).mDescription)).c_str()));
        currentActivity[2].setText(QString((toString((*i).mInsertionDate)).c_str()));
        currentActivity[3].setText(QString((toString((*i).mDeadline)).c_str()));
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

