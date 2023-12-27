#include "qblewindow.h"
#include "ui_qblewindow.h"
#include <adaptermodel.h>

QBleWindow::QBleWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QBleWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(new AdapterModel(this));
}

QBleWindow::~QBleWindow()
{
    delete ui;
}

void QBleWindow::on_pushButton_clicked()
{
    //
}
