#ifndef MOUNT_H
#define MOUNT_H
#include <iostream>
#include <string>
#include "mkdisk.h"
#include "Fdisk.h"


using namespace std;
class mount
{
public:
    
    string path;//Este parámetro será la ruta en la que se encuentra el disco que se montará en el sistema.
    string name;//Indica el nombre de la partición a cargar.
   
    mount();
    void montar(mount *disk);
    void mostrarMount();
    void desmontar(string id);
};
#endif