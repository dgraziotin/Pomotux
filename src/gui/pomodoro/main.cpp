 #include <QApplication>
 #include "pomodoro.hpp"

 int main(int argc, char *argv[])
 {
     QApplication app(argc, argv);
     Pomodoro p(0,25,00);
     p.show();
     p.Start();
     return app.exec();
 }
