#include <QApplication>
#include "insertActivity.hpp"
#include "litesql.hpp"
#include "../pomotuxdatabase.hpp"

using namespace litesql;
using namespace pomotuxdatabase;
using namespace std;

int main(int argc, char *argv[])
{
    try{
    PomotuxDatabase db("sqlite3", "database=pomotux.db");
    db.verbose = false;
    db.create();
    db.begin();
    QApplication app(argc, argv);
    InsertActivity *dialog = new InsertActivity(0, db); 
    dialog->show();
    return app.exec();
    } catch (Except e) {
        cerr << e << endl;
        return -1;
    }

}

