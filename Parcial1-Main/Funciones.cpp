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


void rotations(int ***arrSup, int dim, int NumberMatrix, int state){
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
            for(int i=0;i<n;i++){
                delete[] arrSup[NumberMatrix][i];
            }
            delete[] arrSup[NumberMatrix];
            arrSup[NumberMatrix] = arrSup1;
            break;
        case 2://Estado 2 (180 grados)
            for(int i=0;i<n;i++){
                for(int j=0; j<n; j++){
                    arrSup1[i][j] = arrSup[NumberMatrix][n-1-j][i];
                }
            }
            for(int i=0;i<n;i++){
                delete[] arrSup[NumberMatrix][i];
            }
            delete[] arrSup[NumberMatrix];
            arrSup[NumberMatrix] = new int*[dim];
            for(int i=0;i<n;i++){
                arrSup[NumberMatrix][i] = new int[dim];
            }
            for(int i=0; i<n;i++){
                for(int j=0; j<n; j++){
                    arrSup[NumberMatrix][i][j] = arrSup1[n-1-j][i];
                }
            }
            break;
        case 3://Estado 3 (270 grados)
            for(int i=0;i<n;i++){
                for(int j=0; j<n; j++){
                    arrSup1[i][j] = arrSup[NumberMatrix][n-1-j][i];
                }
            }
            for(int i=0;i<n;i++){
                delete[] arrSup[NumberMatrix][i];
            }
            delete[] arrSup[NumberMatrix];
            arrSup[NumberMatrix] = new int*[dim];
            for(int i=0;i<n;i++){
                arrSup[NumberMatrix][i] = new int[dim];
            }
            for(int i=0; i<n;i++){
                for(int j=0; j<n; j++){
                    arrSup[NumberMatrix][i][j] = arrSup1[n-1-j][i];
                }
            }
            for(int i=0;i<n;i++){
                delete [] arrSup1[i];
            }
            delete [] arrSup1;
            arrSup1 = new int*[dim];
            for(int i=0;i<n;i++){
                arrSup1[i] = new int[dim];
            }
            for(int i=0; i<n;i++){
                for(int j=0; j<n; j++){
                    arrSup1[i][j] = arrSup[NumberMatrix][n-1-j][i];
                }
            }
            for(int i=0;i<n;i++){
                delete[] arrSup[NumberMatrix][i];
            }
            delete[] arrSup[NumberMatrix];
            arrSup[NumberMatrix] = arrSup1;
            break;
    }
}

void cambiar_dimension_matriz(int ***arreglo,int *dimen,int numberMatrix,int tam_inicial){
    /*funcion que cambia la diemnsion de una matriz individual en arreglo superior, number_matrix esta relacionado con la posicion en el arreglo dim
     * donde se almacenan el orden de las matrices*/

    int elemento;

    //liberar memoria
    for (int j = 0; j < tam_inicial; ++j) {
        delete[] arreglo[numberMatrix][j];
    }
    delete[] arreglo[numberMatrix];

    int i=numberMatrix;//solo vamos a rellenar una matriz
    arreglo[i] = new int*[*(dimen+numberMatrix)];//tamaño depende de la posicion que es igual numero de la matriz almacenada en el arreglo dimen
    elemento=1;
    for (int j = 0; j < *(dimen+numberMatrix); ++j) {
        arreglo[i][j] = new int[*(dimen+numberMatrix)];
        //rellenar matriz
        for (int k = 0; k <*(dimen+numberMatrix); ++k) {
            *(*(*(arreglo+i)+j)+k)=elemento;
            if(k==(*(dimen+numberMatrix)/2)&&(j==k)){
                *(*(*(arreglo+i)+j)+k) = 0;
            }
            else{
                elemento++;
            }

        }
    }
}


void compareFunction(int ***ptrPrincipal, int cont1, int cont2, int *ptrCond, int WichCond, int Pos1, int Pos2, int dimensionMatrixToRotate){
    //esta funcion recibira el arreglo con las matrices, la posicion a comparar y dos contadores para saber cuales matrices comparar
    //tambien recibira el arreglo que contiene las condiciones para poder comparar y cual condicion se evaluara
    //retornara true en caso de que la condicion se haya cumplido
    int state = 0, contRotations = 0;
    switch(ptrCond[WichCond]){
    case 0: while(true){
            state++;
                if (ptrPrincipal[cont1][Pos1][Pos2] == ptrPrincipal[cont2][Pos1][Pos2]){
                    break;
                }
                else{
                    //insertar funcion para rotar y llevar un conteo de cuntas veces se ha realizado las rotaciones, para saber cuando debo
                    //subir de orden la matriz
                    contRotations++;
                    if(contRotations<3){
                        rotations(ptrPrincipal,dimensionMatrixToRotate,cont2,state);
                    }
                    else{
                        //insertar funcion para aumentar dimension
                        dimensionMatrixToRotate += 2;
                    }
                }
            }
            break;
        case 1: while(true){
                state++;
                if (ptrPrincipal[cont1][Pos1][Pos2] < ptrPrincipal[cont2][Pos1][Pos2]){
                    break;
                }
                else{
                    //insertar funcion para rotar y llevar un conteo de cuntas veces se ha realizado las rotaciones, para saber cuando debo
                    //subir de orden la matriz
                    contRotations++;
                    if(contRotations<3){
                        //dimensionMatrixToRotate = //insertar funcion que me extraiga dicha dimension
                        rotations(ptrPrincipal,dimensionMatrixToRotate,cont2,state);
                    }
                    else{
                        //insertar funcion para aumentar dimension
                    }
                }
            }
            break;
        case -1: while(true){
                state++;
                if (ptrPrincipal[cont1][Pos1][Pos2] > ptrPrincipal[cont2][Pos1][Pos2]){
                    break;
                }
                else{
                    //insertar funcion para rotar y llevar un conteo de cuntas veces se ha realizado las rotaciones, para saber cuando debo
                    //subir de orden la matriz
                    contRotations++;
                    if(contRotations<3){
                        //dimensionMatrixToRotate = //insertar funcion que me extraiga dicha dimension
                        rotations(ptrPrincipal,dimensionMatrixToRotate,cont2,state);
                    }
                    else{
                        //insertar funcion para aumentar dimension
                    }
                }
            }
            break;
    }

}

//crear funcion para llevar todo el menu y como tal el proceso de encontrar la ceerradura
//crear otra funcion para imprimir la cerradura y todo lo que se neceista imprimir



