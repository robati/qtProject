#include <QCoreApplication>
#include<qprocess.h>
#include<qdebug.h>
#include <QDir>
#include <QObject>
#include <QProcess>
#include <functional>
#include"dlmanager.h"
#include"manifestcontrol.h"
#include"dlcontrol.h"
#include"manifestData.h"
#include"updatemanagement.h"


int main(int argc,char** argv)
{
    QCoreApplication a(argc, argv);

//    dlcontrol control("C:/Users/Mostafa/Desktop/download2/");
//    //control.downloadPath="C:/Users/Mostafa/Desktop/download2/";
//    if(control.setQueue("C:/Users/Mostafa/Desktop/ario_pc_test.manifest")){

//        control.startDownloading();
//    }

    updateManagement manager;
    manager.setMainFile("C:/Users/Mostafa/Desktop/download2/ario_pc_test.manifest","C:/Users/Mostafa/Desktop/download2/");
    manager.update("C:/Users/Mostafa/Desktop/ario_pc_test.manifest","C:/Users/Mostafa/Desktop/download4/");

    // qDebug()<<QFile::copy("C:/Users/Mostafa/Desktop/download2/Campaign/Media/C4S4_BEG.SLP","C:/Users/Mostafa/Desktop/download4/Campaign/Media/C4S4_BEG.SLP");
    return a.exec();
}











