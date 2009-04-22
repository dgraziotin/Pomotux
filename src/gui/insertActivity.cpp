#include <QtGui>
#include "insertActivity.hpp"
#include <string>

InsertActivity::InsertActivity(QWidget *parent): QDialog(parent)
{
    titleLabel = new QLabel(tr("InsertActivity"));
    titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
    QFont font;
    font.setFamily(QString::fromUtf8("AlArabiya"));
    font.setPointSize(20);
    titleLabel->setFont(font);

    descriptionLabel = new QLabel(tr("Description: "));
    descriptionLabel->setObjectName(QString::fromUtf8("descriptionLabel"));
    QFont font1;
    font1.setFamily(QString::fromUtf8("AlArabiya"));
    font1.setPointSize(12);
    descriptionLabel->setFont(font1);
    descriptionLabel->setText(QApplication::translate("InsertActivity", "Description", 0, QApplication::UnicodeUTF8));

    lineEdit = new QLineEdit;
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

    deadlineLabel = new QLabel(tr("deadline: "));
    deadlineLabel->setObjectName(QString::fromUtf8("deadlineLabel"));
    deadlineLabel->setFont(font1);
    deadlineLabel->setText(QApplication::translate("InsertActivity", "Deadline", 0, QApplication::UnicodeUTF8));

    dateEdit = new QDateEdit;
    dateEdit->setObjectName(QString::fromUtf8("dateEdit"));

    submitButton = new QPushButton;
    submitButton->setObjectName(QString::fromUtf8("submitButton"));
    submitButton->setEnabled(true);
    submitButton->setCursor(QCursor(Qt::PointingHandCursor));
    submitButton->setText(QApplication::translate("InsertActivity", "Submit", 0, QApplication::UnicodeUTF8));

    cancelButton = new QPushButton;
    cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
    cancelButton->setCursor(QCursor(Qt::PointingHandCursor));
    cancelButton->setText(QApplication::translate("InsertActivity", "Cancel", 0, QApplication::UnicodeUTF8));

    /*Set the signals*/

    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(insertNewActivity()));

    /*Set the layout*/

    titleLayout = new QVBoxLayout;
    titleLayout->addWidget(titleLabel);
    descriptionLayout = new QHBoxLayout;
    descriptionLayout->addWidget(descriptionLabel);
    descriptionLayout->addWidget(lineEdit);
    deadlineLayout = new QHBoxLayout;
    deadlineLayout->addWidget(deadlineLabel);
    deadlineLayout->addWidget(dateEdit);
    buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(submitButton);
    buttonsLayout->addWidget(cancelButton);
    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(titleLayout);
    mainLayout->addLayout(descriptionLayout);
    mainLayout->addLayout(deadlineLayout);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);
}

void InsertActivity::insertNewActivity()
{

}	

