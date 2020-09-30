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
    QString html = QFileDialog::getOpenFileName(this, "Open", QDir::currentPath(), "Text(*.txt)");

    if (html.isEmpty()) {
        ui->plainTextEdit->setPlainText("Error !");
        ui->temp_edit->clear();
        ui->usd_edit->clear();
        ui->eur_edit->clear();
    }
    QStringList data = getData(html);
    ui->plainTextEdit->setPlainText(html);
    ui->temp_edit->setText(data[0]);
    ui->usd_edit->setText(data[1]);
    ui->eur_edit->setText(data[2]);

}

QStringList MainWindow::getData(const QString &html)
{
    QStringList list;
    QRegExp regex("<span class=\"weather__temp svelte-bjx6w8\" title=\"ощущается как \"([(+|-)\\d,]+)\"\" >([(+|-)\\d,]+)</span>");
    QRegExp regex1("(<div class=\"rate__currency svelte-r2v6pj\">)([\\d,]+)(</div>)");
    int lastPos = 0;
    while((lastPos = regex.indexIn(html, lastPos)) != -1) {
        lastPos += regex.matchedLength();
        list.append(regex.cap(2));
    }
    lastPos = 0;
    while((lastPos = regex1.indexIn(html, lastPos)) != -1) {
        lastPos += regex1.matchedLength();
        list.append(regex1.cap(2));
    }
    return list;
}
