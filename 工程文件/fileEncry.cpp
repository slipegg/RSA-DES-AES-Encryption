#include"fileEncry.h"

void fileEncry::get_txt(string file_name)
{
	len = 0;
	fstream in(file_name, ios::in | ios::binary);
	while (!in)
	{
		cout << "û���ҵ�Ҫ���ܵ��ļ�������������" << endl;
		cin >> file_name;
		in.open(file_name, ios::in | ios::binary);
	}
	in.seekg(0, std::ios::end);
	len = in.tellg();
	in.seekg(0, std::ios::beg);
	txt = new char[len + 20];
	in.read(txt, len);
	in.close();
	int temp = 16 - len % 16;
	if (len % 16 == 0)
	{
		for (int i = 0; i < 16; i++)
			txt[len++] = char(0);
	}
	else
	{
		while (len % 16 != 0)
		{
			txt[len++] = char(temp);
		}
	}
	txt[len] = '\0';
}

void fileEncry::decry_get_txt(string file_name)//�õ������ļ�
{
	fstream fin(file_name, ios::in | ios::binary);
	while (!fin)
	{
		cout << "û���ҵ�Ҫ���ܵ��ļ�������������" << endl;
		cin >> file_name;
		fin.open(file_name, ios::in | ios::binary);
	}
	fin.seekg(0, std::ios::end);    // go to the end  
	int tlen = fin.tellg();           // report location (this is the length)  
	fin.seekg(0, std::ios::beg);    // go back to the beginning  
	encry_txt = new byte[tlen + 20];    // allocate memory for a buffer of appropriate dimension  
	char t1;
	int sum = 0;
	len = 0;
	for (int i = 0; i < tlen; i++)
	{
		t1 = fin.get();
		if (len % 2 == 0)
		{
			if (t1 <= '9')
			{
				sum += (t1 - '0') * 16;
			}
			else
			{
				sum += (t1 - 'a' + 10) * 16;
			}
		}
		else
		{
			if (t1 <= '9')
			{
				sum += (t1 - '0');
			}
			else
			{
				sum += (t1 - 'a' + 10);
			}
			encry_txt[len / 2] = byte(sum);
			sum = 0;
		}
		len++;
	}
	//show_byte(encry_txt, len / 2);
}

void fileEncry::get_fkey(string file_name)//�õ�AES��Կ
{
	int sum = 0;
	char t;
	fstream in;
	in.open(file_name, ios::in);
	while (!in)
	{
		cout << "û���ҵ�AES��Կ�ļ�������������" << endl;
		cin >> file_name;
		in.open(file_name, ios::in);
	}
	for (int i = 0; i < 32; i++)
	{
		t = in.get();
		if (i % 2 == 0)
		{
			if (t <= '9')
			{
				sum += (t - '0') * 16;
			}
			else
			{
				sum += (t - 'a' + 10) * 16;
			}
		}
		else
		{
			if (t <= '9')
			{
				sum += (t - '0');
			}
			else
			{
				sum += (t - 'a' + 10);
			}
			fkey[i / 2] = byte(sum);
			sum = 0;
		}
	}
	//show_byte(fkey, 16);
}

void fileEncry::encrye_txt(string file_name, string key_file_name)//�����ļ�
{
	get_txt(file_name);
	encry_key(key_file_name);
	string name = "����_";
	name = name + file_name;
	fstream fout(name, ios::out | ios::binary);
	AES aes;
	byte p[16], out[16];
	byte y[16];
	for (int i = 0; i < 16; i++)
		y[i] = byte(0);
	for (int i = 0; i < len / 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			p[j] = txt[i * 16 + j] ^ y[j];
		}
		aes.aes(p, fkey, out);
		char s[16] = { '0','1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
		for (int i = 0; i < 16 * 2; i++)
		{
			if (i % 2 == 0)
			{
				int temp = unsigned int(out[i / 2]) >> 4;
				fout << s[temp];
			}
			else
			{
				int temp = unsigned int(out[i / 2]) % 16;
				fout << s[temp];
			}
		}
		for (int i = 0; i < 16; i++)//CBC
			y[i] = out[i];
	}
	fout.close();
}

void fileEncry::decry_txt(string file_name, string key_file_name)//ʹ��AES��Կ���ļ����н���
{
	decry_get_txt(file_name);
	decry_key(key_file_name);
	string name = "����_";
	name = name + file_name;
	fstream fout(name, ios::out | ios::binary);
	AES aes;
	byte y[16];
	for (int i = 0; i < 16; i++)
		y[i] = byte(0);
	for (int j = 0; j < len / 32; j++)
	{
		byte temp[16], res[16];
		for (int k = 0; k < 16; k++)
		{
			temp[k] = encry_txt[j * 16 + k];
		}
		aes.aes_decode(temp, fkey, res);
		for (int i = 0; i < 16; i++)
		{
			res[i] = res[i] ^ y[i];
			y[i] = temp[i];
		}
		if (j == len / 32 - 1)
		{
			int last_i = res[15];
			if (last_i == 0)
				break;
			else
			{
				for (int k = 0; k < 16 - last_i; k++)
				{
					fout.put(res[k]);
				}
			}
		}
		else
		{
			for (int k = 0; k < 16; k++)
			{
				fout.put(res[k]);
			}
		}
	}
	fout.close();
}

ZZ fileEncry::encry_key(string key_file_name)//��ȡ�ļ�����ȡ��Կ��������Կ
{
	get_fkey(key_file_name);
	fstream in("��Կ.txt", ios::in);
	if (!in)
	{
		cout << "û���ҵ���Կ�ļ�����ȷ���������ɹ�Կ.txt" << endl;
		char t = _getch();
		exit(0);
	}
	string t;
	in >> t;
	in >> n;
	in >> t;
	in >> b;
	ZZ res = ZZ(0), temp = ZZ(1);
	for (int i = 0; i < 16; i++)
	{
		res += temp * fkey[i];
		temp <<= 8;
	}
	ZZ y = Z_mul(res, b, n);//RSA����
	string name = "����_";
	name = name + key_file_name;
	fstream out(name, ios::out);
	out << y;
	return y;
}

void fileEncry::decry_key(string key_file_name)//��ȡ˽Կ�����ܳ�AES��Կ
{
	ZZ y;
	fstream yin(key_file_name, ios::in);
	while (!yin)
	{
		cout << "û���ҵ�Ҫ���ܵ�AES��Կ�ļ�������������" << endl;
		cin >> key_file_name;
		yin.open(key_file_name, ios::in);
	}
	yin >> y;
	yin.close();
	fstream in("˽Կ.txt", ios::in);
	if (!in)
	{
		cout << "û���ҵ�˽Կ�ļ�����ȷ����������˽Կ.txt" << endl;

		char t = _getch();
		exit(0);
	}
	string t;
	in >> t;
	in >> n;
	in >> t;
	in >> a;
	ZZ x;
	x = rsa_jiemi(y, a, n);
	//cout << endl << x << endl;
	int temp = 256;
	for (int i = 0; i < 16; i++)
	{
		fkey[i] = byte(x % temp);
		x = x >> 8;
	}
}

void fileEncry::get_aRSA(int Z_n)//���һ��RSA��Կ
{
	ZZ p = get_prim(Z_n);
	ZZ q = get_prim(Z_n);
	ZZ n = p * q;
	ZZ f_n = (p - 1) * (q - 1);
	ZZ gcd = ZZ(0), a, b;
	while (gcd != ZZ(1))
	{
		b = (random_ZZ(Z_n)) % f_n;
		Euclidean(f_n, b, gcd, a);
	}
	ofstream ou("��Կ.txt", ios::out);
	ou << "n=" << endl << n << endl << "b=" << endl << b;
	ou.close();
	ofstream fou("˽Կ.txt", ios::out);
	fou << "n=" << endl << n << endl << "a=" << endl << a << endl << "p=" << endl << p << endl << "q=" << endl << q;
	fou.close();
}
void fileEncry::re_encrye_txt(string file_name, string key_file_name)
{
	get_txt(file_name);
	encry_key(key_file_name);
	string name = file_name;
	fstream fout(name, ios::out | ios::binary);
	AES aes;
	byte p[16], out[16];
	byte y[16];
	for (int i = 0; i < 16; i++)
		y[i] = byte(0);
	for (int i = 0; i < len / 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			p[j] = txt[i * 16 + j] ^ y[j];
		}
		aes.aes(p, fkey, out);
		char s[16] = { '0','1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
		for (int i = 0; i < 16 * 2; i++)
		{
			if (i % 2 == 0)
			{
				int temp = unsigned int(out[i / 2]) >> 4;
				fout << s[temp];
			}
			else
			{
				int temp = unsigned int(out[i / 2]) % 16;
				fout << s[temp];
			}
		}
		for (int i = 0; i < 16; i++)//CBC
			y[i] = out[i];
	}
	fout.close();
}
void fileEncry::re_decry_txt(string file_name, string key_file_name)
{
	decry_get_txt(file_name);
	decry_key(key_file_name);
	//cout << "��Կ��";
	//show_byte(fkey, 16);
	string name = file_name;
	//cout << name;
	fstream fout(name, ios::out | ios::binary);
	AES aes;
	byte y[16];
	for (int i = 0; i < 16; i++)
		y[i] = byte(0);
	for (int j = 0; j < len / 32; j++)
	{
		byte temp[16], res[16];
		for (int k = 0; k < 16; k++)
		{
			temp[k] = encry_txt[j * 16 + k];
		}
		//show_byte(temp, 16);
		aes.aes_decode(temp, fkey, res);
		for (int i = 0; i < 16; i++)
		{
			res[i] = res[i] ^ y[i];
			y[i] = temp[i];
		}
		if (j == len / 32 - 1)
		{
			int last_i = res[15];
			if (last_i == 0)
				break;
			else
			{
				for (int k = 0; k < 16 - last_i; k++)
				{
					fout.put(res[k]);
				}
			}
		}
		else
		{
			for (int k = 0; k < 16; k++)
			{
				fout.put(res[k]);
			}
		}
	}
	fout.close();
}