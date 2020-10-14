#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    fmqw = new FirstMyQtWidget(this);
}

MainWindow::~MainWindow()
{

}

