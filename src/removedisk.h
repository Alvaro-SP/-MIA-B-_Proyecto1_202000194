#ifndef REMOVEDISK_H
#define REMOVEDISK_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*Este parámetro elimina un archivo que representa a un disco duro mostrando
un mensaje de confirmación para eliminar*/
class removedisk
    {
    public:
        removedisk();
        void removeDisco(string rutaArchivo);


    };
#endif 