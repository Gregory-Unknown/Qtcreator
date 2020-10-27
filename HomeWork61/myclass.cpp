#include "myclass.h"

MyClass::MyClass(QObject *parent, int g) : QObject(parent), QGraphicsItem()
{
    x = 0;
    y = 0;
    brush.setColor(QColor(rand() % 256, rand() % 256, rand() % 256));
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    geometry = (Geometry)g;
    setPos(0, 0);
    moving = false;
    rotate = false;
    setFlag(QGraphicsItem::ItemIsMovable, true);
}

void MyClass::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(brush);
    if (geometry == Geometry::RECTANGLE) painter->drawRect(x, y, 200,100);
    if (geometry == Geometry::ELLIPSE) painter->drawEllipse(x, y, 200, 100);
    if (geometry == Geometry::STAR) {
        QPolygon polygon;
        polygon << QPoint(x, y);
        polygon << QPoint(x - 100, y + 200);
        polygon << QPoint(x + 125, y + 80);
        polygon << QPoint(x - 125, y + 80);
        polygon << QPoint(x + 100, y + 200);
        painter->drawPolygon(polygon);
    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF MyClass::boundingRect() const
{
    if (geometry == Geometry::ELLIPSE || geometry == Geometry::RECTANGLE)
        return QRectF(x, y, 200, 100);
    else
        return QRectF(x, y, 50, 50);
}

void MyClass::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        moving = true;
        bpoint = event->pos().toPoint();
    }
    if (event->button() == Qt::RightButton) {
        this->deleteLater();
        emit reDraw();
    }
    if (event->button() == Qt::MidButton) {
        rotate = true;
    }
}

void MyClass::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        moving = false;
        emit reDraw();
    }
    if (event->button() == Qt::MidButton) {
        rotate = false;
    }
}

void MyClass::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (moving) {
        QPoint p = event->pos().toPoint() - bpoint;
        x += p.x();
        y += p.y();
        bpoint = event->pos().toPoint();
        emit reDraw();
    }
    if (rotate) {
        QPoint p = event->pos().toPoint() - bpoint;
        this->setRotation((-p.x() / 5) - (-p.y() / 5));
        emit reDraw();
    }
}
