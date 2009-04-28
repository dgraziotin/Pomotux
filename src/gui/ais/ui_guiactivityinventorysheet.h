/********************************************************************************
** Form generated from reading ui file 'guiactivityinventorysheet.ui'
**
** Created: Mon Apr 27 13:45:15 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_GUIACTIVITYINVENTORYSHEET_H
#define UI_GUIACTIVITYINVENTORYSHEET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GuiActivityInventorySheet
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *titleLayout;
    QLabel *titleLabel;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *aisTableLayout;
    QTableWidget *ais;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *buttonsLayout;
    QPushButton *newActivityButton;
    QPushButton *modifyActivityButton;
    QPushButton *deleteActivityButton;
    QPushButton *insertInTTSButton;

    void setupUi(QMainWindow *GuiActivityInventorySheet)
    {
    if (GuiActivityInventorySheet->objectName().isEmpty())
        GuiActivityInventorySheet->setObjectName(QString::fromUtf8("GuiActivityInventorySheet"));
    GuiActivityInventorySheet->resize(744, 494);
    centralWidget = new QWidget(GuiActivityInventorySheet);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    verticalLayoutWidget = new QWidget(centralWidget);
    verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
    verticalLayoutWidget->setGeometry(QRect(160, 20, 402, 80));
    titleLayout = new QVBoxLayout(verticalLayoutWidget);
    titleLayout->setSpacing(6);
    titleLayout->setMargin(11);
    titleLayout->setObjectName(QString::fromUtf8("titleLayout"));
    titleLayout->setContentsMargins(0, 0, 0, 0);
    titleLabel = new QLabel(verticalLayoutWidget);
    titleLabel->setObjectName(QString::fromUtf8("titleLabel"));

    titleLayout->addWidget(titleLabel);

    horizontalLayoutWidget = new QWidget(centralWidget);
    horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
    horizontalLayoutWidget->setGeometry(QRect(20, 120, 711, 261));
    aisTableLayout = new QHBoxLayout(horizontalLayoutWidget);
    aisTableLayout->setSpacing(6);
    aisTableLayout->setMargin(11);
    aisTableLayout->setObjectName(QString::fromUtf8("aisTableLayout"));
    aisTableLayout->setContentsMargins(0, 0, 0, 0);
    ais = new QTableWidget(horizontalLayoutWidget);
    if (ais->columnCount() < 7)
        ais->setColumnCount(7);
    QTableWidgetItem *__colItem = new QTableWidgetItem();
    ais->setHorizontalHeaderItem(0, __colItem);
    QTableWidgetItem *__colItem1 = new QTableWidgetItem();
    ais->setHorizontalHeaderItem(1, __colItem1);
    QTableWidgetItem *__colItem2 = new QTableWidgetItem();
    ais->setHorizontalHeaderItem(2, __colItem2);
    QTableWidgetItem *__colItem3 = new QTableWidgetItem();
    ais->setHorizontalHeaderItem(3, __colItem3);
    QTableWidgetItem *__colItem4 = new QTableWidgetItem();
    ais->setHorizontalHeaderItem(4, __colItem4);
    QTableWidgetItem *__colItem5 = new QTableWidgetItem();
    ais->setHorizontalHeaderItem(5, __colItem5);
    QTableWidgetItem *__colItem6 = new QTableWidgetItem();
    ais->setHorizontalHeaderItem(6, __colItem6);
    ais->setObjectName(QString::fromUtf8("ais"));

    aisTableLayout->addWidget(ais);

    horizontalLayoutWidget_2 = new QWidget(centralWidget);
    horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
    horizontalLayoutWidget_2->setGeometry(QRect(120, 400, 461, 80));
    buttonsLayout = new QHBoxLayout(horizontalLayoutWidget_2);
    buttonsLayout->setSpacing(6);
    buttonsLayout->setMargin(11);
    buttonsLayout->setObjectName(QString::fromUtf8("buttonsLayout"));
    buttonsLayout->setContentsMargins(0, 0, 0, 0);
    newActivityButton = new QPushButton(horizontalLayoutWidget_2);
    newActivityButton->setObjectName(QString::fromUtf8("newActivityButton"));

    buttonsLayout->addWidget(newActivityButton);

    modifyActivityButton = new QPushButton(horizontalLayoutWidget_2);
    modifyActivityButton->setObjectName(QString::fromUtf8("modifyActivityButton"));

    buttonsLayout->addWidget(modifyActivityButton);

    deleteActivityButton = new QPushButton(horizontalLayoutWidget_2);
    deleteActivityButton->setObjectName(QString::fromUtf8("deleteActivityButton"));

    buttonsLayout->addWidget(deleteActivityButton);

    insertInTTSButton = new QPushButton(horizontalLayoutWidget_2);
    insertInTTSButton->setObjectName(QString::fromUtf8("insertInTTSButton"));

    buttonsLayout->addWidget(insertInTTSButton);

    GuiActivityInventorySheet->setCentralWidget(centralWidget);

    retranslateUi(GuiActivityInventorySheet);

    QMetaObject::connectSlotsByName(GuiActivityInventorySheet);
    } // setupUi

    void retranslateUi(QMainWindow *GuiActivityInventorySheet)
    {
    GuiActivityInventorySheet->setWindowTitle(QApplication::translate("GuiActivityInventorySheet", "GuiActivityInventorySheet", 0, QApplication::UnicodeUTF8));
    titleLabel->setText(QApplication::translate("GuiActivityInventorySheet", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:22pt; font-weight:600;\">Activity Inventory Sheet</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    ais->horizontalHeaderItem(0)->setText(QApplication::translate("GuiActivityInventorySheet", "Id", 0, QApplication::UnicodeUTF8));
    ais->horizontalHeaderItem(1)->setText(QApplication::translate("GuiActivityInventorySheet", "Description", 0, QApplication::UnicodeUTF8));
    ais->horizontalHeaderItem(2)->setText(QApplication::translate("GuiActivityInventorySheet", "Insertion Date", 0, QApplication::UnicodeUTF8));
    ais->horizontalHeaderItem(3)->setText(QApplication::translate("GuiActivityInventorySheet", "Deadline", 0, QApplication::UnicodeUTF8));
    ais->horizontalHeaderItem(4)->setText(QApplication::translate("GuiActivityInventorySheet", "Priority", 0, QApplication::UnicodeUTF8));
    ais->horizontalHeaderItem(5)->setText(QApplication::translate("GuiActivityInventorySheet", "Num Pomodori", 0, QApplication::UnicodeUTF8));
    ais->horizontalHeaderItem(6)->setText(QApplication::translate("GuiActivityInventorySheet", "Is Finished", 0, QApplication::UnicodeUTF8));
    newActivityButton->setText(QApplication::translate("GuiActivityInventorySheet", "New Activity", 0, QApplication::UnicodeUTF8));
    modifyActivityButton->setText(QApplication::translate("GuiActivityInventorySheet", "Modify Activity", 0, QApplication::UnicodeUTF8));
    deleteActivityButton->setText(QApplication::translate("GuiActivityInventorySheet", "Delete Activity", 0, QApplication::UnicodeUTF8));
    insertInTTSButton->setText(QApplication::translate("GuiActivityInventorySheet", "Insert in TTS", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(GuiActivityInventorySheet);
    } // retranslateUi

};

namespace Ui {
    class GuiActivityInventorySheet: public Ui_GuiActivityInventorySheet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUIACTIVITYINVENTORYSHEET_H
