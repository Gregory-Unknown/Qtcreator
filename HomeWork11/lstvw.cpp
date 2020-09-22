#include "lstvw.h"

lstVw::lstVw(QStandardItemModel *model)
{
    QStandardItem* item;
    item = new QStandardItem(QIcon("./Icons/C++.png"), "C++");
    item->setFlags(item->flags() ^ (Qt::ItemIsDropEnabled));
    model->appendRow(item);

    item = new QStandardItem(QIcon("./Icons/Java.png"), "Java");
    item->setFlags(item->flags() ^ (Qt::ItemIsDropEnabled));
    model->appendRow(item);

    item = new QStandardItem(QIcon("./Icons/Python.png"), "Python");
    item->setFlags(item->flags() ^ (Qt::ItemIsDropEnabled));
    model->appendRow(item);

    item = new QStandardItem(QIcon("./Icons/JavaScript.png"), "JavaScript");
    item->setFlags(item->flags() ^ (Qt::ItemIsDropEnabled));
    model->appendRow(item);

    item = new QStandardItem(QIcon("./Icons/C#.png"), "C#");
    item->setFlags(item->flags() ^ (Qt::ItemIsDropEnabled));
    model->appendRow(item);

    item = new QStandardItem(QIcon("./Icons/PHP.png"), "PHP");
    item->setFlags(item->flags() ^ (Qt::ItemIsDropEnabled));
    model->appendRow(item);
}
