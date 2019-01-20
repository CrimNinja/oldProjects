#include "gameboard.hh"
#include "igameboard.hh"

#include <map>
#include <unordered_map>
#include <QtDebug>





GameBoard::GameBoard()
{

}

GameBoard::~GameBoard()
{

}

void GameBoard::initializeBoard(Common::Hex *hexa)
{
        std::shared_ptr<Common::Hex> hexPtr(hexa);
        _hexMap.insert(std::make_pair(hexa->getCoordinates(),
                                      hexPtr));
        if(hexa->getPawnAmount()!=0)
        {
            std::vector<std::shared_ptr<Common::Pawn> > v=hexa->getPawns();
            std::vector<std::shared_ptr<Common::Pawn> >::size_type sizeV=v.size();
            for(std::vector<std::shared_ptr<Common::Pawn> >::size_type i = 0;
                i != sizeV; i++)
            {
                _pawnMap.insert(std::make_pair(v[i]->getId(), v[i]));
            }
        }
}

void GameBoard::initializeGoalHexes()
{

}

void GameBoard::addPawn(int, int)
{
   //useless without cubeCoordinate
}

int GameBoard::checkTileOccupation(Common::CubeCoordinate cubeCoordinate) const
{
    std::shared_ptr<Common::Hex> sharedPtrHex = getHex(cubeCoordinate);

    if(sharedPtrHex!= nullptr)
    {
        return sharedPtrHex->getPawnAmount();
    }
    return -1;
}

bool GameBoard::isWaterTile(Common::CubeCoordinate cubeCoordinate) const
{
    std::shared_ptr<Common::Hex> sharedPtrHex = getHex(cubeCoordinate);

    if(sharedPtrHex!= nullptr)
    {
        if((sharedPtrHex->getPieceType()=="Water") ||
            (sharedPtrHex->getPieceType()=="Coral"))
        {
            return true;
        }
    }
    return false;
}

std::shared_ptr<Common::Hex> GameBoard::getHex(Common::CubeCoordinate cubeCoor) const
{
    if(_hexMap.find(cubeCoor)==_hexMap.end())
    {
        return nullptr;
    }
    return _hexMap.find(cubeCoor)->second;
}

void GameBoard::movePawn(int pawnId, Common::CubeCoordinate pawnCoord)
{
    std::shared_ptr<Common::Hex> newSharedPtrHex = getHex(pawnCoord);

    if(newSharedPtrHex!=nullptr)
    {
        std::shared_ptr<Common::Pawn> pawn=_pawnMap[pawnId];
        std::shared_ptr<Common::Hex> oldSharedPtrHex =
                getHex(pawn->getCoordinates());
        oldSharedPtrHex->removePawn(pawn);
        newSharedPtrHex->addPawn(pawn);
        pawn->setCoordinates(pawnCoord);

    }
}

void GameBoard::removePawn(int pawnId)
{
    std::shared_ptr<Common::Pawn> pawn=_pawnMap[pawnId];
    std::shared_ptr<Common::Hex> oldSharedPtrHex =
            getHex(pawn->getCoordinates());
    oldSharedPtrHex->removePawn(pawn);
}

void GameBoard::moveActor(int actorId, Common::CubeCoordinate coord)
{
    std::shared_ptr<Common::Hex> newSharedPtrHex = getHex(coord);

    if(newSharedPtrHex!=nullptr)
    {
        if(_actorMap.find(actorId)==_actorMap.end())
        {
            std::shared_ptr<Common::Actor> sharedPtrActor =
                    _actorMap.find(actorId)->second;
            std::shared_ptr<Common::Hex> oldSharedPtrHex = sharedPtrActor->getHex();
            oldSharedPtrHex->removeActor(sharedPtrActor);
            newSharedPtrHex->addActor(sharedPtrActor);
            sharedPtrActor->addHex(newSharedPtrHex);
        }
    }

}

void GameBoard::removeActor(int actorId)
{
    if(_actorMap.find(actorId)!= _actorMap.end())
    {
        std::shared_ptr<Common::Actor> sharedPtrActor =
                _actorMap.find(actorId)->second;

        std::shared_ptr<Common::Hex> sharedPtrHex = sharedPtrActor->getHex();
        sharedPtrHex->removeActor(sharedPtrActor);
        _actorMap.erase(_actorMap.find(actorId));
    }
}

void GameBoard::moveTransport(int id, Common::CubeCoordinate coord)
{
    //not implemented
}

void GameBoard::addTransport(std::shared_ptr<Common::Transport> transport, Common::CubeCoordinate coord)
{
    std::shared_ptr<Common::Hex> sharedPtrHex = getHex(coord);
    transport->addHex(sharedPtrHex);
    sharedPtrHex->addTransport(transport);
    _transportMap.insert(std::make_pair(transport->getId(),transport));

}

void GameBoard::addHex(std::shared_ptr<Common::Hex> newHex)
{
    std::shared_ptr<Common::Hex> sharedPtrHex = getHex(newHex->getCoordinates());

    if(sharedPtrHex!= nullptr)
    {
        _hexMap.erase(_hexMap.find(sharedPtrHex->getCoordinates()));
        addHex(newHex);
    }
    else
    {
        _hexMap.insert(std::make_pair(newHex->getCoordinates(), newHex));
    }
}

void GameBoard::addHex(Common::CubeCoordinate newCoord, std::string type)
{
    std::shared_ptr<Common::Hex> sharedPtrHex = getHex(newCoord);
    std::shared_ptr<Common::Hex> newHex(new Common::Hex);
    newHex->setCoordinates(newCoord);
    newHex->setPieceType(type);
    if(sharedPtrHex!= nullptr)
    {
        _hexMap.erase(_hexMap.find(sharedPtrHex->getCoordinates()));
        addHex(newHex);
    }
    else
    {
        _hexMap.insert(std::make_pair(newHex->getCoordinates(), newHex));
    }
}

void GameBoard::addActor(std::shared_ptr<Common::Actor> actor, Common::CubeCoordinate actorCoord)
{
    std::shared_ptr<Common::Hex> sharedPtrHex = getHex(actorCoord);

    if((sharedPtrHex!= nullptr) && (actor != nullptr))
    {
        _actorMap.insert(std::make_pair(actor->getId(), actor));
        sharedPtrHex->addActor(actor);
        actor->move(sharedPtrHex);
    }
}

void GameBoard::addPawn(int playerId, int pawnId, Common::CubeCoordinate coord)
{
    std::shared_ptr<Common::Hex> sharedPtrHex = getHex(coord);

    if(sharedPtrHex!= nullptr)
    {
        auto pawnPtr = std::make_shared<Common::Pawn>(playerId, pawnId, coord);
        _pawnMap.insert(std::make_pair(pawnId, pawnPtr));
        sharedPtrHex->addPawn(pawnPtr);
    }
}



void GameBoard::removeTransport(int transportId)
{
    if(_transportMap.find(transportId)!= _transportMap.end())
    {
        _transportMap.erase(_transportMap.find(transportId));
    }
}

std::string GameBoard::getPieceType(Common::CubeCoordinate coord)
{
    std::shared_ptr<Common::Hex> sharedPtrHex = getHex(coord);

    if(sharedPtrHex!=nullptr)
    {
        return sharedPtrHex->getPieceType();
    }
    return NULL;
}
