#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_EQUIPOS 10
#define MAX_JUGADORES 50
#define MAX_PARTIDOS 20

typedef struct {
    int id;
    char nombre[50];
    int puntos;
    int golesFavor;
    int golesContra;
} Equipo;

typedef struct {
    int id;
    char nombre[50];
    int equipo_id;
    int goles;
} Jugador;

typedef struct {
    int id;
    int equipo_local_id;
    int equipo_visita_id;
    int goles_local;
    int goles_visita;
} Partido;

void registrarEquipos(Equipo equipos[], int *numEquipos);
void guardarEquiposArchivo(Equipo equipos[], int numEquipos);
void cargarEquiposArchivo(Equipo equipos[], int *numEquipos);

void registrarPartido(Partido partidos[], int *numPartidos, Jugador jugadores[], int *numJugadores, Equipo equipos[], int numEquipos);
void mostrarGoleadorDelTorneo(Jugador jugadores[], int numJugadores);
void mostrarTablaDePosiciones(Equipo equipos[], int numEquipos);
void mostrarEquipos(Equipo equipos[], int numEquipos);

#endif