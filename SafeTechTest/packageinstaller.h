#ifndef PACKAGEINSTALLER_H
#define PACKAGEINSTALLER_H
#include "qobject.h"

class PackageInstaller
{
public:
    PackageInstaller();
    enum class InstallationResult{
        AlreadyInstalled,
        Success,
        ErrorAdmin,
        ErrorUnknown
    };
    InstallationResult installPackage(QObject* parent);
    bool checkRegistry();
    InstallationResult parseFile();
private:
    QString fileName = "csp-x64-rus.msi";
    QString logName = "installLog.txt";
};

#endif // PACKAGEINSTALLER_H
