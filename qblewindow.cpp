#include "qblewindow.h"
#include "ui_qblewindow.h"
#include <QDebug>
#include <adaptermodel.h>

QBleWindow::QBleWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QBleWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(new AdapterModel(this));
    ui->tableView->update(QModelIndex());
}

QBleWindow::~QBleWindow()
{
    delete ui;
}

void QBleWindow::on_pushButton_clicked()
{
    //
}

void QBleWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    qDebug() << "TBV doubleClicked:" << index;
}

void QBleWindow::on_tableView_clicked(const QModelIndex &index)
{
    qDebug() << "TBV clicked:" << index;
}

void QBleWindow::on_tableView_activated(const QModelIndex &index)
{
    qDebug() << "TBV activated:" << index;
}
