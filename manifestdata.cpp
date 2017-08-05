#include"manifestData.h"

bool DLinformation::match(DLinformation input){

    return(input.md5==md5 && input.size==size);

}
bool DLinformation::operator==(DLinformation rhs){
    return URL==rhs.URL;
}
