#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

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
    void on_startButton_clicked();

    void on_closeApp_clicked();

private:
    Ui::MainWindow *ui;
    void installProgram();
    void notifyUser(QMessageBox::Icon icon, QString text);

};
#endif // MAINWINDOW_H
