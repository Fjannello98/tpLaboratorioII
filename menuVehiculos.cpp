#ifndef MENUVEHICULOS_CPP_INCLUDED
#define MENUVEHICULOS_CPP_INCLUDED

#include <iostream>
using namespace std;
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "rlutil.h"
using namespace rlutil;

#include "funciones.h"
#include "menuVehiculos.h"

enum MENU_VEHICULOS{
      OPCION_SALIR_MENUVEHICULOS,
      OPCION_CARGAR_VEHICULO,
      OPCION_LISTADO_VEHICULOS,
      OPCION_VER_PAPELERA_VEHICULOS,
      OPCION_BUSCAR_VEHICULO,
      OPCION_CAMBIAR_PAPELERA_VEHICULO,
      OPCION_ELIMINAR_VEHICULO,
      OPCION_AGREGAR_STOCK_VEHICULOS

};
int menuVehiculos(){
  int opc;
  while(true){
      cls();
      gotoxy(55,4);
      cout << "MENU VEHICULOS" << endl;
      LINEA_EN_X(40,86,6,6);
      LINEA_EN_X(40,86,16,6);
      LINEA_EN_Y(6,17,39,6);
      LINEA_EN_Y(6,17,86,6);
      gotoxy(45,8);
      cout << "1. Cargar nuevo vehiculo" << endl;
      gotoxy(45,9);
      cout << "2. Ver lista de vehiculos disponibles" << endl;
      gotoxy(45,10);
      cout << "3. Ver vehiculos en papelera" << endl;
      gotoxy(45,11);
      cout << "4. Revisar stock por ID" << endl;
      gotoxy(45,12);
      cout << "5. Borrar/Recuperar vehiculo de Papelera " << endl;
      gotoxy(45,13);
      cout << "6. Borrar un vehiculo de forma permanente"<< endl;
      gotoxy(45,14);
      cout << "7. Agregar stock a un vehiculo"<< endl;
      gotoxy(45,15);
      cout << "0. Volver al menu anterior" << endl;
      gotoxy(50,19);
      cout << "SELECCIONE UNA OPCION: " << endl;
      gotoxy(72,19);
      cin>>opc;
      cls();
      switch(opc){
        case OPCION_CARGAR_VEHICULO:
                {
                 gotoxy(55,3);
                 cout<<"CARGA DE UN VEHICULO";
                 LINEA_EN_X(50,79,4,6);
                 cout<<endl<<endl;
                 Vehiculo regVehiculo;
                 regVehiculo.Cargar();
                 break;
                }
        case OPCION_LISTADO_VEHICULOS:
                {
                 gotoxy(55,3);
                 cout<<"VEHICULOS DISPONIBLES";
                 LINEA_EN_X(50,79,4,6);
                 cout<<endl<<endl;
                 listarVehiculosDisponibles();
                 break;
                }
       case OPCION_VER_PAPELERA_VEHICULOS:
                {
                 gotoxy(55,3);
                 cout<<"VEHICULOS EN PAPELERA";
                 LINEA_EN_X(50,79,4,6);
                 cout<<endl<<endl;
                 listarVehiculosEnPapelera();
                 break;
                }
        case OPCION_BUSCAR_VEHICULO:
                {
                 gotoxy(55,3);
                 cout<<"BUSCADOR DE VEHICULOS";
                 LINEA_EN_X(50,79,4,6);
                 cout<<endl<<endl;
                 buscarVehiculo();
                 break;
                }
        case OPCION_ELIMINAR_VEHICULO:
                {
                 gotoxy(55,3);
                 cout<<"ELIMINAR UN VEHICULO";
                 LINEA_EN_X(50,79,4,6);
                 cout<<endl<<endl;
                int idVehiculo;
                cout<<"Ingrese el ID del vehiculo que desea eliminar: ";
                cin>>idVehiculo;
                bool tieneOperaciones=buscarVehiculoEnOperaciones(idVehiculo);
                if (tieneOperaciones){
                  cout<<"Ese ID está asociado a un vehiculo con operaciones hechas. Paselo a la papelera en su lugar.";
                  break;
                }
                eliminarVehiculo(idVehiculo);
                break;
                }
        case OPCION_AGREGAR_STOCK_VEHICULOS:
                {
                 gotoxy(45,3);
                 cout<<"SUMAR/RESTAR STOCK A UN VEHICULO";
                 LINEA_EN_X(40,81,4,6);
                 cout<<endl<<endl;
                int id,stock;
                cout<<"Ingrese el ID del vehiculo: ";
                cin>>id;
                cout<<endl<<"Ingrese el numero de stock que ingreso a la sucursal. Si desea reducir el stock, ingrese la cantidad a reducir como numero negativo: ";
                cin>>stock;
                agregarStockVehiculo(id,stock);
                break;
                }
        case OPCION_CAMBIAR_PAPELERA_VEHICULO:
                {
                 gotoxy(55,3);
                 cout<<"CAMBIAR ESTADO DE VEHICULO";
                 LINEA_EN_X(50,85,4,6);
                 cout<<endl<<endl;
                 int id,pos;
                 cout<< "Ingrese el id del vehiculo: ";
                 cin>>id;
                 cout<<endl;
                 pos=buscarPosVehiculo(id);
                 if (pos==-1){
                     cout<<"No se ha encontrado un vehiculo con ese ID"<<endl;
                     break;
                 }
                 changeVehiculoPapelera(pos);
                 break;
                }
        case OPCION_SALIR_MENUVEHICULOS:
                return 0;
                break;
        default: cout<<" OPCION INCORRECTA"<<endl;
                break;
      }
      cout<<endl;
      system("pause");
    }
    return 0;
}


void listarVehiculosDisponibles(){
     Vehiculo regVehiculo;
     int cantVehiculos= cantDeVehiculos();
     for(int i=0;i<cantVehiculos;i++){
        bool leyo=regVehiculo.leerDeDisco(i);
        if (leyo==false) {
                cout<<endl<< "No pudo leer el vehiculo";
                return;
        }
        if (regVehiculo.getEstado()==true){
           regVehiculo.Mostrar();
        cout<<endl<<endl;
        }
     }
     return;
}

void listarVehiculosEnPapelera(){
     Vehiculo regVehiculo;
     int cantVehiculos= cantDeVehiculos();
     for(int i=0;i<cantVehiculos;i++){
        bool leyo=regVehiculo.leerDeDisco(i);
        if (leyo==false) {
                cout<<endl<< "No pudo leer el vehiculo";
                return;
        }
        if (regVehiculo.getEstado()==false){
           regVehiculo.Mostrar();
        cout<<endl<<endl;
        }
     }
     return;
}

void buscarVehiculo(){
     int idVehiculo,pos;
     Vehiculo regVehiculo;
     cout<< "Ingrese el ID del vehiculo: ";
     cin>>idVehiculo;
     cout<<endl;
     pos=buscarPosVehiculo(idVehiculo);
     if (pos==-1){
         cout<<"No se ha encontrado un vehiculo con ese ID"<<endl;
         return;
     }
     bool leyo=regVehiculo.leerDeDisco(pos);
     if (leyo==true){
          cout<<"VEHICULO ENCONTRADO:" <<endl;
          regVehiculo.Mostrar();
          return;
     }
     cout<<"No se pudo abrir el archivo de vehiculos"<<endl;
}



void changeVehiculoPapelera(int pos){
     Vehiculo regVehiculo;
     bool leyo = regVehiculo.leerDeDisco(pos);
     if (leyo == false) return;
     if (regVehiculo.getEstado()==true){
             cout<<"El vehiculo se encuentra disponible."<<endl;
             cout<<"Esta seguro/a que desea enviar a la papelera al vehiculo "<< regVehiculo.getMarca();
             cout<<" "<< regVehiculo.getModelo()<<"?";
     }
     else if (regVehiculo.getEstado()==false){
             cout<<"El vehiculo se encuentra la papelera."<<endl;
             cout<<"Esta seguro/a que desea restaurar de la papelera al vehiculo "<< regVehiculo.getMarca();
             cout<<" "<< regVehiculo.getModelo()<<"?";
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
     if (regVehiculo.getEstado()==true){
               regVehiculo.setEstado(false);
               cout<<endl<<"El vehiculo se enviara a la papelera..."<<endl;
     }
     else if (regVehiculo.getEstado()==false){
               regVehiculo.setEstado(true);
               cout<<endl<<"El vehiculo se restaurara de la papelera..."<<endl;
     }
     bool escribio=regVehiculo.grabarEnDisco(pos);
     if (escribio==false) {
            cout<<"Proceso fallido";
            return;
     }
     cout<<"Proceso exitoso";
}

void eliminarVehiculo(int idVehiculo){
     int tam = cantDeVehiculos(),pos;
     Vehiculo regVehiculo,*vecVehiculo;
     vecVehiculo= new Vehiculo[tam];
     pos=buscarPosVehiculo(idVehiculo);
     if (pos==-1){
        cout<<"El vehiculo no existe."<<endl;
        delete vecVehiculo;
        return;
     }
     FILE *p;
     p=fopen("Vehiculos.dat","rb");
     if (p==NULL){
            cout<<"No se pudo abrir el archivo";
            fclose(p);
            delete vecVehiculo;
            return;
     }
     fread(vecVehiculo,sizeof (Vehiculo),tam,p);
     fclose(p);
     cout<<"Esta seguro/a que desea eliminar al vehiculo "<< vecVehiculo[pos].getMarca()<<" ";
     cout<<vecVehiculo[pos].getModelo()<<"?";

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
     p=fopen("Vehiculos.dat","wb");
     if (p==NULL){
            cout<<"No se pudo abrir el archivo";
            fclose(p);
            delete vecVehiculo;
            return;
     }
     while(pos!=tam-1){
              vecVehiculo[pos]=vecVehiculo[pos+1];
              pos++;
     }
     fseek(p,0,0);
     fwrite(vecVehiculo,sizeof (Vehiculo),tam-1,p);
     cout<<"El vehiculo se ha eliminado correctamente"<<endl;
     fclose(p);
     delete vecVehiculo;

}

void agregarStockVehiculo(int idVehiculo,int stock){
      int stockActual,aux=stock;
      Vehiculo regVehiculo;
      int pos=buscarPosVehiculo(idVehiculo);
      if(pos==-1){
            cout<<endl<<"El vehiculo no existe en el archivo.";
            return;
      }
      bool leyoVehiculo = regVehiculo.leerDeDisco(pos);
      if (!leyoVehiculo){
            cout<<endl<<"Error al buscar el vehiculo.";
            return;
      }
      stockActual=regVehiculo.getStock();
      aux+=stockActual;
      regVehiculo.setStock(aux);
      bool escribio = regVehiculo.grabarEnDisco(pos);
      if (!escribio){
        cout<<endl<<"Error al actualizar el stock";
        return;
      }
      cout<<"Stock actualizado. Stock actual de " << regVehiculo.getMarca() << " "<<regVehiculo.getModelo()<<": "<<aux;
      return;
}


#endif // MENUVEHICULOS_CPP_INCLUDED
