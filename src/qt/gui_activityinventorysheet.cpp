/*
    see hpp file for change needed to attribute and method names.
    Watch the Coding Standards everywhere also here!
*/

#include "gui_activityinventorysheet.hpp"
#include "ui_gui_activityinventorysheet.h"
#include <string>
#include <time.h>
#include <QMessageBox>

GuiActivityInventorySheet::GuiActivityInventorySheet(QWidget *parent, PomotuxDatabase& database)
        : QMainWindow(parent), ui(new Ui::GuiActivityInventorySheet)
{
    db = &database;
    now = time(NULL);
    ui->setupUi(this);
    try {
        /* MEMORY LEAK: rAis is not destroyed anywhere */
        rAis = new ActivityInventorySheet(select<ActivityInventorySheet>(*(db), ActivityInventorySheet::Id == 1).one());
    } catch (NotFound e) {
        rAis = new ActivityInventorySheet(*(db));
        rAis->update();
    }
    connect(this,SIGNAL(DatabaseUpdated()),this,SLOT(RefreshTable()));
}

GuiActivityInventorySheet::~GuiActivityInventorySheet()
{
    delete ui;
}

void GuiActivityInventorySheet::on_newActivityButton_clicked()
{
    try {
        /*Calling the window for creating a new Activity*/
        InsertNewActivity *dialog = new InsertNewActivity(0, *(db));
        dialog->show();
        dialog->exec();
        mainController = dialog->controller;
        /*casting for the description*/
        description = &dialog->text;
        string sDescription = description->toStdString();

        value = &dialog->dayToDeadline;
        time_t deadlineInt = now + *(value)*(86400);

        Activity at(*(db));
        at.mDescription = sDescription;
        at.mInsertionDate = (int) now;
        at.mDeadline = (int)deadlineInt;
        at.update();
        ActivityInventorySheet &cAis = *(rAis);
        cAis.InsertActivity(*(db),at,cAis);
        db->commit();
    } catch (Except e) {
        cerr << e << endl;
    }
    emit DatabaseUpdated();
}

void GuiActivityInventorySheet::on_deleteActivityButton_clicked()
{
    QString idString = this->ui->ais->item(row, 0)->text();

    int id = idString.toInt();
    try {
        Activity at = select<Activity>(*(db), Activity::Id == id).one();
        /* MEMORY LEAK: rTts is not destroyed anywhere */
        rTts = new TodoTodaySheet(select<TodoTodaySheet>(*(db), TodoTodaySheet::Id == 1).one());
        ActivityInventorySheet &cAis = *(rAis);
        TodoTodaySheet &cTts = *(rTts);
        at.Delete(*(db), at, cAis, cTts);
        emit DatabaseUpdated();
    } catch (NotFound e) {
        rTts = new TodoTodaySheet(*(db));
        rTts->update();
    }
}


void GuiActivityInventorySheet::on_ais_itemClicked(QTableWidgetItem* item)
{
    row = item->row();
}

void GuiActivityInventorySheet::on_modifyActivityButton_clicked()
{
    ModifyAnActivity *dialog = new ModifyAnActivity(0, *(db));
    dialog->show();
    dialog->exec();
    description = &dialog->text;
    value = &dialog->dayToDeadline;
    QString idString = this->ui->ais->item(row, 0)->text();
    bool ok;
    int id = idString.toInt(&ok, 16);
    Activity at = select<Activity>(*(db), Activity::Id == id).one();
    string newDescription = description->toStdString();
    at.Modify(*(db), at, *(value), newDescription);
    emit DatabaseUpdated();
}
void GuiActivityInventorySheet::on_insertInTTSButton_clicked()
{
    QString idString = this->ui->ais->item(row, 0)->text();
    bool ok;
    int id = idString.toInt(&ok, 16);
    Activity at = select<Activity>(*(db), Activity::Id == id).one();
    try {
        rTts = new TodoTodaySheet(select<TodoTodaySheet>(*(db), TodoTodaySheet::Id == 1).one());
    } catch (NotFound e) {
        rTts = new TodoTodaySheet(*(db));
        rTts->update();
    }
    ActivityInventorySheet &cAis = *(rAis);
    TodoTodaySheet &cTts = *(rTts);
    cTts.ScheduleActivity(*(db), at, cAis, cTts);
    db->commit();
    emit DatabaseUpdated();
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

    vector<Activity> currentAISActivities = ActivityInAIS::get<Activity>(*(db),Expr(),
                                            ActivityInAIS::ActivityInventorySheet==rAis->id).all();

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
        currentActivity[1].setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled);
        currentActivity[2].setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled);
        currentActivity[3].setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled);
        currentActivity[4].setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled);
        currentActivity[5].setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled);
        currentActivity[6].setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled);
        for (int k=0; k<7; k++)
            ui->ais->setItem(tablePosition,k,&currentActivity[k]);
    }
}


void GuiActivityInventorySheet::showEvent( QShowEvent * event)
{
    RefreshTable();
}

