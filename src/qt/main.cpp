#include <QtGui/QApplication>
#include "gui_activityinventorysheet.hpp"
#include <litesql.hpp>
#include "../pomotuxdatabase.hpp"
#include "pomotuxexception.hpp"
#include <QDir>
#include <QFileInfo>
#include <QString>
//#include <QtPlugin>

//Q_IMPORT_PLUGIN(qjpeg)

using namespace litesql;
using namespace pomotuxdatabase;
using namespace std;

int main(int argc, char *argv[])
{

    QString homeDirStr = QDir::homePath();
    QString pomotuxDirStr = homeDirStr + "/.pomotux/";
    QString databasePathStr = pomotuxDirStr + "pomotux.db";

    QDir pomotuxDir ( pomotuxDirStr );

    QApplication Pomotux(argc, argv);
    try{
        if ( !pomotuxDir.exists() ) {
          if (!pomotuxDir.mkdir( pomotuxDirStr ))
              throw PomotuxException("Error. could not create directory " + pomotuxDirStr.toStdString() + "\nPlease create it by yourself and make sure it is writable.");
        }else {
           QFileInfo databaseFileInfo((databasePathStr));
          if (databaseFileInfo.exists()) {
             if (!databaseFileInfo.isReadable() || !databaseFileInfo.isWritable()) {
                  throw PomotuxException("Error. could not access file " + databasePathStr.toStdString()+"\nPlease make sure that both the file and the directory are writable");
               }
            }
       }
    }catch (PomotuxException e){
        QMessageBox msgBox;
        msgBox.setText(e.getMessage());
        return msgBox.exec();
    }


    try {
        string liteSQLDatabaseArg = "database=" + databasePathStr.toStdString();
        PomotuxDatabase *db;
        db = new PomotuxDatabase("sqlite3", liteSQLDatabaseArg);
        db->verbose = false;
        if (db->needsUpgrade())
            db->upgrade();
        db->begin();
        GuiActivityInventorySheet* mainWindow = new GuiActivityInventorySheet(0,*(db));
        mainWindow->show();
        return Pomotux.exec();
    } catch (Except e) {
        ostringstream errorMsg;
        errorMsg <<"liteSQL ERROR :"<< e;
        QMessageBox msgBox;
        msgBox.setText(errorMsg.str().c_str());
        return msgBox.exec();
    }
}
