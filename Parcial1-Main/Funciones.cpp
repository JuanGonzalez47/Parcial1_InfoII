#include <iostream>

using namespace std;

int* dimensio_variables(int tam_inicial,int n_matrix){

    /*Arreglo que en cada posicion representa la dimension de cada matriz*/

    int *dimen;
    //reservar memoria
    dimen= new int[n_matrix];

    for(int i=0;i<n_matrix;i++){
        *(dimen+i)=tam_inicial;
    }
    return dimen;
}

int*** generar_matrices(int n_matrix,int *dimen){
    int elemento;//numeros de cada posicion en la matriz

    // Reserva de memoria para la primera dimensión
    int ***arreglo = new int**[n_matrix];
    // Reserva de memoria para las otras dos dimensiones
    for (int i = 0; i < n_matrix; ++i) {
        arreglo[i] = new int*[*(dimen+i)];//tamaño depende de la posicion i del arreglo dimen
        elemento=1;
        for (int j = 0; j < *(dimen+i); ++j) {
            arreglo[i][j] = new int[*(dimen+i)];
            //rellenar arreglo
            for (int k = 0; k < *(dimen+i); ++k) {
                *(*(*(arreglo+i)+j)+k)=elemento;
                if(k==(*(dimen+i)/2)&&(j==k)){
                    *(*(*(arreglo+i)+j)+k) = 0;
                }
                else{
                    elemento++;
                }

            }
        }
    }




    /*Imprimir los elementos del arreglo
     for (int i = 0; i <n_matrix; ++i) {
         for (int j = 0; j < *(dimen+i); ++j) {
             for (int k = 0; k < *(dimen+i); ++k) {
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

void rotations(int **arrSup, int dim){
    //Funcion que recibira una sola matriz y su dimension y procedera a rotarla
    // n es la dimension de la matriz
    int n = dim,**arrSup1;

    //creo una matriz vacia pero de igual tamaño que la ingresada
    arrSup1 = new int*[dim];
    for(int i=0;i<n;i++){
        arrSup1[i] = new int[dim];
    }

    //Estado 1 (90 grados)
    for(int i=0; i<n;i++){
        for(int j=0; j<n; j++){
            arrSup1[i][j] = arrSup[n-1-j][i];
        }
    }
    for(int i=0;i<n;i++){
        delete[] arrSup[i];
    }
    delete[] arrSup;
    arrSup = new int *[5];
    for(int i=0;i<n;i++){
        arrSup[i] = new int[5];
    }
    //Estado 2 (180 grados)
    for(int i=0; i<n;i++){
        for(int j=0; j<n; j++){
            arrSup[i][j] = arrSup1[n-1-j][i];
        }
    }
    for(int i=0;i<n;i++){
        delete[] arrSup1[i];
    }
    delete[] arrSup1;
    //Estado 3 (270 grados)
    for(int i=0; i<n;i++){
        for(int j=0; j<n; j++){
            arrSup[i][j] = arrSup1[n-1-j][i];
        }
    }
    //Recordar liberar memoria de arrsup (matriz ingresada)
}



