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

    //    dlcontrol control("C:/Users/Mostafa/Desktop/download/");
    //    if(control.setQueue("C:/Users/Mostafa/Desktop/ario_pc_version.manifest")){

    //        control.startDownloading();
    //    }

    updateManagement manager;
    // manager.setMainFile("C:/Users/Mostafa/Desktop/download2/ario_pc_test.manifest","C:/Users/Mostafa/Desktop/download2/");
    // manager.update("C:/Users/Mostafa/Desktop/ario_pc_test.manifest","C:/Users/Mostafa/Desktop/download4/");
    // manager.update("C:/Users/Mostafa/Desktop/ario_pc_version.manifest");

    //keep all
 //   manager.setMainFile("C:/Users/Mostafa/Desktop/download - t1/ario_pc_test.manifest","C:/Users/Mostafa/Desktop/download - t1/");


    //replace CastleEvolution.txt
 //   manager.setMainFile("C:/Users/Mostafa/Desktop/download - t2/ario_pc_test.manifest","C:/Users/Mostafa/Desktop/download - t2/");

    //download g6c.mp3 (first delete g6c.mp3)
   // manager.setMainFile("C:/Users/Mostafa/Desktop/download - t3/ario_pc_test.manifest","C:/Users/Mostafa/Desktop/download - t3/");

    //delete LOST - Copy.mp3(first copy LOST.mp4
   // manager.setMainFile("C:/Users/Mostafa/Desktop/download - t4/ario_pc_test.manifest","C:/Users/Mostafa/Desktop/download - t4/");

    //downlaod history(first delete history) --CastleEvolution
    //replace Sound/campaign -- xc1s3.mp3 xc4s2end.mp3"
    //delete sound/scenario/ 4xcopy ha (first copy all)
    manager.setMainFile("C:/Users/Mostafa/Desktop/download - t5/ario_pc_test.manifest","C:/Users/Mostafa/Desktop/download - t5/");

    manager.update("C:/Users/Mostafa/Desktop/ario_pc_version.manifest");
    return a.exec();
}











