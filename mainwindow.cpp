#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    my_proc = new QProcess();
    connect(my_proc, SIGNAL(started()), this, SLOT(slotStartedStdout()));
    connect(my_proc, SIGNAL(finished(int)), this, SLOT(slotFinishedStdout(int)));
//    box = new QMessageBox();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString directory = QFileDialog::getSaveFileName(this, "Сохранить как...", "D:", "MP3 (*.mp3)");
    ui->directory->setText(directory);
    QString
            link = " -i " + ui->link->text().toUtf8(), // http://novosibirsk.radiokp32.mp3.streamr.ru, http://air.radiorecord.ru:805/rr_320, etc...
            time = " -t " + secondToTime(ui->time->text().toInt()), // 60 second, 120 second, etc...
            bitrate = " -ab " + ui->bitrate->currentText(), // 128k, 192k, 256k, 320k, etc...
            discretisation = " -ar " + ui->discretisation->currentText(),
    strCommand = "ffmpeg\\bin\\ffmpeg.exe " + link + " -acodec libmp3lame " + bitrate + discretisation + time + " " + directory;
//    box->setText(strCommand); // Debug
//    box->exec(); // Debug
    my_proc->start(strCommand);
}

void MainWindow::slotStartedStdout() {
    ui->textEdit->append("Идет запись!");
}

void MainWindow::slotFinishedStdout(int code) {
    if(code == 0) {
        ui->textEdit->append("Запись завершена!\n");
    }
    else if(code == 1) {
        ui->textEdit->append("Ошибка!\n");
        QString error = my_proc->readAllStandardError();
        ui->textEdit->append(error);
    }
}

QString MainWindow::secondToTime(int i_time) {
    QString time;
    if(i_time < 60) {
        time = "00:00:" + QString::number(i_time);
    }
    else {
        int minute = i_time / 60, hour = minute / 60;
        time = QString::number(hour) + ":" +
               QString::number(minute - 60*hour) + ":" +
               QString::number(i_time - 60*minute);
    }
    return time;
}
