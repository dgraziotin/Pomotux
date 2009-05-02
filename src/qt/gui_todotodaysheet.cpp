/*
    see hpp file for change needed to attribute and method names.
    Watch the Coding Standards everywhere also here!
*/

#include "gui_todotodaysheet.hpp"
#include "ui_gui_todotodaysheet.h"
#include <cstring>
#include <QMessageBox>
#define mins 0
#define secs 10

using namespace litesql;
using namespace pomotuxdatabase;
using namespace std;



TodoTodaySheetGui::TodoTodaySheetGui(QWidget *parent,PomotuxDatabase& database)
        : QMainWindow(parent), ui(new Ui::TodoTodaySheetGuiClass)
{
    db = &database;
    db->begin();

    ui->setupUi(this);
    try {
        rTts = new TodoTodaySheet(select<TodoTodaySheet>(*(db), TodoTodaySheet::Id == 1).one());
    } catch (NotFound e) {
        rTts = new TodoTodaySheet(*(db));
        rTts->update();
    }
    connect(this,SIGNAL(DatabaseUpdated()),this,SLOT(RefreshTable()));
}

TodoTodaySheetGui::~TodoTodaySheetGui()
{
    this->rTts->~Persistent();
    this->current->~Persistent();
    this->pomo->~Pomodoro();
    delete ui;
}



void  TodoTodaySheetGui::Cleaner()
{
    for (int i=0 ; i<ui->tableWidget->rowCount(); i++)
        for (int j=0 ; j<3; j++)
            (*(ui->tableWidget->item(i,j))).~QTableWidgetItem();
    ui->tableWidget->setRowCount(0);
}

void TodoTodaySheetGui::RefreshTable()
{
    vector<Activity> currentTTSActivities = ActivityInTTS::get<Activity>(*(db),Expr(),
                                            ActivityInTTS::TodoTodaySheet==1).orderBy(Activity::MOrder).all();
    Cleaner();
    for (vector<Activity>::iterator i = currentTTSActivities.begin(); i != currentTTSActivities.end(); i++) {
        int tablePosition= ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(tablePosition);
        QTableWidgetItem *currentActivity=new QTableWidgetItem[3];
        currentActivity[0].setText(QString((toString((*i).id)).c_str()));
        currentActivity[1].setText(QString((toString((*i).mDescription)).c_str()));
        currentActivity[2].setText(QString((toString((*i).mOrder)).c_str()));
        currentActivity[0].setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        currentActivity[1].setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled);
        currentActivity[2].setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled);
        for (int k=0; k<3; k++)
            ui->tableWidget->setItem(tablePosition,k,&currentActivity[k]);
    }
}



void TodoTodaySheetGui::on_StartActivityButton_clicked()
{

    try {
        if (this->ui->tableWidget->rowCount()==0) throw PomotuxException("There Are No Activities to be Initialized");
        int id=this->ui->tableWidget->item(0,0)->text().toInt();
        pomo = new Pomodoro(0,mins,secs);
        Activity current = ActivityInTTS::get<Activity>(*(db),Activity::Id==id,ActivityInTTS::TodoTodaySheet==rTts->id).one();
        if (!pomo->IsRunning()) {
            connect(pomo, SIGNAL(PomodoroFinished()), this, SLOT(PomodoroFinished()));
            connect(pomo, SIGNAL(PomodoroBroken()), this, SLOT(PomodoroBroken()));
            this->current = new Activity(current);
            pomo->show();
            pomo->Start();
        } else {
            pomo->show();
            QMessageBox msgBox;
            msgBox.setText("You Should First Break or Wait Untill The End of The Current Pomodoro!!");
            msgBox.exec();
        }
    } catch (PomotuxException e) {
        QMessageBox msgBox;
        msgBox.setText(e.getMessage());
        msgBox.exec();
    }
}

void TodoTodaySheetGui::PomodoroFinished()
{
    try {
        this->current->mNumPomodoro= (this->current->mNumPomodoro +1);
        this->current->update();
        pomo->hide();

        QMessageBox msgBox;
        msgBox.setText("Pomodoro Finished : Now You Should Make A Short Break");
        msgBox.exec();
    } catch (Except e) {
        QMessageBox msgBox;
        msgBox.setText("ERROR");
        msgBox.exec();
    }
}

void TodoTodaySheetGui::PomodoroBroken()
{
    pomo->~QWidget();
    pomo = new Pomodoro (0,mins,secs);
    connect(pomo, SIGNAL(PomodoroFinished()), this, SLOT(PomodoroFinished()));
    connect(pomo, SIGNAL(PomodoroBroken()), this, SLOT(PomodoroBroken()));
    QMessageBox msgBox;
    msgBox.setText("Pomodoro Broken");
    msgBox.exec();
}

void TodoTodaySheetGui::on_PostponeActivityButton_clicked()
{
    QList<QTableWidgetItem *> items = ui->tableWidget->selectedItems();
    try {
        if(items.empty())throw PomotuxException("There Are No Activities Selected");
        for (QList<QTableWidgetItem *>::iterator k = items.begin(); k<items.end(); k++) {
            QTableWidgetItem * activitiesToBePostponed = (*k);
            Activity current = ActivityInTTS::get<Activity>(*(db),Activity::Id==activitiesToBePostponed->text().toInt(),
                               ActivityInTTS::TodoTodaySheet==1).one();
            if (this->current!=NULL||this->current->id!=current.id)rTts->PostponeActivity(*(db),current,*(rTts));
        }
        emit DatabaseUpdated();
    } catch (NotFound e) {
        QMessageBox msgBox;
        msgBox.setText("ERROR");
        msgBox.exec();
    }catch (PomotuxException e){
        QMessageBox msgBox;
        msgBox.setText(e.getMessage());
        msgBox.exec();
    }
}

void TodoTodaySheetGui::on_FinishActivityButton_clicked()
{

      try {
    QList<QTableWidgetItem *> items = ui->tableWidget->selectedItems();
    if(items.empty())throw PomotuxException("There Are No Activities");
    QList<QTableWidgetItem *>::iterator k = items.begin();
    QTableWidgetItem * head = (*k);
    int id=head->text().toInt(0,10);
        Activity current = ActivityInTTS::get<Activity>(*(db),Activity::Id==id,
                           ActivityInTTS::TodoTodaySheet==rTts->id).one();
        rTts->FinishActivity(*(db),current,*(rTts));
        emit DatabaseUpdated();
    } catch (NotFound e) {
        QMessageBox msgBox;
        msgBox.setText("ERROR ");
        msgBox.exec();
    }catch (PomotuxException e){
        QMessageBox msgBox;
        msgBox.setText(e.getMessage());
        msgBox.exec();
    }
}

void TodoTodaySheetGui::on_StopActivityButton_clicked()
{
    if (pomo->IsRunning()) {
        pomo->show();
        pomo->Stop();
    }
}

void TodoTodaySheetGui::showEvent( QShowEvent * event)
{
    RefreshTable();
}
