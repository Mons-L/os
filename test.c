#include<stdio.h>
#include<stdlib.h>


int main(int argc, char *argv[]){
    /*printf("%d\n",argc);
    for(int i=0; i<argc; i++){
        printf("arg%d=%s\n",i,argv[i]);
    }*/

    if(argc ==2){
        if(argv[1][0] == '-' && argv[1][1] == 'i'){
            //Gerer le mode interactif
            printf("C'est le mode interactif\n");
        }
        else if(argv[1][0] == '-' && argv[1][1] == 'f'){
            printf("C'est le mode batch\n");
            //Recupere le chemin du fichier

            //Faire le mode batch
        }
        else{
            printf("Option non reconnue.\n");
            printf("%s\n",argv[1]);
        }
    }
    else{
        printf("C'est le mode CLI\n");
        //Faire la ligne de commande
    }
    return 0;
}
