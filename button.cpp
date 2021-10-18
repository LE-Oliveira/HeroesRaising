#include <QMediaPlayer>
#include <QGraphicsTextItem>
#include <QEvent>
#include <QFont>

#include "button.h"

Button::Button(QString tipo, QString name, QPoint ponto, QPoint init, QPoint end, QColor color, bool b, QGraphicsItem* parent): QGraphicsRectItem(parent){
    text = new QGraphicsTextItem(name, this);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    setRect(init.x(), init.y(), end.x(), end.y());
    brush.setColor(color);
    setAcceptHoverEvents(b);
    type = tipo;
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    if(tipo == "intro") text->setPos(xPos-30, yPos-8);
    else text->setPos(xPos, yPos);
    setPos(ponto.x(), ponto.y());
    setBrush(brush);
}

void Button::setname(QString texto){
    text = new QGraphicsTextItem(texto, this);
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos, yPos);
}

void Button::setColor(QColor q){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(q);
    setBrush(brush);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    if(type == "start"||type == "confirm") brush.setColor(Qt::darkGreen);
    else if(type == "build") brush.setColor(Qt::gray);
    else if(type == "menu"){
        if(this->brush().color() == Qt::red) brush.setColor(Qt::darkRed);
        else if(this->brush().color() == Qt::green) brush.setColor(Qt::darkGreen);
        else if(this->brush().color() == Qt::yellow) brush.setColor(Qt::darkYellow);
        else if(this->brush().color() == Qt::gray) brush.setColor(Qt::darkGray);
        else if(this->brush().color() == Qt::white) brush.setColor(Qt::lightGray);
        else if(this->brush().color() == Qt::cyan) brush.setColor(Qt::darkCyan);
        else if(this->brush().color() == Qt::darkGray) brush.setColor(Qt::black);
    }
    else if(type == "choice") brush.setColor(Qt::darkYellow);
    else if(type == "inventory") brush.setColor(Qt::gray);
    else if(type == "shop"){
        if(this->brush().color() == Qt::cyan) brush.setColor(Qt::darkCyan);
        else brush.setColor(Qt::darkYellow);
    }
    setBrush(brush);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    if(type == "start"||type == "confirm") brush.setColor(Qt::green);
    else if(type == "build") brush.setColor(Qt::lightGray);
    else if(type == "menu"){
        if(this->brush().color() == Qt::darkRed) brush.setColor(Qt::red);
        else if(this->brush().color() == Qt::darkGreen) brush.setColor(Qt::green);
        else if(this->brush().color() == Qt::darkYellow) brush.setColor(Qt::yellow);
        else if(this->brush().color() == Qt::darkGray) brush.setColor(Qt::gray);
        else if(this->brush().color() == Qt::lightGray) brush.setColor(Qt::white);
        else if(this->brush().color() == Qt::darkCyan) brush.setColor(Qt::cyan);
        else if(this->brush().color() == Qt::black) brush.setColor(Qt::darkGray);
    }
    else if(type == "choice") brush.setColor(Qt::yellow);
    else if(type == "inventory") brush.setColor(Qt::lightGray);
    else if(type == "shop"){
        if(this->brush().color() == Qt::darkCyan) brush.setColor(Qt::cyan);
        else brush.setColor(Qt::yellow);
    }
    setBrush(brush);
}

