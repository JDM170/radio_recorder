#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QFileDialog>
//#include <QMessageBox>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QString secondToTime(int);

private slots:
    void on_pushButton_clicked();
    void slotStartedStdout();
    void slotFinishedStdout(int);

private:
    Ui::MainWindow *ui;
    QProcess *my_proc;
//    QMessageBox *box;
};

#endif // MAINWINDOW_H
