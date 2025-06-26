#include <stdio.h>
#include "funciones.h"

int main() {
    Equipo equipos[MAX_EQUIPOS];
    Jugador jugadores[MAX_JUGADORES];
    Partido partidos[MAX_PARTIDOS];

    int numEquipos = 0;
    int numJugadores = 0;
    int numPartidos = 0;

    int opcion;

    cargarEquiposArchivo(equipos, &numEquipos);

    do {
        printf("\n=== MENU ===\n");
        printf("1. Ingresar equipos participantes\n");
        printf("2. Registrar partido y goles por jugador\n");
        printf("3. Mostrar goleador del torneo\n");
        printf("4. Ver tabla de posiciones\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                registrarEquipos(equipos, &numEquipos);
                break;
            case 2:
                registrarPartido(partidos, &numPartidos, jugadores, &numJugadores, equipos, numEquipos);
                break;
            case 3:
                mostrarGoleadorDelTorneo(jugadores, numJugadores);
                break;
            case 4:
                mostrarTablaDePosiciones(equipos, numEquipos);
                break;
            case 0:
                printf("Saliendo del sistema.\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }

    } while (opcion != 0);

    return 0;
}