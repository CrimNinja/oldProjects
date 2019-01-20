#include "player.hh"

Player::Player()
{
    _playerID=1;
    _pawnLeft=_totalPawnCount=1;
    _actionLeft=0;
}

Player::~Player()
{

}

Player::Player(int playerId, int pawnsPerPlayer)
{
    _playerID=playerId;
    _pawnLeft=_totalPawnCount=pawnsPerPlayer;
}

int Player::getPlayerId() const
{
    return _playerID;
}

void Player::setActionsLeft(unsigned int actionsLeft)
{
    _actionLeft=actionsLeft;
}

unsigned int Player::getActionsLeft() const
{
    return _actionLeft;
}


