/********************************************************************************
** Form generated from reading ui file 'insertnewactivity.ui'
**
** Created: Wed Apr 29 09:56:22 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_INSERTNEWACTIVITY_H
#define UI_INSERTNEWACTIVITY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InsertNewActivity
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *iaTitleLayout;
    QLabel *label;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *iaDescriptionLayout;
    QLabel *iaDescriptionLabel;
    QLineEdit *iaDescriptionLineEdit;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *iaDeadlineLayout;
    QLabel *iaDeadlineLabel;
    QSpinBox *iaDeadlineSpinBox;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *InsertNewActivity)
    {
        if (InsertNewActivity->objectName().isEmpty())
            InsertNewActivity->setObjectName(QString::fromUtf8("InsertNewActivity"));
        InsertNewActivity->resize(400, 300);
        horizontalLayoutWidget = new QWidget(InsertNewActivity);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(90, 10, 208, 41));
        iaTitleLayout = new QHBoxLayout(horizontalLayoutWidget);
        iaTitleLayout->setObjectName(QString::fromUtf8("iaTitleLayout"));
        iaTitleLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        iaTitleLayout->addWidget(label);

        horizontalLayoutWidget_2 = new QWidget(InsertNewActivity);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(20, 100, 351, 41));
        iaDescriptionLayout = new QHBoxLayout(horizontalLayoutWidget_2);
        iaDescriptionLayout->setObjectName(QString::fromUtf8("iaDescriptionLayout"));
        iaDescriptionLayout->setContentsMargins(0, 0, 0, 0);
        iaDescriptionLabel = new QLabel(horizontalLayoutWidget_2);
        iaDescriptionLabel->setObjectName(QString::fromUtf8("iaDescriptionLabel"));

        iaDescriptionLayout->addWidget(iaDescriptionLabel);

        iaDescriptionLineEdit = new QLineEdit(horizontalLayoutWidget_2);
        iaDescriptionLineEdit->setObjectName(QString::fromUtf8("iaDescriptionLineEdit"));

        iaDescriptionLayout->addWidget(iaDescriptionLineEdit);

        horizontalLayoutWidget_3 = new QWidget(InsertNewActivity);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(20, 160, 351, 41));
        iaDeadlineLayout = new QHBoxLayout(horizontalLayoutWidget_3);
        iaDeadlineLayout->setObjectName(QString::fromUtf8("iaDeadlineLayout"));
        iaDeadlineLayout->setContentsMargins(0, 0, 0, 0);
        iaDeadlineLabel = new QLabel(horizontalLayoutWidget_3);
        iaDeadlineLabel->setObjectName(QString::fromUtf8("iaDeadlineLabel"));

        iaDeadlineLayout->addWidget(iaDeadlineLabel);

        iaDeadlineSpinBox = new QSpinBox(horizontalLayoutWidget_3);
        iaDeadlineSpinBox->setObjectName(QString::fromUtf8("iaDeadlineSpinBox"));

        iaDeadlineLayout->addWidget(iaDeadlineSpinBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        iaDeadlineLayout->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(InsertNewActivity);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(120, 230, 180, 34));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(InsertNewActivity);

        QMetaObject::connectSlotsByName(InsertNewActivity);
    } // setupUi

    void retranslateUi(QDialog *InsertNewActivity)
    {
        InsertNewActivity->setWindowTitle(QApplication::translate("InsertNewActivity", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("InsertNewActivity", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:22pt; font-weight:600;\">New Activity</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        iaDescriptionLabel->setText(QApplication::translate("InsertNewActivity", "Description", 0, QApplication::UnicodeUTF8));
        iaDeadlineLabel->setText(QApplication::translate("InsertNewActivity", "Deadline    ", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(InsertNewActivity);
    } // retranslateUi

};

namespace Ui {
    class InsertNewActivity: public Ui_InsertNewActivity {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSERTNEWACTIVITY_H
