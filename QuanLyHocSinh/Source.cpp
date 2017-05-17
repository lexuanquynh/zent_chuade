#include<iostream>
#include <conio.h>
#include <fstream>

#define TEN_FILE "hocsinh.data"
#define TEXT_FILE "ketqua1.txt"

using namespace std;

//Dinh nghia cau truc hoc sinh
typedef struct Hocsinh
{
	int mahs;
	char ho[20];
	char ten[20];
	float diemTB;
	int hanhkiem;
} Hocsinh;

enum {
	YEU = 0,
	TRUNG_BINH = 1,
	KHA = 2,
	TOT = 3
};

enum {
	NO,
	YES
};

void nhapHocSinh()
{
	int soluong;
	Hocsinh hocsinh;
	ofstream output_file(TEN_FILE, ios::app | ios::binary | ios::ate);

	if (output_file.is_open())
	{
		cout << "So luong hoc sinh can nhap: " << endl;
		cin >> soluong;

		for (int i = 0; i < soluong; i++) 
		{
			cout << "Nhap ma hoc sinh: ";
			cin >> hocsinh.mahs;

			cout << "Nhap ho: ";
			cin.ignore();
			cin.getline(hocsinh.ho, 20);

			cout << "Nhap ten: ";
			cin.getline(hocsinh.ten, 20);


			cout << "Nhap diemTB: ";
			cin >> hocsinh.diemTB;
			cin.ignore();

			cout << "Nhap hanh kiem:\nYEU = 0\nTRUNGBINH = 1\nKHA = 2\nGIOI = 3 ";
			cin >> hocsinh.hanhkiem;

			output_file.write((char*)&hocsinh, sizeof(Hocsinh));
		}

		output_file.close();
	}
	else 
	{
		cout << "Khong the mo file!" << endl;
	}
}

void hienThiHocSinh(const Hocsinh hocsinh)
{
	cout << hocsinh.mahs << " " << hocsinh.ho << " " << hocsinh.ten << " "
		<< hocsinh.diemTB << " " << hocsinh.hanhkiem << endl;
}

void hienthiHocSinh()
{
	ifstream input_file(TEN_FILE, ios::binary);
	Hocsinh hocsinh;

	if (input_file.is_open())
	{
		while (!input_file.eof())
		{
			input_file.read((char*)&hocsinh, sizeof(Hocsinh));
			
			if (input_file.eof()) break;

			hienThiHocSinh(hocsinh);
		}

		input_file.close();
	}
	else {
		cout << "Khong the mo file!" << endl;
	}
}

int soLuongHocBong()
{
	// Reading and writing binary file
	ifstream input_file(TEN_FILE, ios::binary);
	ofstream output_file(TEN_FILE, ios::app | ios::binary | ios::ate);
	Hocsinh hocsinh;
	int soluongHB = 0;

	if (input_file.is_open())
	{
		cout << "Danh sach dat hoc bong:" << endl;

		while (!input_file.eof() && output_file.is_open())
		{
			input_file.read((char*)&hocsinh, sizeof(Hocsinh));
			
			if (input_file.eof()) break;

			if (hocsinh.diemTB > 8.5 && hocsinh.hanhkiem == TOT)
			{
				soluongHB++;
				hienThiHocSinh(hocsinh);
			}


		}

		if (soluongHB == 0)
			cout << "Khong co hoc sinh nao dat hoc bong!" << endl;

		//ghi so luong vao cuoi file
		//output_file.write((char*)&soluongHB, sizeof(int));

		output_file.close();
		input_file.close();
	}

	return soluongHB;
}

void timHocSinh(float diemTBMin, float diemTBMax, int hanhkiem)
{
	ifstream input_file(TEN_FILE, ios::binary);
	ofstream output_file(TEN_FILE, ios::app | ios::binary | ios::ate);
	Hocsinh hocsinh;
	int timthay = NO;

	if (input_file.is_open())
	{
		cout << "Danh sach hoc sinh diemTB tu 7->8 va hoc luc KHA: " << endl;

		while (!input_file.eof() && output_file.is_open())
		{
			input_file.read((char*)&hocsinh, sizeof(Hocsinh));
			
			if (input_file.eof()) break;

			if (hocsinh.diemTB >= diemTBMin && hocsinh.diemTB <= diemTBMax
				&& hocsinh.hanhkiem == KHA)
			{
				timthay = YES;

				hienThiHocSinh(hocsinh);

			}

			//ghi vao cuoi file
			//	output_file.write((char*)&hocsinh, sizeof(hocsinh));
		}

		if (timthay == NO)
			cout << "Khong tim thay!" << endl;

		input_file.close();
		output_file.close();
	}
	else {
		cout << "Khong the mo file!" << endl;
	}
}

void traoDoi(Hocsinh &hocsinhA, Hocsinh &hocsinhB)
{
	Hocsinh temp;

	temp = hocsinhA;
	hocsinhA = hocsinhB;
	hocsinhB = temp;
}

void sapXepTheoChieuTangdiemTBTB()
{
	ifstream input_file(TEN_FILE, ios::binary);
	ofstream output_file(TEXT_FILE);
	Hocsinh hocsinh[100];
	int soluong = 0;

	if (input_file.is_open())
	{
		//doc tat ca cac hoc sinh ra mang 
		while (!input_file.eof())
		{
			//doc toan bo hoc sinh ra struct de tien hanh sap xep

			input_file.read((char*)&hocsinh[soluong], sizeof(Hocsinh));

			if (input_file.eof()) break;

			soluong++;

			//	output_file.write((char*)&hocsinh, sizeof(hocsinh));
		}

		//tien hanh sap xep theo chieu tang diem trung binh
		//noi bot
		for (int i = 0; i < soluong; i++)
			for (int j = soluong - 1; j > i; j--) {
				if (hocsinh[i].diemTB > hocsinh[j].diemTB)
				{
					traoDoi(hocsinh[i], hocsinh[j]);
				}
			}

		//in ra sau khi sap xep
		if (input_file.eof()) {
			for (int i = 0; i < soluong; i++)
			{
				hienThiHocSinh(hocsinh[i]);

				//ghi ra file
				output_file << hocsinh[i].mahs << " " << hocsinh[i].ho << " " <<
					hocsinh[i].ten << " " << hocsinh[i].diemTB << " " << hocsinh[i].hanhkiem << endl;
			}

			output_file.close();
		}



		input_file.close();

	}
	else {
		cout << "Khong the mo file!" << endl;
	}
}

void Menu()
{
	int chonlua;

	while (1)
	{
		//Doc danh sach
		cout << "Chon chuc nang: " << endl;
		cout << "1. Nhap danh sach hoc sinh" << endl;
		cout << "2. Doc danh sach hoc sinh" << endl;
		cout << "3. Dem so luong hoc sinh dat hoc bong" << endl;
		cout << "4. Tim kiem hoc sinh co diemTB tu 7->8 va hoc luc KHA" << endl;
		cout << "5. Sap xep danh sach hoc sinh theo chieu tang cua diemTB" << endl;

		cout << "Chon lua cua ban: ";
		cin >> chonlua;

		switch (chonlua)
		{
		case 1:
			nhapHocSinh();
			break;
		case 2:
			hienthiHocSinh();
			break;
		case 3:
			soLuongHocBong();
			break;
		case 4:
			timHocSinh(7, 8, KHA);
			break;
		case 5:
			sapXepTheoChieuTangdiemTBTB();
		default:
			exit(0);
			break;
		}

		getch();
		system("cls");
	}
}

int main()
{
	Menu();

	return 0;
}