#ifndef MENUVENTAS_CPP_INCLUDED
#define MENUVENTAS_CPP_INCLUDED

#include <iostream>
using namespace std;
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "rlutil.h"
using namespace rlutil;

#include "funciones.h"
#include "clsFecha.h"
#include "clsOperacion.h"
#include "menuVentas.h"
#include "menuVehiculos.h"

enum MENU_VENTAS{
      OPCION_SALIR_MENUVENTAS,
      OPCION_CARGAR_VENTA,
      OPCION_LISTADO_VENTAS,
      OPCION_ACTUALIZAR_ESTADO,
      OPCION_ELIMINAR_VENTA
};


int menuVentas(){
  int opc;
  while(true){
      cls();
      gotoxy(55,4);
      cout << "MENU VENTAS" << endl;
      LINEA_EN_X(40,86,6,5);
      LINEA_EN_X(40,86,16,5);
      LINEA_EN_Y(6,17,39,5);
      LINEA_EN_Y(6,17,86,5);
      gotoxy(45,8);
      cout << "1. Cargar venta" << endl;
      gotoxy(45,9);
      cout << "2. Ver listado de operaciones" << endl;
      gotoxy(45,10);
      cout << "3. Chequear/actualizar ventas" <<endl;
      gotoxy(45,11);
      cout << "4. Eliminar una operacion" <<endl;
      gotoxy(45,12);
      cout << "0. Volver al menu anterior" << endl;
      gotoxy(50,19);
      cout << "SELECCIONE UNA OPCION: " << endl;
      gotoxy(72,19);
      cin>>opc;
      cls();
      switch(opc){
        case OPCION_CARGAR_VENTA:
                   {
                    gotoxy(55,3);
                    cout<<"CARGA DE VENTA";
                    LINEA_EN_X(50,79,4,5);
                    cout<<endl<<endl;
                    Operacion regOperacion;
                    regOperacion.Cargar();
                     break;
                   }

        case OPCION_LISTADO_VENTAS:
                   {
                    gotoxy(55,3);
                    cout<<"HISTORIAL OPERACIONES";
                    LINEA_EN_X(50,79,4,5);
                    cout<<endl<<endl;
                    listarOperaciones();
                    break;
                   }
        case OPCION_ACTUALIZAR_ESTADO:
                  {
                    gotoxy(50,3);
                    cout<<"CHEQUEAR ESTADO VENTA";
                    LINEA_EN_X(45,78,4,5);
                    cout<<endl<<endl;
                    int cant=cantDeOperaciones();
                    if (cantDeOperaciones==0){
                        cout<<"No hay operaciones disponibles";
                        break;
                    }
                    int cod,pos;
                    cout<<"Ingrese el codigo ID de la venta: ";
                    cin>>cod;
                    pos = buscarPosOperacion(cod);
                    if (pos==-1){
                       cout<<"La operación con ese ID no existe";
                       break;
                    }
                    actualizarEstadoOperacion(pos);
                  }
                   break;
        case OPCION_ELIMINAR_VENTA:
                 {
                    gotoxy(55,3);
                    cout<<"ELIMINAR VENTA";
                    LINEA_EN_X(50,74,4,5);
                    cout<<endl<<endl;
                    int id;
                    cout<<"Ingrese el ID de la operacion: ";
                    cin>>id;
                    eliminarOperacion(id);
                    break;
                 }
        case OPCION_SALIR_MENUVENTAS:
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


void listarOperaciones(){
     Operacion regOperacion;
     int cantOperaciones= cantDeOperaciones();
     for(int i=0;i<cantOperaciones;i++){
        bool leyo=regOperacion.leerDeDisco(i);
        if (leyo==false) {
                cout<<endl<< "No pudo leer la operacion";
                return;
        }
        regOperacion.Mostrar();
        cout<<endl;
     }
     return;
}


void actualizarEstadoOperacion(int pos){
   Operacion regOperacion;
   regOperacion.leerDeDisco(pos);
   cout<<"La venta se encuentra en estado  ";
   if (regOperacion.getVentaCompleta()==true){
    cout<< "cerrado, iniciada el: ";
    regOperacion.getFechaDeInicio().Mostrar();
    cout<< "Fue cerrada el: ";
    regOperacion.getFechaDeFin().Mostrar();
    return;
   }
   cout<<" abierto, iniciada  el ";
   regOperacion.getFechaDeInicio().Mostrar();
   cout<<endl<<"¿Desea cerrar la venta en el dia de hoy? 1-Si  2- No: ";
   int rta;
   cin >> rta;
   while (rta!=1 && rta !=2){
     cout<< endl << "Error! Ingrese una rta valida";
   }
   if (rta==2) {
     cout<<endl<<"Operacion cancelada";
     return;
   }
   regOperacion.setVentaCompleta(true);
   regOperacion.setFechadeFin(getFechaDeHoy());
   regOperacion.grabarEnDisco(pos);
   agregarStockVehiculo(regOperacion.getIdVehiculo(),-1);
   cout<<endl<<"Operacion actualizada";
}



void eliminarOperacion(int id){
     int tam = cantDeOperaciones(),pos;
     Operacion *vecOperacion;
     vecOperacion= new Operacion[tam];
     pos=buscarPosOperacion(id);
     if (pos==-1){
        cout<<"La operacion con ese ID no existe."<<endl;
        delete vecOperacion;
        return;
     }
     FILE *p;
     p=fopen("Operaciones.dat","rb");
     if (p==NULL){
            cout<<"No se pudo abrir el archivo de operaciones";
            fclose(p);
            delete vecOperacion;
            return;
     }
     fread(vecOperacion,sizeof (Operacion),tam,p);
     fclose(p);
     cout<<"Esta seguro/a que desea eliminar la operacion número "<< id <<"?";
     cout<<endl<<"1-Si 2-No: ";"\n";
     int rta;
     cin>>rta;
     while (rta!=1 && rta!=2){
                cout<<endl<<"Ingrese una opcion valida: ";
                cin>>rta;
     }
     if(rta==2){
                cout<<endl<<"Operacion de borrado cancelada.";
                return;
     }
     p=fopen("Operaciones.dat","wb");
     if (p==NULL){
            cout<<"Error al borrar operacion";
            fclose(p);
            delete vecOperacion;
            return;
     }
     while(pos!=tam-1){
              vecOperacion[pos]=vecOperacion[pos+1];
              pos++;
     }
     fseek(p,0,0);
     fwrite(vecOperacion,sizeof (Operacion),tam-1,p);
     cout<<"La operacion se ha eliminado correctamente"<<endl;
     fclose(p);
     delete vecOperacion;

}



#endif // MENUVENTAS_CPP_INCLUDED
