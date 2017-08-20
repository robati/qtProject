#ifndef UPDATEMANAGEMENT_H
#define UPDATEMANAGEMENT_H
#include <QDir>
#include<QFile>
#include<QString>
#include<QtDebug>
#include"dlmanager.h"
#include"manifestcontrol.h"
class updateManagement
{
public:
    updateManagement();
    QString updateFolder;
    QString gameFolder;
    manifestControl *mainFile;
    void setMainFile(QFile* manifest, QString gamepath);
    void update(QFile *second);
    void finalize(QList <DLinformation> ,QList <DLinformation>);
    void downloadandFinalize(QList <DLinformation> dlQueue, QList<DLinformation> deleteQueue, manifestControl *newFile);
    bool moveDownloadfiles(QList <DLinformation> moveQueue);
    bool deleteExtraFiles(QList <DLinformation> deleteQueue);
    bool deleteUpdateFolder();


};

#endif // UPDATEMANAGEMENT_H
