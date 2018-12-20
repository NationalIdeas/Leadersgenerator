//Normal Distribution Function;
#include "stdafx.h"

namespace DistFunction
{
#define  PI 3.14159265354
double Normal(double x,double miu,double sigma) //概率密度函数;
{
	return 1.0/sqrt(2*PI*sigma) * exp(-1*(x-miu)*(x-miu)/(2*sigma*sigma));
}
double NormalRandom(double miu,double sigma,double min,double max)//产生正态分布随机数;
{
	double x;
	double dScope;
	double y;
	do
	{
		x = AverageRandom(min,max); 
		y = Normal(x, miu, sigma);
		dScope = AverageRandom(0, Normal(miu,miu,sigma));
	}while( dScope > y);
	return x;
}
double AverageRandom(double min,double max)
{
	int ret;
	UINT n = 0;
	ret = rand_s(&n);
	return (((double) n / MAXUINT) * (double)max + (double)min);
}


double NormalRand(double Variance,double Expect)
{
	double V1,V2,S;
	int phase = 0;
	double Y;
	int ret;
	UINT n = 0;
	ret = rand_s(&n);
	if ( phase == 0 ) {
		do {
			double U1 = (double)n / UINT_MAX;
			double U2 = (double)n / UINT_MAX;
			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S = V1 * V1 + V2 * V2;
		} while(S >= 1 || S == 0);
		Y = V1 * sqrt(-2 * log(S) / S);
	} else
		Y = V2 * sqrt(-2 * log(S) / S);
	phase = 1 - phase;
	Y = Y * Variance + Expect;
	return Y;
}






}