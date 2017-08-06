#ifndef UPDATEMANAGEMENT_H
#define UPDATEMANAGEMENT_H
#include"manifestcontrol.h"
#include"dlcontrol.h"
#include<QString>

class updateManagement
{
public:
    updateManagement();
    QString downloadPath;
    manifestControl *mainFile;
    dlcontrol *downloadFiles;
    void setMainFile(QString, QString);
    void update(QString,QString);
    void update(QString);
};

#endif // UPDATEMANAGEMENT_H
