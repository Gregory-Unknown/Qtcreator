#ifndef SAVING_HPP
#define SAVING_HPP

#include <QObject>
#include <QStringList>
#include <QArrayData>
#include <QVariant>

class Saving : public QObject
{
    Q_OBJECT
public:
    explicit Saving(QObject *parent = nullptr);

    Q_INVOKABLE void saveTask(QString id, QString name, QString date, int progress);

public slots:
    Q_INVOKABLE int cppMethod() { int task = tasks; return task;};

private:
    QStringList list;
    void writeToFile();
    int tasks = 1;

};

#endif // SAVING_HPP
