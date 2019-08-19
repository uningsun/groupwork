#include <stdio.h>
#include <stdlib.h> // calloc, free �Լ��� ����� ��� ����
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

	int numCase = (sizeof(testCase) / sizeof(int)) / 2; // ���� ���� �ڽ��� ����

	int w = 256; // canvas �� width
	int h = 256; // canvas �� height
	Canvas can = { 0, 0, w, h, true }; // ����ü�� canvas ���� �� �ʱ�ȭ


	Box *r;
	Canvas *c = &can;

	memoryalloc(&r, numCase); // �޸� ���� �Ҵ�

	//�׳� ¥����
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
	
	inputvalue(r, testCase, numCase); // 1,2,3 �� �Ҵ�
	//Nextfit(r, numCase, c); //1
	//inputvalue(r, testCase, numCase); // 1,2,3 �� �Ҵ�
	Sorting(r, numCase); //2,3
	//smaller_height_first(r, numCase,c );//2
	//rotate_input(r, testCase, numCase);//4
	//Sorting(r, numCase);
	//rotate(r, numCase, c);//4

	
	free(r); // �޸� �����Ҵ� ����
	return 0;

}

void memoryalloc(Box**r, int size)
{
	*r = (Box *)calloc((size), sizeof(Box)); // ����ü �迭 ����
	if (*r == NULL) // ���� �Ҵ翡 �����ϸ� NULL ��ȯ �� ���α׷� ����
	{
		printf("�޸𸮰� �����մϴ�.\n");
		exit(1);
	}
}


void inputvalue(Box*r, int*testcase, int size)
{
	int temp = 0;
	for (int i = 0; i < size; i++) // w,h ���� �Ҵ�
	{
		r[i].w = testcase[i * 2]; // (*(r+i)).w  �Ǵ� (r+i) -> w �� ����
		r[i].h = testcase[i * 2 + 1];
		//printf("%d %d %d\n", i, r[i].w, r[i].h);
		r[i].r = false;
	}
}


void rotate_input(Box*r, int*testcase, int size)
{
	int temp = 0;
	for (int i = 0; i < size; i++) // w,h ���� �Ҵ�
	{
		if (r[i].w > r[i].h) // rotation ���� h�� �� ũ��(����)
		{
			temp = r[i].w;
			r[i].w = r[i].h;
			r[i].h = temp;
			r[i].r = true; //rotation�� �� ���� �ٲ���
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
		if (c->y + r[i].h > c->h) // ���ڳֱ� ��
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
	while(k--) //i�� -1���� ���� ����
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

		if (c->y + r[j].h > c->h)//�� ĭ�� �� ���� ���� ã��
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
	int w = 256; // canvas �� width
	int h = 256; // canvas �� height
	Mat img(w, h, CV_8UC3, Scalar(0, 0, 0));
	Color col;

	int u = 0; // user space
	int maxHeight = 0; // max height
	int i = size;
	int j;
	int temp;

	i = size;
	while (i--) //find item for next column //i�� case�� ����(numCase) �ڿ��� ���� �ҷ��ͼ� draw�� �ڽ��� splice(del)�ϰ�
	{
		for (j = i; j >= 0; j--)// ���� �� find�ϸ� j�� -1���� ������
		{
			if (r[j].in == true) // true�� ���� �̹� draw�� �� continue��Ű�� for�� �ٽ� �ö󰡼� j++
			{
				continue;
			}
			if (c->x + r[j].w <= c->w) // �ڽ��� �ʺ� ĵ������ ���� �ʺ� ���� �۰ų� ������ ����
			{
				break;
			}
		}

		//go to the next row
		if (j < 0) // ���� �� �˻��ؼ� j=-1�̸� ���� ��
		{
			j = i; // �ٽ� �ʱ�ȭ
			c->x = 0; // x���� ����
			c->y += maxHeight;
			maxHeight = 0;
		}

		//�غκп� ä���
		if (r[j].h > c->h - c->y)
		{ // ������ ���̰� ĵ������ ���� ���̺��� ��鼭 
			if (r[j].w <= c->h - c->y)
			{// ������ �ʺ� ĵ������ ���� ���̺��� �۴ٸ� ����
				temp = r[i].w;
				r[i].w = r[i].h;
				r[i].h = temp;
				r[i].r = false;
			}// �ʺ�� ���̸� ĵ���� ũ�⿡ �°� ȸ��
			else continue;//�ʺ� ���� ���̺��� ��ٸ� ó������
		}

		if (r[j].r) // ȸ���� �༮�� �ƴ� �༮ ������ ����
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