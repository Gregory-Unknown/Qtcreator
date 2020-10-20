#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mdiArea = new QMdiArea(this);
    QWidget *wgt = new QWidget(this);
    setCentralWidget(wgt);
    QGridLayout *layout = new QGridLayout(this);
    wgt->setLayout(layout);
    layout->addWidget(mdiArea, 1, 0, 10, 5);
    mdiArea->addSubWindow(ui->plainTextEdit);
    mdiArea->cascadeSubWindows();

    QMenu *fileMenu = menuBar()->addMenu(tr("File"));

    QAction *newAct = fileMenu->addAction(tr("New"));
    connect(newAct, SIGNAL(triggered(bool)), this, SLOT(on_new_Button_clicked()));

    QAction *openAct = fileMenu->addAction(tr("Open"));
    connect(openAct, SIGNAL(triggered(bool)), this, SLOT(on_open_Button_clicked()));

    QAction *readAct = fileMenu->addAction(tr("Read"));
    connect(readAct, SIGNAL(triggered(bool)), this, SLOT(on_read_Button_clicked()));

    QAction *saveAct = fileMenu->addAction(tr("Save"));
    connect(saveAct, SIGNAL(triggered(bool)), this, SLOT(on_save_Button_clicked()));

    QAction *helpAct = fileMenu->addAction(tr("Help"));
    connect(helpAct, SIGNAL(triggered(bool)), this, SLOT(on_help_Button_clicked()));

    fileMenu->addSeparator();

    QAction *printAct = fileMenu->addAction(tr("Print"));
    connect(printAct, SIGNAL(triggered(bool)), this, SLOT(on_print_Button_clicked()));

    fileMenu->addSeparator();

    QAction *closeAct = fileMenu->addAction(tr("Exit"));
    connect(closeAct, SIGNAL(triggered(bool)), this, SLOT(close()));

    QMenu* fileMenu2 = menuBar()->addMenu(tr("theme"));

    QAction* themeAct = fileMenu2->addAction(tr("Dark"));
    connect(themeAct, SIGNAL(triggered(bool)), this, SLOT(darkTheme()));

    QAction* themeAct2 = fileMenu2->addAction(tr("Light"));
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
    ui->retranslateUi(this);
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

void MainWindow::on_print_Button_clicked()
{
    QMdiSubWindow* activSubWindow = mdiArea->activeSubWindow();
        QWidget* wdg = activSubWindow->widget();
        QPlainTextEdit* plainTextEdit = (QPlainTextEdit*)wdg;
        QPrinter printer;
        QPrintDialog dlg(&printer, this);
        if(dlg.exec() == QDialog::Accepted) {
            plainTextEdit->print(&printer);
        }
}

void MainWindow::on_new_Button_clicked()
{
    QPlainTextEdit* plainTextEdit = new QPlainTextEdit(this);
    mdiArea->addSubWindow(plainTextEdit);
    plainTextEdit->setWindowTitle(tr("New"));
    plainTextEdit->show();
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
    if (static_cast<QPushButton*>(obj) == ru_RU) switchLanguage("ru");
    if (static_cast<QPushButton*>(obj) == en_EN) switchLanguage("en");
}

