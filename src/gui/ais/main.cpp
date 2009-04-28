#include <QtGui/QApplication>
#include "guiactivityinventorysheet.h"
#include "litesql.hpp"
#include "../sep/src/pomotuxdatabase.hpp"

int main(int argc, char *argv[])
{
    try{
    PomotuxDatabase *db;
    db = new PomotuxDatabase("sqlite3", "database=pomotux.db");
    db->verbose = false;
    db->create();
    db->begin();
    //ActivityInventorySheet ais(db);
    //ais.update();
    QApplication a(argc, argv);
    GuiActivityInventorySheet *w = new GuiActivityInventorySheet(0,*(db));
    w->show();
    return a.exec();
    } catch (Except e) {
        cerr << e << endl;
        return -1;
    }
}
