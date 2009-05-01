#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent,PomotuxDatabase& database) :
        QMainWindow(parent),
        m_ui(new Ui::MainWindow)
{
    this->db= &database;
    m_ui->setupUi(this);
    //wTTS = new TodoTodaySheetGui(this,*(db));
    wAIS = new GuiActivityInventorySheet(this,*(db));
}

MainWindow::~MainWindow()
{
    delete m_ui;

}

void MainWindow::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_TTSButton_clicked()
{
    wTTS = new TodoTodaySheetGui(this,*(db));
    wTTS->show();
}

void MainWindow::on_AISButton_clicked()
{
    wAIS->show();
}
