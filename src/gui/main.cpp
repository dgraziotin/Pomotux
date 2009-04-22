#include <QApplication>
#include "insertActivity.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    InsertActivity *dialog = new InsertActivity; 
    dialog->show();
    return app.exec();
}

