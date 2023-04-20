#include "DES.h"

int S[8][64] = {
	{ 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,0,15,7,4,15,2,13,1,10,6,12,11,9,5,3,8,4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 },
	{ 15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 },
	{ 10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 },
	{ 7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,12,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 },
	{ 2,12,4, 1,7,10,11,6,8,5,3,15,13,0,14,9,14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 },
	{ 12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 },
	{ 4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 },
	{ 13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 }
};

bitset<64>  StrToBit(string a)//字符转bit类型
{
	bitset<64> bits;
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
		{
			bits[8 * i + (7 - j)] = ((a[i] >> j) & 1);
		}
	return bits;
}

bitset<64> even_check(bitset<64> a)//补充校验位
{
	bitset<64> bits;
	for (int i = 0; i < 8; i++)
	{
		bool temp = 0;
		for (int j = 0; j < 7; j++)
		{
			bits[i * 8 + j] = a[i * 8 + j];
			temp = temp ^ a[i * 8 + j];
		}
		bits[i * 8 + 7] = temp;
	}
	return bits;
}

void show_bit(bitset<64> a)//展示输出bit
{
	for (int i = 0; i < 64; i++)
	{
		break;//cout << a[i];
	}
	//cout << endl;
}

void DES::get_key(bitset<64> in)//获得密钥
{
	/*string a;//= "0001001100110100010101110111100110011011101111001101111111110001";//"0001001100110100010101110111100110011011101111001101111111110001";
	getline(cin, a);
	bitset<64> or_key = StrToBit(a);

	for (int i = 0; i < 64; i++)
	{
		or_key[i] = (a[ i] == '1');
	}*/
	bitset<64> or_key = in;
	//cout << "原始密钥：";
	show_bit(or_key);
	s_key = even_check(or_key);
	//s_key = or_key;
	//cout << "校验后的密钥：";
	show_bit(s_key);
}

bitset<56> DES::key_IP_change(bitset<64>in)//密钥经过IP盒变化
{
	bitset<56> son_key;
	int K_IP[56] = { 57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,
		60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4 };
	for (int i = 0; i < 56; i++)
	{
		son_key[i] = s_key[(K_IP[i]) - 1];
	}
	return son_key;
}

void DES::get_key_CD(bitset <56> son_key, bitset<28> key_C[17], bitset<28> key_D[17])//获得密钥的分组CD
{
	for (int i = 0; i < 28; i++)
		key_C[0][i] = son_key[i];
	for (int i = 28; i < 56; i++)
		key_D[0][i - 28] = son_key[i];
	int left_move_n = 0;
	for (int i = 1; i < 17; i++)
	{
		int temp;
		if (i == 1 || i == 2 || i == 9 || i == 16)
			temp = 1;
		else
			temp = 2;
		left_move_n += temp;
		for (int CDi = 0, j = left_move_n; j < left_move_n + 28; CDi++, j++)
		{
			key_C[i][CDi] = key_C[0][j % 28];
			key_D[i][CDi] = key_D[0][j % 28];
		}
	}
}

void DES::get_16_son_key_48(bitset<28> key_C[17], bitset<28> key_D[17])//得到16个48长度的密钥
{
	int change[48] = { 14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,
		20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32 };
	for (int i = 0; i < 16; i++)
	{
		bitset<56> temp;
		for (int j = 0; j < 28; j++)
			temp[j] = key_C[i + 1][j];
		for (int k = 28; k < 56; k++)
			temp[k] = key_D[i + 1][k - 28];
		for (int t = 0; t < 48; t++)
		{
			r_son_key[i][t] = temp[change[t] - 1];
		}
	}
}

void DES::get_all_key()//得到所有的密钥
{
	bitset<56>temp;
	temp = key_IP_change(s_key);

	//cout << endl;
	bitset<28> key_C[17];
	bitset<28> key_D[17];
	get_key_CD(temp, key_C, key_D);
	/*for (int j = 0; j < 17; j++)
	{
		//cout <<  j << " : ";
		for (int i = 0; i < 28; i++)
			//cout << key_C[j][i];
		//cout <<"   " <<j << " : ";
			for (int i = 0; i < 28; i++)
				;//cout << key_D[j][i];
			//cout << endl;
	}*/
	get_16_son_key_48(key_C, key_D);
}


void DES::get_txt(bitset<64> in)//输入加密的txt
{
	/*string a;// = "0000000100100011010001010110011110001001101010111100110111101111";
	getline(cin, a);
	txt= StrToBit(a);
	for (int i = 0; i < 64; i++)
	{
		txt[i] = (a[i] == '1');
	}*/
	txt = in;
	//cout << endl << "原始明文：";
	show_bit(txt);
}

bitset<64> DES::IP_change(bitset<64> in)//对输入进行IP盒变换
{
	bitset<64> res;
	int ip[64] = { 58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,
				  25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7 };
	if (!is_decode)
	{
		for (int i = 0; i < 64; i++)
		{
			res[i] = in[ip[i] - 1];
		}
	}
	else
	{
		for (int i = 0; i < 64; i++)
		{
			res[ip[i] - 1] = in[i];
		}
	}
	return res;
}

bitset<32> DES::xor_32(bitset<32> a, bitset<32> b)//32位bit的数据进行异或
{
	bitset<32>res;
	for (int i = 0; i < 32; i++)
	{
		res[i] = a[i] ^ b[i];
	}
	return res;
}

void DES::separate(bitset<64>in, bitset<32>& l_txt, bitset<32>& r_txt)//将in对半分成l_txt和r_txt
{
	for (int i = 0; i < 32; i++)
		l_txt[i] = in[i];
	for (int i = 32; i < 64; i++)
		r_txt[i - 32] = in[i];
}

bitset<64> DES::IP_1_change(bitset<64> in)//进行另一种IP变换
{
	int ip[64] = { 40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,36,4,44,12,
					52,20,60,28,35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25 };
	bitset<64> res;
	if (is_decode)
	{
		for (int i = 0; i < 64; i++)
		{
			res[ip[i] - 1] = in[i];
		}
	}
	else
	{
		for (int i = 0; i < 64; i++)
		{
			res[i] = in[ip[i] - 1];
		}
	}
	return res;
}

bitset<48> DES::TO_48(bitset<32> right_txt)//将32位的输入变为48位
{
	int To_rule[48] = { 32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,
		19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1 };
	bitset<48> ex_txt;
	for (int i = 0; i < 48; i++)
	{
		ex_txt[i] = right_txt[To_rule[i] - 1];
	}
	return ex_txt;
}

bitset<48> DES::XOR(bitset<48> ex_48, bitset<48> key)//48位的进行异或
{
	bitset<48> xor_res;
	for (int i = 0; i < 48; i++)
	{
		xor_res[i] = ex_48[i] ^ key[i];
	}
	return xor_res;
}

bitset<32> DES::S_change(bitset<48> xor_res)//S盒变换
{
	bitset<6> temp[8];
	bitset<32> S_res;
	for (int i = 0; i < 48; i++)
	{
		temp[i / 6][i % 6] = xor_res[i];
	}
	for (int i = 0; i < 8; i++)
	{
		//cout << "S" << i + 1 << ":  ";
		int row, col;
		row = 2 * temp[i][0] + temp[i][5];
		col = 8 * temp[i][1] + 4 * temp[i][2] + 2 * temp[i][3] + temp[i][4];
		int chose = S[i][row * 16 + col];
		//cout << "row:" << row << "   col:" << col <<"  chose:"<< chose <<endl;
		for (int j = 0; j < 4; j++)
		{
			S_res[4 * i + 3 - j] = (chose >> j) & 1;
		}

	}
	return S_res;
}

bitset<32> DES::IP_change2(bitset<32>S_res)//另一种IP变换
{
	bitset<32> f_out;
	int ip[32] = { 16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25 };
	for (int i = 0; i < 32; i++)
	{
		f_out[i] = S_res[ip[i] - 1];
	}
	return f_out;
}

bitset<32> DES::f(bitset<32>a, bitset<48> key)//F函数，整合了上面的一些运算
{
	bitset<48>ex_48, xor_res;
	bitset<32>S_res, f_out;
	ex_48 = TO_48(a);
	xor_res = XOR(ex_48, key);
	S_res = S_change(xor_res);
	f_out = IP_change2(S_res);
	/*cout << "拓展到48位：";
	for (int i = 0; i < 48; i++)
		cout << ex_48[i];
	cout << endl;
	cout << "拓展之后异或的结果：";
	for (int i = 0; i < 48; i++)
		cout << xor_res[i];
	cout << endl;
	cout << "S盒操作完后：";
	for (int i = 0; i < 32; i++)
		cout << S_res[i];
	cout << endl;
	cout << "再次IP置换后：";
	for (int i = 0; i < 32; i++)
		cout << f_out[i];
	cout << endl;*/
	return f_out;
}

bitset<64> DES::merge_once_res(bitset<32>right_txt, bitset<32>xor_res, int n)//将输入进行拼接
{
	bitset<64>res;
	if (n != 15)
	{
		for (int i = 0; i < 32; i++)
			res[i] = right_txt[i];
		for (int i = 32; i < 64; i++)
		{
			res[i] = xor_res[i - 32];
		}
	}
	else
	{
		for (int i = 0; i < 32; i++)
			res[i] = xor_res[i];
		for (int i = 32; i < 64; i++)
		{
			res[i] = right_txt[i - 32];
		}
	}
	return res;
}

bitset<64>DES::once(bitset<64> in, bitset<48>key, int n)//对in使用key进行一轮的完整加密，加密结果返回
{
	bitset<32> left_txt;
	bitset<32> right_txt;
	bitset<32>f_out, xor_res;
	bitset<64>res;
	separate(in, left_txt, right_txt);
	if (!is_decode || n == 15)//注意最后一轮有所不同
	{
		f_out = f(right_txt, key);
		xor_res = xor_32(left_txt, f_out);
		res = merge_once_res(right_txt, xor_res, n);
		return res;
	}
	else
	{
		f_out = f(left_txt, key);
		xor_res = xor_32(right_txt, f_out);
			res = merge_once_res(xor_res, left_txt, n);
		return res;
	}
}

void DES::oper_16()//操作16次，进行完整加密
{
	bitset<64>temp;
	temp = IP_change(txt);
	show_bit(temp);
	for (int i = 0; i < 16; i++)
	{
		temp = once(temp, r_son_key[i], i);
	}
	des_res = IP_1_change(temp);
}

void DES::get_ctxt(bitset<64> in)//输入密文
{
	c_txt = in;
	//cout << endl << "原始密文：";
	show_bit(txt);
}


void DES::decode()//解密
{
	is_decode = 1;
	bitset<64>temp;
	temp = IP_1_change(c_txt);
	for (int i = 15; i >= 0; i--)
	{
		temp = once(temp, r_son_key[i], i);
	}
	decode_res = IP_change(temp);
}

bitset<64> axor(bitset<64> a, bitset<64> b)//64位的异或
{
	bitset<64> res;
	for (int i = 0; i < 64; i++)
	{
		res[i] = a[i] ^ b[i];
	}
	return res;

}

bitset<64> three_des(bitset<64> in, DES des1, DES des2)//3轮交替的des加密、解密
{
	des1.get_txt(in);
	des1.oper_16();

	des2.get_ctxt(des1.des_res);
	des2.decode();

	des1.get_txt(des2.decode_res);
	des1.oper_16();

	return des1.des_res;
}

void des_opera(bitset<64>* x, int m)//得到m个64位的bit数组，放入到x中
{
	//密钥直接固定死，全靠时间的不同产生随机
	string ss;
	ss = "987654a3210";
	bitset<64> s = StrToBit(ss);
	show_bit(s);

	string s1;
	s1 = "oiuyfcvbjyfdcv";
	bitset<64> or_key1 = StrToBit(s1);

	string s2;
	s2 = "rewqasfgfdcghy";
	bitset<64> or_key2 = StrToBit(s2);

	char local_time[8];
	SYSTEMTIME st = { 0 };
	char a[10];
	GetLocalTime(&st);  //获取当前时间 精确到ms
	sprintf(a, "%2d%2d%2d%3d",st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
	for (int i = 0; i < 8; i++)
	{
		if (a[i] == ' ')
			a[i] = '0';
		local_time[i] = a[i];
	}
	bitset<64> key_time = StrToBit(local_time);

	DES des1;
	des1.get_key(or_key1);
	des1.get_all_key();
	DES des2;
	des2.get_key(or_key2);
	des2.get_all_key();

	bitset<64> I = three_des(key_time, des1, des2);
	bitset<64> I_xor_s;
	for (int k = 0; k < m; k++)
	{
		I_xor_s = axor(I, s);
		bitset<64> xt = three_des(I_xor_s, des1, des2);
		x[k] = xt;
		bitset<64> x_xor_I = axor(xt, I);
		s = three_des(x_xor_I, des1, des2);
	}
}

ZZ random_ZZ(int n)//获得对应n个bit大小的随机数
{
	ZZ res = ZZ(0), t = ZZ(1);
	int m = n / 64;
	bitset<64>* x = new bitset<64>[m];
	des_opera(x, m);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			if (x[i][j] == 1)
			{
				res += t;
			}
			t = t << 1;
		}
	}
	return res;
}
/*
int mtest()//测试
{
	ZZ r = random_ZZ(512);
	cout << "随机数为：" << endl;
	bitset<4> t = 3;
	cout << r;
	return 0;
}
*/