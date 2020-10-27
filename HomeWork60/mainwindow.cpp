#include "mainwindow.h"

#include <QFont>
#include <QFontDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Text Edit"));
    mdiArea = new QMdiArea(this);
    QWidget *wgt = new QWidget(this);
    setCentralWidget(wgt);
    QGridLayout *layout = new QGridLayout(this);
    wgt->setLayout(layout);
    layout->addWidget(mdiArea, 1, 0, 10, 5);
    comboBox = new QComboBox(this);
    comboBox->addItems(QStringList() << "en_US" << "ru_RU" );
    connect(comboBox, static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            [=](const QString &str){
           Translator.load("://QtLanguage_" + str, ".");
           qApp->installTranslator(&Translator);
    });
    Translator.load(QString("://QtLanguage_") + QString("ru_RU"));
    qApp->installTranslator(&Translator);
    layout->addWidget(comboBox, 0, 1, 1, 1);

    plainTextEdit = new QPlainTextEdit(this);
    mdiArea->addSubWindow(plainTextEdit);
    mdiArea->cascadeSubWindows();

    fileMenu = menuBar()->addMenu(tr("File"));

    newAct = fileMenu->addAction(tr("New"));
    connect(newAct, SIGNAL(triggered(bool)), this, SLOT(on_new_Button_clicked()));

    openAct = fileMenu->addAction(tr("Open"));
    connect(openAct, SIGNAL(triggered(bool)), this, SLOT(on_open_Button_clicked()));

    readAct = fileMenu->addAction(tr("Read"));
    connect(readAct, SIGNAL(triggered(bool)), this, SLOT(on_read_Button_clicked()));

    saveAct = fileMenu->addAction(tr("Save"));
    connect(saveAct, SIGNAL(triggered(bool)), this, SLOT(on_save_Button_clicked()));

    helpAct = fileMenu->addAction(tr("Help"));
    connect(helpAct, SIGNAL(triggered(bool)), this, SLOT(on_help_Button_clicked()));

    fileMenu->addSeparator();

    printAct = fileMenu->addAction(tr("Print"));
    connect(printAct, SIGNAL(triggered(bool)), this, SLOT(on_print_Button_clicked()));

    fileMenu->addSeparator();

    closeAct = fileMenu->addAction(tr("Exit"));
    connect(closeAct, SIGNAL(triggered(bool)), this, SLOT(close()));

    fileMenu2 = menuBar()->addMenu(tr("theme"));

    themeAct = fileMenu2->addAction(tr("Dark"));
    connect(themeAct, SIGNAL(triggered(bool)), this, SLOT(darkTheme()));

    themeAct2 = fileMenu2->addAction(tr("Light"));
    connect(themeAct2, SIGNAL(triggered(bool)), this, SLOT(lightTheme()));

    fileMenu3 = menuBar()->addMenu(tr("Font"));

    setFontAct = fileMenu3->addAction(tr("Change"));
    connect(setFontAct, SIGNAL(triggered()), this , SLOT(setFont()));

    copyFormatAct = fileMenu3->addAction(tr("Copy format"));
    connect(copyFormatAct, SIGNAL(triggered()), this , SLOT(copyFormat()));

    pasteFormatAct = fileMenu3->addAction(tr("Paste format"));
    connect(pasteFormatAct, SIGNAL(triggered()), this , SLOT(pasteFormat()));
}

MainWindow::~MainWindow()
{

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
        plainTextEdit->setPlainText(byteArray.data());
    }
}

void MainWindow::on_read_Button_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Read"), QDir::currentPath(), "Text(*.txt)");
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray byteArray = file.readAll();
        plainTextEdit->setReadOnly(file.isOpen());
        plainTextEdit->setPlainText(byteArray.data());
    }
}

void MainWindow::on_save_Button_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save"), QDir::currentPath(), "Text(*.txt)");
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QString str = plainTextEdit->toPlainText();
        QByteArray byteArray = str.toUtf8();
        file.write(byteArray, byteArray.length());
    }
}

void MainWindow::on_help_Button_clicked()
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    QFile file (":/new/prefix1/help.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray byteArray = file.readAll();
    msgBox.setText(tr(byteArray.data()));
    msgBox.exec();
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

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        setWindowTitle(tr("Текстовый редактор"));
        plainTextEdit->setWindowTitle(tr("Неизвестный"));
        fileMenu->setTitle(tr("Файл"));
        newAct->setText(tr("Новый"));
        openAct->setText(tr("Открть"));
        saveAct->setText(tr("Сохранить"));
        printAct->setText(tr("Печать"));
        helpAct->setText(tr("Помощь"));
        closeAct->setText(tr("Выход"));
        fileMenu2->setTitle(tr("Тема"));
        themeAct->setText(tr("Тёмная"));
        themeAct2->setText(tr("Светлая"));
        fileMenu3->setTitle(tr("Шрифт"));
        setFontAct->setText(tr("Изменение"));
        copyFormatAct->setText(tr("Копировать формат"));
        pasteFormatAct->setText(tr("Вставить формат"));

//        setWindowTitle(tr("Text Edit"));
//        plainTextEdit->setWindowTitle(tr("Unknown"));
//        fileMenu->setTitle(tr("File"));
//        newAct->setText(tr("New"));
//        openAct->setText(tr("Open"));
//        saveAct->setText(tr("Save"));
//        printAct->setText(tr("Print"));
//        helpAct->setText(tr("Help"));
//        closeAct->setText(tr("Exit"));
//        fileMenu2->setTitle(tr("theme"));
//        themeAct->setText(tr("Dark"));
//        themeAct2->setText(tr("Light"));
//        fileMenu3->setTitle(tr("Font"));
//        setFontAct->setText(tr("Change"));
//        copyFormatAct->setText(tr("Copy format"));
//        pasteFormatAct->setText(tr("Paste format"));

    }

}

void MainWindow::setFont()
{
    QFont font = plainTextEdit->textCursor().charFormat().font();
    QFontDialog fntDlg(font, this);
    bool ok;
    font = fntDlg.getFont(&ok);
    if (ok) {
        QTextCharFormat fmt;
        fmt.setFont(font);
        plainTextEdit->textCursor().setCharFormat(fmt);
    }
}

void MainWindow::copyFormat()
{
    QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow();
    QWidget *wgt = activeSubWindow->widget();
    QTextEdit* te = (QTextEdit*)wgt;
    format = te->textCursor().charFormat();
}

void MainWindow::pasteFormat()
{
    QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow();
    QWidget *wgt = activeSubWindow->widget();
    QTextEdit* te = (QTextEdit*)wgt;
    te->textCursor().setCharFormat(format);
}
