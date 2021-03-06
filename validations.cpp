#ifndef VALIDATIONS_CPP_INCLUDED
#define VALIDATIONS_CPP_INCLUDED

#include <iostream>
using namespace std;
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>

#include "clsVendedor.h"
#include "clsVehiculo.h"
#include "clsCliente.h"
#include "clsOperacion.h"
#include "validations.h"
#include "funciones.h"
#include "rlutil.h"

using namespace rlutil;


bool validateInt(char *cIn){

}

// VALIDACIONES CLASE FECHA


int validateDia(int dia, int mes, int anio){
     int aux=dia;
     int auxM=mes;
     int auxA=anio;
     switch(mes){
        case  1 :
        case  3 :
        case  5 :
        case  7 :
        case  8 :
        case 10 :
        case 12 :  while(aux>31 || aux<1){
                    setBackgroundColor(RED);
                    cout<<endl<<"Error!";
                    setBackgroundColor(BLACK);
                    cout<<"Ingrese un dia valido: ";
                    cin>>aux;
                    }
                    return aux;
                    break;
        case  4 :
        case  6 :
        case  9 :
        case 11 :   while(aux>30 || aux<1){
                    setBackgroundColor(RED);
                    cout<<endl<<"Error!";
                    setBackgroundColor(BLACK);
                    cout<<"Ingrese un dia valido: ";
                    cin>>aux;
                    }
                    return aux;
                    break;
        case 2: {
            if((auxA % 4 == 0 && auxA % 100 != 0) || (auxA % 400 == 0)){
                        while(aux>29 || aux<1){
                    setBackgroundColor(RED);
                    cout<<endl<<"Error!";
                    setBackgroundColor(BLACK);
                    cout<<"Ingrese un dia valido: ";
                    cin>>aux;
                    }
                    return aux;
                    }
            else{
                while(aux>28 || aux<1){
                    setBackgroundColor(RED);
                    cout<<endl<<"Error!";
                    setBackgroundColor(BLACK);
                    cout<<"Ingrese un dia valido: ";
                    cin>>aux;
                    }
                    return aux;}
            }
            break;
     }
}


int validateMes(int mes,int dia){
     int aux=mes;

     while(aux>12 || aux<1){
         setBackgroundColor(RED);
         cout<<endl<<"Error!";
         setBackgroundColor(BLACK);
         cout<<"Ingrese un mes valido: ";
         cin>>aux;
     }
     return aux;
}

int validateAnio(int anio){
     int aux=anio;
     while(aux<1900){
         setBackgroundColor(RED);
         cout<<endl<<"Error!";
         setBackgroundColor(BLACK);
         cout<<"Ingrese un anio valido: ";
         cin>>aux;
     }
     return aux;

}

// VALIDACIONES DE LA CLASE PERSONA

Fecha validateEsMayor(Fecha fechaDeNacimiento){
     Fecha aux_fechaDeNacimiento = fechaDeNacimiento;
     time_t t;
     t = time(NULL);
     struct tm *fecha;
     fecha = localtime(&t);
     Fecha fechaDeHoy;
     fechaDeHoy.setDia(fecha->tm_mday);
     fechaDeHoy.setMes(fecha->tm_mon+1);
     fechaDeHoy.setAnio(fecha->tm_year+1900);
     int diferenciaAnio=fechaDeHoy.getAnio()-aux_fechaDeNacimiento.getAnio();
     int diferenciaMes=fechaDeHoy.getMes()-aux_fechaDeNacimiento.getMes();
     int diferenciaDia=fechaDeHoy.getDia()-aux_fechaDeNacimiento.getDia();
     while (diferenciaAnio<18||(diferenciaAnio==18 && diferenciaMes<0) || (diferenciaAnio==18 && diferenciaMes==0 && diferenciaDia<0)) {
         setBackgroundColor(RED);
         cout<<endl<<"Error!";
         setBackgroundColor(BLACK);
         cout<<"En esta concesionaria solo entran mayores de edad. Ingrese una fecha de nacimiento valida:  \n";
         aux_fechaDeNacimiento.Cargar();
         diferenciaAnio=fechaDeHoy.getAnio()-aux_fechaDeNacimiento.getAnio();
         diferenciaMes=fechaDeHoy.getMes()-aux_fechaDeNacimiento.getMes();
         diferenciaDia=fechaDeHoy.getDia()-aux_fechaDeNacimiento.getDia();

     }
     if (diferenciaMes==0 && diferenciaDia==0){
        cout<<endl<<"Hoy es su cumpleanios! Deseale un feliz dia";
        return aux_fechaDeNacimiento;
     }
     return aux_fechaDeNacimiento;
}


int digits(int nro){
    int c=1,aux=nro;
    while(aux/10>0){
        c++;
        aux=aux/10;
    }
    return c;
}





// VALIDACIONES CLASE CLIENTE

int validateDniCliente(int dni){
    int aux=dni;
    while(digits(aux)<8){
         setBackgroundColor(RED);
         cout<<endl<<"Error!";
         setBackgroundColor(BLACK);
         cout<<"Ingrese un Dni de al menos 8 digitos: ";
         cin>>aux;
    }
    int pos=buscarPosCliente(aux);
    while (pos!=-1){
         setBackgroundColor(RED);
         cout<<endl<<"Error!";
         setBackgroundColor(BLACK);
         cout<<"Ya hay un cliente registrado con ese DNI, ingrese un DNI que no haya sido registrado: ";
         cin>>aux;
         pos=buscarPosCliente(aux);
    }
    return aux;
}


// VALIDACIONES CLASE VENDEDOR


int validateDniVendedor(int dni){
    int aux=dni;
    while(digits(aux)<8){
         setBackgroundColor(RED);
         cout<<endl<<"Error!";
         setBackgroundColor(BLACK);
         cout<<"Ingrese un Dni de al menos 8 digitos: ";
         cin>>aux;
    }
    int pos=buscarPosVendedor(aux);
    while (pos!=-1){
         setBackgroundColor(RED);
         cout<<endl<<"Error!";
         setBackgroundColor(BLACK);
         cout<<"Ya hay un vendedor registrado con ese DNI, ingrese un DNI que no haya sido registrado: ";
         cin>>aux;
         pos=buscarPosVendedor(aux);
    }
    return aux;
}


float validateSueldo(float sueldoBruto){
   float aux= sueldoBruto;
   while (aux<40000){
         setBackgroundColor(RED);
         cout<<endl<<"Error!";
         setBackgroundColor(BLACK);
         cout<<"El sueldo minimo de la concesionaria es de 40000$. Ingrese un monto correcto: ";
         cin>>aux;
   }
   return aux;
}

float validateComisionPorcentaje(float comisionPorcentaje){
   float aux=comisionPorcentaje;
   while (aux>50 || aux<0){
         setBackgroundColor(RED);
         cout<<endl<<"Error!";
         setBackgroundColor(BLACK);
         cout<<"La comision de un vendedor onda entre el 0 y el 50% de cada operacion. Ingrese un porcentaje valido: ";
         cin>>aux;
   }
   return aux;
}


// VALIDACIONES DE LA CLASE VEHICULO

int validateIdVehiculo(int id){
    int aux=id;
    int pos=buscarPosVehiculo(aux);
    while (pos!=-1){
         setBackgroundColor(RED);
         cout<<endl<<"Error!";
         setBackgroundColor(BLACK);
         cout<<"Ya hay un vehiculo registrado con ese ID, ingrese un ID que no haya sido registrado: ";
         cin>>aux;
         pos=buscarPosVehiculo(aux);
    }
    return aux;
}

int validateAnioDelModelo(int anio){
   int aux = anio;
   while(aux>getFechaDeHoy().getAnio()){
        setBackgroundColor(RED);
        cout<<endl<<"Error!";
        setBackgroundColor(BLACK);
        cout<<endl<<"Un auto del futuro! Ingrese un anio valido: ";
        cin >> aux;
   }
   return aux;
}

int validateCantDePuertas(int cantDePuertas){
   int aux = cantDePuertas;
   while (aux != 3 && aux != 5){
        setBackgroundColor(RED);
        cout<<endl<<"Error!";
        setBackgroundColor(BLACK);
        cout<<endl<<"Los autos que vendemos son con 3 o 5 puertas ?nicamente. Ingrese un n?mero v?lido: ";
        cin >> aux;
   }
   return aux;
}




// VALIDACIONES CLASE OPERACION

int validateIdOperacion(int idOperacion){
    int aux=idOperacion;
    Operacion regOperacion;
    int pos=regOperacion.buscarPosEnDisco(aux);
    while (pos!=-1){
         setBackgroundColor(RED);
         cout<<endl<<"Error!";
         setBackgroundColor(BLACK);
         cout<<"Ya hay una operacion registrada con ese ID, ingrese un ID que no haya sido registrado: ";
         cin>>aux;
         pos=regOperacion.buscarPosEnDisco(aux);
    }
    while(idOperacion<0){
         setBackgroundColor(RED);
         cout<<endl<<"Error!";
         setBackgroundColor(BLACK);
         cout<<"Ingrese un n?mero entero como ID: ";
         cin>>aux;
    }
    return aux;
}

float validateMonto(float monto){
   float aux=monto;
   while (aux<200000){
         setBackgroundColor(RED);
         cout<<endl<<"Error!";
         setBackgroundColor(BLACK);
         cout<<"El precio minimo de un auto es de $200 mil pesos: ";
         cin>>aux;
         cout<<endl;
   }
   return aux;
}

Fecha validateFechaDeInicio(Fecha fechaDeInicio){
    Fecha aux=fechaDeInicio;
    while (aux.getAnio()<2019){
            setBackgroundColor(RED);
            cout<<endl<<"Error!";
            setBackgroundColor(BLACK);
            cout <<"Esta concesionaria solo estuvo activa entre el 2019 y el 2021. Ingrese una fecha v?lida: ";
            cout <<endl;
            aux.Cargar();"\n";
    }
    return aux;
}

Fecha validateFechaDeFin(Fecha fechaDeFin,Fecha fechaDeInicio){
    Fecha auxInicio=fechaDeInicio;
    Fecha auxFin=fechaDeFin;
    while (auxFin.getAnio()<2019){
            setBackgroundColor(RED);
            cout<<endl<<"Error!";
            setBackgroundColor(BLACK);
            cout <<"Esta concesionaria solo estuvo activa entre el 2019 y el 2021. Ingrese una fecha v?lida: ";
            cout <<endl;
            auxFin.Cargar();"\n";
    }
    int diferenciaAnio=auxFin.getAnio()-auxInicio.getAnio();
    int diferenciaMes=auxFin.getMes()-auxInicio.getMes();
    int diferenciaDia=auxFin.getDia()-auxInicio.getDia();
    while (diferenciaAnio<0||(diferenciaAnio==0 && diferenciaMes<0) || (diferenciaAnio==0 && diferenciaMes==0 && diferenciaDia<0)) {
         setBackgroundColor(RED);
         cout<<endl<<"Error!";
         setBackgroundColor(BLACK);
         cout<<"Ingrese una fecha de finalizacion valida de acuerdo a la fecha de inicio ingresada:  \n";
         auxFin.Cargar();
         diferenciaAnio=auxFin.getAnio()-auxInicio.getAnio();
         diferenciaMes=auxFin.getMes()-auxInicio.getMes();
         diferenciaDia=auxFin.getDia()-auxInicio.getDia();

    }

    return auxFin;
}

int validateVehiculoExiste(int idVehiculo){
    Vehiculo regVehiculo;
    int pos=buscarPosVehiculo(idVehiculo);
    if (pos==-1){
            cout<<endl<<endl<<"El vehiculo no existe.";
            setBackgroundColor(LIGHTGREEN);
            cout<<"Inicializando creacion...";
            setBackgroundColor(BLACK);
            cout<<endl<<"------------------------------------------------";
            regVehiculo.Cargar();
            return regVehiculo.getIdVehiculo();
    }
    return idVehiculo;
}


int validateVehiculoStock(int idVehiculo){
    Vehiculo regVehiculo;
    int pos=buscarPosVehiculo(idVehiculo);
    bool leyoVehiculo = regVehiculo.leerDeDisco(pos);
    if (!leyoVehiculo){
         cout<<endl<<endl<<"Error al leer el vehiculo del disco.";
         return 0;
    }
    if(regVehiculo.getEstado()==false){
         cout<<endl<<endl<<"El vehiculo no se encuentra disponible.";
         cout<<endl<<"Esto puede deberse a que haya sido enviado a la papelera. Restaurelo en la seccion 'Gestionar vehiculos' antes de cargar esta operacion";
         return 0;
    }
    if(regVehiculo.getStock()==0){
         cout<<endl<<endl<<"El vehiculo no se encuentra disponible.";
         cout<<endl<<"No tiene stock disponible. Agregue stock en la seccion 'Gestionar Vehiculos' antes de cargar esta operacion.";
         return 0;
    }
    return idVehiculo;
}

int validateClienteExiste(int dniCliente){
    Cliente regCliente;
    int pos=buscarPosCliente(dniCliente);
    if (pos==-1){
            cout<<endl<<endl<<"El cliente no existe.";
            setBackgroundColor(LIGHTGREEN);
            cout<<"Inicializando creacion...";
            setBackgroundColor(BLACK);
            cout<<endl<<"------------------------------------------------";
            regCliente.Cargar();
            return regCliente.getDni();
    }
    bool leyoCliente = regCliente.leerDeDisco(pos);
    if (!leyoCliente){
      cout<<endl<<endl<<"Error al leer cliente";
      return 0;
    }
    if (regCliente.getEstado()==false){
       cout<<"El cliente se encuentra en la papelera. Saque al cliente de la papelera en la seccion 'Gestionar Clientes' antes de sumarle operaciones.";
       return 0;
    }
    return dniCliente;
}

int validateVendedorExiste(int dniVendedor){
    Vendedor regVendedor;
    int pos=buscarPosVendedor(dniVendedor);
    if (pos==-1){
            cout<<endl<<endl<<"El vendedor no existe.";
            setBackgroundColor(LIGHTGREEN);
            cout<<"Inicializando creacion...";
            setBackgroundColor(BLACK);
            cout<<endl<<"------------------------------------------------";
            regVendedor.Cargar();
            return regVendedor.getDni();
    }
    bool leyoVendedor = regVendedor.leerDeDisco(pos);
    if (!leyoVendedor){
      cout<<endl<<endl<<"Error al leer vendedor";
      return 0;
    }
    if (regVendedor.getEstado()==false){
       cout<<"El vendedor se encuentra en la papelera. Saque al vendedor de la papelera en la seccion 'Gestionar Vendedores' antes de sumarle operaciones.";
       return 0;
    }
    return dniVendedor;
}


int validateDominio(char *dominioVehiculo, int numcadena){
    int i;
    for(i=0;i<numcadena;i++){
            if(i==0 || i==1){
                if(isalpha(dominioVehiculo[i])==false){
                    setBackgroundColor(RED);
                    cout<<"ERROR!!";
                    setBackgroundColor(BLACK);
                    cout<<" LOS PRIMEROS DOS DIGITOS DEBEN SER LETRAS (LLNNNLL)"<<endl;
                    return 1;
                }
            }
            if(i==2 || i==3 || i==4){
                if(isdigit(dominioVehiculo[i])==false){
                    setBackgroundColor(RED);
                    cout<<"ERROR!!";
                    setBackgroundColor(BLACK);
                    cout<<"  LOS TRES DIGITOS DEL MEDIO DEBEN SER NUMEROS (LLNNNLL)"<<endl;
                    return 1;
                }
            }
            if(i==5 || i==6){
                if(isalpha(dominioVehiculo[i])==false){
                    setBackgroundColor(RED);
                    cout<<"ERROR!!";
                    setBackgroundColor(BLACK);
                    cout<<" LOS ULTIMOS DOS DIGITOS DEBERIAN SER LETRAS (LLNNNLL)"<<endl;
                    return 1;
                }
            }
    }
    cout<<endl<<"Validando disponibilidad de dicha patente...";
    int cantOpRegistradas = cantDeOperaciones();
    if (cantOpRegistradas == 0){
      setBackgroundColor(GREEN);
      cout<<endl<<"Patente disponible.";
      setBackgroundColor(BLACK);
      return 0;
    }
    FILE *p;
    Operacion regOperacion;
    p=fopen("Operaciones.dat","rb");
    if (p==NULL){
        cout<<endl<<"Error al tratar de buscar la patente.";
        return -1;
    }
    while (fread(&regOperacion,sizeof (Operacion),1,p)==1){
        if (strcmp(regOperacion.getDominioVehiculo(),dominioVehiculo)==0){
           setBackgroundColor(RED);
           cout<<endl<<"Error!";
           setBackgroundColor(BLACK);
           cout<<" La patente no se encuentra disponible, ya est? asociada al vehiculo de otra operacion.";
           cout<<endl;
           fclose(p);
           return -1;
        }
    }
    fclose(p);
    setBackgroundColor(GREEN);
    cout<<endl<<"Patente disponible.";
    setBackgroundColor(BLACK);
    cout<<endl;
    return 0;
}

#endif // VALIDATIONS_CPP_INCLUDED
