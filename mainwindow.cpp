#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), process(this)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonCmdExec_clicked()
{
    QStringList args("gui");
    process.start("git",args,QIODevice::ReadOnly);
    ui->resultLabel->setText("FOO");
}

