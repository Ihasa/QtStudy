#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QStringList>
#include <QDir>
#include <QMap>

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
    void on_initCmdEnd();
    void on_pushButtonCmdExec_clicked();
    void on_cmdend();
    void on_cmdFinished(int);
    void on_cmdFinished2(int, QProcess::ExitStatus);
    void on_cmdendErr();
    void on_errorOccurred(QProcess::ProcessError);

    void on_showHelpButton_clicked();

    void on_cmdList_activated(QString);

private:
    Ui::MainWindow *ui;
    QProcess process;
    QProcess initProcess;
    QMap<QString, QString> cmdDescMap;

    QString getCmdDesc(QString);

};
#endif // MAINWINDOW_H
