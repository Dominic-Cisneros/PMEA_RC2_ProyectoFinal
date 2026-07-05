#ifndef REGISTRO_H
#define REGISTRO_H
 
#define MAX_REGISTROS 200
#define MAX_COD 16
#define MAX_FECHA 11
#define MAX_CENTRO 20
 
typedef struct {
    char codigo_registro[MAX_COD];
    char fecha[MAX_FECHA];
    char centro_costo[MAX_CENTRO];
    int turno;
    float materia_prima_kg;
    float desperdicio_kg;
    int tiempo_min;
    int unidades_producidas;
} Registro;
 
extern Registro registros[MAX_REGISTROS];
extern int totalRegistros;
 
void registrarTurno();
void listarRegistros();
void buscarRegistro();
void actualizarRegistro();
void eliminarRegistro();
void reportePorCentro();
float calcularRendimiento(Registro *r);
int existeCodigo(char *codigo);
int existeDuplicado(char *fecha, char *centro, int turno, char *codigoExcluir);
 
#endif