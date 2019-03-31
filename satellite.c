/*
���������Ϊ�Ƕ��ƣ�Ŀǰalpha�������¼���
*/

#include<stdio.h>
#include<math.h>
#define pi 3.1415926535897932384626
#define G 6.67259e-11  //GΪ����������mΪ��������
#define m 5.965e24
double alpha = 40; //��ǰʱ�̵ĸ������κ���ʱ��alpha�������ֵ���������ϵ��x��ļнǣ��������κ���ʱ����Ҫ���ݵ�ǰʱ��������㣩
double L, B; //���µ�ľ���L��γ��B

void location(double a, double e, double i, double omega, double w, double M0, double t){
	i = i / 90 * (pi / 2);
	w = w / 90 * (pi / 2);
	omega = omega / 90 * (pi / 2);
	M0 = M0 / 90 * (pi / 2);
	alpha = alpha / 90 * (pi / 2); //���Ƕȶ�ת��Ϊ������
	double M, n; //tʱ�̵�ƽ�����M������ƽ�����ٶ�n
	n = sqrt(G * m / pow(a, 3));
	M = M0 + n * t;
	double E = 1, E0 = 0; //��ʼ��ƫ�����E
	while(fabs(E0 - E) > 1e-6){
		E = E0 -(E0 - M - e * sin(E0))/(1 - e * cos(E0));
		E0 = E;
	} //������⿪���շ��̣�����ƫ�����E
	double xx, yy, zz; //�����ڹ������ϵ�е�����
	double b = a * sqrt(1 - e * e);
	xx = a * cos(E) - a * e;
	yy = b * sin(E);
	zz = 0;
	double x, y, z; //�������ϵ���ӹ������ϵת�����������ϵ
	x = xx * (cos(w) * cos(omega - alpha) - sin(w) * cos(i) * sin(omega - alpha)) + yy * (- sin(w) * cos(omega - alpha) - cos(w) * cos(i) * sin(omega - alpha)) + zz * (sin(i) * sin(omega - alpha));
	y = xx * (cos(w) * sin(omega - alpha) + sin(w) * cos(i) * cos(omega - alpha)) + yy * (- sin(w) * sin(omega - alpha) + cos(w) * cos(i) * cos(omega - alpha)) + zz * (- sin(i) * cos(omega - alpha));
	z = xx * (sin(w) * sin(i)) + yy * (cos(w) * sin(i)) + zz * cos(i);
	double theta = atan((z * a)/(b * sqrt(x * x + y * y)));
	double e_square = (a * a - b * b)/(a * a), ee_square = (a * a - b * b)/(b * b);
	L = atan(y / x) / (pi / 2) * 90; //�õ���γ��
	B = atan((z + ee_square * b * pow(sin(theta), 3)) / (sqrt(x * x + y * y) - e_square * a * pow(cos(theta), 3))) / (pi / 2) * 90;
}

int main(){
	double a, e, i, omega, w, M0, t; //����볤��a�����ƫ����e��������i��������ྭomega�����ص����w��t0ʱ��ƽ�����M0��ʱ��t
	scanf("%lf %lf %lf %lf %lf %lf %lf", &a, &e, &i, &omega, &w, &M0, &t); //��������������ʱ��t
	location(a, e, i, omega, w, M0, t);
	printf("%lf %lf\n", L, B);
	return 0;
}