#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    translator.load(":/language/QtLanguage_ru.qm");
    qApp->installTranslator(&translator);
    setWindowTitle(tr("Homework"));

    //
    // Добавить в текстовый редактор поддержку многодокументного интерфейса.
    //

    mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setViewMode(QMdiArea::TabbedView);
    mdiArea->setTabsMovable(true);
    mdiArea->setTabsClosable(true);
    mdiArea->setDocumentMode(true);
    setCentralWidget(mdiArea);

    //
    // Добавить меню в текстовый редактор.
    //

    QMenuBar * menuBar = this->menuBar();

    fileMenu = menuBar->addMenu(tr("File"));
    newAction = fileMenu->addAction(tr("New"), this, SLOT(newFile()));
    openAction = fileMenu->addAction(tr("Open"), this, SLOT(openFile()));
    fileMenu->addSeparator();
    saveAction = fileMenu->addAction(tr("Save"), this, SLOT(saveFile()));
    fileMenu->addSeparator();


    //
    // Добавить в текстовый редактор кнопку для вывода на печать.
    //

    printAction = fileMenu->addAction(tr("Print"), this, SLOT(printFile()));

    /* Меню правки ============================================================================================================= */

    editMenu = menuBar->addMenu(tr("Edit"));
    selectAction = editMenu->addAction(tr("Select"), this, SLOT(sendSelectText()));
    cutAction = editMenu->addAction(tr("Cut"), this, SLOT(sendCutText()));
    copyAction = editMenu->addAction(tr("Copy"), this, SLOT(sendCopyText()));
    pasteAction = editMenu->addAction(tr("Paste"), this, SLOT(sendPasteText()));
    dateInsAct = editMenu->addAction(tr("Date"), this, SLOT(dateIns()));
    timeInsAct = editMenu->addAction(tr("Time"), this, SLOT(timeIns()));


    /* Меню настройки окна ===================================================================================================== */
    theme = true;
    setDefaultTheme();
    windowMenu = menuBar->addMenu(tr("Window"));
    themeMenu = windowMenu->addMenu(tr("Theme"));
    lightTheme = themeMenu->addAction(tr("Light"), this, SLOT(switchToLightTheme()));
    lightTheme->setCheckable(true);
    lightTheme->setChecked(true);
    darkTheme = themeMenu->addAction(tr("Dark"), this, SLOT(switchToDarkTheme()));
    darkTheme->setCheckable(true);
    darkTheme->setChecked(false);

    language = false;
    languageMenu = windowMenu->addMenu(tr("Language"));
    englishLanguage = languageMenu->addAction(tr("English"), this, SLOT(switchToEnglishLanguage()));
    englishLanguage->setCheckable(true);
    englishLanguage->setChecked(false);
    russianLanguage = languageMenu->addAction(tr("Russian"), this, SLOT(switchToRussianLanguage()));
    russianLanguage->setCheckable(true);
    russianLanguage->setChecked(true);

    /* Панель инструментов ===================================================================================================== */

//    toolBar = addToolBar(tr("Tool bar"));
//    toolBar->setMovable(false);
//    selectAct = toolBar->addAction(tr("Select"), this, SLOT(sendSelectText()));
//    cutAct = toolBar->addAction(tr("Cut"), this, SLOT(sendCutText()));
//    copyAct = toolBar->addAction(tr("Copy"), this, SLOT(sendCopyText()));
//    pasteAct = toolBar->addAction(tr("Paste"), this, SLOT(sendPasteText()));

    newFile();
    setDefaultFile();
}

MainWindow::~MainWindow() {

}

/* Файл по-умолчанию =========================================================================================================== */

void MainWindow::setDefaultFile() {
    MdiChild * mdiChild = createMdiChild();
    mdiChild->openFile(":/info/reference.txt");
    mdiChild->showMaximized();
}

/* Новый файл ================================================================================================================== */

void MainWindow::newFile() {
     MdiChild * mdiChild = createMdiChild();
     mdiChild->newFile();
     mdiChild->show();
}

MdiChild * MainWindow::createMdiChild() {
    MdiChild * mdiChild = new MdiChild;
    mdiArea->addSubWindow(mdiChild);
    return mdiChild;
}

/* Открыть файл ================================================================================================================ */

void MainWindow::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) {
        QMdiSubWindow * mdiSubWindow = findMdiChild(fileName);
        if (mdiSubWindow) {
            mdiArea->setActiveSubWindow(mdiSubWindow);
            return;
        }
        MdiChild * mdiChild = createMdiChild();
        if (mdiChild->openFile(fileName)) {
            mdiChild->show();
        } else {
            mdiChild->close();
        }
    }
}

QMdiSubWindow * MainWindow::findMdiChild(const QString & fileName) {
    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();
    foreach (QMdiSubWindow * mdiSubWindow, mdiArea->subWindowList()) {
        MdiChild * mdiChild = qobject_cast<MdiChild *>(mdiSubWindow->widget());
        if (mdiChild->getCurrentFile() == canonicalFilePath) return mdiSubWindow;
    }
    return 0;
}



/* Сохранить файл ================================================================================================================ */

void MainWindow::saveFile() {
     QMdiSubWindow * activeSubWindow = mdiArea->activeSubWindow();
     if (activeSubWindow == nullptr) {
         QMessageBox::warning(this, tr("Error"), tr("No file to save!"));
         return;
     }
     QWidget * wgt = activeSubWindow->widget();
     MdiChild * mdiChild = (MdiChild *)wgt;
     mdiChild->saveAs();
}

/* Напечатать файл ============================================================================================================= */

void MainWindow::printFile() {
    QMdiSubWindow * activeSubWindow = mdiArea->activeSubWindow();
    if (activeSubWindow == nullptr) {
        QMessageBox::warning(this, tr("Error"), tr("No file to print!"));
        return;
    }
    QWidget * wgt = activeSubWindow->widget();
    MdiChild * mdiChild = (MdiChild *)wgt;
    mdiChild->printFile();
}

/* Инструменты ================================================================================================================= */

void MainWindow::sendSelectText() {
    QMdiSubWindow * activeSubWindow = mdiArea->activeSubWindow();
    if (activeSubWindow == nullptr) {
        return;
    }
    QWidget * wgt = activeSubWindow->widget();
    MdiChild * mdiChild = (MdiChild *)wgt;
    mdiChild->selectText();
}

void MainWindow::sendCutText() {
    QMdiSubWindow * activeSubWindow = mdiArea->activeSubWindow();
    if (activeSubWindow == nullptr) {
        return;
    }
    QWidget * wgt = activeSubWindow->widget();
    MdiChild * mdiChild = (MdiChild *)wgt;
    mdiChild->cutText();
}

void MainWindow::sendCopyText() {
    QMdiSubWindow * activeSubWindow = mdiArea->activeSubWindow();
    if (activeSubWindow == nullptr) {
        return;
    }
    QWidget * wgt = activeSubWindow->widget();
    MdiChild * mdiChild = (MdiChild *)wgt;
    mdiChild->copyText();
}

void MainWindow::sendPasteText() {
    QMdiSubWindow * activeSubWindow = mdiArea->activeSubWindow();
    if (activeSubWindow == nullptr) {
        return;
    }
    QWidget * wgt = activeSubWindow->widget();
    MdiChild * mdiChild = (MdiChild *)wgt;
    mdiChild->pasteText();
}

void MainWindow::dateIns()
{
    QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow();
    QWidget *wgt = activeSubWindow->widget();
    QTextEdit* te = (QTextEdit*)wgt;
    int day = QInputDialog::getInt(this,"Input","day:",1,1,31,1);
    int month = QInputDialog::getInt(this,"Input","month:",1,1,12,1);
    int year = QInputDialog::getInt(this,"Input","year:",2019,0,3000,1);
    if (day && month && year)
    {
        QDate date;
        date.setDate(year,month,day);
        const QString month[] = {"", " января " , " февраля ", " марта ",
                                      " апреля ", " мая ", " июня ",
                                      " июля ", " августа ", " сентября ",
                                      " октября ", " ноября ", " декабря ",
                                     }; // Месяцы отсчитываются от 1, поэтому первый
                                        // элемент - пустая строка
        QString dstr = QString::number(date.day()) + month[date.month()] + QString::number(date.year());
        QTextCursor cur = te->textCursor();
        cur.insertHtml(dstr);
    }

}

void MainWindow::timeIns()
{
    QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow();
    QWidget *wgt = activeSubWindow->widget();
    QTextEdit* te = (QTextEdit*)wgt;
    int h = QInputDialog::getInt(this,"Input","hours:",0,1,23,1);
    int m = QInputDialog::getInt(this,"Input","minutes:",0,1,59,1);
    int s = QInputDialog::getInt(this,"Input","seconds:",0,1,59,1);
    if (h && m && s)
    {
        QTime time;
        QString zeroS;
        QString zeroM;
        QString zeroH;
        time.setHMS(h,m,s);
        if (time.second() < 10)
            zeroS = '0';
        else
            zeroS = "";
        if (time.minute() < 10)
            zeroM = '0';
        else
            zeroM = "";
        if (time.hour() < 10)
            zeroH = '0';
        else
            zeroH = "";
        QString tstr = zeroH + QString::number(time.hour()) + ':' + zeroM + QString::number(time.minute())
                + ':' + zeroS + QString::number(time.second());
        QTextCursor cur = te->textCursor();
        cur.insertHtml(tstr);
    }

}
/* Переклчюение темы =========================================================================================================== */

void MainWindow::setDefaultTheme() {
    setStyleSheet("QTabBar::tab {font: 12px}"
                  "QTabBar::tab {color: #000000}"
                  "QTabBar::tab {background-color: #DFDFDF}"
                  "QTabBar::tab:hover {background-color: #BDBDBD}"
                  "QTabBar::tab:selected {background-color: #A8A8A8}"
                  "QTextEdit {color: #000000}"
                  "QTextEdit {selection-color: #000000}"
                  "QTextEdit {background-color: #FFFFFF}"
                  "QTextEdit {selection-background-color: #ADD0F7}"
                  "QMainWindow {background-color: #CECECE}");
}

void MainWindow::switchToLightTheme() {
    if (!theme) {
        theme = true;
        setDefaultTheme();
    }
    lightTheme->setChecked(true);
    darkTheme->setChecked(false);
}

void MainWindow::switchToDarkTheme() {
    if (theme) {
        theme = false;
        setStyleSheet("QTabBar::tab {font: 12px}"
                      "QTabBar::tab {color: #8A8A8A}"
                      "QTabBar::tab {background-color: #242424}"
                      "QTabBar::tab:hover {background-color: #101010}"
                      "QTabBar::tab:selected {background-color: #414141}"
                      "QTextEdit {color: #F9F9F9}"
                      "QTextEdit {selection-color: #F9F9F9}"
                      "QTextEdit {background-color: #1E1E1E}"
                      "QTextEdit {selection-background-color: #406188}"
                      "QMainWindow {background-color: #CECECE}");
    }
    darkTheme->setChecked(true);
    lightTheme->setChecked(false);
}

/* Переклчюение языка ========================================================================================================== */

void MainWindow::setDefaultLanguage() {
    qApp->removeTranslator(&translator);
}

void MainWindow::switchToEnglishLanguage() {
    if (!language) {
        language = true;
        translator.load(":/language/QtLanguage_en.qm");
        qApp->installTranslator(&translator);
    }
    englishLanguage->setChecked(true);
    russianLanguage->setChecked(false);
}

void MainWindow::switchToRussianLanguage() {
    if (language) {
        language = false;
        translator.load(":/language/QtLanguage_ru.qm");
        qApp->installTranslator(&translator);
    }
    russianLanguage->setChecked(true);
    englishLanguage->setChecked(false);
}

void MainWindow::setDefaultText() {
    setWindowTitle(tr("Homework"));
    fileMenu->setTitle(tr("File"));
    newAction->setText(tr("New"));
    openAction->setText(tr("Open"));
    saveAction->setText(tr("Save"));
    printAction->setText(tr("Print"));
    editMenu->setTitle(tr("Edit"));
    selectAction->setText(tr("Select"));
    cutAction->setText(tr("Cut"));
    copyAction->setText(tr("Copy"));
    pasteAction->setText(tr("Paste"));
    dateInsAct->setText(tr("Date"));
    timeInsAct->setText(tr("Time"));
    windowMenu->setTitle(tr("Window"));
    themeMenu->setTitle(tr("Theme"));
    lightTheme->setText(tr("Light"));
    darkTheme->setText(tr("Dark"));
    languageMenu->setTitle(tr("Language"));
    englishLanguage->setText(tr("English"));
    russianLanguage->setText(tr("Russian"));
}

void MainWindow::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        setDefaultText();
        mdiArea->repaint();
        this->repaint();
    }
}

