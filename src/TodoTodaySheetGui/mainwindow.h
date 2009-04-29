#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "../ActivityInventorySheetGui/guiactivityinventorysheet.h"
#include "todotodaysheetgui.h"
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
    virtual void changeEvent(QEvent *e);

private:
    PomotuxDatabase *db;
    GuiActivityInventorySheet *wAIS;
    TodoTodaySheetGui *wTTS;
    Ui::MainWindow *m_ui;

private slots:
    void on_AISButton_clicked();
    void on_TTSButton_clicked();
};

#endif // MAINWINDOW_H
