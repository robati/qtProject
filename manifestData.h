#ifndef INFORMATION_H
#define INFORMATION_H
#include<QString>
//struct DLinformation{
class DLinformation{
public:
    QString URL;
    QString md5;
    double size;
    bool match(DLinformation);
    bool operator==(DLinformation rhs);
};


#endif // INFORMATION_H
