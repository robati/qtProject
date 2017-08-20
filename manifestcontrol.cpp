#include "manifestcontrol.h"



manifestControl::manifestControl(QString urlprefix)
{
    urlPrefix=urlprefix;
   // parseManifest();
}
manifestControl::manifestControl(QFile *manifestFile)
{
   // manifestPath = manifestAddress;
    parseManifest(manifestFile);
}
int manifestControl::parseManifest(QFile *file){


    QByteArray filedata;
    //QFile file;
    //file.setFileName(this->manifestPath);
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    filedata = file->readAll();
    file->close();

    QJsonDocument document = QJsonDocument::fromJson(filedata.data());
    QJsonObject documentobj = document.object();
    urlPrefix= documentobj.value("packageUrl").toString();
    QJsonValue  valueMessage = documentobj.value("assets");
    QJsonObject objMessage = valueMessage.toObject();
    QString path;
    int index;
    if(objMessage.keys().size() == 0){
        //if there's no file in manifest
        return 0;
    }

    for(int i = 0; i < objMessage.keys().size(); i++){
        DLinformation temp;
        path= objMessage.keys()[i];
        temp.directory= path;
        temp.URL= urlPrefix + path;
        temp.md5= objMessage.value(path).toObject().value("md5").toString();
        temp.size= objMessage.value(path).toObject().value("size").toDouble();
        temp.id= i;
        informationList.append(temp);
        index= i;
    }
    qDebug()<<"files in the manifest";
    qDebug()<<objMessage.keys().size();

    if(index == objMessage.keys().size()-1){
        //if all files in manifest are appended in list
        count=objMessage.keys().size();
        return count;
    }

    return 0;
}

QString manifestControl::getDirectory(DLinformation input,QString mydirectory){
    QString destinationFolderDir = mydirectory + input.directory;
    QFileInfo dir(destinationFolderDir);
    QString temp = dir.absoluteDir().absolutePath();
    return temp;


}

void manifestControl::composedownloadList(QList <DLinformation> DLQueue,QString downloadDirectory,QString infile){
    //creates an input file using a qlist of DLinformation .
    for(int i=0; i < DLQueue.length(); i++){
        DLQueue[i].setID(i);
    }
    informationList=DLQueue;
    createinputFile(infile, downloadDirectory);

}
void manifestControl::createinputFile(QString filename,QString downloadDirectory){
    //creates an input file from the informationList .
    QFile file(filename);
    file.resize(0);
    int queueLen = informationList.length();
    qDebug()<< "queueLen"<< queueLen;
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        for(int i = 0; i < queueLen; i++){
            stream << informationList[i].URL<< endl;
            stream<<"\tdir="<<getDirectory(informationList[i], downloadDirectory)<< endl;
            stream<<"\tchecksum=md5="<<informationList[i].md5<< endl;
        }

    }
}



