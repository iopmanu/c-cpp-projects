#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>

extern "C" {
#include "../s21_calculation/s21_calculation.h"
}

namespace Ui {
class Graph;
}

class Graph : public QWidget
{
    Q_OBJECT

public:
    explicit Graph(QWidget *parent = nullptr);
    void scailing();
    void rescale();
    void plot(char *expression);
    void graph_proccessing();
    ~Graph();
    private slots:
        void replot_clicked();


private:
    Ui::Graph *ui;
    double xBegin = -100, xEnd = 100;
    double step;
    char *last_expression;
    std::pair<std::vector<double>, std::vector<double>> graph_points;
};

#endif // GRAPH_H
