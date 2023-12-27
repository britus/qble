#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QTableView>

namespace Ui
{
class QBleWindow;
}

class QBleWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QBleWindow(QWidget *parent = nullptr);
    ~QBleWindow();

private slots:
    void on_pushButton_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_activated(const QModelIndex &index);

private:
    Ui::QBleWindow *ui;
};
