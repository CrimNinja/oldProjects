# Programming 3 : Project

This project contain our project for the Programming 3 : Techniques course in Tampere University of Technology Fall 2018


### Compute part

The compute part manage GameState object, x Player objects, GameBoard object through the GameCode object.

When a tile is clicked in the UI part, a GameCode's function doAction is called with the basebox_ptr of the tile clicked. The action to perform is computed with the states of the fields in GameState. If an action is needed, GameBoard's fields will be modified and the boolean true will be returned to the UI. In case no action is needed, a boolean set to false will be return.

### Hex
GameBoard manage the hexes objects and we use them in GameCode.
The addHex(CubeCoordinate, string) is implemented but the test fails.

### Pawn
GameBoard manage the pawns object and we use them in GameCode.

### Actor
GameBoard manage the actor object. There is no use of any actor object right now so GameCode do not modify any actor object.

### Transport
GameBoard manage the transport object. There is no use of any transport object right now so GameCode do not modify any transport object.

## Graphical part

The UI is manage by GameWindow and gamescene.
We use basebox and basepawn to drawn a tile and a pawn. The generation of the entire board is supported by hexboard.

When a tile is clicked, the basebox which represente the tile catch the event adn call gamescene. Each basebox have a pointer to its hex object. The tile's caracteristics like type, position or number of pawns on are accessible through the hex pointer.

![Alt text](/class_diagram.jpg?raw=true "class diagram")

## Rules
Currently we have implemented the followinf rules :
- There is 2 players. Each player's pawns start on a unique tile, different for eahc player.
- the max of pawn is 4. More pawns are not visible (to small) so there is no implementation
- Each turn :
  - the player sink a tile
  - the player choose a tile with at less one of his pawns. This tile must have at less one neighbour which is not a "Water" tile (not a tile already sinked)
  - the player choose the destination of his pawn. The destination tile must be next to the start tile.
- If a clicked tile is not valid (try to sink a tile already sinked, try to move a pawn from a tile without a pawn, try to move too long from the start tile,...), the click is ignored.
- If a pawn is on a sinking tile, the pawn is removed from the board. If the player who sinked the tile own this pawn, he get -1 point. If not, the player get +1 point.
- when a player lose all his pawns, he lose.
- when a current player's pawns are all on a tile surrounded by water, no more move is possible, the player lose.
- the wheel is implemented but useless. Clicking on the button will spin the wheel but not impact the game.

## Test
The tst_gameboardtest.cpp file is partially commented. The firsts test pass. The commented test have not been tried but may pass.
