#ifndef CGRAPHICSSECENE_H
#define CGRAPHICSSECENE_H

#include <QGraphicsScene>
#include <QWidget>
#include <QGraphicsSceneMouseEvent>


class CGraphicsSecene : public QGraphicsScene
{

    Q_OBJECT

public:
    explicit CGraphicsSecene(QObject *parent = nullptr);
    ~CGraphicsSecene();

private:

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;


signals:
    void clickedOnField(QPointF);
//    void resizeGraphicsScene(void);

};

#endif // CGRAPHICSSECENE_H
