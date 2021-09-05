#include "gui_ball.h"
#include <QDebug>

Gui_ball::Gui_ball(Ball *ball, QPointF translation, QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    this->ball = ball;
    this->setPos(this->ball->getPosition());
    QPixmap *pic = new QPixmap(":/new/pics/ball.png");
    this->setPixmap(pic->scaled(ball->getSize(),ball->getSize(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

    this->translationFromGlobal = translation;

}

void Gui_ball::updatePosition()
{
    //this->setPos(this->ball->getPosition());
    QPointF pos = this->ball->getPosition();
    pos.rx() -= pixmap().width()/2;
    pos.ry() -= pixmap().height()/2;
    pos += translationFromGlobal;
    this->setPos(pos);
}
