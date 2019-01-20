#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include "gamewindow.hh"

#include <QDialog>

namespace Ui {
class startDialog;
}

class startDialog : public QDialog
{
    Q_OBJECT

public:
    explicit startDialog(QWidget *parent = 0);
    ~startDialog();

    int numberOfPawns;

public slots:
//    void startGameWindow();

private slots:
    void on_exitButton_clicked();

    void on_startButton_clicked();

private:
    Ui::startDialog *ui;
    gameWindow *newGameWindow;
};

#endif // STARTDIALOG_H
