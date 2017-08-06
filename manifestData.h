#ifndef INFORMATION_H
#define INFORMATION_H
#include<QString>
enum updateStatus{download,replace,keep,extra,unknown};
class DLinformation{
public:
    QString URL;
    QString md5;
    double size;
    updateStatus Status;
    QString directory;
    DLinformation();
    bool match(DLinformation);
    bool operator==(DLinformation rhs);
};


#endif // INFORMATION_H
