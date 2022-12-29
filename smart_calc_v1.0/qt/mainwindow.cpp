#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton0, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton1, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton2, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton3, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton4, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton5, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton6, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton7, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton8, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton9, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton_openbracket, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton_closebracket, SIGNAL(clicked()), this,
              SLOT(signal_processing()));
      connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(clicked_clear()));
      connect(ui->pushButton_minux, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton_multi, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton_var, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton_degree, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton_exp, SIGNAL(clicked()), this, SLOT(signal_processing()));
      connect(ui->pushButton_equal, SIGNAL(clicked()), this, SLOT(signal_processing()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::signal_processing() {
    QPushButton *button = (QPushButton *)sender();
    QString sender_text = button->text();

    if (button->text() == "=") {
            clicked_equal();
            return;
    }

    if (flag) {
        flag = false;
        if ((ui->label->text() == "ERROR") || (ui->label->text() == "nan")) {
            clicked_clear();
            make_expression();
        }
    } else {
        make_expression();
    }
}

void MainWindow::make_expression() {
    QPushButton *button = (QPushButton *)sender();
    QString sender_text = button->text();

    if (ui->label->text() == "0") {
        if (sender_text == ".") {
            ui->label->setText("0" + sender_text);
        } else {
            ui->label->setText(sender_text);
        }
    } else {
        ui->label->setText(ui->label->text() + sender_text);
    }
}

void MainWindow::clicked_clear() {
    ui->label->setText("0");
}

void MainWindow::clicked_equal() {
    double result = 0;
    QString screen_expression = ui->label->text();
    QByteArray sequence = screen_expression.toLocal8Bit();
    char *infix_expression = sequence.data();

    int8_t error = main_calculations(infix_expression, 0, &result);

    if (error) {
        ui->label->setText("ERROR");
    } else {
        QString result_string = QString::number(result, 'g', 8);
        ui->label->setText(result_string);
    }

    flag = true;
}
