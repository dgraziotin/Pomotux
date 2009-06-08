
#include "gui_todotodaysheet.hpp"
#include "ui_gui_todotodaysheet.h"
#include <cstring>
#include <QMessageBox>
#include <QFileInfo>
#include <QProcess>
#include <QSound>
#define secs 5

using namespace litesql;
using namespace pomotuxdatabase;
using namespace std;



TodoTodaySheetGui::TodoTodaySheetGui(QWidget *parent,PomotuxDatabase& database)
        : QMainWindow(parent), ui(new Ui::TodoTodaySheetGuiClass)
{

    this->mNumInterruption = 0;
    this->mpDatabase = &database;
    this->mpDatabase->begin();
    this->mpCurrentActivity = new Activity(*(this->mpDatabase));
    this->mConsecutivePomodoro=0;
    ui->setupUi(this);
    this->ui->NumInterruptions->setText(QString((toString(this->mNumInterruption)).c_str()));

    try {
        this->mpTts = new TodoTodaySheet(select<TodoTodaySheet>(*(this->mpDatabase), TodoTodaySheet::Id == 1).one());
    } catch (NotFound e) {
        this->mpTts = new TodoTodaySheet(*(this->mpDatabase));
        this->mpTts->update();
    }

    try {
        this->mpAis = new ActivityInventorySheet(select<ActivityInventorySheet>(*(mpDatabase), ActivityInventorySheet::Id == 1).one());
    } catch (NotFound e) {
        this->mpAis = new ActivityInventorySheet(*(mpDatabase));
        this->mpAis->update();
    }
    this->mpPomodoro = new Pomodoro(0,0,secs);

    this->wInsertActivity =new InsertNewActivity(this,*(this->mpDatabase));

    this->RefreshPreferences();
    connect(this,SIGNAL(DatabaseUpdated()),this,SLOT(RefreshTable()));
    connect(this, SIGNAL(SoundAlert()), this, SLOT(PlaySound()));
    connect(this,SIGNAL(Interruption()),this,SLOT(HandleInterruption()));

    connect(this->mpPomodoro, SIGNAL(PomodoroFinished()), this, SLOT(PomodoroFinished()));
    connect(this->mpPomodoro, SIGNAL(PomodoroBroken()), this, SLOT(PomodoroBroken()));
    this->RefreshTable();
    this->ui->tableWidget->setColumnWidth(0, 0);
    this->ui->tableWidget->setColumnWidth(1, 405);
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
    try {
        vector<Activity> currentTTSActivities = ActivityInTTS::get<Activity>(*(this->mpDatabase),Expr(),
                                                ActivityInTTS::TodoTodaySheet==1).orderBy(Activity::MOrder).all();
        Cleaner();
        for (vector<Activity>::iterator i = currentTTSActivities.begin(); i != currentTTSActivities.end(); i++) {
            int tablePosition= ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(tablePosition);
            this->ui->tableWidget->setColumnWidth(0, 0);
            this->ui->tableWidget->setColumnWidth(1, 390);
            QTableWidgetItem *currentActivity=new QTableWidgetItem[3];
            currentActivity[0].setText(QString((toString((*i).id)).c_str()));
            currentActivity[1].setText(QString((toString((*i).mDescription)).c_str()));
            currentActivity[2].setText(QString((toString((*i).mNumPomodoro)).c_str()));
            currentActivity[0].setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            currentActivity[1].setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled);
            currentActivity[2].setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled);
            for (int k=0; k<3; k++)
                ui->tableWidget->setItem(tablePosition,k,&currentActivity[k]);
        }
        this->ui->MoveMagnitudeBox->setMaximum(ActivityInTTS::get<Activity>(*(this->mpDatabase),Expr()).count());
    } catch (Except e) {
        ostringstream errorMsg;
        errorMsg <<"liteSQL ERROR :"<< e;
        QMessageBox msgBox;
        msgBox.setText(errorMsg.str().c_str());
        msgBox.exec();
    }
}



void TodoTodaySheetGui::on_StartActivityButton_clicked()
{

    try {
        if (this->ui->tableWidget->rowCount()==0) throw PomotuxException("There Are No Activities selected");
        int id=this->ui->tableWidget->item(0,0)->text().toInt();
        Activity current = ActivityInTTS::get<Activity>(*(this->mpDatabase),Activity::Id==id,ActivityInTTS::TodoTodaySheet==this->mpTts->id).one();
        if (!this->mpPomodoro->IsRunning()) {
            this->mpCurrentActivity = new Activity(current);
            this->mpPomodoro->Reset();
            this->mpPomodoro->show();
            this->mpPomodoro->Start();
        } else {
            this->mpPomodoro->show();
            throw PomotuxException("You Should First Break or Wait Untill The End of The Current Pomodoro!!");
        }
        this->ui->newActivityButton->setText("Handle Interruption");
        this->showMinimized();
        this->parentWidget()->showMinimized();
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
}

void TodoTodaySheetGui::PomodoroFinished()
{
    try {
        this->mpCurrentActivity->mNumPomodoro= (this->mpCurrentActivity->mNumPomodoro +1);
        this->mpCurrentActivity->update();
        this->mpPomodoro->hide();
        this->mConsecutivePomodoro=(this->mConsecutivePomodoro+1);
        emit DatabaseUpdated();
        if (this->mConsecutivePomodoro>=4) {
            this->mConsecutivePomodoro=0;
            throw PomotuxException("You Should now take a break longer than usual");
        }
        this->      ui->newActivityButton->setText("new activity");
        throw PomotuxException("Now you Should take a short break");
    } catch (Except e) {
        ostringstream errorMsg;
        errorMsg <<"liteSQL ERROR :"<< e;
        QMessageBox msgBox;
        msgBox.setText(errorMsg.str().c_str());
        msgBox.exec();
    } catch (PomotuxException e) {
        bool isSoundActivated = false;
        try {
            Settings soundActivated = select<Settings>(*(this->mpDatabase), Settings::MName=="soundActivated").one();
            isSoundActivated = (bool) atoi(soundActivated.mValue);
        } catch (NotFound e) {
            Settings soundActivated(*(this->mpDatabase));
            soundActivated.mName= "soundActivated";
            soundActivated.mValue = "0";
            soundActivated.update();
            isSoundActivated = false;
        } catch (Except e) {
            ostringstream errorMsg;
            errorMsg <<"liteSQL ERROR :"<< e;
            QMessageBox msgBox;
            msgBox.setText(errorMsg.str().c_str());
            msgBox.exec();
            isSoundActivated = false;
        }

        if (isSoundActivated)
            emit SoundAlert();
        QMessageBox msgBox;
        msgBox.setText(e.getMessage());
        msgBox.exec();

    }
}

void TodoTodaySheetGui::PomodoroBroken()
{
    this->mpPomodoro->hide();
    this->mpPomodoro->Reset();
    this->ui->newActivityButton->setText("new activity");
    QMessageBox msgBox;
    msgBox.setText("Pomodoro Broken");
    msgBox.exec();
}

void TodoTodaySheetGui::on_PostponeActivityButton_clicked()
{
    QList<QTableWidgetItem *> items = ui->tableWidget->selectedItems();
    try {
        if (items.empty())throw PomotuxException("There Are No Activities Selected");
        for (QList<QTableWidgetItem *>::iterator k = items.begin(); k!=items.end(); k++) {
            QTableWidgetItem * activitiesToBePostponed = (*k);
            Activity current = ActivityInTTS::get<Activity>(*(this->mpDatabase),Activity::Id==activitiesToBePostponed->text().toInt(),ActivityInTTS::TodoTodaySheet==this->mpTts->id).one();
            if (this->mpCurrentActivity->id!=current.id || !(this->mpPomodoro->IsRunning()))this->mpTts->PostponeActivity(*(this->mpDatabase),current,*(this->mpTts));
        }
        emit DatabaseUpdated();
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
}

void TodoTodaySheetGui::on_FinishActivityButton_clicked()
{

    try {
        QList<QTableWidgetItem *> items = ui->tableWidget->selectedItems();
        if (items.empty())throw PomotuxException("There Are No Activities");
        QList<QTableWidgetItem *>::iterator k = items.begin();
        QTableWidgetItem * head = (*k);
        int id=head->text().toInt(0,10);
        Activity current = ActivityInTTS::get<Activity>(*(this->mpDatabase),Activity::Id==id,ActivityInTTS::TodoTodaySheet==this->mpTts->id).one();
        if (!(this->mpCurrentActivity==NULL||this->mpCurrentActivity->id!=current.id)&&this->mpPomodoro->IsRunning())throw PomotuxException("current activity could be marked as finished only once current pomodoro is over");
        this->mpTts->FinishActivity(*(this->mpDatabase),current,*(this->mpTts));
        emit DatabaseUpdated();
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
}

void TodoTodaySheetGui::on_StopActivityButton_clicked()
{
    if (this->mpPomodoro->IsRunning()) {
        this->mpPomodoro->show();
        this->mpPomodoro->Stop();
    }
}


void TodoTodaySheetGui::ChangeActivityPriority(int magnitude,int direction,Activity& activityToMove)
{
    try {
        for (int i=magnitude; i>0; i--)
            this->mpTts->MoveActivity(*(this->mpDatabase),activityToMove,*(this->mpTts),direction);
        emit DatabaseUpdated();
    } catch (NotFound e) {
        emit DatabaseUpdated();
    }
}

void TodoTodaySheetGui::on_MoveActivityButton_clicked()
{
    try {
        QList<QTableWidgetItem *> items = ui->tableWidget->selectedItems();
        if (items.empty())throw PomotuxException("There Are No Activities");
        QList<QTableWidgetItem *>::iterator k = items.begin();
        QTableWidgetItem * head = (*k);
        int id=head->text().toInt(0,10);
        Activity current = ActivityInTTS::get<Activity>(*(this->mpDatabase),Activity::Id==id,ActivityInTTS::TodoTodaySheet==this->mpTts->id).one();
        if (this->mpPomodoro->IsRunning()&&this->mpCurrentActivity->id==current.id)throw PomotuxException("Could not change priority of the current Activity");
        this->ChangeActivityPriority(ui->MoveMagnitudeBox->value(),(ui->MoveDirectionBox->currentText()=="upward")?-1:1,current);
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
}

void TodoTodaySheetGui::on_newActivityButton_clicked()
{
    this->wInsertActivity->show();
    emit Interruption();
}

void TodoTodaySheetGui::PlaySound()
{

    if (QSound::isAvailable()) {
        QSound::play(this->SoundFile);
    } else {
        QString program = "aplay";
        QStringList arguments;
        arguments << this->SoundFile;
        QProcess myProcess(this);
        myProcess.start(program, arguments);
        myProcess.waitForFinished();
    }
}

void TodoTodaySheetGui::RefreshPreferences()
{
    try {
        Settings length = select<Settings>(*(this->mpDatabase), Settings::MName=="length").one();
        this->mMinutesPomodoroLength = atoi(length.mValue);
        this->mpPomodoro->SetMinutes(this->mMinutesPomodoroLength);
    } catch (NotFound e) {
        Settings length(*(this->mpDatabase));
        length.mName="length";
        length.mValue="25";
        length.update();
        this->mpDatabase->commit();
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
        QString filePath="";
        Settings SoundLib= select<Settings>(*(this->mpDatabase), Settings::MName=="SoundLib").one();
        filePath += QString((toString(SoundLib.mValue)).c_str());
        filePath +="/";
        Settings SoundFile= select<Settings>(*(this->mpDatabase), Settings::MName=="SoundFile").one();
        filePath += QString((toString(SoundFile.mValue)).c_str());
        QFileInfo myFile(filePath);
        if (!myFile.exists())throw PomotuxException("Sound file does not exist");
        if (!myFile.isReadable())throw PomotuxException("Sound file cannot be read check your permissions");
        this->SoundFile=filePath;
    } catch (NotFound e) {
        Settings SoundLib(*(this->mpDatabase));
        SoundLib.mName= "SoundLib";
        SoundLib.mValue = "";
        SoundLib.update();
        Settings SoundFile(*(this->mpDatabase));
        SoundFile.mName= "SoundFile";
        SoundFile.mValue = "";
        SoundFile.update();
        this->mpDatabase->commit();
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
}

InsertNewActivity* TodoTodaySheetGui::getInsertActivity()
{
    return this->wInsertActivity;
}

void TodoTodaySheetGui::HandleInterruption()
{
    this->mNumInterruption+=1;
    this->ui->NumInterruptions->setText(toString(this->mNumInterruption).c_str());
}

TodoTodaySheetGui::~TodoTodaySheetGui()
{
    this->wInsertActivity->~InsertNewActivity();
    delete this->wInsertActivity;
    this->wInsertActivity = NULL;

    this->mpTts->~Persistent();
    delete this->mpTts;
    this->mpTts = NULL;

    this->mpAis->~Persistent();
    delete this->mpAis;
    this->mpAis = NULL;

    this->mpCurrentActivity->~Persistent();
    delete this->mpCurrentActivity;
    this->mpCurrentActivity = NULL;

    this->mpPomodoro->~Pomodoro();
    delete this->mpPomodoro;
    this->mpPomodoro = NULL;

    delete ui;
}
