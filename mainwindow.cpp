#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), process(this)
{
    ui->setupUi(this);

    //connect(&process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(on_cmdend()));
    connect(&process, SIGNAL(readyReadStandardOutput()), this, SLOT(on_cmdend()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonCmdExec_clicked()
{
    QStringList args("--version");

    process.start("git",args);

    //ui->resultLabel->setText("command started");

//    if(true == process.waitForFinished(5000)){

//        on_cmdend();

//    } else {
//        ui->resultLabel->setText("cmd not end");
//    }

}

void MainWindow::on_cmdend(){
    QByteArray array;
    QString result;

    array = process.readAllStandardOutput();
    result = QString::fromLocal8Bit(array);

    //result = "called";

    ui->resultLabel->setText(result);
}


void MainWindow::on_resultGetButton_clicked()
{
    on_cmdend();
}
