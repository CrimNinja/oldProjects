#ifndef PLAYER_HH
#define PLAYER_HH

#include "iplayer.hh"


class Player : public Common::IPlayer
{
public:
    /**
     * @brief Constructor
     */
    Player();

    /**
      * @brief Destructor
      */
    ~Player();

    /**
     * @brief Constructor with param
     * @param playerId the id for this player
     * @param pawnsPerPlayer the number of pawns per player from the start
     */
    Player(int playerId, int pawnsPerPlayer);

    /**
     * @brief getPlayer gets the player id.
     * @return The identifier of the player.
     * @post Exception quarantee: nothrow
     */
    int getPlayerId() const;

    /**
     * @brief setActionsLeft sets the player's remaining number of actions.
     * @param actionsLeft The number of actions left.
     * @post Actions left set to parameter value. Exception quarantee: nothrow
     */
    void setActionsLeft(unsigned int actionsLeft);

    /**
     * @brief getActionsLeft returns the amount of actions left for the player
     * @return amount of actions
     * @post Exception quarantee: nothrow
     */
    unsigned int getActionsLeft() const;

private:
    int _playerID;
    unsigned int _actionLeft;
    int _pawnLeft;
    int _totalPawnCount;

};

#endif // PLAYER_HH
