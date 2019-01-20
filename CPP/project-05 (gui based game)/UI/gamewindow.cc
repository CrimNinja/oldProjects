#include "gamewindow.hh"
#include "gamescene.hh"
#include "ui_gamewindow.h"

extern gamescene* gScene;

gameWindow::gameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gameWindow)
{
    ui->setupUi(this);


    gScene = new gamescene(ui->graphicsView);
////    gScene = new gamescene();
//    gScene->show();
    gScene->turn = turnAction::Sink;
    gScene->init();
//    QGraphicsScene * scene = new QGraphicsScene();
//    ui->graphicsView->setScene(scene);


}

gameWindow::~gameWindow() {
    delete ui;
}

void gameWindow::switchAction() {
    if (ui->sinkRadioButton->isChecked()) {
        ui->selectStartRadioButton->setChecked(true);
    } else  if(ui->selectStartRadioButton->isChecked()){
        ui->selectDestinationRadioButton->setChecked(true);
    }else {
        ui->sinkRadioButton->setChecked(true);
    }
}

void gameWindow::on_quitButton_clicked() {

    QCoreApplication::quit();
}

void gameWindow::on_wheelButton_clicked() {

    gScene->Wheel->spin();
    gScene->wheelSpun = true;
    int wheelValue;
    wheelValue = gScene->Wheel->getCurrentValue();
    if (wheelValue == 4) {
        ui->wheelOutput->setText(QString("D"));
    } else {
        ui->wheelOutput->setText(QString::number(wheelValue));
    }
}




