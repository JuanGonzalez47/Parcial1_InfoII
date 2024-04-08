#include <iostream>
#include "Prototipos.h"

using namespace std;

int*** generar_matrices(int n_matrix,int tamInicial){
    int elemento;//numeros de cada posicion en la matriz

    // Reserva de memoria para la primera dimensión
    int ***ptrPrincipal = new int**[n_matrix];
    // Reserva de memoria para las otras dos dimensiones
    for (int i = 0; i < n_matrix; ++i){
        ptrPrincipal[i] = new int*[tamInicial];//tamaño depende de la posicion i del arreglo dimen
    elemento=1;
        for (int j = 0; j < tamInicial; ++j){
            ptrPrincipal[i][j] = new int[tamInicial];
            //rellenar arreglo
            for (int k = 0; k < tamInicial; ++k) {
                *(*(*(ptrPrincipal+i)+j)+k)=elemento;
                if(k==(tamInicial/2)&&(j==k)){
                *(*(*(ptrPrincipal+i)+j)+k) = 0;
                }
                else{
                    elemento++;
                }
            }
        }
    }
    return ptrPrincipal;
}


void rotations(int ***arrSup, int dim, int NumberMatrix){
    //Funcion que recibira el arreglo de matrices, dimension de la que quiero rotar
    //y cual de ellos quiero rotar y procedera a rotarla
    // n es la dimension de la matriz
    int n = dim,**arrSup1;

    //creo una matriz vacia pero de igual tamaño que la ingresada
    arrSup1 = new int*[dim];
    for(int i=0;i<n;i++){
        arrSup1[i] = new int[dim];
    }
    for(int i=n-1; i>=0;i--){
        for(int j=0; j<n; j++){
            arrSup1[j][i] = arrSup[NumberMatrix][i][n-1-j];
        }
    }
    for(int i=n-1; i>=0;i--){
        for(int j=0; j<n; j++){
            arrSup[NumberMatrix][i][j] = arrSup1[i][j];
        }
    }
    //liberar arrsup1
    for(int i=0;i<n;i++){
        delete [] arrSup1[i];
    }
    delete [] arrSup1;
}



void cambiar_dimension_matriz(int ***arreglo,int dimen,int numberMatrix,int tam_inicial){
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

}



bool compareFunction(int ***ptrPrincipal, int *ptrCond, int Pos1, int Pos2, int dimensionMatrixToRotate, int AmountConditions, int *ptrStates, int *ptrorden,bool bajar_dimension,int InitialSizeIteration1){
    //esta funcion recibira el arreglo con las matrices, la posicion a comparar, tambien dos arreglos, uno para almacenar los estados y otro
    //para almacenar los ordenes de la matriz, para la impresion de la cerradura al final
    //tambien recibira el arreglo que contiene las condiciones para poder comparar y la cantidad de condiciones que se deberan evaluar

    int amountof1 = 0, state = 0, contRotations = 0, WichCond = 0, InicialSize,cont1, cont2, PosAux1, PosAux2, Aux1, Aux2, out;
    bool Repetition = false;

    //posicion de cada matriz ptrPrincipal
    cont1=0;
    cont2=1;
    //WichCond: bandera cuando terminan las comparaciones
    ptrStates[WichCond] = state;
    ptrorden[WichCond] = dimensionMatrixToRotate;
    //dimension inicial de cada matriz
    InicialSize = dimensionMatrixToRotate;
    //se le resta uno porque las posiciones de un arreglo empienzan desde 0 y las de una matriz desde 1
    Pos1-=1;
    Pos2-=1;
    Aux1 = Pos1;
    Aux2 = Pos2;
    PosAux1=Pos1;
    PosAux2=Pos2;

    while(WichCond<AmountConditions){
        switch(ptrCond[WichCond]){
        case 0: cambiar_dimension_matriz(ptrPrincipal,ptrorden[WichCond],cont2,dimensionMatrixToRotate);
                dimensionMatrixToRotate += ptrorden[WichCond] - InicialSize;
                ptrStates[WichCond+1] = ptrStates[WichCond];
                ptrorden[WichCond+1] = dimensionMatrixToRotate;
            break;
        case -1: while(true){
                if (ptrPrincipal[cont1][Pos1][Pos2] < ptrPrincipal[cont2][PosAux1][PosAux2]){
                    ptrStates[WichCond+1] = state;
                    ptrorden[WichCond+1] = dimensionMatrixToRotate;
                    state = 0;
                    contRotations = 0;
                    break;
                }
                else{
                    state++;
                    if(contRotations<3){
                        contRotations++;
                        rotations(ptrPrincipal,dimensionMatrixToRotate,cont2);
                    }
                    else{
                        cambiar_dimension_matriz(ptrPrincipal,dimensionMatrixToRotate + 2,cont2,dimensionMatrixToRotate);
                        dimensionMatrixToRotate += 2;
                        state = 0;
                        contRotations = 0;
                        PosAux1++;
                        PosAux2++;
                    }
                }
            }
            break;
        case 1:
            amountof1++;
            while(true){
                if(Pos1 < 0 || Pos2 < 0){
                    cout<<"No se ha podido encontrar una cerradura para tu clave debido a que no su cumplio la condicion: "<<WichCond+1<<" : (1) "<<endl;
                    cout<<"consejo: (trate de no ingresar demasiados 1 de seguido) "<<endl;
                    cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
                    for(int i=WichCond+1;i<=AmountConditions;i++){
                        ptrorden[i] = dimensionMatrixToRotate;
                    }
                    liberar_memoria(ptrPrincipal,ptrStates,ptrorden,ptrCond,AmountConditions,true);
                    return true;
                }
                if (ptrPrincipal[cont1][Pos1][Pos2] > ptrPrincipal[cont2][PosAux1][PosAux2]){
                    ptrStates[WichCond+1] = state;
                    ptrorden[WichCond+1] = dimensionMatrixToRotate;
                    state = 0;
                    contRotations = 0;
                    break;
                }
                else if (ptrStates[WichCond] != 0 && ptrPrincipal[cont1][Pos1][Pos2] == 1){
                    /*Si el programa no encuentra un numero menor en la siguiente matriz en su dimension inicial y depsues de haber pasado por todos
                             * los estados, debido que la matriz aumentara el orden nunca encontra dicho numero ya que este aumentara su valor, en consecuencia
                             * nunca se cumplira la condicion*/
                        cout<<"No se ha podido encontrar una cerradura para tu clave debido a que no su cumplio la condicion: "<<WichCond+1<<" : (1) "<<endl;
                        cout<<"Posibles razones: "<<endl<<endl<<"1. se tomo un numero de la primera fila de la matriz "<<endl;
                        cout<<"2. Ingresaste un numero correspondiente a una esquina de la matriz, y luego de ser rotada tomo el valor de 1"<<endl;
                        cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;

                        for(int i=WichCond+1;i<=AmountConditions;i++){
                            ptrorden[i] = dimensionMatrixToRotate;
                        }
                        liberar_memoria(ptrPrincipal,ptrStates,ptrorden,ptrCond,AmountConditions,true);

                        return true;
                    }
                else if(ptrStates[WichCond] == 0 && ptrPrincipal[cont1][Pos1][Pos2] >=  1 && ptrPrincipal[cont1][Pos1][Pos2] < InitialSizeIteration1){
                    cout<<"No se ha podido encontrar una cerradura para tu clave debido a que no su cumplio la condicion: "<<WichCond+1<<" : (1) "<<endl;
                    cout<<"Posibles razones: "<<endl<<endl<<"1. Ingresaste un numero de la primera fila de la matriz "<<endl;
                    cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;

                    for(int i=WichCond+1;i<=AmountConditions;i++){
                        ptrorden[i] = dimensionMatrixToRotate;
                    }
                    liberar_memoria(ptrPrincipal,ptrStates,ptrorden,ptrCond,AmountConditions,true);

                    return true;
                }
                else{
                    state++;
                    if(contRotations<3){
                        contRotations++;
                        rotations(ptrPrincipal,dimensionMatrixToRotate,cont2);
                    }
                    else if(bajar_dimension && dimensionMatrixToRotate > InitialSizeIteration1){
                        cambiar_dimension_matriz(ptrPrincipal,dimensionMatrixToRotate - 2,cont2,dimensionMatrixToRotate);
                        dimensionMatrixToRotate -= 2;
                        state = 0;
                        contRotations = 0;
                        PosAux1--;
                        PosAux2--;
                    }
                    else{
                        for(int i=WichCond+1;i<=AmountConditions;i++){
                            ptrorden[i] = dimensionMatrixToRotate;
                        }
                        liberar_memoria(ptrPrincipal,ptrStates,ptrorden,ptrCond,AmountConditions,false);
                        ptrPrincipal=generar_matrices(AmountConditions+1,InicialSize+(amountof1*2));
                        ptrStates = new int[AmountConditions+1];
                        ptrorden = new int[AmountConditions+1];
                        Pos1=Aux1;
                        Pos2=Aux2;
                        Repetition = compareFunction(ptrPrincipal,ptrCond,Pos1+1,Pos2+1,InicialSize+(amountof1*2),AmountConditions,ptrStates,ptrorden,true,InitialSizeIteration1);
                        if (Repetition) return true;
                        return false;
                    }
                }
            }
            break;
        }
        WichCond++;
        //cambiar posicion
        cont1++;
        cont2++;
        //inicializar condicionas para comparar las siguientes matrices
        dimensionMatrixToRotate = InicialSize;
        Pos1 = PosAux1;
        Pos2 = PosAux2;
        PosAux1 = Aux1;
        PosAux2 = Aux2;
    }

    imprimir_cerradura(ptrorden,ptrStates,AmountConditions+1);
    liberar_memoria(ptrPrincipal,ptrStates,ptrorden,ptrCond,AmountConditions,true);
    while (true){
        cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<"si desea volver al menu principal presione 1 o si desea salir presione 2: ";cin>>out;cout<<endl;
        if (out == 1){
            return true;
        }
        else if (out == 2){
            return false;
        }
        else{
            cout<<"Ingrese una opcion valida: (1 o 2)"<<endl;
        }
    }

}







