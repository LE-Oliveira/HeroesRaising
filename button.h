#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QString>

class Button: public QObject, public QGraphicsRectItem{
  Q_OBJECT
public:
  Button(QString type, QString name, QPoint ponto, QPoint init, QPoint end, QColor color, bool b, QGraphicsItem* parent = nullptr);
  void setColor(QColor q);
  void setname(QString texto);
  void mousePressEvent(QGraphicsSceneMouseEvent *event);
  void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
  void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
  QGraphicsTextItem *text;

signals:
  void clicked();

private:
  QString type;
};

#endif // BUTTON_H
