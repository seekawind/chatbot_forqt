#include"networkclass.h"
#include"database.h"
#include"control.h"
//    ApiClient *yp=nullptr;
//database *bp=nullptr;
void control:: write(QString answer){
    bp->insertTextWithTimestamp(answer);
}
//废弃函数
void control:: showtext (){

}
