#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include "player.h"
#include "environment.h"

using namespace std;

const double masinf=9999999999.0, menosinf=-9999999999.0;


// Constructor
Player::Player(int jug){
    jugador_=jug;
}

// Actualiza el estado del juego para el jugador
void Player::Perceive(const Environment & env){
    actual_=env;
}

double Puntuacion(int jugador, const Environment &estado){
    double suma=0;

    for (int i=0; i<7; i++)
      for (int j=0; j<7; j++){
         if (estado.See_Casilla(i,j)==jugador){
            if (j<3)
               suma += j;
            else
               suma += (6-j);
         }
      }

    return suma;
}

//Devuelve el número de 3-rayas que hace el jugador para una fila y columna
int tresRayas(const Environment &estad, int fila, int columna, int jugador) {
  //cout << "Miro fila y col" << fila << " " << columna << endl;
  int ganador;
  int nrayas = 0;
  if (estad.See_Casilla(fila,columna)==0)
      nrayas = 0;
//  ganador=0;
  //En la misma Fila
  if (columna<5){
    if ((estad.See_Casilla(fila,columna)%3)   == (estad.See_Casilla(fila, (columna+1))%3) and
        (estad.See_Casilla(fila,columna+1)%3) == (estad.See_Casilla(fila,columna+2)%3)) { //and
        //(estado.See_Casilla(fila,columna+2)%3) == (estado.See_Casilla(fila,columna+3)%3)){
        //cout << "En la misma fila\n";
        ganador = (estad.See_Casilla(fila,columna));
        //cout << "El valor de la casilla MOD actual es " << estad.See_Casilla(fila,columna+1) << endl;
        //cout << "El ganador es " << ganador << endl;
        if (ganador == jugador)
          nrayas++;
        //cout << "Entro en el if del ganador" << endl;
    }
  }
  //En la misma columna
  if (fila<5){
    if ((estad.See_Casilla(fila,columna)%3)   == (estad.See_Casilla(fila+1,columna)%3) and
        (estad.See_Casilla(fila+1,columna)%3) == (estad.See_Casilla(fila+2,columna)%3)) { //and
      //  (estado.See_Casilla(fila+2,columna)%3) == (estado.See_Casilla(fila+3,columna)%3)) {
        //cout << "En la misma columna\n";
        ganador = (estad.See_Casilla(fila,columna));
        //cout << "El valor de la casilla MOD actual es " << estad.See_Casilla(fila+1,columna)  << endl;
        //cout << "El ganador es " << ganador << endl;
        if (ganador == jugador)
          nrayas++;
        //cout << "Entro en el if del ganador" << endl;
    }
  }
  //En la diagonal hacia arriba
  if (fila<5 and columna<5){
    if ((estad.See_Casilla(fila,columna)%3) == (estad.See_Casilla(fila+1,columna+1)%3) and
        (estad.See_Casilla(fila+1,columna+1)%3) == (estad.See_Casilla(fila+2,columna+2)%3)) { //and
        //(estado.See_Casilla(fila+2,columna+2)%3) == (estado.See_Casilla(fila+3,columna+3)%3)){
        //cout << "En la diagonal principal\n";
        //cout << "El valor de la casilla MOD actual es " << estad.See_Casilla(fila+2,columna)  << endl;
        ganador = (estad.See_Casilla(fila,columna));
        //cout << "El ganador es " << ganador << endl;
        if (ganador == jugador)
          nrayas++;
        //cout << "Entro en el if del ganador" << endl;
    }
  }

  //En la diagonal hacia abajo
  if (fila>1 and columna<5){
    if ((estad.See_Casilla(fila,columna)%3)   == (estad.See_Casilla(fila-1,columna+1)%3) and
        (estad.See_Casilla(fila-1,columna+1)%3) == (estad.See_Casilla(fila-2,columna+2)%3)) { //and
        //(estado.See_Casilla(fila-2,columna+2)%3) == (estado.See_Casilla(fila-3,columna+3)%3)) {
        //cout << "En la diagonal secundaria\n";

        ganador = (estad.See_Casilla(fila-1,columna+1));
        //cout << "El valor de la casilla MOD actual es " << estad.See_Casilla(fila-1,columna)  << endl;
        if (ganador == jugador)
          nrayas++;
        //cout << "Entro en el if del ganador" << endl;
    }
  }

  return nrayas;
}

//Devuelve el número de 3-rayas que hace el jugador para una fila y columna
int dosRayas(const Environment &estad, int fila, int columna, int jugador) {
  //cout << "Miro fila y col" << fila << " " << columna << endl;
  int ganador;
  int nrayas = 0;
  if (estad.See_Casilla(fila,columna)==0)
      nrayas = 0;
//  ganador=0;
  //En la misma Fila
  if (columna<6){
    if ((estad.See_Casilla(fila,columna)%3)   == (estad.See_Casilla(fila, (columna+1))%3)) {// and
        //(estad.See_Casilla(fila,columna+1)%3) == (estad.See_Casilla(fila,columna+2)%3)) { //and
        //(estado.See_Casilla(fila,columna+2)%3) == (estado.See_Casilla(fila,columna+3)%3)){
        //cout << "En la misma fila\n";
        ganador = (estad.See_Casilla(fila,columna));
        //cout << "El valor de la casilla MOD actual es " << estad.See_Casilla(fila,columna+1) << endl;
        //cout << "El ganador es " << ganador << endl;
        if (ganador == jugador)
          nrayas++;
        //cout << "Entro en el if del ganador" << endl;
    }
  }
  //En la misma columna
  if (fila<6){
    if ((estad.See_Casilla(fila,columna)%3)   == (estad.See_Casilla(fila+1,columna)%3)) {// and
      //  (estad.See_Casilla(fila+1,columna)%3) == (estad.See_Casilla(fila+2,columna)%3)) { //and
      //  (estado.See_Casilla(fila+2,columna)%3) == (estado.See_Casilla(fila+3,columna)%3)) {
        //cout << "En la misma columna\n";
        ganador = (estad.See_Casilla(fila,columna));
        //cout << "El valor de la casilla MOD actual es " << estad.See_Casilla(fila+1,columna)  << endl;
        //cout << "El ganador es " << ganador << endl;
        if (ganador == jugador)
          nrayas++;
        //cout << "Entro en el if del ganador" << endl;
    }
  }
  //En la diagonal hacia arriba
  if (fila<6 and columna<6){
    if ((estad.See_Casilla(fila,columna)%3) == (estad.See_Casilla(fila+1,columna+1)%3)) {// and
      //  (estad.See_Casilla(fila+1,columna+1)%3) == (estad.See_Casilla(fila+2,columna+2)%3)) { //and
        //(estado.See_Casilla(fila+2,columna+2)%3) == (estado.See_Casilla(fila+3,columna+3)%3)){
        //cout << "En la diagonal principal\n";
        //cout << "El valor de la casilla MOD actual es " << estad.See_Casilla(fila+2,columna)  << endl;
        ganador = (estad.See_Casilla(fila,columna));
        //cout << "El ganador es " << ganador << endl;
        if (ganador == jugador)
          nrayas++;
        //cout << "Entro en el if del ganador" << endl;
    }
  }

  //En la diagonal hacia abajo
  if (fila>0 and columna<6) {
    if ((estad.See_Casilla(fila,columna)%3)   == (estad.See_Casilla(fila-1,columna+1)%3)) {// and
      //  (estad.See_Casilla(fila-1,columna+1)%3) == (estad.See_Casilla(fila-2,columna+2)%3)) { //and
        //(estado.See_Casilla(fila-2,columna+2)%3) == (estado.See_Casilla(fila-3,columna+3)%3)) {
        //cout << "En la diagonal secundaria\n";

        ganador = (estad.See_Casilla(fila-1,columna+1));
        //cout << "El valor de la casilla MOD actual es " << estad.See_Casilla(fila-1,columna)  << endl;
        if (ganador == jugador)
          nrayas++;
        //cout << "Entro en el if del ganador" << endl;
    }
  }

  return nrayas;
}


// Funcion de valoracion para testear Poda Alfabeta
double ValoracionTest(const Environment &estado, int jugador){
    int ganador = estado.RevisarTablero();

    if (ganador==jugador)
       return 99999999.0; // Gana el jugador que pide la valoracion
    else if (ganador!=0)
            return -99999999.0; // Pierde el jugador que pide la valoracion
    else if (estado.Get_Casillas_Libres()==0)
            return 0;  // Hay un empate global y se ha rellenado completamente el tablero
    else
          return Puntuacion(jugador,estado);
}

// ------------------- Los tres metodos anteriores no se pueden modificar



// Funcion heuristica (ESTA ES LA QUE TENEIS QUE MODIFICAR)
double Valoracion(const Environment &est, int numJug){
  int adversario;
  if (numJug == 1)
    adversario = 2;
  else
    adversario = 1;

  if(est.RevisarTablero() == numJug) {
    return masinf;
  }
  else if(est.RevisarTablero() == adversario)
    return menosinf;


  double valoracion = 0;

  //Número de 3-rayas
  int nRayasCurrent = 0;
  int nRayasAdversario = 0;

  int nDosRayasCurrent = 0;
  int nDosRayasAdversario = 0;



  for(int i = 0; i < 7; i++) {
    for(int j = 0; j < 7; j++) {
      nRayasCurrent += tresRayas(est, i, j, numJug);
      nRayasAdversario += tresRayas(est, i, j, adversario);
      nDosRayasCurrent += dosRayas(est, i, j, numJug);
      nDosRayasAdversario += dosRayas(est, i, j, adversario);
    }
  }

  //cout << "Current jugador hace " << nRayasCurrent << endl;
  //cout << "Adversario hace " << nRayasAdversario << endl;
  //cout << "-----------" << endl;

  valoracion = -(nRayasCurrent * 100) + (nRayasAdversario * 100);
  valoracion += (- (nDosRayasCurrent*0.5)  + (0.5*nDosRayasAdversario));
  //cout << "VALORACION FUNCION " << valoracion << endl;
  return valoracion;
}


// Esta funcion no se puede usar en la version entregable
// Aparece aqui solo para ILUSTRAR el comportamiento del juego
// ESTO NO IMPLEMENTA NI MINIMAX, NI PODA ALFABETA
void JuegoAleatorio(bool aplicables[], int opciones[], int &j){
    j=0;
    for (int i=0; i<8; i++){
        if (aplicables[i]){
           opciones[j]=i;
           j++;
        }
    }
}

// AQUI ES DONDE TENGO QUE HACER EL MINIMAX Y ALFABETA
// DE MOMENTO ES MINIMAX, SIN PODA

// estado actual - jugador actual -
//double Poda_AlfaBeta(actual_, jugador_, 0, PROFUNDIDAD_ALFABETA, accion, alpha, beta) {
double Poda_AlfaBeta(const Environment &a,int jug,int depth, int PROFUNDIDAD_ALFABETA,Environment::ActionType &accion,double alpha,double beta) {
  // Calculo todas las acciones posibles a partir de actual_
  int n_estados_siguientes;
  //Calcular la lista de estados siguientes posibles
  Environment estados_siguientesAux[8];
  n_estados_siguientes = a.GenerateAllMoves(estados_siguientesAux);

  //Si no hay estados siguientes, es nodo hoja, o bien, llego a la profunidad
  if (n_estados_siguientes == 0 || depth == PROFUNDIDAD_ALFABETA || a.RevisarTablero() == 1 || a.RevisarTablero() == 2) {
    //cout << "fin de busqueda por estado final: "<< n_estados_siguientes << endl;
    return Valoracion(a, jug);
  }

  // Si es el que maximiza
  //j es el estado que ha dado el valor maximo
  int j = 0;
  if (depth % 2 == 0) {
    double maxEval = menosinf;
    //Los hijos son los estados posibles
    for(int i = 0; i < n_estados_siguientes; i++) {
      double eval = Poda_AlfaBeta(estados_siguientesAux[i],jug, depth+1, PROFUNDIDAD_ALFABETA, accion, alpha, beta);
      if (eval > maxEval) {
        maxEval = max(maxEval, eval);
        alpha = max(alpha, eval);
        //cout << "El valor de beta y alpha es " << beta << "-- " << alpha << endl;
        j = i;
      }
      if(beta <= alpha)
        break;
    }
    //Devolvemos la accion que ha tenido mayor puntuacion
    if(depth==0)
      accion = static_cast< Environment::ActionType > (estados_siguientesAux[j].Last_Action(jug));

    return maxEval;
  } else {
    double minEval = masinf;
    for(int i = 0; i < n_estados_siguientes; i++) {
      double eval = Poda_AlfaBeta(estados_siguientesAux[i],jug, depth+1, PROFUNDIDAD_ALFABETA, accion, alpha, beta);
      minEval = min(minEval, eval);
      beta = min(beta,eval);
      if (beta <= alpha)
        break;
    }
    //Devolvemos valor nodo y guardamos la accion a devolver en accion
    return minEval;
  }
}



// Invoca el siguiente movimiento del jugador
Environment::ActionType Player::Think(){
    const int PROFUNDIDAD_MINIMAX = 6;  // Umbral maximo de profundidad para el metodo MiniMax
    const int PROFUNDIDAD_ALFABETA = 8; // Umbral maximo de profundidad para la poda Alfa_Beta

    Environment::ActionType accion; // acci�n que se va a devolver
    bool aplicables[8]; // Vector bool usado para obtener las acciones que son aplicables en el estado actual. La interpretacion es
                        // aplicables[0]==true si PUT1 es aplicable
                        // aplicables[1]==true si PUT2 es aplicable
                        // aplicables[2]==true si PUT3 es aplicable
                        // aplicables[3]==true si PUT4 es aplicable
                        // aplicables[4]==true si PUT5 es aplicable
                        // aplicables[5]==true si PUT6 es aplicable
                        // aplicables[6]==true si PUT7 es aplicable
                        // aplicables[7]==true si BOOM es aplicable



    double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha, beta; // Cotas de la poda AlfaBeta

    int n_act; //Acciones posibles en el estado actual

/*
    n_act = actual_.possible_actions(aplicables); // Obtengo las acciones aplicables al estado actual en "aplicables"
    int opciones[10];

    // Muestra por la consola las acciones aplicable para el jugador activo
    //actual_.PintaTablero();
    cout << " Acciones aplicables ";
    (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
    for (int t=0; t<8; t++)
      if (aplicables[t])
         cout << " " << actual_.ActionStr( static_cast< Environment::ActionType > (t)  );
    cout << endl;
  */


    //--------------------- COMENTAR Desde aqui

    /*
    cout << "\n\t";
    int n_opciones=0;
    JuegoAleatorio(aplicables, opciones, n_opciones);

    if (n_act==0){
      (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
      cout << " No puede realizar ninguna accion!!!\n";
      //accion = Environment::actIDLE;
    }
    else if (n_act==1){
           (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
            cout << " Solo se puede realizar la accion "
                 << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[0])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[0]);

         }
         else { // Hay que elegir entre varias posibles acciones
            int aleatorio = rand()%n_opciones;
            cout << " -> " << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[aleatorio])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[aleatorio]);
         }

    //--------------------- COMENTAR Hasta aqui

    */


    //--------------------- AQUI EMPIEZA LA PARTE A REALIZAR POR EL ALUMNO ------------------------------------------------
    /*
    Environment estados_siguientes[8];
    int n_estados_siguientes;
    //Calcular la lista de estados siguientes posibles
    n_estados_siguientes = actual_.GenerateAllMoves(estados_siguientes);
    //Iterar por la lista de estados siguientes
    bool hayJugadaGanadora = false;
    for(int i = 0; i < n_estados_siguientes && !hayJugadaGanadora; i++) {
      Environment e = estados_siguientes[i];

      //Con el jugador_actual sé si gano o no
      //Si da True, es que ha ganado
      if(e.RevisarTablero() == jugador_) {
        //Devolvemos la accion que nos ha llevado a este estado ganador
        int n_accion = e.Last_Action(jugador_);
        accion = static_cast< Environment::ActionType > (n_accion);
        hayJugadaGanadora = true;

        cout << "Se ha encontrado jugada ganadora " << actual_.ActionStr(accion) << endl;
      }
    }

    if(!hayJugadaGanadora) {
      //Como no hay una jugada ganadora, seleccionamos uno aleatoria
      int seleccion_aleatoria;
      seleccion_aleatoria = rand() % n_estados_siguientes;

      Environment estado_aleatorio;
      estado_aleatorio = estados_siguientes[seleccion_aleatoria];

      int n_accion = estado_aleatorio.Last_Action(jugador_);
      accion = static_cast< Environment::ActionType > (n_accion);
      cout << "No se ha encontrado jugada ganadora " << actual_.ActionStr(accion) << endl;
    }
    */


    // Opcion: Poda AlfaBeta
    // NOTA: La parametrizacion es solo orientativa
    alpha = menosinf;
    beta = masinf;
    valor = Poda_AlfaBeta(actual_, jugador_, 0, PROFUNDIDAD_ALFABETA, accion, alpha, beta);
    cout << "Valor MiniMax: " << valor << "  Accion: " << actual_.ActionStr(accion) << endl;

    return accion;
}
