
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QColorDialog>
#include "lightmapping.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
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
    this->ui->spin_Times->setValue(this->ui->Lightmapping->times());
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


void MainWindow::on_spin_Length_valueChanged(double length)
{
    this->ui->Lightmapping->setSideLength(length);
}

void MainWindow::on_btnStart_clicked()
{
    this->ui->Lightmapping->setStart(true);
}


void MainWindow::on_spin_Times_valueChanged(int times)
{
    this->ui->Lightmapping->setTimes(times);
}


void MainWindow::on_spin_PenW_valueChanged(int penW)
{
    this->ui->Lightmapping->setPenW(penW);
}


void MainWindow::on_btnColor1_clicked()
{
    QColor color = QColorDialog::getColor(ui->Lightmapping->color1(), this, "Select Color1");
    this->ui->Lightmapping->setColor1(color);
}


void MainWindow::on_btnColor2_clicked()
{
    QColor color = QColorDialog::getColor(ui->Lightmapping->color2(), this, "Select Color2");
    this->ui->Lightmapping->setColor2(color);
}

