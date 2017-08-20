#include <QCoreApplication>
#include<qprocess.h>
#include<qdebug.h>
#include <QDir>
#include <QObject>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <functional>
#include <QCoreApplication>
#include"dlmanager.h"
#include"manifestcontrol.h"

#include"manifestData.h"
#include"updatemanagement.h"




int main(int argc,char** argv)
{
    QCoreApplication a(argc, argv);



    QString downloadpath = "C:/Users/Mostafa/Desktop/Aladdin/";
    QString infile = "C:/Users/Mostafa/Desktop/file.txt";
    QString originalManifestname = "C:/Users/Mostafa/Desktop/ario_pc_game (4).manifest";
    QString newManifestname="C:/Users/Mostafa/Desktop/ario_pc_game .manifest";
    QFile *originalManifest=new QFile(originalManifestname);
    QFile *newManifest=new QFile(newManifestname);
    //    download

        manifestControl* manifestDataManagement = new manifestControl( originalManifest);
        manifestDataManagement->createinputFile(infile, downloadpath);

        DLmanager::getInstance()->setinformationList( manifestDataManagement->informationList);
        DLmanager::getInstance()->setdlPath( downloadpath);
        DLmanager::getInstance()->downlaod( infile, [=](QString message,int finishCode){
            qDebug()<< message<< finishCode;

            int counter = DLmanager::getInstance()->dlerrorList.length();
            for(int i = 0; i < counter; i++){
                qDebug() <<"error" << DLmanager::getInstance()->dlerrorList[i].directory << DLmanager::getInstance()->dlerrorList[i].Status;
            }
        });



    //   updatemanager;


    updateManagement manager;

    manager.setMainFile(originalManifest,downloadpath);
    manager.update(newManifest);

    return a.exec();
}










