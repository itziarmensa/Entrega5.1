#include <stdio.h>
#include <string.h>
typedef struct{
	char nombre[20];
	int socket;
}Conectado;

typedef struct{
	Conectado conectados[100];
	int num;
}ListaConectados;

int Pon(ListaConectados *lista, char nombre[20], int socket){
	//añade nuevo conectados. retorna 0 si ok y -1 si la lista ya estaba llena
	if(lista->num == 100)
		return -1;
	else{
		strcpy(lista->conectados[lista->num].nombre, nombre);
		lista->conectados[lista->num].socket = socket;
		lista->num++;
		return 0;
	}
}

int DamePosicion(ListaConectados *lista, char nombre[20]){
	//Devuelve el socket o -1 si no está en la lista
	int i = 0;
	int encontrado = 0;
	while((i<lista->num)&&!encontrado)
	{
		if(strcmp(lista->conectados[i].nombre,nombre) == 0)
			encontrado = 1;
		if(!encontrado)
			i = i+1;
	}
	if(encontrado)
		return i;
	else
		return -1;
}

int Eliminar(ListaConectados *lista, char nombre[20]){
	//Retorna 0 si elimina y -1 si no puede
	int pos = DamePosicion(lista, nombre);
	if(pos == -1)
		return -1;
	else{
		int i;
		for (i = pos; i<lista->num-1; i++)
		{
			strcpy(lista->conectados[i].nombre, lista->conectados[i+1].nombre);
			lista->conectados[i].socket = lista->conectados[i+1].socket;
		}
		lista->num--;
		return 0;
	}
}

void DameConectados(ListaConectados *lista, char conectados[300]){
	//Pone en conectados los nombre de todos los conectados separados por /. Pirmero pone el numero de conectados. Ejemeplo: "3/Juan/Maria/Pedro
	sprintf(conectados,"%d", lista->num);
	int i;
	for (i=0; i<lista->num; i++)
		sprintf(conectados,"%s,%s", conectados, lista->conectados[i].nombre);
}

void Entrega(ListaConectados *lista, char conectados[300]){
	DameConectados(lista,conectados);
	int i;
	for (i=0; i<lista->num; i++)
		sprintf(conectados,"%s,%s", conectados, lista->conectados[i].socket);
	
}

int main(int argc, char *argv[]) {
	ListaConectados miLista;
	miLista.num = 0;
	Pon(&miLista, "Luis", 5);
	Pon(&miLista, "Maria", 5);
	Pon(&miLista, "Victor", 5);
	int res = Pon(&miLista, "Juan", 5);
	if(res == -1)
		printf("Lista llena. No se ha podido añadir.\n");
	else
		printf("Añadido bien.\n");
	int pos = DamePosicion(&miLista, "Juan");
	if(pos != -1)
		printf("El socket de Juan es: %d\n", miLista.conectados[pos].socket);
	else
		printf("No encontrado el usuario.\n");
	int elimina = Eliminar (&miLista, "Juan");
	if(elimina == -1)
		printf("no está.\n");
	else
		printf("eliminado.\n");
	char misconectados[300];
	DameConectados(&miLista, misconectados);
	printf("Resultado: %s\n", misconectados);
	
	char *p = strtok(misconectados, "/");
	int n = atoi(p);
	int i;
	for(i = 0; i<n; i++)
	{
		char nombre[20];
		int socket;
		p = strtok (NULL, "/");
		strcpy(nombre, p);
		printf("Conectado: %s\n", nombre);
	}
	
	char conectados[300];
	Entrega(&miLista, conectados);
	printf("Entrega: %s\n", conectados);
	
	
	return 0;
}

