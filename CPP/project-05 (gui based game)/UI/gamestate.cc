#include "gamestate.hh"
#include "gameengine.hh"
#include "igamestate.hh"


GameState::GameState()
{

}

GameState::~GameState()
{

}

void GameState::initializeVector(int numberOfPlayer, int numberOfPawns)
{
    _gamePhaseId=Common::GamePhase::SINKING;
    _playerInTurn=1;
    _pawnPerPlayer=numberOfPawns;

    for(int i=1; i<=numberOfPlayer; i++)
    {
        _playerPointVector.push_back(std::make_pair(i,0));
        _playerPawnVector.push_back(std::make_pair(i,_pawnPerPlayer));

    }
}

Common::GamePhase GameState::currentGamePhase() const
{
    return _gamePhaseId;
}

int GameState::currentPlayer() const
{
    return _playerInTurn;
}

int GameState::getPawnPerPlayer()
{
    return _pawnPerPlayer;
}

void GameState::changeGamePhase(Common::GamePhase)
{
    //no use of argument
    changeGamePhase();
}

void GameState::changeGamePhase()
{

    if (_gamePhaseId == Common::GamePhase::SINKING) {
        _gamePhaseId = Common::GamePhase::MOVEMENT;
    } else if (_gamePhaseId == Common::GamePhase::SPINNING) {
        _gamePhaseId = Common::GamePhase::MOVEMENT;
    } else if (_gamePhaseId == Common::GamePhase::MOVEMENT) {
        _gamePhaseId = Common::GamePhase::SINKING;
    }
}

void GameState::changePlayerTurn(int playerInTurn)
{
    _playerInTurn= playerInTurn;
}

void GameState::addPointsToPlayer(int playerId, int numberOfPointToAdd)
{
    _playerPointVector[playerId-1].second+=numberOfPointToAdd;
}

void GameState::deletePawn(int playerId)
{
    --_playerPawnVector[playerId-1].second;
}

int GameState::playerPawnsLeft(int playerId)
{
    return _playerPawnVector[playerId-1].second;
}

int GameState::getTheWinner()
{
    if(_playerPointVector[0].second>_playerPointVector[1].second)
    {
        return _playerPointVector[0].first;
    }else
    {
        return _playerPointVector[1].first;
    }
}
