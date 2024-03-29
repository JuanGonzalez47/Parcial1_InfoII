#include <iostream>

using namespace std;

int*** generar_matrices(int n_matrix,int tam_inicial){
    int elemento;

    // Reserva de memoria para la primera dimensión
    int ***arreglo = new int**[n_matrix];
    // Reserva de memoria para las otras dos dimensiones
    for (int i = 0; i < n_matrix; ++i) {
        arreglo[i] = new int*[tam_inicial];
        for (int j = 0; j < tam_inicial; ++j) {
            arreglo[i][j] = new int[tam_inicial];
        }
    }
    //Rellenar arreglo
    for (int i = 0; i < n_matrix; ++i) {
        elemento=1;
        for (int j = 0; j < tam_inicial; ++j) {
            for (int k = 0; k < tam_inicial; ++k) {
                *(*(*(arreglo+i)+j)+k)=elemento;
                if(k==(tam_inicial/2)&&(j==k)){
                    *(*(*(arreglo+i)+j)+k) = 0;
                }
                else{
                    elemento++;
                }
            }
        }
    }


    /* Imprimir los elementos del arreglo
    for (int i = 0; i <n_matrix; ++i) {
        for (int j = 0; j < tam_inicial; ++j) {
            for (int k = 0; k < tam_inicial; ++k) {
                cout <<  *(*(*(arreglo+i)+j)+k) << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
*/
    return arreglo;
}

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

int*** rotations(int ***arrSup, int dim, int NumberMatrix, int state){
    //Funcion que recibira el arreglo de matrices, dimension de la que quiero rotar
    //y cual de ellos quiero rotar y procedera a rotarla
    // n es la dimension de la matriz
    int n = dim,**arrSup1;

    //creo una matriz vacia pero de igual tamaño que la ingresada
    arrSup1 = new int*[dim];
    for(int i=0;i<n;i++){
        arrSup1[i] = new int[dim];
    }
    switch (state){
        case 0://No rotar
            break;
        case 1://Estado 1 (90 grados)
            for(int i=0; i<n;i++){
                for(int j=0; j<n; j++){
                    arrSup1[i][j] = arrSup[NumberMatrix][n-1-j][i];
                }
            }
            break;
        case 2://Estado 2 (180 grados)
            for(int i=0; i<n;i++){
                for(int j=0; j<n; j++){
                    arrSup1[i][j] = arrSup[NumberMatrix][n-1-j][i];
                }
            }
            break;
        case 3://Estado 3 (270 grados)
            for(int i=0; i<n;i++){
                for(int j=0; j<n; j++){
                    arrSup1[i][j] = arrSup[NumberMatrix][n-1-j][i];
                }
            }
            break;
    }
        for(int i = 0; i < n; i++){
            delete[] arrSup[NumberMatrix][i];
        }
        delete[] arrSup[NumberMatrix];
        arrSup[NumberMatrix] = arrSup1;

        return arrSup;
}



