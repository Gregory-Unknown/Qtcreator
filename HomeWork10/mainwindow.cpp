#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    parseText = new ParseText();
    if (!parseText) close();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_plainTextEdit_textChanged()
{
    QString txt = ui->plainTextEdit->toPlainText();
    qint32 pos = 0;
    while (1) {
        qint32 fnd = txt.indexOf("#@", pos);
        if (fnd == (-1)) return;
        pos = fnd + 1;
        int r = txt.indexOf('@', fnd + 2);
        if (r > 0 && r > (fnd + 2)) {
            txt = parseText->func(fnd, r, txt);
            QTextCursor str = ui->plainTextEdit->textCursor();
            ui->plainTextEdit->setPlainText(txt);
            ui->plainTextEdit->setTextCursor(str);
        }
    }
}
