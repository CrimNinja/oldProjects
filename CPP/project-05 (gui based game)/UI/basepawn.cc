#include "basepawn.hh"

#include <QPointF>
#include <QPolygonF>
#include <QVector>
#include <QBrush>


basepawn::basepawn(int id) {
    playerId = id;

    QVector<QPointF> basePoints;
    basePoints << QPointF(0, 0) << QPointF(1, 0) << QPointF(0, 1)
               << QPointF(1, 1) << QPointF(0, 0);

    int scaler = 7;

    for (int i = 0; i < basePoints.size(); ++i) {
        basePoints[i] *= scaler;
    }

    QPolygonF boxPawn(basePoints);

    setPolygon(boxPawn);
}

void basepawn::colorPawn() {

    QBrush brush;

    brush.setStyle(Qt::SolidPattern);

    if (playerId == 1) {
        brush.setColor(Qt::red);
    } else {
        brush.setColor(Qt::black);
    }
    setBrush(brush);
}
