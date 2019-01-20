#include "hexboard.hh"
#include "gamescene.hh"
#include "basebox.hh"
#include "basepawn.hh"
#include "pawn.hh"
#include "QtDebug"

extern QGraphicsScene *iscene;

hexboard::hexboard() {

}

QList<basebox *> hexboard::getHexes() {
    return hexes;
}

basebox *hexboard::getBaseboard(Common::CubeCoordinate cubeCoordinates)
{
    for (int i = 0; i < hexes.size(); ++i)
    {
        if(hexes[i]->hex->getCoordinates()==cubeCoordinates)
        {
            return hexes[i];
        }
    }
    return NULL;
}

Common::CubeCoordinate hexboard::getCube(basebox *box) {
    return box->cubeCoordinates;
}

void hexboard::placeHexes(int x, int y, int cols, int rows) {

    for (int i = 1; i <= cols; ++i) {
        if (i % 2 == 0) {
            createColumn(x + xShift * i, y, rows, i);
        } else {
            createColumn(x + xShift * i, y + yShift, rows, i);
        }
    }
}

void hexboard::placePawns(int pawnsPerPlayer) {

    int counterPawnID =1;
    for (int i = 1; i <= pawnsPerPlayer; ++i) {
        // set player 1
        int playerId = 1;
        int col = 1;
        int row = 6;
        auto box = gethex(toCube(col, row));
        box->placePawn(playerId);
        auto pawnPtr = std::make_shared<Common::Pawn>(counterPawnID,
                                                      playerId,box->cubeCoordinates);
        box->hex->addPawn(pawnPtr);
        ++counterPawnID;

        // set player 2
        playerId = 2;
        col = 9;
        row = 6;
        auto box2 = gethex(toCube(col, row));
        box2->placePawn(playerId);
         pawnPtr = std::make_shared<Common::Pawn>(counterPawnID,
                                                  playerId,box2->cubeCoordinates);
        box2->hex->addPawn(pawnPtr);
        ++counterPawnID;
    }
}

basebox *hexboard::gethex(Common::CubeCoordinate cubeCoordinates) {
    QListIterator<basebox *> iter(hexes);

    while (iter.hasNext()) {
        if (iter.next()->cubeCoordinates == cubeCoordinates) {
            return iter.next();
        }
    }

    return NULL;
}

void hexboard::createColumn(int x, int y, int n_rows, int col) {

    for (int i = 1; i <= n_rows; ++i) {

            basebox* box = new basebox();
            Common::Hex *hex = new Common::Hex();

            box->hex = hex;
            box->col_row.q = col;
            box->col_row.r = i;
            box->cubeCoordinates = toCube(col, i);
            box->hex->setCoordinates(box->cubeCoordinates);

            box->setPos(x, y + (xShift * i));
            box->OffCoordinates.x = x;
            box->OffCoordinates.y = (y + (xShift * i));
            hexes.append(box);
            iscene->addItem(box);

            // color properly here and remove unwanted hexes

            box->setColor(colorCode::Water);
            box->color = colorCode::Water;
            box->hex->setPieceType(box->getString(colorCode::Water));

            if ((col == 1) || (col == 9)) {
                if ((i > 2) && (i < 8)) {
                    box->setColor(colorCode::Beach);
                    box->color = colorCode::Beach;
                    box->hex->setPieceType(box->getString(colorCode::Beach));
                } else {
                    hexes.removeAll(box);
                    iscene->removeItem(box);
                }
            } else if ((col == 2) || (col == 8)) {
                if ((i > 2) && (i < 9)) {
                    box->setColor(colorCode::Beach);
                    box->color = colorCode::Beach;
                    box->hex->setPieceType(box->getString(colorCode::Beach));
                } else {
                    hexes.removeAll(box);
                    iscene->removeItem(box);
                }
            } else if ((col == 3 || col == 7)) {
                if ((i > 1) && (i < 9)) {
                    box->setColor(colorCode::Beach);
                    box->color = colorCode::Beach;
                    box->hex->setPieceType(box->getString(colorCode::Beach));
                } else {
                    hexes.removeAll(box);
                    iscene->removeItem(box);
                }

                if ((i > 3) && (i < 7)) {
                    box->setColor(colorCode::Forest);
                    box->color = colorCode::Forest;
                    box->hex->setPieceType(box->getString(colorCode::Forest));
                }
            } else if ((col == 4) || (col == 6)) {
                if (i > 1) {
                    box->setColor(colorCode::Beach);
                    box->color = colorCode::Beach;
                    box->hex->setPieceType(box->getString(colorCode::Beach));
                } else {
                    hexes.removeAll(box);
                    iscene->removeItem(box);
                }

                if ((i > 3) && (i < 8)) {
                    box->setColor(colorCode::Forest);
                    box->color = colorCode::Forest;
                    box->hex->setPieceType(box->getString(colorCode::Forest));
                }

                if ((i == 5) || (i == 6)) {
                    box->setColor(colorCode::Mountain);
                    box->color = colorCode::Mountain;
                    box->hex->setPieceType(box->getString(colorCode::Mountain));
                }
            } else if ((col == 5)) {
                box->setColor(colorCode::Beach);
                box->color = colorCode::Beach;
                box->hex->setPieceType(box->getString(colorCode::Beach));

                if ((i == 3) || (i == 7)) {
                    box->setColor(colorCode::Forest);
                    box->color = colorCode::Forest;
                    box->hex->setPieceType(box->getString(colorCode::Forest));
                }

                if ((i == 4) || (i == 6)) {
                    box->setColor(colorCode::Mountain);
                    box->color = colorCode::Mountain;
                    box->hex->setPieceType(box->getString(colorCode::Mountain));
                }

                if (i == 5) {
                    box->setColor(colorCode::Peak);
                    box->color = colorCode::Peak;
                    box->hex->setPieceType(box->getString(colorCode::Peak));
                }
            }
    }
}

Common::CubeCoordinate hexboard::toCube(int q, int r) {
    Common::CubeCoordinate out;
    int shift = 5;
    q -= shift;
    r += shift;
    out.x = q;
    out.y = r - (q + (q&1))/2;
    out.z = - (out.x + out.y);

    return out;
}

column_row hexboard::toOff(Common::CubeCoordinate cubeCoordinates) {
    column_row out;
    out.q = cubeCoordinates.x;
    out.r = cubeCoordinates.z + (cubeCoordinates.x + (cubeCoordinates.x&1))/2;

    return out;
}
