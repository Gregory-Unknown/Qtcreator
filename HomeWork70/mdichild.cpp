#include "mdichild.h"

MdiChild::MdiChild() {
    setAttribute(Qt::WA_DeleteOnClose);
    isUntitled = true;

    /* Контекстное меню ======================================================================================================== */

    menu = new QMenu(this);
    selectAction = menu->addAction(tr("Select"), this, SLOT(selectAll()));
    cutAction = menu->addAction(tr("Cut"), this, SLOT(cut()));
    copyAction = menu->addAction(tr("Copy"), this, SLOT(copy()));
    pasteAction = menu->addAction(tr("Paste"), this, SLOT(paste()));
    dateInsAct = menu->addAction(tr("Date"), this, SLOT(dateIns()));
    timeInsAct = menu->addAction(tr("Time"), this, SLOT(timeIns()));
    readOnlyAction = menu->addAction(tr("Read Only"), this, SLOT(readingModeSelection()));
    readOnlyAction->setCheckable(true);
    readOnlyAction->setChecked(false);
}

/* Новый файл ================================================================================================================== */

void MdiChild::newFile() {
    static int sequence = 1;
    isUntitled = true;
    currentFile = tr("document%1.txt").arg(sequence++);
    setWindowTitle(currentFile);
    connect(document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));
}

/* Открыть файл ================================================================================================================ */

bool MdiChild::openFile(const QString & fileName) {
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot read file %1:\n%2.").arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream textStream(& file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    setPlainText(textStream.readAll());
    QApplication::restoreOverrideCursor();
    setCurrentFile(fileName);
    connect(document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));
    return true;
}

/* Сохранить файл ============================================================================================================== */

bool MdiChild::save() {
    if (isUntitled) return saveAs();
    else return saveFile(currentFile);
}

bool MdiChild::saveAs() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), currentFile);
    if (fileName.isEmpty()) return false;
}

bool MdiChild::saveFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot write file %1:\n%2.").arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream textStream(& file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    textStream << toPlainText();
    QApplication::restoreOverrideCursor();
    setCurrentFile(fileName);
    return true;
 }

/* Напечатать файл ============================================================================================================= */

void MdiChild::printFile() {
    QPrinter printer;
    QPrintDialog printDialog(& printer, this);
    printDialog.setWindowTitle(tr("Printer"));
    if (printDialog.exec() == QDialog::Accepted) {
        this->print(& printer);
    }
}

/* Инструменты ================================================================================================================= */

void MdiChild::selectText() {
    this->selectAll();
}

void MdiChild::cutText() {
    this->cut();
}

void MdiChild::copyText() {
    this->copy();
}

void MdiChild::pasteText() {
    this->paste();
}

/* Переключение режима «Только для чтения» ===================================================================================== */

void MdiChild::readingModeSelection() {
    if (this->isReadOnly()) {
        this->setReadOnly(false);
    } else {
        this->setReadOnly(true);
    }
}

/* Переключение языка ========================================================================================================== */

void MdiChild::translate() {
    this->repaint();
    selectAction->setText(tr("Select"));
    cutAction->setText(tr("Cut"));
    copyAction->setText(tr("Copy"));
    pasteAction->setText(tr("Paste"));
    dateInsAct->setText(tr("Date"));
    timeInsAct->setText(tr("Time"));
    readOnlyAction->setText(tr("Read Only"));
}

/* Другие ====================================================================================================================== */

QString MdiChild::userFriendlyCurrentFile() {
    return strippedName(currentFile);
}

QString MdiChild::strippedName(const QString & fullFileName) {
    return QFileInfo(fullFileName).fileName();
}

QString MdiChild::getCurrentFile() {
    return currentFile;
}

void MdiChild::setCurrentFile(const QString & fileName) {
    currentFile = QFileInfo(fileName).canonicalFilePath();
    isUntitled = false;
    document()->setModified(false);
    setWindowModified(false);
    setWindowTitle(userFriendlyCurrentFile());
}

void MdiChild::documentWasModified(){
    setWindowModified(document()->isModified());
}

void MdiChild::contextMenuEvent(QContextMenuEvent *e) {
    translate();
    menu->exec(e->globalPos());
}
