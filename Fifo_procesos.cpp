#include "paulo.h"
using namespace std;

struct lista {
    string nombreProceso;
    int tiempoLlegada;
    int tiempoCPU;
    int prioridad;
    int numeroProceso;
    int inicio;
    int fin;
    int tiempoEspera;
    struct lista *next;
    struct lista *before;
};

typedef struct lista LISTA;
typedef LISTA *apuntador_lista;

void insertarAlFinal(apuntador_lista *inicio, int llegada, int cpu, string Nombre);
void imprimir(apuntador_lista actual);
void prioridad (apuntador_lista *cabeza);

int main (){
    system ("cls");
    apuntador_lista nuevoNodo = NULL;

    float Numeroprocesos;

    cout << "Digite el numero de procesos a ingresar: "; cin >> Numeroprocesos;
    cout << endl;

    string NombreProceso;
    int llegada, cpu;
    for (int i=0; i< Numeroprocesos; i++){
        cout << "Digite el nombre del Proceso " << i << " ";
        cin.ignore(); // Ignorar el salto de línea anterior
        getline(cin, NombreProceso);
        cout << "Digite el tiempo de llegada de " << NombreProceso << " "; cin >> llegada;
        cout << "Digite el tiempo en CPU de " << NombreProceso << " "; cin >> cpu;
        insertarAlFinal(&nuevoNodo,llegada,cpu,NombreProceso);
    }
    system ("cls");
    prioridad(&nuevoNodo);
    apuntador_lista actual = nuevoNodo;
    apuntador_lista actual2=nuevoNodo;
    //imprimir(nuevoNodo);

    int contador=0;
    for (int i=0;i<Numeroprocesos;i++){
        contador+=actual2->tiempoCPU;
        actual2=actual2->next;
    }

    int aux2 = 0;
while (actual != NULL) {
    actual->inicio = aux2;
    aux2 += actual->tiempoCPU;
    actual->fin = (actual->tiempoCPU + actual->inicio) - 1;
    actual->tiempoEspera = actual->inicio - actual->tiempoLlegada;
    actual = actual->next; // Primero actualiza actual
}


     apuntador_lista copiaActual = nuevoNodo;
    int aux3=0;
    posxy(1,1); cout << "NOMBRE DEL PROCESO";
    posxy(21,1); cout << "LLEGADA";
    posxy(30,1); cout << "TIMEPO EN CPU";
    posxy(45,1); cout << "INICIO";
    posxy(53,1); cout << "FIN";
    posxy(59,1); cout << "TIEMPO EN ESPERA";
    float sumEspera=0, sumRegresion=0;
    for (int i = 0; i < Numeroprocesos; i++) {
        posxy(1,(i+1)*2); cout << copiaActual->nombreProceso;
        posxy(21,(i+1)*2); cout << copiaActual->tiempoLlegada;
        posxy(30,(i+1)*2); cout << copiaActual->tiempoCPU;
        posxy(45,(i+1)*2); cout << copiaActual->inicio;
        posxy(53,(i+1)*2); cout << copiaActual->fin;
        posxy(59,(i+1)*2); cout << copiaActual->tiempoEspera;
        sumEspera+=copiaActual->tiempoEspera;
        sumRegresion+= copiaActual->fin;
        copiaActual = copiaActual->next;
        aux3=(i+1)*2;
    }

    // IMPRIMIR SEGUNDA MATRIZ
    cout << endl << endl << endl;
    apuntador_lista nuevo5 = nuevoNodo;

    posxy(1,aux3+2); cout << "PROCESOS";
    for (int i=0; i<contador;i++){
        posxy(11+i*4,aux3+2);cout << i;
    }

    for (int i=0; i<Numeroprocesos;i++){
        posxy(1,(aux3+4)+i*2); cout << nuevo5->nombreProceso;
        nuevo5=nuevo5->next;
    }



    vector<vector<char>> matrizProcesos(Numeroprocesos, vector<char>(contador, ' ')); // Crear la matriz

apuntador_lista nuevo6 = nuevoNodo;
apuntador_lista auxNuevo6;

for (int tiempo = 0; tiempo < contador; tiempo++) {
    nuevo6 = nuevoNodo; // Reiniciar el puntero al principio de la lista
    auxNuevo6 = nuevoNodo;

    for (int i = 0; i < Numeroprocesos; i++) {
        if (tiempo >= nuevo6->inicio && tiempo <= nuevo6->fin) {
            matrizProcesos[i][tiempo] = 'E';
        } else if (tiempo >= nuevo6->tiempoLlegada && tiempo < nuevo6->inicio) {
            matrizProcesos[i][tiempo] = 'P';
        }
        nuevo6 = nuevo6->next;
    }
}

// Imprimir la matriz
for (int i = 0; i < Numeroprocesos; i++) {
    for (int j = 0; j < contador; j++) {
        posxy(11+j*4,(aux3+3)+i*2+1);cout << matrizProcesos[i][j] << " ";
    }
    cout << endl;
} 
    




    cout <<endl<<endl<< " TIEMPO DE ESPERA: "<< sumEspera/Numeroprocesos<<endl;
    cout << "TIEMPO DE REGRESION:  " << sumRegresion/Numeroprocesos;
    getch();
    return 0;
}

void insertarAlFinal(apuntador_lista *inicio, int llegada, int cpu, string Nombre) {
    apuntador_lista nuevo = new LISTA();
    if (nuevo != NULL) {
        nuevo->tiempoLlegada=llegada;
        nuevo->tiempoCPU = cpu;
        nuevo->nombreProceso = Nombre;
        nuevo->prioridad=llegada;
        nuevo->next = NULL;

        if (*inicio == NULL) {
            nuevo->before = NULL;
            *inicio = nuevo;
        } else {
            apuntador_lista actual = *inicio;
            while (actual->next != NULL) {
                actual = actual->next;
            }
            actual->next = nuevo;
            nuevo->before = actual;
        }
    } else {
        //cout << valor << " No insertado" << endl;
    }
}

void imprimir(apuntador_lista actual)
{
    if(actual==NULL){
        cout<<"La lista esta vacia"<<endl;
    }
    else{
        cout<<"La lista es:\t"<<endl;
        while(actual!=NULL){
            cout<<"-->"<<actual->nombreProceso << " ," << actual->tiempoLlegada<< ", " << actual->tiempoCPU << "NumProceso: "<<actual->numeroProceso;
            actual=actual->next;
            cout <<endl;
        }
        cout<<"NULL"<<endl;
    }
}

void prioridad(apuntador_lista *cabeza) {
    apuntador_lista actual, siguiente, primeroConPrioridad0, ultimoConPrioridad0;
    int prio;
    string nombre;
    int llegada, cpu;

    actual = *cabeza;
    primeroConPrioridad0 = NULL;
    ultimoConPrioridad0 = NULL;

    // Mover los elementos con prioridad 0 al principio de la lista
    while (actual != NULL && actual->prioridad == 0) {
        ultimoConPrioridad0 = actual;
        actual = actual->next;
    }

    // Si hay elementos con prioridad 0, desconectarlos de la lista
    if (ultimoConPrioridad0 != NULL) {
        *cabeza = actual; // Actualizar el puntero principal
        ultimoConPrioridad0->next = NULL;
    }

    // Ordenar la lista en función del tiempo de llegada
    apuntador_lista prev = NULL;
    apuntador_lista minElement = NULL;
    apuntador_lista minPrev = NULL;

    while (*cabeza != NULL) {
        prev = NULL;
        actual = *cabeza;
        minElement = *cabeza;
        minPrev = NULL;

        while (actual != NULL) {
            if (actual->tiempoLlegada < minElement->tiempoLlegada) {
                minElement = actual;
                minPrev = prev;
            }
            prev = actual;
            actual = actual->next;
        }

        if (minPrev != NULL) {
            minPrev->next = minElement->next;
        } else {
            *cabeza = minElement->next;
        }

        // Insertar el elemento mínimo al principio de la lista ordenada
        if (primeroConPrioridad0 == NULL) {
            primeroConPrioridad0 = minElement;
            ultimoConPrioridad0 = minElement;
        } else {
            ultimoConPrioridad0->next = minElement;
            ultimoConPrioridad0 = minElement;
        }

        minElement->next = NULL;
    }

    // Asignar los números de proceso después de ordenar la lista
    int numeroProceso = 0;
    actual = primeroConPrioridad0;
    while (actual != NULL) {
        actual->numeroProceso = numeroProceso++;
        actual = actual->next;
    }

    // Reconectar los elementos con prioridad 0 al principio de la lista ordenada
    if (primeroConPrioridad0 != NULL) {
        ultimoConPrioridad0->next = *cabeza;
        *cabeza = primeroConPrioridad0;
    }
}

