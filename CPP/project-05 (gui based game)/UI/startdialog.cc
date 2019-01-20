#include "startdialog.hh"
#include "ui_startdialog.h"
#include "gamewindow.hh"

extern gameWindow *gWindow;

startDialog::startDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::startDialog)
{
    ui->setupUi(this);
}

startDialog::~startDialog()
{
    delete ui;
}

//void startDialog::startGameWindow()
//{
//    newGameWindow = new gameWindow;
//    newGameWindow->show();
//    this->hide();
//}

void startDialog::on_exitButton_clicked()
{
    QCoreApplication::quit();
}

void startDialog::on_startButton_clicked()
{
    numberOfPawns = ui->pawnsSpinBox->value();
    gWindow = new gameWindow();
    gWindow->show();
    this->hide();
}
