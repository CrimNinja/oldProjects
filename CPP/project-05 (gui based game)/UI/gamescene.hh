#ifndef GAMESCENE_HH
#define GAMESCENE_HH

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QObject>
#include "wheel.hh"
#include <QMouseEvent>
#include "hexboard.hh"
#include "basebox.hh"
#include "gamecode.hh"

enum turnAction {
    Move,
    Sink
};

class gamescene : public QGraphicsView {
    Q_OBJECT
public:

    // constructor
    gamescene(QGraphicsView *gView = NULL);

    void init();
    void sinkHex(basebox* box);
    void clicked(basebox* box);
    void updateBasebox(basebox* box);
    void mousePressEvent(QMouseEvent *event);

    int getCurrentPlayer();
    void takePawn(basepawn *pawn);
    bool placePawn(basebox *box);

    hexboard* hBoard;
    wheel* Wheel;
    QGraphicsScene* scene;
    GameCode* gCode;
    turnAction turn;
    int numberOfPawns;
    int currentPlayer;

    QPointF originalPosition;

    basepawn *currPawn;
    basebox *currBox;

    bool wheelSpun;
public slots:
    void finish(int playerID);
};

#endif // GAMESCENE_HH
