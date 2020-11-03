#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QGridLayout>
#include <QTextEdit>
#include <QMenu>
#include <QMenuBar>
#include <QContextMenuEvent>
#include <QToolBar>
#include <QAction>
#include <QFile>
#include <QFileDialog>
#include <QTranslator>
#include <QApplication>
#include <QEvent>
#include <QInputDialog>
#include "mdichild.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget * parent = nullptr);
    ~MainWindow();

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void printFile();

    void sendSelectText();
    void sendCutText();
    void sendCopyText();
    void sendPasteText();

    void switchToLightTheme();
    void switchToDarkTheme();
    void switchToEnglishLanguage();
    void switchToRussianLanguage();

    MdiChild * createMdiChild();

    void timeIns();
    void dateIns();
protected:
    void changeEvent(QEvent *event) override;

private:
    QMdiArea *mdiArea;
    QWidget *widget;
    QGridLayout *gridLayout;

    QMenu *fileMenu;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *printAction;

    QMenu *editMenu;
    QAction *selectAction;
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *dateInsAct;
    QAction *timeInsAct;

    QMenu *windowMenu;

    QMenu *themeMenu;
    QAction *lightTheme;
    QAction *darkTheme;
    bool theme;

    QMenu *languageMenu;
    QAction *englishLanguage;
    QAction *russianLanguage;
    bool language;

    QToolBar *toolBar;
    QAction *selectAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;

    QMdiSubWindow *findMdiChild(const QString &fileName);

    void setDefaultTheme();
    void setDefaultLanguage();
    void setDefaultFile();
    void setDefaultText();

    QTranslator translator;

};

#endif // MAINWINDOW_H
