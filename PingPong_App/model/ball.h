#ifndef BALL_H
#define BALL_H

#include "paddle.h"

#include <QPoint>

class Game;

class Ball
{
private:
    Game *game;
    QPointF position;
    QPointF velocity;
    double speed;

public:

    Ball(Game *game);

    void move(double dt);

    QPointF getPosition() const;
    void setPosition(const QPoint &value);

    void randomVelocity(double angle);
private:
    double getAngle();
    Paddle *findPaddle(int possitionX);

};

#endif // BALL_H