typedef enum{
    opcion1=1,
    opcion2,
    opcion3,
    opcion4,
    salida
}menu_t;

typedef struct{
    int integer;
    char string[30];
    float float_num;  
}estructura_t;

typedef struct{
    uint16_t codigo;
    uint16_t edad;
    char nombre[MAX_CHAR];
    float promedio;
}alumno_t;

