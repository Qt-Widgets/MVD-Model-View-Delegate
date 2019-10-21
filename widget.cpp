#include "widget.h"
#include "ui_widget.h"

#include "tabledelegate.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    tableModel = new TableModel();  // Model
    ui->tableView->setModel(tableModel);    // View
    ui->tableView->setItemDelegate(new TableDelegate);  // Delegate

    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    tableModel->addElement("C++", 90);
    tableModel->addElement("C", 70);
    tableModel->addElement("C#", 50);
    tableModel->addElement("Java", 30);
    tableModel->addElement("PHP", 15);
    tableModel->addElement("Visual Basic", 7);
    tableModel->addElement("Objective-C", 5);
    tableModel->addElement("Python", 4);
}

Widget::~Widget()
{
    delete ui;
}

