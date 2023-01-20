#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("3DViewer_v1.0");
    QColor color(255, 127, 50);

    ui->widget = new GraphEngine(parent);

    QFont font = ui->filename_label->font();
    font.setPixelSize(15);
    ui->filename_label->setFont(font);

    font = ui->SCALE->font();
    font.setPixelSize(15);
    ui->SCALE->setFont(font);

    font = ui->ROTATE->font();
    font.setPixelSize(15);
    ui->ROTATE->setFont(font);

    font = ui->MOVE->font();
    font.setPixelSize(15);
    ui->MOVE->setFont(font);
}

MainWindow::~MainWindow()
{
    delete ui;
}

