#ifndef GAMECODE_HH
#define GAMECODE_HH

#include "gameboard.hh"
#include "gamestate.hh"
#include "player.hh"
#include <QList>
#include "basebox.hh"
#include "pawn.hh"
#include <QObject>

class GameCode: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief constructor
     */
    GameCode()=default;

    /**
      * @brief destructor
      */
    ~GameCode();

    /**
     * @brief constructor
     */
    explicit GameCode(int numberOfPawns);

    /**
     * @brief initializationMaps_game
     * @param hexList the list of Hexes
     * @param baseboxList the list of baseboxes
     */
    void initializationMaps(QList<basebox*>  baseboxList);

    /**
     * @brief doAction choose function from gamestate.gamePhase's state
     * @param bBox the basebox clicked by the player
     * @return true if any action was performed
     */
    bool doAction(basebox* bBox);




signals:
    void weHaveAWinner(int playerID);
private:

    /**
     * @brief sink manage the sinking part
     * @param bBox the basebox clicked
     * @return true if the tile was sinked
     */
    bool sink(basebox* bBox);

    /**
     * @brief selectStartForMove manage the selection of the start's move tile
     * @param bBox the basebox clicked
     * @return true if the tile is a possible tile for a move
     */
    bool selectStartForMove(basebox* bBox);

    /**
     * @brief selectDestinationForMove manage the selection of the destination's move tile
     * @param bBox the basebox clicked
     * @return true if the move was performed
     */
    bool selectDestinationForMove(basebox* bBox);

    /**
     * @brief removeSinkedPawns remove pawns of a sinked tile
     * @param shared_ptr of the hex sinked
     */
    void removeSinkedPawns(Common::Hex* hex);

    GameBoard* _gameBoard;
    GameState* _gameState;
    std::unordered_map<int, std::shared_ptr<Player> > _playerMap;
    std::shared_ptr<Common::Hex> firstHex;
    bool firstHexValid;

};

#endif // GAMECODE_HH
