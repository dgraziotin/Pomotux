/*
 * TODO: Doxygen comments!
 */

#ifndef TODOTODAYSHEETGUI_H
#define TODOTODAYSHEETGUI_H

#include <QtGui/QMainWindow>
#include <litesql.hpp>
#include "../pomotuxdatabase.hpp"
#include "pomodoro.hpp"
#include "pomotuxexception.hpp"

using namespace litesql;
using namespace pomotuxdatabase;
using namespace std;

namespace Ui {
class TodoTodaySheetGuiClass;
}

class TodoTodaySheetGui : public QMainWindow {
    Q_OBJECT

public:
    TodoTodaySheetGui(QWidget *parent,PomotuxDatabase& database);
    ~TodoTodaySheetGui();

private:
    PomotuxDatabase *mpDatabase;
    Pomodoro *mpPomodoro;
    Activity *mpCurrentActivity;
    TodoTodaySheet *mpTts;
    Ui::TodoTodaySheetGuiClass *ui;
    void Cleaner();


private slots:
    void on_StopActivityButton_clicked();
    void on_PostponeActivityButton_clicked();
    void on_StartActivityButton_clicked();
    void on_FinishActivityButton_clicked();
    void PomodoroFinished();
    void PomodoroBroken();
    void RefreshTable();

signals:
    /**
      * Signal launched when the database is updated
      */
    void DatabaseUpdated();
};

#endif // TODOTODAYSHEETGUI_H
