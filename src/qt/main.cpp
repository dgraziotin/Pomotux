#include <QtGui/QApplication>
#include "gui_activityinventorysheet.hpp"
#include <litesql.hpp>
#include "../pomotuxdatabase.hpp"


using namespace litesql;
using namespace pomotuxdatabase;
using namespace std;

int main(int argc, char *argv[])
{
    try {
        /* MEMORY LEAK: db is not destroyed anywhere */
        PomotuxDatabase *db;
        db = new PomotuxDatabase("sqlite3", "database=pomotux.db");
        db->verbose = false;
        if (db->needsUpgrade())
            db->upgrade();
        db->begin();
        QApplication a(argc, argv);

        GuiActivityInventorySheet *w = new GuiActivityInventorySheet(0,*(db));
        w->show();
        return a.exec();
    } catch (Except e) {
        //  cerr << e << endl;
        return -1;
    }
}
