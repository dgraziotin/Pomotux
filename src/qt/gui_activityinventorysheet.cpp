#include "gui_activityinventorysheet.hpp"
#include "ui_gui_activityinventorysheet.h"
#include <string>
#include <time.h>

GuiActivityInventorySheet::GuiActivityInventorySheet(QWidget *parent, PomotuxDatabase& database)
    : QMainWindow(parent), ui(new Ui::GuiActivityInventorySheet)
{
    db = &database;
    ui->setupUi(this);
    now = time(NULL);
    count = 0;
}

GuiActivityInventorySheet::~GuiActivityInventorySheet()
{
    delete ui;
}

void GuiActivityInventorySheet::on_newActivityButton_clicked()
{
    /*Calling the window for creating a new Activity*/
    InsertNewActivity *dialog = new InsertNewActivity(0, *(db));
    dialog->show();
    dialog->exec();

    mainController = dialog->controller;
    if (mainController > 0) {
        count++;
        int idNumber = (int) count;
        int riga = (int) count - 1;
        /*casting for the description*/
        description = &dialog->text;
        QByteArray ba = description->toLatin1();
        const char *text = ba.data();

        /*for the dates*/
        char today[80];
        struct tm *ts;
        ts = localtime(&now);
        strftime(today, 80, "%a %Y-%m-%d", ts);

        value = &dialog->dayToDeadline;
        time_t deadlineInt = now + *(value)*(86400);
        char deadline[80];
        struct tm *ts2;
        ts2 = localtime(&deadlineInt);
        strftime(deadline, 80, "%a %Y-%m-%d", ts2);

        /*casting for the id*/
        stringstream sstr;
        sstr << idNumber;
        string str1 = sstr.str();
        const char *id = str1.c_str();

        /*casting for numPomodoro and priority*/
        stringstream sstr1;
        sstr1 << 0;
        string str2 = sstr1.str();
        const char *defaultValues = str2.c_str();

        if (this->ui->ais->rowCount() < count)
            this->ui->ais->setRowCount(count);

        /*creating the new row*/
        QTableWidgetItem *__rowItem = new QTableWidgetItem();
        this->ui->ais->setVerticalHeaderItem(riga, __rowItem);
        QTableWidgetItem *__tableItem2 = new QTableWidgetItem();
        this->ui->ais->setItem(riga, 0, __tableItem2);
        QTableWidgetItem *__tableItem3 = new QTableWidgetItem();
        this->ui->ais->setItem(riga, 1, __tableItem3);
        QTableWidgetItem *__tableItem4 = new QTableWidgetItem();
        this->ui->ais->setItem(riga, 2, __tableItem4);
        QTableWidgetItem *__tableItem5 = new QTableWidgetItem();
        this->ui->ais->setItem(riga, 3, __tableItem5);
        QTableWidgetItem *__tableItem6 = new QTableWidgetItem();
        this->ui->ais->setItem(riga, 4, __tableItem6);
        QTableWidgetItem *__tableItem7 = new QTableWidgetItem();
        this->ui->ais->setItem(riga, 5, __tableItem7);
        QTableWidgetItem *__tableItem8 = new QTableWidgetItem();
        this->ui->ais->setItem(riga, 6, __tableItem8);

        /*Insert the correct values in the fields*/
        this->ui->ais->verticalHeaderItem(riga)->setText(QApplication::translate("GuiActivityInventorySheet", "-->", 0, QApplication::UnicodeUTF8));
        this->ui->ais->item(riga, 0)->setText(QApplication::translate("GuiActivityInventorySheet", id, 0, QApplication::UnicodeUTF8));
        this->ui->ais->item(riga, 1)->setText(QApplication::translate("GuiActivityInventorySheet", text , 0, QApplication::UnicodeUTF8));
        this->ui->ais->item(riga, 2)->setText(QApplication::translate("GuiActivityInventorySheet", today , 0, QApplication::UnicodeUTF8));
        this->ui->ais->item(riga, 3)->setText(QApplication::translate("GuiActivityInventorySheet", deadline , 0, QApplication::UnicodeUTF8));
        this->ui->ais->item(riga, 4)->setText(QApplication::translate("GuiActivityInventorySheet", defaultValues , 0, QApplication::UnicodeUTF8));
        this->ui->ais->item(riga, 5)->setText(QApplication::translate("GuiActivityInventorySheet", defaultValues , 0, QApplication::UnicodeUTF8));
        this->ui->ais->item(riga, 6)->setText(QApplication::translate("GuiActivityInventorySheet", "False" , 0, QApplication::UnicodeUTF8));

        Q_UNUSED(this);
    }
}

void GuiActivityInventorySheet::on_deleteActivityButton_clicked()
{
    QString idString = this->ui->ais->item(row, 0)->text();
    bool ok;
    int id = idString.toInt(&ok, 16);
    Activity at = select<Activity>(*(db), Activity::Id == id).one();
    at.del();
    this->ui->ais->removeRow(row);
    count --;
}


void GuiActivityInventorySheet::on_ais_itemClicked(QTableWidgetItem* item)
{
        row = (int) item->row();
}

void GuiActivityInventorySheet::on_modifyActivityButton_clicked()
{
    ModifyAnActivity *dialog = new ModifyAnActivity(0, *(db));
    dialog->show();
    dialog->exec();

    description = &dialog->text;
    QByteArray ba = description->toLatin1();
    const char *text = ba.data();

    value = &dialog->dayToDeadline;

    /*
    time_t deadlineInt = now + *(value)*(86400);
    char deadline[80];
    struct tm *ts2;
    ts2 = localtime(&deadlineInt);
    strftime(deadline, 80, "%a %Y-%m-%d", ts2);*/

    QString idString = this->ui->ais->item(row, 0)->text();
    bool ok;
    int id = idString.toInt(&ok, 16);

    Activity at = select<Activity>(*(db), Activity::Id == id).one();

    string newDescription = description->toStdString();
    at.Modify(*(db), at, *(value), newDescription);

    this->ui->ais->item(row, 1)->setText(QApplication::translate("GuiActivityInventorySheet", text , 0, QApplication::UnicodeUTF8));

}
