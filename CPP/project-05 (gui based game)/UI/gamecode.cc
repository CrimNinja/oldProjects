#include "gamecode.hh"
#include "player.hh"
#include "gameboard.hh"
#include "basebox.hh"
#include "gamescene.hh"
#include <QtDebug>

GameCode::~GameCode()
{

}

GameCode::GameCode(int numberOfPawns)
{
    int nbOfPlayer=2;
    for (int i=1; i<=nbOfPlayer; ++i)
    {
        auto playerPtr = std::make_shared<Player>(i,numberOfPawns);
       _playerMap.insert(std::make_pair(i,playerPtr));
    }
    _gameState= new GameState();
    _gameState->initializeVector(nbOfPlayer,numberOfPawns);
    _gameBoard = new GameBoard();
}





void GameCode::initializationMaps(QList<basebox*>  baseboxList)
{
    QList<basebox*>::iterator i, baseBoxEnd=baseboxList.end();
    for (i = baseboxList.begin(); i != baseBoxEnd; ++i)
    {
        basebox* bBox=*i;
        _gameBoard->initializeBoard(bBox->hex);
    }
}

bool GameCode::doAction(basebox *bBox)
{
    bool actionPerformed = false;
    switch(_gameState->currentGamePhase())
    {
        case Common::GamePhase::SINKING:
            actionPerformed = sink(bBox);
            break;
        case Common::GamePhase::MOVEMENT:

            if(!firstHexValid)
            {
                actionPerformed = selectStartForMove(bBox);
            }else
            {

                actionPerformed = selectDestinationForMove(bBox);
            }
            break;
        case Common::GamePhase::SPINNING:
            break;
        default:
            break;
    }
    return actionPerformed;
}

bool GameCode::sink(basebox* bBox)
{
    std::string bBoxType =bBox->hex->getPieceType();
    if((bBoxType!="Peak") && (bBoxType!="Coral"))
    {
        switch (bBox->color)
        {
            case colorCode::Water:
                bBox->color = colorCode::Coral;
                break;
            case colorCode::Beach:
            {
                bBox->color = colorCode::Water;
                removeSinkedPawns(bBox->hex);
            }
                break;
            case colorCode::Forest:
                bBox->color = colorCode::Beach;
                break;
            case colorCode::Mountain:
                bBox->color = colorCode::Forest;
                break;
            default:
                break;
        }
        bBox->setColor(bBox->color);
        bBox->hex->setPieceType(bBox->getString(bBox->color));

        auto it = _playerMap.begin(), endPlayerMap=_playerMap.end();
        for (it = _playerMap.begin(); it != endPlayerMap; ++it )
        {
            if(_gameState->playerPawnsLeft(it->first)==0)
            {
                emit weHaveAWinner(_gameState->getTheWinner());
            }
        }
        _gameState->changeGamePhase();
        return true;

    }else{
        return false;
    }
}

bool GameCode::selectStartForMove(basebox *bBox)
{
    std::vector<Common::CubeCoordinate> neighbourCubeCoordinateVector=
            bBox->hex->getNeighbourVector();
    std::vector<Common::CubeCoordinate>::size_type i;
    std::vector<Common::CubeCoordinate>::size_type sizeNeighbourCubeCoordinateVector=
            neighbourCubeCoordinateVector.size();
    for( i= 0; i != sizeNeighbourCubeCoordinateVector; ++i)
    {
        std::shared_ptr<Common::Hex> hexNeighbour=
                _gameBoard->getHex(neighbourCubeCoordinateVector[i]);
        if(hexNeighbour!=NULL)
        {

            if(!_gameBoard->isWaterTile(hexNeighbour->getCoordinates()))
            {
                std::vector<std::shared_ptr<Common::Pawn> > v=bBox->hex->getPawns();
                std::vector<std::shared_ptr<Common::Pawn> >::size_type j;
                std::vector<std::shared_ptr<Common::Pawn> >::size_type sizeV=v.size();
                for( j = 0; j!= sizeV; ++j)
                {
                    if(v[j]!=NULL && v[j]->getPlayerId()==_gameState->currentPlayer())
                    {
                        firstHex=_gameBoard->getHex(bBox->hex->getCoordinates());
                        firstHexValid=true;
                        return true;
                    }
                }
            }
        }
    }
    int nbPawnsOfCurrentPlayerOnbBox =0;
    std::vector<std::shared_ptr<Common::Pawn> > v=bBox->hex->getPawns();
    std::vector<std::shared_ptr<Common::Pawn> >::size_type j;
    std::vector<std::shared_ptr<Common::Pawn> >::size_type sizeV=v.size();
    for( j = 0; j!= sizeV; ++j)
    {
        if((v[j]!=NULL) &&
            (v[j]->getPlayerId()==_gameState->currentPlayer()))
        {
            ++nbPawnsOfCurrentPlayerOnbBox;
        }

    }
    if(_gameState->playerPawnsLeft(_gameState->currentPlayer())==
            nbPawnsOfCurrentPlayerOnbBox)
    {
        _gameState->addPointsToPlayer(_gameState->currentPlayer(),
                                      -nbPawnsOfCurrentPlayerOnbBox);
        emit weHaveAWinner(_gameState->getTheWinner());
    }
    return false;
}

bool GameCode::selectDestinationForMove(basebox *bBox)
{
    if(!_gameBoard->isWaterTile(bBox->hex->getCoordinates()))
    {
        std::vector<Common::CubeCoordinate> neighbourCubeCoordinateVector=
                bBox->hex->getNeighbourVector();
        std::vector<Common::CubeCoordinate>::size_type i;
        std::vector<Common::CubeCoordinate>::size_type sizeNeighbourCCr=
                neighbourCubeCoordinateVector.size();
        for( i= 0; i != sizeNeighbourCCr; ++i)
        {
            if(neighbourCubeCoordinateVector[i]==firstHex->getCoordinates())
            {
                std::vector<std::shared_ptr<Common::Pawn> > v=firstHex->getPawns();
                std::vector<std::shared_ptr<Common::Pawn> >::size_type j;
                std::vector<std::shared_ptr<Common::Pawn> >::size_type sizeV=v.size();
                for( j= 0; j != sizeV; ++j)
                {
                    if(v[j]->getPlayerId()==_gameState->currentPlayer())
                    {
                        firstHex->removePawn(v[j]);
                        bBox->hex->addPawn(v[j]);
                        firstHexValid=false;

                        if(bBox->hex->getPieceType()=="Peak")
                        {
                            _gameState->addPointsToPlayer(v[j]->getPlayerId(),1);
                        }
                        _gameState->changeGamePhase();

                        if(_gameState->currentPlayer()==1)
                        {
                            _gameState->changePlayerTurn(2);
                        }else
                        {
                            _gameState->changePlayerTurn(1);
                        }
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void GameCode::removeSinkedPawns(Common::Hex* hex)
{
    std::vector<std::shared_ptr<Common::Pawn> > pawns=hex->getPawns();
    while(!pawns.empty())
    {
        if(pawns.back()->getPlayerId()!=_gameState->currentPlayer())
        {
            _gameState->addPointsToPlayer(_gameState->currentPlayer(),1);
        }else
        {
            _gameState->addPointsToPlayer(_gameState->currentPlayer(),-1);
        }
        _gameState->deletePawn(pawns.back()->getPlayerId());
        hex->removePawn(pawns.back());
        pawns.pop_back();
    }
}

