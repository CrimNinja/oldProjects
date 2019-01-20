#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <map>
#include <unordered_map>
#include <QList>
#include "igameboard.hh"
#include "hex.hh"
#include "pawn.hh"
#include "actor.hh"
#include "transport.hh"


class GameBoard : public Common::IGameBoard
{
public:
    /**
     * @brief constructor
     */
    GameBoard();

    /**
      * @brief destructor
      */
    ~GameBoard();

    /**
     * @brief initialize the board for the game
     */
    void initializeBoard(Common::Hex *hexa);

    /**
     * @brief initialize the end goal hexes
     */
    void initializeGoalHexes();

    /**
     * @brief adds pawn to the player
     * @param id of the player to add pawns to, id of new pawn (integer, integer)
     */
    void addPawn(int, int);

    /**
     * @brief addPawn with call to the pawn constructor
     * @param playerId
     * @param pawnId
     * @param coord
     */
    void addPawn(int playerId, int pawnId, Common::CubeCoordinate coord);

    /**
     * @brief check the type of tile in question
     * @param tileCoord coordinates for the tile in question
     * @return type of tile (integer)
     */
    int checkTileOccupation(Common::CubeCoordinate tileCoord) const;

    /**
     * @brief check if the tile in question is a water tile
     * @param tileCoord coordinates for the tile in question
     * @return true or false depending on if it is a water tile or not
     */
    bool isWaterTile(Common::CubeCoordinate tileCoord) const;

    /**
     * @brief get the hex for the current tile
     * @param coordinates for the tile in question
     * @return pointer to the hex
     */
    std::shared_ptr<Common::Hex> getHex(Common::CubeCoordinate cubeCoor) const;

    /**
     * @brief movePawn sets a new location for the pawn.
     * @details Pawn is added to a Hex that is in the specified coordinates and removed from the old.
     * If there is no Hex-object in specified coordinates, the pawn remains in the old Hex.
     * @param pawnId The identifier of the pawn.
     * @param pawnCoord The target location of the pawn in coordinates.
     * @pre Pawn exists
     * @post Pawn is moved to the target location or stays in place if location doesn't exist.
     * @post Pawn's location is updated.
     * Exception quarantee: basic
     */
    virtual void movePawn(int pawnId, Common::CubeCoordinate pawnCoord);

    /**
     * @brief removePawn removes a pawn.
     * @details Removed pawn should be removed from a Hex-object if it is contained in one.
     * @param pawnId The identifier of the pawn.
     * @pre Pawn exists
     * @post pawn matching the id is removed. Exception quarantee: basic
     */
    virtual void removePawn(int pawnId);

    /**
     * @brief move actor to the desired location
     * @param id of the actor to be moved, coordinates to be moved to (integer, coordinates)
     */
    void moveActor(int, Common::CubeCoordinate);

    /**
     * @brief removeActor removes an actor.
     * @details The actor should be removed from a Hex-object.
     * @param actorId The identifier of the actor.
     * @pre Actor exists
     * @post Actor actorId is removed. Exception quarantee: basic
     */
    void removeActor(int);

    /**
     * @brief moveTransport sets a new location for the transport.
     * @details Transport is added to a Hex that is in the specified coordinates and removed from the old.
     * If there is no Hex-object in specified coordinates, the transport remains in the old Hex.
     * @param id The identifier of the transport.
     * @param coord The target location of the transport in coordinates.
     * @post transport is moved to a new location or stays in place if location doesn't exist.
     * @post All pawns in transport are moved to the new location with the transport.
     * @post Transport's and included pawns' locations will be updated.
     * Exception quarantee: basic
     */
    void moveTransport(int id, Common::CubeCoordinate coord);

    /**
     * @brief addTransport adds a new transport to the game board
     * @param transport transport to be added
     * @param coord
     * @pre CubeCoordinate must contain a Hex-tile. Transport isn't null-pointer.
     * @post Transport has been added to the hex in target coordinates.
     * @post Transport's location set to the hex in target coordinates.
     * Exception guarantee: basic
     */
    void addTransport(std::shared_ptr<Common::Transport> transport, Common::CubeCoordinate coord);

    /**
     * @brief addHex adds a new hex tile to the board
     * @param newHex Pointer of a new hex to add
     * @pre newHex is valid
     * @post newHex is added to the board. Any existing hex at the same
     * coordinates is replaced. Exception quarantee: basic
     */
    void addHex(std::shared_ptr<Common::Hex> newHex);
    /**
     * @brief addHex creates and adds a new hex tile to the board
     * @param newCoord coord of the new hex to add
     * @param type type of the tile to add
     * @post newHex is added to the board. Any existing hex at the same
     * coordinates is replaced. Exception quarantee: basic
     */
    void addHex(Common::CubeCoordinate newCoord, std::string type);

    /**
     * @brief addActor adds a actor to the game board
     * @param actor
     * @param actorCoord
     * @pre CubeCoordinate must contain a Hex-tile. Actor is not null-pointer.
     * @post Actor has been added to the hex in target coordinates
     * @post Actor's location set to the hex in target coordinates
     */
    void addActor(std::shared_ptr<Common::Actor> actor, Common::CubeCoordinate actorCoord);


    /**
     * @brief removeTransport removes an transport.
     * @param id The identifier of the transport.
     * @post transport removed from the gameboard and Hex-object. Exception quarantee: basic
     */
    void removeTransport(int id);



private:
    /**
     * @brief get the type of piece at the given coordinates
     * @param coordinates of the tile and the place in the tile ?
     * @return type of piece in the coordinates (string)
     */
    std::string getPieceType(Common::CubeCoordinate coord);


    std::unordered_map<int, std::shared_ptr<Common::Pawn> > _pawnMap;
    std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex> > _hexMap;
    std::map<int, std::shared_ptr<Common::Actor> > _actorMap;
    std::map<int, std::shared_ptr<Common::Transport> > _transportMap;


};
#endif // GAMEBOARD_HH
