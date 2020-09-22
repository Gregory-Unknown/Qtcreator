#ifndef PARSETEXT_H
#define PARSETEXT_H

#include <QMainWindow>
#include <QTextCursor>

class ParseText : public QMainWindow
{
    Q_OBJECT;
public:
    ParseText();
    QString func(qint32 fnd, int r, QString str);
    QString func(QString str);
private:
    QString txt;
    QString str;
};

#endif // PARSETEXT_H
