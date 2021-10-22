#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<cstdlib>
#include<time.h>
#include<stdio.h>

extern "C" {
#include"../template-project-2/SDL2-2.0.10/include/SDL.h"
#include"../template-project-2/SDL2-2.0.10/include/SDL_main.h"
}

#define SCREEN_WIDTH	760
#define SCREEN_HEIGHT	640
#define TIME 50
#define mnoznikPredkosci 1


// narysowanie napisu txt na powierzchni screen, zaczynaj¹c od punktu (x, y)
// charset to bitmapa 128x128 zawieraj¹ca znaki
void DrawString(SDL_Surface *screen, int x, int y, const char *text,
                SDL_Surface *charset) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while(*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
		};
	};


// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt œrodka obrazka sprite na ekranie
void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
	};


// rysowanie pojedynczego pixela
// draw a single pixel
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32 *)p = color;
	};


// rysowanie linii o d³ugoœci l w pionie (gdy dx = 0, dy = 1) 
// b¹dŸ poziomie (gdy dx = 1, dy = 0)
// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for(int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
		};
	};


// rysowanie prostok¹ta o d³ugoœci boków l i k
// draw a rectangle of size l by k
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k,
                   Uint32 outlineColor, Uint32 fillColor) {
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for(i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
	};


void resetFrog(double& positionX, double& positionY, double& worldTime, int& highest_pos)
{
	positionX = SCREEN_WIDTH / 2;
	positionY = SCREEN_HEIGHT - 60;
	highest_pos = SCREEN_HEIGHT - 60;
	worldTime = 0;
}


void death(double &positionX, double & positionY, int &zycia , double & worldTime,int & highest_pos,int &taken) {
	if(taken == 1)
	taken = 2;
	resetFrog(positionX, positionY, worldTime,highest_pos);
	zycia--;
}


int ifOutOfScreen(int positionOnScreen) {
	if (positionOnScreen > 1200)
		positionOnScreen = positionOnScreen % 1320 - 120;
	else
		if (positionOnScreen < -320)
			positionOnScreen = (positionOnScreen %1320)+1200 ;
	return positionOnScreen;
}


void HitCar1(double carPositionX, double carPositionY, double &positionX, double &positionY, int &zycia , double& worldTime, int& highest_pos, int & taken)
{
	if ((carPositionX -35 < positionX +10) && (carPositionX + 35 > positionX - 10)&&(carPositionY == positionY ))
	{
		death(positionX, positionY, zycia, worldTime, highest_pos, taken);
	}
}
void HitCar2(double carPositionX, double carPositionY, double& positionX, double& positionY, int& zycia, double& worldTime, int& highest_pos, int& taken)
{
	if ((carPositionX - 27 < positionX + 10) && (carPositionX + 27 > positionX - 10) && (carPositionY == positionY))
	{
		death(positionX, positionY, zycia, worldTime, highest_pos, taken);
	}
}
void HitCar3(double carPositionX, double carPositionY, double& positionX, double& positionY, int& zycia, double& worldTime, int& highest_pos, int& taken)
{
	if ((carPositionX - 65 < positionX + 10) && (carPositionX + 65 > positionX - 10) && (carPositionY == positionY))
	{
		death(positionX, positionY, zycia, worldTime, highest_pos, taken);
	}
}
void HitCar4(double carPositionX, double carPositionY, double& positionX, double& positionY, int& zycia, double& worldTime, int& highest_pos, int& taken)
{
	if ((carPositionX - 28 < positionX + 10) && (carPositionX + 28 > positionX - 10) && (carPositionY == positionY))
	{
		death(positionX, positionY, zycia, worldTime, highest_pos, taken);
	}
}
void HitCar5(double carPositionX, double carPositionY, double& positionX, double& positionY, int& zycia, double& worldTime, int& highest_pos, int& taken)
{
	if ((carPositionX - 40 < positionX + 10) && (carPositionX + 40 > positionX - 10) && (carPositionY == positionY))
	{
		death(positionX, positionY, zycia, worldTime, highest_pos, taken);
	}
}


void HitLog(double logPositionX, double logPositionY, double &positionX, double &positionY, double speed,bool &up,bool&pause)
{
	if ((logPositionX - 40 <= positionX + 20) && (logPositionX + 40 >= positionX - 20)&&(logPositionY == positionY -4 )&&(pause==1))
	{
		positionX = positionX + speed * mnoznikPredkosci;
		positionY = positionY;
		up = 1;
	}
}


void HitTurtle(double logPositionX, double logPositionY, double& positionX, double& positionY, double speed, bool &up, bool& pause)
{
	if ((logPositionX - 40 <= positionX + 20) && (logPositionX + 40 >= positionX - 20) && (logPositionY == positionY - 4)&&(pause==1))
	{
		positionX = positionX + speed*mnoznikPredkosci;
		positionY = positionY;
		up = 1;
	}
}


void Water(double& positionX, double& positionY, bool &up, int& zycia, double& worldTime, bool& pause, int& highest_pos, int& taken)
{
	if ((positionY > 136) && (positionY < 301) && (up == 0)&&(pause==1))
	{
		death(positionX, positionY, zycia, worldTime, highest_pos, taken);
	}
}


void PosWin(bool position[], double& positionX, double &positionY ,int& zycia, double& worldTime, int &wynik, int& highest_pos, int& bee_pos, bool &bee_picked, int &taken, int &bonus)
{
	for (int i = 0; i < 5; i++)
	{
		if ((positionY == 100) && (positionX > (i*165+20)) && (positionX < (i * 165+80))) {
			if (position[i] == 1) {
				death(positionX, positionY, zycia, worldTime, highest_pos, taken);
			}
			else {
				if (bee_pos == i)
				{
					if (bee_picked == 0)
					{
						bee_picked = 1;
						wynik = wynik + 200;
						bonus++;
					}
				}
				if (taken == 1)
				{
					taken = 2;
					wynik = wynik + 200;
					bonus++;
				}
				position[i] = 1;
				wynik = wynik + 50;
				wynik = wynik + (int(TIME - worldTime) * 10);
				resetFrog(positionX, positionY, worldTime, highest_pos);
			}
		}
	}
	if (positionY == 100)
	{
		death(positionX, positionY, zycia, worldTime, highest_pos, taken);
	}
}


void PosWinDraw(bool pos[], SDL_Surface* screen, SDL_Surface* sprite)
{
	for (int i = 0; i < 5; i++)
	{
		if (pos[i] == 1)
		{
			DrawSurface(screen, sprite, 50 +(165*i), 100);
		}
		
	}
}


void gameOver(SDL_Surface* screen, SDL_Surface* eti,int &czarny, int& zielony, SDL_Surface* logo, int& restart, int &wynik)
{
	DrawSurface(screen, logo,380, 280);
	restart = 0;
}


void gameWon(SDL_Surface* screen, int& czarny, int& zielony, SDL_Surface* logo, int& restart, bool& pause, int& menu, int &wynik, int result[])
{
	DrawRectangle(screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT-40, zielony, czarny);
	DrawSurface(screen, logo, SCREEN_WIDTH/2, 280);
	if(wynik>result[9])
	{
		menu = 5;
		pause = 0;
	}
	else
	{
		menu = 1;
		pause = 0;
		restart = 0;
	}
}


void ileZyc(int zycia, SDL_Surface* screen, SDL_Surface* eti,int& czarny, int& zielony, bool &pause ,int &menu, SDL_Surface*logo,int &restart,int& wynik)
{
	for (int i = 1; i <= zycia; i++)
	{
		DrawSurface(screen, eti, 24+40*(i-1), 22);
	}
	if (zycia == 0)
	{
		menu = 1;
			pause = 0;

		gameOver(screen,eti,czarny,zielony,logo,restart,wynik);
	}
}


void start(SDL_Surface* screen, SDL_Surface* eti, int& czarny, int& zielony, SDL_Surface* logo, int&menu)
{
	DrawRectangle(screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT-40, zielony, czarny);
	DrawSurface(screen, logo, 490, SCREEN_HEIGHT/2);
}


void doYouWantToQuit(SDL_Surface* screen, SDL_Surface* slajd1, SDL_Surface* slajd2, SDL_Surface* slajd3, int& restart, int& ifQuit, int& menu, int val )
{
	if(val==1)
		DrawSurface(screen, slajd2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	if(val==2)
		DrawSurface(screen, slajd3, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		menu=2;
}


void zabapkt(int& highest_pos, int& wynik)
{
	if (highest_pos == 100) {
		highest_pos = 580;
	}
}


void minizaba(int& taken,int positionX,int positionY, SDL_Surface *screen, SDL_Surface *babyzaba,double pos[],int frog_pos)
{
	if (taken == 0)
	{
		DrawSurface(screen, babyzaba, ifOutOfScreen(pos[3] + 580 + frog_pos), 256);
		if (positionX + 30 >= ifOutOfScreen(pos[3] + 580+frog_pos) && positionX - 30 <= ifOutOfScreen(pos[3] + 580+frog_pos) && positionY == 260)
		{
			taken = 1;
		}

	}
	else
	if (taken == 1)
	{
		DrawSurface(screen, babyzaba, positionX, positionY);
	}
}


void highscoreLoad(FILE* plik,int result[],char name[10][4])
{
	for (int i = 0; i < 10; i++)
	{
		fscanf(plik, "%d", &result[i]);
		fscanf(plik, "%s", &name[i]);
	}
}


void LepszyWynik(FILE* plik, int result[10], char name[10][4],int wynik, char user[4])
{
	for (int i = 0; i < 10; i++)
	{
		if (result[i] < wynik)
		{
			for (int j =9; j >= i; j--)
			{
				result[j] = result[j-1];
				for (int k = 0; k < 4; k++)
				{
					name[j][k] = name[j - 1][k];
				}
			}
			result[i] = wynik;
			for (int k = 0; k < 4; k++)
			{
				name[i][k] = user[k];
			}
			break;

		}
	}
	fclose(plik);
	fopen("wyniki.txt", "w+");
	for (int i = 0; i < 10; i++)
	{
		fprintf(plik, "%d", result[i]);
		fprintf(plik, " %s \n", &name[i]);
	}
}

void ifNotLoaded(SDL_Surface *screen, SDL_Texture* scrtex, SDL_Window* window, SDL_Renderer* renderer )
{
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

// main
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char **argv) {

	FILE* plik;
	int t1, t2, quit, frames, rc, zycia = 3, menu = 0, restart = 0, ifQuit = 0, val = 1, start = 1, wynik = 0, highest_pos = 580, bee_pos, taken = 0, bonus = 0, NumberOfChar = 0;
	double delta, worldTime, fpsTimer, fps, distance, etiSpeed, pos[10] = {}, positionX, positionY ,temp,frog_pos;
	bool up = 0, pause = 1, bee_picked = 0;
	bool position[5] = {};
	char user[4] = "";
	int result[10];
	char name[10][4];
	SDL_Event event;
	SDL_Surface *screen, *charset;
	SDL_Surface *eti,*froggi, * autoThree, * autoFour, * autoFive, * autoSix, * slajdOne, * slajdTwo, * slajdThree, *bee, *zolwNurek, *babyzaba;
	SDL_Surface *kloda, *zolw, *autoOne, *autoTwo, *meta , *zaba2, *jakubpauza, *logo, *youWon;
	SDL_Texture *scrtex;
	SDL_Window *window;
	SDL_Renderer *renderer;

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
		}

	// tryb pe³noekranowy / fullscreen mode
	//rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP,
	  //                               &window, &renderer);
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
	                                 &window, &renderer);
	if(rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
		};
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Frogger");

	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
	                              0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
	                           SDL_TEXTUREACCESS_STREAMING,
	                           SCREEN_WIDTH, SCREEN_HEIGHT);

	// wy³¹czenie widocznoœci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);

	// wczytanie obrazka cs8x8.bmp
	charset = SDL_LoadBMP("../template-project-2/bmp/cs8x8.bmp");
	if (charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		ifNotLoaded(screen, scrtex, window, renderer);
		return 1;
	};

	SDL_SetColorKey(charset, true, 0x000000);

	eti = SDL_LoadBMP("../template-project-2/bmp/eti.bmp");	if (eti == NULL) {
		printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(eti);
		ifNotLoaded(screen, scrtex, window, renderer);
		return 1;
	};

	zaba2 = SDL_LoadBMP("../template-project-2/bmp/zaba2.bmp");
	if (zaba2 == NULL) {
		printf("SDL_LoadBMP(zaba2.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(zaba2);
		ifNotLoaded(screen, scrtex, window, renderer);
		return 1;
	};

	kloda = SDL_LoadBMP("../template-project-2/bmp/log.bmp");
	if (kloda == NULL) {
		printf("SDL_LoadBMP(log.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(kloda);
		ifNotLoaded(screen, scrtex, window, renderer);
		return 1;
	};

	zolw = SDL_LoadBMP("../template-project-2/bmp/zolw.bmp");
	if (zolw == NULL) {
		printf("SDL_LoadBMP(zolw.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(zolw);
		ifNotLoaded(screen, scrtex, window, renderer);
		return 1;
	};

	autoOne = SDL_LoadBMP("../template-project-2/bmp/auto.bmp");
	if (autoOne == NULL) {
		printf("SDL_LoadBMP(auto.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(autoOne);
		ifNotLoaded(screen, scrtex, window, renderer);
		return 1;
	};

	autoThree = SDL_LoadBMP("../template-project-2/bmp/car3.bmp");
	if (autoThree == NULL) {
		printf("SDL_LoadBMP(car3.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(autoThree);
		ifNotLoaded(screen, scrtex, window, renderer);
		return 1;
	};

	autoFour = SDL_LoadBMP("../template-project-2/bmp/car4.bmp");
	if (autoFour == NULL) {
		printf("SDL_LoadBMP(car4.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(autoFour);
		ifNotLoaded(screen, scrtex, window, renderer);	
		return 1;
	};

	autoFive = SDL_LoadBMP("../template-project-2/bmp/car5.bmp");
	if (autoFive == NULL) {
		printf("SDL_LoadBMP(car5.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(autoFive);
		ifNotLoaded(screen, scrtex, window, renderer);
		return 1;
	};

	autoSix = SDL_LoadBMP("../template-project-2/bmp/car7.bmp");
	if (autoSix == NULL) {
		printf("SDL_LoadBMP(car7.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(autoSix);
		ifNotLoaded(screen, scrtex, window, renderer);
		return 1;
	};

	meta = SDL_LoadBMP("../template-project-2/bmp/finish.bmp");
	if (meta == NULL) {
		printf("SDL_LoadBMP(finish.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(meta);
		ifNotLoaded(screen, scrtex, window, renderer);
		return 1;
	};

	jakubpauza = SDL_LoadBMP("../template-project-2/bmp/gamepaused.bmp");
	if (jakubpauza == NULL) {
		printf("SDL_LoadBMP(gamepaused.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(jakubpauza);
		ifNotLoaded(screen, scrtex, window, renderer);
		return 1;
	};

	logo = SDL_LoadBMP("../template-project-2/bmp/gameover.bmp");
	if (logo == NULL) {
		printf("SDL_LoadBMP(gameover.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(logo);
		ifNotLoaded(screen, scrtex, window, renderer);
		return 1;
	};

	youWon = SDL_LoadBMP("../template-project-2/bmp/youWin.bmp");
	if (youWon == NULL) {
		printf("SDL_LoadBMP(youWin.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(youWon);
		ifNotLoaded(screen, scrtex, window, renderer);
		return 1;
	};

	slajdOne = SDL_LoadBMP("../template-project-2/bmp/slajd1.bmp");
	if (slajdOne == NULL) {
		printf("SDL_LoadBMP(slajd1.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(slajdOne);
		ifNotLoaded(screen, scrtex, window, renderer);
		return 1;
	};

	slajdTwo = SDL_LoadBMP("../template-project-2/bmp/slajd2.bmp");
	if (slajdTwo == NULL) {
		printf("SDL_LoadBMP(slajd2.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(slajdTwo);
		ifNotLoaded(screen, scrtex, window, renderer);
		return 1;
	};

	slajdThree = SDL_LoadBMP("../template-project-2/bmp/slajd3.bmp");
	if (slajdThree == NULL) {
		printf("SDL_LoadBMP(slajd3.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(slajdThree);
		ifNotLoaded(screen, scrtex, window, renderer);
		return 1;
	};

	froggi = SDL_LoadBMP("../template-project-2/bmp/start.bmp");
	if (froggi == NULL) {
		printf("SDL_LoadBMP(start.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(froggi);
		ifNotLoaded(screen, scrtex, window, renderer);
		return 1;
	};

	bee = SDL_LoadBMP("../template-project-2/bmp/bee.bmp");
	if (bee == NULL) {
		printf("SDL_LoadBMP(bee.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(bee);
		ifNotLoaded(screen, scrtex, window, renderer);
		return 1;
	};

	zolwNurek = SDL_LoadBMP("../template-project-2/bmp/zolwPodWoda.bmp");
	if (zolwNurek == NULL) {
		printf("SDL_LoadBMP(zolwPodWoda.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(zolwNurek);
		ifNotLoaded(screen, scrtex, window, renderer);
		return 1;
	};

	babyzaba = SDL_LoadBMP("../template-project-2/bmp/froggie.bmp");
	if (babyzaba == NULL) {
		printf("SDL_LoadBMP(froggie.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(babyzaba);
		ifNotLoaded(screen, scrtex, window, renderer);
		return 1;
	};


	char text[128];
	int czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int fioletowy = SDL_MapRGB(screen->format, 0x8A, 0x2B, 0xE2);
	int szary = SDL_MapRGB(screen->format, 0x80, 0x80, 0x80);
	int czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);

	//wczytywanie pliku
	plik = fopen("wyniki.txt", "a+");
	highscoreLoad(plik, result, name);

	//losowanie pozycji dla pszczo³y oraz ¿aby
	srand(time(NULL));
	bee_pos = rand()%5;
	frog_pos = rand() % 60;

	t1 = SDL_GetTicks();

	frames = 0;
	fpsTimer = 0;
	fps = 0;
	quit = 0;
	worldTime = 0;
	distance = 0;
	etiSpeed = 1;
	positionX = SCREEN_WIDTH / 2;
	positionY = SCREEN_HEIGHT - 60;

	while (!quit) {


		//restart zmiennych
		if (restart == 1)
		{
			zycia = 3, menu = 0, restart = 0,start=0, wynik=0;
			positionX, positionY,  temp;
			up = 0, pause = 1;
			bee_pos = rand() % 5;
			frames = 0;
			fpsTimer = 0;
			fps = 0;
			quit = 0;
			bee_picked = 0;
			taken = 0;
			NumberOfChar = 0;
			worldTime = 0;
			distance = 0;
			etiSpeed = 1;
			positionX = SCREEN_WIDTH / 2;
			positionY = SCREEN_HEIGHT - 60;
			for (int i = 0; i < 5; i++)
			{
				position[i]=0;
			}

			restart = 0;
		}

		t2 = SDL_GetTicks();

		// w tym momencie t2-t1 to czas w milisekundach,
		// jaki uplyna³ od ostatniego narysowania ekranu
		// delta to ten sam czas w sekundach
		// here t2-t1 is the time in milliseconds since
		// the last screen was drawn
		// delta is the same time in seconds
		delta = (t2 - t1) * 0.001;
		t1 = t2;


		if (pause == 0)
		{
			delta = 0;
		}

		worldTime += delta;

		SDL_FillRect(screen, NULL, czarny);

		//Rysowanie Planszy
		DrawRectangle(screen, 0, 42, SCREEN_WIDTH, 78, zielony, zielony);
		DrawSurface(screen, meta, 500, 92);
		DrawRectangle(screen, 0, 120, SCREEN_WIDTH, 200, niebieski, niebieski);
		DrawRectangle(screen, 0, 320, SCREEN_WIDTH, 40, fioletowy, fioletowy);
		DrawRectangle(screen, 0, 360, SCREEN_WIDTH, 200, szary, szary);
		DrawRectangle(screen, 0, 560, SCREEN_WIDTH, 40, fioletowy, fioletowy);

		//rysowanie k³ód i ¿ó³wi, sprawdzanie hitboxów k³ód i ¿ó³wi
		DrawSurface(screen, kloda, ifOutOfScreen(pos[0]), 136);
		HitLog(ifOutOfScreen(pos[0]), 136, positionX, positionY, 0.5, up, pause);
		DrawSurface(screen, kloda, ifOutOfScreen(pos[0] + 200), 136);
		HitLog(ifOutOfScreen(pos[0] + 200), 136, positionX, positionY, 0.5, up, pause);
		DrawSurface(screen, kloda, ifOutOfScreen(pos[0] + 420), 136);
		HitLog(ifOutOfScreen(pos[0] + 420), 136, positionX, positionY, 0.5, up, pause);
		DrawSurface(screen, kloda, ifOutOfScreen(pos[0] + 760), 136);
		HitLog(ifOutOfScreen(pos[0] + 760), 136, positionX, positionY, 0.5, up, pause);
		DrawSurface(screen, kloda, ifOutOfScreen(pos[0] + 960), 136);
		HitLog(ifOutOfScreen(pos[0] + 960), 136, positionX, positionY, 0.5, up, pause);

		if (ifOutOfScreen(pos[1]) >= 500 && ifOutOfScreen(pos[1]) <= 600|| ifOutOfScreen(pos[1]) >= 200 && ifOutOfScreen(pos[1]) <= 300) {  //nurkuj¹cy ¿ó³w
			DrawSurface(screen, zolwNurek, ifOutOfScreen(pos[1]), 176);
			HitTurtle(ifOutOfScreen(pos[1]), 176, positionX, positionY, -0.7, up, pause);
		}
		else if (ifOutOfScreen(pos[1]) > 300 && ifOutOfScreen(pos[1]) < 500 ) {
		}
		else
		{
			DrawSurface(screen, zolw, ifOutOfScreen(pos[1]), 176);
			HitTurtle(ifOutOfScreen(pos[1]), 176, positionX, positionY, -0.7, up, pause);
		}
		DrawSurface(screen, zolw, ifOutOfScreen(pos[1] + 240), 176);
		HitTurtle(ifOutOfScreen(pos[1] + 240), 176, positionX, positionY, -0.7, up, pause);
		DrawSurface(screen, zolw, ifOutOfScreen(pos[1] + 440), 176);
		HitTurtle(ifOutOfScreen(pos[1] + 440), 176, positionX, positionY, -0.7, up, pause);
		if (ifOutOfScreen(pos[1] + 720) >= 600 && ifOutOfScreen(pos[1] + 720) <= 700 || ifOutOfScreen(pos[1] + 720) >= 300 && ifOutOfScreen(pos[1] + 720) <= 400) {//nurkuj¹cy ¿ó³w
			DrawSurface(screen, zolwNurek, ifOutOfScreen(pos[1] + 720), 176);
			HitTurtle(ifOutOfScreen(pos[1] + 720), 176, positionX, positionY, -0.7, up, pause);
		}
		else if (ifOutOfScreen(pos[1] + 720) > 400 && ifOutOfScreen(pos[1] + 720) < 600) {
		}
		else
		{
			DrawSurface(screen, zolw, ifOutOfScreen(pos[1] + 720), 176);
			HitTurtle(ifOutOfScreen(pos[1] + 720), 176, positionX, positionY, -0.7, up, pause);
		}
		DrawSurface(screen, zolw, ifOutOfScreen(pos[1] + 960), 176);
		HitTurtle(ifOutOfScreen(pos[1] + 960), 176, positionX, positionY, -0.7, up, pause);

		DrawSurface(screen, kloda, ifOutOfScreen(pos[2]), 216);
		HitLog(ifOutOfScreen(pos[2]), 216, positionX, positionY, 1.3, up, pause);
		DrawSurface(screen, kloda, ifOutOfScreen(pos[2] + 300), 216);
		HitLog(ifOutOfScreen(pos[2] + 300), 216, positionX, positionY, 1.3, up, pause);
		DrawSurface(screen, kloda, ifOutOfScreen(pos[2] + 600), 216);
		HitLog(ifOutOfScreen(pos[2] + 600), 216, positionX, positionY, 1.3, up, pause);
		DrawSurface(screen, kloda, ifOutOfScreen(pos[2] + 850), 216);
		HitLog(ifOutOfScreen(pos[2] + 850), 216, positionX, positionY, 1.3, up, pause);
		DrawSurface(screen, kloda, ifOutOfScreen(pos[2] + 1050), 216);
		HitLog(ifOutOfScreen(pos[2] + 1050), 216, positionX, positionY, 1.3, up, pause);

		DrawSurface(screen, kloda, ifOutOfScreen(pos[3]), 256);
		HitLog(ifOutOfScreen(pos[3]), 256, positionX, positionY, 0.6, up, pause);
		DrawSurface(screen, kloda, ifOutOfScreen(pos[3] + 160), 256);
		HitLog(ifOutOfScreen(pos[3] + 160), 256, positionX, positionY, 0.6, up, pause);
		DrawSurface(screen, kloda, ifOutOfScreen(pos[3] + 320), 256);
		HitLog(ifOutOfScreen(pos[3] + 320), 256, positionX, positionY, 0.6, up, pause);
		DrawSurface(screen, kloda, ifOutOfScreen(pos[3] + 600), 256);
		HitLog(ifOutOfScreen(pos[3] + 600), 256, positionX, positionY, 0.6, up, pause); 
		DrawSurface(screen, kloda, ifOutOfScreen(pos[3] + 760), 256);
		HitLog(ifOutOfScreen(pos[3] + 760), 256, positionX, positionY, 0.6, up, pause);
		DrawSurface(screen, kloda, ifOutOfScreen(pos[3] + 920), 256);
		HitLog(ifOutOfScreen(pos[3] + 920), 256, positionX, positionY, 0.6, up, pause);


		if (ifOutOfScreen(pos[4]) >= 500 && ifOutOfScreen(pos[4]) <= 600 || ifOutOfScreen(pos[4]) >= 200 && ifOutOfScreen(pos[4]) <= 300) { //nurkuj¹cy ¿ó³w
			DrawSurface(screen, zolwNurek, ifOutOfScreen(pos[4]), 296);
			HitTurtle(ifOutOfScreen(pos[4]), 296, positionX, positionY, -0.3, up, pause); 
		}
		else if (ifOutOfScreen(pos[4]) > 300 && ifOutOfScreen(pos[4]) < 500) {}
		else
		{
			DrawSurface(screen, zolw, ifOutOfScreen(pos[4]), 296);
			HitTurtle(ifOutOfScreen(pos[4]), 296, positionX, positionY, -0.3, up, pause);
		}
		DrawSurface(screen, zolw, ifOutOfScreen(pos[4] + 200), 296);
		HitTurtle(ifOutOfScreen(pos[4] + 200), 296, positionX, positionY, -0.3, up, pause);
		DrawSurface(screen, zolw, ifOutOfScreen(pos[4] + 400), 296);
		HitTurtle(ifOutOfScreen(pos[4] + 400), 296, positionX, positionY, -0.3, up, pause);
		if (ifOutOfScreen(pos[4] + 700) >= 700 && ifOutOfScreen(pos[4] + 700) <= 800 || ifOutOfScreen(pos[4] + 700) >= 400 && ifOutOfScreen(pos[4] + 700) <= 500) { //nurkuj¹cy ¿ó³w
			DrawSurface(screen, zolwNurek, ifOutOfScreen(pos[4] + 700), 296);
			HitTurtle(ifOutOfScreen(pos[4] + 700), 296, positionX, positionY, -0.3, up, pause);
		}
		else if (ifOutOfScreen(pos[4] + 700) > 500 && ifOutOfScreen(pos[4] + 700) < 700) {
		}
		else
		{
			DrawSurface(screen, zolw, ifOutOfScreen(pos[4] + 700), 296);
			HitTurtle(ifOutOfScreen(pos[4] + 700), 296, positionX, positionY, -0.3, up, pause);
		}
		DrawSurface(screen, zolw, ifOutOfScreen(pos[4] + 900), 296);
		HitTurtle(ifOutOfScreen(pos[4] + 900), 296, positionX, positionY, -0.3, up, pause);


		//rysowanie samochodów, sprawdzanie hitboxów samochodów
		DrawSurface(screen, autoSix, ifOutOfScreen(pos[5]), 380);
		HitCar1(ifOutOfScreen(pos[5]), 380, positionX, positionY, zycia, worldTime, highest_pos, taken);
		DrawSurface(screen, autoSix, ifOutOfScreen(pos[5] + 300), 380);
		HitCar1(ifOutOfScreen(pos[5] + 300), 380, positionX, positionY, zycia, worldTime, highest_pos, taken);
		DrawSurface(screen, autoSix, ifOutOfScreen(pos[5] + 620), 380);
		HitCar1(ifOutOfScreen(pos[5] + 620), 380, positionX, positionY, zycia, worldTime, highest_pos, taken);
		DrawSurface(screen, autoSix, ifOutOfScreen(pos[5] + 950), 380);
		HitCar1(ifOutOfScreen(pos[5] + 950), 380, positionX, positionY, zycia, worldTime, highest_pos, taken);

		DrawSurface(screen, autoThree, ifOutOfScreen(pos[6] + 180), 420);
		HitCar2(ifOutOfScreen(pos[6] + 180), 420, positionX, positionY, zycia, worldTime, highest_pos, taken);
		DrawSurface(screen, autoThree, ifOutOfScreen(pos[6] + 360), 420);
		HitCar2(ifOutOfScreen(pos[6] + 360), 420, positionX, positionY, zycia, worldTime, highest_pos, taken);
		DrawSurface(screen, autoThree, ifOutOfScreen(pos[6] + 610), 420);
		HitCar2(ifOutOfScreen(pos[6] + 610), 420, positionX, positionY, zycia, worldTime, highest_pos, taken);
		DrawSurface(screen, autoThree, ifOutOfScreen(pos[6] + 950), 420);
		HitCar2(ifOutOfScreen(pos[6] + 950), 420, positionX, positionY, zycia, worldTime, highest_pos, taken);
		DrawSurface(screen, autoThree, ifOutOfScreen(pos[6] + 1150), 420);
		HitCar2(ifOutOfScreen(pos[6] + 1150), 420, positionX, positionY, zycia, worldTime, highest_pos, taken);

		DrawSurface(screen, autoFour, ifOutOfScreen(pos[7] + 20), 460);
		HitCar3(ifOutOfScreen(pos[7] + 20), 460, positionX, positionY, zycia, worldTime, highest_pos, taken);
		DrawSurface(screen, autoFour, ifOutOfScreen(pos[7] + 360), 460);
		HitCar3(ifOutOfScreen(pos[7] + 360), 460, positionX, positionY, zycia, worldTime, highest_pos, taken);
		DrawSurface(screen, autoFour, ifOutOfScreen(pos[7] + 780), 460);
		HitCar3(ifOutOfScreen(pos[7] + 780), 460, positionX, positionY, zycia, worldTime, highest_pos, taken);
		DrawSurface(screen, autoFour, ifOutOfScreen(pos[7] + 1000), 460);
		HitCar3(ifOutOfScreen(pos[7] + 1000), 460, positionX, positionY, zycia, worldTime, highest_pos, taken);

		DrawSurface(screen, autoFive, ifOutOfScreen(pos[8]), 500);
		HitCar4(ifOutOfScreen(pos[8]), 500, positionX, positionY, zycia, worldTime, highest_pos, taken);
		DrawSurface(screen, autoFive, ifOutOfScreen(pos[8] + 160), 500);
		HitCar4(ifOutOfScreen(pos[8] + 160), 500, positionX, positionY, zycia, worldTime, highest_pos, taken);
		DrawSurface(screen, autoFive, ifOutOfScreen(pos[8] + 460), 500);
		HitCar4(ifOutOfScreen(pos[8] + 460), 500, positionX, positionY, zycia, worldTime, highest_pos, taken);
		DrawSurface(screen, autoFive, ifOutOfScreen(pos[8] + 740), 500);
		HitCar4(ifOutOfScreen(pos[8] + 740), 500, positionX, positionY, zycia, worldTime, highest_pos, taken);
		DrawSurface(screen, autoFive, ifOutOfScreen(pos[8] + 1060), 500);
		HitCar4(ifOutOfScreen(pos[8] + 1060), 500, positionX, positionY, zycia, worldTime, highest_pos, taken);

		DrawSurface(screen, autoOne, ifOutOfScreen(pos[9]), 540);
		HitCar5(ifOutOfScreen(pos[9]), 540, positionX, positionY, zycia, worldTime, highest_pos, taken);
		DrawSurface(screen, autoOne, ifOutOfScreen(pos[9] + 200), 540);
		HitCar5(ifOutOfScreen(pos[9] + 200), 540, positionX, positionY, zycia, worldTime, highest_pos, taken);
		DrawSurface(screen, autoOne, ifOutOfScreen(pos[9] + 440), 540);
		HitCar5(ifOutOfScreen(pos[9] + 440), 540, positionX, positionY, zycia, worldTime, highest_pos, taken);
		DrawSurface(screen, autoOne, ifOutOfScreen(pos[9] + 920), 540);
		HitCar5(ifOutOfScreen(pos[9] + 920), 540, positionX, positionY, zycia, worldTime, highest_pos, taken);

		//wynik w zale¿noœci od pozycji góra dó³
		if (positionY < highest_pos)
		{
			highest_pos = highest_pos - 40;
			wynik = wynik + 10;
		}

		//sprawdzanie czy ¿aba znajduje siê w wodzie
		Water(positionX, positionY, up, zycia, worldTime, pause, highest_pos, taken);

		up = 0;

		//sprawdzanie czy ¿abka wygra³a
		PosWin(position, positionX, positionY, zycia, worldTime,wynik, highest_pos, bee_pos, bee_picked, taken,bonus);
		//rysowanie ekranu gry z napisem you win !!!
		PosWinDraw(position, screen, zaba2);


		//je¿eli pauza pozycja k³ód,¿ó³wi i samochodów nie zmienia siê, w przeciwnym wypadku zmiana pozycji k³ód, ¿ó³wi , samochodów
		if (pause == 0)
		{
			for (int i = 0; i < 10; i++)
			{
				pos[i] = pos[i];
			}
		}
		else
		{
			pos[0] += 0.5* mnoznikPredkosci;
			pos[1] -= 0.7 * mnoznikPredkosci;
			pos[2] += 1.3 * mnoznikPredkosci;
			pos[3] += 0.6 * mnoznikPredkosci;
			pos[4] -= 0.3 * mnoznikPredkosci;
			pos[5] += 0.8 * mnoznikPredkosci;
			pos[6] -= 1 * mnoznikPredkosci;
			pos[7] += 0.9 * mnoznikPredkosci;
			pos[8] -= 0.4 * mnoznikPredkosci;
			pos[9] += 1.1 * mnoznikPredkosci;
		}
		//rysowanie pszczo³y
		if (bee_picked == 0) {
			DrawSurface(screen, bee, 50 + (165 * bee_pos), 90);
		}

		//je¿eli wyjdzie za ekran
		DrawSurface(screen, eti, positionX, positionY);
		if ((positionX < -10) || (positionX > 770) || (positionY < 100) || (positionY > 600))
		{
			death(positionX, positionY, zycia, worldTime, highest_pos, taken);
		}

		//rysowanie minizaby
		minizaba(taken, positionX, positionY, screen, babyzaba, pos, frog_pos);

		//licznik FPS
		fpsTimer += delta;
		if (fpsTimer > 0.5) {
			fps = frames * 2;
			frames = 0;
			fpsTimer -= 0.5;
		};

		// FPS oraz górny prostok¹t
		DrawRectangle(screen, 0, 1, SCREEN_WIDTH, 38, czerwony, niebieski);
		sprintf(text, "Frogger, %.0lf klatek / s", fps);
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);

		//instrukcja do gry
		sprintf(text, "Q - Exit , P-Pause , \030 \031 \032 \033 - Move");
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);

		//dolna czêœæ informacyjna planszy(czas,wynik)
		DrawRectangle(screen, 760, 600, SCREEN_WIDTH, 38, czerwony, niebieski);
		sprintf(text, "Time : %.1lf s", TIME - worldTime);
		DrawString(screen, 640, 616, text, charset);
		sprintf(text, "Score: %d", wynik);
		DrawString(screen, 12, 616, text, charset);
		temp = 484 - (484 / (50 / (TIME - worldTime)));
		if (TIME - worldTime < 10) {													//zmiana koloru paska czasu w zale¿noœci od czasu
			DrawRectangle(screen, 124 + temp, 610, 484 - temp, 20, czerwony, czerwony);
			if (TIME - worldTime <= 0)
				death(positionX, positionY, zycia, worldTime, highest_pos, taken);
		}
		else
		{
			DrawRectangle(screen, 124 + temp, 610, 484 - temp, 20, zielony, zielony);
		}

		//rysowany napisu pauzy
		if ((pause == 0) && (menu == 0))
			DrawSurface(screen, jakubpauza, SCREEN_WIDTH/2, 330);

		//Sprawdzanie ile ¿yæ ma gracz
		ileZyc(zycia, screen, eti, czarny, zielony, pause, menu, logo, restart,wynik);

		//sprawdzanie czy 5 miejsc zosta³o odwiedzonych przez froggera
		int iffive = 0;
		for (int i = 0; i < 5; i++)
		{
			iffive = iffive + position[i];
		}

		//menu opuszczenia gry po wciœniêciu q
		if (ifQuit == 1) {
			doYouWantToQuit(screen, slajdOne, slajdTwo, slajdThree, restart, ifQuit, menu,val);
		}

		//Czy gra zosta³a wygrana
		if (iffive == 5) {
			gameWon(screen, czarny, zielony, youWon, restart, pause, menu, wynik,result);
		}

		//rysowanie menu g³ównego
		if (start == 1) {
			pause = 0;
			menu = 3;
			DrawRectangle(screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, zielony, fioletowy);
			DrawSurface(screen, froggi, 380, 320);
			sprintf(text, "H - Highscore, 1-Start Game, ESC-Quit");
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 540, text, charset);
		}
		else if (start == 2)
		{
			menu = 4;
			pause = 0;
			DrawRectangle(screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, czarny, niebieski);
		}

		//rysowanie planszy highscore
		if ((menu == 4)|| (menu == 5))
		{
			DrawRectangle(screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, czarny, niebieski);
			sprintf(text, "HIGHSCORES !!!");
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
			for (int i = 0; i < 10; i++)
			{
				sprintf(text, "%d. %s %d", i + 1, name[i], result[i]);
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 120 + (20 * i), text, charset);
			}
			if ((wynik > result[9])&&(menu==5)) {

				sprintf(text, "WYNIK W TOP 10");
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 340, text, charset);
				sprintf(text, "Podaj nickname(3 znaki) :");
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 380, text, charset);
				sprintf(text, "%s", user);
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 420, text, charset);
				sprintf(text, "Press Space to submit");
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 500, text, charset);
				sprintf(text, "twoj wynik to : %d ", wynik);
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 460, text, charset);
			}
			else if (menu == 4)
			{
				sprintf(text, "Press F to return");
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 500, text, charset);
			}
		}


		zabapkt(highest_pos, wynik);

		//wyœwietlanie bonusów za ¿abkê oraz pszczó³kê
		if (bonus > 0)
		{
			DrawRectangle(screen, 320, 40, 120, 80, zielony, fioletowy);
			sprintf(text, "Bonus %d !!!",bonus*200);
			DrawString(screen, 328, 75, text, charset);
			if ((TIME - worldTime) < 48)
				bonus = 0;
		}

		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		//		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);


		int x = 1;
		// obs³uga zdarzeñ (o ile jakieœ zasz³y) / handling of events (if there were any)
		while (SDL_PollEvent(&event)) {

			switch(menu){
				case 0: 
						{
						switch (event.type) {
						case SDL_KEYDOWN:

							if (event.key.keysym.sym == SDLK_q)
							{
								if (pause == 0)
									pause = 1;
								else
									pause = 0;
								ifQuit = 1; val = 1;
							}
							if (event.key.keysym.sym == SDLK_p)
							{
								if (pause == 0)
									pause = 1;
								else
									pause = 0;
							}
							if (pause == 1)
							{
								if ((event.key.keysym.sym == SDLK_RIGHT) && (positionX <= 720))
									positionX = positionX + 40;
								else if ((event.key.keysym.sym == SDLK_LEFT) && (positionX >= 40))
									positionX = positionX - 40;
								else if ((event.key.keysym.sym == SDLK_DOWN) && (positionY < 580))
									positionY = positionY + 40;
								else if (event.key.keysym.sym == SDLK_UP) positionY = positionY - 40;
							}
							break;
						case SDL_QUIT:
							quit = 1;
							break;
						};

						break;
						}
				case 1:
						{
						if (event.type == SDL_KEYDOWN)
						{
							zycia = 3;
							menu = 3;
							start = 1;
						}
						break;
						}
				case 2:
						{
						if (event.key.keysym.sym == SDLK_RIGHT)
							val = 2;
						if (event.key.keysym.sym == SDLK_LEFT)
							val = 1;
						if (event.key.keysym.sym == SDLK_SPACE)
						{
							if (val == 1)
							{
								restart = 0;
								menu = 3;
								start = 1;
								ifQuit = 0;
							}
							if (val == 2)
							{
								menu = 0;
								ifQuit = 0;
								pause = 1;
							}
						}
						break;
						}
				case 3:
						{
						if (event.key.keysym.sym == SDLK_1)
						{
							restart = 1;
						}
						if (event.key.keysym.sym == SDLK_ESCAPE)
						{
							quit = 1;
						}
						if (event.key.keysym.sym == SDLK_h)
						{
							menu = 4;
							start = 2;
						}
						break;
						}
				case 4:
						{
						if (event.key.keysym.sym == SDLK_f)
						{
							menu = 3;
							start = 1;
						}
						break;
						}
				case 5:
						{
						if (wynik > result[9])
						{
							if (NumberOfChar < 3)
							{
								if (event.type == SDL_KEYDOWN) {
									user[NumberOfChar] = char(event.key.keysym.sym);
									NumberOfChar++;

								}
							}
							if (NumberOfChar >= 3)
							{
								if (event.key.keysym.sym == SDLK_SPACE)
								{
									LepszyWynik(plik, result, name, wynik, user);
									wynik = 0;
									menu = 3;
									restart = 0;
								}
							}
						}
						else
						{
							if (event.key.keysym.sym == SDLK_SPACE)
							{
								wynik = 0;
								menu = 3;
								restart = 0;
							}
						}
						break;
						}
				default:
						break;
				};
			
		};
		frames++;
	};

	// zwolnienie powierzchni / freeing all surfaces
	fclose(plik);
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
	};
