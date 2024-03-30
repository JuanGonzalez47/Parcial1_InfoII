#include <iostream>
#include "Prototipos.h"

using namespace std;

int main(){

    //Menu para guardar variables a usar mas adelante, como las condiciones, la posicion y el numero de matrices
    //verificaciones de que las entradas de la clave sean correctas

    int *ptrToKey, *dimension, *ptrStates, ***matrix, *ptrorden; int z, m, n, cond, dimMatrix;

    cout<<"Ingrese la clave K(m,n,cond1,cond2,...,condz) para la cual quiere generar una cerradura X"<<endl;
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    while(true){
        cout<<"Ingrese la cantidad de condiciones que va a usar: ";cin>>z;cout<<endl;
        if (z>1){
            ptrToKey = new int[z];
            ptrStates = new int[z+1];
            ptrorden = new int[z+1];
            break;
        }
        else{
            cout<<"Ingrese mas de una condicion"<<endl;
        }
    }
    while (true){
        cout<<"Ingrese m (posicion en filas): ";cin>>m;cout<<endl;
        if (m>0){
            break;
        }
        else{
            cout<<"Ingrese un numero entero positivo"<<endl;
        }
    }
    while (true){
        cout<<"Ingrese n (posicion en columnas): ";cin>>n;cout<<endl;
        if (n>0){
            break;
        }
        else{
            cout<<"Ingrese un numero entero positivo"<<endl;
        }
    }
    //si m y n son menores que 3, las matrices que debemos de generar son las de 3x3, si uno esmayor que otro y ese mayor es par debemos sumar 1 y esa
    //sera la dimension de las matrices
    if(m<=3 && n<=3){
        dimMatrix = 3;
    }
    else if (m>=n){
        if(m%2 == 0){
            dimMatrix = m+1;
        }
        else{
            dimMatrix = m;
        }
    }
    else if (n>=m){
        if(n%2 == 0){
            dimMatrix = n+1;
        }
        else{
            dimMatrix = n;
        }
    }
    for(int i = 1;i<=z;i++){
        while(true){
            cout<<"Ingrese la condicion numero "<<i<<": ";cin>>cond;cout<<endl;
            if (cond == 1 || cond == -1 || cond == 0){
                ptrToKey[i-1] = cond;
                break;
            }
            else{
                cout<<"Ingrese una condicion valida (-1 o 0 o 1)"<<endl;
            }
        }
    }
    cout<<"Clave ingresada correctamente, trabajaremos para crear la cerrdura X..."<<endl;
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    //recordar liberar memoria cuando ya no se vaya a usar mas las condiciones (final del programa)

    matrix = generar_matrices(z+1,dimMatrix);
    compareFunction(matrix,ptrToKey,m,n,dimMatrix,z,ptrStates,ptrorden);
}


