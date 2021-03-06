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

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (Qt::ControlModifier) {
        if (event->key() == Qt::Key_O) {
            on_open_Button_clicked();
        } else if (event->key() == Qt::Key_S) {
            on_save_Button_clicked();
        } else if (event->key() ==  Qt::Key_N){
            on_open_Button_clicked();
        } else if (event->key() == Qt::Key_Q) {
            close();
        }
    }

}

void MainWindow::on_open_Button_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open"), QDir::currentPath(), "Text(*.txt)");
    QFile file(fileName);
    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        QByteArray byteArray = file.readAll();
        ui->plainTextEdit->setPlainText(byteArray.data());
    }
}

void MainWindow::on_read_Button_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Read"), QDir::currentPath(), "Text(*.txt)");
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray byteArray = file.readAll();
        ui->plainTextEdit->setReadOnly(file.isOpen());
        ui->plainTextEdit->setPlainText(byteArray.data());
    }
}

void MainWindow::on_save_Button_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save"), QDir::currentPath(), "Text(*.txt)");
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QString str = ui->plainTextEdit->toPlainText();
        QByteArray byteArray = str.toUtf8();
        file.write(byteArray, byteArray.length());
    }
}

void MainWindow::on_help_Button_clicked()
{
    QFile file(":/new/prefix1/help.txt");
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray byteArray = file.readAll();
        ui->plainTextEdit->setPlainText(byteArray.data());
    }
}

