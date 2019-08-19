#include <stdio.h>
#include <stdlib.h> // calloc, free 함수가 선언된 헤더 파일
#include <opencv2/opencv.hpp> // opencv2
#include <iostream>
#include <list>

using namespace cv;
typedef struct box
{
	int w;
	int h;
	bool r;
	bool in;
}Box;

struct point
{
	int x;
	int y;
};

typedef struct Canvas
{
	int x;
	int y;
	int w;
	int h;
	bool v;
}Canvas;

typedef struct color
{
	int R;
	int G;
	int B;
}Color;


void memoryalloc(Box**r, int size);
void inputvalue(Box*r, int*testcase, int size);
void rotate_input(Box*r, int*testcase, int size);
void Sorting(Box *r, int size);
void Nextfit(Box *r, int size, Canvas *c);
void smaller_height_first(Box *r, int size, Canvas *c);
void larger_height_first(Box *r, int size, Canvas *c);
void rotate(Box *r, int size, Canvas *c);
void larger_height_first2(Box *r, int size, Canvas*c);

int main()
{

	int testCase[] = { 11, 21, 43, 39, 13, 52, 35, 25, 28, 20, 66, 55, 54, 62, 50, 61, 49, 16, 60, 51, 39, 27, 54, 62, 65, 13, 34, 50, 48, 63, 19, 41, 18, 61, 23, 51, 39, 58, 35, 14, 35, 31, 67, 58, 25, 24, 58, 63, 59, 57, 69, 57, 34, 28, 61, 30, 18, 57, 10, 26, 42, 66, 31, 50, 63, 13, 42, 10, 57, 63, 61, 54, 50, 53, 20, 54, 66, 31, 48, 35, 28, 25, 37, 54, 32, 50, 42, 49, 62, 37, 31, 24, 63, 44, 66, 29, 25, 51, 52, 17, 67, 55, 27, 48, 23, 39, 38, 41, 46, 15, 46, 68, 24, 41, 38, 20, 33, 42, 12, 12, 51, 31, 53, 41, 25, 28, 39, 69, 61, 12, 55, 59, 35, 60, 13, 60, 22, 41, 60, 68, 28, 33, 31, 60, 27, 48, 38, 60, 19, 63, 28, 50, 24, 31, 42, 38, 11, 17, 50, 36, 27, 59, 42, 25, 16, 61, 35, 19, 32, 67, 40, 53, 33, 42, 15, 40, 62, 23, 42, 19, 57, 42, 43, 59, 12, 10, 45, 68, 16, 15, 15, 34, 67, 33, 27, 54, 53, 64, 18, 22 };
	//int testCase[] = { 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11, 10,20, 22,11 };
	//int testCase[] = { 160,160,80,80,80,80,60,60,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10 };
	//int testCase[] = { 67,75,67,75,67,75,67,75,67,75,67,75,67,75,67,75,67,75,67,75,67,75,67,75,50,11,50,11,50,11,50,11,50,11,50,11,50,11,50,11,50,11,50,11,50,11,50,11,50,11,50,11,50,11,50,11,50,11,50,11,50,11,50,11,50,11,50,11,50,11,50,11,50,11,50,11,50,11,50,11,50,11,50,11 };

	int numCase = (sizeof(testCase) / sizeof(int)) / 2; // 집어 넣을 박스의 숫자

	int w = 256; // canvas 의 width
	int h = 256; // canvas 의 height
	Canvas can = { 0, 0, w, h, true }; // 구조체로 canvas 선언 및 초기화


	Box *r;
	Canvas *c = &can;

	memoryalloc(&r, numCase); // 메모리 동적 할당

	//그냥 짜보기
	int i = numCase;
	int j;
	int maxHeight = 0;
	int u = 0;
	Mat img(256, 256, CV_8UC3, Scalar(0, 0, 0));

	inputvalue(r, testCase, numCase);
	Sorting(r, numCase);
	while (i--) {
		for (j = i; j >= 0; j--) {
			if (r[j].w <= c->w - c->x) {
				break;
			}
		}
		if (j < 0) {
			j = i;
			c->x = 0;
			c->y += maxHeight;
			maxHeight = 0;
		}

		if (c->y + r[j].h > c->h) {
			continue;
		}
		rectangle(img, Point(c->x, c->y), Point(c->x + r[j].w, c->y + r[i].h), Scalar(0, 0, 255), -1);
		rectangle(img, Point(c->x, c->y), Point(c->x + r[j].w, c->y + r[i].h), Scalar(255, 0, 0), 1);

		c->x += r[j].w;
		if (r[i].h > maxHeight)
		{
			maxHeight = r[i].h;
		}
		u += (r[j].w) * (r[j].h);

		memmove(&r[j], &r[j + 1], sizeof(Box)*(i - j + 1));
	}


	imshow("result", img);
	waitKey(0);
	
	inputvalue(r, testCase, numCase); // 1,2,3 값 할당
	//Nextfit(r, numCase, c); //1
	//inputvalue(r, testCase, numCase); // 1,2,3 값 할당
	Sorting(r, numCase); //2,3
	//smaller_height_first(r, numCase,c );//2
	//rotate_input(r, testCase, numCase);//4
	//Sorting(r, numCase);
	//rotate(r, numCase, c);//4

	
	free(r); // 메모리 동적할당 해제
	return 0;

}

void memoryalloc(Box**r, int size)
{
	*r = (Box *)calloc((size), sizeof(Box)); // 구조체 배열 선언
	if (*r == NULL) // 동적 할당에 실패하면 NULL 반환 및 프로그램 종료
	{
		printf("메모리가 부족합니다.\n");
		exit(1);
	}
}


void inputvalue(Box*r, int*testcase, int size)
{
	int temp = 0;
	for (int i = 0; i < size; i++) // w,h 값을 할당
	{
		r[i].w = testcase[i * 2]; // (*(r+i)).w  또는 (r+i) -> w 도 가능
		r[i].h = testcase[i * 2 + 1];
		//printf("%d %d %d\n", i, r[i].w, r[i].h);
		r[i].r = false;
	}
}


void rotate_input(Box*r, int*testcase, int size)
{
	int temp = 0;
	for (int i = 0; i < size; i++) // w,h 값을 할당
	{
		if (r[i].w > r[i].h) // rotation 전부 h가 더 크게(길쭉)
		{
			temp = r[i].w;
			r[i].w = r[i].h;
			r[i].h = temp;
			r[i].r = true; //rotation한 후 색깔 바꿔줌
		}
	}
}


void Sorting(Box *r, int size) // Bubble Sort
{
	int i, j;
	Box temp;

	//sorting by height
	for (i = 0; i < size - 1; i++)
	{
		for (j = 0; j < size - 1; j++)
		{
			if (r[j].h > r[j + 1].h)
			{
				temp = r[j];
				r[j] = r[j + 1];
				r[j + 1] = temp;
			}
		}
	}
	for (i = 0; i < size; i++) {
		printf("%d %d %d\n", i, r[i].w, r[i].h);
	}
}


void Nextfit(Box *r, int size, Canvas *c)
{
	int i;
	int u = 0;//used space
	int maxHeight = 0;//maxHeight

	Mat img(256, 256, CV_8UC3, Scalar(0, 0, 0));

	for (i = 0; i < size; i++)
	{
		if (c->x + r[i].w > c->w)
		{
			c->x = 0;
			c->y += maxHeight;
			maxHeight = 0;
		}
		if (c->y + r[i].h > c->h)
		{
			break;
		}
		rectangle(img, Point(c->x, c->y), Point(c->x + r[i].w, c->y + r[i].h), Scalar(0, 0, 255), -1);
		rectangle(img, Point(c->x, c->y), Point(c->x + r[i].w, c->y + r[i].h), Scalar(255, 0, 0), 1);

		c->x += r[i].w;
		if (r[i].h > maxHeight)
		{
			maxHeight = r[i].h;
		}
		u += (r[i].w)*(r[i].h);
	}
	imshow("result", img);
	waitKey(0);
}
void smaller_height_first(Box *r, int size, Canvas *c)
{
	int i;
	int u = 0;//used space
	int maxHeight = 0;//maxHeight

	//Canvas can = { 0, 0, 256, 256, true };
	Mat img(256, 256, CV_8UC3, Scalar(0, 0, 0));
	
	for (i = 0; i < size; i++)
	{
		if (c->x + r[i].w > c->w)
		{
			c->x = 0;
			c->y += maxHeight;
			maxHeight = 0; // reset
		}
		if (c->y + r[i].h > c->h) // 상자넣기 끝
		{
			break;
		}
		rectangle(img, Point(c->x, c->y), Point(c->x + r[i].w, c->y + r[i].h), Scalar(0, 0, 255), -1);
		rectangle(img, Point(c->x, c->y), Point(c->x + r[i].w, c->y + r[i].h), Scalar(255, 0, 0), 1);

		c->x += r[i].w;
		if (r[i].h > maxHeight)
		{
			maxHeight = r[i].h;
		}
		u += (r[i].w)*(r[i].h);
	}
	imshow("result", img);
	waitKey(0);
}


void larger_height_first(Box *r, int size, Canvas *c)
{
	int i, j, k;
	int u = 0;//used space
	int maxHeight = 0;//maxHeight

	Mat img(256, 256, CV_8UC3, Scalar(0, 0, 0));
	k = size;
	while(k--) //i가 -1까지 가서 멈춤
	{
		i = size-1;
		for (j = i; j >= 0; j--)
		{
			if (r[j].in == true)
			{
				continue;
			}

			if (c->x + r[j].w <= c->w)
			{
				break;
			}
		}

		if (j < 0)
		{
			j = i;
			c->x = 0;
			c->y += maxHeight;
			maxHeight = 0;
		}

		if (c->y + r[j].h > c->h)//밑 칸에 들어갈 작은 상자 찾기
		{
			continue;
		}

		//draw
		rectangle(img, Point(c->x, c->y), Point(c->x + r[j].w, c->y + r[i].h), Scalar(0, 0, 255), -1);
		rectangle(img, Point(c->x, c->y), Point(c->x + r[j].w, c->y + r[i].h), Scalar(255, 0, 0), 1);

		c->x += r[j].w;
		if (r[j].h > maxHeight)
		{
			maxHeight = r[j].h;
		}
		r[j].in = true;
		u += (r[j].w)*(r[j].h);
		
	}

	imshow("result", img);
	waitKey(0);
}


void rotate(Box *r, int size, Canvas *c)
{
	int w = 256; // canvas 의 width
	int h = 256; // canvas 의 height
	Mat img(w, h, CV_8UC3, Scalar(0, 0, 0));
	Color col;

	int u = 0; // user space
	int maxHeight = 0; // max height
	int i = size;
	int j;
	int temp;

	i = size;
	while (i--) //find item for next column //i는 case의 개수(numCase) 뒤에서 부터 불러와서 draw한 박스를 splice(del)하게
	{
		for (j = i; j >= 0; j--)// 전부 다 find하면 j가 -1까지 떨어짐
		{
			if (r[j].in == true) // true인 것은 이미 draw한 거 continue시키면 for로 다시 올라가서 j++
			{
				continue;
			}
			if (c->x + r[j].w <= c->w) // 박스의 너비가 캔버스의 남은 너비 보다 작거나 같으면 나가
			{
				break;
			}
		}

		//go to the next row
		if (j < 0) // 전부 다 검사해서 j=-1이면 다음 줄
		{
			j = i; // 다시 초기화
			c->x = 0; // x부터 시작
			c->y += maxHeight;
			maxHeight = 0;
		}

		//밑부분에 채우기
		if (r[j].h > c->h - c->y)
		{ // 상자의 높이가 캔버스의 남은 높이보다 길면서 
			if (r[j].w <= c->h - c->y)
			{// 상자의 너비가 캔버스의 남은 높이보다 작다면 실행
				temp = r[i].w;
				r[i].w = r[i].h;
				r[i].h = temp;
				r[i].r = false;
			}// 너비와 높이를 캔버스 크기에 맞게 회전
			else continue;//너비가 남은 높이보다 길다면 처음으로
		}

		if (r[j].r) // 회전된 녀석과 아닌 녀석 색으로 구별
		{
			col = { 0,0,255 };
		}
		else
		{
			col = { 255,0,0 };
		}

		//draw
		rectangle(img, Point(c->x, c->y), Point(c->x + r[j].w, c->y + r[j].h), Scalar(col.R, col.G, col.B), 1);
		c->x += r[j].w;
		if (r[j].h > maxHeight)
		{
			maxHeight = r[j].h;
		}
		r[j].in = true;
		u += (r[j].w)*(r[j].h);

	}

	imshow("result", img);
	waitKey(0);
}