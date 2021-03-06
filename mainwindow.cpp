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

    connect(&initProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(on_initCmdEnd()));

    initProcess.start("git",QStringList("version"));

    QDir dir = QDir::currentPath();
    this->setWindowTitle(dir.absolutePath());

    cmdDescMap.insert("log","履歴を表示する");
    cmdDescMap.insert("diff", "任意のリビジョン間の差分を表示する");
    cmdDescMap.insert("status", "作業コピーの状況を表示する");
    cmdDescMap.insert("branch", "ブランチを操作する");

    ui->cmdDescText->setText(getCmdDesc(ui->cmdList->currentText()));

    fileDialog.setFileMode(QFileDialog::DirectoryOnly);

    stm = QScxmlStateMachine::fromFile("test.scxml");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonCmdExec_clicked()
{
    QStringList args;

    args.append(ui->cmdList->currentText());

    process.start("git",args);
stm->submitEvent("T1");
QStringList act = stm->activeStateNames();
QString str = (act.size() > 0) ? act[0] : "";

    ui->execedCmdLabel->setText(process.program() +" "+ args.join(" ") + str);



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
    QTextCodec* codec = QTextCodec::codecForName(ui->encodingComboBox->currentText().toLocal8Bit());

    array = process.readAllStandardOutput();
    result = codec->toUnicode(array);//QString::fromLocal8Bit(array);

    ui->resultLabel->setText(result);
}

void MainWindow::on_cmdendErr(){
    QByteArray array;
    QString result;
    QTextCodec* codec = QTextCodec::codecForName(ui->encodingComboBox->currentText().toLocal8Bit());

    array = process.readAllStandardError();
    result = codec->toUnicode(array);

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

void MainWindow::on_initCmdEnd(){
    ui->gitverLabel->setText(QString::fromLocal8Bit(initProcess.readAllStandardOutput()));
}

void MainWindow::on_showHelpButton_clicked()
{
    QStringList args = QStringList(ui->cmdList->currentText());
    args.append("--help");
    process.start("git",args);
    ui->execedCmdLabel->setText(process.program() +" "+ args.join(" "));

    on_cmdend();
}

void MainWindow::on_cmdList_activated(QString selected)
{
    ui->cmdDescText->setText(getCmdDesc(selected));
}

QString MainWindow::getCmdDesc(QString selected){
    QString desc = "説明なし";
    if(cmdDescMap.contains(selected)){
        desc = cmdDescMap[selected];
    }
    return desc;
}

void MainWindow::on_selectDirButton_clicked()
{
    QString dirPath;
    QDir dir;
    QString gitMsg;
    if(fileDialog.exec()){
        dir = fileDialog.directory();
        fileDialog.setDirectory(dir);

        dirPath = dir.absolutePath();
        process.setWorkingDirectory(dirPath);
        ui->currentDirText->setText(dirPath);

        if(isGitRepository(dir)){
            gitMsg = "this folder is git repository";
        } else {
            gitMsg = "this folder is not git repository";
        }
        ui->isGitRepoLabel->setText(gitMsg);

    }
}

bool MainWindow::isGitRepository(QDir dir){
    bool res = false;

    do{
        if(dir.exists(".git")){
            res = true;
            break;
        } else {
            /* nothing */
        }
    }while(dir.cdUp());

    return res;
}
