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
    qDebug()<<queueLen;
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
bool dlcontrol::downloadIfNotFound(DLinformation input){
    //this function will download the input url if
    //it is not found in manifest informationlist or
    //it exist in the list but has different md5/size and returns 1
    int index;
    index=manifestDataManagement->informationList.indexOf(input);
    if(index!=-1){
        if(input.match(manifestDataManagement->informationList.at(index))){
            qDebug()<<"matched";
            return 0;}

    }
    qDebug()<<"here"<<input.URL;
    qDebug()<< manifestDataManagement->getDirectory(input,downloadPath);
    DLmanager::getInstance()->downlaod( input.URL,manifestDataManagement->getDirectory(input,downloadPath), [=](QString debugstr,int exitcode){});
    return 1;

}
bool dlcontrol::shouldBeDownloaded(DLinformation input){
    //if file exist correctly returns 0 else returns 1
    int index;
    index=manifestDataManagement->informationList.indexOf(input);
    if(index!=-1){
        if(input.match(manifestDataManagement->informationList.at(index))){
            qDebug()<<"matched";
            return 0;}

    }
    return 1;
}
