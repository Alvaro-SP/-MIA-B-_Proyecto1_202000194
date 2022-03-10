#include "mount.h"
#include "v.h"
#include <cstdio>

mount::mount() {}

MBR* mount::obtainMBR(char path[]){
    FILE *myFile;
    myFile = fopen(path,"rb+");
    if(myFile!=NULL){
        
    }else{
        cout<<"FFFFFFF no se encuentra el disco FFFFFF\n";
        return NULL;
    }
    fseek(myFile, 0, SEEK_SET);
    MBR *mbr = (MBR*)malloc(sizeof(MBR));
    fread(mbr,sizeof(MBR),1,myFile);
    fclose(myFile);
    return mbr;
}

char* mount::obtainKey( int numero, char letra){
    string key("94");
    key+=to_string(numero);
    key+=letra;    
    return &key[0];
}

//! ███████████████████████████████████████████  MOUNT.  ██████████████████████████████████████████
void mount::montar(mount *disk){
    int contador = 0;
    bool existeono= false;
    
   //* VALIDACION SI EXISTE LA PARTICION DENTRO DE LAS QUE YA ESTAN MONTADAS
    while(partsMounted[contador]!=NULL){

        
        if(strcmp(partsMounted[contador]->path, disk->path.c_str() )==0){
            existeono = true;
            break;
        }
        contador++;
    }
    if(!existeono){
        //* Si no esta montada la particion se crea un montaje con sus atributos
        partsMounted[contador] = new DISKMOUNT();
        strcpy(partsMounted[contador]->path,disk->path.c_str());
        partsMounted[contador]->letter = 65+contador; //manipulacion de mis letras usando los ASCII
    }
    


    bool existPart = true;
    //! se hace instancia de los discos que estan montados 
    DISKMOUNT *mdisk = partsMounted[contador];
    int contador2=0;
    //* Si ya esta montada la particion no da ningun problema 
    while(mdisk->parts[contador2]!=NULL){
        if(strcmp(mdisk->parts[contador2]->name,disk->name.c_str())==0){
            cout<<"FFFFFFFFF Error al montar la particion, ya existe un nombre igual "<<disk->name<<"  FFFFFFFFF"<<endl;
            return;
        }
        contador2++;
    }
    //*Busco y abro el MBR desde la ruta del disco
    MBR *disco = obtainMBR(mdisk->path);
    if(disco==NULL){
        return ;
    }
    //! se busca particion primaria 
    int i;
    int init;
    for(i=0;i<4;i++){
        if(strcmp(disco->mbr_p[i].part_name,disk->name.c_str())==0){
            existPart = false;
            init = disco->mbr_p[i].part_start;
            break;
        }
    }
    //! si hay una particion entonces se va a agregar una particion montada ...
    if(!existPart){
         mdisk->parts[contador2] = new MountedPart();
         char *key=obtainKey(contador2, mdisk->letter);
         strcpy(mdisk->parts[contador2]->id,key);
         strcpy(mdisk->parts[contador2]->name, disk->name.c_str());
         mdisk->parts[contador2]->start = init;
    }else{
        cout<<"FFFFFFFFF Error al montar la particion, porque la particion "<<disk->name<<" No Existe  FFFFFFFFF"<<endl;
        return ;
    }
  
    cout<<"Se ha montado la particion: "<<disk->name<<" correctamente, Bravho!!"<<endl;
    return ;
}

//! ███████████████████████████████████████████  UNMOUNT.  ██████████████████████████████████████████

void mount::desmontar(char id[]){
    string str(id);
    //* SI la longitud del ID es menor a 4 eso significa de que no es correcto            
    if(strlen(id)<4){
        cout<<"FFFFFFFF No se ha encontrado el Disco a desmontar: ID incorrecto  FFFFFFF";
        return;
    }
    // 94   +   Numero  +   Letra
    char letra = str.at(3);
    
    int contDisks = 0;
    bool existeDisco= false;
    while(partsMounted[contDisks]!=NULL){
        if(partsMounted[contDisks]->letter == letra){
            existeDisco = true;
            break;
        }
        contDisks++;
    }
    if(!existeDisco){
        cout<<"FFFFF Error debido a que el disco no existe. FFFFFF";
        return;
    }


    int tampart= 0;
    bool existePart = true;
    int contadorPart = 0;
    
    //! mientras las particiones montadas no sean vacias se aumenta el tamano de la particiones
    while((partsMounted[contDisks])->parts[tampart]!=NULL){
        tampart++;
    }
    //* recorro las particiones montadas y si encuentro una particion que coincida con el id entonces si existe.
    while((partsMounted[contDisks])->parts[contadorPart]!=NULL){
        if(strcmp((partsMounted[contDisks])->parts[contadorPart]->id,id)==0){
            existePart = false;// si existe
            break;
        }
        contadorPart++;
    }
    //! si existe entonces se va a eliminar esa montacion"""
    if(!existePart){
        delete (partsMounted[contDisks])->parts[contadorPart];
        (partsMounted[contDisks])->parts[contadorPart] = NULL;
        tampart--; // se disminuye el tamano de la particion.
        //* Pero y si llego a 0?
        
    }else{
        cout<<"FFFFFFF La particion se encuentra en estado DESMONTADA (No Montada) FFFFFFF";
        return;
    }
    cout<<"\n Se ha desmontado la Particion con exito del disco"<<endl;
    return;
}
