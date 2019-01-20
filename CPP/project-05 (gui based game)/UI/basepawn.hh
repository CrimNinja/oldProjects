#ifndef BASEPAWN_HH
#define BASEPAWN_HH

#include <QGraphicsPolygonItem>
//#include <QGraphicsSceneMouseEvent>

class basepawn : public QGraphicsPolygonItem {
public:
    basepawn(int id);

    void colorPawn();

    int playerId;
    int pawnNumber;
};

#endif // BASEPAWN_HH
