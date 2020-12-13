#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QStringList>

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
    void on_pushButtonCmdExec_clicked();
    void on_cmdend();

    void on_resultGetButton_clicked();

private:
    Ui::MainWindow *ui;
    QProcess process;

};
#endif // MAINWINDOW_H
