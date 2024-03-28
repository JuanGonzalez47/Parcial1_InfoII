#include <iostream>

using namespace std;

int* KeyVerification(){

    //Funcion que pide la clave K y verifica que esta sea correcta
    //devuelve true en caso de que este correcta, para continuar con el projecto
    //de lo contrario se queda pidiendo una contraseña correcta

    int *ptrToKey; int z, m, n, cond; bool value = true, Verify = true;

    cout<<"Ingrese la clave K(m,n,cond1,cond2,...,condz) para la cual quiere generar una cerradura X"<<endl;
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    while(true){
        cout<<"Ingrese la cantidad de condiciones que va a usar: ";cin>>z;cout<<endl;
        if (z>1){
            ptrToKey = new int[z+2];
            break;
        }
        else{
            cout<<"Ingrese mas de una condicion"<<endl;
        }
    }
    while (true){
        cout<<"Ingrese m (posicion en filas): ";cin>>m;cout<<endl;
        if (m>0){
            ptrToKey[0] = m;
            break;
        }
        else{
            cout<<"Ingrese un numero entero positivo"<<endl;
        }
    }
    while (true){
        cout<<"Ingrese n (posicion en columnas): ";cin>>n;cout<<endl;
        if (n>0){
            ptrToKey[1] = n;
            break;
        }
        else{
            cout<<"Ingrese un numero entero positivo"<<endl;
        }
    }
    for(int i = 1;i<=z;i++){
        while(true){
            cout<<"Ingrese la condicion numero "<<i<<": ";cin>>cond;cout<<endl;
            if (cond == 1 || cond == -1 || cond == 0){
                ptrToKey[i+1] = cond;
                break;
            }
            else{
                cout<<"Ingrese una condicion valida (-1 o 0 o 1)"<<endl;
            }
        }
    }
    cout<<"Clave ingresada correctamente, trabajaremos para crear la cerrdura X..."<<endl;
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    return ptrToKey;
}


