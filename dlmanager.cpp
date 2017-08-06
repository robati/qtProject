#include "dlmanager.h"
#include <QCoreApplication>
#include<qprocess.h>
#include<qdebug.h>
#include <QDir>
#include <QObject>
#include <QProcess>
#include <functional>
DLmanager* DLmanager::instanceSingleton = nullptr;
DLmanager::DLmanager()
{
    process=new QProcess();
    program = "C:/Users/Mostafa/Desktop/aria2c.exe";
}
void DLmanager::conncectProcess(std::function<void(int, QString)> _notify){

	connection_started = connect(process, &QProcess::started, [](){
       // qDebug()<<"started";
    });

	connection_readyread = connect(process, &QProcess::readyReadStandardOutput, [this](){
        QString output;
        output=process->readLine();
        while(!output.isEmpty()){
            if(includesDetail(output)){
                qDebug()<<output.mid(90);

            }
            output=process->readLine();
        }
    });

	connection_finished = connect(process, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)> (&QProcess::finished), [=](int exitCode, QProcess::ExitStatus exitStatus) {
         qDebug()<<"finished" << exitCode;
		 _notify(exitCode, "finish signal connection established");
       
    });
	connection_error = connect(process, static_cast<void(QProcess::*)(QProcess::ProcessError)> (&QProcess::errorOccurred), [=](QProcess::ProcessError error) {
        qDebug()<<"*****errorOccurred" << error;
    });
	connection_statechanged = connect(process, &QProcess::stateChanged, [=](QProcess::ProcessState state) {
     //   qDebug()<<"****stateChanged" << state;
    });
}


bool DLmanager::includesDetail(QString line){
    QRegExp detail("\\[#[0-9a-z]{6}");
    detail.setMinimal(true);
    int pos = detail.indexIn(line);
    if (pos > -1)
        return 1;
    return 0;
}
void DLmanager::downlaod(QString url, QString dir, std::function<void(QString, int)> mainnotify){
    qDebug() << "startdl";
    arguments.clear();
    arguments << "--dir="+dir;
    arguments << url;
    conncectProcess([mainnotify, this](int exitcode, QString str){
        QObject::disconnect(connection_started);
        QObject::disconnect(connection_readyread);
        QObject::disconnect(connection_finished);
        QObject::disconnect(connection_error);
        QObject::disconnect(connection_statechanged);
        mainnotify("hello from dlmanager",exitcode);
    });
    process->start(program, arguments);
   // qDebug()<<"i am downloading"<<arguments[1];
    process->waitForFinished();


}

//-------------------------------------//singleton-------------------
DLmanager::~DLmanager(){}
DLmanager* DLmanager::getInstance() {
    if(instanceSingleton == nullptr){
        instanceSingleton = new DLmanager();
    }
    return instanceSingleton;
}
