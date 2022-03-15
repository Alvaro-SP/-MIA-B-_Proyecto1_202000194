//! Reporte MBR
//! Mostrará tablas con toda la información del MBR, así como de los EBR que se
//! pudieron haber creado.
#include <iostream>
#include "mkdisk.h"
#include "Fdisk.h"
#include "fstream"
#include "mount.h"
#include "v.h"
#include "rep.h"
#include <iomanip>
#include <stdlib.h>
#include <unistd.h>
string rutaglobal;
rep::rep(){

}
bool rep::isvalidDirectory(const char *path)
{
    // cout<<path<<endl;
    if (path == NULL)
    {
        return false;
    }

    DIR *directorio;
    bool existeono = false;
    
    directorio = opendir(path);

    if (directorio != NULL)
    {
        existeono = true;
        (void)closedir(directorio);
    }
    return existeono;
}

vector<string> rep::splitSimulated(string myargument, char quitar) // solo simulo un split
{
    int positioninitial = 0;
    int positionfound = 0;
    string palabra;
    vector<string> mycommand;
    while (positionfound >= 0)
    {
        
        positionfound = myargument.find(quitar, positioninitial);
        palabra = myargument.substr(positioninitial, positionfound - positioninitial);
        positioninitial = positionfound + 1;
        mycommand.push_back(palabra);
		// cout<<palabra<<endl;
    }
    return mycommand;
}


//* ██████████████████████████████████████  MBR  █████████████████████████████████████

MBR* rep::obtainMBR(char pathF[], string idi){

    // char id[idie.length()];
 
    // size_t i;
    // for ( i = 0; i < sizeof(idie); i++) {
    //     id[i] = idie[i];
    //    // cout << id[i];
    // }
    //*--------
    string paths="";
    char* id=&idi[0];
    string str(id);
    cout<<" Id a mostrar MBR de disco: " << str << endl;
    //* SI la longitud del ID es menor a 4 eso significa de que no es correcto            
    if(strlen(id)<4){
        cout<<"FFFFFFFF No se ha encontrado el Disco a desmontar: ID incorrecto  FFFFFFF";
        return NULL;
    }
    // 94   +   Numero  +   Letra
    char letra = str.at(3);
    cout<<" La letra: "<<letra<<endl;
    
    int contDisks = 0;
    bool existeDisco= false;
    while(partsMounted[contDisks]!=NULL){
        cout<<partsMounted[contDisks]->letter <<" con "<< letra<<endl;
        if(partsMounted[contDisks]->letter == letra){
            existeDisco = true;
            break;
        }
        contDisks++;
    }
    if(!existeDisco){
        cout<<"FFFFF Error debido a que el disco no existe. FFFFFF";
        return NULL;
    }

   
    int tampart= 0;
    bool existePart = true;
    int contadorPart = 0;

    
    //* recorro las particiones montadas y si encuentro una particion que coincida con el id entonces si existe.
    while((partsMounted[contDisks])->parts[contadorPart]!=NULL){
        if(strcmp((partsMounted[contDisks])->parts[contadorPart]->id,id)==0){
            existePart = false;// si existe
            paths=(partsMounted[contDisks])->path;
            break;
        }
        contadorPart++;
    }




    if (existePart)
    {

        cout << "La particion \"" << id <<"\" no ha sido encontrada para el reporte MBR" << endl;
    }


    FILE *myarchivo = fopen("GenPartitions.bin", "rb");
	struct GenPartition t1;
    bool abcde = false;
	if (abcde)
	{
		fread(&t1, 100, 1, myarchivo);
        cout<<"\n va por aqui"<<endl;
        
		while (!feof(myarchivo))
		{
            cout<<"a"<<endl;
            cout<<t1.id<<" con "<<id<<endl;
            if(t1.id == id){
                cout<<paths<<endl;
                paths=t1.ruta;
                break;
            }
            
			fread(&t1, 100, 1, myarchivo);
		}
	}
	else
	{
        
	};
	fclose(myarchivo);

    rutaglobal=paths;
    char* path=&paths[0];
    FILE *myFile;
    myFile = fopen(path,"rb+");
    if(myFile!=NULL){
        
    }else{
        cout<<"FFFFFFF No se encuentra el disco FFFFFF\n";
        return NULL;
    }
    fseek(myFile, 0, SEEK_SET);
    MBR *mbr = (MBR*)malloc(sizeof(MBR));
    fread(mbr,sizeof(MBR),1,myFile);
    fclose(myFile);
    return mbr;
}

EBR* rep::primerEBR(MBR *disco,char path[]){
    int i;
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

void rep::mbr(string nombres, string idi, string paths,string path_reports){
    char* path=&paths[0];
    char* nombre=&nombres[0];
    // 
    char* id=&idi[0];
    // char* pathr=&path_reports[0];


    //! ████████████  VERIFICACION DE LA RUTA  ████████████
    // Primero validamos de que exista la carpeta donde creare el disco.
    vector<string> ccarpetold = (splitSimulated(paths, '/'));
    vector<string> ccarpet ;

    string espacio = " ";
    bool com = false;    
    for (size_t i = 0; i < ccarpetold.size(); i++){//recorro mi vector de la ruta para ver si no hay espacios
        if (ccarpetold[i][0] != (char)00)//!si no es un (char)00
        {
            if (ccarpetold[i][0] != '#')//!si no es un comentario
            {
                if (com == false)//! y si com no ha sido modificado.
                {
                    ccarpet.push_back(ccarpetold[i]);//* meto la posicion de mi vector en el nuevo vector.
                }
            }
            else
            {
                com = true;
            }
        }
    }
    

    string tempath = "";
    string tempath2 = "";
    // cout<<ccarpet.size()<<endl;
    MBR mbr;
    if(ccarpet.size()>0){
        for (size_t  i = 0; i < ccarpet.size()-1; i++)
        {
            tempath += "/" + ccarpet[i];
            // cout<<ccarpet[i]<<"  -----------------------"<<endl;
            // Si las carpetas de la ruta no existen deberán crearse.
            // cout<<"tempath; "<<tempath<<endl;
            if (!isvalidDirectory(tempath.c_str()))
            {
                string comando = "mkdir " + tempath2 + "/\"" + ccarpet[i] + "\"";
                // cout<<"comando; "<<comando<<endl;
                system(comando.c_str());
            }
            tempath2 += "/" + ccarpet[i];
        }

    }







    MBR* disco;
    // ! necesito buscar el disco donde se ubica la particion con el idi dado
    try
    {
       disco = obtainMBR(path,id);
    }
    catch(...)
    {
         cout<<"FFFFFFFFFF   No se pudo generar el reporte, el disco de esa ruta es vacio.    FFFFFFFFFFFF\n";
        return;
    }
    
    
    cout<<"here"<<endl;
    if(disco==NULL){
        cout<<"FFFFFFFFFF   No se pudo generar el reporte, el disco de esa ruta es vacio.    FFFFFFFFFFFF\n";
        return;
    }

    FILE *myFile;
    myFile =  fopen("REPORTE_MBR_202000194.dot","w+");
    if (myFile==NULL)
    {
        cout<<"Error al crear el archivo\n";
        return;
    }
    if(myFile!=NULL){
    fseek(myFile, 0, SEEK_SET);
    fputs("digraph migraph{\n", myFile);
    fputs("     bgcolor=\"yellow:cyan\" ", myFile);
    fputs("    gradientangle=0", myFile);
    fputs("    label=\"", myFile);
    fputs(nombre, myFile);
    fputs(" en: ", myFile);
    fputs(path, myFile);
    fputs("\"", myFile);
    fputs("    fontcolor=\"black\"", myFile);
    fputs("    fontname=\"Helvetica,Arial,sans-serif\"", myFile);
    // fputs("bgcolor=\"yellow:cyan\" gradientangle=0  fontcolor=\"black\" fontname=\"Helvetica,Arial,sans-serif\"", myFile);
    fputs("", myFile);

    fputs("\n\ntbl [\nshape=plaintext\n label=<\n", myFile);
    
    fputs("<table border='0' cellborder='1' cellspacing='0'>\n",myFile);
    fputs("<tr><td colspan=\"3\" bgcolor=\"blue:cyan\">REPORTE DE MBR</td></tr>\n",myFile);
    fputs("<th><td>Nombre</td><td>Valor</td></th>\n",myFile);
    //* SETEO LOS DATOS DEL MBR
    //* STTEO EL TAMANO DEL MBR
    fputs("<tr><td bgcolor=\"lightblue\">mbr_tamaño</td><td bgcolor=\"lightblue\">",myFile);
    fputs(&to_string(disco->mbr_tamano)[0],myFile);
    fputs("</td></tr>\n",myFile);
    //* STTEO EL FECHA DE CREACION DEL MBR
    fputs("<tr><td bgcolor=\"lightblue\">mbr_Fecha_creación</td><td bgcolor=\"lightblue\">",myFile);
    fputs(disco->mbr_fecha_creacion,myFile);
    fputs("</td></tr>\n",myFile);
    //* STTEO EL SIGNATURE DEL MBR
    fputs("<tr><td bgcolor=\"lightblue\">mbr_disk_signature</td><td bgcolor=\"lightblue\">",myFile);
    fprintf(myFile, "%i", disco->mbr_disk_signature);
    fputs("</td></tr>\n",myFile);
    //* STTEO EL FIT DEL MBR
    fputs("<tr><td bgcolor=\"lightblue\">mbr_disk_fit</td><td bgcolor=\"lightblue\">",myFile);
    fprintf(myFile, "%s", disco->disk_fit);
    fputs("</td></tr>\n",myFile);
///* el nombre


    int i;
    PARTITION part;
    char colors[4][10];
    
    for(int i = 0; i < 10; i++)
        {
            colors[0][i] = 0;
        }
    strcat(colors[0],"#bcf7c1");
    for(int i = 0; i < 10; i++)
        {
            colors[1][i] = 0;
        }
    strcat(colors[1],"#f8fc92");
    for(int i = 0; i < 10; i++)
        {
            colors[2][i] = 0;
        }
    strcat(colors[2],"#fcc292");
    for(int i = 0; i < 10; i++)
        {
            colors[3][i] = 0;
        }
    strcat(colors[3],"#dfbcf7");
    cout<<"\n Generando el Dot..."<<endl;
    sleep(2);
    for(i=0;i<4;i++){
        // if(part.part_type=='p'||part.part_type=='P'||part.part_type=='E'||part.part_type=='e'){
        //     for(int j = 0; j < 10; i++)
        //     {
        //         colors[i][j] = 0;
        //     }
        //     strcat(colors[i],"#dfbcf7");
        // }else if(part.part_type=='l' || part.part_type=='L'){
        //     for(int j = 0; j < 10; i++)
        //     {
        //         colors[i][j] = 0;
        //     }
        //     strcat(colors[i],"#bcf7c1");
        // }
        part = disco->mbr_p[i];
        // if(strcmp((part.part_status , id)==0)
        
        if(part.part_status == '0') continue;

        //* SETEO EL NOMBRE DE LA PARTICION
        fputs("<tr><td colspan=\"2\" bgcolor=\"",myFile);
        fputs(colors[i],myFile);
        fputs("\">",myFile);


        cout<<"particion "<<i<<endl;
        cout<<part.part_name<<endl;
        cout<<part.part_fit<<endl;
        cout<<part.part_size<<endl;
        cout<<part.part_start<<endl;
        cout<<part.part_status<<endl;
        cout<<part.part_type<<endl;


        // fprintf(myFile, "%s", part.part_name);
        // cout<<part.part_name<<endl;
        fputs(part.part_name,myFile);
        fputs("</td></tr>\n",myFile);
        
        fputs("<tr><td bgcolor=\"",myFile);
        fputs(colors[i],myFile);
        fputs("\">part_status</td><td bgcolor=\"",myFile);
        fputs(colors[i],myFile);
        fputs("\">",myFile);
        fprintf(myFile, "%c", part.part_status);
        fputs("</td></tr>\n",myFile);
        
        fputs("<tr><td bgcolor=\"",myFile);
        fputs(colors[i],myFile);
        fputs("\">part_type</td><td bgcolor=\"",myFile);
        fputs(colors[i],myFile);
        fputs("\">",myFile);
        fprintf(myFile, "%c", part.part_type);
        fputs("</td></tr>\n",myFile);
   
        fputs("<tr><td bgcolor=\"",myFile);
        fputs(colors[i],myFile);
        fputs("\">part_fit</td><td bgcolor=\"",myFile);
        fputs(colors[i],myFile);
        fputs("\">",myFile);
        fprintf(myFile, "%c", part.part_fit);
        fputs("</td></tr>\n",myFile);
        
        fputs("<tr><td bgcolor=\"",myFile);
        fputs(colors[i],myFile);
        fputs("\">part_start</td><td bgcolor=\"",myFile);
        fputs(colors[i],myFile);
        fputs("\">",myFile);
        fprintf(myFile, "%d", part.part_start);
        fputs("</td></tr>\n",myFile);
        
        fputs("<tr><td bgcolor=\"",myFile);
        fputs(colors[i],myFile);
        fputs("\">part_size</td><td bgcolor=\"",myFile);
        fputs(colors[i],myFile);
        fputs("\">",myFile);
        fputs(&to_string(part.part_size)[0],myFile);
        fputs("</td></tr>\n",myFile);

        fputs("<tr><td bgcolor=\"",myFile);
        fputs(colors[i],myFile);
        fputs("\">part_name</td><td bgcolor=\"",myFile);
        fputs(colors[i],myFile);
        fputs("\">",myFile);
        fprintf(myFile, "%s", part.part_name);
        fputs("</td></tr>\n",myFile);

        if(part.part_type=='e' || part.part_type=='E'){
            //! SETEANDO LOS EBR

            // i = 0;
            // cout<<path<<endl;
            char* pathg=&rutaglobal[0];
            EBR *ebr = primerEBR(disco,pathg);
            // cout<<"corrido";
            // string nombreNodo = "tbl"+to_string(i+2);
            // fputs(nombreNodo.c_str(),myFile);
            // fputs(" [\nshape=plaintext\n label=<\n", myFile);
            
            // fputs("<table border='0' cellborder='1' cellspacing='0'>\n",myFile);
            // fputs("<tr><td colspan=\"3\">",myFile);
            // fputs("REPORTE DE EBR'S",myFile);
            // fputs("</td></tr>\n",myFile);
            while(ebr!=NULL){
                
                
            


                fputs("<tr><td colspan=\"3\">",myFile);
                fputs(ebr->part_name,myFile);
                fputs("</td></tr>\n",myFile);
                fputs("<th><td>Nombre</td><td>Valor</td></th>\n",myFile);
            
                fputs("<tr><td bgcolor=\"#fcc8c8\">part_status</td><td bgcolor=\"#fcc8c8\">",myFile);
                fprintf(myFile, "%c", ebr->part_status);
                fputs("</td></tr>\n",myFile);

                // fputs("<tr><td bgcolor=\"#fcc8c8\">part_type</td><td bgcolor=\"#fcc8c8\">",myFile);
                // fprintf(myFile, "%c", ebr->pa);
                // fputs("</td></tr>\n",myFile);
                
                fputs("<tr><td bgcolor=\"#fcc8c8\">part_fit</td><td bgcolor=\"#fcc8c8\">",myFile);
                fprintf(myFile, "%c", ebr->part_fit);
                fputs("</td></tr>\n",myFile);
                fputs("<tr><td bgcolor=\"#fcc8c8\">part_start",myFile);
                fputs("</td><td bgcolor=\"#fcc8c8\">",myFile);
                fprintf(myFile, "%d", ebr->part_start);
                fputs("</td></tr>\n",myFile);
            
                fputs("<tr><td bgcolor=\"#fcc8c8\">part_size</td><td bgcolor=\"#fcc8c8\">",myFile);
                fputs(&to_string(ebr->part_size)[0],myFile);
                fputs("</td></tr>\n",myFile);
                
                fputs("<tr><td bgcolor=\"#fcc8c8\">part_next</td><td bgcolor=\"#fcc8c8\">",myFile);
                fprintf(myFile, "%d", ebr->part_next);
                fputs("</td></tr>\n",myFile);
                
                


                if(ebr->part_next!=-1){

                    FILE *myFile = fopen(pathg,"rb+");
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
                i++;
            }
            // fputs("</table>\n",myFile);
            // fputs(">];\n", myFile);
        }
    }
    
    fputs("</table>\n",myFile);
    fputs(">];\n\n", myFile);
    fputs("\n\ntbl3 [\nshape=plaintext\n label=<\n", myFile);
    fputs("<table border='0' cellborder='1' cellspacing='0'>\n",myFile);
            fputs("<tr><td colspan=\"3\">",myFile);
            fputs("REPORTE DE EBRS",myFile);
            fputs("</td></tr>\n",myFile);
            fputs("<th><td>Nombre</td><td>Valor</td></th>\n",myFile);
            // fputs(colors[i],myFile);
            // fputs("\">",myFile);
    for(i=0;i<4;i++){
        // if(part.part_type=='p'||part.part_type=='P'||part.part_type=='E'||part.part_type=='e'){
        //     for(int j = 0; j < 10; i++)
        //     {
        //         colors[i][j] = 0;
        //     }
        //     strcat(colors[i],"#dfbcf7");
        // }else if(part.part_type=='l' || part.part_type=='L'){
        //     for(int j = 0; j < 10; i++)
        //     {
        //         colors[i][j] = 0;
        //     }
        //     strcat(colors[i],"#bcf7c1");
        // }
        part = disco->mbr_p[i];
        // if(strcmp((part.part_status , id)==0)
        
        if(part.part_status == '0') continue;

        
        if(part.part_type=='e' || part.part_type=='E'){
            //! SETEANDO LOS EBR

            // i = 0;
            // cout<<path<<endl;
            // char* pathg=&rutaglobal[0];
            // EBR *ebr = primerEBR(disco,pathg);
            // cout<<"corrido";
            // string nombreNodo = "tbl"+to_string(i+2);
            // fputs(nombreNodo.c_str(),myFile);
            // fputs(" [\nshape=plaintext\n label=<\n", myFile);
            
            // fputs("<table border='0' cellborder='1' cellspacing='0'>\n",myFile);
            // fputs("<tr><td colspan=\"3\">",myFile);
            // fputs("REPORTE DE EBR'S",myFile);
            //* SETEO EL NOMBRE DE LA PARTICION
            // fputs("<tr><td colspan=\"2\" bgcolor=\"",myFile);
            // fputs(colors[i],myFile);
            // fputs("\">",myFile);


            // cout<<"particion "<<i<<endl;
            // cout<<part.part_name<<endl;
            // cout<<part.part_fit<<endl;
            // cout<<part.part_size<<endl;
            // cout<<part.part_start<<endl;
            // cout<<part.part_status<<endl;
            // cout<<part.part_type<<endl;


            // fprintf(myFile, "%s", part.part_name);
            // cout<<part.part_name<<endl;
            fputs("<tr><td colspan=\"3\">",myFile);
            fputs(part.part_name,myFile);
            fputs("</td></tr>\n",myFile);
            
            fputs("<tr><td bgcolor=\"",myFile);
            fputs("#bcf7c1",myFile);
            fputs("\">part_status</td><td bgcolor=\"",myFile);
            fputs("#bcf7c1",myFile);
            fputs("\">",myFile);
            fprintf(myFile, "%c", part.part_status);
            fputs("</td></tr>\n",myFile);
            
            fputs("<tr><td bgcolor=\"",myFile);
            fputs("#bcf7c1",myFile);
            fputs("\">part_type</td><td bgcolor=\"",myFile);
            fputs("#bcf7c1",myFile);
            fputs("\">",myFile);
            fprintf(myFile, "%c", part.part_type);
            fputs("</td></tr>\n",myFile);
    
            fputs("<tr><td bgcolor=\"",myFile);
            fputs("#bcf7c1",myFile);
            fputs("\">part_fit</td><td bgcolor=\"",myFile);
            fputs("#bcf7c1",myFile);
            fputs("\">",myFile);
            fprintf(myFile, "%c", part.part_fit);
            fputs("</td></tr>\n",myFile);
            
            fputs("<tr><td bgcolor=\"",myFile);
            fputs("#bcf7c1",myFile);
            fputs("\">part_start</td><td bgcolor=\"",myFile);
            fputs("#bcf7c1",myFile);
            fputs("\">",myFile);
            fprintf(myFile, "%d", part.part_start);
            fputs("</td></tr>\n",myFile);
            
            fputs("<tr><td bgcolor=\"",myFile);
            fputs("#bcf7c1",myFile);
            fputs("\">part_size</td><td bgcolor=\"",myFile);
            fputs("#bcf7c1",myFile);
            fputs("\">",myFile);
            fputs(&to_string(part.part_size)[0],myFile);
            fputs("</td></tr>\n",myFile);

            fputs("<tr><td bgcolor=\"",myFile);
            fputs("#bcf7c1",myFile);
            fputs("\">part_name</td><td bgcolor=\"",myFile);
            fputs("#bcf7c1",myFile);
            fputs("\">",myFile);
            fprintf(myFile, "%s", part.part_name);
            fputs("</td></tr>\n",myFile);

            
        }
    }
    fputs("</table>\n",myFile);
     fputs(">];\n", myFile);
    
    fputs("}\n",myFile);
    


    fclose (myFile);
    string pathString(path);
    string command = "dot -Tpng REPORTE_MBR_202000194.dot -o \""+pathString+"\"";
    system(command.c_str());
    cout<<"\n Generando la imagen..."<<endl;
    sleep(2);
    cout<<"\n Se ha generado el Reporte de MBR sin problemas, vaya a: \n\t\t"<<pathString<<"  para verlo"<<endl;
    // i++;
    }else{
        cout<<"\n FFFFFFFFFFF Error el archivo es Nulo a saber porque...   FFFFFFFFFFF";
    }
    
    
     
}

//* ██████████████████████████████████████  DISK  █████████████████████████████████████

//* ██████████████████████████████████████  MBR  █████████████████████████████████████

//* ██████████████████████████████████████  MBR  █████████████████████████████████████

//* ██████████████████████████████████████  MBR  █████████████████████████████████████







