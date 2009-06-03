#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QtGui/QDialog>

namespace Ui {
    class AboutWindow;
}

class AboutWindow : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(AboutWindow)
public:
    explicit AboutWindow(QWidget *parent = 0);
    virtual ~AboutWindow();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::AboutWindow *m_ui;
};

#endif // ABOUTWINDOW_H
