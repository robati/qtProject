#include "updatemanagement.h"

updateManagement::updateManagement()
{

}
void updateManagement::setMainFile(QFile* manifest,QString gamepath){
    //path jayie ke dl mishe toosh
    gameFolder = gamepath;
    updateFolder = gameFolder.left(gameFolder.length()-1) + "update/";
    mainFile = new manifestControl(manifest);

}

void updateManagement::update(QFile* secondFile){


    manifestControl *newgameManifest = new manifestControl(secondFile);
    QList < DLinformation> DLQueue;
    QList < DLinformation> deleteQueue;
    int newManifestLen = newgameManifest->count;


    for(int i = 0; i < newManifestLen; i++){
        DLinformation newItem = newgameManifest->informationList[i];
        int index = mainFile->informationList.indexOf(newItem);
        qDebug()<< index;

        if(index!=-1){
            qDebug()<<"found";
            DLinformation lastfile = mainFile->informationList[index];
            qDebug()<< lastfile.URL;
            if(newItem.match(lastfile)){
                qDebug()<<"matched";
            }
            else{
                DLQueue.append(newItem);
                deleteQueue.append(lastfile);
                qDebug()<<"delete and add to download queue ";
            }
        }
        else{
            DLQueue.append(newItem);
            qDebug()<<"doesnt Exist download queue";
        }

    }

    for(int i = 0; i < mainFile->informationList.length(); i++){
        DLinformation newItem = mainFile->informationList[i];
        int index = newgameManifest->informationList.indexOf(newItem);
        if(index == -1){
            qDebug()<< newItem.URL;
            deleteQueue.append(newItem);
            qDebug()<< "extra and removed";
        }
    }

    downloadandFinalize(DLQueue,deleteQueue,newgameManifest);

}

bool updateManagement::moveDownloadfiles(QList <DLinformation> moveQueue){

    QString updateFileName;
    QString destinationFileName;
    QString destinationFolderDir;

    bool errorFlag = false;

    qDebug()<<"files to be moved";
    qDebug()<<moveQueue.length();

    for(int i=0;i<moveQueue.length();i++){
		
		updateFileName = updateFolder + moveQueue[i].directory;
		destinationFileName = gameFolder + moveQueue[i].directory;
        QFile updatedir(updateFileName);
		if(updatedir.exists()){

            QFileInfo dir(destinationFileName);
            destinationFolderDir = dir.absoluteDir().absolutePath();
            QDir destinationFolder(destinationFolderDir);

            if (!destinationFolder.exists()) {
                destinationFolder.mkpath(".");
            }

            QFile checkfile(destinationFileName);
            if(checkfile.exists()){
                checkfile.close();
                checkfile.remove();
            }
            if(!updatedir.rename(updateFileName,destinationFileName)){
                qDebug()<<"renaming failed";
                errorFlag = true;
            }

        }
        else{
            qDebug() << "rename file doesnt exist" << updateFileName;
            errorFlag = true;
        }
    }

    return !errorFlag;
}

bool updateManagement::deleteExtraFiles(QList <DLinformation> deleteQueue){

    QString destinationFileName;

    qDebug()<<"delete files";
    qDebug()<<deleteQueue.length();

    bool errorFlag = false;

    for(int i = 0; i < deleteQueue.length(); i++){

		destinationFileName = gameFolder + deleteQueue[i].directory;

        QFile deleteFile(destinationFileName);
        QFile deleteAriaFile(destinationFileName + ".aria2");

        if(deleteFile.exists()){
            deleteFile.close();
            if(!deleteFile.remove()){
                qDebug()<<"delete failed";
                errorFlag = true;
            }
        }
        else {
            qDebug()<<"deleteFile doesnt exist"<<destinationFileName;
            errorFlag = true;
        }

        if(deleteAriaFile.exists()){
            deleteFile.close();
            deleteAriaFile.remove();
        }
    }
    return !errorFlag;
}
void updateManagement::downloadandFinalize(QList <DLinformation> DLQueue,QList <DLinformation> deleteQueue,manifestControl *newManifest){

    if(DLQueue.length()){
        QString updateInputFile = gameFolder.left( gameFolder.length()-1)+"newfile.txt";
        manifestControl* manifestDataManagement=new manifestControl( newManifest->urlPrefix);
        manifestDataManagement->composedownloadList( DLQueue, updateFolder, updateInputFile);

        DLmanager::getInstance()->setinformationList(manifestDataManagement->informationList);
        DLmanager::getInstance()->setdlPath(updateFolder);
        DLmanager::getInstance()->downlaod(updateInputFile,[DLQueue, deleteQueue, this](QString message,int finishCode){
            qDebug()<< message<< finishCode;
            if(finishCode == 0){
                finalize(DLQueue,deleteQueue);
            }
            else{
                qDebug()<< "download problem";
            }
        });

        QFile file(updateInputFile);
        //file.remove();
    }
    else{
        qDebug()<< "no Download ";
        finalize(DLQueue,deleteQueue);
    }
}
void updateManagement::finalize(QList <DLinformation> DLQueue,QList <DLinformation>deleteQueue){
    qDebug()<<"finial";
    deleteExtraFiles(deleteQueue);
    if(moveDownloadfiles(DLQueue))
        deleteUpdateFolder();
    qDebug()<<"done.";
}

bool updateManagement::deleteUpdateFolder(){
    QDir updatedir(updateFolder);
    if(updatedir.exists())
        if(updatedir.removeRecursively())
            return true;
    return false;
}


