#include <QCoreApplication>
#include<QFile>
#include<QDebug>
#include <QJsonObject>
#include<QJsonDocument>
#include<QJsonArray>
#include "manifestData.h"
#include "manifestcontrol.h"
#include<QString>
#include <functional>


manifestControl::manifestControl()
{

}
manifestControl::manifestControl(QString manifestAddress)
{
this->manifestPath=manifestAddress;
}
int manifestControl::parseManifest(){


    QByteArray filedata;
    QFile file;
    file.setFileName(this->manifestPath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    filedata = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(filedata.data());
    QJsonObject documentobj = document.object();
    urlPrefix= documentobj.value("packageUrl").toString();
    QJsonValue  valueMessage = documentobj.value("assets");  //&
    QJsonObject objMessage = valueMessage.toObject();
    QString path;
    int index;
    if(objMessage.keys().size()==0){
        //if there's no file in manifest
        return 0;
    }
    for(int i=0; i<objMessage.keys().size(); i++){
        DLinformation temp;
        path=objMessage.keys()[i];
        temp.URL=urlPrefix+path;
        temp.md5=objMessage.value(path).toObject().value("md5").toString();
        temp.size=objMessage.value(path).toObject().value("size").toDouble();

        informationList.append(temp);
        index=i;
    }
    if(index==objMessage.keys().size()-1)
        //if all files in manifest are appended in list
         return (objMessage.keys().size());


}
QString manifestControl::getDirectory(DLinformation input,QString mydirectory){
    QString a= mydirectory+input.URL.mid(urlPrefix.length(),input.URL.lastIndexOf('/')-urlPrefix.length());
   // qDebug()<<a;
    return a;


}
QString manifestControl::getFilePath(DLinformation input,QString mydirectory){
    QString a= mydirectory+input.URL.mid(urlPrefix.length());//,input.URL.lastIndexOf('/')-urlPrefix.length());
   // qDebug()<<a;
    return a;


}

