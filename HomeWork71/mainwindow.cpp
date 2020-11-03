#include "mainwindow.h"
#include <QDir>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
{

   QWidget *centerWidget = new QWidget(this);
   setCentralWidget(centerWidget);
   QGridLayout *layout = new QGridLayout(this);
   centerWidget->setLayout(layout);
   fmqw = new FirstMyQtWidget(this);
   layout->addWidget(fmqw, 0, 0, 1, 2);
   searchEdit = new QLineEdit(this);
   layout->addWidget(searchEdit, 0, 0, 0, 2);
   //****************
   selDrive = new QComboBox(this);
   layout->addWidget(selDrive, 0, 3);
   if (QSysInfo::productType() == "windows") // Для ОС Windows
   {
       QFileInfoList infolist = QDir::drives();
       int amount = infolist.count();
       for (int i = 0; i < amount; i++)
       {
           selDrive->addItem(infolist.at(i).path());
       }

   }
   else {                                    // Для UNIX-подобных систем
       QStringList str = {"/", "/home/", "/mount/", "/opt/"};
       int amount = str.count();
       for (int i = 0; i < amount; i++)
       {
           selDrive->addItem(str.at(i));
       }
   }
   //****************
   startFindButton = new QPushButton(this);
   startFindButton->setText(tr("Find"));
   layout->addWidget(startFindButton, 0, 5);
   connect(startFindButton, SIGNAL(clicked()), this, SLOT(findFileSlot()));
   infoText = new QTextEdit(this);
   layout->addWidget(infoText, 1, 0, 10, 10);
   controllerl = new Controller(this);
   statusLabel = new QLabel(this);
   QStatusBar *statusBar = this->statusBar();
   statusBar->addWidget(statusLabel);
   connect(controllerl, SIGNAL(changFindPath(QString)), this, SLOT(changStatusLabel(QString)));
   connect(controllerl, SIGNAL(genPathOfFile(QString)), this, SLOT(printFindFile(QString)));
   connect(controllerl, SIGNAL((newFind())), infoText, SLOT(clear()));
}

MainWindow::~MainWindow()
{

}
void MainWindow::findFileSlot()
{
   QString linesearch = searchEdit->text();
   if (linesearch.length() == 0) return;
   controllerl->startFind(selDrive->currentText(), linesearch);
}

void MainWindow::changStatusLabel(QString line)
{
   statusLabel->setText(line);
}

void MainWindow::printFindFile(QString str)
{
   infoText->append(str);
}
