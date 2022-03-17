#ifndef MOUNT_H
#define MOUNT_H
#include <iostream>
#include <string>
#include "mkdisk.h"
#include "Fdisk.h"


// using namespace std;
class mount
{
public:
    
    string path;//Este parámetro será la ruta en la que se encuentra el disco que se montará en el sistema.
    string name;//Indica el nombre de la partición a cargar.
   
    mount();
    MBR* obtainMBR(char path[]);
    EBR* primerEBR(MBR *disco,string paths);
    void desmontar(char id[]);
    char* obtainKey( int numero, char letra);
    void montar(mount *disk);
    // void montar(char[],char[]);
    void mostrarMount();
    void desmontar(string id);
};
#endif