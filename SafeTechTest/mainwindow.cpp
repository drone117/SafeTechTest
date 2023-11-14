#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "packageinstaller.h"
#include <QProcess>
#include <QDesktopServices>
#include <QUrl>
#include <QList>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startButton_clicked()
{
    PackageInstaller *pi = new PackageInstaller;
    PackageInstaller::InstallationResult install = pi->installPackage(this);
    delete pi;
    switch (install){
    case PackageInstaller::InstallationResult::AlreadyInstalled:
        notifyUser(QMessageBox::Warning, "Пакет уже установлен!");
        break;
    case PackageInstaller::InstallationResult::Success:
        notifyUser(QMessageBox::Information, "Установка успешно завершена!");
        break;
    case PackageInstaller::InstallationResult::ErrorAdmin:
        notifyUser(QMessageBox::Critical, "Установка не завершена!\nНеобходимо запустить программу от имени администратора!");
        break;
    case PackageInstaller::InstallationResult::ErrorUnknown:
        notifyUser(QMessageBox::Critical, "Установка не завершена!\nНеизвестная ошибка!");
        break;
    }
}

void MainWindow::notifyUser(QMessageBox::Icon icon, QString text)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Результат установки");
    msgBox.setIcon(icon);
    msgBox.setText(text);
    msgBox.exec();
}



void MainWindow::on_closeApp_clicked()
{
    QCoreApplication::quit();
}

