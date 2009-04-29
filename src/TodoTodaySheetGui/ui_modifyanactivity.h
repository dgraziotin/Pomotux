/********************************************************************************
** Form generated from reading ui file 'modifyanactivity.ui'
**
** Created: Wed Apr 29 02:26:51 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MODIFYANACTIVITY_H
#define UI_MODIFYANACTIVITY_H

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

class Ui_ModifyAnActivity
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *mATitleLayout;
    QLabel *mATitleLabel;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *mADescriptionLayout;
    QLabel *mADescriptionlabel;
    QLineEdit *mADescriptionLineEdit;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *mADeadlineLayout;
    QLabel *mADeadlineLabel;
    QSpinBox *mADeadlineSpinBox;
    QSpacerItem *horizontalSpacer;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ModifyAnActivity)
    {
        if (ModifyAnActivity->objectName().isEmpty())
            ModifyAnActivity->setObjectName(QString::fromUtf8("ModifyAnActivity"));
        ModifyAnActivity->resize(400, 300);
        horizontalLayoutWidget = new QWidget(ModifyAnActivity);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(70, 10, 249, 41));
        mATitleLayout = new QHBoxLayout(horizontalLayoutWidget);
        mATitleLayout->setObjectName(QString::fromUtf8("mATitleLayout"));
        mATitleLayout->setContentsMargins(0, 0, 0, 0);
        mATitleLabel = new QLabel(horizontalLayoutWidget);
        mATitleLabel->setObjectName(QString::fromUtf8("mATitleLabel"));

        mATitleLayout->addWidget(mATitleLabel);

        horizontalLayoutWidget_2 = new QWidget(ModifyAnActivity);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(20, 90, 361, 51));
        mADescriptionLayout = new QHBoxLayout(horizontalLayoutWidget_2);
        mADescriptionLayout->setObjectName(QString::fromUtf8("mADescriptionLayout"));
        mADescriptionLayout->setContentsMargins(0, 0, 0, 0);
        mADescriptionlabel = new QLabel(horizontalLayoutWidget_2);
        mADescriptionlabel->setObjectName(QString::fromUtf8("mADescriptionlabel"));

        mADescriptionLayout->addWidget(mADescriptionlabel);

        mADescriptionLineEdit = new QLineEdit(horizontalLayoutWidget_2);
        mADescriptionLineEdit->setObjectName(QString::fromUtf8("mADescriptionLineEdit"));

        mADescriptionLayout->addWidget(mADescriptionLineEdit);

        horizontalLayoutWidget_3 = new QWidget(ModifyAnActivity);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(20, 170, 361, 41));
        mADeadlineLayout = new QHBoxLayout(horizontalLayoutWidget_3);
        mADeadlineLayout->setObjectName(QString::fromUtf8("mADeadlineLayout"));
        mADeadlineLayout->setContentsMargins(0, 0, 0, 0);
        mADeadlineLabel = new QLabel(horizontalLayoutWidget_3);
        mADeadlineLabel->setObjectName(QString::fromUtf8("mADeadlineLabel"));

        mADeadlineLayout->addWidget(mADeadlineLabel);

        mADeadlineSpinBox = new QSpinBox(horizontalLayoutWidget_3);
        mADeadlineSpinBox->setObjectName(QString::fromUtf8("mADeadlineSpinBox"));

        mADeadlineLayout->addWidget(mADeadlineSpinBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        mADeadlineLayout->addItem(horizontalSpacer);

        horizontalLayoutWidget_4 = new QWidget(ModifyAnActivity);
        horizontalLayoutWidget_4->setObjectName(QString::fromUtf8("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(110, 220, 182, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        buttonBox = new QDialogButtonBox(horizontalLayoutWidget_4);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);


        retranslateUi(ModifyAnActivity);

        QMetaObject::connectSlotsByName(ModifyAnActivity);
    } // setupUi

    void retranslateUi(QDialog *ModifyAnActivity)
    {
        ModifyAnActivity->setWindowTitle(QApplication::translate("ModifyAnActivity", "Dialog", 0, QApplication::UnicodeUTF8));
        mATitleLabel->setText(QApplication::translate("ModifyAnActivity", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:22pt; font-weight:600;\">Modify Activity</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        mADescriptionlabel->setText(QApplication::translate("ModifyAnActivity", "New Description     ", 0, QApplication::UnicodeUTF8));
        mADeadlineLabel->setText(QApplication::translate("ModifyAnActivity", "New Deadline         ", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(ModifyAnActivity);
    } // retranslateUi

};

namespace Ui {
    class ModifyAnActivity: public Ui_ModifyAnActivity {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIFYANACTIVITY_H
