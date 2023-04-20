#include <iostream>
#include<string>
#include <cstdlib>
#include <fstream>
#include <bitset>
#include <NTL/ZZ.h>
#include <windows.h>
using namespace std;
using namespace NTL;
ZZ random_ZZ(int n);
ZZ get_prim(int Z_n);
int get_Z_n(ZZ a);

void Euclidean(ZZ a, ZZ b,ZZ &gcd,ZZ &t)//gcd是a和b的公因数，如果gcd=1，t就是b的逆元
{
	ZZ a0 = a;
	if (b > a)
	{
		ZZ temp = a;
		a = b;
		b = temp;
	}
	ZZ t0 = ZZ(0);
	t = ZZ(1);
	ZZ q = a / b;
	gcd = a-q*b;
	ZZ temp;
	while (gcd>ZZ(0))
	{
		temp = (t0 - q * t)%a0;
		t0 = t;
		t = temp;
		a = b;
		b = gcd;
		q = a / b;
		gcd = a - q * b;
	}
	gcd = b;
}


ZZ Z_mul(ZZ b, ZZ c, ZZ n)//返回b的c次方模n
{
	if (c == 0)
		return ZZ(1);
	ZZ flag = ZZ(1), temp;
	int Z_c = get_Z_n(c);
	//cout << "Z_n:" << Z_n << endl;
	ZZ* t = new ZZ[Z_c];
	ZZ k = b;
	t[0] = k;
	for (int i = 1; i < Z_c; i++)
	{
		t[i] = (t[i - 1] * t[i - 1]) % n;
	}
	ZZ sum = ZZ(1);
	temp = c;
	for (int i = 0; i < Z_c; i++)
	{
		//cout <<i <<":"<< temp << endl;
		ZZ f = temp % ZZ(2);
		if (f == ZZ(1))
		{
			sum = (sum * t[i]) % n;
		}
		temp = temp >> 1;
	}
	return sum;
}

ZZ rsa_jiemi(ZZ y, ZZ a, ZZ n)//RSA解密
{
	ZZ x = Z_mul(y, a, n);
	return x;
}


//以下是测试过程使用的函数
/*
ZZ jiami_test(ZZ x,ZZ& p1,ZZ& q1,ZZ&n1 ,ZZ &f_n1,ZZ &a1,ZZ &b1)
{
	ZZ p = get_prim(512);// ZZ(101);
	ZZ q = get_prim(512);//ZZ(113);
	ZZ n = p * q;
	ZZ f_n = (p - 1) * (q - 1);
	ZZ gcd = ZZ(0), a, b;
	while (gcd != ZZ(1))
	{
		b = (random_ZZ(512)) % f_n;
		Euclidean(f_n, b, gcd, a);
	}
	ZZ y = Z_mul(x, b, n);
	p1 = p;
	q1 = q;
	f_n1 = f_n;
	a1 = a;
	b1 = b;
	n1 = n;
	return y;
}


int rsa_test()
{
	ZZ p =get_prim(512);// ZZ(104);
	ZZ q = get_prim(512);////ZZ(113);
	ZZ n = p * q;
	ZZ f_n = (p - 1) * (q - 1);
	ZZ gcd=ZZ(0), a ,b;
	while (gcd != ZZ(1))
	{
		b = (RandomBits_ZZ(512))%f_n;
		Euclidean(f_n, b, gcd, a);
		cout << "b=" << b << endl;
		cout << "gcd=" << gcd << endl;
	}
	cout << "公钥："<< endl << "n=" << endl << n << endl << "b=" << endl << b << endl;
	cout << "私钥：" << endl << "p=" << endl << p << endl << "q=" << endl << q << endl << "a=" << endl << a << endl;
	ZZ k = (RandomBits_ZZ(128))%n;
	cout << "k=" << endl << k << endl;;
	ZZ c1 = Z_mul(k, b, n);
	cout << "k^b mod n=" << endl << c1 << endl;
	ZZ c2 = Z_mul(c1, a, n);
	cout << "解密出k="<< endl << c2 << endl;
	return 0;
}*/