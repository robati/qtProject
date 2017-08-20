#include "dlmanager.h"


DLmanager* DLmanager::instanceSingleton = nullptr;

DLmanager::DLmanager()//must put aria2c.exe in debug/releasefolder
{
    process = new QProcess();
    program = "aria2c.exe";
    //program = "C:/Users/Mostafa/Desktop/aria2c.exe";
    downloadcomplete = 0;
}
void DLmanager::conncectProcess(std::function<void(int, QString)> _notify)
{
    connection_started = connect( process, &QProcess::started, [](){
        qDebug()<< "started";
    });

    connection_readyread = connect( process, &QProcess::readyReadStandardOutput, [this](){
        QString output;
        output = process->readLine();

        while(!output.isEmpty()){
            // qDebug()<<output;
            ParseOutput( output );
            output = process->readLine();
        }
    });

    connection_finished = connect( process, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)> (&QProcess::finished), [=](int exitCode, QProcess::ExitStatus ) {
        qDebug()<<"finished" << exitCode;
        disconncectProcess();
        _notify( exitCode , "finish code");

    });
    connection_error = connect(process, static_cast<void(QProcess::*)(QProcess::ProcessError)> (&QProcess::errorOccurred), [=](QProcess::ProcessError error) {
        qDebug()<<"*****errorOccurred" << error;
        _notify(911, "error ");
    });
    connection_statechanged = connect(process, &QProcess::stateChanged, [=](QProcess::ProcessState state) {
        qDebug()<<"****stateChanged" << state;
    });

}

void DLmanager::disconncectProcess(){

    QObject::disconnect(connection_started);
    QObject::disconnect(connection_readyread);
    QObject::disconnect(connection_finished);
    QObject::disconnect(connection_error);
    QObject::disconnect(connection_statechanged);
}


bool DLmanager::isCompelete(QString line){

    if(line.contains( "Download complete" )){
        int INDEX = line.indexOf( downloadPath);
        QString url = line.mid( INDEX + downloadPath.length()).left( line.mid( INDEX + downloadPath.length()).length()-1);
        qDebug()<< url<< downloadcomplete<< DLinformationMap[url];
        qDebug()<< informationList[ DLinformationMap[ url ]].URL<< informationList[ DLinformationMap[ url]].size;
        informationList[DLinformationMap[url]].setStatus( Downloaded);
        downloadcomplete += informationList[ DLinformationMap[ url]].size;
        return true;
    }
    return false;
}

void DLmanager::ParseOutput(QString line){

    isCompelete(line);

    QRegularExpression re_downloadLog("\\[(?<data>#.*)\\]");
    QRegularExpressionMatch downloadLogMatch = re_downloadLog.match(line);
    if (downloadLogMatch.hasMatch()) {

        QString downloadLogData = downloadLogMatch.captured("data");
        if(downloadLogData.split(' ').length()>3){
            QStringList infoprogress = downloadLogData.split(' ');
            qDebug()<< "**"<< infoprogress;
            QString dlpercent = downloadLogData.split(' ')[1];
            if(dlpercent.split('/').length() > 1){
                QString numerator = dlpercent.split('/')[0];
                qDebug()<< numerator;
                QRegularExpression re_downloadedFromthisFile("(?<number>\\d+\\.?\\d*)(?<unit>\\w+)");
                QRegularExpressionMatch downloadedFromthisFileMatch = re_downloadedFromthisFile.match(numerator);
                if ( downloadedFromthisFileMatch.hasMatch()) {
                    double digit = downloadedFromthisFileMatch.captured("number").toDouble();
                    QString unit = downloadedFromthisFileMatch.captured("unit");
                    CalculateProgress( digit, unit);
                }
            }
        }
    }
}

double DLmanager::CalculateProgress(double num,QString unit){
    int cf = 1024;
    if(unit == "MiB"){
        cf = 1048576;
    }
    else if(unit == "GiB"){
        cf = 1073741824;
    }

    int downloadedFromthisFile = num * cf;
    double progress = ((downloadcomplete + downloadedFromthisFile) / totalsize)* 100;

    qDebug()<< "progress"<< progress;
    qDebug()<< downloadedFromthisFile<< downloadcomplete<< totalsize;
    return progress;
}

void DLmanager::downlaod( QString dir, std::function<void( QString, int)> notify){
    qDebug()<< "startdl";
    QStringList arguments;
    arguments.clear();
    arguments<< "--input-file=" + dir << "--continue" << "--force-sequential=true" << "--max-concurrent-downloads=1" << "--max-tries=3";
    conncectProcess([=]( int finishCode , QString msg ){
        for(int i = 0; i < informationList.length(); i++){

            if(informationList[i].Status != Downloaded){
                dlerrorList.append( informationList[i] );
            }
        }
        qDebug()<< "dlerrorlist length"<< dlerrorList.length();
        notify( msg, finishCode);

    });

    process->start( program, arguments );
    process->waitForFinished();

}

void DLmanager::setdlPath(QString dlPath){
    downloadPath = dlPath;
}

void DLmanager::setinformationList(QList <DLinformation> list){

    downloadcomplete = 0;
    informationList = list;
    dlerrorList.clear();
    totalsize = 0;
    DLinformationMap.clear();
    for(int i = 0; i < list.length(); i++){
        DLinformationMap.insert( list[i].directory, list[i].id);
        totalsize += list[i].size;
    }

    qDebug()<<"totalsize="<<totalsize;
}


//-------------------------------------//singleton-------------------

DLmanager* DLmanager::getInstance() {
    if(instanceSingleton == nullptr){
        instanceSingleton = new DLmanager();
    }
    return instanceSingleton;
}
DLmanager::~DLmanager()
{
    delete instanceSingleton;
}
