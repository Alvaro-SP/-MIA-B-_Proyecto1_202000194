#ifndef FDISK_H
#define FDISK_H

#include <string.h>
#include <string>
#include <iostream>

using namespace std;
class Fdisk
{
public:
    Fdisk();

    int size;
    string unit;
    string path;
    string type;
    string fit;
    string deleted;
    string name;
    string add;
    // int searchLogicPartitionsDelete(Fdisk *disco, FILE *archivo, int inicio);
    EBR createnewEBR();   
    void CreatePartition(Fdisk *disco);
    void ExtendPartition(Fdisk *disco);
    void deleteFast(FILE *archivo, int pos);
    void deleteFull(FILE *archivo, int pos);
    int searchLogicPartitionsDelete(Fdisk *disco, FILE *archivo, int inicio);
    void DeletePartition(Fdisk *disco);
    bool StateInactiveCreate(int i, int espacio_disp, MBR mbr, int p_gen_tam, bool p_existe , Fdisk *disco, FILE *archivo, int hayespaciodisp);         
    void genrep();
    bool isExtended(string tipoParticion,MBR mbr,Fdisk *disco);
    void crearPrimariaExtendida(MBR mbr,Fdisk *disco,int p_gen_tam,bool p_existe, FILE *archivo);
    void adminPartition(Fdisk *disco);
    void ExtendPartition(FILE *archivo, int cantidad, int inicio);
    void searchLogica(int tam_part,Fdisk *disco, FILE *archivo, int start, int total);
    int searchname(FILE *archivo, int inicio, string nombre);
};
#endif // FDISK_H