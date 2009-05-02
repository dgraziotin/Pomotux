/**
 *  A class for Pomodoro objects. Contains all the operations regarding a Pomodoro,
 *  as well as its graphical representation (a QLCDNumber).
 *  It is studied for re-use, as it is completely isolated from the rest of the project.
 *  It emits signals either when the pomodoro is finished or broken.
 *
 *  An example on how to use it:
 *   #include <QApplication>
 *   #include "pomodoro.hpp"
 *
 *   int main(int argc, char *argv[])
 *   {
 *      QApplication app(argc, argv);
 *      Pomodoro p(0,25,0); // a pomodoro in an indipendent window, with length of 25 minutes
 *      p.show();           // show the pomodoro
 *      p.Start();          // start the pomodoro
 *      return app.exec();
 *   }
 *
 */


#ifndef POMODORO_H
#define POMODORO_H

#include <QLCDNumber>

class Pomodoro : public QLCDNumber {
    Q_OBJECT

public:
    /**
       * Constructor of a Pomodoro. Sets the attributes and calls ShowTimer() automatically.
       * @param parent a pointer to the parent widget (0 if we want a new window)
       * @param minutes an integer for the length of Pomodoro (default 25)
       * @param seconds an integer for the length of Pomodoro (default 0)
       * @see ShowTimer()
       */
    Pomodoro(QWidget *parent,int minutes,int seconds);

    /**
       * Starts a Pomodoro. Sets the signal handler, starts the internal timer, sets mIsRunning to true.
       * It calls Run() as last thing.
       * @see Run()
       * @see PomodoroBroken()
       */
    void Start();

    /**
      * Stops a Pomodoro. If it detects that the pomodoro was broken, it launches a PomodoroBroken() signal.
      * It stops the internal timer, and sets mIsRunning to false.
      */
    void Stop();

    /**
      * Resets the Pomodoro.
      * This method is just for having a single Pomodoro object during the execution of the program.
      */
    void Reset();

    /**
       * Getter for mIsRunning variable
       * @return mIsRunning
       */
    bool IsRunning();

    /**
       * Default destructor
       */
    ~Pomodoro();
private:
    /**
       * Integer to store the minutes of length of a Pomodoro
       */
    int mMinutes;
    /**
       * Integer to store the seconds of length of a Pomodoro
       */
    int mSeconds;
    /**
       * Boolean to represent the status of the Pomodoro (true = running)
       */
    bool mIsRunning;

    /**
       * Internal timer that launches a signal every 1 second.
       */
    QTimer* mpTimer;

    /**
       * Internal time object, to hold the minutes and the seconds of a Pomodoro
       */
    QTime* mpTime;


private slots:
    /**
       * Sets and shows the timer (LCD)
       */
    void ShowTimer();

    /**
       * Decrements the seconds and calls ShowTimer().
       * Detects if the Pomodoro finishes and emits a PomodoroFinished() signal, then calls Stop()
       * @see PomodoroFinished()
       * @see Stop()
       */
    void Run();

signals:
    /**
      * Signal launched when the Pomodoro finishes normally
      */
    void PomodoroFinished();

    /**
      * Signal launched when the Pomodoro is broken
      */
    void PomodoroBroken();
};

#endif

