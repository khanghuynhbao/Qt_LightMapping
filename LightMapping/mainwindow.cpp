
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QColorDialog>
#include "lightmapping.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setStyleSheet("background-color: black;");
    ui->setupUi(this);

    update_ui();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::update_ui()
{
    this->ui->spin_X->setValue(this->ui->Lightmapping->point_x());
    this->ui->spin_Y->setValue(this->ui->Lightmapping->point_y());
    this->ui->spin_Length->setValue(this->ui->Lightmapping->sideLength());
    this->ui->spin_PenW->setValue(this->ui->Lightmapping->penW());
}


void MainWindow::on_spin_X_valueChanged(int point_x)
{
    this->ui->Lightmapping->setPoint_X(point_x);
}


void MainWindow::on_spin_Y_valueChanged(int point_y)
{
    this->ui->Lightmapping->setPoint_Y(point_y);
}


void MainWindow::on_spin_Length_valueChanged(int length)
{
     this->ui->Lightmapping->setSideLength(length);
}

void MainWindow::on_spin_PenW_valueChanged(int penW)
{
    this->ui->Lightmapping->setPenW(penW);
}

void MainWindow::on_btn_Start_clicked()
{
    this->ui->Lightmapping->setStart(true);
    this->ui->Lightmapping->initializeTimers();
}

void MainWindow::on_btn_Color1_clicked()
{
    QString currentStylesheet = this->styleSheet();
    this->setStyleSheet("");
    QColorDialog colorDialog(ui->Lightmapping->color1(), this);
    colorDialog.setStyleSheet("background-color: white;");
    this->setStyleSheet(currentStylesheet);

    QColor color1 = colorDialog.getColor("Select Color1");
    if (color1.isValid()) {
        ui->Lightmapping->setColor1(color1);
        ui->Lightmapping->update();
    }
}


void MainWindow::on_btn_Color2_clicked()
{
    QString currentStylesheet = this->styleSheet();
    this->setStyleSheet("");
    QColorDialog colorDialog(ui->Lightmapping->color1(), this);
    colorDialog.setStyleSheet("background-color: white;");
    this->setStyleSheet(currentStylesheet);

    QColor color2 = colorDialog.getColor("Select Color2");
    if (color2.isValid()) {
        ui->Lightmapping->setColor1(color2);
        ui->Lightmapping->update();
    }
}

void MainWindow::on_btn_Color3_clicked()
{
    QString currentStylesheet = this->styleSheet();
    this->setStyleSheet("");
    QColorDialog colorDialog(ui->Lightmapping->color1(), this);
    colorDialog.setStyleSheet("background-color: white;");
    this->setStyleSheet(currentStylesheet);

    QColor color3 = colorDialog.getColor("Select Color3");
    if (color3.isValid()) {
        ui->Lightmapping->setColor1(color3);
        ui->Lightmapping->update();
    }
}


