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
    mpDatabase = &database;
    mpDatabase->begin();
    this->mpCurrentActivity = new Activity(*(this->mpDatabase));
    ui->setupUi(this);
    try {
        mpTts = new TodoTodaySheet(select<TodoTodaySheet>(*(mpDatabase), TodoTodaySheet::Id == 1).one());
    } catch (NotFound e) {
        mpTts = new TodoTodaySheet(*(mpDatabase));
        mpTts->update();
    }
    connect(this,SIGNAL(DatabaseUpdated()),this,SLOT(RefreshTable()));
    mpPomodoro = new Pomodoro(0,mins,secs);
    connect(mpPomodoro, SIGNAL(PomodoroFinished()), this, SLOT(PomodoroFinished()));
    connect(mpPomodoro, SIGNAL(PomodoroBroken()), this, SLOT(PomodoroBroken()));
    emit DatabaseUpdated();
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
    vector<Activity> currentTTSActivities = ActivityInTTS::get<Activity>(*(mpDatabase),Expr(),
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
    this->ui->MoveMagnitudeBox->setMaximum(ActivityInTTS::get<Activity>(*(this->mpDatabase),Expr()).count());
}



void TodoTodaySheetGui::on_StartActivityButton_clicked()
{

    try {
        if (this->ui->tableWidget->rowCount()==0) throw PomotuxException("There Are No Activities to be Initialized");
        int id=this->ui->tableWidget->item(0,0)->text().toInt();

        Activity current = ActivityInTTS::get<Activity>(*(mpDatabase),Activity::Id==id,ActivityInTTS::TodoTodaySheet==mpTts->id).one();
        if (!mpPomodoro->IsRunning()) {

            this->mpCurrentActivity = new Activity(current);
            mpPomodoro->show();
            mpPomodoro->Start();
        } else {
            mpPomodoro->show();
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
        this->mpCurrentActivity->mNumPomodoro= (this->mpCurrentActivity->mNumPomodoro +1);
        this->mpCurrentActivity->update();
        this->mpPomodoro->hide();


       emit DatabaseUpdated();
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

    this->mpPomodoro->hide();
    this->mpPomodoro->Reset();
    QMessageBox msgBox;
    msgBox.setText("Pomodoro Broken");
    msgBox.exec();
}

void TodoTodaySheetGui::on_PostponeActivityButton_clicked()
{
    QList<QTableWidgetItem *> items = ui->tableWidget->selectedItems();
    try {
        if(items.empty())throw PomotuxException("There Are No Activities Selected");
        for (QList<QTableWidgetItem *>::iterator k = items.begin(); k<items.end(); k++)
        {
            QTableWidgetItem * activitiesToBePostponed = (*k);
            Activity current = ActivityInTTS::get<Activity>(*(mpDatabase),Activity::Id==activitiesToBePostponed->text().toInt(),ActivityInTTS::TodoTodaySheet==this->mpTts->id).one();
            if (this->mpCurrentActivity->id!=current.id)mpTts->PostponeActivity(*(mpDatabase),current,*(mpTts));
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

    try
     {
        QList<QTableWidgetItem *> items = ui->tableWidget->selectedItems();
        if(items.empty())throw PomotuxException("There Are No Activities");
        QList<QTableWidgetItem *>::iterator k = items.begin();
        QTableWidgetItem * head = (*k);
        int id=head->text().toInt(0,10);
        Activity current = ActivityInTTS::get<Activity>(*(mpDatabase),Activity::Id==id,ActivityInTTS::TodoTodaySheet==mpTts->id).one();
        if (!(this->mpCurrentActivity==NULL||this->mpCurrentActivity->id!=current.id)&&this->mpPomodoro->IsRunning())throw PomotuxException("current activity could be marked as finished only once current pomodoro is over");
        mpTts->FinishActivity(*(mpDatabase),current,*(mpTts));
        emit DatabaseUpdated();
    } catch (NotFound e) {
        QMessageBox msgBox;
        msgBox.setText("ERROR ");
        msgBox.exec();
    } catch (PomotuxException e){
        QMessageBox msgBox;
        msgBox.setText(e.getMessage());
        msgBox.exec();
    }
}

void TodoTodaySheetGui::on_StopActivityButton_clicked()
{
    if (mpPomodoro->IsRunning()) {
        mpPomodoro->show();
        mpPomodoro->Stop();
    }
}

TodoTodaySheetGui::~TodoTodaySheetGui()
{
    this->mpTts->~Persistent();
    this->mpCurrentActivity->~Persistent();
    this->mpPomodoro->~Pomodoro();
    delete ui;
}

void TodoTodaySheetGui::ChangeActivityPriority(int magnitude,int direction,Activity& activityToMove)
{
    try{
        for (int i=magnitude;i>0;i--)
        this->mpTts->MoveActivity(*(this->mpDatabase),activityToMove,*(this->mpTts),direction);
        emit DatabaseUpdated();
    }catch (NotFound e){
        emit DatabaseUpdated();
    }
}

void TodoTodaySheetGui::on_MoveActivityButton_clicked()
{
    try{
        QList<QTableWidgetItem *> items = ui->tableWidget->selectedItems();
        if(items.empty())throw PomotuxException("There Are No Activities");
        QList<QTableWidgetItem *>::iterator k = items.begin();
        QTableWidgetItem * head = (*k);
        int id=head->text().toInt(0,10);
        Activity current = ActivityInTTS::get<Activity>(*(mpDatabase),Activity::Id==id,ActivityInTTS::TodoTodaySheet==mpTts->id).one();
        if(this->mpPomodoro->IsRunning()&&this->mpCurrentActivity->id==current.id)throw PomotuxException("Could not change priority of the current Activity");
        this->ChangeActivityPriority(ui->MoveMagnitudeBox->value(),(ui->MoveDirectionBox->currentText()=="upward")?-1:1,current);
    }catch (Except e){
        QMessageBox msgBox;
        msgBox.setText("SQL Error");
        msgBox.exec();
    }catch (PomotuxException e){
        QMessageBox msgBox;
        msgBox.setText(e.getMessage());
        msgBox.exec();
    }
}
