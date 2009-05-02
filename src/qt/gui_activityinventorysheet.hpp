/*
 * TODO: Doxygen comments!
 */
#ifndef GUIACTIVITYINVENTORYSHEET_H
#define GUIACTIVITYINVENTORYSHEET_H

#include <QtGui/QMainWindow>
#include <QTableWidget>
#include "insertnewactivity.hpp"
#include "modifyactivity.hpp"
#include "litesql.hpp"
#include "../pomotuxdatabase.hpp"
#include <time.h>

using namespace litesql;
using namespace pomotuxdatabase;
using namespace std;

namespace Ui {
class GuiActivityInventorySheet;
}

class GuiActivityInventorySheet : public QMainWindow {
    Q_OBJECT

public:
    GuiActivityInventorySheet(QWidget *parent, PomotuxDatabase& database);
    ~GuiActivityInventorySheet();
    QString *description;
    float *value;   // TODO: should be mpValue, make private
    float mainController;   // TODO: mMainController, make private
    time_t now; // TODO: Coding Standards, make private
    void showEvent( QShowEvent * event);   // TODO: CS

private:
    Ui::GuiActivityInventorySheet *ui;  // CS
    PomotuxDatabase *db;    // CS
    ActivityInventorySheet *rAis;
    TodoTodaySheet *rTts;   // CS: TodoTodaySheet* mpTTS;
    float row;  // CS
    void cleaner(); // CS
    void refreshTable();    // CS

private slots:
    void on_insertInTTSButton_clicked();    // CS: should be on_InsertInTTSButton_clicked(), if possible, so for the next
    void on_modifyActivityButton_clicked();
    void on_ais_itemClicked(QTableWidgetItem* item);
    void on_deleteActivityButton_clicked();
    void on_newActivityButton_clicked();

signals:
    /**
      * Signal launched when the database is updated
      */
    void DatabaseUpdated();
};

#endif // GUIACTIVITYINVENTORYSHEET_H
