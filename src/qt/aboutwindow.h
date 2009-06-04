/**
 * A class for About window.
 * It shows to the user some information about the program and about the programmer
 *
 *  @include <QtGui/QDialog>
 *
 *  @see http://doc.trolltech.com/4.5/index.html
 */
#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QtGui/QDialog>

namespace Ui {
    class AboutWindow;
}

/**
 * A class for About window.
 * It shows to the user some information about the program and about the programmer
 *
 *  @see http://doc.trolltech.com/4.5/index.html
 */
class AboutWindow : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(AboutWindow)
public:

    /**
     * Constructor of a About Graphical User Interface window.
     * @param parent a pointer to the parent widget (0 if we want a new window)
     */
    explicit AboutWindow(QWidget *parent = 0);

    /**
     * Default Destructor
     */
    virtual ~AboutWindow();

protected:
    virtual void changeEvent(QEvent *e);

private:
    /**
     * Default pointer created by qtCreator
     */
    Ui::AboutWindow *m_ui;
};

#endif // ABOUTWINDOW_H
