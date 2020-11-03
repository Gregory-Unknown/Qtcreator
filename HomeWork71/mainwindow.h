#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QGridLayout>
#include <QComboBox>
#include <QLabel>
#include "controller.h"
#include "firstmyqtwidget.h"

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   MainWindow(QWidget *parent = 0);
   ~MainWindow();
private:
   FirstMyQtWidget *fmqw;
   QLineEdit *searchEdit;
   QPushButton *startFindButton;
   QTextEdit *infoText;
   QComboBox *selDrive;
   Controller *controllerl;
   QLabel *statusLabel;
private slots:
   void findFileSlot();
   void changStatusLabel(QString);
   void printFindFile(QString);
};

#endif // MAINWINDOW_H
