#include <iostream>
#include <string>
#include "position.hpp"
#include "piece.hpp"
#include "king.hpp"
#include "queen.hpp"
#include "knight.hpp"
#include "bishop.hpp"
#include "rook.hpp"
#include "pawn.hpp"
#include <fstream>

using namespace std;

Piece*** crearTablero(int rows, int cols);
void destruirTablero(Piece*** tablero, int rows, int cols);
void imprimir(Piece*** tablero);
void chessInit(Piece*** tablero);
int charToInt(char coordenada);
bool ganar(Piece*** tablero);
void Guardar(Piece*** tablero);

int main(int argc, char const *argv[]){
	const int ROWS = 8;
	const int COLS = 8;
	Piece*** tablero = crearTablero(ROWS,COLS);

	string nombre1,nombre2;
	cout<<"Jugador1 ingrese su nombre: "<<endl;
	cin>>nombre1;
	cout<<"Jugador2 ingrese su nombre: "<<endl;
	cin>>nombre2;
	int turno=0;
	bool gano=false;
	char coordenada1, coordenada2;	
	while(!gano){
		bool valid = false;//variable de validacion
		imprimir(tablero);
		turno++;
		int x=0,y=0,x1=0,y1=0;
		if (turno % 2 == 1) {
			while(!valid){//ciclo de validacion
				cout<<"Turno de: "<< nombre1 <<endl;
				cout<<"Ingrese columna de la pieza que desea mover: ";
				cin >> x ; //Se cambio la variable que obtiene datos
				x--;
				cout<<"Ingrese fila de la pieza que desea mover: ";
				cin >> y;
				y --; //Se hizo su substraccion para agarrar su posicion real dentro de la matriz
				cout<<"Ingrese columna a la desea mover la pieza: ";
				cin >> x1;
				x1--;
				cout<<"Ingrese fila a la desea mover la pieza: : ";
				cin >> y1;
				y1 --;
				Position pos(x1,y1);
				if (tablero[y][x]->getColor()=='N' && tablero[y][x] != NULL){//validacion de mover
					if(tablero[y][x]->moveTo(tablero,pos))
						valid = true;//variable de validacion
					else
						valid = false;
				}else{
					cerr << "No se puede mover las piezas del juagdor opuesto" << endl;
				}
			}

		}else{
			while(!valid){//ciclo de validacion
				cout<<"Turno de: "<<nombre2<<endl;
				cout<<"Ingrese columna de la pieza que desea mover: ";
				cin>>x;
				x--;
				cout<<"Ingrese fila de la pieza que desea mover: ";
				cin >> y; //Se cambio la variable que obtiene datos
				y --; //Se hizo su substraccion para agarrar su posicion real dentro de la matriz
				cout<<"Ingrese columna a la desea mover la pieza: ";
				cin>>x1;
				x1--;
				cout<<"Ingrese fila a la desea mover la pieza: : ";
				cin >> y1; //Se cambio la variable que obtiene datos
				y1 --; //Se hizo su substraccion para agarrar su posicion real dentro de la matriz

				Position pos(x1,y1);
				if (tablero[y][x]->getColor()=='B' && tablero[y][x] != NULL){//validacion de mover
					if(tablero[y][x]->moveTo(tablero,pos))
						valid = true;//variable de validacion
					else
						valid = false;
				}else{
					cerr << "No se puede mover las piezas del jugador opuesto" << endl;
				}
			}
		}
		Guardar(tablero);
		gano = ganar(tablero);
		if (gano == true)
		{
			if ( remove ( "chess.alv") != 0)
			{
				cout<<"Error borrando archivo"<<endl;
			}else{
				cout<<"El archivo se borro exitosamente!"<<endl;
			}
		}
	}

	destruirTablero(tablero,ROWS,COLS);
	return 0;
}
Piece*** crearTablero(int rows, int cols){
	Piece*** retval = new Piece**[rows];
	for (int i = 0; i < rows; ++i)	{
		retval[i] = new Piece*[cols];
	}
	for (int i = 0; i < rows; ++i){
		for (int j = 0; j < cols; ++j){
			retval[i][j] = NULL;
		}
	}
	chessInit(retval);
	return retval;
}
void destruirTablero(Piece*** tablero, int rows, int cols){
	for (int i = 0; i < cols; ++i)	{
		delete[] tablero[i];
	}
	delete[] tablero;
}
void imprimir(Piece*** tablero){//imprimir tablero
	char letras[] = "ABCDEFGH";
	int numeros[] = {1,2,3,4,5,6,7,8};
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j)	{
			if(tablero[i][j] != NULL)
				cout << "[" << tablero[i][j]->toString() << "]";
			else
				cout << "[ ]";
		}
		cout << numeros[i] << endl;
	}
	for (int i = 0; i < 8; ++i)	{
		cout << " " << letras[i] << " ";
	}
	cout << endl;
}
void chessInit(Piece*** tablero){//Inicializar tablero
	//piezas blancas
	//torres
	tablero[0][0] = new Rook('B',0,0);
	tablero[0][7] = new Rook('B',7,0);
	//caballos
	tablero[0][1] = new Knight('B',1,0);
	tablero[0][6] = new Knight('B',6,0);
	//alfiles
	tablero[0][2] = new Bishop('B',2,0);
	tablero[0][5] = new Bishop('B',5,0);
	//rey
	tablero[0][3] = new King('B',3,0);
	//reina
	tablero[0][4] = new Queen('B',4,0);
	//peones
	for (int i = 0; i < 8; ++i){
		tablero[1][i] = new Pawn('B',i,1);
	}
	//piezas negras
	//torres
	tablero[7][0] = new Rook('N',0,7);
	tablero[7][7] = new Rook('N',7,7);
	//caballos
	tablero[7][1] = new Knight('N',1,7);
	tablero[7][6] = new Knight('N',6,7);
	//alfiles
	tablero[7][2] = new Bishop('N',2,7);
	tablero[7][5] = new Bishop('N',5,7);
	//rey
	tablero[7][3] = new King('N',3,7);
	//reina
	tablero[7][4] = new Queen('N',4,7);
	//peones
	for (int i = 0; i < 8; ++i){
		tablero[6][i] = new Pawn('N',i,6);
	}
}
int charToInt(char coordenada){
	switch (coordenada){
		case 'a':
			return 0;
		case 'b':
			return 1;
		case 'c':
			return 2;
		case 'd':
			return 3;
		case 'e':
			return 4;
		case 'f':
			return 5;
		case 'g':
			return 6;
		case 'h':
			return 7;
		case 'A':
			return 0;
		case 'B':
			return 1;
		case 'C':
			return 2;
		case 'D':
			return 3;
		case 'E':
			return 4;
		case 'F':
			return 5;
		case 'G':
			return 6;
		case 'H':
			return 7;
		default:
			return -1;
	}
}
bool ganar(Piece*** tablero){
	int cont=0;
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			if(dynamic_cast<King*>(tablero[i][j]) != NULL){
				King* king = dynamic_cast<King*>(tablero[i][j]);
				cont++;
			}
		}
	}
	if (cont==1)
	{
		return true;
	}
	return false;
}


void Guardar(Piece*** tablero){
	ofstream archivo;
	archivo.open("chess.alv" , ios::out | ios::binary);
	archivo.write(reinterpret_cast<char *> (&tablero), sizeof(tablero));
	archivo.close();
}