#ifndef TODOTODAYSHEETGUI_H
#define TODOTODAYSHEETGUI_H

#include <QtGui/QMainWindow>
#include <litesql.hpp>
#include "../pomotuxdatabase.hpp"
#include "../gui/pomodoro/pomodoro.hpp"

using namespace litesql;
using namespace pomotuxdatabase;
using namespace std;

namespace Ui
{
    class TodoTodaySheetGuiClass;
}

class TodoTodaySheetGui : public QMainWindow
{
    Q_OBJECT

public:
    TodoTodaySheetGui(QWidget *parent,PomotuxDatabase& database);
    ~TodoTodaySheetGui();


private:
    PomotuxDatabase *db;
    Pomodoro *pomo;
    Activity *current;
    Ui::TodoTodaySheetGuiClass *ui;

    void cleaner();
    void refreshTable();

private slots:
    void on_stopActivity_clicked();
    void on_postponeActivityButton_clicked();
    void on_startActivityButton_clicked();
    void on_finishActivityButton_clicked();
};

#endif // TODOTODAYSHEETGUI_H
