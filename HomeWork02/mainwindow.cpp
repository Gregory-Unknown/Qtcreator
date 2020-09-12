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


void MainWindow::on_button_1_clicked()
{
    QString dest = ui->qpte_1->toPlainText();
    ui->qpte_2->insertPlainText(dest);
}

void MainWindow::on_button_2_clicked()
{
    QString dest = ui->qpte_1->toPlainText();
    ui->qpte_2->setPlainText(dest);
}

void MainWindow::on_button_3_clicked()
{
    QString dest = ui->qpte_1->toPlainText();
    ui->qpte_2->setHtml("<font color='red'>Hello</font>");
}
