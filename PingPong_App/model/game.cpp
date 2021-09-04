#include "game.h"

#include <qthread.h>
#include <QDebug>
#include <QKeyEvent>
Game::Game():
    board(0,0,800,600)
{
    board.setRect(0,0,boardSizeX,boardSizeY);
    this->ball = new Ball(this);
    this->padles = new QList<Paddle *>();
    this->padles->append(new Paddle(this, QPointF(0,board.height()/2), board.height()/8));
    this->padles->append(new Paddle(this, QPointF(board.width()-1,board.height()/2), board.height()/8));
    connect(&server,SIGNAL(messageToInterprete(QString)),this,SLOT(interpreteMessage(QString)),Qt::QueuedConnection);
    startServer();
}

void Game::startGame()
{
    board.setRect(0,0,boardSizeX,boardSizeY);
    this->getPadle(0)->setSize(board.height()/8);
    this->getPadle(0)->setPosition(QPoint(0, board.height()/2));
    this->getPadle(1)->setSize(board.height()/8);
    this->getPadle(1)->setPosition(QPoint(board.width()-1,board.height()/2));
    this->start();

}

void Game::stopGame()
{
    mutex.lock();
    this->isLive = false;
    mutex.unlock();
}

void Game::startServer()
{
    server.startServer(port);
}

void Game::stopServer()
{
    server;
}

void Game::prepareGame()
{
    this->score.first = 0;
    this->score.second = 0;
    this->ball->setPosition(this->board.center());
    this->ball->randomVelocity(45);
}

void Game::run()
{
    this->isLive = true;
    auto lastTime = std::chrono::high_resolution_clock::now();
    this->prepareGame();
    while (true) {
        auto dt = std::chrono::high_resolution_clock::now() - lastTime;
        lastTime = std::chrono::high_resolution_clock::now();
        long double dtns = ((long double)std::chrono::duration_cast<std::chrono::nanoseconds>(dt).count())/1000000000;   //time in s
        makeMoves(dtns);
        emit updateGui();

        mutex.lock();
        if(!isLive)break;
        mutex.unlock();
    }
}


void Game::makeMoves(long double dt)
{
    this->ball->move(dt);
    for(int i=0;i<this->padles->size();i++){
        (*this->padles)[i]->move(dt);
    }
}

QRect Game::getBoard() const
{
    return board;
}

QList<Paddle *> *Game::getPadles() const
{
    return padles;
}
Paddle *Game:: getPadle(int i) const
{
    return (*this->padles)[i];
}

Ball *Game::getBall() const
{
    return ball;
}

void Game::setBoardSizeX(int value)
{
    boardSizeX = value;
}

void Game::setBoardSizeY(int value)
{
    boardSizeY = value;
}

Game::~Game()
{
    stopServer();
    delete this->ball;
    while (padles->size() != 0) {
        delete this->padles->takeFirst();

    }
    delete this->padles;
}

void Game::interpreteMessage(QString message)
{

}


