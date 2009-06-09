#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent) :
        QDialog(parent),
        m_ui(new Ui::AboutWindow)
{
    m_ui->setupUi(this);
}

AboutWindow::~AboutWindow()
{
    delete m_ui;
}

void AboutWindow::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
