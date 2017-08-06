#include "updatemanagement.h"
#include<QtDebug>
#include<QFile>
#include <QDir>
updateManagement::updateManagement()
{

}
void updateManagement::setMainFile(QString manifest,QString path){
     //path jayie ke dl mishe toosh
    downloadPath=path;
    mainFile=new manifestControl(manifest);
    mainFile->parseManifest();

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
            QString mainfileAdd=mainFile->getFilePath(newFile->informationList.at(i),downloadPath);
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
void updateManagement::update(QString secondFile){
    manifestControl *newFile=new manifestControl(secondFile);
    QList <DLinformation> DLQueue;
    int queueLen=newFile->parseManifest();
    qDebug()<<secondFile<<queueLen;

    for(int i=0;i<queueLen;i++){
        DLinformation myfile=newFile->informationList.at(i);
        int index=mainFile->informationList.indexOf(myfile);
        qDebug()<<index;
        if(index!=-1){
            qDebug()<<"found";
            DLinformation lastfile=mainFile->informationList.at(index);
            qDebug()<<lastfile.URL;
            if(myfile.match(lastfile)){
                qDebug()<<"matched";
                }
            else{
                QDir dir2;
                dir2.remove(mainFile->getFilePath(lastfile,downloadPath));
                DLQueue.append(myfile);
                qDebug()<<"remove add to Queue";
            }


        }
        else{
            qDebug()<<"doesnt Exist add to Queue";
        DLQueue.append(myfile);
        }

        }
    for(int i=0;i<mainFile->informationList.length();i++){
        DLinformation myfile=mainFile->informationList.at(i);
        int index=newFile->informationList.indexOf(myfile);
        qDebug()<<myfile.URL<<index;
        if(index==-1){
        QDir dir2;
        dir2.remove(mainFile->getFilePath(myfile,downloadPath));
        qDebug()<<"extra and removed";
        }


    }

    if(DLQueue.length()){
        downloadFiles=new dlcontrol(downloadPath);
        downloadFiles->setQueue(DLQueue,newFile->urlPrefix);
        qDebug()<<downloadFiles->manifestDataManagement->informationList.length();
        downloadFiles->startDownloading();
    }


//    }
}


