/********************************************************************************
** Form generated from reading ui file 'todotodaysheetgui.ui'
**
** Created: Wed Apr 29 09:56:22 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_TODOTODAYSHEETGUI_H
#define UI_TODOTODAYSHEETGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TodoTodaySheetGuiClass
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTableWidget *tableWidget;
    QGroupBox *groupBox;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *startActivityButton;
    QPushButton *stopActivity;
    QPushButton *postponeActivityButton;
    QPushButton *finishActivityButton;

    void setupUi(QMainWindow *TodoTodaySheetGuiClass)
    {
        if (TodoTodaySheetGuiClass->objectName().isEmpty())
            TodoTodaySheetGuiClass->setObjectName(QString::fromUtf8("TodoTodaySheetGuiClass"));
        TodoTodaySheetGuiClass->resize(600, 439);
        centralWidget = new QWidget(TodoTodaySheetGuiClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 70, 351, 351));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setMargin(11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        tableWidget = new QTableWidget(verticalLayoutWidget);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout->addWidget(tableWidget);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(420, 70, 151, 351));
        verticalLayoutWidget_2 = new QWidget(groupBox);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 30, 131, 301));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setMargin(11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        startActivityButton = new QPushButton(verticalLayoutWidget_2);
        startActivityButton->setObjectName(QString::fromUtf8("startActivityButton"));

        verticalLayout_2->addWidget(startActivityButton);

        stopActivity = new QPushButton(verticalLayoutWidget_2);
        stopActivity->setObjectName(QString::fromUtf8("stopActivity"));

        verticalLayout_2->addWidget(stopActivity);

        postponeActivityButton = new QPushButton(verticalLayoutWidget_2);
        postponeActivityButton->setObjectName(QString::fromUtf8("postponeActivityButton"));

        verticalLayout_2->addWidget(postponeActivityButton);

        finishActivityButton = new QPushButton(verticalLayoutWidget_2);
        finishActivityButton->setObjectName(QString::fromUtf8("finishActivityButton"));

        verticalLayout_2->addWidget(finishActivityButton);

        TodoTodaySheetGuiClass->setCentralWidget(centralWidget);

        retranslateUi(TodoTodaySheetGuiClass);

        QMetaObject::connectSlotsByName(TodoTodaySheetGuiClass);
    } // setupUi

    void retranslateUi(QMainWindow *TodoTodaySheetGuiClass)
    {
        TodoTodaySheetGuiClass->setWindowTitle(QApplication::translate("TodoTodaySheetGuiClass", "TodoTodaySheetGui", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("TodoTodaySheetGuiClass", "Activity List:", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("TodoTodaySheetGuiClass", "id", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("TodoTodaySheetGuiClass", "description", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("TodoTodaySheetGuiClass", "position", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("TodoTodaySheetGuiClass", "commands", 0, QApplication::UnicodeUTF8));
        startActivityButton->setText(QApplication::translate("TodoTodaySheetGuiClass", "start", 0, QApplication::UnicodeUTF8));
        stopActivity->setText(QApplication::translate("TodoTodaySheetGuiClass", "stop", 0, QApplication::UnicodeUTF8));
        postponeActivityButton->setText(QApplication::translate("TodoTodaySheetGuiClass", "postpone", 0, QApplication::UnicodeUTF8));
        finishActivityButton->setText(QApplication::translate("TodoTodaySheetGuiClass", "finish", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(TodoTodaySheetGuiClass);
    } // retranslateUi

};

namespace Ui {
    class TodoTodaySheetGuiClass: public Ui_TodoTodaySheetGuiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TODOTODAYSHEETGUI_H
