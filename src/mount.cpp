#include "mount.h"
#include "v.h"
#include <cstdio>
#include <cctype>
#include <iostream>
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

EBR* mount::primerEBR(MBR *disco,string paths){
    int i;
    char* path=&paths[0];
    PARTITION *extended = NULL;
    for(i=0;i<4;i++){
        //* Si la particion es ACTIVA y es una EXTENDIDA.
        if(disco->mbr_p[i].part_status == '1' && disco->mbr_p[i].part_type == 'e'){
            extended = &disco->mbr_p[i];
            break;
        }
    }
        if(extended!=NULL){

            FILE *myFile = fopen(path,"rb+");
            if(myFile==NULL){

                cout<<"\n FFFFFFFFFFF   Error al abrir el archivo  FFFFFFFFFFF \n";
                return NULL;
            }
            EBR *ebr = (EBR*)malloc(sizeof(EBR));

            fseek(myFile, extended->part_start, SEEK_SET);
            fread(ebr, sizeof(EBR), 1, myFile);
            fclose(myFile);
            return ebr;
            
        }

    return NULL;
}

char* mount::obtainKey( int numero, char letra){
    string key("94");
    key+=to_string(numero);
    key+= char(tolower(letra));// 

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
        // partsMounted[contador]->letter = tolower(65+contador); //manipulacion de mis letras usando los ASCII
        partsMounted[contador]->num = contador+1;
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
    PARTITION part;
    int i;
    int init;
    for(i=0;i<4;i++){
        if(strcmp(disco->mbr_p[i].part_name,disk->name.c_str())==0){
            existPart = false;
            init = disco->mbr_p[i].part_start;
            break;
        }
        part = disco->mbr_p[i];
        if(part.part_type=='e' || part.part_type=='E'){
            EBR *ebr = primerEBR(disco,disk->path.c_str());
            while(ebr!=NULL){
                if(strcmp(ebr->part_name,disk->name.c_str())==0){
                    existPart = false;
                    init = ebr->part_start;
                    break;
                }
                if(ebr->part_next!=-1){
                    FILE *myFile = fopen(disk->path.c_str(),"rb+");
                    if(myFile==NULL){
                        cout<<"FFFFFFFFFFFFF   Error al abrir el archivo   FFFFFFFFFFFFF\n";
                        ebr= NULL;
                    }
                    EBR *ebrtemp = (EBR*)malloc(sizeof(EBR));

                    fseek(myFile, ebr->part_next, SEEK_SET);
                    fread(ebrtemp, sizeof(EBR), 1, myFile);
                    fclose(myFile);
                    // cout<<"comparte"<<endl;
                    ebr =ebrtemp;
                }else{
                    ebr = NULL;
                }
            }
        }
    }
    string llave="";
    //! si hay una particion entonces se va a agregar una particion montada ...
    if(!existPart){
         mdisk->parts[contador2] = new MountedPart();
         
         char *key=(obtainKey(mdisk->num,tolower(65+contador2)));
         llave=key;
         strcpy(mdisk->parts[contador2]->id,key);
         strcpy(mdisk->parts[contador2]->name, disk->name.c_str());
         mdisk->parts[contador2]->start = init;
    }else{
        cout<<"FFFFFFFFF Error al montar la particion, porque la particion "<<disk->name<<" No Existe  FFFFFFFFF"<<endl;
        return ;
    }
    // FILE *myarchivo = fopen("GenPartitions.bin", "ab");

	// if (myarchivo)
	// {
	// 	struct GenPartition t1;
    //     t1.id=llave;
    //     t1.ruta= disk->path;
		
    cout<<"\nagregado al superbloque\n"<<endl;
	// 	// fseek(myarchivo,linea,SEEK_END);
	// 	// fwrite( el apuntador,sizeof(tamanoDeVariable), ElementosAInsertar,myarchivo);
	// 	fwrite(&t1, sizeof(struct GenPartition), 1, myarchivo);
	// 	fclose(myarchivo);
	// 	cout<<"\nSe inserto la estructura GenPartition en el archivo!! :)"<<endl;
	// }
	// else
	// {
	// 	cout<<"\nno se pudo crear hay algun dato malo.\n"<<endl;
	// };


    //*Por ejemplo, al usar mount, debe actualizar s_mtime,
    cout<<"Se ha montado la particion: "<<disk->name<<" correctamente, el id es: "<<llave<<"\n\nBravho!!"<<endl;
    //! ███████████████████ MODIFICANDO EL SUPERBLOQUE ████████████████████████
    char* pathsuper=&disk->path[0];
    char* namesuper=&disk->name[0];
    SuperBlock *sb =obtainSuperBlock(pathsuper,namesuper);
    if(sb==NULL){
        cout<<"FFFFFFF  Error al obtener el superbloque FFFFFFFFFFF"<<endl;
        return ;
    }
    sb->s_mnt_count = sb->s_mnt_count+1;//*Indica cuantas veces se ha montado el sistema

    //! ████████████  Agregando fecha en el SUPERBLOCK  ████████████
    time_t tiempo = time(0);
    struct tm *loc = localtime(&tiempo);
    char fechacreado[16];
    strftime(fechacreado, 16, "%d/%m/%y %H:%M:%S", loc);
    strcpy(sb->s_mtime, fechacreado);//todo Fecha y hora de desmontado

    // char *pathnew = partsMounted[contDisks]->path;
            
    // int init =partsMounted[contDisks]->parts[contofParts]->start;
    
    FILE * myFile;
    myFile = fopen (pathsuper,"rb+");
    if (myFile==NULL)
    {
        cout<<"FFFFFFFFFFF  Error al abrir el disco  FFFFFFFFF\n";
    }
    fseek(myFile, init, SEEK_SET);
    fwrite(sb, sizeof(SuperBlock), 1, myFile);
    
    fclose (myFile);
    cout<<"\n todo bien\n";
    return ;
}

//! ███████████████████████████████████████████  UNMOUNT.  ██████████████████████████████████████████

bool mount::primerPartition(MBR* disco, char name[], int *init){
    int i;
    for(i = 0; i < 4; i++){
        if(disco->mbr_p[i].part_status == '1'){
            if(strcmp(disco->mbr_p[i].part_name,name)==0){
                *init = disco->mbr_p[i].part_start;
                return true;
            }
        }
    }
    return false;
}

SuperBlock* mount::obtainSuperBlock(char path[], char name[]){
    MBR *disco = obtainMBR(path);
    SuperBlock *sb = (SuperBlock*)malloc(sizeof(SuperBlock));
    if(disco==NULL){
        std::cout<<"Error al leer el disco\n";
        return NULL;
    }
    int init;
    bool isthepart = primerPartition(disco,name,&init);
    if(!isthepart){
        return NULL;
    }
    delete disco;
    FILE *myFile = fopen(path,"rb+");
    if(myFile==NULL){
        cout<<"Error al abrir el disco \n";
        return NULL;
    }
    fseek(myFile, init, SEEK_SET);
    fread(sb, sizeof(SuperBlock), 1, myFile);
    fclose(myFile);
    return sb;
}

void mount::desmontar(string idi){
    // char id[idie.length()];
 
    // size_t i;
    // for ( i = 0; i < sizeof(idie); i++) {
    //     id[i] = idie[i];
    //    // cout << id[i];
    // }
    //*--------
    char* id=&idi[0];
    string str(id);
    cout<<" Id a Desmontar: " << str << endl;
    //* SI la longitud del ID es menor a 4 eso significa de que no es correcto            
    if(strlen(id)<4){
        cout<<"FFFFFFFF No se ha encontrado el Disco a desmontar: ID incorrecto  FFFFFFF";
        return;
    }
    // 94   +   Numero  +   Letra
    char num = str.at(2);
    cout<<" El numero de ID : "<<num<<endl;
    string s(1, num);
    int contDisks = 0;
    bool existeDisco= false;
    while(partsMounted[contDisks]!=NULL){
        cout<<partsMounted[contDisks]->num <<" con "<< num<<endl;
        if(partsMounted[contDisks]->num == stoi(s)){
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
    int contofParts = 0;
    
    //! mientras las particiones montadas no sean vacias se aumenta el tamano de la particiones
    while((partsMounted[contDisks])->parts[tampart]!=NULL){
        tampart++;
    }
    //* recorro las particiones montadas y si encuentro una particion que coincida con el id entonces si existe.
    while((partsMounted[contDisks])->parts[contofParts]!=NULL){
        if(strcmp((partsMounted[contDisks])->parts[contofParts]->id,id)==0){
            existePart = false;// si existe
            break;
        }
        contofParts++;
    }
    //! si existe entonces se va a eliminar esa particion montada"""
    if(!existePart){
        delete (partsMounted[contDisks])->parts[contofParts];
        (partsMounted[contDisks])->parts[contofParts] = NULL;
        tampart--; // se disminuye el tamano de la particion.
        //* Pero y si llego a 0?
        if(tampart == 0){
            
            SuperBlock *sb =obtainSuperBlock(partsMounted[contDisks]->path, partsMounted[contDisks]->parts[contofParts]->name);
            if(sb==NULL){
                cout<<" FFFFFFFF  ERROR AL OBTENER EL SUPER BLOQUE FFFFFFFFFFFFFF"<<endl;
            }
            

            //! ████████████  Agregando fecha en el SUPERBLOCK  ████████████
            time_t tiempo = time(0);
            struct tm *loc = localtime(&tiempo);
            char fechacreado[16];
            strftime(fechacreado, 16, "%d/%m/%y %H:%M:%S", loc);
            strcpy(sb->s_umtime, fechacreado);//todo Fecha y hora de desmontado
          
            char *pathnew = partsMounted[contDisks]->path;
            
            int init =partsMounted[contDisks]->parts[contofParts]->start;
            
            FILE * myFile;
            myFile = fopen (pathnew,"rb+");
            if (myFile==NULL)
            {
                cout<<"FFFFFFFFFFF  Error al abrir el disco  FFFFFFFFF\n";
            }
            fseek(myFile, init, SEEK_SET);
            fwrite(sb, sizeof(SuperBlock), 1, myFile);
            
            fclose (myFile);


            while((partsMounted[contDisks])!=NULL){
                delete partsMounted[contDisks];
                (partsMounted[contDisks]) = (partsMounted[contDisks+1]);
            }
            partsMounted[contDisks] = NULL;
        }
        
    }else{
        cout<<"FFFFFFF La particion se encuentra en estado DESMONTADA (No Montada) FFFFFFF";
        return;
    }
    cout<<"\n Se ha desmontado la Particion con exito del disco"<<endl;
    return;
}
