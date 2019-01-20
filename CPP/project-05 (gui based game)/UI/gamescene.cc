#include "gamescene.hh"
#include "hexboard.hh"
#include "gamewindow.hh"
#include "startdialog.hh"
#include "algorithm"
#include <QtDebug>
#include <QMessageBox>
#include <cstdlib>

extern gameWindow *gWindow;
extern startDialog *sWindow;
extern QGraphicsScene *iscene;

gamescene::gamescene(QGraphicsView* gView) {



    iscene = new QGraphicsScene(gView);
    gView->setScene(iscene);
    Wheel = new wheel();
    currentPlayer = 1;
}

void gamescene::init() {


    wheelSpun = false;
    numberOfPawns = sWindow->numberOfPawns;
    currPawn = NULL;
    gCode = new GameCode(numberOfPawns);
    hBoard = new hexboard();
    connect(this->gCode, &GameCode::weHaveAWinner,this, &gamescene::finish);

    hBoard->placeHexes(100, 100, 9, 9);
    hBoard->placePawns(numberOfPawns);
    gCode->initializationMaps(hBoard->getHexes());

}


void gamescene::sinkHex(basebox *box) {

    switch (box->color) {
        case colorCode::Coral:
            box->color = colorCode::Coral;
            break;
        case colorCode::Water:
            box->color = colorCode::Coral;
            break;
        case colorCode::Beach:
            box->color = colorCode::Water;
            break;
        case colorCode::Forest:
            box->color = colorCode::Beach;
            break;
        case colorCode::Mountain:
            box->color = colorCode::Forest;
            break;
        case colorCode::Peak:
//            box->color = colorCode::Mountain;
            break;
        default:
            break;
        }
    box->setColor(box->color);
    box->hex->setPieceType(box->getString(box->color));
}

void gamescene::clicked(basebox *box)
{

    if(gCode->doAction(box))
    {
        updateBasebox(box);
        gWindow->switchAction();

        updateBasebox(box);

        std::vector<Common::CubeCoordinate> neighbourCubeCoordinateVector=
                box->hex->getNeighbourVector();
        std::vector<Common::CubeCoordinate>::size_type i,
                sizeNeighbourCubeCoordinateVector=neighbourCubeCoordinateVector.size();
        for( i= 0; i != sizeNeighbourCubeCoordinateVector; ++i)
        {
            basebox* boxNeighbour=
                    hBoard->getBaseboard(neighbourCubeCoordinateVector[i]);
            if (boxNeighbour!=NULL)
            {
                updateBasebox(boxNeighbour);
            }
        }
    }
}

void gamescene::updateBasebox(basebox *box)
{
    while(!box->pawns.isEmpty())
    {
        iscene->removeItem(box->pawns.first());
        box->pawns.removeFirst();
    }
    box->numberOfPawns=box->hex->getPawnAmount();
    std::vector<std::shared_ptr<Common::Pawn> > v=box->hex->getPawns();
    std::vector<std::shared_ptr<Common::Pawn> >::size_type j,
            sizeV=v.size();
    for(j = 0; j != sizeV; ++j)
    {
        box->placePawn(v[j]->getPlayerId());
    }
}

void gamescene::finish(int playerID)
{
    QMessageBox messageBox;
    std::string s="Player "+std::to_string(playerID)+" Win";
    messageBox.setText(QString::fromStdString(s));
    messageBox.setWindowTitle("Island game.");
    messageBox.exec();
    std::exit(0);
}

void gamescene::mousePressEvent(QMouseEvent *event) {

    QGraphicsView::mousePressEvent(event);
}

int gamescene::getCurrentPlayer() {
    return currentPlayer;
}

void gamescene::takePawn(basepawn *pawn) {
    originalPosition = pawn->pos();
    return;
}

bool gamescene::placePawn(basebox *box) {
    if (box->placePawn(currPawn)) {
        currBox->numberOfPawns -= 1;
        currBox->pawns.removeAll(currPawn);
    }
}

