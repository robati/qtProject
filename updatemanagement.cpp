#include "updatemanagement.h"
#include<QtDebug>
#include<QFile>
#include <QDir>
updateManagement::updateManagement()
{

}
void updateManagement::setMainFile(QString manifest,QString path){
     //path jayie ke dl mishe toosh
    mainFile=new dlcontrol(path);
    mainFile->setQueue(manifest);

}
void updateManagement::update(QString secondFile,QString newPath){
    manifestControl *newFile=new manifestControl(secondFile);
    QList <DLinformation> DLQueue;
    int queueLen=newFile->parseManifest();
    for(int i=0;i<queueLen;i++){
        if(mainFile->shouldBeDownloaded(newFile->informationList.at(i))){
            DLQueue.append(newFile->informationList.at(i));
        }
        else{
            QString mainfileAdd=mainFile->manifestDataManagement->getFilePath(newFile->informationList.at(i),mainFile->downloadPath);
            QString path=newFile->getFilePath(newFile->informationList.at(i),newPath);
            QDir dir(newFile->getDirectory(newFile->informationList.at(i),newPath));
            if (!dir.exists()) {
                dir.mkpath(".");
            }
            qDebug()<<QFile::copy(mainfileAdd, path);

        }

    }
    if(DLQueue.length()){
    downloadFiles=new dlcontrol(newPath);
    downloadFiles->setQueue(DLQueue,newFile->urlPrefix);
    qDebug()<<downloadFiles->manifestDataManagement->informationList.length();
    downloadFiles->startDownloading();}

}
