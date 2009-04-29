#include "gui_todotodaysheet.hpp"
#include "ui_gui_todotodaysheet.h"
#include <cstring>
#include <QMessageBox>


using namespace litesql;
using namespace pomotuxdatabase;
using namespace std;



TodoTodaySheetGui::TodoTodaySheetGui(QWidget *parent,PomotuxDatabase& database)
    : QMainWindow(parent), ui(new Ui::TodoTodaySheetGuiClass)
{
    db = &database;
    pomo = new Pomodoro(0,25,00);
 //   connect(*(pomo),SIGNAL(PomodoroFinished()),this,SLOT(incrementPomodoro()));

    ui->setupUi(this);
    refreshTable();
}

TodoTodaySheetGui::~TodoTodaySheetGui()
{
    delete ui;
}



void  TodoTodaySheetGui::cleaner()
{
    for (int i=0 ;i<ui->tableWidget->rowCount();i++)
    for (int j=0 ;j<3;j++)
    (*(ui->tableWidget->item(i,j))).~QTableWidgetItem();
    ui->tableWidget->setRowCount(0);
}

void TodoTodaySheetGui::refreshTable()
{
    vector<Activity> currentTTSActivities = ActivityInTTS::get<Activity>(*(db),Expr(),
                                ActivityInTTS::TodoTodaySheet==1).orderBy(Activity::MOrder).all();
    cleaner();
    for (vector<Activity>::iterator i = currentTTSActivities.begin(); i != currentTTSActivities.end(); i++)
    {
        int tablePosition= ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(tablePosition);
        QTableWidgetItem *currentActivity=new QTableWidgetItem[3];
        currentActivity[0].setText(QString((toString((*i).id)).c_str()));
        currentActivity[1].setText(QString((toString((*i).mDescription)).c_str()));
        currentActivity[2].setText(QString((toString((*i).mOrder)).c_str()));
        currentActivity[0].setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        currentActivity[1].setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled);
        currentActivity[2].setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled);
        for (int k=0;k<3;k++)
        ui->tableWidget->setItem(tablePosition,k,&currentActivity[k]);
    }
}



void TodoTodaySheetGui::on_startActivityButton_clicked()
{
    pomo->show();
    pomo->Start();
    /*
    try
    {
    QList<QTableWidgetItem *> items = this->ui->tableWidget->selectedItems();
     QList<QTableWidgetItem *>::iterator k = items.begin();
     QTableWidgetItem * head = (*k);
     int id=head->text().toInt(0,10);

         Activity current = ActivityInTTS::get<Activity>(*(db),Activity::Id==id,
                                ActivityInTTS::TodoTodaySheet==1).one();
        if (this->current == NULL || this->current->id != current.id)
         {
             this->current= new Activity(*(db));
              this->current->id = current.id;
              pomo->~Pomodoro();
             pomo = new Pomodoro(0,25,00);
       }
        pomo->show();
         pomo->Start();

       QMessageBox msgBox;
        msgBox.setText("ERROR");
        msgBox.exec();
     }
     */
}


void TodoTodaySheetGui::on_postponeActivityButton_clicked()
{
     QList<QTableWidgetItem *> items = ui->tableWidget->selectedItems();
     try
     {
         TodoTodaySheet currentTts = select<TodoTodaySheet>(*(db), TodoTodaySheet::Id == 1).one();
         for (QList<QTableWidgetItem *>::iterator k = items.begin();k<items.end();k++)
         {
             QTableWidgetItem * activitiesToBePostponed = (*k);
             Activity current = ActivityInTTS::get<Activity>(*(db),Activity::Id==activitiesToBePostponed->text().toInt(),
                                ActivityInTTS::TodoTodaySheet==1).one();
             currentTts.PostponeActivity(*(db),current,currentTts);
         }
         refreshTable();
     }catch(NotFound e)
     {
        QMessageBox msgBox;
        msgBox.setText("ERROR");
        msgBox.exec();
     }
}

void TodoTodaySheetGui::on_finishActivityButton_clicked()
{
     QList<QTableWidgetItem *> items = ui->tableWidget->selectedItems();
     QList<QTableWidgetItem *>::iterator k = items.begin();
     QTableWidgetItem * head = (*k);
     int id=head->text().toInt(0,10);
     try
     {
         Activity current = ActivityInTTS::get<Activity>(*(db),Activity::Id==id,
                                ActivityInTTS::TodoTodaySheet==1).one();
         TodoTodaySheet currentTts = select<TodoTodaySheet>(*(db), TodoTodaySheet::Id == 1).one();
         currentTts.FinishActivity(*(db),current,currentTts);
         refreshTable();
     }catch(NotFound e)
     {
        QMessageBox msgBox;
        msgBox.setText("ERROR");
        msgBox.exec();
     }
}

void TodoTodaySheetGui::on_stopActivity_clicked()
{
    if(pomo->IsRunning())
    {
        pomo->show();
        pomo->Stop();
    }
}
