#include "dlcontrol.h"
#include"dlmanager.h"
#include"manifestcontrol.h"
#include"dlcontrol.h"
#include<QDebug>



dlcontrol::dlcontrol(QString path)
{
    downloadPath=path;
    queueLen=0;
    currentID=0;
    stop=1;

}

bool dlcontrol::setQueue(QString manifest){
    //this function reads the manifest file and creates manifestDataManagement.informationlist
    //that contains manifestData object for every downloadURL in manifest
    //returns false if no downloadURL found.
    manifestDataManagement=new manifestControl(manifest);
    queueLen=manifestDataManagement->parseManifest();
    qDebug()<<manifest<<queueLen;
    return queueLen==0?0:1;

}
void dlcontrol::setQueue(QList <DLinformation> informationList,QString prefix){

    manifestDataManagement=new manifestControl();
    manifestDataManagement->informationList=informationList;
    manifestDataManagement->urlPrefix=prefix;
    queueLen=informationList.length();

}

void dlcontrol::downloadNext(){
    //this function downloads every url in manifest list sequentially
    //if the last download was successful and stop is false
    DLinformation currentDownload=manifestDataManagement->informationList[currentID];
    DLmanager::getInstance()->downlaod( currentDownload.URL,manifestDataManagement->getDirectory(currentDownload,downloadPath), [=](QString debugstr,int exitcode){
        if(exitcode==0){
              qDebug()<<queueLen<<currentID<<exitcode;
            qDebug()<<manifestDataManagement->informationList[currentID].URL;
            if(!stop&&currentID<queueLen-1){
                qDebug()<<currentID;
                currentID++;
                downloadNext();

            }
            else{
                qDebug()<<"ok";
            }
        }

    });

}
void dlcontrol::startDownloading(){
    //starts downloading sequence
    stop=0;
    downloadNext();

}

