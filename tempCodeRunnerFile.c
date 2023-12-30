#include <stdio.h>
#include <stdlib.h>


void menu(){
    printf("*******************************");
    printf("*********1. guess numbers *****");
    printf("*********0. quit          *****");
    printf("*******************************");
}

void game(){

}
int main(){
int input = 0;
    do{     
        menu();
        scanf("%d\n", &input);
        switch (input)
        {
        case 1:
            game();
            break;
        
        case 0:
            printf("exit!");
            break;
    
        default:
            printf("wrong selection, please reselect.");
            break;
        }
    }while (input);
    
}