#ifndef INSERTACTIVITY_H
#define INSERTACTIVITY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDateEdit>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QDialog>
#include <iostream>
#include <stdlib.h>

QT_BEGIN_NAMESPACE

class InsertActivity : public QDialog
{
Q_OBJECT // macro used when signals and slots appears 
public:
    InsertActivity(QWidget *parent = 0);

private slots:
    void insertNewActivity();

private:
    QVBoxLayout *titleLayout;
    QLabel *titleLabel;
    QHBoxLayout *descriptionLayout;
    QLabel *descriptionLabel;
    QLineEdit *lineEdit;
    QHBoxLayout *deadlineLayout;
    QLabel *deadlineLabel;
    QDateEdit *dateEdit;
    QHBoxLayout *buttonsLayout;
    QPushButton *submitButton;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer2;
    QPushButton *cancelButton;
    QVBoxLayout *mainLayout;
};

#endif // UI_INSERTACTIVITY_H
