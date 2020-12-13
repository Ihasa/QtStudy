#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), process(this)
{
    ui->setupUi(this);
    //connect(&process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(on_cmdFinished(int)));
    connect(&process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(on_cmdFinished2(int, QProcess::ExitStatus)));
    connect(&process, SIGNAL(readyReadStandardOutput()), this, SLOT(on_cmdend()));
    connect(&process, SIGNAL(readyReadStandardError()), this, SLOT(on_cmdendErr()));
    connect(&process, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(on_errorOccurred(QProcess::ProcessError)));
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

void MainWindow::on_cmdendErr(){
    QByteArray array;
    QString result;

    array = process.readAllStandardError();
    result = QString::fromLocal8Bit(array);

    //result = "called";

    ui->errorLabel->setText(result);
}

void MainWindow::on_errorOccurred(QProcess::ProcessError errorcode){
    ui->errorcodeLabel->setText(QString::number(errorcode));
}

void MainWindow::on_cmdFinished(int exitcode){
    ui->exitcodeLabel->setText(QString::number(exitcode));
}

void MainWindow::on_cmdFinished2(int exitcode, QProcess::ExitStatus errorcode){
    ui->exitcodeLabel->setText(QString::number(errorcode) +" "+ QString::number(exitcode));
}

void MainWindow::on_resultGetButton_clicked()
{
    on_cmdend();
}
