#ifndef FUNCIONES_CPP_INCLUDED
#define FUNCIONES_CPP_INCLUDED
#include <ctime>


#include "funciones.h"
#include "rlutil.h"
using namespace rlutil;
#include "clsOperacion.h"


void cargarCadena(char *pal, int tam){
  int i;
  fflush(stdin);
  for(i=0;i<tam;i++){
      pal[i]=cin.get();
	  if(pal[i]=='\n') break;
	  }
  pal[i]='\0';
  fflush(stdin);
}

Fecha getFechaDeHoy(){
     time_t t;
     t = time(NULL);
     struct tm *fecha;
     fecha = localtime(&t);
     Fecha fechaDeHoy;
     fechaDeHoy.setDia(fecha->tm_mday);
     fechaDeHoy.setMes(fecha->tm_mon+1);
     fechaDeHoy.setAnio(fecha->tm_year+1900);
     return fechaDeHoy;
}


void LINEA_EN_Y(const int yInicial,const int yFinal, const int x,const int color){
   void gotoxy(int x,int y);
   for (int i=yInicial;i<yFinal;i++){
         gotoxy(x,i);
         setBackgroundColor(color);
         cout << "  ";
   }
   setBackgroundColor(0);
}
void LINEA_EN_X(const int xInicial,const int xFinal,const int y,const int color){
   void gotoxy(int x,int y);
   for (int i=xInicial;i<xFinal;i++){
         gotoxy(i,y);
         setBackgroundColor(color);
         cout << " ";
   }
   setBackgroundColor(0);
}


// Buscar Posicion

int buscarPosOperacion(const int cod){
   FILE *p;
   Operacion regOperacion;
   p=fopen("Operaciones.dat","rb");
   if (p==NULL){
    fclose(p);
    return -1;
   }
   int pos=-1,c=0;
   while(fread(&regOperacion,sizeof (Operacion),1,p)==1){
     if (regOperacion.getIdOperacion()== cod){
        pos=c;
     }
     c++;
   }
   fclose(p);
   return pos;
}

int buscarPosCliente(const int dni){
   FILE *p;
   Cliente regCliente;
   p=fopen("Clientes.dat","rb");
   if (p==NULL){
    return -1;
   }
   int pos=-1,c=0;
   while(fread(&regCliente,sizeof (Cliente),1,p)==1){
     if (regCliente.getDni()== dni){
        pos=c;
     }
     c++;
   }
   fclose(p);
   return pos;
}

int buscarPosVendedor(const int dni){
   FILE *p;
   Vendedor regVendedor;
   p=fopen("Vendedores.dat","rb");
   if (p==NULL){
    return -1;
   }
   int pos=-1,c=0;
   while(fread(&regVendedor,sizeof (Vendedor),1,p)==1){
     if (regVendedor.getDni()== dni){
        pos=c;
     }
     c++;
   }
   fclose(p);
   return pos;
}

int buscarPosVehiculo(const int id){
   FILE *p;
   Vehiculo regVehiculo;
   p=fopen("Vehiculos.dat","rb");
   if (p==NULL){
    return -1;
   }
   int pos=-1,c=0;
   while(fread(&regVehiculo,sizeof (Vehiculo),1,p)==1){
     if (regVehiculo.getIdVehiculo()== id){
        pos=c;
     }
     c++;
   }
   fclose(p);
   return pos;
}
#endif // FUNCIONES_CPP_INCLUDED
