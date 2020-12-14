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
	{ // T��� ��
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
	{    // ���� ��
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
	{   // ���� �� �ݴ�
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
	{   // 1���� ��
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
	{   // L���� ��
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
	{   // L���� �� �ݴ�
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
	{   // �׸� ��
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

int space[15 + 1][10 + 2] = {  // ���� 15+1(�Ʒ���)ĭ, ���� 10+2(���� ��)ĭ  
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

string board[100][100];

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
void draw_rectangle(int w, int h, int x, int y, wstring str, wstring content);

stringstream ss;

int qq() {
	Init();
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
	unsigned char grid[100][100];

	grid[0][0] = 'c';
	grid[0][1] = 'a';
	grid[1][0] = 'c';
	// null�κ� ��ġ��
	//for (int i = 0; i <= sizeof(grid[0]) - 1; i++)
	//{
	//	printf("%c", grid[0][i]);
	//	if (grid[0][i] == NULL)
	//		break;
	//}

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
			i += (str.length() / 2);
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

	gotoxy(x, y + h + 1);
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
				if (t == 1 || t >= 2) { // ���� ��, ���� ��
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
			// ���� ��� ����
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (block[blockForm][blockRotation][i][j] == 1) {
						space[i + y][j + x / 2] = blockForm + 2;
						// ���� ��ȣ�� space�� 2�� �ƴ� blockForm+2�� �����ؼ� ���� ����
						gotoxy(x + j * 2, y + i);
						printf("��");
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
	for (int i = 15; i >= 0; i--) { // ������ ������ ��
		int cnt = 0;
		for (int j = 1; j < 11; j++) { // 
			if (space[i][j] >= 2) {
				cnt++;
			}
		}
		if (cnt >= 10) { // ������ �� ���ִٸ�
			for (int j = 0; i - j >= 0; j++) {
				for (int x = 1; x < 11; x++) {
					if (i - j - 1 >= 0)
					{
						space[i - j][x] = space[i - j - 1][x];
						// ���� �� ���� ������
					}
					else
						// õ���̸� 0����
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
				board[j * 2][i] = "��";
				//				printf("��");
			}
			else if (space[i][j] >= 2) {
				gotoxy(j * 2, i);
				textcolor(space[i][j] + 6, space[i][j] + 6);

				//				printf("��");
			}
			textcolor(15, 0);
		}
	}
	cout << ss.str();

	draw_rectangle(10, 8, 25, 1, "������", "");
	draw_rectangle(10, 3, 25, 12, "����", to_string(score) + "��");
	draw_rectangle(10, 8, 50, 1, "����Ⱥ�", "");
	DrawBlock2(32, 4, nextBlockForm);
	DrawBlock2(58, 4, saveBlock);
}
// nextBlockForm �����
void DrawBlock() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[blockForm][blockRotation][i][j] == 1) {
				gotoxy(x + j * 2, y + i);

				textcolor(blockForm + 8, blockForm + 8);
				printf("��");
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
				printf("��");
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
			if (savedBlock == false)
			{
				if (saveBlock == -1)
				{
					saveBlock = blockForm;
					blockForm = nextBlockForm;
					CreateRandomForm();
					// �����
					//blockForm = nextBlockForm;
				}
				else
				{
					blockTrunk = blockForm;
					blockForm = saveBlock;
					saveBlock = blockTrunk;
				}
				y = 0;
				savedBlock = true;

				// �̰� ������ ������ ���� ��  ��.
			}
			break;
		}
		system("cls");
	}
}