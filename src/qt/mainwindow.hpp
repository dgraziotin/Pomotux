/*
 * TODO: Doxygen comments!
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "gui_activityinventorysheet.hpp"
#include "gui_todotodaysheet.hpp"
#include "../pomotuxdatabase.hpp"


using namespace litesql;
using namespace pomotuxdatabase;
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    Q_DISABLE_COPY(MainWindow)
public:
    explicit MainWindow(QWidget *parent,PomotuxDatabase& database);
    virtual ~MainWindow();

protected:
    virtual void changeEvent(QEvent *e);    // Coding Standards: ChangeEvent()

private:
    PomotuxDatabase *db;                // CS..
    GuiActivityInventorySheet *wAIS;    // CS: GuiActivityInventorySheet* mpAIS (what does w stand for?)
    TodoTodaySheetGui *wTTS;            // CS
    Ui::MainWindow *m_ui;               // CS and choose a better name

private slots:
    void on_AISButton_clicked();
    void on_TTSButton_clicked();
};

#endif // MAINWINDOW_H
