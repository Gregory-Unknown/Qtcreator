#include "saving.hpp"
#include <QFile>
#include <QTextStream>

Saving::Saving(QObject *parent) : QObject(parent)
{
    QFile file("Tasks.txt");
    if (file.open(QIODevice::ReadOnly))
        while(!file.atEnd()) {
            list.append(file.readLine());
            tasks++;
        }
}

void Saving::saveTask(QString id, QString name, QString date, int progress)
{
    id = QString::number(tasks);
    list.insert(tasks, "ID " + id + ", Name task: " + name + ", Date: " + date + ", % " + QString::number(progress) + "\n");
    writeToFile();
    tasks++;
}

void Saving::writeToFile()
{
    QFile file("Tasks.txt");
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        for (int i = 0; i < list.count(); i++) {
            stream << list.at(i).toUtf8();
        }

        file.flush();
        file.close();
    }
}
