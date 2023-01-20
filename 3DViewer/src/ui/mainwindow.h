#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "engine.hpp"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void clicked_draw();
    void set_object_filename();

private:
    Ui::MainWindow *ui;
    GraphEngine view;
};
#endif  // MAINWINDOW_H
