#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>
#include <QGraphicsItem>
#include <QContextMenuEvent>
#include <QBrush>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

class MyClass : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QBrush brush)
public:
    explicit MyClass(QObject *parent = nullptr, int g = 0);
    void setBrush(QBrush brush) {
        this->brush = brush;
        emit reDraw();
    }
    int x, y;

signals:
    void reDraw();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    enum Geometry {RECTANGLE, ELLIPSE, STAR};
    Geometry geometry;
    QPoint bpoint;
    bool moving;
    bool rotate;
    QBrush brush;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // MYCLASS_H
