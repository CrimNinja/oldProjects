#ifndef GAMESTATE_HH
#define GAMESTATE_HH

#include "igamestate.hh"
#include "basebox.hh"

#include <vector>


class GameState : public Common::IGameState
{
public:
    /**
     * @brief constructor
     */
    GameState();

    /**
      * @brief destructor
      */
    ~GameState();

    /**
     * @brief initializeVector
     * @param numberOfPlayer
     * @param numberOfPawns
     */
    void initializeVector(int numberOfPlayer, int numberOfPawns);

    /**
     * @brief get the current game phase
     * @return game phase
     */
    Common::GamePhase currentGamePhase() const;

    /**
     * @brief get the current player id
     * @return the player id (integer)
     */
    int currentPlayer() const;

    /**
     * @brief get the number of pawns per each player
     * @return the number of pawns per player (integer)
     */
    int getPawnPerPlayer();

    /**
     * @brief change the phase of the game
     * @param phase that needs to be set
     */
    void changeGamePhase(Common::GamePhase);
    /**
     * @brief change the phase of the game
     * @param phase that needs to be set
     */
    void changeGamePhase();

    /**
     * @brief changes the current player to the chosen player
     * @param id of the player that needs to be the current player (integer)
     */
    void changePlayerTurn(int);

    /**
     * @brief add a number of points to a player
     * @param player id, along with the number of points to be added (integer, integer)
     */
    void addPointsToPlayer(int, int);

    /**
     * @brief delete a pawn from the game
     * @param id of the player who will have a pawn to be deleted (integer)
     */
    void deletePawn(int);

    /**
     * @brief gets the number of pawns left for the player
     * @param id of the player in question (integer)
     * @return number of pawns left (integer)
     */
    int playerPawnsLeft(int);

    /**
     * @brief getTheWinner get the player with the most points
     * @return the playerId who won
     */
    int getTheWinner();

private:
    Common::GamePhase _gamePhaseId;
    int _playerInTurn;
    int _pawnPerPlayer;
    std::vector<std::pair<int, int>> _playerPointVector;
    std::vector<std::pair<int, int>> _playerPawnVector;
    QList<basebox> baseboxList;
};

#endif // GAMESTATE_HH
