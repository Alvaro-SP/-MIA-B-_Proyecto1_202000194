#ifndef MKFS_H
#define MKFS_H

#include <iostream>
#include <string>
#include <string.h>
#include "mkdisk.h"

using namespace std;

class mkfs
{

public:
    string id; //Indicará el id que se generó con el comando mount.
    string type;//Indicará que tipo de formateo se realizará.
    string fs; //Indica el sistema de archivos a formatear.
    mkfs();

    void formato(mkfs *disco);
    void EXT2format(mkfs *disco);
    void EXT3format(mkfs *disco);
    MountedPart* obtainMountedPart(string idi);
    DISKMOUNT* obtainMountedDisk(string idi);
};

#endif // MKFS_H