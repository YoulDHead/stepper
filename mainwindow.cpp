#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SSerial();
}


bool MainWindow::SSerial(){


    SPort.setPortName("COM10");

    SPort.open(QSerialPort::ReadWrite);

    SPort.setBaudRate(QSerialPort::Baud9600);
    SPort.setDataBits(QSerialPort::Data8);
    SPort.setParity(QSerialPort::NoParity);
    SPort.setStopBits(QSerialPort::OneStop);
    SPort.setFlowControl(QSerialPort::NoFlowControl);

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{



    QString left = "left200\n\r";

    SPort.write(left.toUtf8());


}

void MainWindow::on_pushButton_2_clicked()
{
    QString left = "right200\n\r";

    SPort.write(left.toUtf8());
}
