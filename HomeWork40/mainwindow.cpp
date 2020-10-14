#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMenu* fileMenu = menuBar()->addMenu(tr("theme"));

    QAction* themeAct = fileMenu->addAction(tr("Dark"));
    connect(themeAct, SIGNAL(triggered(bool)), this, SLOT(darkTheme()));

    QAction* themeAct2 = fileMenu->addAction(tr("Light"));
    connect(themeAct2, SIGNAL(triggered(bool)), this, SLOT(lightTheme()));

    ru_RU = new QPushButton(this);
    bool rez = (ru_RU != NULL);
    en_EN = new QPushButton(this);
    rez &= (en_EN != NULL);

    if (!rez) {
        qApp->quit();
        return;
    }

    ru_RU->move(100, 0);
    en_EN->move(400, 0);

    ru_RU->resize(200, 30);
    en_EN->resize(200, 30);

    switchLanguage(QLocale::system().name());
    connect(ru_RU, SIGNAL(clicked()), this, SLOT(clickSwitch()));
    connect(en_EN, SIGNAL(clicked()), this, SLOT(clickSwitch()));
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

void MainWindow::darkTheme()
{
    setStyleSheet("QPlainTextEdit { background-color: Grey}"
                  "QPushButton {background-color: Grey}");
}

void MainWindow::lightTheme()
{
    setStyleSheet("QPlainTextEdit { background-color: Snow}"
                  "QPushButton {background-color: Snow}");
}

void MainWindow::switchLanguage(QString language)
{
    translater.load("switchlang_" + language + ".qm");
    qApp->installTranslator(&translater);
    QString str = tr("Switch language on ");
    ru_RU->setText(str + "Русский");
    en_EN->setText(str + "English");
}

void MainWindow::clickSwitch()
{
    QObject *obj = sender();
    if (obj == ru_RU) switchLanguage("ru");
    if (obj == en_EN) switchLanguage("en");
}

