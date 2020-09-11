#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    double a = ui->input_a->text().toDouble();
    double b = ui->input_b->text().toDouble();
    double c = ui->input_c->text().toDouble();
    double disc = (qPow(b,2) - (4 * a * c));
    double x1 = 0;
    double x2 = 0;
    if (a == 0 && b == 0 && c == 0)
        ui->result->setText("x is a any number");
    else if (a == 0 && b == 0)
        ui->result->setText("No roots");
    else if (a == 0 && c == 0)
        ui->result->setText("x = 0");
    else if (a == 0) {
        x1 = -c/b;
        ui->result->setText("x = " +QString::number(x1));
    }
    else if (disc < 0)
        ui->result->setText("No roots");
    else if (disc == 0) {
        x1 = x2 = ((-b) / 2 * a);
        ui->result->setText("x1 = x2 = "+QString::number(x1));
    }
    else if (disc > 0) {
        x1 = (((-b) + qSqrt(disc)) / 2 * a);
        x2 = (((-b) - qSqrt(disc)) / 2 * a);
        ui->result->setText("x1 = " +QString::number(x1)+" x2 = "+QString::number(x2));
    }
}
