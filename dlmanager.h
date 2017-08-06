#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QCoreApplication>
#include<qprocess.h>
#include<qdebug.h>
#include <QDir>
#include <QObject>
#include <QProcess>


class DLmanager : public QObject
{
    Q_OBJECT
public:
    QProcess *process;
    QStringList arguments;
    QString program;
    void conncectProcess(std::function<void(int, QString)> _notify);
    void startDownload(std::function<void(QString,int)> notify);
    bool includesDetail(QString line);
    void downlaod(QString url, QString dir, std::function<void(QString, int)> mainnotify);
    static DLmanager* getInstance() ;
private:
    static DLmanager *instanceSingleton;
    DLmanager();
    ~DLmanager();
	QMetaObject::Connection connection_started, connection_readyread, connection_finished, connection_error, connection_statechanged;
};

#endif // CONNECTOR_H
