#ifndef HEXBOARD_HH
#define HEXBOARD_HH

#include <QList>
#include "basebox.hh"

class hexboard {
public:
    hexboard();

    QList<basebox *> getHexes();
    basebox* getBaseboard(Common::CubeCoordinate cubeCoordinates);

    Common::CubeCoordinate getCube(basebox* box);

    void placeHexes(int x, int y, int cols, int rows);
    void placePawns(int pawnsPerPlayer);

    basebox *gethex(Common::CubeCoordinate cubeCoordinates);

private:
    void createColumn(int x, int y, int n_rows, int col);
    Common::CubeCoordinate toCube(int q, int r);
    column_row toOff(Common::CubeCoordinate cubeCoordinates);

    QList<basebox *> hexes;
    int xShift = 40;
    int yShift = 20;

};


#endif // HEXBOARD_HH
