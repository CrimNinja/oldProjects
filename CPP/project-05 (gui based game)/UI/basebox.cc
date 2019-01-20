#include "basebox.hh"
#include "gamescene.hh"
#include "gamewindow.hh"

#include <QPointF>
#include <QPolygonF>
#include <QVector>
#include <QBrush>
#include <QMessageBox>
#include "gamescene.hh"
#include "gamewindow.hh"
#include <QtDebug>

extern gamescene* gScene;
extern gameWindow *gWindow;
extern QGraphicsScene *iscene;

basebox::basebox() {

    QVector<QPointF> basePoints;
    basePoints << QPointF(1, 0) << QPointF(2, 0) << QPointF(3, 1)
               << QPointF(2, 2) << QPointF(1, 2) << QPointF(0, 1);

    int scaler = 20;
    for (int i = 0; i < basePoints.size(); ++i) {
        basePoints[i] *= scaler;
    }

    QPolygonF hexagon(basePoints);

    setPolygon(hexagon);

    numberOfPawns = 0;
}

void basebox::setColor(int id) {
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    switch (id) {
    case 1:
        brush.setColor(Qt::cyan);
        break;
    case 2:
        brush.setColor(Qt::yellow);
        break;
    case 3:
        brush.setColor(Qt::green);
        break;
    case 4:
        brush.setColor(Qt::gray);
        break;
    case 5:
        brush.setColor(Qt::darkGray);
        break;
    default:
        brush.setColor(Qt::cyan);
        break;
    }
    setBrush(brush);
}

void basebox::mousePressEvent(QGraphicsSceneMouseEvent *event) {

    gScene->clicked(this);   
}

std::string basebox::getString(colorCode color) {
    std::string out;

    switch (color) {
    case colorCode::Coral:
        out = "Coral";
        break;
    case colorCode::Water:
        out = "Water";
        break;
    case colorCode::Beach:
        out = "Beach";
        break;
    case colorCode::Forest:
        out = "Forest";
        break;
    case colorCode::Mountain:
        out = "Mountain";
        break;
    case colorCode::Peak:
        out = "Peak";
        break;
    default:
        out = "Unknown";
        break;
    }
    return out;
}

void basebox::placePawn(int id) {

    switch (numberOfPawns) {
    case 0: {
        basepawn *pawn = new basepawn(id);
        placePawnSupport(pawn, 1);
        iscene->addItem(pawn);
        pawn->colorPawn();
        pawns.append(pawn);
    }
        break;
    case 1: {
        basepawn *pawn = new basepawn(id);
        placePawnSupport(pawn, 2);
        iscene->addItem(pawn);
        pawn->colorPawn();
        pawns.append(pawn);
    }
        break;
    case 2: {
        basepawn *pawn = new basepawn(id);
        placePawnSupport(pawn, 3);
        iscene->addItem(pawn);
        pawn->colorPawn();
        pawns.append(pawn);
    }
        break;
    case 3: {
        basepawn *pawn = new basepawn(id);
        placePawnSupport(pawn, 4);
        iscene->addItem(pawn);
        pawn->colorPawn();
        pawns.append(pawn);
    }
        break;
    }
    ++numberOfPawns;

}

bool basebox::placePawn(basepawn *pawn) {
    switch (numberOfPawns) {
    case 0: {
        iscene->removeItem(pawn);
        placePawnSupport(pawn, 1);
        iscene->addItem(pawn);
        pawn->colorPawn();
        pawns.append(pawn);
        ++numberOfPawns;
        return true;
    }
        break;
    case 1: {
        iscene->removeItem(pawn);
        placePawnSupport(pawn, 2);
        iscene->addItem(pawn);
        pawn->colorPawn();
        pawns.append(pawn);
        ++numberOfPawns;
        return true;
    }
        break;
    case 2: {
        iscene->removeItem(pawn);
        placePawnSupport(pawn, 3);
        iscene->addItem(pawn);
        pawn->colorPawn();
        pawns.append(pawn);
        ++numberOfPawns;
        return true;
    }
        break;
    case 3: {
        iscene->removeItem(pawn);
        placePawnSupport(pawn, 4);
        iscene->addItem(pawn);
        pawn->colorPawn();
        pawns.append(pawn);
        ++numberOfPawns;
        return true;
    }
        break;
    }
    return false;
}

void basebox::placePawnSupport(basepawn *pawn, int pawnNumber) {
    int x = OffCoordinates.x;
    int y = OffCoordinates.y;

    switch (pawnNumber) {
    case 1: {
        x += xShift;
        y += yShift;

        pawn->setPos(x, y);
        pawn->pawnNumber = 1;
    }
        break;
    case 2: {
        x += xShift + xShift/2;
        y += yShift;

        pawn->setPos(x, y);
        pawn->pawnNumber = 2;
    }
        break;
    case 3: {
        x += xShift;
        y += 2 * yShift;

        pawn->setPos(x, y);
        pawn->pawnNumber = 3;
    }
        break;
    case 4: {
        x += xShift + xShift/2;
        y += 2 * yShift;

        pawn->setPos(x, y);
        pawn->pawnNumber = 4;
    }
        break;
    }
}

void basebox::resetPawns() {
    for (int i = 0; i < pawns.size(); ++i) {
        if ((i + 1) != pawns.at(i)->pawnNumber) {
            if (placePawn(pawns.at(i))) {
            }
        }
    }
}
