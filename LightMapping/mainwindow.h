
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
    void on_spin_Length_valueChanged(double arg1);
    void on_btnStart_clicked();
    void on_spin_PenW_valueChanged(int arg1);
    void on_spin_Times_valueChanged(int arg1);

    void on_btnColor1_clicked();
    void on_btnColor2_clicked();

private:
    void update_ui();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
