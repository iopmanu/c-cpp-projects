#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

extern "C" {
#include "../s21_calculation/s21_calculation.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
  private slots:
    void signal_processing();
    void make_expression();
    void clicked_clear();
    void clicked_equal();
private:
    Ui::MainWindow *ui;
    bool flag = false;
    bool contains_x = false;
};
#endif // MAINWINDOW_H
