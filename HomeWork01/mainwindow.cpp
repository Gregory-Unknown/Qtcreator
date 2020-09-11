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
    double a = ui->side_a->text().toDouble();
    double b = ui->side_b->text().toDouble();
    double alpha = ui->angle_alpha->text().toDouble();
    if (a <= 0.0 || b <= 0.0 || alpha <= 0.0)
        ui->result->setText("Incorrect input ! ERROR !");
    else if (ui->degree_button->isChecked() && alpha > 180)
        ui->result->setText("Incorrect input angle ! ERROR !");
    else if (ui->radian_button->isChecked() && alpha > M_PI)
        ui->result->setText("Incorrect input angle ! ERROR !");
    else {
        if (ui->degree_button->isChecked())
            alpha = qDegreesToRadians(alpha);
        double c = qSqrt(qPow(a, 2) + qPow(b, 2) - 2 * a * b * qCos(alpha));
        ui->result->setText(QString::number(c));
    }

}
