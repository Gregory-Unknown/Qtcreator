#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QStandardItemModel(this);
    LstVW = new lstVw(model);
    if (!LstVW) close();

    ui->listView->setModel(model);
    ui->listView->setAcceptDrops(true);
    ui->listView->setDragEnabled(true);
    ui->listView->setDefaultDropAction(Qt::MoveAction);


}

MainWindow::~MainWindow()
{
    if (LstVW) {
        delete LstVW;
        LstVW = nullptr;
    }

    delete ui;
}



void MainWindow::on_checkBox_clicked()
{
    if (ui->checkBox->isChecked()) {
        ui->listView->setViewMode(QListView::IconMode);
    }
    else {
        ui->listView->setViewMode(QListView::ListMode);
    }

    ui->listView->setAcceptDrops(true);
    ui->listView->setDragEnabled(true);
    ui->listView->setDragDropMode(QAbstractItemView::DragDrop);
    ui->listView->setDefaultDropAction(Qt::MoveAction);
}

void MainWindow::on_pushButton_clicked()
{
    model->appendRow(new QStandardItem(QIcon("./Icons/XXX.png"), "newElement"));
}
