#ifndef GUIACTIVITYINVENTORYSHEET_H
#define GUIACTIVITYINVENTORYSHEET_H

#include <QtGui/QMainWindow>
#include <QTableWidget>
//#include "../sep/src/gui/insertActivity.hpp"
#include "insertnewactivity.hpp"
#include "modifyactivity.hpp"
#include "litesql.hpp"
#include "../pomotuxdatabase.hpp"
#include <time.h>

using namespace litesql;
using namespace pomotuxdatabase;
using namespace std;

namespace Ui
{
    class GuiActivityInventorySheet;
}

class GuiActivityInventorySheet : public QMainWindow
{
    Q_OBJECT

public:
    GuiActivityInventorySheet(QWidget *parent, PomotuxDatabase& database);
    ~GuiActivityInventorySheet();
    QString *description;
    float row;
    float *value;
    float mainController;
    time_t now;


private:
    Ui::GuiActivityInventorySheet *ui;
    PomotuxDatabase *db;
    double count;

private slots:
    void on_modifyActivityButton_clicked();
    void on_ais_itemClicked(QTableWidgetItem* item);
    void on_deleteActivityButton_clicked();
    void on_newActivityButton_clicked();
};

#endif // GUIACTIVITYINVENTORYSHEET_H
