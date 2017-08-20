#ifndef INFORMATION_H
#define INFORMATION_H
#include<QString>
enum downloadStatus{unknown,Downloaded};
class DLinformation{
public:
    QString URL;
    QString md5;
    double size;
    int id;
    downloadStatus Status;
    QString directory;
    DLinformation();
    bool match(DLinformation);
    bool operator==(DLinformation rhs);
    void setStatus(downloadStatus);
    void setID(int number);
    downloadStatus getStatus();
};


#endif // INFORMATION_H
