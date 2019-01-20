#include "gameboard.hh"
#include "gamestate.hh"
#include "player.hh"
#include "startdialog.hh"
#include "gamewindow.hh"
#include "basebox.hh"
#include "gamescene.hh"

#include <memory>
#include <QApplication>

gamescene* gScene;
gameWindow *gWindow;
startDialog *sWindow;
QGraphicsScene *iscene;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

//    gScene = new gamescene();
//    gScene->show();
//    gScene->init();

    sWindow = new startDialog();

    sWindow->show();

    return a.exec();
}
