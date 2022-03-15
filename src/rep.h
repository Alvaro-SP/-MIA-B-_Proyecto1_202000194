#ifndef REP_H
#define REP_H
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include "mkdisk.h"
using namespace std;

class rep
{
public:
    rep();
    MBR* obtainMBR(char path[], string id);
    void disk(string nombres, string idi, string paths,string path_reports);
    bool isvalidDirectory(const char *path);
        vector<string> splitSimulated(string str, char pattern);
    void mbr(string nombre, string id, string rutaParticion, string nombreArchivo);
    EBR* primerEBR(MBR *disco,char path[]);
   
};

#endif // REPORTE_H