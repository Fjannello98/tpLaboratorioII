#ifndef CLSOPERACION_CPP_INCLUDED
#define CLSOPERACION_CPP_INCLUDED

#include <iostream>
using namespace std;
#include <cstdlib>
#include <cstdio>
#include <cstring>


#include "clsOperacion.h"
#include "clsFecha.h"
#include "validations.h"
#include "funciones.h"
#include "menuVehiculos.h"



void Operacion::setIdOperacion(const float idOperacion){this->idOperacion=idOperacion;}
void Operacion::setMonto(const float monto){this->monto=monto;}
void Operacion::setIdVehiculo(const int idVehiculo){this->idVehiculo=idVehiculo;}
void Operacion::setDniVendedor(const int dniVendedor){this->dniVendedor=dniVendedor;}
void Operacion::setDniCliente(const int dniCliente){this->dniCliente=dniCliente;}
void Operacion::setDominioVehiculo(const char *dominioVehiculo){strcpy(this->dominioVehiculo,dominioVehiculo);}
void Operacion::setFechadeInicio(const Fecha fechaDeInicio){this->fechaDeInicio=fechaDeInicio;}
void Operacion::setFechadeFin(const Fecha fechaDeFin){this->fechaDeFin=fechaDeFin;}
void Operacion::setVentaCompleta(const bool ventaCompleta){this->ventaCompleta=ventaCompleta;}
void Operacion::setGananciasAVendedor(const float gananciasAVendedor){this->gananciasAVendedor=gananciasAVendedor;}
void Operacion::setGananciasAConcesionaria(const float gananciasAConcesionaria){this->gananciasAConcesionaria=gananciasAConcesionaria;}
int Operacion::getIdOperacion(){return idOperacion;}
float Operacion::getMonto(){return monto;}
int Operacion::getIdVehiculo(){return idVehiculo;}
int Operacion::getDniVendedor(){return dniVendedor;}
int Operacion::getDniCliente(){return dniCliente;}
char* Operacion::getDominioVehiculo(){return dominioVehiculo;}
Fecha Operacion::getFechaDeInicio(){return fechaDeInicio;}
Fecha Operacion::getFechaDeFin(){return fechaDeFin;}
bool Operacion::getVentaCompleta(){return ventaCompleta;}
float Operacion::getGananciasAConcesionaria(){return gananciasAConcesionaria;}
float Operacion::getGananciasAVendedor(){return gananciasAVendedor;}





void Operacion::Cargar(){
    cout <<"Ingrese el ID de la operacion: ";
    cin >> idOperacion;"\n";
    idOperacion=validateIdOperacion(idOperacion);
    cout <<"Ingrese el monto de la venta: ";
    cin >> monto;"\n";
    monto=validateMonto(monto);
    cout <<"Ingrese el dominio del vehiculo. Patente ejemplo: LLNNNNLL (L: Letra, N:Numero entero) :  ";
    int val;
    cargarCadena(dominioVehiculo,7);"\n";
    val=validateDominio(dominioVehiculo,7);
    while(val!=0){
        cout <<"Ingrese el dominio del vehiculo nuevamente: ";
        cargarCadena(dominioVehiculo,7);"\n";
        val=validateDominio(dominioVehiculo,7);
    }
    cout <<"Ingrese la fecha de inicio de la venta: ";
    cout <<endl;
    fechaDeInicio.Cargar();"\n";
    fechaDeInicio=validateFechaDeInicio(fechaDeInicio);
    int rta;
    cout <<"La venta se cerro? 1-Si 2-No: ";
    cin >> rta;"\n";
    while( rta!= 1&& rta!=2){
        cout <<"Ingrese una respuesta valida (1 o 2): ";
        cin >> rta; "\n";
    }
    if (rta==2) ventaCompleta=false;
    if (rta==1){
            ventaCompleta=true;
            cout <<"Ingrese la fecha de fin de la venta: ";"\n";
            cout <<endl;
            fechaDeFin.Cargar();"\n";
            fechaDeFin=validateFechaDeFin(fechaDeFin, fechaDeInicio);
    }
    cout<<"Ingrese el ID del vehiculo de la operacion: ";
    cin >> idVehiculo;"\n";
    idVehiculo=validateVehiculoExiste(idVehiculo);
    idVehiculo=validateVehiculoStock(idVehiculo);
    if (idVehiculo==0) return;
    cout<<endl<<"Ingrese el DNI del cliente: ";
    cin >> dniCliente;"\n";
    dniCliente=validateClienteExiste(dniCliente);
    if (dniCliente==0) return;
    cout<<"Ingrese el DNI del vendedor: ";
    cin >> dniVendedor;"\n";
    dniVendedor=validateVendedorExiste(dniVendedor);
    if (dniVendedor==0) return;
    if (ventaCompleta==true) agregarStockVehiculo(idVehiculo,-1);
    gananciasAVendedor=Operacion::calculateGananciasAVendedor();
    gananciasAConcesionaria=monto-gananciasAVendedor;
    Operacion::cargarEnArchivo();
    cout<<"Venta cargada con exito.";
}


void Operacion::cargarEnArchivo(){
     FILE *p;
     p=fopen("Operaciones.dat","ab");
     if (p==NULL){
            cout<<"No se pudo abrir el archivo";
            return;
     }
     fwrite(this,sizeof (Operacion),1,p);
     fclose(p);
     return;
}


void Operacion::Mostrar(){
    Vehiculo regVehiculo;
    Vendedor regVendedor;
    Cliente regCliente;
    int pos=buscarPosVehiculo(idVehiculo);
    bool leyoVehiculo = regVehiculo.leerDeDisco(pos);
    if (!leyoVehiculo || pos == -1){
        cout<<endl<<"Error al mostrar operacion";
        return;
    }
    pos=buscarPosVendedor(dniVendedor);
    bool leyoVendedor = regVendedor.leerDeDisco(pos);
    if (!leyoVendedor || pos == -1){
        cout<<endl<<"Error al mostrar operacion";
        return;
    }
    pos=buscarPosCliente(dniCliente);
    bool leyoCliente = regCliente.leerDeDisco(pos);
    if (!leyoCliente || pos == -1){
        cout<<endl<<"Error al mostrar operacion";
        return;
    }
    cout<<endl<<"ID de la operacion: "<< idOperacion;
    cout<<endl<<"Veh?culo: ";
    cout<<regVehiculo.getMarca()<<" "<<regVehiculo.getModelo();
    cout<<endl<<"Dominio del vehiculo: "<<dominioVehiculo;
    cout<<endl<<"Vendedor: ";
    cout<<regVendedor.getNombre()<<" "<<regVendedor.getApellido();
    cout<<endl<<"Cliente: ";
    cout<<regCliente.getNombre()<<" "<<regCliente.getApellido();
    cout<<endl<<"Monto de la venta: $"<<monto ;
    cout<<endl<<"Ganancias del vendedor: $"<<gananciasAVendedor;


}


bool Operacion::leerDeDisco(const int pos){
        FILE *p;
        p=fopen("Operaciones.dat","rb");
        if (p==NULL){
                cout<<"No se pudo abrir el archivo";
                return false;
         }
        fseek(p, pos*sizeof *this, 0);
        bool leyo=fread(this, sizeof *this, 1, p);
        fclose(p);
        return leyo;
}

bool Operacion::grabarEnDisco(const int pos){
    FILE *p;
    p=fopen("Operaciones.dat","rb+");
    if (p==NULL){
            cout<<"No se pudo abrir el archivo";
            return false;
     }
    fseek(p, pos*sizeof *this, 0);
    bool escribio=fwrite(this, sizeof *this, 1, p);
    fclose(p);
    return escribio;
}


int Operacion::buscarPosEnDisco(const int idOperacion){
      FILE *p;
      p=fopen("Operaciones.dat","rb");
      if (p==NULL) return -1;
      int c=0,pos=-1;
      while(fread(this,sizeof (Operacion),1,p)==1){
         if(this->idOperacion==idOperacion){
                pos=c;
         }
          c++;
      }
      fclose(p);
      return pos;
}

int Operacion::calculateGananciasAVendedor(){
     Vendedor regVendedor;
     int pos=buscarPosVendedor(dniVendedor);
     regVendedor.leerDeDisco(pos);
     int ganancias=monto*regVendedor.getComisionPorcentaje()/float(100);
     return ganancias;
}

#endif // CLSOPERACION_CPP_INCLUDED
