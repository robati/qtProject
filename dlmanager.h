#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <functional>
#include <QDebug>
#include <QDir>
#include <QObject>
#include <QProcess>
#include<QRegularExpression>
#include"manifestData.h"

class DLmanager : public QObject
{
    Q_OBJECT

public:
    QProcess *process;
    QString program;
    QString downloadPath;
    QList < DLinformation > informationList;
    //QList <DLinformation> downloadsuccess;
    QList < DLinformation > dlerrorList;
    QMap < QString, int > DLinformationMap;
    double totalsize;
    double downloadedFromthisFile;
    double downloadcomplete;
    void conncectProcess( std::function<void( int, QString)> _notify);
    void disconncectProcess();
    void ParseOutput(QString line);
    bool isCompelete(QString line);
    void downlaod(QString dir,std::function<void( QString, int)> notify);
    static DLmanager* getInstance() ;
    void setdlPath(QString dlPath);
    void setinformationList(QList < DLinformation > list);
    double CalculateProgress( double , QString );

private:
    static DLmanager *instanceSingleton;
    DLmanager();
    ~DLmanager();
    QMetaObject::Connection connection_started, connection_readyread, connection_finished, connection_error, connection_statechanged;
};

#endif // CONNECTOR_H
