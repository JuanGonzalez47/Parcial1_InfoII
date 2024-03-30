#include <iostream>

using namespace std;

int*** generar_matrices(int n_matrix,int tamInicial){
    int elemento;//numeros de cada posicion en la matriz

    // Reserva de memoria para la primera dimensión
    int ***arreglo = new int**[n_matrix];
    // Reserva de memoria para las otras dos dimensiones
    for (int i = 0; i < n_matrix; ++i){
        arreglo[i] = new int*[tamInicial];//tamaño depende de la posicion i del arreglo dimen
    elemento=1;
        for (int j = 0; j < tamInicial; ++j){
            arreglo[i][j] = new int[tamInicial];
            //rellenar arreglo
            for (int k = 0; k < tamInicial; ++k) {
                *(*(*(arreglo+i)+j)+k)=elemento;
                if(k==(tamInicial/2)&&(j==k)){
                *(*(*(arreglo+i)+j)+k) = 0;
                }
                else{
                    elemento++;
                }
            }
        }
    }
    return arreglo;
}




int ***rotations(int ***arrSup, int dim, int NumberMatrix){
    //Funcion que recibira el arreglo de matrices, dimension de la que quiero rotar
    //y cual de ellos quiero rotar y procedera a rotarla
    // n es la dimension de la matriz
    int n = dim,**arrSup1;

    //creo una matriz vacia pero de igual tamaño que la ingresada
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

    return arrSup;

}

void impresion(int *dimension_final,int *rotacion_final,int n_matrix){
    /*funcion que imprime la cerradura X y el estado en el que quedo cada matriz*/

    cout<<"cerradura X(";
    for(int i=0;i<n_matrix;i++){
        if(i!=(n_matrix-1)){
            cout<<*(dimension_final+i)<<",";
        }
        else{
            cout<<*(dimension_final+i);
        }
    }
    cout<<")"<<endl;

    for(int i=0;i<n_matrix;i++){
        cout<<"M"<<i+1<<"("<<*(dimension_final+i)<<"x"<<*(dimension_final+i)<<")"<<" -> Estado: "<<*(rotacion_final+i)<<endl;
    }

}

int*** cambiar_dimension_matriz(int ***arreglo,int dimen,int numberMatrix,int tam_inicial){
    /*funcion que cambia la diemnsion de una matriz individual en arreglo superior, number_matrix esta relacionado con la posicion en el arreglo dim
     * donde se almacenan el orden de las matrices*/

    int elemento;

    //liberar memoria
    for (int j = 0; j < tam_inicial; ++j) {
        delete[] arreglo[numberMatrix][j];
    }
    delete[] arreglo[numberMatrix];

    int i=numberMatrix;//solo vamos a rellenar una matriz
    arreglo[i] = new int*[dimen];//tamaño depende de la posicion que es igual numero de la matriz almacenada en el arreglo dimen
    elemento=1;
    for (int j = 0; j < dimen; ++j) {
        arreglo[i][j] = new int[dimen];
        //rellenar matriz
        for (int k = 0; k < dimen; ++k) {
            *(*(*(arreglo+i)+j)+k)=elemento;
            if(k==(dimen/2)&&(j==k)){
                *(*(*(arreglo+i)+j)+k) = 0;
            }
            else{
                elemento++;
            }

        }
    }
    return arreglo;
}


void compareFunction(int ***ptrPrincipal, int *ptrCond, int Pos1, int Pos2, int dimensionMatrixToRotate, int AmountConditions, int *ptrStates, int *ptrorden){
    //esta funcion recibira el arreglo con las matrices, la posicion a comparar, tambien dos arreglos, uno para almacenar los estados y otro
    //para almacenar los ordenes de la matriz, para la impresion de la cerradura al final
    //tambien recibira el arreglo que contiene las condiciones para poder comparar y la cantidad de condiciones que se deberan evaluar
    //retornara true en caso de que la condicion se haya cumplido
    int state = 0, contRotations = 0, cont1 = 0, cont2 = 1, WichCond = 0, InicialSize;

    ptrStates[WichCond] = state;
    ptrorden[WichCond] = dimensionMatrixToRotate;
    InicialSize = dimensionMatrixToRotate;
    while(WichCond<AmountConditions){
        switch(ptrCond[WichCond]){
        case 0: while(true){
                if (ptrPrincipal[cont1][Pos1][Pos2] == ptrPrincipal[cont2][Pos1][Pos2]){
                    ptrStates[WichCond+1] = state;
                    ptrorden[WichCond+1] = dimensionMatrixToRotate;
                    break;
                }
                else{
                    state++;
                    if(contRotations<3){
                        contRotations++;
                        ptrPrincipal = rotations(ptrPrincipal,dimensionMatrixToRotate,cont2);
                    }
                    else{
                        ptrPrincipal = cambiar_dimension_matriz(ptrPrincipal,dimensionMatrixToRotate + 2,cont2,dimensionMatrixToRotate);
                        dimensionMatrixToRotate += 2;
                        state = 0;
                        contRotations = 0;
                    }
                }
            }
            break;
        case 1: while(true){
                if (ptrPrincipal[cont1][Pos1][Pos2] < ptrPrincipal[cont2][Pos1][Pos2]){
                    ptrStates[WichCond+1] = state;
                    ptrorden[WichCond+1] = dimensionMatrixToRotate;
                    break;
                }
                else{
                    state++;
                    if(contRotations<3){
                        contRotations++;
                        ptrPrincipal = rotations(ptrPrincipal,dimensionMatrixToRotate,cont2);
                    }
                    else{
                        ptrPrincipal = cambiar_dimension_matriz(ptrPrincipal,dimensionMatrixToRotate + 2,cont2,dimensionMatrixToRotate);
                        dimensionMatrixToRotate += 2;
                        state = 0;
                        contRotations = 0;
                    }
                }
            }
            break;
        case -1: while(true){
                if (ptrPrincipal[cont1][Pos1][Pos2] > ptrPrincipal[cont2][Pos1][Pos2]){
                    ptrStates[WichCond+1] = state;
                    ptrorden[WichCond+1] = dimensionMatrixToRotate;
                    break;
                }
                else{
                    state++;
                    if(contRotations<3){
                        contRotations++;
                        ptrPrincipal = rotations(ptrPrincipal,dimensionMatrixToRotate,cont2);
                    }
                    else{
                        ptrPrincipal = cambiar_dimension_matriz(ptrPrincipal,dimensionMatrixToRotate + 2,cont2,dimensionMatrixToRotate);
                        dimensionMatrixToRotate += 2;
                        state = 0;
                        contRotations = 0;
                    }
                }
            }
            break;
        }
        state = 0;
        contRotations = 0;
        WichCond++;
        cont1 = cont2;
        cont2++;
        dimensionMatrixToRotate = InicialSize;
    }
    impresion(ptrorden,ptrStates,AmountConditions+1);
    //falta eliminar ptrstates, ptrorden, ptrprincipal, ptrcond
}

