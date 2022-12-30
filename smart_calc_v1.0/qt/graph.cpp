#include "graph.h"
#include "ui_graph.h"

Graph::Graph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Graph)
{
    ui->setupUi(this);
    connect(ui->Reprint, SIGNAL(clicked()), this, SLOT(replot_clicked()));
}

Graph::~Graph()
{
    delete ui;
}

void Graph::rescale() {
    QString xBegin_string = ui->lineBegin->text();
    QString xEnd_string = ui->lineEnd->text();

    this->xBegin = xBegin_string.toDouble();
    this->xEnd = xEnd_string.toDouble();
}

void Graph::scailing() {
    if (xEnd - xBegin <= 10)
        this->step = 0.00001;
      else if (xEnd - xBegin <= 100)
        this->step = 0.0001;
      else if (xEnd - xBegin <= 1000)
        this->step = 0.001;
      else if (xEnd - xBegin <= 10000)
        this->step = 0.01;
      else if (xEnd - xBegin <= 100000)
        this->step = 0.1;
      else if (xEnd - xBegin > 100000)
        this->step = 0.5;
}

void Graph::plot(char *expression) {
    for (double x = xBegin; (x <= xEnd); x += step) {
        double calculated_number = 0;
        if (main_calculations(expression, x, &calculated_number)) {
            continue;
        } else {
            this->graph_points.first.push_back(x);
            this->graph_points.second.push_back((calculated_number));
       }
    }

    this->last_expression = expression;
}

void Graph::replot_clicked() {
    this->graph_points.first.clear();
    this->graph_points.second.clear();
    this->rescale();
    this->scailing();
    this->plot(this->last_expression);
    this->graph_proccessing();
}

void Graph::graph_proccessing() {
    ui->graph->yAxis->setRange(this->xBegin, this->xEnd);
    ui->graph->xAxis->setRange(this->xBegin, this->xEnd);
    ui->graph->addGraph();
    ui->graph->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->graph->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 2));

    QVector<double> x_points = QVector<double>(this->graph_points.first.begin(), this->graph_points.first.end());
    QVector<double> y_points = QVector<double>(this->graph_points.second.begin(), this->graph_points.second.end());

    ui->graph->graph(0)->addData(x_points, y_points);
    ui->graph->replot();
    ui->graph->setInteraction(QCP::iRangeZoom, true);
    ui->graph->setInteraction(QCP::iRangeDrag, true);
}
