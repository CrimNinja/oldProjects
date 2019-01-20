#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void reset();
    bool male();
    ~MainWindow();

public slots:
    void calculate_BMI();
    void update_gender();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
