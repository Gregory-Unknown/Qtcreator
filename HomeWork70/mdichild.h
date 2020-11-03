#ifndef MDICHILD_H
#define MDICHILD_H

#include <QTextEdit>
#include <QtGui>
#include <QMessageBox>
#include <QApplication>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QMenu>

class MdiChild : public QTextEdit {
    Q_OBJECT

public:
    MdiChild();

    void newFile();
    bool openFile(const QString & fileName);
    bool save();
    bool saveAs();
    bool saveFile(const QString & fileName);

    void printFile();

    void selectText();
    void cutText();
    void copyText();
    void pasteText();

    void translate();

    QString getCurrentFile();
    QString userFriendlyCurrentFile();

protected:
    void contextMenuEvent(QContextMenuEvent *e) override;

private:
    QString currentFile;
    bool isUntitled;
    void setCurrentFile(const QString & fileName);
    QString strippedName(const QString & fullFileName);
    QMenu *menu;
    QAction *selectAction;
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *dateInsAct;
    QAction *timeInsAct;
    QAction *readOnlyAction;
    bool language;

private slots:
    void documentWasModified();
    void readingModeSelection();

};

#endif // MDICHILD_H
