#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view = new QGraphicsView();
    scence = new QGraphicsScene();

    view->setScene(scence);
    this->setCentralWidget(view);
    counter = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton) {
        MyClass *item;
        if (counter == 3) counter = 0;
        item = new MyClass(this, counter);
        counter++;
        item->setBrush(QBrush(QColor(rand() % 256, rand() % 256, rand() % 256)));
        scence->addItem(item);
        item->setPos(ev->pos().x(), ev->pos().y());
        connect(item, SIGNAL(reDraw()), this, SLOT(reDraw()));
    }
}

void MainWindow::wheelEvent(QWheelEvent *ev)
{
    const double scalefactor = 1.15;
    if (ev->delta() > 0) {
        view->scale(scalefactor, scalefactor);
    } else {
        view->scale(1.0 / scalefactor, 1.0 / scalefactor);
    }
}

void MainWindow::reDraw()
{
    scence->update();
    this->update();
}
