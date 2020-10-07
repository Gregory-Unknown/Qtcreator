#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QPushButton>
#include <QKeyEvent>

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
