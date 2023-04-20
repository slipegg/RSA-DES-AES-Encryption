#include <iostream>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;
ZZ random_ZZ(int n);

int get_Z_n(ZZ a)
{
	int Z_n = 0;//7:111
	while (a != 0)
	{
		a = a >> 1;
		Z_n++;
	}
	return Z_n;
}

ZZ get_j(ZZ b,ZZ c, ZZ n)
{
	ZZ flag = ZZ(1), temp ;
	int Z_c = get_Z_n(c);
	//cout << "Z_n:" << Z_n << endl;
	ZZ* t = new ZZ[Z_c];
	ZZ k=b;
	t[0] = k;
	for (int i = 1; i < Z_c; i++)
	{
		t[i] = (t[i - 1] * t[i - 1]) % n;
	}
	ZZ sum  = ZZ(1);
	temp = c;
	for (int i = 0; i < Z_c; i++)
	{
		//cout <<i <<":"<< temp << endl;
		ZZ f = temp % ZZ(2);
		if (f == ZZ(1))
		{
			sum = (sum*t[i])%n;
		}
		temp = temp >> 1;
	}

	return sum;
}


int jacobi(ZZ a, ZZ n)
{
	ZZ  e = ZZ(0), a1, n1;
	int s;
	if (0 == a || 1 == a)
		return 1;
	ZZ temp = a;

	while (temp % 2 == 0)
	{
		temp =temp>>1;
		e++;
	}

	a1 = temp;
	if (0 == e % 2)
		s = 1;
	else
	{
		if (1 == n % 8 || 7 == n % 8)
			s = 1;
		else if (3 == n % 8 || 5 == n % 8)
			s = -1;
	}
	if (3 == n % 4 && 3 == a1 % 4)
		s = -s;
	n1 = n % a1;
	if (1 == a1)
		return s;
	else
		return s * Jacobi(n1, a1);
}

ZZ get_prim(int Z_n)
{
	cout << "查找素数中..." << endl;
	ZZ n;
	int find_sum = 0;
	while (1)
	{
		bool is_find = true;
		n = random_ZZ(Z_n);
		if (n % 2 == 0||n%5==0)
			continue;
		find_sum++;
		if (find_sum % 10 == 0 && find_sum != 0)
			cout << "已查找随机数" << find_sum << "次" << endl;
		for (int i = 0; i < Z_n; i++)
		{
			ZZ b;
			while (1)
			{
				b = (random_ZZ(Z_n)) % n;
				if (b > 0)
					break;
			}

			ZZ j = get_j(b, (n - 1) / 2, n);
			if (j != 1 && j != n - 1)
			{
				is_find = false;
				break;
			}
			int jac_res = jacobi(b, n);
			if ((n + jac_res) % n != j)
			{
				is_find = false;
				break;
			}
		}
		if (is_find)
		{
			cout << "找到一个素数!" << endl;
			return n;
		}
	}
}