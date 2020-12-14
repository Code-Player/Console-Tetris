#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>


using namespace std;

clock_t startDropT, endT, startGroundT;
int x = 8, y = 0;
RECT blockSize;
int blockForm;
int blockRotation = 0;
int key;
int score = 0;
int nextBlockForm;
int comboStack = 0;
bool combo = false;
int scoreBackup = 0;
int saveBlock = -1;
bool savedBlock = false;
int blockTrunk;

clock_t startT;
int gameTime = 5;

int block[7][4][4][4] = {
	{ // T모양 블럭
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{0,1,1,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{0,1,0,0}
		}
	},
	{    // 번개 블럭
		{
			{0,0,0,0},
			{0,1,1,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,1,0,0}
		}
	},
	{   // 번개 블럭 반대
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{1,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{1,0,0,0}
		}
	},
	{   // 1자형 블럭
		{
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0}
		},
		{
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0}
		}
	},
	{   // L자형 블럭
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{1,0,0,0},
			{1,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,1,0},
			{0,0,1,0},
			{0,0,0,0}
		},
		{
			{0,1,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{0,0,0,0}
		}
	},
	{   // L자형 블럭 반대
		{
			{0,0,0,0},
			{0,0,1,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{1,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,1,0},
			{1,0,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		}
	},
	{   // 네모 블럭
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		}
	}
};

int space[15 + 1][10 + 2] = {  // 세로 15+1(아래벽)칸, 가로 10+2(양쪽 벽)칸  
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1}
};

string board[50][50];

void Init();
void gotoxy(int x, int y);
void CreateRandomForm();
int  CheckCrash(int x, int y);
void DropBlock();
void BlockToGround();
void RemoveLine();
void DrawMap();
void DrawBlock();
void DrawBlock2(int x, int y, int block);
void InputKey();
void textcolor(int foreground, int background);
void draw_rectangle(int w, int h, int x, int y, string str, string content);

stringstream ss;

int main() {
	Init();
	DrawBlock2(4, 2, 3);
	DrawBlock2(10, 2, 1);
	DrawBlock2(10, 3, 5);
	DrawBlock2(20, 3, 6);
	DrawBlock2(16, 3, 5);
	DrawBlock2(8, 0, 4);
	gotoxy(16, 2);
	cout << "Tetris Game" << endl;

	string description[] = { 
		"엔터 키 :              블록 저장",
		"스페이스바 키 :        블록 회전",
		"방향키(왼쪽, 오른쪽) : 블록 이동\n",
	};
	int i = 8;
	for (auto s :description) {
		gotoxy(3, i);
		cout << s << endl;
		i++;
	}
	gotoxy(3, 12);
	cout << "콤보 시스템 :: 한번에 여러줄을 격파 시,";
	textcolor(13, 0);
	cout << "14점";
	textcolor(15, 0);
	cout << "씩 점수가 증가되어 주어집니다.";
	gotoxy(8, 15);
	cout << "아무키나 누르면 게임이 시작됩니다.";
	//cout << "Enter Key : Block Save\n";
	//cout << "SpaceBar Key : Block Reform\n";
	//cout<<"Left, Right Key : Block Move\n";
	
	_getch();
	system("cls");

	startDropT = clock();
	CreateRandomForm();

	while (true) {
		DrawMap();
		DrawBlock();
		DropBlock();
		RemoveLine();
		BlockToGround();
		InputKey();
	}
	return 0;
}

void Init() {
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	srand(time(NULL));
}

void draw_rectangle(int w, int h, int x, int y, string str, string content)
{
	int i, j;
	unsigned char a = 0xa6;
	unsigned char b[7];

	for (i = 1; i < 7; i++)
		b[i] = 0xa0 + i;

	gotoxy(x, y);
	printf("%c%c", a, b[3]);
	for (i = 0; i < w; i++)
	{
		if (i == 1)
		{
			// - (str.length() / 2)) {
			cout << " " << str << " ";
			i+=(str.length()/2);
		}
		else
			printf("%c%c ", a, b[1]);
	}
	printf("%c%c", a, b[4]);
	printf("\n");

	for (i = 0; i <= h; i++)
	{
		gotoxy(x, y + i + 1);
		printf("%c%c", a, b[2]);
		for (j = 0; j < w; j++)
			printf("  ");

		printf("%c%c", a, b[2]);
		printf("\n");
	}

	gotoxy(x, y + h+1);
	printf("%c%c", a, b[6]);
	for (i = 0; i < w; i++)
		printf("%c%c ", a, b[1]);
	printf("%c%c", a, b[5]);
	printf("\n");

	gotoxy((x + (w / 2)) + ((content.length() / 2)), y + (h / 2) + 1);
	cout << content;
}


void gotoxy(int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void CreateRandomForm() {
	blockForm = nextBlockForm;
	nextBlockForm = rand() % 7;
}

int CheckCrash(int x, int y) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[blockForm][blockRotation][i][j] == 1) {
				int t = space[i + y][j + x / 2];
				if (t == 1 || t >= 2) { // 벽일 때, 블럭일 때
					return true;
				}
			}
		}
	}
	return false;
}

void DropBlock() {
	endT = clock();
	if ((float)(endT - startDropT) >= 800) {
		if (CheckCrash(x, y + 1) == true) return;
		y++;
		startDropT = clock();
		startGroundT = clock();
		system("cls");
	}
}

void BlockToGround() {
	if (CheckCrash(x, y + 1) == true) {
		if ((float)(endT - startGroundT) > 1500) {
			// 현재 블록 저장
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (block[blockForm][blockRotation][i][j] == 1) {
						space[i + y][j + x / 2] = blockForm + 2;
						// 블럭의 번호를 space에 2가 아닌 blockForm+2로 저장해서 색상 지정
						gotoxy(x + j * 2, y + i);
						printf("■");
					}
				}
			}
			x = 8;
			y = 0;
			if (score <= scoreBackup + 100)
			{
				comboStack = 0;
				savedBlock = false;
			}
			CreateRandomForm();
		}
	}
}

void RemoveLine() {
	for (int i = 15; i >= 0; i--) { // 벽라인 제외한 값
		int cnt = 0;
		for (int j = 1; j < 11; j++) { // 
			if (space[i][j] >= 2) {
				cnt++;
			}
		}
		if (cnt >= 10) { // 벽돌이 다 차있다면
			for (int j = 0; i - j >= 0; j++) {
				for (int x = 1; x < 11; x++) {
					if (i - j - 1 >= 0)
					{
						space[i - j][x] = space[i - j - 1][x];
						// 줄이 다 차면 지워줌
					}
					else
						// 천장이면 0저장
						space[i - j][x] = 0;
				}
			}

			score += 100 + ((comboStack * 100) / 7);
			comboStack += 1;
			scoreBackup = score;
		}
	}
}

void textcolor(int foreground, int background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void DrawMap() {
	gotoxy(0, 0);
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 12; j++) {
			if (space[i][j] == 1) {
				gotoxy(j * 2, i);
				printf("□");
			}
			else if (space[i][j] >= 2) {
				gotoxy(j * 2, i);
				textcolor(space[i][j] + 6, space[i][j] + 6);
				printf("■");
			}
			 textcolor(15, 0);
		}
	}

	cout << ss.str();


	gotoxy(25, 1);
	printf("다음 블럭");
	//draw_rectangle(10, 8, 25, 1, "다음블럭", "");
	gotoxy(50, 1);
	printf("저장된 블럭");
//	draw_rectangle(10, 3, 25, 12, "점수", to_string(score) + "점");
	gotoxy(25, 12);
	printf("총 %d점 / %d콤보", score, comboStack);
	//draw_rectangle(10, 8, 50, 1, "저장된블럭", "");
	DrawBlock2(32, 4, nextBlockForm);
	DrawBlock2(58, 4, saveBlock);
}
// nextBlockForm 만들기
void DrawBlock() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[blockForm][blockRotation][i][j] == 1) {
				gotoxy(x + j * 2, y + i);
				
				textcolor(blockForm + 8, blockForm + 8);
				printf("■");
				textcolor(15, 0);
			}
		}
	}
}

void DrawBlock2(int x, int y, int _blockForm) {
	gotoxy(x, y);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[_blockForm][0][i][j] == 1) {
				gotoxy(x + j * 2, y + i);
				textcolor(_blockForm + 8, _blockForm + 8);
				printf("■");
				textcolor(15, 0);
			}
		}
	}
}

void InputKey() {
	if (_kbhit()) {
		key = _getch();
		switch (key) {
		case 32: // space
			blockRotation++;
			if (blockRotation >= 4) blockRotation = 0;
			startGroundT = clock();
			break;
		case 75: // left
			if (CheckCrash(x - 2, y) == false) {
				x -= 2;
				startGroundT = clock();
			}
			break;
		case 77: // right
			if (CheckCrash(x + 2, y) == false) {
				x += 2;
				startGroundT = clock();
			}
			break;
		case 80: // down
			if (CheckCrash(x, y + 1) == false)
				y++;
			break;
		case 13: // Enter
			if (savedBlock==false)
			{
				if (saveBlock == -1)
				{
					saveBlock = blockForm;
					blockForm = nextBlockForm;
					CreateRandomForm();
					// 사라짐
					//blockForm = nextBlockForm;
				}
				else
				{
					blockTrunk = blockForm;
					blockForm = saveBlock;
					saveBlock = blockTrunk;
				}
				y = 0;
				x = 8;
				savedBlock = true;

				// 이걸 맨위로 보내면 실행 잘  됨.
			}
			break;
		}
		system("cls");
	}
}
