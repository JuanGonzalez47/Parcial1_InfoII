#include <iostream>
#include "Prototipos.h"

using namespace std;


void imprimir_matrices(int ***ptrPrincipal, int n_matrix, int *dimension_final){
    for (int i = 0; i <n_matrix; ++i) {
        for (int j = 0; j < dimension_final[i]; ++j) {
            for (int k = 0; k < dimension_final[i]; ++k) {
                cout <<  *(*(*(ptrPrincipal+i)+j)+k) << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}



int*** matrices_validar_regla(int n_matrix,int *dimen){

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

    return arreglo;
}



bool validar_regla(int ***ptrPrincipal, int *ptrCond, int Pos1, int Pos2,int AmountConditions, int *ptrStates, int *ptrorden){

    int state = 0, contRotations = 0, WichCond = 0,cont1, cont2,paux1,paux2;
    //posicion de cada matriz ptrPrincipal
    cont1=0;
    cont2=1;
    //WichCond: bandera cuando terminan las comparaciones
    ptrStates[WichCond] = state;
    //cambio de posicion

    //se le resta uno porque las posiciones de un arreglo empienzan desde 0 y las de una matriz desde 1
    Pos1-=1;
    Pos2-=1;

    paux1=Pos1;
    paux2=Pos2;

    //nuevas posiciones
    if(*(ptrorden+WichCond) < *(ptrorden+WichCond+1)){
        Pos1=Pos1-(((*(ptrorden+WichCond+1))-(*(ptrorden+WichCond)))/2);
        Pos2=Pos2-(((*(ptrorden+WichCond+1))-(*(ptrorden+WichCond)))/2);
    }else{
        Pos1=Pos1+(((*(ptrorden+WichCond))-(*(ptrorden+WichCond+1)))/2);
        Pos2=Pos2+(((*(ptrorden+WichCond))-(*(ptrorden+WichCond+1)))/2);
    }



    while(WichCond<AmountConditions){
        switch(ptrCond[WichCond]){
        case 0: while(true){

                if (ptrPrincipal[cont1][paux1][paux2] == ptrPrincipal[cont2][Pos1][Pos2]){
                    //guardar estado y diemension en arreglos en el que queda cada matriz
                    ptrStates[WichCond+1] = state;
                    break;
                }
                else{
                    state++;//cambiar estado de rotacion
                    if(contRotations<3){
                        contRotations++;
                        //rotar la matriz
                        rotations(ptrPrincipal,*(ptrorden+WichCond+1),cont2);
                    }
                    else{
                        //no se econtro la cerradura
                        cout<<"La cerradura y la clave no coinciden "<<endl<<"ingrese otros parametros";
                        return true;
                    }
                }
            }
            break;
        case 1: while(true){

                if (ptrPrincipal[cont1][paux1][paux2] > ptrPrincipal[cont2][Pos1][Pos2]){

                    ptrStates[WichCond+1] = state;
                    break;
                }
                else{
                    state++;
                    if(contRotations<3){
                        contRotations++;
                        rotations(ptrPrincipal,*(ptrorden+WichCond+1),cont2);
                    }
                    else{
                        //no se econtro la cerradura
                        return true;
                    }
                }
            }
            break;
        case -1: while(true){

                if (ptrPrincipal[cont1][paux1][paux2] < ptrPrincipal[cont2][Pos1][Pos2]){

                    ptrStates[WichCond+1] = state;
                    break;
                }
                else{
                    state++;
                    if(contRotations<3){
                        contRotations++;
                        rotations(ptrPrincipal,*(ptrorden+WichCond+1),cont2);
                    }
                    else{
                        //no se econtro la cerradura
                        return true;
                    }
                }
            }
            break;
        }
        WichCond++;
        //posicion anterior
        paux1=Pos1;
        paux2=Pos2;
        //nuevas posiciones
        if(*(ptrorden+WichCond) < *(ptrorden+WichCond+1)){
            Pos1=Pos1+(((*(ptrorden+WichCond+1))-(*(ptrorden+WichCond)))/2);
            Pos2=Pos2+(((*(ptrorden+WichCond+1))-(*(ptrorden+WichCond)))/2);
        }else{
            Pos1=Pos1-(((*(ptrorden+WichCond))-(*(ptrorden+WichCond+1)))/2);
            Pos2=Pos2-(((*(ptrorden+WichCond))-(*(ptrorden+WichCond+1)))/2);
        }
        //cambiar posicion
        cont1++;
        cont2++;
        //inicializar condicionas para comparar las siguientes matrices
        state = 0;
        contRotations = 0;
    }

    return false;

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


void liberar_memoria(int ***ptrPrincipal,int *rotacion_final,int *dimension_final,int *ptrToKey,int AmountConditions,bool confir){
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
    if (confir){
        delete[] ptrToKey;
    }

}

void principal_menu(int *ptrToKey,int * ptrStates,int * ptrorden,int *** arreglo,int z,int m, int n, int cond, int dimMatrix, bool end){

    int option, dimension, out;
    bool validation;


    while(end){
        while(true){
            if (out == 2){
                break;
            }
            cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
            cout<<"Ingrese 1 si desea validar una cerradura, 2 si desea ingresar una clave o 3 para salir: ";
            cin>>option;
            if(option == 1){
                cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
                cout<<"Ingrese la clave K(m,n,cond1,cond2,...,condz) para la cual quiere generar una cerradura X"<<endl;
                cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
                while(true){
                    cout<<"Ingrese la cantidad de condiciones que tiene la clave: ";cin>>z;cout<<endl;
                    if (z>=1){
                        //crear arreglos
                        ptrToKey = new int[z];
                        ptrStates = new int[z+1];
                        ptrorden = new int[z+1];
                        break;
                    }
                    else{
                        cout<<"Ingrese una condicion o mas "<<endl;
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
                imprimir_clave(ptrToKey,m,n,z);
                cout<<"Ingrese las dimensiones de las matrices"<<endl;


                for (int i = 0; i < z+1; i++){
                    cout<<"Ingrese la dimension de la matriz numero "<<i+1<<": ";cin>>dimension;cout<<endl;
                    if(dimension%2==0 || dimension==1){
                        cout<<"dimensión no valida, ingrese solo dimensiones pares"<<endl;
                        i--;
                    }
                    else{
                        ptrorden[i] = dimension;
                    }
                }

                arreglo = matrices_validar_regla(z+1,ptrorden);
                validation = validar_regla(arreglo,ptrToKey,m,n,z,ptrStates,ptrorden);
                if(validation==false){
                    cout<<"La clave ingresada abre la cerradura"<<endl;
                    cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
                    imprimir_cerradura(ptrorden,ptrStates,z+1);
                    while (true){
                        cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
                        cout<<"si desea volver al menu principal presione 1 o si desea salir presione 2: ";cin>>out;cout<<endl;
                        if (out == 1){
                            break;
                        }
                        else if (out == 2){
                            end = false;
                            break;
                        }
                        else{
                            cout<<"Ingrese una opcion valida: (1 o 2)"<<endl;
                        }
                    }
                }
                else{
                    cout<<"La cerradura y la clave no coinciden ingrese otros parametros"<<endl;
                    while (true){
                        cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
                        cout<<"si desea volver al menu principal presione 1 o si desea salir presione 2: ";cin>>out;cout<<endl;
                        if (out == 1){
                            break;
                        }
                        else if (out == 2){
                            end = false;
                            break;
                        }
                        else{
                            cout<<"Ingrese una opcion valida: (1 o 2)"<<endl;
                        }
                    }
                }
            }
            else if (option == 2){
                cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
                cout<<"Ingrese la clave K(m,n,cond1,cond2,...,condz) para la cual quiere generar una cerradura X"<<endl;
                cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
                while(true){
                    cout<<"Ingrese la cantidad de condiciones que va a usar: ";cin>>z;cout<<endl;
                    if (z>=1){
                        //crear arreglos
                        ptrToKey = new int[z];
                        ptrStates = new int[z+1];
                        ptrorden = new int[z+1];
                        break;
                    }
                    else{
                        cout<<"Ingrese una condicion o mas "<<endl;
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
                //si m y n son menores o iguales a 3, las matrices que debemos de generar son las de 3x3, si uno es mayor que otro y ese mayor es par debemos sumar 1 y esa
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
                else{
                    if(n%2 == 0){
                        dimMatrix = n+1;
                    }
                    else{
                        dimMatrix = n;
                    }
                }
                //verificar que la posicion no coincida con el espacio en blanco
                if( n==m && (dimMatrix/2)==(m-1)){
                    dimMatrix+=2;
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
                imprimir_clave(ptrToKey,m,n,z);
                arreglo = generar_matrices(z+1,dimMatrix);
                end=compareFunction(arreglo,ptrToKey,m,n,dimMatrix,z,ptrStates,ptrorden,false,dimMatrix);
                break;
            }
            else if (option == 3){
                end = false;
                break;
            }
            else{
                cout<<"Ingrese una opcion valida: (1,2 o 3)"<<endl;
            }
        }
    }
    cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
}
