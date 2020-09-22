#ifndef LSTVW_H
#define LSTVW_H

#include <QMainWindow>
#include <QModelIndexList>
#include <QStandardItem>

class lstVw : public QMainWindow
{
    Q_OBJECT
public:
    lstVw(QStandardItemModel *model);

private:

};

#endif // LSTVW_H
