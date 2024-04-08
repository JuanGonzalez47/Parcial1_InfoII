#include <iostream>

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

    /*for (int i = 0; i <n_matrix; ++i) {
        for (int j = 0; j < tamInicial; ++j) {
            for (int k = 0; k < tamInicial; ++k) {
                cout <<  *(*(*(ptrPrincipal+i)+j)+k) << " ";
            }
            cout << endl;
        }
        cout << endl;
    }*/

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
    for(int i=0;i<n;i++){
        delete[] arrSup[NumberMatrix][i];
    }
    delete[] arrSup[NumberMatrix];
    arrSup[NumberMatrix] = arrSup1;

}

void imprimir_cerradura(int *dimension_final,int *rotacion_final,int n_matrix){
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
        cout<<"M"<<i+1<<"("<<*(dimension_final+i)<<"x"<<*(dimension_final+i)<<")"<<" -> Rotacion: ";
        switch (*(rotacion_final+i)) {
         case 0:
            cout<<"0 -> estado: neutro"<<endl;
             break;
         case 1:
             cout<<"90 -> estado: 1"<<endl;
             break;
         case 2:
             cout<<"180 -> estado: 2"<<endl;
             break;
         case 3:
             cout<<"270 -> estado: 3"<<endl;
        }
    }

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


bool compareFunction(int ***ptrPrincipal, int *ptrCond, int Pos1, int Pos2, int dimensionMatrixToRotate, int AmountConditions, int *ptrStates, int *ptrorden){
    //esta funcion recibira el arreglo con las matrices, la posicion a comparar, tambien dos arreglos, uno para almacenar los estados y otro
    //para almacenar los ordenes de la matriz, para la impresion de la cerradura al final
    //tambien recibira el arreglo que contiene las condiciones para poder comparar y la cantidad de condiciones que se deberan evaluar
    int state = 0, contRotations = 0, WichCond = 0, InicialSize,cont1, cont2;

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


    while(WichCond<AmountConditions){
        switch(ptrCond[WichCond]){
        case 0: while(true){

                if (ptrPrincipal[cont1][Pos1][Pos2] == ptrPrincipal[cont2][Pos1][Pos2]){
                    //guardar estado y diemension en arreglos en el que queda cada matriz
                    ptrStates[WichCond+1] = state;
                    ptrorden[WichCond+1] = dimensionMatrixToRotate;
                    break;
                }
                else{
                    state++;//cambiar estado de rotacion
                    if(contRotations<3){
                        contRotations++;
                        //rotar la matriz
                        rotations(ptrPrincipal,dimensionMatrixToRotate,cont2);
                    }
                    else{
                        //aumentar dimension
                        cambiar_dimension_matriz(ptrPrincipal,dimensionMatrixToRotate + 2,cont2,dimensionMatrixToRotate);
                        dimensionMatrixToRotate += 2;
                        state = 0;
                        contRotations = 0;
                    }
                }
            }
            break;
        case 1: while(true){

                //verificar que la posicion no coincida con el espacio en blanco
                if(ptrPrincipal[cont2][Pos1][Pos2]==0){
                    cambiar_dimension_matriz(ptrPrincipal,dimensionMatrixToRotate + 2,cont2,dimensionMatrixToRotate);
                    dimensionMatrixToRotate += 2;
                }

                if (ptrPrincipal[cont1][Pos1][Pos2] < ptrPrincipal[cont2][Pos1][Pos2]){

                    ptrStates[WichCond+1] = state;
                    ptrorden[WichCond+1] = dimensionMatrixToRotate;
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
                    }
                }
            }
            break;
        case -1: while(true){

                //verificar que la posicion no coincida con el espacio en blanco
                if(ptrPrincipal[cont2][Pos1][Pos2]==0){
                    cambiar_dimension_matriz(ptrPrincipal,dimensionMatrixToRotate + 2,cont2,dimensionMatrixToRotate);
                    dimensionMatrixToRotate += 2;
                }

                if (ptrPrincipal[cont1][Pos1][Pos2] > ptrPrincipal[cont2][Pos1][Pos2]){

                    ptrStates[WichCond+1] = state;
                    ptrorden[WichCond+1] = dimensionMatrixToRotate;
                    break;
                }
                else{
                    state++;
                    if(contRotations<3){
                        contRotations++;
                        rotations(ptrPrincipal,dimensionMatrixToRotate,cont2);
                    }
                    else{

                        /*Si el programa no encuentra un numero menor en la siguiente matriz en su dimension inicial y depsues de haber pasado por todos
                         * los estados, debido que la matriz aumentara el orden nunca encontra dicho numero ya que este aumentara su valor, en consecuencia
                         * nunca se cumplira la condicion*/


                        cout<<"No se ha podido encontrar una cerradura para tu clave debido a que no su cumplio la condicion: "<<WichCond+1<<" : (-1) "<<endl;
                        cout<<"ingrese una clave diferente (consejo: No ingrese demasiados -1 de seguido) "<<endl;
                        cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
                        for(int i=WichCond+1;i<AmountConditions;i++){
                            ptrorden[i] = dimensionMatrixToRotate;
                        }
                        return true;
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
        state = 0;
        contRotations = 0;
    }
    imprimir_cerradura(ptrorden,ptrStates,AmountConditions+1);
    return false;
}


void imprimir_clave(int *ptrToKey,int m,int n,int z){
    int cont=0;
    cout<<"Clave ingresada correctamente: ";
    cout<<"clave K(";
    for(int i=0;i<z+2;i++){
        if(cont == 0){
            cout<<m<<",";
        }
        else if (cont == 1){
            cout<<n<<",";
        }
        else{
            for(int j=0;j<z;j++){
                if (j == z-1){
                    cout<<ptrToKey[j];
                }
                else{
                    cout<<ptrToKey[j]<<",";
                }
            }
            break;
        }
        cont++;
    }
    cout<<") trabajaremos para crear la cerrdura X..."<<endl;
    cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
}


void liberar_memoria(int ***ptrPrincipal,int *rotacion_final,int *dimension_final,int *ptrToKey,int AmountConditions){
    //liberar memoria para ptrPrincipal
    for (int i = 0; i < AmountConditions+1; ++i) {
        //todas las matrices no tienen las mismas dimensiones depende de la posicion i de dimension_final
        for (int j = 0; j < *(dimension_final+i); ++j) {
            delete[] ptrPrincipal[i][j];
        }
        delete[] ptrPrincipal[i];
    }
    delete[] ptrPrincipal;

    //liberar memoria para el resto de arreglos

    delete[] dimension_final;
    delete[] rotacion_final;
    delete[] ptrToKey;


}





