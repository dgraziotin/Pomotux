#include <QtGui/QApplication>
#include "gui_activityinventorysheet.hpp"
#include <litesql.hpp>
#include "../pomotuxdatabase.hpp"
#include <QDir>
#include <QFileInfo>
#include <QString>

using namespace litesql;
using namespace pomotuxdatabase;
using namespace std;

int main(int argc, char *argv[])
{

    QString homeDirStr = QDir::homePath();
    QString pomotuxDirStr = homeDirStr + "/.pomotux/";
    QString databasePathStr = pomotuxDirStr + "pomotux.db";

    QDir pomotuxDir ( pomotuxDirStr );
    if ( !pomotuxDir.exists() ) {
        if (!pomotuxDir.mkdir( pomotuxDirStr )) {
            cout << endl << "----------------------------" << endl;
            cout << "Error. could not create directory " << pomotuxDirStr.toStdString() << endl;
            cout << "Please create it by yourself and make sure it is writable.";
            cout << endl << "----------------------------" << endl;
            return 0;
        }
    } else {
        QFileInfo databaseFileInfo((databasePathStr));
        if (databaseFileInfo.exists()) {
            if (!databaseFileInfo.isReadable() || !databaseFileInfo.isWritable()) {
                cout << endl << "----------------------------" << endl;
                cout << "Error. could not access file " << databasePathStr.toStdString() << endl;
                cout << "Please make sure that both the file and the directory are writable";
                cout << endl << "----------------------------" << endl;
                return 0;
            }
        }

    }


    try {
        string liteSQLDatabaseArg = "database=" + databasePathStr.toStdString();
        PomotuxDatabase *db;
        db = new PomotuxDatabase("sqlite3", liteSQLDatabaseArg);
        db->verbose = false;
        if (db->needsUpgrade())
            db->upgrade();
        db->begin();

        QApplication Pomotux(argc, argv);

        GuiActivityInventorySheet* mainWindow = new GuiActivityInventorySheet(0,*(db));
        mainWindow->show();
        return Pomotux.exec();
    } catch (Except e) {
        //cerr << e << endl;
        return -1;
    }
}
