//5) Define los siguientes tipo registro y sus funciones 
//asociadas. Además, implementa un programa principal que te permita probar todas las funciones:

/*
- TTimeStamp: el registro almacena 3 enteros, cada uno almacena el número de horas, minutos y segundos de una marca de tiempo.
    Implementa la función isValid que determina si un timestamp tiene valores correctos en los campos horas, minutos y segundos.
    Implementa la función readTimestamp que lee de teclado un timestamp válido y lo devuelve.
    Implementa la función showTimeStamp que dada una variable TTimestamp muestra por pantalla la marca de tiempo con el formato
    hh:mm:ss
*/
#include <stdio.h>
#include <string.h>

enum event{START, STOP, PAUSE, FORWARD, BACKWARD};
typedef struct TTimeStamp{
    int horas;
    int minutos;
    int segundos;
}TTimeStamp;

typedef struct TTimedEvent{
    TTimeStamp time;
    enum event evento;


}TTimedEvent;

TTimedEvent readTimedEvent(){
    TTimedEvent res;
    res.time = readTimestamp();
    char event[10];
    printf("Introduzca el evento\n");
    scanf("%s",event);
    res.evento = stringToEvent(event);
    while (res.evento == -1){
        printf("Evento no válido. Inténtelo de nuevo.\n");
        printf("Introduzca el evento\n");
        scanf("%s",event);
        res.evento = stringToEvent(event);
    }
    return res;

} 



int stringToEvent(char *event){
    if(strcmp("START",event) == 0){
        return START;
    } else if(strcmp("STOP",event) == 0){
        return STOP;
    } else if(strcmp("PAUSE",event) == 0){
        return PAUSE;
    } else if(strcmp("FORWARD",event) == 0){
        return FORWARD;
    } else if(strcmp("BACKWARD",event) == 0){
        return BACKWARD;
    }
    return -1;
}

char *eventToString(enum event event){
    switch(event){
        case START:
            return "START";
        case STOP:
            return "STOP";
        case PAUSE:
            return "PAUSE";
        case FORWARD:
            return "FORWARD";
        case BACKWARD:
            return "BACKWARD";
    }
    return "ERROR";
}



int isValid(TTimeStamp time){
   return (time.horas <= 24 && time.minutos <= 60 && time.segundos <= 60);
}

TTimeStamp readTimestamp() {
    TTimeStamp res;
    printf("Ingrese el timestamp en formato hh:mm:ss: ");
    scanf("%d:%d:%d", &res.horas, &res.minutos, &res.segundos);
    if (isValid(res)) {
        return res;
    } else {
        printf("Timestamp no válido. Inténtelo de nuevo.\n");
        // Devuelve un timestamp inválido para indicar un error.
        res.horas = -1;
        res.minutos = -1;
        res.segundos = -1;
        return res;
    }
}

void showTimeStamp(TTimeStamp time){
    printf("%d:%d:%d", time.horas, time.minutos, time.segundos);
}


int main(int argc, char *argv[]){

    TTimeStamp time = readTimestamp();
    showTimeStamp(time);


}