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

private:
    Ui::QBleWindow *ui;
};
