#include "mainwindow.h"
#include "ui_mainwindow.h"

extern "C" {
#include "smart_calc.h"
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_min, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_l_br, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_r_br, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits()
{
    QPushButton *button = (QPushButton *)sender();
    ui->display->setText(ui->display->text() + button->text());
}

void MainWindow::on_pushButton_dot_clicked()
{
    if(!(ui->display->text().contains('.')))
        ui->display->setText(ui->display->text() + ".");
}


void MainWindow::on_pushButton_del_clicked()
{
     ui->display->setText(ui->display->text().left(ui->display->text().size()-1));
}


void MainWindow::on_pushButton_AC_clicked()
{
    ui->display->setText("");
}

void MainWindow::on_pushButton_eq_clicked()
{
    QString to_display;
    double result = 0.0;
    x_value = ui->x_display->text().toDouble();
    int error = parse_input((char*)ui->display->text().toStdString().c_str(), x_value, &result);
    if (error) {
       ui->display->setText("Ошибка в данных");
    } else {
       to_display = QString::number(result, 'g', 7);
       ui->display->setText(to_display);
    }
}

void MainWindow::on_pushButton_pow_clicked()
{
    ui->display->setText(ui->display->text() + "^");
}

void MainWindow::on_pushButton_graph_clicked()
{
    ui->graphic->clearGraphs();

    h = 0.1;
    xBegin = ui->min_x->value();
    xEnd = ui->max_x->value();
    ui->graphic->xAxis->setRange(ui->min_x->value(), ui->max_x->value());
    ui->graphic->yAxis->setRange(ui->min_y->value(), ui->max_y->value());

    N = (xEnd-xBegin)/h+2;

    for (X = xBegin; X <= xEnd; X += h) {
        parse_input((char*)ui->display->text().toStdString().c_str(), X, &Y);
        x.push_back(X);
        y.push_back(Y);
    }

    ui->graphic->addGraph();
    ui->graphic->graph(0)->addData(x, y);
    ui->graphic->replot();
    x.clear();
    y.clear();
}

