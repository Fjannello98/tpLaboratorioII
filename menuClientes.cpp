#ifndef MENUCLIENTES_CPP_INCLUDED
#define MENUCLIENTES_CPP_INCLUDED

#include <iostream>
using namespace std;
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "rlutil.h"
using namespace rlutil;

#include "funciones.h"
#include "menuClientes.h"
#include "validations.h"



enum MENU_CLIENTES{
      OPCION_SALIR_DE_MENUCLIENTES,
      OPCION_CARGAR_CLIENTE,
      OPCION_LISTADO_CLIENTES,
      OPCION_VER_PAPELERA_CLIENTES,
      OPCION_BUSCAR_CLIENTE,
      OPCION_CAMBIAR_PAPELERA_CLIENTE,
      OPCION_BORRAR_CLIENTE
};

int menuClientes(){
   int opc;
  while(true){
      cls();
      gotoxy(55,4);
      cout << "MENU CLIENTES" << endl;
      LINEA_EN_X(40,86,6,4);
      LINEA_EN_X(40,86,16,4);
      LINEA_EN_Y(6,17,39,4);
      LINEA_EN_Y(6,17,86,4);
      gotoxy(45,8);
      cout << "1. Cargar cliente" << endl;
      gotoxy(45,9);
      cout << "2. Ver listado de clientes" << endl;
      gotoxy(45,10);
      cout << "3. Ver clientes en Papelera" << endl;
      gotoxy(45,11);
      cout << "4. Buscar cliente por DNI" << endl;
      gotoxy(45,12);
      cout << "5. Borrar/Recuperar cliente de Papelera"<< endl;
      gotoxy(45,13);
      cout << "6. Borrar un cliente de forma permanente"<< endl;
      gotoxy(45,14);
      cout << "0. Volver al menu anterior" << endl;
      gotoxy(50,19);
      cout << "SELECCIONE UNA OPCION: " << endl;
      gotoxy(72,19);
      cin>>opc;
      system("cls");
      switch(opc){
        case OPCION_CARGAR_CLIENTE:
                {
                 gotoxy(55,3);
                 cout<<"CARGA DE UN CLIENTE";
                 LINEA_EN_X(50,79,4,4);
                 cout<<endl<<endl;
                 Cliente regCliente;
                 regCliente.Cargar();
                 break;
                }
        case OPCION_LISTADO_CLIENTES:
                {
                 gotoxy(55,3);
                 cout<<"CLIENTES ACTIVOS";
                 LINEA_EN_X(50,77,4,4);
                 cout<<endl<<endl;
                 listarClientesActivos();
                 break;
                }
        case OPCION_VER_PAPELERA_CLIENTES:
                {
                 gotoxy(55,3);
                 cout<<"CLIENTES EN PAPELERA";
                 LINEA_EN_X(50,76,4,4);
                 cout<<endl<<endl;
                 listarClientesEnPapelera();
                 break;
                }
        case OPCION_BUSCAR_CLIENTE:
                {
                 gotoxy(55,3);
                 cout<<"BUSCAR UN CLIENTE POR DNI";
                 LINEA_EN_X(50,85,4,4);
                 cout<<endl<<endl;
                 buscarCliente();
                 break;
                }
        case OPCION_CAMBIAR_PAPELERA_CLIENTE:
                {
                 gotoxy(55,3);
                 cout<<"CAMBIAR ESTADO DE CLIENTE";
                 LINEA_EN_X(50,85,4,4);
                 cout<<endl<<endl;
                 int dni,pos;
                 cout<< "Ingrese el dni del cliente: ";
                 cin>>dni;
                 cout<<endl;
                 pos=buscarPosCliente(dni);
                 if (pos==-1){
                     cout<<"No se ha encontrado un cliente con ese DNI"<<endl;
                     break;
                 }
                 changeClientePapelera(pos);
                 break;
                }
        case OPCION_BORRAR_CLIENTE:
                {
                gotoxy(45,3);
                cout<<"BORRAR UN CLIENTE PERMANENTEMENTE";
                gotoxy(30,4);
                cout<<"(¡Solo se pueden borrar clientes sin operaciones asociadas!)";
                LINEA_EN_X(25,95,5,4);
                cout<<endl<<endl;
                int dni;
                cout<<"Ingrese el DNI del cliente a eliminar: ";
                cin>>dni;
                bool tieneOperaciones=buscarClienteEnOperaciones(dni);
                if (tieneOperaciones){
                  cout<<"El dni está asociado a un cliente con operaciones. Elimine primero las operaciones asociadas o pase el cliente a la papelera en su lugar.";
                  break;
                }
                eliminarCliente(dni);
                break;
                }
        case OPCION_SALIR_DE_MENUCLIENTES: return 0;
                break;
        default: cout<<" OPCION INCORRECTA"<<endl;
                break;
      }
      cout<<endl;
      system("pause");
    }
    return 0;
}



void listarClientesActivos(){
     Cliente regCliente;
     int cantClientes= cantDeClientes();
     for(int i=0;i<cantClientes;i++){
        bool leyo=regCliente.leerDeDisco(i);
        if (leyo==false) {
                cout<<endl<< "No pudo leer el cliente";
                return;
        }
        if (regCliente.getEstado()==true){
                regCliente.Mostrar();
        }
        cout<<endl<<endl;
     }
     return;
}

void listarClientesEnPapelera(){
     Cliente regCliente;
     int cantClientes= cantDeClientes();
     for(int i=0;i<cantClientes;i++){
        bool leyo=regCliente.leerDeDisco(i);
        if (leyo==false) {
                cout<<endl<< "No pudo leer el cliente";
                return;
        }
        if (regCliente.getEstado()==false){
                regCliente.Mostrar();
        }
        cout<<endl<<endl;
     }
     return;
}


void buscarCliente(){
     int dni,pos;
     Cliente regCliente;
     cout<< "Ingrese el dni del cliente: ";
     cin>>dni;
     cout<<endl;
     pos=buscarPosCliente(dni);
     if (pos==-1){
         cout<<"No se ha encontrado un cliente con ese DNI"<<endl;
         return;
     }
     bool leyo=regCliente.leerDeDisco(pos);
     if (leyo==true){
          cout<<"CLIENTE ENCONTRADO:" <<endl;
          regCliente.Mostrar();
          return;
     }
     cout<<"No se pudo abrir el archivo de clientes"<<endl;
}



void changeClientePapelera(int pos){
     Cliente regCliente;
     bool leyo = regCliente.leerDeDisco(pos);
     if (leyo == false) return;
     if (regCliente.getEstado()==true){
             cout<<"El Cliente se encuentra en el registro."<<endl;
             cout<<"Esta seguro/a que desea enviar a la papelera al vendededor/a "<< regCliente.getNombre();
             cout<<" "<< regCliente.getApellido()<<"?";
     }
     else if (regCliente.getEstado()==false){
             cout<<"El Cliente se encuentra la papelera"<<endl;
             cout<<"Esta seguro/a que desea restaurar de la papelera al vendededor/a "<< regCliente.getNombre();
             cout<<" "<< regCliente.getApellido()<<"?";
     }
     cout<<endl<<"1-Si 2-No: ";"\n";
     int rta;
     cin>>rta;
     while (rta!=1 && rta!=2){
       cout<<endl<<"Ingrese una opcion valida: ";
       cin>>rta;
     }
     if(rta==2){
       cout<<endl<<"Operacion cancelada.";
       return;
     }
     if (regCliente.getEstado()==true){
               regCliente.setEstado(false);
               cout<<endl<<"El Cliente se enviara a la papelera..."<<endl;
     }
     else if (regCliente.getEstado()==false){
               regCliente.setEstado(true);
               cout<<endl<<"El Cliente se restaurara de la papelera..."<<endl;
     }
     bool escribio=regCliente.grabarEnDisco(pos);
     if (escribio==false) {
            cout<<"Proceso fallido";
            return;
     }
     cout<<"Proceso exitoso";

};

void eliminarCliente(int dni){
     int tam = cantDeClientes(),pos;
     Cliente *vecCliente;
     vecCliente= new Cliente[tam];
     pos=buscarPosCliente(dni);

     if (pos==-1){
        cout<<"El cliente no existe."<<endl;
        delete vecCliente;
        return;
     }
     FILE *p;
     p=fopen("Clientes.dat","rb");
     if (p==NULL){
            cout<<"No se pudo abrir el archivo de clientes";
            fclose(p);
            delete vecCliente;
            return;
     }
     fread(vecCliente,sizeof (Cliente),tam,p);
     fclose(p);
     cout<<"Esta seguro/a que desea eliminar al cliente "<< vecCliente[pos].getNombre();
     cout<<" "<< vecCliente[pos].getApellido()<<"?";
     cout<<endl<<"1-Si 2-No: ";"\n";
     int rta;
     cin>>rta;
     while (rta!=1 && rta!=2){
                cout<<endl<<"Ingrese una opcion valida: ";
                cin>>rta;
     }
     if(rta==2){
                cout<<endl<<"Operacion cancelada.";
                return;
     }
     p=fopen("Clientes.dat","wb");
     if (p==NULL){
            cout<<"No se pudo abrir el archivo";
            fclose(p);
            delete vecCliente;
            return;
     }
     while(pos!=tam-1){
              vecCliente[pos]=vecCliente[pos+1];
              pos++;
     }
     fseek(p,0,0);
     fwrite(vecCliente,sizeof (Cliente),tam-1,p);
     cout<<"El cliente se ha eliminado correctamente"<<endl;
     fclose(p);
     delete vecCliente;

}





#endif // MENUCLIENTES_CPP_INCLUDED
