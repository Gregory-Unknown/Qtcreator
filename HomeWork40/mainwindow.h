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

private slots:

    void on_open_Button_clicked();
    void on_save_Button_clicked();
    void on_help_Button_clicked();
    void on_read_Button_clicked();
    void on_print_Button_clicked();
    void on_new_Button_clicked();
    void darkTheme();
    void lightTheme();
    void clickSwitch();

private:
    Ui::MainWindow *ui;
    QPushButton *ru_RU, *en_EN;
    QTranslator translater;
    void switchLanguage(QString language);
    QMdiArea *mdiArea;
};
#endif // MAINWINDOW_H

