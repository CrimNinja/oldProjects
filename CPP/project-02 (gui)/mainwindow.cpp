//Siva Sankar Kannan 267605
//siva.kannan@student.tut.fi

//Joe David 267598
//joe.david@bstudent.tut.fi

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    Add suffix for the spin boxes.
    ui->weight_spinBox->setSuffix(" kg");
    ui->height_spinBox->setSuffix(" cm");

//    Creating an action group to make easier having exclusively only one
//    option selected at all times.
    QActionGroup *Gender_group = new QActionGroup(this);
    Gender_group->addAction(ui->action_male);
    Gender_group->addAction(ui->action_female);
    Gender_group->setExclusive(true);

//    Connect all the actions to their specific functions.
    connect(ui->action_female, SIGNAL(triggered(bool)),
            this, SLOT(update_gender()));
    connect(ui->action_male, SIGNAL(triggered(bool)),
            this, SLOT(update_gender()));

    connect(ui->action_Quit, &QAction::triggered,
            this, &MainWindow::close);
    connect(ui->action_Reset, &QAction::triggered,
            this, &MainWindow::reset);

    connect(ui->weight_spinBox, SIGNAL(valueChanged(int)),
            this, SLOT(calculate_BMI()));
    connect(ui->height_spinBox, SIGNAL(valueChanged(int)),
            this, SLOT(calculate_BMI()));
}

MainWindow::~MainWindow() {

    delete ui;
}

void MainWindow::reset() {

//    Reset all the values to defaults.
    ui->weight_Slider->setValue(0);
    ui->height_Slider->setValue(0);
    ui->action_female->setChecked(true);
    ui->Gender_display->setText("female");
    ui->BMI_display->setText("-");
    ui->interpretation_display->setText("-");
}

void MainWindow::calculate_BMI() {

//    Get the height and weight values.
    double height_value = ui->height_spinBox->value();
    double weight_value = ui->weight_spinBox->value();

//    Calculate the BMI provided both the height and the weight values
//    are non-zero. It is possible to calculate without this check, but
//    that would make no sense as to haveing 0 height or weight.
    if (height_value != 0 and weight_value != 0) {

        double BMI = weight_value/(0.0001*height_value*height_value);

//        Use ternery operator to simplify the conditional statement,
//        that is used to store the points needed for BMI calculation.
        std::vector<double> points;
        QString interpretation;
        male() ? points = {20.7, 26.4, 27.8, 31.1}:
                 points = {19.1, 25.8, 27.3, 32.2};

//        Calculate BMI and classify the BMI with the interpretation.
        if (BMI <= points[0])
            interpretation = "underweight";
        else if (BMI <= points[1])
            interpretation = "normal";
        else if (BMI <= points[2])
            interpretation = "slightly overweight";
        else if (BMI <= points[3])
            interpretation = "overweight";
        else if (BMI > points[3])
            interpretation = "much overweight";

//        Display the BMI along with the interpretation.
        ui->BMI_display->setText(QString::number(BMI));
        ui->interpretation_display->setText(interpretation);
    } else {

//        If either height or weight is turned to 0, reset just the table.
        ui->BMI_display->setText("-");
        ui->interpretation_display->setText("-");
    }
}

bool MainWindow::male() {
//    Returns if the selected gender is male.
    return ui->action_male->isChecked();
}

void MainWindow::update_gender() {
//    Update the gender display and recalculate BMI.
    QString gender;
    male() ? gender = "male" : gender = "female";

    ui->Gender_display->setText(gender);
    calculate_BMI();
}

