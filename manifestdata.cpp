#include"manifestData.h"

bool DLinformation::match(DLinformation input){

    return(input.md5 == md5  &&  input.size == size);

}

bool DLinformation::operator==(DLinformation rhs){
    return URL == rhs.URL;
}

DLinformation::DLinformation(){
    Status = unknown;
}

void DLinformation::setStatus(downloadStatus state){
    Status = state;
}

downloadStatus DLinformation::getStatus(){
    return Status;
}

void DLinformation::setID(int number){
    id = number;
}
