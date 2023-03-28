#include "cgraphicssecene.h"/*
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>*/



CGraphicsSecene::CGraphicsSecene(QObject *parent)
    : QGraphicsScene{parent}
{

}

CGraphicsSecene::~CGraphicsSecene()
{

}

void CGraphicsSecene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << event->scenePos();
}
void CGraphicsSecene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clickedOnField(event->scenePos());
}


