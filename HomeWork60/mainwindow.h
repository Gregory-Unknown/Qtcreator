#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QPushButton>
#include <QKeyEvent>
#include <QTranslator>
#include <QMenu>
#include <QMenuBar>
#include <QComboBox>
#include <QLabel>
#include <QApplication>
#include <QMdiArea>
#include <QGridLayout>
#include <QPrinter>
#include <QPrintDialog>
#include <QMdiSubWindow>
#include <QPlainTextEdit>
#include <QMessageBox>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyReleaseEvent(QKeyEvent* event) override;
    void changeEvent(QEvent * event) override;

private slots:

    void on_open_Button_clicked();
    void on_save_Button_clicked();
    void on_help_Button_clicked();
    void on_read_Button_clicked();
    void on_print_Button_clicked();
    void on_new_Button_clicked();
    void darkTheme();
    void lightTheme();
    void setFont();
    void copyFormat();
    void pasteFormat();

private:
    QMdiArea *mdiArea;
    QPlainTextEdit *plainTextEdit;
    QTextCharFormat format;
    QComboBox *comboBox;
    QTranslator Translator;

    QMenu *fileMenu;
    QAction *newAct;
    QAction *openAct;
    QAction *readAct;
    QAction *saveAct;
    QAction *helpAct;
    QAction *printAct;
    QAction *closeAct;

    QMenu *fileMenu2;
    QAction *themeAct;
    QAction *themeAct2;

    QMenu *fileMenu3;
    QAction *setFontAct;
    QAction *copyFormatAct;
    QAction *pasteFormatAct;
};
#endif // MAINWINDOW_H
