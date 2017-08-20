#ifndef MANIFESTCONTROL_H
#define MANIFESTCONTROL_H


#include <functional>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <qlist>
#include <QString>
#include <QString>

#include "manifestData.h"

class manifestControl
{
public:
    QList < DLinformation> informationList;
    QString manifestPath;
    QString urlPrefix;
    QString getDirectory( DLinformation, QString);
    int count;
    manifestControl(QString urlprefix);
    manifestControl(QFile *manifestFile);
    int parseManifest(QFile *manifestFile);
    void createinputFile(QString filename,QString downloaddir);
    void composedownloadList(QList < DLinformation> DLQueue, QString downloadpath, QString infile);

};

#endif // MANIFESTCONTROL_H
