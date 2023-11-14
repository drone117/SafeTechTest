#include "packageinstaller.h"
#include <QProcess>
#include <QDir>
#include <QFile>
#include <QThread>
#include <QTextStream>
#include <QSettings>


PackageInstaller::PackageInstaller()
{

}

PackageInstaller::InstallationResult PackageInstaller::installPackage(QObject* parent)
{
    if (checkRegistry()){
        return InstallationResult::AlreadyInstalled;
    }
    QProcess *process = new QProcess(parent);
    process->startCommand(QString("cd %1").arg(QDir::currentPath()));
    process->waitForFinished(30000);
    process->startCommand(QString("msiexec.exe /i %1 /qn /l*v %2").arg(fileName, logName));
    if( !process->waitForStarted() ) {
        return InstallationResult::ErrorUnknown;
       }
//    QProcess::connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),[=](int exitCode, QProcess::ExitStatus exitStatus)
//        {
//          return parseFile();
//       });
    process->waitForFinished(30000);
    return parseFile();
}

bool PackageInstaller::checkRegistry()
{
    QSettings uninstallFolder("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\", QSettings::NativeFormat);
    QStringList installedPackages = uninstallFolder.childGroups();
    for (auto &packageName : installedPackages){
          uninstallFolder.beginGroup(packageName);
          QString displayName = uninstallFolder.value("DisplayName").toString();
          if(displayName.contains("КриптоПро CSP")){
              uninstallFolder.endGroup();
              return true;
          }
          uninstallFolder.endGroup();
    }
    return false;
}

PackageInstaller::InstallationResult PackageInstaller::parseFile()
{
    QFile fileLog;
    fileLog.setFileName(logName);
    QTextStream stream (&fileLog);
//    QDir::setCurrent("E:/");
    fileLog.open(QIODevice::ReadOnly);
    while (!stream.atEnd()){
          QString line = stream.readLine();
          if(line.contains("Для установки программного продукта необходимы права администратора.")){
              return InstallationResult::ErrorAdmin;
          }
          else if (line.contains("Операция установки успешно завершена.")){
              return InstallationResult::Success;
          }
    }
    fileLog.close();
    return InstallationResult::ErrorUnknown;

}
