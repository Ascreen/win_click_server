// window_server.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//
#include <winsock2.h>
#pragma comment(lib,"ws2_32")
#include <stdio.h>
#include <stdlib.h>


#define PORT 20000
#define LENGTH 5000


#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <math.h>

#include "opencv2/highgui/highgui.hpp"
#include "opencv/cv.h"

#include "opencv2/core/core_c.h"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc.hpp"

#include "opencv/cxcore.h"

#include "opencv2/core/core.hpp"

#include "opencv2/imgproc/imgproc_c.h"

#include "opencv2/opencv.hpp"



#define Pi 3.14159265
#define Length 510
#define Height 210

#define monitor_l 1440
#define monitor_h 900

#define CameraNum 0
#define Time 1
#define X 2
#define Y 3


using namespace cv;
using namespace std;


int check_one=0, check_two=0, check_three=0, check_four=0;


int data1[10][4];
int data2[10][4];
int data3[10][4];
int data4[10][4];

Point dr_c(0, 0);
Point dr_l(0, 0);
Point dr_h(0, 0);
Point dr_touched(0, 0);
float dr_l_dgree;
float dr_h_dgree;

Point ur_c(0, 0);
Point ur_l(0, 0);
Point ur_h(0, 0);
Point ur_touched(0, 0);
float ur_l_dgree;
float ur_h_dgree;

Point ul_c(0, 0);
Point ul_l(0, 0);
Point ul_h(0, 0);
Point ul_touched(0, 0);
float ul_l_dgree;
float ul_h_dgree;

Point dl_c(0, 0);
Point dl_l(0, 0);
Point dl_h(0, 0);
Point dl_touched(0, 0);
float dl_l_dgree;
float dl_h_dgree;

void setting_parsing() {
	string settingFilePath = "setting.txt";

	ifstream openFile(settingFilePath.data());
	if (openFile.is_open()) {
		string line;
		int num = 0;
		while (getline(openFile, line)) {

			std::vector<char> writable(line.begin(), line.end());
			writable.push_back('\0');
			char* ptr = &writable[0];
			//std::cout << ptr;

			char* token = strtok(ptr, "/");

			int count = 0;
			while (token) {
				if (count == 0) {
					dr_c.x = atoi(token);
					count++;
				}
				else if (count == 1) {
					dr_c.y = atoi(token);
					count++;
				}
				else if (count == 2) {
					dr_l.x = atoi(token);
					count++;
				}
				else if (count == 3) {
					dr_l.y = atoi(token);
					count++;
				}
				else if (count == 4) {
					dr_h.x = atoi(token);
					count++;
				}
				else if (count == 5) {
					dr_h.y = atoi(token);
					count++;
				}
				else if (count == 6) {
					ur_c.x = atoi(token);
					count++;
				}
				else if (count == 7) {
					ur_c.y = atoi(token);
					count++;
				}
				else if (count == 8) {
					ur_l.x = atoi(token);
					count++;
				}
				else if (count == 9) {
					ur_l.y = atoi(token);
					count++;
				}
				else if (count == 10) {
					ur_h.x = atoi(token);
					count++;
				}
				else if (count == 11) {
					ur_h.y = atoi(token);
					count++;
				}
				else if (count == 12) {
					ul_c.x = atoi(token);
					count++;
				}
				else if (count == 13) {
					ul_c.y = atoi(token);
					count++;
				}
				else if (count == 14) {
					ul_l.x = atoi(token);
					count++;
				}
				else if (count == 15) {
					ul_l.y = atoi(token);
					count++;
				}
				else if (count == 16) {
					ul_h.x = atoi(token);
					count++;
				}
				else if (count == 17) {
					ul_h.y = atoi(token);
					count++;
				}
				else if (count == 18) {
					dl_c.x = atoi(token);
					count++;
				}
				else if (count == 19) {
					dl_c.y = atoi(token);
					count++;
				}
				else if (count == 20) {
					dl_l.x = atoi(token);
					count++;
				}
				else if (count == 21) {
					dl_l.y = atoi(token);
					count++;
				}
				else if (count == 22) {
					dl_h.x = atoi(token);
					count++;
				}
				else if (count == 23) {
					dl_h.y = atoi(token);
					count++;
				}
				token = strtok(NULL, "/");
			}
			/*
			cout << dr_c<< endl;
			cout << dr_l << endl;
			cout << dr_h << endl;
			cout << ur_c<< endl;
			cout << ur_l << endl;
			cout << ur_h << endl;
			cout << ul_c<< endl;
			cout << ul_l << endl;
			cout << ul_h << endl;
			cout << dl_c<< endl;
			cout << dl_l << endl;
			cout << dl_h << endl;
			*/

		}
		openFile.close();
	}
}

void save(int* data, int* tmp, int camera) {
	data[CameraNum] = camera;
	data[Time] = tmp[Time];
	data[X] = tmp[X];
	data[Y] = tmp[Y];
}

void text_parsing(string filePath, int camera) {

	int tmp1[4];
	int tmp2[4];
	int counter = 0;
	ifstream openFile(filePath.data());
	if (openFile.is_open()) {

		/******************************/
		string init;
		getline(openFile, init);
		//cout<<init<<endl;
		std::vector<char> writable(init.begin(), init.end());
		writable.push_back('\0');
		char* init_tmp = &writable[0];
		char* token = strtok(init_tmp, "/");
		//cout<<token<<endl;
		tmp1[CameraNum] = atoi(token);
		token = strtok(NULL, "/");
		tmp1[Time] = atoi(token) * 10000;
		token = strtok(NULL, "/");
		tmp1[Time] = tmp1[Time] + atoi(token) * 100;
		token = strtok(NULL, "/");
		tmp1[Time] = tmp1[Time] + atoi(token);
		token = strtok(NULL, "/");
		tmp1[X] = atoi(token);
		token = strtok(NULL, "/");
		tmp1[Y] = atoi(token);
		/*****************************/
		int num = 1;
		string line;
		cout << "**************************" << endl;
		while (getline(openFile, line)) {
			std::vector<char> writable(line.begin(), line.end());
			writable.push_back('\0');
			char* ptr = &writable[0];
			int time = 0;
			token = strtok(ptr, "/");
			tmp2[CameraNum] = atoi(token);
			token = strtok(NULL, "/");
			time = atoi(token) * 10000;
			token = strtok(NULL, "/");
			time = time + atoi(token) * 100;
			token = strtok(NULL, "/");
			time = time + atoi(token);
			tmp2[Time] = time;
			token = strtok(NULL, "/");
			tmp2[X] = atoi(token);
			token = strtok(NULL, "/");
			tmp2[Y] = atoi(token);

			if (tmp1[X]<10 || tmp1[Y]<10) {
				tmp1[CameraNum] = tmp2[CameraNum];
				tmp1[Time] = tmp2[Time];
				tmp1[X] = tmp2[X];
				tmp1[Y] = tmp2[Y];
			}
			if (tmp2[Time] - tmp1[Time]<3) {
				//cout<<"why...1"<<tmp2[Time]<<"/"<<tmp1[Time]<<endl;
				if ((abs(tmp1[X] - tmp2[X])<50) || (abs(tmp1[Y] - tmp2[Y])<50)) {
					num += 1;
					tmp1[Time] = ((tmp1[Time] * (num - 1)) + tmp2[Time]) / num;
					tmp1[X] = ((tmp1[X] * (num - 1)) + tmp2[X]) / num;
					tmp1[Y] = ((tmp1[Y] * (num - 1)) + tmp2[Y]) / num;
				}
				else { continue; }
			}
			else if (tmp2[Time] - tmp1[Time]>1) {
				//cout<<"why..."<<tmp2[Time]-tmp1[Time]<<endl;
				num = 1;
				if (!getline(openFile, line)) {
					if (camera == 1 && data1[counter - 1][Time] != tmp1[Time]) {
						save(data1[counter], tmp1, camera);
						cout << data1[counter][CameraNum] << "/" << data1[counter][Time] << "/" << data1[counter][X] << "/" << data1[counter][Y] << endl;
					}
					if (camera == 2 && data2[counter - 1][Time] != tmp1[Time]) {
						save(data2[counter], tmp1, camera);
						cout << data2[counter][CameraNum] << "/" << data2[counter][Time] << "/" << data2[counter][X] << "/" << data2[counter][Y] << endl;
					}
					if (camera == 3 && data3[counter - 1][Time] != tmp1[Time]) {
						save(data3[counter], tmp1, camera);
						cout << data3[counter][CameraNum] << "/" << data3[counter][Time] << "/" << data3[counter][X] << "/" << data3[counter][Y] << endl;
					}
					if (camera == 4 && data4[counter - 1][Time] != tmp1[Time]) {
						save(data4[counter], tmp1, camera);
						cout << data3[counter][CameraNum] << "/" << data3[counter][Time] << "/" << data3[counter][X] << "/" << data3[counter][Y] << endl;
					}
				}
				if (camera == 1) {
					save(data1[counter], tmp1, camera);
					memcpy(tmp1, tmp2, sizeof(tmp2));
					cout << data1[counter][CameraNum] << "/" <<
						data1[counter][Time] << "/" <<
						data1[counter][X] << "/" <<
						data1[counter][Y] << endl;
				}
				else if (camera == 2) {
					save(data2[counter], tmp1, camera);
					memcpy(tmp1, tmp2, sizeof(tmp2));
					cout << data2[counter][CameraNum] << "/" <<
						data2[counter][Time] << "/" <<
						data2[counter][X] << "/" <<
						data2[counter][Y] << endl;
				}
				else if (camera == 3) {
					save(data3[counter], tmp1, camera);
					cout << data3[counter][CameraNum] << "/" <<
						data3[counter][Time] << "/" <<
						data3[counter][X] << "/" <<
						data3[counter][Y] << endl;
					memcpy(tmp1, tmp2, sizeof(tmp2));
				}
				else if (camera == 4) {
					save(data4[counter], tmp1, camera);
					memcpy(tmp1, tmp2, sizeof(tmp2));
					cout << data4[counter][CameraNum] << "/" <<
						data4[counter][Time] << "/" <<
						data4[counter][X] << "/" <<
						data4[counter][Y] << endl;
				}
				counter++;
			}
		}
		openFile.close();
	}
}

int find_min(int cam1, int cam2, int cam3, int cam4) {
	int result;
	int tmp[4] = { cam1,cam2,cam4,cam4 };
	//cout<<tmp[0]<<"/"<<tmp[1]<<"/"<<tmp[2]<<"/"<<tmp[3]<<endl;
	sort(tmp, tmp + 4);
	//cout<<tmp[0]<<"/"<<tmp[1]<<"/"<<tmp[2]<<"/"<<tmp[3]<<endl;
	if (tmp[0] != 0) {
		result = tmp[0];
	}
	else if (tmp[1] != 0) {
		result = tmp[1];
	}
	else { result = tmp[2]; }
	//cout<<"min:"<<result<<endl;
	return result;
}

int zero_counting(int cam1, int cam2, int cam3, int cam4) {
	int zero = 0;
	if (cam1 == 0) { zero++; }
	if (cam2 == 0) { zero++; }
	if (cam3 == 0) { zero++; }
	if (cam4 == 0) { zero++; }

	return zero;
}


float getAngle(Point p1, Point p2) {
	float result;
	result = atan2(p2.y - p1.y, p2.x - p1.x);
	while (result<0) {
		result = 2 * Pi + result;
	}
	return result;
}

void calculate_dr(Point dr_touched) {
	Point tmp_dr_c(0, 0);
	Point tmp_dr_l(0, 0);
	Point tmp_dr_h(0, 0);
	Point tmp_dr_touched(0, 0);

	float dgree;

	//1st change for y
	tmp_dr_c.x = dr_c.x;
	tmp_dr_c.y = Height - dr_c.y;
	tmp_dr_l.x = dr_l.x;
	tmp_dr_l.y = Height - dr_l.y;
	tmp_dr_h.x = dr_h.x;
	tmp_dr_h.y = Height - dr_h.y;
	tmp_dr_touched.x = dr_touched.x;
	tmp_dr_touched.y = Height - dr_touched.y;
	/*
	cout << tmp_dr_c << endl;
	cout << tmp_dr_l<< endl;
	cout << tmp_dr_h<< endl;
	cout << tmp_dr_touched<< endl;
	*/
	//2nd change for x,y (move parell)

	tmp_dr_l.x = tmp_dr_l.x - tmp_dr_c.x;
	tmp_dr_l.y = tmp_dr_l.y - tmp_dr_c.y;
	tmp_dr_h.x = tmp_dr_h.x - tmp_dr_c.x;
	tmp_dr_h.y = tmp_dr_h.y - tmp_dr_c.x;
	tmp_dr_touched.x = tmp_dr_touched.x - tmp_dr_c.x;
	tmp_dr_touched.y = tmp_dr_touched.y - tmp_dr_c.y;
	tmp_dr_c.x = tmp_dr_c.x - tmp_dr_c.x;
	tmp_dr_c.y = tmp_dr_c.y - tmp_dr_c.y;

	/*
	cout << tmp_dr_c << endl;
	cout << tmp_dr_l<< endl;
	cout << tmp_dr_h<< endl;
	cout << tmp_dr_touched<< endl;
	*/


	dgree = getAngle(tmp_dr_h, Point(1, 0)) - getAngle(tmp_dr_l, Point(1, 0));
	dr_h_dgree = (-1)*(getAngle(tmp_dr_touched, Point(1, 0)) - getAngle(tmp_dr_h, Point(1, 0))) * 90 / dgree;
	dr_l_dgree = (-1)*(getAngle(tmp_dr_l, Point(1, 0)) - getAngle(tmp_dr_touched, Point(1, 0))) * 90 / dgree;


	cout << "---dgree-dr---" << endl;
	cout << dr_l_dgree << endl;
	cout << dr_h_dgree << endl;
	/*
	cout << tmp_dr_c << endl;
	cout << tmp_dr_l<< endl;
	cout << tmp_dr_h<< endl;
	cout << tmp_dr_touched<< endl;
	*/

}

void calculate_ur(Point ur_touched) {
	Point tmp_ur_c(0, 0);
	Point tmp_ur_l(0, 0);
	Point tmp_ur_h(0, 0);
	Point tmp_ur_touched(0, 0);
	float dgree;


	//1st change for y
	tmp_ur_c.x = ur_c.x;
	tmp_ur_c.y = Height - ur_c.y;
	tmp_ur_l.x = ur_l.x;
	tmp_ur_l.y = Height - ur_l.y;
	tmp_ur_h.x = ur_h.x;
	tmp_ur_h.y = Height - ur_h.y;
	tmp_ur_touched.x = ur_touched.x;
	tmp_ur_touched.y = Height - ur_touched.y;



	//2nd change for x,y (move parell)
	tmp_ur_l.x = tmp_ur_l.x - tmp_ur_c.x;
	tmp_ur_l.y = tmp_ur_l.y - tmp_ur_c.y;
	tmp_ur_h.x = tmp_ur_h.x - tmp_ur_c.x;
	tmp_ur_h.y = tmp_ur_h.y - tmp_ur_c.x;
	tmp_ur_touched.x = tmp_ur_touched.x - tmp_ur_c.x;
	tmp_ur_touched.y = tmp_ur_touched.y - tmp_ur_c.y;
	tmp_ur_c.x = tmp_ur_c.x - tmp_ur_c.x;
	tmp_ur_c.y = tmp_ur_c.y - tmp_ur_c.y;

	dgree = getAngle(tmp_ur_h, Point(1, 0)) - getAngle(tmp_ur_l, Point(1, 0));
	ur_l_dgree = (-1)*(getAngle(Point(1, 0), tmp_ur_l) - getAngle(Point(1, 0), tmp_ur_touched)) * 90 / dgree;
	ur_h_dgree = (-1)*(getAngle(tmp_ur_touched, Point(1, 0)) - getAngle(tmp_ur_h, Point(1, 0))) * 90 / dgree;


	//cout << tmp_ur_c << endl;
	//cout << tmp_ur_l<< endl;
	//cout << tmp_ur_h<< endl;
	//cout << tmp_ur_touched<< endl;

	cout << "---dgree-ur---" << endl;
	cout << ur_l_dgree << endl;
	cout << ur_h_dgree << endl;


}

void calculate_ul(Point ul_touched) {
	Point tmp_ul_c(0, 0);
	Point tmp_ul_l(0, 0);
	Point tmp_ul_h(0, 0);
	Point tmp_ul_touched(0, 0);
	float dgree;


	//1st change for y
	tmp_ul_c.x = ul_c.x;
	tmp_ul_c.y = Height - ul_c.y;
	tmp_ul_l.x = ul_l.x;
	tmp_ul_l.y = Height - ul_l.y;
	tmp_ul_h.x = ul_h.x;
	tmp_ul_h.y = Height - ul_h.y;
	tmp_ul_touched.x = ul_touched.x;
	tmp_ul_touched.y = Height - ul_touched.y;

	//2nd change for x,y (move parell)
	tmp_ul_l.x = tmp_ul_l.x - tmp_ul_c.x;
	tmp_ul_l.y = tmp_ul_l.y - tmp_ul_c.y;
	tmp_ul_h.x = tmp_ul_h.x - tmp_ul_c.x;
	tmp_ul_h.y = tmp_ul_h.y - tmp_ul_c.x;
	tmp_ul_touched.x = tmp_ul_touched.x - tmp_ul_c.x;
	tmp_ul_touched.y = tmp_ul_touched.y - tmp_ul_c.y;
	tmp_ul_c.x = tmp_ul_c.x - tmp_ul_c.x;
	tmp_ul_c.y = tmp_ul_c.y - tmp_ul_c.y;

	dgree = getAngle(tmp_ul_h, Point(1, 0)) - getAngle(tmp_ul_l, Point(1, 0));
	ul_l_dgree = (getAngle(tmp_ul_touched, Point(1, 0)) - getAngle(tmp_ul_l, Point(1, 0))) * 90 / dgree;
	ul_h_dgree = (getAngle(tmp_ul_h, Point(1, 0)) - getAngle(tmp_ul_touched, Point(1, 0))) * 90 / dgree;

	cout << "---dgree-ul---" << endl;
	cout << ul_l_dgree << endl;
	cout << ul_h_dgree << endl;

}

void calculate_dl(Point dl_touched) {
	Point tmp_dl_c(0, 0);
	Point tmp_dl_l(0, 0);
	Point tmp_dl_h(0, 0);
	Point tmp_dl_touched(0, 0);
	float dgree;


	//1st change for y
	tmp_dl_c.x = dl_c.x;
	tmp_dl_c.y = Height - dl_c.y;
	tmp_dl_l.x = dl_l.x;
	tmp_dl_l.y = Height - dl_l.y;
	tmp_dl_h.x = dl_h.x;
	tmp_dl_h.y = Height - dl_h.y;
	tmp_dl_touched.x = dl_touched.x;
	tmp_dl_touched.y = Height - dl_touched.y;

	//2nd change for x,y (move parell)
	tmp_dl_l.x = tmp_dl_l.x - tmp_dl_c.x;
	tmp_dl_l.y = tmp_dl_l.y - tmp_dl_c.y;
	tmp_dl_h.x = tmp_dl_h.x - tmp_dl_c.x;
	tmp_dl_h.y = tmp_dl_h.y - tmp_dl_c.x;
	tmp_dl_touched.x = tmp_dl_touched.x - tmp_dl_c.x;
	tmp_dl_touched.y = tmp_dl_touched.y - tmp_dl_c.y;
	tmp_dl_c.x = tmp_dl_c.x - tmp_dl_c.x;
	tmp_dl_c.y = tmp_dl_c.y - tmp_dl_c.y;

	dgree = getAngle(tmp_dl_l, Point(1, 0)) - getAngle(tmp_dl_h, Point(1, 0));
	dl_l_dgree = (getAngle(tmp_dl_l, Point(1, 0)) - getAngle(tmp_dl_touched, Point(1, 0))) * 90 / dgree;
	dl_h_dgree = (getAngle(tmp_dl_touched, Point(1, 0)) - getAngle(tmp_dl_h, Point(1, 0))) * 90 / dgree;


	cout << "---dgree-dl---" << endl;
	cout << dl_l_dgree << endl;
	cout << dl_h_dgree << endl;


}

int calculate_y() {
	int result;
	int result1;
	int result2;
	double alpha;
	double beta;

	if (ur_h_dgree != 0 && ul_h_dgree != 0) {
		alpha = ur_h_dgree * Pi / 180;
		beta = ul_h_dgree * Pi / 180;
		result1 = sin(alpha)*sin(beta)*monitor_l / sin(Pi - alpha - beta);
		if (result1<0) {
			result1 = result1 * (-1);
		}
	}
	if (dr_h_dgree != 0 && dl_h_dgree != 0) {

		alpha = dr_h_dgree * Pi / 180;
		beta = dl_h_dgree * Pi / 180;
		result2 = sin(alpha)*sin(beta)*monitor_l / sin(Pi - alpha - beta);
		if (result2<0) {
			result2 = result2 * (-1);
		}
	}
	if (result1 != 0 && result2 != 0) {
		result = ((monitor_h - result2) + result1) / 2;
	}
	else if (result1 == 0) {
		result = monitor_h - result2;
	}
	else if (result2 == 0) {
		result = result1;
	}
	return result;
}

int calculate_x() {

	int result;
	int result1;
	int result2;
	double alpha;
	double beta;

	if (ur_h_dgree != 0 && dr_h_dgree != 0) {
		alpha = ur_h_dgree * Pi / 180;
		beta = dr_h_dgree * Pi / 180;
		result1 = sin(alpha)*sin(beta)*monitor_h / sin(Pi - alpha - beta);
		if (result1<0) {
			result1 = result1 * (-1);

		}


	}
	if (ul_h_dgree != 0 && dl_h_dgree != 0) {

		alpha = ul_h_dgree * Pi / 180;
		beta = dl_h_dgree * Pi / 180;
		result2 = sin(alpha)*sin(beta)*monitor_h / sin(Pi - alpha - beta);
		if (result2<0) {
			result2 = result2 * (-1);
		}
	}
	if (result1 != 0 && result2 != 0) {
		result = ((monitor_l - result2) + result1) / 2;
	}
	else if (result1 == 0) {
		result = monitor_l - result2;
	}
	else if (result2 == 0) {
		result = result1;
	}
	return result;
}

void CLICK(int x, int y) {
	if (x != 0 && y != 0) {
		SetCursorPos(x, y);
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		//cout<<"["<<x<<","<<y<<"]"<<endl;
		Sleep(500);
	}
}

void clickHaJa(int* click, int counter1, int counter2, int counter3, int counter4) {
	int x;
	int y;

	if (click[0] == 1) {
		dr_touched.x = data1[counter1 - 1][X];
		dr_touched.y = data1[counter1 - 1][Y];
		calculate_dr(dr_touched);
	}if (click[1] == 1) {
		ur_touched.x = data2[counter2 - 1][X];
		ur_touched.y = data2[counter2 - 1][Y];
		calculate_ur(ur_touched);
	}if (click[2] == 1) {
		ul_touched.x = data3[counter3 - 1][X];
		ul_touched.y = data3[counter3 - 1][Y];
		calculate_ul(ul_touched);
	}if (click[3] == 1) {
		dl_touched.x = data4[counter4 - 1][X];
		dl_touched.y = data4[counter4 - 1][Y];
		calculate_dl(dl_touched);
	}if (click[0] == 0) {
		dr_touched.x = 0;
		dr_touched.y = 0;
	}if (click[1] == 0) {
		ur_touched.x = 0;
		ur_touched.y = 0;
	}if (click[2] == 0) {
		ul_touched.x = 0;
		ul_touched.y = 0;
	}if (click[3] == 0) {
		dl_touched.x = 0;
		dl_touched.y = 0;
	}

	cout << "clicked with!" << dr_touched << ur_touched << ul_touched << dl_touched << endl;
	x = calculate_x();
	y = calculate_y();
	//cout<<x<<"/"<<y<<endl;
	CLICK(x, y);


}

void clickHalKa() {
	int counter1 = 0;
	int counter2 = 0;
	int counter3 = 0;
	int counter4 = 0;

	int can_click = 0;
	int click[4] = { 0,0,0,0 };

	int criteria_time = 0;

	int zero_counter = 0;
	while (zero_counter<2) {
		//cout<<counter1<<"_"<<counter2<<"_"<<counter3<<"_"<<counter4<<endl;

		//cout<<data1[counter1][Time]<<","<<data2[counter2][Time]<<","<<data3[counter3][Time]<<","<<data4[counter4][Time]<<endl;
		can_click = 0;
		zero_counter = zero_counting(data1[counter1][Time], data2[counter2][Time], data3[counter3][Time], data4[counter4][Time]);
		//cout<<zero_counter<<endl;
		criteria_time = find_min(data1[counter1][Time], data2[counter2][Time], data3[counter3][Time], data4[counter4][Time]);


		if (data1[counter1][Time] == criteria_time || abs(data1[counter1][Time] - criteria_time)<2) {
			counter1++;
			click[0] = 1;
			//cout<<click[0]<<endl;
			can_click++;
		}
		if (data2[counter2][Time] == criteria_time || abs(data2[counter2][Time] - criteria_time)<2) {
			counter2++;
			click[1] = 1;
			//cout<<click[1]<<endl;
			can_click++;
		}
		//cout<<criteria_time<<"-"<<data3[counter3][Time]<<endl;
		if (data3[counter3][Time] == criteria_time || abs(data3[counter3][Time] - criteria_time)<2) {
			//cout<<data3[counter3][Time]<<"-"<<criteria_time<<"-"<<abs(data3[counter3][Time]-criteria_time)<<endl;
			counter3++;
			click[2] = 1;
			//cout<<click[2]<<endl;
			can_click++;
		}
		if (data4[counter4][Time] == criteria_time || abs(data4[counter4][Time] - criteria_time)<2) {

			counter4++;
			click[3] = 1;
			//out<<click[3]<<endl;
			can_click++;
		}
		//cout<<criteria_time<<endl;
		//cout<<click[0]<<"/"<<click[1]<<"/"<<click[2]<<"/"<<click[3]<<endl;
		//cout<<"zero_counter"<<zero_counter<<endl;
		if (can_click>2 && zero_counter<2) {
			//cout<<criteria_time<<endl;
			//cout<<"why"<<"/c:"<<can_click<<"/z:"<<zero_counter<<endl;
			clickHaJa(click, counter1, counter2, counter3, counter4);
			memset(click, 0, sizeof(click));
			can_click = 0;
			//Sleep(1000);

		}
		if (zero_counter>1) { break; }
		//cout<<"why...?"<<endl;
	}
}

int sbjz_main() {
	while (dr_c.x != 0 || dr_c.y != 0 || dr_l.x != 0 || dr_l.y != 0 || dr_h.x != 0 || dr_h.y != 0 ||
		ur_c.x != 0 || ur_c.y != 0 || ur_l.x != 0 || ur_l.y != 0 || ur_h.x != 0 || ur_h.y != 0 ||
		ul_c.x != 0 || ul_c.y != 0 || ul_l.x != 0 || ul_l.y != 0 || ul_h.x != 0 || ul_h.y != 0 ||
		ur_c.x != 0 || ur_c.y != 0 || ur_l.x != 0 || ur_l.y != 0 || ur_h.x != 0 || ur_h.y != 0) {
		setting_parsing();
	}

	text_parsing("C:/Users/ksy/Desktop/one.txt", 1);
	text_parsing("C:/Users/ksy/Desktop/two.txt", 2);
	text_parsing("C:/Users/ksy/Desktop/three.txt", 3);
	text_parsing("C:/Users/ksy/Desktop/four.txt", 4);

	clickHalKa();

	return 0;
}

//void ErrorHandling(const char* message);

int main(int argc, char** argv)
{
	WSADATA wsaData;	 //	초기화 할때 쓰려고 선언했습니다.	//
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAddr, clntAddr;
	char revbuf[LENGTH]; // Receiver buffer
	int success = 0;
	int szClntAddr;

	//sbjz_main();


	if (argc != 2) {	//	포트정보가 입력되었는지 여부 검사	//
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	//	윈속 2.2사용 초기화	//
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)	//	Error check	//
		exit(1);
	else
		printf("[Server] Winsock2.2 Configuring is successfully\n");

	//	소켓을 생성합니다.	//
	hServSock = socket(AF_INET, SOCK_STREAM, 0);	//	TCP socket	//
	if (hServSock == INVALID_SOCKET)
		exit(1);
	else
		printf("[Server] Creating socket successfully\n");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;			//	TCP를 사용합니다.	//
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);	//	모든 IP를 받아줍니다.	//
	servAddr.sin_port = htons(atoi(argv[1]));	//	포트 정보	//
												//  host to network short

	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)	//	소켓에 주소를 부여합니다.	//
		exit(1);
	else

		printf("[Server] Binded tcp port %d in addr host successfully.\n", PORT);

	if (listen(hServSock, 10) == SOCKET_ERROR)	//	소켓대기상태로 만듭니다, 동시에 10명까지 가능합니다.	//
		exit(1);
	else
		printf("[Server] Listening the port %d successfully.\n", PORT);

	while (success == 0)
	{
		szClntAddr = sizeof(SOCKADDR_IN);

		/* Wait a connection, and obtain a new socket file despriptor for single connection */
		if ((hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr)) == SOCKET_ERROR)
		{
			fprintf(stderr, "ERROR: Obtaining new Socket Despcritor. (errno = %d)\n", errno);
			exit(1);
		}
		else
			printf("[Server] Server has got connected from Clinet.\n");// inet_ntoa(addr_remote.sin_addr));

																	   /*	Receive File from Client(show console)	*/
																	   //int fr_block_sz = 0;
																	   //while ((fr_block_sz = recv(hClntSock, revbuf, LENGTH, 0)) > 0)
																	   //{
																	   //	printf(revbuf);
																	   //}
																	   /*	Receive File from Client(save text)		*/
		const char* fr_one = "C:/Users/ksy/Desktop/one.txt";
		const char* fr_two = "C:/Users/ksy/Desktop/two.txt";
		const char* fr_three = "C:/Users/ksy/Desktop/three.txt";
		const char* fr_four = "C:/Users/ksy/Desktop/four.txt";

		FILE *fr;




		/*

		if (fr1 == NULL)
			printf("File %s Cannot be opened file on server.\n", fr1);
		else if(fr2 == NULL)
			printf("File %s Cannot be opened file on server.\n", fr2);
		else if(fr3==NULL)
			printf("File %s Cannot be opened file on server.\n", fr3);
		else if(fr4==NULL)
			printf("File %s Cannot be opened file on server.\n", fr4);
		*/

		//else{
			memset(revbuf, LENGTH, '0');
			int fr_block_sz = 0;
			while ((fr_block_sz = recv(hClntSock, revbuf, LENGTH, 0)) > 0)
			{
				if (!strncmp(&revbuf[0],"1",1)) {
					fr = fopen(fr_one, "w");
					check_one = 1;
				}
				else if (!strncmp(&revbuf[0], "2",1)) {
					fr = fopen(fr_two, "w");
					check_two = 1;
				}
				else if (!strncmp(&revbuf[0], "3",1)) {
					fr = fopen(fr_three, "w");
					check_three = 1;
				}
				else {
					fr = fopen(fr_four, "w");
					check_four = 1;
				}
				int write_sz1 = fwrite(revbuf, sizeof(char), fr_block_sz, fr);
				if (write_sz1 < fr_block_sz)
				{
					exit(1);
				}

				memset(revbuf, LENGTH, '0');
				if (check_one + check_two + check_three + check_four == 4) {
					sbjz_main();
					check_one = 0;
					check_two = 0;
					check_three = 0;
					check_four = 0;
				}
				if (fr_block_sz == 0 || fr_block_sz != 1024)
				{
					break;
				}
			}
		//}
		fclose(fr);
	}
	return 0;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
