/*
 * TODO: Doxygen comments!
 */

#ifndef TODOTODAYSHEETGUI_H
#define TODOTODAYSHEETGUI_H

#include <QtGui/QMainWindow>
#include <litesql.hpp>
#include "../pomotuxdatabase.hpp"
#include "pomodoro.hpp"

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
    void showEvent( QShowEvent * event);    // Coding Standards

private:
    PomotuxDatabase *db;    // Coding Standards: PomotuxDatabase* mpDatabase
    Pomodoro *pomo;         // CS: Pomodoro* mpPomodoro
    Activity *current;      // CS
    Ui::TodoTodaySheetGuiClass *ui; // CS

    void cleaner();     // CS
    void refreshTable();    // CS

private slots:
    void on_stopActivity_clicked();     // If possible, should be on_StopActivity_clicked(), so for the next methods
    void on_postponeActivityButton_clicked();
    void on_startActivityButton_clicked();
    void on_finishActivityButton_clicked();
    void PomodoroFinished();
    void PomodoroBroken();
};

#endif // TODOTODAYSHEETGUI_H
