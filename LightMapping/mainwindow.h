
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_spin_X_valueChanged(int arg1);
    void on_spin_Y_valueChanged(int arg1);
    void on_spin_Length_valueChanged(int arg1);
    void on_btn_Start_clicked();
    void on_spin_PenW_valueChanged(int arg1);
    void on_btn_Color1_clicked();
    void on_btn_Color2_clicked();
    void on_btn_Color3_clicked();

private:
    void update_ui();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
