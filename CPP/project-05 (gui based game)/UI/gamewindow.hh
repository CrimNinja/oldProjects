#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>

namespace Ui {
class gameWindow;
}

class gameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit gameWindow(QWidget *parent = 0);
    ~gameWindow();

    void switchAction();
//    int inputPawns;

private slots:
    void on_quitButton_clicked();

    void on_wheelButton_clicked();



private:
    Ui::gameWindow *ui;
};

#endif // GAMEWINDOW_H
