#include <QtGui>
#include <iostream>
#include "pomodoro.hpp"

Pomodoro::Pomodoro(QWidget *parent, int minutes, int seconds)
        : QLCDNumber(parent)
{

    setSegmentStyle(Filled);
    mpTime = new QTime(0,minutes,seconds,0);
    mpTimer = new QTimer(this);
    mIsRunning = false;
    setWindowTitle(tr("Pomodoro"));
    resize(350, 190);
    ShowTimer();
}

bool Pomodoro::IsRunning()
{
    return mIsRunning;
}

void Pomodoro::Start()
{

    connect(mpTimer, SIGNAL(timeout()), this, SLOT(Run()));
    mpTimer->start(1000);
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

void Pomodoro::Run()
{
    if (mpTime->minute() == 0 && mpTime->second() == 0) {
        emit PomodoroFinished();
        Stop();
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

Pomodoro::~Pomodoro(){
    delete this->mpTime;
    delete this->mpTimer;
    mpTime = NULL;
    mpTimer = NULL;
    delete this;
}
