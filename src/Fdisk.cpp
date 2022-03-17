#include "Fdisk.h"
#include "mkdisk.h"
#include <cstdio>

Fdisk::Fdisk()
{
}
//! █████████████████████████████████████████████  ADMINISTRACION GENERAL.  ██████████████████████████████████████████
void Fdisk::adminPartition(Fdisk *disco)
{
    /*  P: en este caso se creará una partición primaria.
        E: en este caso se creará una partición extendida.
        L: Con este valor se creará una partición lógica.*/

        //! No se considerará el caso de que se pongan parámetros incompatibles, por
        //! ejemplo, en un mismo comando fdisk llamar a delete y add.
    if (disco->add.empty() != true)
    {   //* Si add no esta vacio se va a extender/achicar una particion
        if(disco->path.empty()!=true){ //VALIDANDO RUTA
            FILE *myfile;
            myfile = fopen(disco->path.c_str(), "rb+");
            if (myfile != NULL)//?validando la ruta.
            {
                if (disco->name.empty()!=true) //?validando el name
                {
                    cout<<"███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.EXTENDIENDO UNA PARTICION.░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████ "<<endl;
                    ExtendPartition(disco); //se extiende
                }else{

                    cout << "FFFFFFFFF      El nombre es OBLIGATORIO       FFFFFFFFF"<< std::endl;
                    return;
                }
                
            }else{

                cout << "FFFFFFFFF      El disco: \"" << disco->path << "\" no existe       FFFFFFFFF"<< std::endl;
                return;
            }
        }else{
            cout << "FFFFFFFFF      FALTA LA RUTA, ES COMANDO OBLIGATORIO       FFFFFFFFF"<< std::endl;
            return;
        }
        
    }
    else if (disco->deleted.empty() != true)
    {  
        if(disco->path.empty()!=true){ //VALIDANDO RUTA
        
        }else{
            cout << "FFFFFFFFF      FALTA LA RUTA, ES COMANDO OBLIGATORIO       FFFFFFFFF"<< std::endl;
            return;
        }
        cout << "Esta usted seguro de Borrar el disco? [Y/n]------------>";
        string siu;
        cin >> siu;

        if (siu == "y" || siu == "Y")
        {
            //* Si deleted no esta vacio, se va a eliminar una particion.
            FILE *myfile;
            myfile = fopen(disco->path.c_str(), "rb+");
            if (myfile != NULL)//?validando la ruta.
            {

                if (disco->name.empty()!=true) //?validando el name
                {
                    cout<<"███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.ELIMINANDO UNA PARTICION.░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████ "<<endl;
                    DeletePartition(disco); //! se elimina
                }else{

                    cout << "FFFFFFFFF      El nombre es OBLIGATORIO       FFFFFFFFF"<< std::endl;
                    return;
                }
                
            }else{

                cout << "FFFFFFFFF      El disco: \"" << disco->path << "\" no existe       FFFFFFFFF"<< std::endl;
                return;
            }
        }else{
            cout<<" Operacion cancelada, No se elimino el disco."<<endl;
        }
        
        
    }   
    else
    {   //* Sino por default se va a CREAR una particion.
    
        if (disco->size > 0) //?validando el tamano
        {
            if(disco->path.empty()!=true){ //VALIDANDO RUTA
                FILE *myfile;
                myfile = fopen(disco->path.c_str(), "rb+");
                if (myfile != NULL)//?validando la ruta.
                {
                    if (disco->name.empty()!=true) //?validando el name
                    {
                        cout<<"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.CREANDO UNA PARTICION. \""<< disco->name <<"\" de tipo \""<<disco->type<<"\"  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"<<endl;
                        CreatePartition(disco); //se crea
                    }else{

                        cout << "FFFFFFFFF      El nombre es OBLIGATORIO       FFFFFFFFF"<< std::endl;
                        return;
                    }            
                    
                }else{

                    cout << "FFFFFFFFF      El disco: \"" << disco->path << "\" no existe       FFFFFFFFF"<< std::endl;
                    return;
                }


            }else{
                cout << "FFFFFFFFF      FALTA LA RUTA, ES COMANDO OBLIGATORIO       FFFFFFFFF"<< std::endl;
                    return;
            }
            
        }else{
            cout << "FFFFFFFFF      EL COMANDO SIZE DE LA PARTICION ES MENOR QUE 0 O NO EXISTE     FFFFFFFFF" << endl;
            return;
        }
        
        
    }

}

void Fdisk::genrep()
{
    // string dot;
    // dot+=
    /**/
}
//* █████████████████████████████████████████  CREACION DE UN NUEVO EBR.  ████████████████████████████████████████
EBR Fdisk::createnewEBR(){
    
    EBR newebr;
    newebr.part_fit = '-';
    newebr.part_next = -1;
    newebr.part_size = -1;
    newebr.part_start = -1;
    newebr.part_status = '0';
    newebr.part_name[0] = '\0';
    return newebr;
}

//* █████████████████████████████████  VALIDACION Y RETORNO DE ESTADO DE PARTICION.  ███████████████████████████████

int Fdisk::searchname(FILE *archivo, int start, string name)
{
    //* El metodo solo me retorna un nombre el cual encuentra utilizando recursividad.
    //SE USA RECURSIVIDAD PARA IR BUSCANDO MIS PARTICIOES CON EL FIN DE OPTIMIZAR BUSQUEDA/
    EBR ebr;
    int retorno;
    fseek(archivo, start, SEEK_SET);
    fread(&ebr, sizeof(EBR), 1, archivo);

    if (ebr.part_status != '0')//Indica si la partición está activa o no
    {
        if (ebr.part_next != -1 )//|| ebr.part_next!=0
        {
            if (ebr.part_name == name)
            {
                retorno=ebr.part_start - sizeof(EBR);
                return retorno;
            }
            else
            {
                return searchname(archivo, ebr.part_next, name);//problem
            }
        }
        else
        {
            if (ebr.part_name == name)
            {
                // return ebr.part_start - sizeof(EBR);
                retorno=ebr.part_start - sizeof(EBR);
                return retorno;
            }
            else
            {
                return -1;
            }
        }


        
    }
    else if(ebr.part_status == '0')
    {
        if (ebr.part_next != -1)//Byte en el que está el próximo EBR. -1 si no hay siguiente
        {
            return searchname(archivo, ebr.part_next, name);
        }
        else
        {
            return -1;
        }
    }
    return -1;
}

//* ██████████████████████████████████████  VALIDACION CREACION DE UNA PARTICION LOGICA.  █████████████████████████████████████
void Fdisk::searchLogica(int tam_part, Fdisk *disco, FILE *archivo, int start, int total )
{
    EBR ebr;
    int temporalint=0;
    // int startnext=0;
    fseek(archivo, start, SEEK_SET);
    fread(&ebr, sizeof(EBR), 1, archivo);
    //! ████████████  VERIFICACION DE PARTICIONES ACTIVAS  ████████████
    if (ebr.part_status != '0'){
        // * Si la particion esta activa, entonces paso a la siguiente particion.
        int sig= ebr.part_next;
        searchLogica(tam_part, disco, archivo, sig, total);
    }else if (ebr.part_status == '0')
    {
        //*Tipo de ajuste de la partición. Tendrá los valores 
        //*     B (Best), 
        //*     F (First)
        //*     W (worst)
        ebr.part_status = '1';
        //! ████████████  VALIDACION DE FIT  ████████████
        //!Indicará el ajuste que utilizará el disco para crear las
        //!particiones dentro del disco Podrá tener los siguientes valores:
        if (disco->fit.empty())
        {
            ebr.part_fit = 'w';
        }
        else if (disco->fit == "bf" ||disco->fit == "b" ) //Indicará el mejor ajuste (Best Fit)
        {
            ebr.part_fit = 'b';
            cout<<"Indicará el mejor ajuste (Best Fit)"<<endl;
        }else if(disco->fit == "f" || disco->fit == "ff")
        {
            cout<<"Utilizará el primer ajuste (First Fit)"<<endl;
            ebr.part_fit = 'f';
        }else if(disco->fit == "w" || disco->fit == "wf")
        {
            ebr.part_fit = 'w';
            cout<<"Utilizará el peor ajuste (Worst Fit)"<<endl;
        }else
        {
            ebr.part_fit = 'w';
            cout << "  EL AJUSTE FIT ES INCORRECTO PERO SE ASIGNO W   " << endl;
        }

        //! ████████████  VALIDACION DE SIGUIENTE EBR  ████████████
        ebr.part_start = start + sizeof(EBR);//*se agrega la sigui9ente posicion del EBR 
        
        if (ebr.part_next == -1) //* si llega al ultimo EBR entonces...
        {
            
            //* necesito verificar si se tiene espacio para crear la particion
            // si el total de miparticion es mayor que la particion actual y la posicion del
            // bit juntas donde se quedo entonces debo tener espacio.
            //todo ████████████  Valido el tamano de la particion a crear ████████████ 
            temporalint=tam_part + ebr.part_start;
            if (total < temporalint)
            {
                cout << "FFFFFFFF No hay suficiente espacio para la nueva particion: " << disco->name <<" FFFFFFFF"<< endl;
                return;
                
            }
            else
            {
                ebr.part_next = temporalint;
            }
            
            strcpy(ebr.part_name, disco->name.c_str());// PORST A ESO PASO EL NOMBRE
            //* despues paso el tamano de la particion del ebr
            ebr.part_size = tam_part;  
             
            
            
            //todo ████████████  Modificacion del EBR  ████████████ 
            fseek(archivo, start, SEEK_SET);
            fwrite(&ebr, sizeof(EBR), 1, archivo);
            EBR ebrnext = createnewEBR();
            //*simulando una lista enlazada creo el siguiente EBR que seria el final de la lista.
            
            fseek(archivo, ebr.part_next, SEEK_SET);
            fwrite(&ebrnext, sizeof(EBR), 1, archivo);
            cout<<"La particion \""<<disco->name<<"\" de tipo \""<<disco->type<<"\" Se ha creado exitosamente. Ruta: \"" << disco->path << "\""<<endl;
        }
        //* si no es el ultimo 
        else
        {
            
            EBR ebr_next = createnewEBR();
            //*si el tamano de la particion es menor que el tamano del EBR 
            if (tam_part < ebr.part_size)
            {
                int nextemp=ebr.part_next;
                int startnext=ebr.part_start + tam_part + sizeof(EBR); //* l*uego calculo la posicion inicial con el tamano de mi particion y 
                //*con el tamano del EBR a crear o generar.

                //*primero calculo la posicion siguiente de mi EBR
                int nextebr=startnext - sizeof(EBR);// 

                //*Seteo los valores del disco.
                ebr.part_size=tam_part;
                strcpy(ebr.part_name, disco->name.c_str());
                ebr.part_next = nextebr;


                ebr_next.part_next = nextemp;
                ebr_next.part_start = startnext;
                ebr_next.part_size = ebr.part_next - ebr_next.part_start;

                               

                fseek(archivo, start, SEEK_SET);
                fwrite(&ebr, sizeof(EBR), 1, archivo);

                fseek(archivo, ebr.part_next, SEEK_SET);
                fwrite(&ebr_next, sizeof(EBR), 1, archivo);

                cout<<"La particion "<<disco->name<<"\" de tipo \""<<disco->type<<"\"  Se ha creado exitosamente."<<endl;

            }else if (tam_part == ebr.part_size)
            {
                //** SI el tamano de particion es igual entonces...
                strcpy(ebr.part_name, disco->name.c_str());//? paso el nombre

                
                fseek(archivo, start, SEEK_SET);
                fwrite(&ebr, sizeof(EBR), 1, archivo);
                cout<<"La particion "<<disco->name<<"\" de tipo \""<<disco->type<<"\"  Se ha creado exitosamente."<<endl;
            }
            else
            {
                cout << "FFFFFFF No hay suficiente espacio para la particion: " << disco->name <<" FFFFFFF"<< endl;
                return;
            }
        }
    }
    else
    {    
        // * Si la particion esta activa, entonces paso a la siguiente particion.
        int sig= ebr.part_next;
        searchLogica(tam_part, disco, archivo, sig, total);    
    }
}

//* ██████████████████████████████████  VERIFICACION SI LA PARTICION ES EXTENDIDA.  ████████████████████████████████
bool Fdisk::isExtended(string tipoParticion,MBR mbr,Fdisk *disco){
    //* si en dado caso es extendida alguna entonces no se puede crear la particion 
    if (tipoParticion == "e")
    {
        if (mbr.mbr_p[0].part_type == 'e'||mbr.mbr_p[1].part_type == 'e'||mbr.mbr_p[2].part_type == 'e'||mbr.mbr_p[3].part_type == 'e')
        {
            cout << "╬╬╬╬╬ Imposible crear la particion " + disco->name + " Se tiene una particion extendida alli "+ disco->path +" ╬╬╬╬╬" << endl;
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
};

//* ███████████████████████████████████  SE CREA LA PARTICION SI ES INACTIVA.  ██████████████████████████████████
bool Fdisk::StateInactiveCreate(int i, int espacio_disp, MBR mbr, int p_gen_tam, bool p_existe , Fdisk *disco, FILE *archivo, int hayespaciodisp){
    bool sesale=true;
    // bool hayespacio = false;         
    // bool hayespaciodisp=true;
    int posback=i-1;
    //* seteo la posicion inicial de la particion mbr que se esta creando.
    int mbrpartini=mbr.mbr_p[posback].part_start + mbr.mbr_p[posback].part_start;
    mbr.mbr_p[i].part_start = mbrpartini;
    espacio_disp = mbr.mbr_tamano - mbr.mbr_p[i].part_start;

    //todo ███████████████████████ ESPACIO DISPONIBLE EN LAS PARTICIONES████████████████████████
    for (int j = i; j < 4; j++)
    {
        if (mbr.mbr_p[j].part_start == '1')
        {
            int dispobilidad=mbr.mbr_p[j].part_start - mbr.mbr_p[i].part_start;
            espacio_disp = dispobilidad;
            return sesale;
        }
    }

    if (p_gen_tam <= espacio_disp)
    {
        hayespaciodisp = false;
    }
    

    if (hayespaciodisp==false)
    {
        if (!p_existe)
        {

            //! ████████████  VALIDACION DE FIT  ████████████
            //!Indicará el ajuste que utilizará el disco para crear las
            //!particiones dentro del disco Podrá tener los siguientes valores:
            if (disco->fit == "b" || disco->fit == "bf"  ) //Indicará el mejor ajuste (Best Fit)
            {
                mbr.mbr_p[i].part_fit = 'b';
                // strcpy(mbr.mbr_p[i].part_fit, 'b');
                cout<<"Indicará el mejor ajuste (Best Fit)"<<endl;
            }else if(disco->fit == "f" || disco->fit == "ff")
            {
                mbr.mbr_p[i].part_fit = 'f';
                cout<<"Utilizará el primer ajuste (First Fit)"<<endl;
                // strcpy(mbr.mbr_p[i].disk_fit, "f");
            }else if(disco->fit == "w" || disco->fit == "wf" || disco->unit.empty())
            {
                mbr.mbr_p[i].part_fit = 'w';
                // strcpy(mbr.mbr_p[i].disk_fit, "wf");
                cout<<"Utilizará el peor ajuste (Worst Fit)"<<endl;
            }else
            {
                mbr.mbr_p[i].part_fit = 'w';
                //*Si se utiliza otro valor que no sea alguno de los anteriores mostrará un mensaje de error.
                // strcpy(mbr.disk_fit, "bf");
                cout << "  EL AJUSTE FIT ES INCORRECTO REVISELO...  (se asigno wf por si acaso)" << endl;
            }

            //! ████████████  GUARDAR DATOS DEL NUEVO MBR  ████████████
            //* Al crear una particion se debe guardar el nombre, agregar el tamano de la particion
            //* y se debe marcar el estado de la particion como ACTIVA:
            strcpy(mbr.mbr_p[i].part_name, disco->name.c_str());
            mbr.mbr_p[i].part_size = p_gen_tam;
            mbr.mbr_p[i].part_status = '1';            

            //! ████████████  VALIDACION DE SI ES PRIMARIA O EXTENDIDA  ████████████
            if ( disco->type == "e") // si es una extendida debo agregar el EBR a mi FILE...
            {   
                // ebr.part_fit = '-';
                // ebr.part_next = -1;
                // ebr.part_size = -1;
                // ebr.part_start = -1;
                // ebr.part_status = '0';
                // ebr.part_name[0] = '\0';
                mbr.mbr_p[i].part_type = 'e';
                EBR ebr=createnewEBR();
                
                fseek(archivo, mbr.mbr_p[i].part_start, SEEK_SET);
                fwrite(&ebr, sizeof(EBR), 1, archivo);
            }else if (disco->type == "p")
            {
                mbr.mbr_p[i].part_type = 'P';
            }
            else{

            }
            // fseek(archivo, start, SEEK_SET);
            // fwrite(&ebr, sizeof(EBR), 1, archivo);
            
            cout<<"La particion "<<disco->name<<"\" de tipo \""<<disco->type<<"\"  Se ha creado exitosamente. Ruta: \"" << disco->path << "\""<<endl;
        }
        else
        {
            cout << "FFFFFFFFFF  La particion  \"" << disco->name << "\" Ya existe, No se puede crear   FFFFFFFFF" << endl;
            
            fclose(archivo);
            return sesale;
        }
    }
    
    else
    {
        cout << "FFFFFFFFF Imposible crear la Particion, se tiene el espacio ocupado, espacio: "<<espacio_disp<<"  FFFFFFFFFFF" << endl;
        fclose(archivo);
        return sesale;
    }

    fseek(archivo, 0, SEEK_SET);
    fwrite(&mbr, sizeof(MBR), 1, archivo);
    fclose(archivo);
    return sesale;

}

//* █████████████████████████████████  SE CREA LA PARTICION PRIMARIA O EXTENDIDA.  ████████████████████████████████
void Fdisk::crearPrimariaExtendida(MBR mbr,Fdisk *disco,int p_gen_tam,bool p_existe, FILE *archivo){
    //! Verifico las particiones que sean y esten disponibles
    int total = 0;
    for (int i = 0; i < 4; i++)
    {
        if (mbr.mbr_p[i].part_status == '1')//!si tienen un 1 es porque estan disponibles 
        {
            total += 1;
        }
        if (total == 4)//! si ya se tienen 4 es porque todas estan ocupadas.
        {
            cout << "╬╬╬╬╬╬ Se tienen todas las particiones ocupadas ╬╬╬╬╬╬" << endl;
            return;
        }
    }
    string tipoParticion=disco->type;
    
    //! Verifico que no exista una particion de tipo extendida
    bool hayextended=isExtended(tipoParticion, mbr,disco);
    //* hay extendida?
    if (hayextended){ return; }

    //* La primera particion debo agregar los valores y verificando el espacio disponible.

    int espacio_disp;
    // ! innicio de primer particion
    bool hayespaciodisp=true;


    mbr.mbr_p[0].part_start = sizeof(mbr); 
    espacio_disp = mbr.mbr_tamano - sizeof(mbr);

    int cantEnabled=0;
    for (int j = 1; j < 4; j++)
    {
        if (mbr.mbr_p[j].part_start == '1')
        {
            // *El espacio disponible sera lo que se tiene en la posicion inicial del MBR menos el tamano del MBR actual. 
            cantEnabled= mbr.mbr_p[j].part_start - sizeof(mbr);
            espacio_disp = mbr.mbr_p[j].part_start; 
            // *El espacio disponible sera lo que se tiene en la posicion inicial del MBR menos el tamano del MBR actual. 
            espacio_disp = cantEnabled;
            
            break;
        }
    }
    
    //Se verifica que la partición entre en el espacio
    if ( espacio_disp >=  p_gen_tam)
    {
        hayespaciodisp = false;
    }
     // ! fin de primer particion   
     
    //! ████████████  BUSQUEDAD DE PARTICION ACTIVA.  ████████████    
    //**Recorro las particiones buscando una que sea inactiva
    for (int i = 0; i < 4; i++)
    {
        

        //* busco una particion que sea estado inactivo porque no puedeo crear en una particion que haya sido usado.
        if (mbr.mbr_p[i].part_status == '0')
        {
            bool sesale=StateInactiveCreate(i, espacio_disp, mbr, p_gen_tam,p_existe, disco, archivo, hayespaciodisp);
            if(sesale){
                break; // se termina de generar la particion 
            }
        }
        
    }


}

//! ██████████████████████████████████████████████  SE CREA LA PARTICION.  ██████████████████████████████████████████
void Fdisk::CreatePartition(Fdisk *disco)
{
    //! ████████████  TOMO EL MBR DEL DISCO A PARTICIONAR.  ████████████
    //* Obteniendo el MBR del disco..
    FILE *archivo;
    archivo = fopen(disco->path.c_str(), "rb+");
    fseek(archivo, 0, SEEK_SET);
    MBR mbr;
    fread(&mbr, sizeof(MBR), 1, archivo);
    cout<<"tamano del ebr: "<<sizeof(mbr)<<endl;
    //! ████████████  VERIFICO QUE EL NOMBRE NO SEA REPETIDO  ████████████
    //* El nombre no debe repetirse dentro de las particiones de cada disco.
    bool p_existe = false;
    //? Deberá tener en cuenta las restricciones de teoría de particiones:
    for (int i = 0; i < 4; i++)//!solo son 4 particiones, entonces las recorro.
    {
        cout<<mbr.mbr_p[i].part_name<<endl;
        cout<<i<<endl;
        // La suma de primarias y extendidas debe ser como máximo 4.
        if (mbr.mbr_p[i].part_name == disco->name)//!si el nombre de la particion mbr  es igual al nombre
        {
            p_existe = true; //!si ya existe entonces me salgo :v   true==si existe el nombre
            break;
        }else{
           
        }
        if (mbr.mbr_p[i].part_type == 'e')//*E: en este caso se creará una partición extendida.
        {
            //Solo puede haber una partición extendida por disco.
            //*** va a buscar el nombre de la particion extendida.
            int existe = searchname(archivo, mbr.mbr_p[i].part_start, disco->name);
            if (existe != -1) //!-1 si no hay siguiente
            {   //?osea si si hay siguiente.
                p_existe = true;
                break;
            }
        }
    }

    int p_gen_tam;

    //! ████████████  UNIDADES DE CREACION DE LA PARTICION  ████████████
    //! se debe validar en que Unidades estamos hablando de creacion de la particion
    //*Este parámetro es opcional, si no se encuentra se creará una partición en Kilobytes.
    if (  disco->unit == "b")
    {        //*B: indicará que se utilizarán bytes.
        p_gen_tam = disco->size;
    }
    else if (disco->unit == "m")
    {
            //*M:indicará que se utilizarán Megabytes(1024 * 1024bytes).
        p_gen_tam = disco->size * 1024 * 1024;
    }
    else if (disco->unit == "k" || disco->unit.empty() == true)
    {
            //*K: indicará que se utilizarán Kilobytes(1024 bytes)
        p_gen_tam = disco->size * 1024;
        
    }else{
        //*Si se utiliza un valor diferente mostrará un mensaje de error.
        cout << "FFFFFFFFF      La Unidad de tamano de particion es Incorrecta       FFFFFFFFF"<< std::endl;
        return;
    }

    //! ████████████  VALIDACION DE TIPO DE PARTICION  ████████████
    /*  P: en este caso se creará una partición primaria.
        E: en este caso se creará una partición extendida.
        L: Con este valor se creará una partición lógica.*/
    if (disco->type == "l")
    {
        int nopart;
        //*No se puede crear una partición lógica si no hay una extendida.
        // Se debe validar una extendida al menos
        bool existext = true;
        for (int i = 0; i < 4; i++)
        {
            // Las particiones lógicas sólo pueden estar dentro de
            // la extendida sin sobrepasar su tamaño.
            // cout<<i<<endl;
            if (mbr.mbr_p[i].part_type == 'e')
            {
                existext = false;
                nopart = i;
            }
        }
        if (existext == true)
        {
            cout << "No se ha encontrado ninguna particion extendida." << endl;
            return;
        }

        if (!p_existe)//* si existe la particion
        {
            // cout<<""<<nopart;
            cout<<" \ncreando una particion Logica en el EBR ...";
            // Busco su EBR
            //* y creo la unidad logica si asi fuera el caso de la creacion de particioners.........
            searchLogica(p_gen_tam, disco, archivo, mbr.mbr_p[nopart].part_start, mbr.mbr_p[nopart].part_start + mbr.mbr_p[nopart].part_size);
        }
        else
        {
            cout << "FFFFFFFFFF  La particion  \"" << disco->name << "\" Ya existe, No se puede crear   FFFFFFFFF" << endl;
        }

        fclose(archivo);
    }
    else if ( disco->type == "p" || disco->type == "e" || disco->type=="")
    {
        //todo Procedo a crear una particion primaria o extendida...
        crearPrimariaExtendida(mbr,disco, p_gen_tam, p_existe, archivo);
    }
    else
    {
        //Si se utiliza otro valor diferente a los anteriores
        //deberá mostrar un mensaje de error
        cout << "FFFFFFFF   Error, se uso un valor diferente " << disco->type << ", en vez de P,E,L   FFFFFFFF" << endl;
    }
}


//* █████████████████████████████████  BUSQUEDA DE PARTICIONES LOGICAS DENTRO EXTENDIDA █████████████████████████████
int Fdisk::searchLogicPartitionsDelete(Fdisk *disco, FILE *archivo, int inicio)
{
    EBR ebr;
    // bool seelimina=false; //* no se elimina
    fseek(archivo, inicio, SEEK_SET);
    fread(&ebr, sizeof(EBR), 1, archivo);

    if (ebr.part_status != '0')
    {
        if (ebr.part_next == -1)
        {
            if (ebr.part_name == disco->name)
            {
                int tamano= ebr.part_start - sizeof(EBR);
                return tamano;
            }
            else
            {
                return -1;
            }


            
        }
        else
        {
            if (ebr.part_name == disco->name)
            {
                int tamano= ebr.part_start - sizeof(EBR);
                return tamano;
            }
            else
            {
                return searchLogicPartitionsDelete(disco, archivo, ebr.part_next);
            }
        }



       
    }
    else
    {
         if (ebr.part_next != -1)
        {
             return searchLogicPartitionsDelete(disco, archivo, ebr.part_next); 
        }
        else
        {
            return -1;
        }
        // if (ebr.part_next == -1)
        // {
        //     return -1;
            
        // }
        // else  if(ebr.part_next != -1)
        // {
        //     return searchLogicPartitionsDelete(disco, archivo, ebr.part_next);  
        // }else{
        //     return -1;
        // }
    }

    
}

//* █████████████████████████████████      ELIMINACION DE PARTICION DE FORMA RAPIDA    █████████████████████████████

EBR* Fdisk::primerEBR(MBR *disco,string paths){
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



void Fdisk::deleteFast(FILE *archivo, int pos){
    EBR ebr;
    fseek(archivo, pos, SEEK_SET);
    fread(&ebr, sizeof(EBR), 1, archivo);

    ebr.part_fit = '-';
    ebr.part_status = '0';
    ebr.part_name[0] = '\0';
    int posfinal= ebr.part_start - sizeof(EBR);
    fseek(archivo, posfinal, SEEK_SET);
    fwrite(&ebr, sizeof(EBR), 1, archivo);
    cout << "Se ha eliminado la particion " << ebr.part_name << " rapidamente." << endl;
}

//* █████████████████████████████████    ELIMINACION DE PARTICION DE FORMA COMPLETA   █████████████████████████████
void Fdisk::deleteFull(FILE *archivo, int pos){
    EBR ebr;
    fseek(archivo, pos, SEEK_SET);
    fread(&ebr, sizeof(EBR), 1, archivo);

    char relleno = '\0';
    
    fseek(archivo, ebr.part_start, SEEK_SET);

    for (int i = 0; i < ebr.part_size; i++)
    {
        fwrite(&relleno, sizeof(relleno), 1, archivo);
        fseek(archivo, ebr.part_start + i, SEEK_SET);
    }

    ebr.part_name[0] = '\0';
    ebr.part_fit = '-';
    ebr.part_status = '0';    

    fseek(archivo, ebr.part_start - sizeof(EBR), SEEK_SET);
    fwrite(&ebr, sizeof(EBR), 1, archivo);
    cout << "Se ha eliminado la particion " << ebr.part_name << " completamente." << endl;
}
MBR* Fdisk::obtainMBR(char path[]){
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
//! ██████████████████████████████████████████████  SE ELIMINA LA PARTICION.  ██████████████████████████████████████████
void Fdisk::DeletePartition(Fdisk *disco)
{
    if(disco==NULL){
        return ;
    }

    FILE *archivo;
    archivo = fopen(disco->path.c_str(), "rb+");
    if(archivo!=NULL){
        
    }else{
        cout<<"FFFFFFF no se encuentra el disco FFFFFF\n";
        return;
    }

    // MBR *mbr= obtainMBR(disco->path.c_str());

    fseek(archivo, 0, SEEK_SET);
    MBR *mbr = (MBR*)malloc(sizeof(MBR));
    fread(mbr,sizeof(MBR),1,archivo);
    fclose(archivo);
    

    //* Si la partición no existe deberá mostrar error. 

    //* Si se elimina la partición extendida, deben eliminarse las
    //* particiones lógicas que tenga adentro.

  
    if (disco->deleted == "fast")
    {   
        PARTITION part;
        bool eliminada=false; // no se ha eliminado
        //* Fast: Esta opción marca como vacío el espacio en la
        // *tabla de particiones.
        for (int i = 0; i < 4; i++)//?recorro mi tabla de particiones.
        {

            // if(mbr.mbr_p[i].part_type){


            // }
            part = mbr->mbr_p[i];
            //* RECORRO MIS EBR'S EN BUSCA DE UNA PARTICION QUE MATCHE CON LA PARTICION QUE SE QUIERE ELIMINAR.
            if(part.part_type=='e' || part.part_type=='E'){
                
                EBR *ebr = primerEBR(mbr,disco->path.c_str());
                while(ebr!=NULL){
                    //  if ebr->part_name == disco->name)
                    if(strcmp(ebr->part_name,disco->name.c_str())==0){
                        
                        EBR *newebr;
                        newebr->part_fit = '-';
                        newebr->part_next = -1;
                        newebr->part_size = -1;
                        newebr->part_start = -1;
                        newebr->part_status = '0';
                        newebr->part_name[0] = '\0';

                        ebr=newebr;
                        //!█████████████████ rellena el espaciocon el carácter \0 █████████████████

                        //* como es fast alli se queda xdxd                        
                        eliminada=true;                            
                        break;
                    }
                    if(ebr->part_next!=-1){
                        FILE *myFile = fopen(disco->path.c_str(),"rb+");
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



            if (mbr->mbr_p[i].part_name == disco->name) // si encuentro la particion la borro
            {   
                // seteando y borrando los datos de mi particion.
                for (int j = 0; j < 16; j++)
                {
                    mbr->mbr_p[i].part_name[j] = '\0';
                }
                mbr->mbr_p[i].part_status = '0';
                mbr->mbr_p[i].part_type = '-';
                mbr->mbr_p[i].part_fit = '-';
                mbr->mbr_p[i].part_start= -1;
                mbr->mbr_p[i].part_size= -1;
                
                fseek(archivo, 0, SEEK_SET);
                fwrite(&mbr, sizeof(MBR), 1, archivo);
                fclose(archivo);
                
                //* y si la particion es una particion extendida
            //!Si se  //! elimina la partición extendida, deben eliminarse las
            //! particiones lógicas que tenga adentro.
                //* si la particion eliminada es extendida, entonces procedo a eliminar  las particiones lógicas que tenga adentro.
                if (mbr->mbr_p[i].part_type == 'e')
                {   
                    int inicio=mbr->mbr_p[i].part_start; // el innicio de la particion actual
                    int pos=searchLogicPartitionsDelete(disco, archivo, inicio);
                    if (pos == -1)
                    {
                        
                    }else{
                        deleteFast(archivo, pos);
                        fclose(archivo);
                    }
                }
                eliminada=true;
                cout << "Se elimino la particion: " << disco->name << " que se encontraba en: \"" << disco->path << "\" " << endl;
                
                break;
            }
            
          
        }
        if(eliminada==false){
            //! Si la partición no existe deberá mostrar error. 
            cout<<"FFFFFFFFF   No se ha encontrado la particion a eliminar, verifique el nombre y ruta  FFFFFFFFF"<<endl;
        }
        
    }else if (disco->deleted == "full")
    {
        //* Full: Esta opción además marcar como vació el
        //* espacio en la tabla de particiones, rellena el espacio
        //* con el carácter \0. Si se utiliza otro valor diferente,
        //* mostrará un mensaje de error.
        bool eliminada=false; // no se ha eliminado
        bool isdeleted=false;
        char buff = '\0';
        PARTITION part;
       
        
        if(!isdeleted){
            for (int i = 0; i < 4; i++)
            {
                // if(mbr.mbr_p[i].part_type){


                // }
                part = mbr->mbr_p[i];
                //* RECORRO MIS EBR'S EN BUSCA DE UNA PARTICION QUE MATCHE CON LA PARTICION QUE SE QUIERE ELIMINAR.
                if(part.part_type=='e' || part.part_type=='E'){
                    
                    EBR *ebr = primerEBR(mbr,disco->path.c_str());
                    while(ebr!=NULL){
                        //  if ebr->part_name == disco->name)
                        if(strcmp(ebr->part_name,disco->name.c_str())==0){
                            int init=ebr->part_start;
                            EBR *newebr=(EBR*)malloc(sizeof(EBR));
                            newebr->part_fit = '-';
                            newebr->part_next = -1;
                            newebr->part_size = -1;
                            newebr->part_start = -1;
                            newebr->part_status = '0';
                            newebr->part_name[0] = '\0';
                            int inicio=part.part_start; 
                            ebr=newebr;
                            //!█████████████████ rellena el espaciocon el carácter \0 █████████████████
                            // int pos=searchLogicPartitionsDelete(disco, archivo, inicio);
                            // if (pos == -1)
                            // {
                                
                            // }else{
                                deleteFull(archivo, init);
                                fclose(archivo);
                            // }
                            // deleteFull();

                            eliminada=true;                            
                            break;
                        }
                        if(ebr->part_next!=-1){
                            FILE *myFile = fopen(disco->path.c_str(),"rb+");
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




                if (mbr->mbr_p[i].part_name == disco->name)
                {
                    fseek(archivo, mbr->mbr_p[i].part_start, SEEK_SET);

                    for (int j = 0; j < mbr->mbr_p[i].part_size; j++)
                    {
                        fwrite(&buff, sizeof(buff), 1, archivo);
                        fseek(archivo, mbr->mbr_p[i].part_start + j, SEEK_SET);
                    }

                    mbr->mbr_p[i].part_status = '0';
                    mbr->mbr_p[i].part_type = '-';
                    mbr->mbr_p[i].part_fit = '-';
                    mbr->mbr_p[i].part_start = -1;
                    mbr->mbr_p[i].part_size = -1;
                    for (int j = 0; j < 16; j++)
                    {
                        mbr->mbr_p[i].part_name[j] = '\0';
                    }

                    fseek(archivo, 0, SEEK_SET);
                    fwrite(mbr, sizeof(MBR), 1, archivo);
                    fclose(archivo);

                    if (mbr->mbr_p[i].part_type == 'e')
                    {
                        int inicio=mbr->mbr_p[i].part_start; 
                        int pos=searchLogicPartitionsDelete(disco, archivo, inicio);
                        if (pos == -1)
                        {
                            
                        }else{
                            deleteFull(archivo, pos);
                            fclose(archivo);
                        }

                        
                    }
                    eliminada=true;
                    break;
                }

                
            }
        
        }
        
        if(eliminada==false){
            //! Si la partición no existe deberá mostrar error. 
            cout<<"FFFFFFFFF   No se ha encontrado la particion a eliminar, verifique el nombre y ruta o talvez ya la borro! FFFFFFFFF"<<endl;
        }else{
            cout<<"\n         Se ha eliminado la Particion "<<disco->name<<endl;
        }
    }
    else
    {
        cout << "FFFFFFFFFFFFFF   Error " << disco->deleted << " No Valido   FFFFFFFFFFFFFFF" << endl;
    }
}


//! ██████████████████████████████████████████████  SE EXTIENDE LA PARTICION.  ██████████████████████████████████████████
void Fdisk::ExtendPartition(Fdisk *disco){
    //todo ████████████  VERIFICACION DE EXISTENCIA DEL DISCO  ████████████
    FILE *archivo;
    archivo = fopen(disco->path.c_str(), "rb+");

    if (archivo != NULL)
    {
        fseek(archivo, 0, SEEK_SET);
        MBR mbr;
        fread(&mbr, sizeof(MBR), 1, archivo);


        //*Este parámetro se utilizará para agregar o quitar espacio de la partición. Puede ser positivo o negativo.
        int unidadesAgregar=0;
        //todo ████████████  UNIDADES A EXTENDER DE LA PARTICION  ████████████
        //! se debe validar en que Unidades estamos hablando de creacion de la particion
        //*Este parámetro es opcional, si no se encuentra se creará una partición en Kilobytes.
        if (  disco->unit == "b")
        {        //*B: indicará que se utilizarán bytes.
            unidadesAgregar = stoi(disco->add);
        }
        else if (disco->unit == "m")
        {
                //*M:indicará que se utilizarán Megabytes(1024 * 1024bytes).
            unidadesAgregar = stoi(disco->add) * 1024 * 1024;
        }
        else if (disco->unit == "k" || disco->unit.empty())
        {
                //*K: indicará que se utilizarán Kilobytes(1024 bytes)
            unidadesAgregar = stoi(disco->add) * 1024;
            
        }else{
            //*Si se utiliza un valor diferente mostrará un mensaje de error.
            cout << "FFFFFFFFF      La Unidad de tamano de particion es Incorrecta       FFFFFFFFF"<< std::endl;
            return;
        }


        //! ████████████  VERIFICO QUE EL NOMBRE NO SEA REPETIDO  ████████████
        //* El nombre no debe repetirse dentro de las particiones de cada disco.
        bool p_existe = false;
        //? Deberá tener en cuenta las restricciones de teoría de particiones:
        for (int i = 0; i < 4; i++)//!solo son 4 particiones, entonces las recorro.
        {
            // La suma de primarias y extendidas debe ser como máximo 4.
            if (mbr.mbr_p[i].part_name == disco->name)//!si el nombre de la particion mbr  es igual al nombre
            {
                p_existe = true; //!si ya existe entonces me salgo :v   true==si existe el nombre
                break;
            }else{
            
            }
            if (mbr.mbr_p[i].part_type == 'e')//*E: en este caso se creará una partición extendida.
            {
                //Solo puede haber una partición extendida por disco.
                //*** va a buscar el nombre de la particion extendida.
                int existe = searchname(archivo, mbr.mbr_p[i].part_start, disco->name);
                if (existe != -1) //!-1 si no hay siguiente
                {   //?osea si si hay siguiente.
                    p_existe = true;
                    break;
                }
            }
        }

        //!En el caso de agregar espacio, deberá comprobar que exista espacio libre después de la partición.
        if(unidadesAgregar>0){
            if (p_existe)
            {

                for (int i = 0; i < 4; i++)
                {
                    //! Me ubico en la particion a Extender
                    if (mbr.mbr_p[i].part_name == disco->name)
                    {
                        int espacioOcupado=mbr.mbr_p[i].part_start + mbr.mbr_p[i].part_size;
                        int siguiente;
                        if (i < 3)
                        {
                            siguiente = mbr.mbr_tamano;
                            for (int j = i + 1; j < 4; j++)
                            {
                                if (mbr.mbr_p[j].part_status == '1')
                                {
                                    siguiente = mbr.mbr_p[j].part_start;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            siguiente = mbr.mbr_tamano;
                        }

                        if ((espacioOcupado + unidadesAgregar) < siguiente)
                        {
                            int agrandar=mbr.mbr_p[i].part_size + unidadesAgregar;
                            mbr.mbr_p[i].part_size = agrandar;
                            cout << "Se ha agregado (extendido) " << disco->add << disco->unit << " la particion " << disco->name << "" << endl;
                        }
                        else
                        {
                           cout << "FFFFFFFF   No se ha podido AGREGAR espacio a : " << disco->name << "  FFFFFFF" << endl;
                        }

                        fseek(archivo, 0, SEEK_SET);
                        fwrite(&mbr, sizeof(MBR), 1, archivo);
                        fclose(archivo);
                        break;
                    }
                    
                }
    

            }
        
        }else if(unidadesAgregar<0){
            //!En el caso de quitar espacio se debe comprobar que quede espacio en la partición (no espacio negativo).
            if (p_existe)
            {

                for (int i = 0; i < 4; i++)
                {
                    //! Me ubico en la particion a Reducir
                    if (mbr.mbr_p[i].part_name == disco->name)
                    {
                        int llegaHasta = mbr.mbr_p[i].part_start + mbr.mbr_p[i].part_size;
                        int siguiente;
                        if (i < 3)
                        {
                            siguiente = mbr.mbr_tamano;
                            for (int j = i + 1; j < 4; j++)
                            {
                                if (mbr.mbr_p[j].part_status == '1')
                                {
                                    siguiente = mbr.mbr_p[j].part_start;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            siguiente = mbr.mbr_tamano;
                        }

                        if (siguiente > (llegaHasta + unidadesAgregar))
                        {
                            int encoger=mbr.mbr_p[i].part_size + unidadesAgregar;
                            mbr.mbr_p[i].part_size = encoger;
                            cout << "Se ha quitado (reducido) " << disco->add << disco->unit << " la particion " << disco->name << "" << endl;
                        }
                        else
                        {
                            cout << "FFFFFFFF   No se ha podido quitar espacio a : " << disco->name << "  FFFFFFF" << endl;
                        }

                        fseek(archivo, 0, SEEK_SET);
                        fwrite(&mbr, sizeof(MBR), 1, archivo);
                        fclose(archivo);
                        break;
                    }

                 
                }
        

            }
        
        }else{
            cout<<"No se agrego ni se quito espacio de la particion, tamano extension:"<<unidadesAgregar<<endl;
        }
    
    }else{
        cout << "Error!\n El disco no existe\n";
        return;
    }

    
}






