#ifndef DLCONTROL_H
#define DLCONTROL_H
#include"QString"
#include"manifestcontrol.h"
#include"manifestData.h"
class dlcontrol
{
public:
    dlcontrol(QString path);
    manifestControl * manifestDataManagement;
    int queueLen;
    int currentID;
    QString downloadPath;
    bool stop;
    bool setQueue(QString);
    void setQueue(QList <DLinformation> ,QString);
    void downloadNext();
    void startDownloading();
    bool downloadIfNotFound(DLinformation);
    bool shouldBeDownloaded(DLinformation);

};

#endif // DLCONTROL_H
