#ifndef BASEBOX_HH
#define BASEBOX_HH

#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>

#include "hex.hh"
#include "basepawn.hh"
//#include <vector>
//#include "cubecoordinate.hh"
//#include "gamescene.hh"

enum colorCode {
    Coral,
    Water,
    Beach,
    Forest,
    Mountain,
    Peak
};

struct column_row {
    int q;
    int r;
};

struct offsetCoordinates {
    int x;
    int y;
};

class basebox : public QGraphicsPolygonItem {
public:
    // constructors
    basebox();
    void setColor(int id);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    std::string getString(colorCode color);

    int numberOfPawns;

    void placePawn(int id);
    bool placePawn(basepawn *pawn);
    void placePawnSupport(basepawn *pawn, int pawnNumber);

    void resetPawns();

    Common::CubeCoordinate cubeCoordinates;
    column_row col_row;
    offsetCoordinates OffCoordinates;

    QList<basepawn *> pawns;

    Common::Hex *hex;
    colorCode color;

    int xShift = 20;
    int yShift = 10;

};

#endif // BASEBOX_HH
