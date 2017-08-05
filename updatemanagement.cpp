#include "updatemanagement.h"
#include<QtDebug>
#include<QFile>
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
//        else{
//            QString myfile=mainFile->manifestDataManagement->getDirectory(newFile->informationList.at(i));
//           qDebug()<<myfile;
//                    // QFile::copy(), newPath);
//        }

    }
    qDebug()<<DLQueue.length();
    downloadFiles=new dlcontrol(newPath);
    downloadFiles->setQueue(DLQueue,newFile->urlPrefix);
    qDebug()<<downloadFiles->manifestDataManagement->informationList.length();
    downloadFiles->startDownloading();

}
