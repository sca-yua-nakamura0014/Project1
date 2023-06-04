#include <iostream>
#include <chrono>
#include <thread>
#include<Windows.h>

using namespace std;



const int BufferWidth = 10;
const int BufferHeight = 20;

const int mapWidth = 10;
const int mapHeight = 20;



char gBuffer[BufferWidth][BufferHeight];

char gMap[mapWidth][mapHeight];



int ObjectX = 0;

int ObjectY =0;




const float ObjectSpeed = 0.5f;



std::chrono::steady_clock::time_point PrevFrameTime;

bool gamestart = true;


void Initialize()

{


	for (int y = 0; y < BufferHeight; ++y)
	{

		for (int x = 0; x < BufferWidth; ++x)
		{

			gBuffer[x][y] = ' ';

		}

	}


	PrevFrameTime = std::chrono::steady_clock::now();

}

void InitializeMap()
{
	for (int y = 0; y < mapHeight; y++)
	{
		for (int x = 0; x < mapWidth; x++)
		{
			gMap[x][y] = '#';
		}
	}
}

void RenderMap()
{
	
	for (int y = 0; y < mapHeight; y++)
	{
		for (int x = 0; x < mapWidth; x++)
		{
			if (x == ObjectX && y == ObjectY)
			{
				gMap[x][y] = 'P';
			}
			
			cout << gMap[x][y];
		}
		cout << endl;
	}
	cout << "\n"<<endl;
}



void Update()
{
	if (GetAsyncKeyState('A'))
	{
		if (ObjectX >=1)
		{
			ObjectX--;
		}
		
	}
	if (GetAsyncKeyState('D'))
	{
		ObjectX++;
	}
	if (GetAsyncKeyState('W'))
	{
		ObjectY-= 2;
	}
	if (GetAsyncKeyState('S'))
	{
		ObjectY+= 2;
	}

	std::chrono::steady_clock::time_point currentFrameTime = std::chrono::steady_clock::now();



	std::chrono::duration<float> deltaTime = currentFrameTime - PrevFrameTime;



	ObjectX += static_cast<int>((ObjectSpeed * deltaTime.count()));


	for (int y = 0; y < BufferHeight; ++y)
	{
		for (int x = 0; x < BufferWidth; ++x)
		{
			gBuffer[x][y] = '#';
		}

	}

	gBuffer[ObjectX][ObjectY] = 'P';

	for (int y = 0; y < BufferHeight; ++y)
	{

		for (int x = 0; x < BufferWidth; ++x)
		{
			if ((x == 0 && y <= 16) || (x == 1 && y >= 11 && y <= 13)|| (x == 2 && y >= 4 && y <= 18)|| (x == 3 && y >= 4 && y <= 7)|| (x == 4 && y >= 6 && y <= 16)|| (x == 5 && y >= 14 && y <= 16)
				|| (x == 6 && y >= 4 && y <= 16)|| (x == 7 && y >= 4 && y <= 6)|| (x == 8 && y >= 4 && y <= 19))
			{
				gBuffer[x][y] = ' ';
			}

			if (x == 9 && y >= 18)
			{
				gBuffer[x][y] = 'G';
			}
		}

	}
	if (gBuffer[ObjectX][ObjectY] == 'P' || gBuffer[ObjectX][ObjectY] == 'G')
	{
		gamestart = false;
	}


	for (int y = 0; y < BufferHeight; ++y)
	{

		for (int x = 0; x < BufferWidth; ++x)
		{
			if (x == ObjectX && y == ObjectY)
			{
				cout << "P";
			}
			else if ((x == 0 && y <= 16) || (x == 1 && y >= 11 && y <= 13) || (x == 2 && y >= 4 && y <= 18) || (x == 3 && y >= 4 && y <= 7) || (x == 4 && y >= 6 && y <= 16) || (x == 5 && y >= 14 && y <= 16)
				|| (x == 6 && y >= 4 && y <= 16) || (x == 7 && y >= 4 && y <= 6) || (x == 8 && y >= 4 && y <= 19))
			{
				cout << " ";
			}
			else if (x == 9 && y >= 18)
			{
				cout << "G";
			}
			else
			{
				cout << gBuffer[x][y];
			}

		}

		cout << endl;

	}

	PrevFrameTime = currentFrameTime;
	
}


void GameLoop()
{
	while (gamestart)
	{
		
		int prevObjectX = ObjectX;
		int prevObjectY = ObjectY;

		std::chrono::steady_clock::time_point currentFrameTime = std::chrono::steady_clock::now();



		std::chrono::duration<float> deltaTime = currentFrameTime - PrevFrameTime;



		ObjectX += static_cast<int>(ObjectSpeed * deltaTime.count());



		for (int y = 0; y < BufferHeight; ++y)
		{

			for (int x = 0; x < BufferWidth; ++x)

			{
				gBuffer[x][y] = '#';
			}

		}

		ObjectY++;

		gBuffer[ObjectX][ObjectY] = 'P';

		for (int y = 0; y < BufferHeight; ++y)
		{

			for (int x = 0; x < BufferWidth; ++x)
			{
				if ((x == 0 && y <= 16) || (x == 1 && y >= 11 && y <= 13) || (x == 2 && y >= 4 && y <= 18) || (x == 3 && y >= 4 && y <= 7) || (x == 4 && y >= 6 && y <= 16) || (x == 5 && y >= 14 && y <= 16)
					|| (x == 6 && y >= 4 && y <= 16) || (x == 7 && y >= 4 && y <= 6) || (x == 8 && y >= 4 && y <= 19))
				{
					gBuffer[x][y] = ' ';
				}
				if (x == 9 && y >= 18)
				{
					gBuffer[x][y] = 'G';
				}
			}

		}
		if (gBuffer[ObjectX][ObjectY] == 'P' || gBuffer[ObjectX][ObjectY] == 'G')
		{
			gamestart = false;
			break;
		}



		for (int y = 0; y < BufferHeight; ++y)
		{

			for (int x = 0; x < BufferWidth; ++x)
			{
				if (x == ObjectX && y == ObjectY)
				{
					cout << "P";
				}
				else if ((x == 0 && y <= 16) || (x == 1 && y >= 11 && y <= 13) || (x == 2 && y >= 4 && y <= 18) || (x == 3 && y >= 4 && y <= 7) || (x == 4 && y >= 6 && y <= 16) || (x == 5 && y >= 14 && y <= 16)
					|| (x == 6 && y >= 4 && y <= 16) || (x == 7 && y >= 4 && y <= 6) || (x == 8 && y >= 4 && y <= 19))
				{
					cout << " ";
				}
				else if (x == 9 && y>=18)
				{
					cout<<"G";
				}
				else
				{
					cout << gBuffer[x][y];
				}
			}

			cout << endl;

		}
		cout << "\n" << endl;



		PrevFrameTime = currentFrameTime;


		Update();



		std::this_thread::sleep_for(std::chrono::milliseconds(280));

	}

}


int main()
{
	cout << "イライラ棒" << endl;
	cout << "#に触れるとゲームオーバーです。" << endl << "Pを動かしてGを目指してください。"<<endl;
	cout << "W・・・上に進む" << endl << "A・・・下に進む" << endl << "D・・・右に進む" << endl << "A・・・左に進む"<<endl;
	cout << "*Pは常に下に落ち続けるため注意が必要です" << endl;
	cout << "Zでスタート";
	while (true)
	{
		if (GetAsyncKeyState('Z'))
		{
			InitializeMap();
			Initialize();
			RenderMap();
			GameLoop();

			if (gBuffer[ObjectX][ObjectY] == 'P')
			{
				system("cls");
				cout << "GameOver....";
				break;
			}
			if (gBuffer[ObjectX][ObjectY] == 'G')
			{
				system("cls");
				cout << "GameClear!!!";
				break;
			}
			
		}
	}
	

	return 0;
	

	

}
