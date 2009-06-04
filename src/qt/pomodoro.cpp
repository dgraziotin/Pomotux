#include <QtGui>
#include <iostream>
#include "pomodoro.hpp"

Pomodoro::Pomodoro(QWidget *parent, int minutes, int seconds)
        : QLCDNumber(parent)
{
    this->mMinutes = minutes;
    this->mSeconds = seconds;
    setSegmentStyle(Filled);
    mpTime = new QTime(0,minutes,seconds,0);
    mpTimer = new QTimer(this);
    mpTimer->setInterval(1000);
    mIsRunning = false;
    setWindowTitle(tr("Pomodoro"));
    connect(mpTimer, SIGNAL(timeout()), this, SLOT(Run()));
    resize(350, 190);
    ShowTimer();
}

bool Pomodoro::IsRunning()
{
    return mIsRunning;
}

void Pomodoro::Start()
{

    mpTimer->start();
    mIsRunning = true;
    Run();
}

void Pomodoro::Stop()
{
    mIsRunning = false;
    mpTimer->stop();
    if (!(mpTime->minute() == 0 && mpTime->second() == 0))
        emit PomodoroBroken();
}

void Pomodoro::Reset()
{
    mIsRunning = false;
    mpTimer->stop();
    mpTime->setHMS(0,this->mMinutes,this->mSeconds,0);
}


void Pomodoro::Run()
{
    if (mpTime->minute() == 0 && mpTime->second() == 0) {
        emit PomodoroFinished();
        Reset();
    } else {
        *mpTime = mpTime->addSecs(-1);
    }
    ShowTimer();
}

void Pomodoro::ShowTimer()
{
    QString text = mpTime->toString("mm:ss");
    if ((mpTime->second() % 2) != 0)
        text[2] = ' ';
    display(text);
}

int Pomodoro::GetMinutes()
{
    return this->mMinutes;
}

void Pomodoro::SetMinutes(int minutes)
{
    this->mMinutes=minutes%60;
}

Pomodoro::~Pomodoro()
{
    delete this->mpTime;
    delete this->mpTimer;
    mpTime = NULL;
    mpTimer = NULL;
    delete this;
}

void Pomodoro::closeEvent(QCloseEvent *event)
{
   event->ignore();
}
