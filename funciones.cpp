#ifndef FUNCIONES_CPP_INCLUDED
#define FUNCIONES_CPP_INCLUDED
#include <ctime>
#include "funciones.h"
#include "rlutil.h"
using namespace rlutil;

#include "clsOperacion.h"
#include "clsFecha.h"

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


void LINEA_EN_Y(int yInicial, int yFinal, int x, int color){
   void gotoxy(int x,int y);
   for (int i=yInicial;i<yFinal;i++){
         gotoxy(x,i);
         setBackgroundColor(color);
         cout << "  ";
   }
   setBackgroundColor(0);
}
void LINEA_EN_X(int xInicial, int xFinal, int y,int color){
   void gotoxy(int x,int y);
   for (int i=xInicial;i<xFinal;i++){
         gotoxy(i,y);
         setBackgroundColor(color);
         cout << " ";
   }
   setBackgroundColor(0);
}


// Buscar Posicion

int buscarPosOperacion(int cod){
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

#endif // FUNCIONES_CPP_INCLUDED
