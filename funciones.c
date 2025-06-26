#include <stdio.h>
#include <string.h>
#include "funciones.h"

void registrarEquipos(Equipo equipos[], int *numEquipos) {
    printf("Cuantos equipos desea registrar? ");
    scanf("%d", numEquipos);
    for (int i = 0; i < *numEquipos; i++) {
        printf("Nombre del equipo %d: ", i + 1);
        scanf(" %[^\n]", equipos[i].nombre);
        equipos[i].id = i + 1; // IDs empiezan desde 1
        equipos[i].puntos = 0;
        equipos[i].golesFavor = 0;
        equipos[i].golesContra = 0;
    }
    guardarEquiposArchivo(equipos, *numEquipos);
}

void guardarEquiposArchivo(Equipo equipos[], int numEquipos) {
    FILE *file = fopen("equipos.txt", "w");
    for (int i = 0; i < numEquipos; i++) {
        fprintf(file, "%d,%s,%d,%d,%d\n", equipos[i].id, equipos[i].nombre, equipos[i].puntos, equipos[i].golesFavor, equipos[i].golesContra);
    }
    fclose(file);
}

void cargarEquiposArchivo(Equipo equipos[], int *numEquipos) {
    FILE *file = fopen("equipos.txt", "r");
    *numEquipos = 0;
    if (file == NULL) return;
    while (fscanf(file, "%d,%[^,],%d,%d,%d\n", &equipos[*numEquipos].id, equipos[*numEquipos].nombre, &equipos[*numEquipos].puntos, &equipos[*numEquipos].golesFavor, &equipos[*numEquipos].golesContra) == 5) {
        (*numEquipos)++;
    }
    fclose(file);
}

void mostrarEquipos(Equipo equipos[], int numEquipos) {
    printf("Equipos participantes:\n");
    for (int i = 0; i < numEquipos; i++) {
        printf("%d: %s\n", equipos[i].id, equipos[i].nombre);
    }
}

int buscarJugadorPorID(Jugador jugadores[], int numJugadores, int id) {
    for (int i = 0; i < numJugadores; i++) {
        if (jugadores[i].id == id) return i;
    }
    return -1;
}

void registrarPartido(Partido partidos[], int *numPartidos, Jugador jugadores[], int *numJugadores, Equipo equipos[], int numEquipos) {
    Partido *p = &partidos[*numPartidos];
    p->id = *numPartidos + 1;

    mostrarEquipos(equipos, numEquipos);

    printf("Ingrese ID equipo local: ");
    int idLocal;
    scanf("%d", &idLocal);
    printf("Ingrese ID equipo visita: ");
    int idVisita;
    scanf("%d", &idVisita);

    // Validar IDs equipos
    int validLocal = 0, validVisita = 0;
    for (int i = 0; i < numEquipos; i++) {
        if (equipos[i].id == idLocal) validLocal = 1;
        if (equipos[i].id == idVisita) validVisita = 1;
    }
    if (!validLocal || !validVisita || idLocal == idVisita) {
        printf("IDs de equipos invalidos o iguales.\n");
        return;
    }

    p->equipo_local_id = idLocal;
    p->equipo_visita_id = idVisita;

    int golesLocal = 0, golesVisita = 0;

    printf("Cuantos goles marco el equipo local %s? ", equipos[idLocal-1].nombre);
    scanf("%d", &golesLocal);

    for (int i = 0; i < golesLocal; i++) {
        int jugador_id;
        printf("Ingrese ID del jugador que anoto el gol local #%d (o 0 para registrar nuevo jugador):\n", i+1);
        for (int j = 0; j < *numJugadores; j++) {
            if (jugadores[j].equipo_id == idLocal) {
                printf("%d: %s\n", jugadores[j].id, jugadores[j].nombre);
            }
        }
        scanf("%d", &jugador_id);

        if (jugador_id == 0) {
            if (*numJugadores >= MAX_JUGADORES) {
                printf("Limite de jugadores alcanzado.\n");
                i--; 
                continue;
            }
            printf("Ingrese nombre del nuevo jugador: ");
            getchar(); 
            scanf(" %[^\n]", jugadores[*numJugadores].nombre);
            jugadores[*numJugadores].id = (*numJugadores) + 1;
            jugadores[*numJugadores].equipo_id = idLocal;
            jugadores[*numJugadores].goles = 1;
            (*numJugadores)++;
        } else {
            int idx = buscarJugadorPorID(jugadores, *numJugadores, jugador_id);
            if (idx == -1 || jugadores[idx].equipo_id != idLocal) {
                printf("Jugador invalido para el equipo local.\n");
                i--; 
            } else {
                jugadores[idx].goles++;
            }
        }
    }

    printf("Cuantos goles marco el equipo visita %s? ", equipos[idVisita-1].nombre);
    scanf("%d", &golesVisita);

    for (int i = 0; i < golesVisita; i++) {
        int jugador_id;
        printf("Ingrese ID del jugador que anoto el gol visita #%d (o 0 para registrar nuevo jugador):\n", i+1);
        for (int j = 0; j < *numJugadores; j++) {
            if (jugadores[j].equipo_id == idVisita) {
                printf("%d: %s\n", jugadores[j].id, jugadores[j].nombre);
            }
        }
        scanf("%d", &jugador_id);

        if (jugador_id == 0) {
            if (*numJugadores >= MAX_JUGADORES) {
                printf("Limite de jugadores alcanzado.\n");
                i--; 
                continue;
            }
            printf("Ingrese nombre del nuevo jugador: ");
            getchar(); // limpiar buffer
            scanf(" %[^\n]", jugadores[*numJugadores].nombre);
            jugadores[*numJugadores].id = (*numJugadores) + 1;
            jugadores[*numJugadores].equipo_id = idVisita;
            jugadores[*numJugadores].goles = 1;
            (*numJugadores)++;
        } else {
            int idx = buscarJugadorPorID(jugadores, *numJugadores, jugador_id);
            if (idx == -1 || jugadores[idx].equipo_id != idVisita) {
                printf("Jugador invalido para el equipo visita.\n");
                i--; // repetir
            } else {
                jugadores[idx].goles++;
            }
        }
    }

    p->goles_local = golesLocal;
    p->goles_visita = golesVisita;

    equipos[idLocal-1].golesFavor += golesLocal;
    equipos[idLocal-1].golesContra += golesVisita;
    equipos[idVisita-1].golesFavor += golesVisita;
    equipos[idVisita-1].golesContra += golesLocal;

    if (golesLocal > golesVisita) equipos[idLocal-1].puntos += 3;
    else if (golesLocal < golesVisita) equipos[idVisita-1].puntos += 3;
    else {
        equipos[idLocal-1].puntos += 1;
        equipos[idVisita-1].puntos += 1;
    }

    (*numPartidos)++;
    guardarEquiposArchivo(equipos, numEquipos);

    printf("Resultado: %s %d - %d %s\n", equipos[idLocal-1].nombre, golesLocal, golesVisita, equipos[idVisita-1].nombre);
}

void mostrarGoleadorDelTorneo(Jugador jugadores[], int numJugadores) {
    int maxGoles = -1;
    int idGoleador = -1;

    for (int i = 0; i < numJugadores; i++) {
        if (jugadores[i].goles > maxGoles) {
            maxGoles = jugadores[i].goles;
            idGoleador = i;
        }
    }

    if (idGoleador != -1) {
        printf("Goleador del torneo: %s con %d goles\n", jugadores[idGoleador].nombre, jugadores[idGoleador].goles);
    } else {
        printf("No hay goles registrados aun.\n");
    }
}

void mostrarTablaDePosiciones(Equipo equipos[], int numEquipos) {
    printf("\n=== Tabla de Posiciones ===\n");
    printf("%-3s %-20s %-6s %-6s %-6s\n", "ID", "Equipo", "PTS", "GF", "GC");
    for (int i = 0; i < numEquipos; i++) {
        printf("%-3d %-20s %-6d %-6d %-6d\n", equipos[i].id, equipos[i].nombre, equipos[i].puntos, equipos[i].golesFavor, equipos[i].golesContra);
    }
}