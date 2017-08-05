#ifndef MANIFESTCONTROL_H
#define MANIFESTCONTROL_H
#include<QString>
#include<functional>
#include<qlist>
#include"manifestData.h"


class manifestControl
{
public:
    QList <DLinformation> informationList;
    QString manifestPath;
    QString urlPrefix;
    QString getDirectory(DLinformation,QString);
    manifestControl();
    manifestControl(QString);
    int parseManifest();
};

#endif // MANIFESTCONTROL_H
