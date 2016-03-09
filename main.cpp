#include <ncurses.h>
#include <string>
#include <cmath>

using std::abs;
using std::string;

int** contructorArray(int, int);
void destructorArray(int**,int);
void impTablero(int**, int, int);
void llenarTablero(int**, int,int);
char* movimientoFun(int);
void textoMov(char*,int,int);
void deleteMov(char*);
void cambiarTablero(int**,char*);
int coorX(char*);
int coorX2(char*);
int coorY(char*);
int coorY2(char*);
bool validarPiezaSel(int**,int,char*);
bool validarMoviento(char*, int, int**,int,int);
bool validarRey(char*,int**);
bool validarTorre(char*,int**);
bool validarAlfil(char*,int**);
bool validarCab(char*,int**);
bool validarPeon(char*, int, int**);
bool validarReina(char*,int**);
bool piezaComePieza(char*, int, int**);
bool pasoLibre(char*, int, int**);

int main(int argc, char const *argv[])
{
	initscr();
    start_color();
	const int columns = 8;//x
	const int rows = 8;//y
	const int cantChars = 5;
	int** tableroMain = contructorArray(columns, rows);
	llenarTablero(tableroMain,columns, rows);//Defaulr
	bool seguir = true, posiblePrbl = true;
	int turno = 1, turnoJug1=1, turnoJug2=1;
	char* movimiento1 = movimientoFun(cantChars);
	do
	{
		if (turno == 1)
		{
			impTablero(tableroMain, columns, rows);
			while(posiblePrbl)
			{
				textoMov(movimiento1, cantChars, turno);
				getch();
				refresh();
				if (validarMoviento(movimiento1, turno, tableroMain,columns, rows) == true)
				{
					turno =2;
					posiblePrbl = false;
				}
				else
				{
					posiblePrbl = true;
				}
			}
			posiblePrbl = true;
		}
		else if (turno = 2)
		{
			impTablero(tableroMain, columns, rows);
			while(posiblePrbl)
			{
				textoMov(movimiento1, cantChars, turno);
				getch();
				refresh();
				if (validarMoviento(movimiento1, turno, tableroMain,columns, rows) == true)
				{
					turno =1;
					posiblePrbl = false;
				}
				else
				{
					posiblePrbl = true;
				}
			}
			posiblePrbl = true;
		}
	} while (seguir);
	destructorArray(tableroMain, rows);
	deleteMov(movimiento1);
	getch();
	refresh();
	endwin();
	return 0;
}
int** contructorArray(int col, int row)
{
	int** tablero = new int*[col];
	for (int i = 0; i < col; ++i)
	{
		tablero[i] = new int[row];
	}
	return tablero;
}
void destructorArray(int** tablero, int row)
{
	for (int i = 0; i < row; ++i)
	{
		delete [] tablero[i];
	}
	delete [] tablero;
}
void textoMov(char* movimiento, int numChars, int turno)
{
	int contador =0;
	int moveX = 15;
	while(contador < (numChars -1) ){
		if (turno == 1)
		{
			/* Jugador 1 - Blancas */
			mvprintw(20,0, "Jugador 1");
		}else
		{
			/* Jugador 2 - Negras */
			mvprintw(20,0, "Jugador 2");
		}
		noecho();
		char temp;
		temp = getch();
		if( ((temp >= 65 && temp <= 72) || (temp >= 97 && temp <= 104)) && ((contador == 0) || contador ==2) ){
			echo();
			mvaddch(20,(moveX + contador),temp);
			movimiento[contador] = temp;
			contador++;
		}
		if(  (temp >= '0' && temp <= '7') && ((contador == 1) || contador==3) ){
			echo();
			mvaddch(20,(moveX + contador),temp);
			movimiento[contador] = temp;
			contador++;
		}
	}
	movimiento[numChars] = '\0';
}
char* movimientoFun(int numChars)
{
	char* movimiento1 = new char[numChars];	
	return movimiento1;
}
void deleteMov(char* coord){delete [] coord;}
void llenarTablero(int** array, int col, int row)
{
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			//Blancas
			if ( (i == 0 && j == 0) || (i == 0  && j == (col - 1)) )
			{//Torre
				array[i][j] = 4;
			}else if( (i == 0 && j == 1) || (i == 0  && j == (col - 2)) )
			{//Alfil
				array[i][j] = 3;
			}else if ( (i == 0 && j == 2) || (i == 0  && j == (col - 3)) )
			{//Caballero
				array[i][j] = 2;
			}else if ( (i == 0 && j == 3) )
			{//Rey
				array[i][j] = 1;
			}else if ((i == 0 && j == 4))
			{//Reina
				array[i][j] = 0;
			}else if ( i == 1 && ( j == 0 || j == 1 || j == 2 || j == 3 || j == 4 || j == 5 || j == 6 || j == 7)  )
			{//Peón
				array[i][j] = 5;
			}
			//Negras
			else if ( (i == 7 && j == 0) || (i == 7  && j == (col - 1)) )
			{//Torre
				array[i][j] = 7;
			}else if( (i == 7 && j == 1) || (i == 7  && j == (col - 2)) )
			{//Alfil
				array[i][j] = 8;
			}else if ( (i == 7 && j == 2) || (i == 7  && j == (col - 3)) )
			{//Caballero
				array[i][j] = 9;
			}else if ( (i == 7 && j == 3) )
			{//Rey
				array[i][j] = 10;
			}else if ((i == 7 && j == 4))
			{//Reina
				array[i][j] = 11;
			}else if ( i == 6 && ( j == 0 || j == 1 || j == 2 || j == 3 || j == 4 || j == 5 || j == 6 || j == 7)  )
			{//Peón
				array[i][j] = 12;
			}else
			{//Otros
				array[i][j] = 13;
			}
		}
	}
}

void impTablero(int** array, int col, int row)
{
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_RED);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    int desplasarHor = 2,desplasarVert =1;
    mvprintw(2,3,"0");
    mvprintw(4,3,"1");
    mvprintw(6,3,"2");
    mvprintw(8,3,"3");
    mvprintw(10,3,"4");
    mvprintw(12,3,"5");
    mvprintw(14,3,"6");
    mvprintw(16,3,"7");
    mvprintw(1,8," A ");
    mvprintw(1,12," B ");
    mvprintw(1,16," C ");
    mvprintw(1,20," D ");
    mvprintw(1,24," E ");
    mvprintw(1,28," F ");
    mvprintw(1,32," G ");
    mvprintw(1,36," H ");

	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			if (array[i][j] == 4)
			{//Blancas
				attron(COLOR_PAIR(2));
				mvprintw((i+desplasarVert)*2,(j+desplasarHor)*4,"[T]");
			}else if (array[i][j] == 3)
			{
				attron(COLOR_PAIR(2));
				mvprintw((i+desplasarVert)*2,(j+desplasarHor)*4, "[A]");
			}else if (array[i][j] == 2)
			{
				attron(COLOR_PAIR(2));
				mvprintw((i+desplasarVert)*2,(j+desplasarHor)*4, "[C]");
			}else if (array[i][j] == 1)
			{
				attron(COLOR_PAIR(2));
				mvprintw((i+desplasarVert)*2,(j+desplasarHor)*4, "[R]");
			}else if (array[i][j] == 0)
			{
				attron(COLOR_PAIR(2));
				mvprintw((i+desplasarVert)*2,(j+desplasarHor)*4, "[Q]");				
			}else if (array[i][j] == 5)
			{
				attron(COLOR_PAIR(2));
				mvprintw((i+desplasarVert)*2,(j+desplasarHor)*4, "[P]");
			}else if (array[i][j] == 7)
			{//Negras
			    attron(COLOR_PAIR(1));
				mvprintw((i+desplasarVert)*2,(j+desplasarHor)*4,"[T]");
			}else if (array[i][j] == 8)
			{
				attron(COLOR_PAIR(1));
				mvprintw((i+desplasarVert)*2,(j+desplasarHor)*4, "[A]");
			}else if (array[i][j] == 9)
			{
				attron(COLOR_PAIR(1));
				mvprintw((i+desplasarVert)*2,(j+desplasarHor)*4, "[C]");
			}else if (array[i][j] == 10)
			{
				attron(COLOR_PAIR(1));
				mvprintw((i+desplasarVert)*2,(j+desplasarHor)*4, "[R]");
			}else if (array[i][j] == 11)
			{
				attron(COLOR_PAIR(1));
				mvprintw((i+desplasarVert)*2,(j+desplasarHor)*4, "[Q]");
			}else if (array[i][j] == 12)
			{
				attron(COLOR_PAIR(1));
				mvprintw((i+desplasarVert)*2,(j+desplasarHor)*4, "[P]");
			}else
			{
				attron(COLOR_PAIR(3));
				mvprintw((i+desplasarVert)*2,(j+desplasarHor)*4, "[ ]");
			}
		}
	}
}
int coorX(char* coord)//Seleccionar
{
	char coordx[] = {'a','A','b','B','c','C','d','D','e','E','f','F','g','G','h','H','\0'};
	if (  (coord[0]== coordx[0] || coord[0]==coordx[1])  )
	{
		return 0;
	}else if ( (coord[0]==coordx[2] || coord[0] == coordx[3]))
	{
		return 1;
	}else if ((coord[0]==coordx[4] || coord[0]== coordx[5]))
	{
		return 2;
	}else if ((coord[0] == coordx[6] || coord[0]== coordx[7]))
	{
		return 3;
	}else if ((coord[0]== coordx[8] || coord[0]== coordx[9]))
	{
		return 4;
	}else if ((coord[0] == coordx[10] || coord[0]== coordx[11]))
	{
		return 5;
	}else if ((coord[0] == coordx[12] || coord[0] == coordx[13]))
	{
		return 6;
	}else if (( coord[0] == coordx[14] || coord[0] == coordx[15]))
	{
		return 7;
	}
}
int coorX2(char* coord)//Mover
{
	char coordx[] = {'a','A','b','B','c','C','d','D','e','E','f','F','g','G','h','H','\0'};
		if (  (coord[2]== coordx[0] || coord[2]==coordx[1])  )
		{
			return 0;
		}else if ( (coord[2]==coordx[2] || coord[2] == coordx[3]))
		{
			return 1;
		}else if ((coord[2]==coordx[4] || coord[2]== coordx[5]))
		{
			return 2;
		}else if ((coord[2] == coordx[6] || coord[2]== coordx[7]))
		{
			return 3;
		}else if ((coord[2]== coordx[8] || coord[2]== coordx[9]))
		{
			return 4;
		}else if ((coord[2] == coordx[10] || coord[2]== coordx[11]))
		{
			return 5;
		}else if ((coord[2] == coordx[12] || coord[2] == coordx[13]))
		{
			return 6;
		}else if (( coord[2] == coordx[14] || coord[2] == coordx[15]))
		{
			return 7;
		}
}
int coorY(char* coord)
{
	char coordy[] = {'0','1','2','3','4','5','6','7','\0'};
	if (  (coord[1]== coordy[0])  )
	{
		return 0;
	}else if ( (coord[1]==coordy[1]))
	{
		return 1;
	}else if ((coord[1]==coordy[2] ))
	{
		return 2;
	}else if ((coord[1] == coordy[3] ))
	{
		return 3;
	}else if ((coord[1]== coordy[4] ))
	{
		return 4;
	}else if ((coord[1] == coordy[5] ))
	{
		return 5;
	}else if ((coord[1] == coordy[6] ))
	{
		return 6;
	}else if (( coord[1] == coordy[7] ))
	{
		return 7;
	}
}
int coorY2(char* coord)
{
	char coordy[] = {'0','1','2','3','4','5','6','7','\0'};
	if (  (coord[3]== coordy[0])  )
	{
		return 0;
	}else if ( (coord[3]==coordy[1]))
	{
		return 1;
	}else if ((coord[3]==coordy[2] ))
	{
		return 2;
	}else if ((coord[3] == coordy[3] ))
	{
		return 3;
	}else if ((coord[3]== coordy[4] ))
	{
		return 4;
	}else if ((coord[3] == coordy[5] ))
	{
		return 5;
	}else if ((coord[3] == coordy[6] ))
	{
		return 6;
	}else if (( coord[3] == coordy[7] ))
	{
		return 7;
	}
}
bool validarPiezaSel(int** array,int turno, char* coord)
{
	int posx = coorX(coord);//Col
	int posy = coorY(coord);
	if (turno == 1)
	{
		if (array[posy][posx] == 0 ||array[posy][posx] == 1 ||array[posy][posx] == 2 || array[posy][posx] == 3 || array[posy][posx] == 4 || array[posy][posx] == 5)
		{
			return true;
		}else{
			return false;
		}
	}
	else if (turno == 2)
	{
		if (array[posy][posx] == 7 || array[posy][posx] == 8 || array[posy][posx] == 9 || array[posy][posx] == 10 || array[posy][posx] == 11 || array[posy][posx] == 12)
		{
			return true;
		}else{
			return false;
		}
	}
}
bool validarMoviento(char* coord, int turno, int** array,int col, int row)
{
	int posx = coorX(coord);
	int posy = coorY(coord);
	int posx2 = coorX2(coord);
	int posy2 = coorY2(coord);
	if (validarPiezaSel(array, turno, coord))
	{
		if(pasoLibre(coord, turno, array))
		{
			cambiarTablero(array, coord);
			return true;
		}
		else
		{
			return false;
		}
	}else{
		return false;
	}
}

void cambiarTablero(int** array, char* coord)
{
	int posx = coorX(coord);
	int posy = coorY(coord);
	int posx2 = coorX2(coord);
	int posy2 = coorY2(coord);
	int temp = array[posy][posx];
	array[posy2][posx2] = temp;
	array[posy][posx] = 13;
}

bool jaque(char* coord, int turno, int** array)
{
	int posx = coorX(coord);
	int posy = coorY(coord);
	int posx2 = coorX2(coord);
	int posy2 = coorY2(coord);
	if (turno == 1)
	{
		/* code */
	}else if (turno == 2)
	{
		/* code */
	}
}

bool validarRey(char* coord, int** array)
{
	int posx = coorX(coord);
	int posy = coorY(coord);
	int posx2 = coorX2(coord);
	int posy2 = coorY2(coord);
	if ( (( (abs(posx - posx2) == 1) || (abs(posx - posx2) == 0) ) && ( (abs(posy - posy2) == 1) || (abs(posy - posy2) == 0) ) && (abs(posx - posx2) != 0 && abs(posy - posy2) != 0 )) && (array[posy][posx] == 10 || array[posy][posx] == 1))
	{
		return true;
	}else 
	{
		return false;
	}
}

bool validarAlfil(char* coord, int** array)
{
	int posx = coorX(coord);
	int posy = coorY(coord);
	int posx2 = coorX2(coord);
	int posy2 = coorY2(coord);
	if ( ( abs(posx - posx2) == abs(posy - posy2) ) && (array[posy][posx] == 3 || array[posy][posx] == 8))
	{
		return true;
	}else
	{
		return false;
	}	
}

bool validarTorre(char* coord, int** array)
{
	int posx = coorX(coord);
	int posy = coorY(coord);
	int posx2 = coorX2(coord);
	int posy2 = coorY2(coord);
	if ( ((abs(posx - posx2) == 0) || (abs(posy - posy2) == 0 ) && ( abs(posx - posx2) != abs(posy - posy2) )) && (array[posy][posx] == 4 || array[posy][posx] == 7))
	{
		return true;
	}else
	{
		return false;
	}
}

bool validarCab(char * coord, int** array)
{
	int posx = coorX(coord);
	int posy = coorY(coord);
	int posx2 = coorX2(coord);
	int posy2 = coorY2(coord);
	if ( (( (abs(posx - posx2) == 1) || (abs(posx - posx2) == 2) ) && ( (abs(posy - posy2) == 1) || (abs(posy - posy2) == 2) ) && ( abs(posx - posx2) != abs(posy - posy2) )) && (array[posy][posx] == 2 || array[posy][posx] == 9))
	{
		return true;
	}else
	{
		return false;
	}	
}

bool validarReina(char* coord, int** array)
{
	int posx = coorX(coord);
	int posy = coorY(coord);
	int posx2 = coorX2(coord);
	int posy2 = coorY2(coord);
	if ( (( abs(posx - posx2) == abs(posy - posy2) ) || (abs(posx - posx2) == 0) || (abs(posy - posy2) ==0 )) && (array[posy][posx] == 0 || array[posy][posx] == 11))
	{
		return true;
	}else
	{
		return false;
	}
}

bool validarPeon(char* coord, int turno, int** array)
{
	int posx = coorX(coord);
	int posy = coorY(coord);
	int posx2 = coorX2(coord);
	int posy2 = coorY2(coord);
	if (turno == 1)
	{
		if (posy == 1)
		{
			if ( ( abs(posx - posx2) == 0) && ( (posy2 - posy) == 2 || (posy2 - posy) == 1) && (array[posy2][posx2] == 13) && (array[posy][posx] == 5 ) )
			{
				return true;
			}
			else if ( (posy2 == (posy + 1)) && (abs(posx - posx2) == 1) && (piezaComePieza(coord, turno, array)) && ( array[posy][posx] == 5 ) )
			{
				return true;
			}
			else
			{
				return false;
			}
		}else if (posy != 1)
		{
			if ( ( abs(posx - posx2) == 0) && ( (posy2 - posy) == 1) &&(array[posy2][posx2] == 13) && ( array[posy][posx] == 5 ))
			{
				return true;
			}
			else if ( (posy2 == (posy + 1)) && (abs(posx - posx2) == 1) && (piezaComePieza(coord, turno, array)) && ( array[posy][posx] == 5 ))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else 
		{

			return false;
		}
	}
	else if (turno == 2)
	{
		if (posy == 6)
		{
			if  ( (abs(posx - posx2) == 0) && ((posy2 - posy) == 2 || (posy2 - posy2 == 1)) && (array[posy2][posx2] == 13) && (array[posy][posx] == 12 ) )
			{
				return true;
			}
			if ( (posy == (posy2 - 1) ) && (abs(posx - posx2) == 1) && (array[posy][posx] == 12) && (piezaComePieza(coord, turno, array)) )
			{
				return true;
			}
			else
			{
				return false;
			}
		}else if (posy != 6)
		{
			if ( ( abs(posx - posx2) == 0) && ( (posy - posy2) == 1) && (array[posy2][posx2] == 13) && (array[posy][posx] == 12 ) )
			{
				return true;
			}
			if ( (posy == (posy2 - 1) ) && (abs(posx - posx2) == 1) && (array[posy][posx] == 12) && (piezaComePieza(coord, turno, array)) )
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;	
		}
	}	
}

bool piezaComePieza(char* coord, int turno, int** array)
{
	int posx2 = coorX2(coord);
	int posy2 = coorY2(coord);
	if (turno == 1)
	{
		if (array[posy2][posx2]  == 7 || array[posy2][posx2]  == 8 || array[posy2][posx2]  == 9 || array[posy2][posx2]  == 10 || array[posy2][posx2]  == 11 || array[posy2][posx2]  == 12)
		{
			return true;
		}else
		{
			return false;
		}
	}else if (turno == 2)
	{
		if (array[posy2][posx2]  == 0 || array[posy2][posx2]  == 1 || array[posy2][posx2]  == 2 || array[posy2][posx2]  == 3 || array[posy2][posx2]  == 4 || array[posy2][posx2]  == 5)
		{
			return true;
		}else
		{
			return false;
		}
	}
}

bool pasoLibre(char* coord, int turno, int** array)
{
	int posx = coorX(coord);
	int posy = coorY(coord);
	int posx2 = coorX2(coord);
	int posy2 = coorY2(coord);
	int diffX = abs(posx - posx2);
	int diffY = abs(posy - posy2);
	if (validarTorre(coord, array))
	{
		if (diffX == 0)
		{
			if (posy < posy2)//vertical  AR-AB
			{
				for (int i = (posy+1) ; i < posy2; ++i)
				{
					if (array[i][posx] != 13)
					{
						return false;
						break;
					}
					else
					{
						return true;
					}
				}
			}
			else if (posy > posy2)//vertical  AB-AR
			{
				for (int i = (posy2+1) ; i < posy; --i)
				{
					if (array[i][posx] != 13)
					{
						return false;
						break;
					}
					else
					{
						return true;
					}
				}
			}
		}
		else if (diffY == 0)
		{
			if (posx < posx2)
			{
				for (int i = (posx+1) ; i < posx2; ++i)//Hor DER-IZQ
				{
					if (array[posy][i] != 13)
					{
						return false;
						break;
					}
					else
					{
						return true;
					}
				}
			}
			else if (posx > posx2)
			{
				for (int i = (posx2+1) ; i < posx; --i)//Hor DER-IZQ
				{
					if (array[posy][i] != 13)
					{
						return false;
						break;
					}
					else
					{
						return true;
					}
				}
			}
		}
	}
	else if(validarAlfil(coord, array))
	{
		for (int i = (posy+1); i < posy2; ++i)
		{
			for (int j = (posx+1); j <= (i+1); ++j)
			{
				if (array[i][j] != 13)
				{
					return false;
					break;
				}
				else
				{
					return true;
				}
			}
		}
	}
	else if (validarCab(coord, array))
	{
		if (piezaComePieza(coord, turno, array))
		{
			return true;
		}
		else if(array[posy2][posx2] == 13)
		{
			return true;
		}
		else
		{
			return true;
		}
	}
	else if (validarRey(coord, array))
	{
		if (piezaComePieza(coord, turno, array))
		{
			return true;
		}
		else if(array[posy2][posx2] == 13)
		{
			return true;
		}
		else 
		{
			return false;
		}
	}
	else if (validarReina(coord, array))
	{
		if (diffX == 0)
		{
			for (int i = (posy+1) ; i < posy2; ++i)
			{
				if (array[i][posx] != 13)
				{
					return false;
					break;
				}
				else
				{
					return true;
				}
			}
		}
		else if (diffY == 0)
		{
			for (int i = (posx+1) ; i < posx2; ++i)
			{
				if (array[posy][i] != 13)
				{
					return false;
					break;
				}
				else
				{
					return true;
				}
			}
		}
	}
	else if (validarPeon(coord, turno, array))
	{
		return true;
	}
	else
	{
		return false;
	}
}