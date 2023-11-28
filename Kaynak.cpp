/********************************************************************************************************************************************
**					                                    SAKARYA �N�VERS�TES�											                   **
**			                                   B�LG�SAYAR VE B�L���M B�L�MLER� FAK�LTES�												   **
**				                                    B�LG�SAYAR M�HEND�SL��� B�L�M�														   **
**				                                       PROGRAMLAMAYA G�R�� DERS�														   **
**																																		   **
**				                            �DEV NUMARASI: 1.Proje																		   **
**				                              ��RENC� ADI: Elif YERL�KAYA																   **
**				                         ��RENC� NUMARASI: G221210031																	   **
**				                               DERS GRUBU: �kinci ��retim B Grubu													       **
********************************************************************************************************************************************/




#include<iostream>
#include<fstream>
#include<ctime>
#include<string>
#include <clocale>
#include <algorithm>
#include <iomanip>
#include <stdlib.h>


using namespace std;

int i = 20;
class �r�nler
{
public:

	string �r�nAdi, sonkullanim, �retim;
	float kalori;
	float stokAdedi;
	float fiyat;
	void setKay�tEkleme()// depodaki �r�nleri depo.txt dosyas�na yazar.
	{
		ofstream kay�tEkle;
		kay�tEkle.open("depo.txt", ios::app);
		kay�tEkle << �r�nAdi << " kalorisi: " << kalori << endl << �r�nAdi << " stok adedi: " << stokAdedi << endl << �r�nAdi << " fiyat�: " << fiyat << endl << �r�nAdi << " �retim tarihi: " << �retim << endl << �r�nAdi << " son kullanma tarihi: " << sonkullanim << endl << endl;
		kay�tEkle.close();
	}

	void kay�tsilme() {// depodan istenen de�eri siler ayn� �ekilde depo.txt dosyas�ndan da siler
		ifstream okuma;
		okuma.open("depo.txt", ios::app);
		ofstream ge�icidosya;
		ge�icidosya.open("ge�ici.txt", ios::app | ios::out);
		string sat�r;
		while (getline(okuma, sat�r)) {
			if (sat�r.substr(0, �r�nAdi.size()) != �r�nAdi) {
				ge�icidosya << sat�r << endl;
			}
		}
		okuma.close();
		ge�icidosya.close();
		remove("depo.txt");
		rename("ge�ici.txt", "depo.txt");
	}
	void kay�tg�ncelleme() //depodaki �r�n bilgilerini g�ncellemeyi sa�lar.
	{

		cout << "�r�n�n 100gr'daki g�ncellenmi� kalorisini giriniz:" << endl;
		cin >> kalori;
		cout << "�r�n�n g�ncellenmi� stok adedini giriniz:" << endl;
		cin >> stokAdedi;
		cout << "�r�n�n g�ncellenmi� fiyat�n� giriniz:" << endl;
		cin >> fiyat;
		cout << "�r�n�n g�ncellenmi� �retim tarihini giriniz: " << endl;
		cin >> �retim;
		cout << "�r�n�n g�ncellenmi� son kullan�m tarihini giriniz: " << endl;
		cin >> sonkullanim;

	}
	void raporal() { // depodaki �r�nler hakk�nda rapor almay� sa�lar.
		ifstream okuma;
		okuma.open("depo.txt", ios::app);
		ofstream ge�icidosya;
		ge�icidosya.open("ge�ici.txt", ios::app | ios::out);
		string sat�r;
		while (getline(okuma, sat�r)) {
			if (sat�r.substr(0, �r�nAdi.size()) == �r�nAdi) {
				ge�icidosya << sat�r << endl;
			}
		}
		okuma.close();
		ge�icidosya.close();
		remove("depo.txt");
		rename("ge�ici.txt", "depo.txt");
	}
};

�r�nler urun[34];
int alisveris[34] = { 0 };

struct malzemeler {
	int adedi;
	malzemeler()
	{
		adedi = 0;
	}
};

struct yemekler {
	string �r�nAdi;
	double maliyet, satis, kar;
	int adet, satisAdet;
	malzemeler malzemeler[34];
	yemekler()
	{
		adet = 0;
	}
}yemekler[22];

void malzemeDosya(int* malzeme) //Malzeme dosyas�na malzemeleri yazar.
{
	ofstream malzemeListesi;
	malzemeListesi.open("malzeme.txt");
	for (int i = 0; i < 33; i++) //D�ng� 33 kere d�ner ve malzemeleri s�rayla malzeme listesine yazar.
	{
		malzemeListesi << urun[i].�r�nAdi << " " << malzeme[i] << endl;
	}
}

void yemekRaporAl() // Se�ilen yemek do�rultusunda sat�� fiyat�,malzemeleri kalorisi gibi raporlar� almaya sa�lar.
{
	string yemekismi;
	double kalori = 0;

	cout << "G�r�nt�lemek istedi�iniz yeme�in ismini giriniz" << endl;
	cin.ignore();
	getline(cin, yemekismi);
	transform(yemekismi.begin(), yemekismi.end(), yemekismi.begin(), ::tolower);
	yemekismi[0] = toupper(yemekismi[0]);

	for (int i = 0; i < 22; i++) {// D�ng� 22 defa d�ner.
		if (yemekler[i].�r�nAdi == yemekismi) // Kullan�c�dan al�nan isim ve yemek ismini kar��la�t�r�r. Ayn� ise ko�ul �al���r.
		{
			cout << endl << yemekler[i].�r�nAdi << " ";
			cout << yemekler[i].satis << " TL" << endl << endl;
			for (int j = 0; j < 32; j++) { // D�ng� 33 defa �al���r.
				if (yemekler[i].malzemeler[j].adedi != 0) { // Yemekteki malzeme adedi s�f�r de�ilse ko�ul �al���r.
					kalori += urun[j].kalori; //Ko�uldaki �r�nlerin kalorini toplar.
					cout << urun[j].�r�nAdi << endl << yemekler[i].malzemeler[j].adedi << " gr" << endl;
				}
			}
		}
	}
	cout << "\nKalori: " << kalori << " cal" << endl;
}

void yemekSatis() //restorant�n g�nl�k yemeklerden ne kadar satt���n� random olarak belirler.
{
	for (int i = 0; i < 22; i++) //D�ng� 22 defa �al���r.
	{
		if (yemekler[i].adet != 0)//Yemek adedi s�f�rdan farkl� ise ko�ul sa�lan�r.
		{
			yemekler[i].satisAdet = rand() % yemekler[i].adet + 1; // sat�� adedi random �ekilde atan�r.
		}
	}

}

int siparisSil(int* malzeme)// Se�ilen yeme�e g�re silme i�lemini yapar. Malzemelerinin kullan�m�na g�re malzemeleri azalt�r.
{
	int secim, adet;
	char sec;
	do {
		cout << "Silmek istedi�iniz yeme�i yaz�n" << endl << "1-Bruschetta " << "2-Risotto " << "3-Tortellini " << "4-Bolonez Soslu Spagetti " << "5-Pesto Soslu Linguine " << "6-Fettucine Alfredo " << "7-Lazanya " << "8-Kremal� Mantar Soslu Penne " << "9-Penne Arabiatta " << "10-Napoliten Soslu Spagetti " << "11-Margarita Pizza " << "12-Kar���k Pizza " << "13-�� Peynirli Pizza " << "14-Vejetaryen Pizza " << "15-Barbek� Soslu Tavuklu Pizza " << "16-Pepperoni Pizza " << "17-D�nerli Pizza " << "18-Tiramisu " << "19- B���rtlen Soslu Panna Cotta " << "20-Cannoli " << endl; ;
		cin >> secim;
		cout << "Ka� adet silmek istiyorsunuz: ";
		cin >> adet;
		switch (secim) { // se�ilen yemek ismine g�re swith case �al���r.
		case 1:
			malzeme[1] -= yemekler[0].malzemeler[1].adedi * adet;
			malzeme[2] -= yemekler[0].malzemeler[2].adedi * adet;
			malzeme[3] -= yemekler[0].malzemeler[3].adedi * adet;
			malzeme[4] -= yemekler[0].malzemeler[4].adedi * adet;
			malzeme[5] -= yemekler[0].malzemeler[5].adedi * adet;
			malzeme[6] -= yemekler[0].malzemeler[6].adedi * adet;
			malzeme[7] -= yemekler[0].malzemeler[7].adedi * adet;
			malzeme[8] -= yemekler[0].malzemeler[8].adedi * adet;
			malzeme[0] -= yemekler[0].malzemeler[0].adedi * adet;
			malzeme[9] -= yemekler[0].malzemeler[9].adedi * adet;
			yemekler[0].adet -= adet;
			break;
		case 2:
			malzeme[2] -= yemekler[1].malzemeler[2].adedi * adet;
			malzeme[6] -= yemekler[1].malzemeler[6].adedi * adet;
			malzeme[10] -= yemekler[1].malzemeler[10].adedi * adet;
			malzeme[11] -= yemekler[1].malzemeler[11].adedi * adet;
			malzeme[13] -= yemekler[1].malzemeler[13].adedi * adet;
			malzeme[7] -= yemekler[1].malzemeler[7].adedi * adet;
			yemekler[1].adet -= adet;
			break;
		case 3:
			malzeme[0] -= yemekler[2].malzemeler[0].adedi * adet;
			malzeme[9] -= yemekler[2].malzemeler[9].adedi * adet;
			malzeme[12] -= yemekler[2].malzemeler[12].adedi * adet;
			malzeme[7] -= yemekler[2].malzemeler[7].adedi * adet;
			malzeme[6] -= yemekler[2].malzemeler[6].adedi * adet;
			malzeme[4] -= yemekler[2].malzemeler[4].adedi * adet;
			yemekler[2].adet -= adet;
			break;
		case 4:
			malzeme[0] -= yemekler[3].malzemeler[0].adedi * adet;
			malzeme[9] -= yemekler[3].malzemeler[9].adedi * adet;
			malzeme[7] -= yemekler[3].malzemeler[7].adedi * adet;
			malzeme[1] -= yemekler[3].malzemeler[1].adedi * adet;
			malzeme[19] -= yemekler[3].malzemeler[19].adedi * adet;
			malzeme[2] -= yemekler[3].malzemeler[2].adedi * adet;
			malzeme[6] -= yemekler[3].malzemeler[6].adedi * adet;
			yemekler[3].adet -= adet;
			break;
		case 5:
			malzeme[0] -= yemekler[4].malzemeler[0].adedi * adet;
			malzeme[9] -= yemekler[4].malzemeler[9].adedi * adet;
			malzeme[3] -= yemekler[4].malzemeler[3].adedi * adet;
			malzeme[13] -= yemekler[4].malzemeler[13].adedi * adet;
			malzeme[6] -= yemekler[4].malzemeler[6].adedi * adet;
			malzeme[7] -= yemekler[4].malzemeler[7].adedi * adet;
			yemekler[4].adet -= adet;
			break;
		case 6:
			malzeme[0] -= yemekler[5].malzemeler[0].adedi * adet;
			malzeme[9] -= yemekler[5].malzemeler[9].adedi * adet;
			malzeme[6] -= yemekler[5].malzemeler[6].adedi * adet;
			malzeme[7] -= yemekler[5].malzemeler[7].adedi * adet;
			malzeme[16] -= yemekler[5].malzemeler[16].adedi * adet;
			malzeme[11] -= yemekler[5].malzemeler[11].adedi * adet;
			malzeme[12] -= yemekler[5].malzemeler[12].adedi * adet;
			yemekler[5].adet -= adet;
			break;
		case 7:
			malzeme[0] -= yemekler[6].malzemeler[0].adedi * adet;
			malzeme[9] -= yemekler[6].malzemeler[9].adedi * adet;
			malzeme[6] -= yemekler[6].malzemeler[6].adedi * adet;
			malzeme[7] -= yemekler[6].malzemeler[7].adedi * adet;
			malzeme[12] -= yemekler[6].malzemeler[12].adedi * adet;
			malzeme[19] -= yemekler[6].malzemeler[19].adedi * adet;
			malzeme[17] -= yemekler[6].malzemeler[17].adedi * adet;
			yemekler[6].adet -= adet;
			break;
		case 8:
			malzeme[0] -= yemekler[7].malzemeler[0].adedi * adet;
			malzeme[9] -= yemekler[7].malzemeler[9].adedi * adet;
			malzeme[6] -= yemekler[7].malzemeler[6].adedi * adet;
			malzeme[7] -= yemekler[7].malzemeler[7].adedi * adet;
			malzeme[16] -= yemekler[7].malzemeler[16].adedi * adet;
			malzeme[12] -= yemekler[7].malzemeler[12].adedi * adet;
			yemekler[7].adet -= adet;
			break;
		case 9:
			malzeme[0] -= yemekler[8].malzemeler[0].adedi * adet;
			malzeme[9] -= yemekler[8].malzemeler[9].adedi * adet;
			malzeme[6] -= yemekler[8].malzemeler[6].adedi * adet;
			malzeme[7] -= yemekler[8].malzemeler[7].adedi * adet;
			malzeme[1] -= yemekler[8].malzemeler[1].adedi * adet;
			malzeme[15] -= yemekler[8].malzemeler[15].adedi * adet;
			malzeme[2] -= yemekler[8].malzemeler[2].adedi * adet;
			yemekler[8].adet -= adet;
			break;
		case 10:
			malzeme[0] -= yemekler[9].malzemeler[0].adedi * adet;
			malzeme[9] -= yemekler[9].malzemeler[9].adedi * adet;
			malzeme[6] -= yemekler[9].malzemeler[6].adedi * adet;
			malzeme[7] -= yemekler[9].malzemeler[7].adedi * adet;
			malzeme[1] -= yemekler[9].malzemeler[1].adedi * adet;
			malzeme[15] -= yemekler[9].malzemeler[15].adedi * adet;
			yemekler[9].adet -= adet;
			break;
		case 11:
			malzeme[0] -= yemekler[10].malzemeler[0].adedi * adet;
			malzeme[9] -= yemekler[10].malzemeler[9].adedi * adet;
			malzeme[6] -= yemekler[10].malzemeler[6].adedi * adet;
			malzeme[7] -= yemekler[10].malzemeler[7].adedi * adet;
			malzeme[1] -= yemekler[10].malzemeler[1].adedi * adet;
			malzeme[4] -= yemekler[10].malzemeler[4].adedi * adet;
			yemekler[10].adet -= adet;
			break;
		case 12:
			malzeme[0] -= yemekler[11].malzemeler[0].adedi * adet;
			malzeme[9] -= yemekler[11].malzemeler[9].adedi * adet;
			malzeme[6] -= yemekler[11].malzemeler[6].adedi * adet;
			malzeme[7] -= yemekler[11].malzemeler[7].adedi * adet;
			malzeme[1] -= yemekler[11].malzemeler[1].adedi * adet;
			malzeme[17] -= yemekler[11].malzemeler[17].adedi * adet;
			malzeme[14] -= yemekler[11].malzemeler[14].adedi * adet;
			malzeme[18] -= yemekler[11].malzemeler[18].adedi * adet;
			yemekler[11].adet -= adet;
			break;
		case 13:
			malzeme[0] -= yemekler[12].malzemeler[0].adedi * adet;
			malzeme[9] -= yemekler[12].malzemeler[9].adedi * adet;
			malzeme[6] -= yemekler[12].malzemeler[6].adedi * adet;
			malzeme[7] -= yemekler[12].malzemeler[7].adedi * adet;
			malzeme[4] -= yemekler[12].malzemeler[4].adedi * adet;
			malzeme[17] -= yemekler[12].malzemeler[17].adedi * adet;
			malzeme[13] -= yemekler[12].malzemeler[13].adedi * adet;
			malzeme[1] -= yemekler[12].malzemeler[1].adedi * adet;
			yemekler[12].adet -= adet;
			break;
		case 14:
			malzeme[0] -= yemekler[13].malzemeler[0].adedi * adet;
			malzeme[9] -= yemekler[13].malzemeler[9].adedi * adet;
			malzeme[6] -= yemekler[13].malzemeler[6].adedi * adet;
			malzeme[7] -= yemekler[13].malzemeler[7].adedi * adet;
			malzeme[1] -= yemekler[13].malzemeler[1].adedi * adet;
			malzeme[20] -= yemekler[13].malzemeler[20].adedi * adet;
			malzeme[21] -= yemekler[13].malzemeler[21].adedi * adet;
			malzeme[17] -= yemekler[13].malzemeler[17].adedi * adet;
			yemekler[13].adet -= adet;
			break;
		case 15:
			malzeme[0] -= yemekler[14].malzemeler[0].adedi * adet;
			malzeme[9] -= yemekler[14].malzemeler[9].adedi * adet;
			malzeme[6] -= yemekler[14].malzemeler[6].adedi * adet;
			malzeme[7] -= yemekler[14].malzemeler[7].adedi * adet;
			malzeme[1] -= yemekler[14].malzemeler[1].adedi * adet;
			malzeme[22] -= yemekler[14].malzemeler[22].adedi * adet;
			malzeme[11] -= yemekler[14].malzemeler[11].adedi * adet;
			yemekler[14].adet -= adet;
			break;
		case 16:
			malzeme[0] -= yemekler[15].malzemeler[0].adedi * adet;
			malzeme[9] -= yemekler[15].malzemeler[9].adedi * adet;
			malzeme[6] -= yemekler[15].malzemeler[6].adedi * adet;
			malzeme[7] -= yemekler[15].malzemeler[7].adedi * adet;
			malzeme[1] -= yemekler[15].malzemeler[1].adedi * adet;
			malzeme[14] -= yemekler[15].malzemeler[14].adedi * adet;
			malzeme[4] -= yemekler[15].malzemeler[4].adedi * adet;
			yemekler[15].adet -= adet;
			break;
		case 17:
			malzeme[0] -= yemekler[16].malzemeler[0].adedi * adet;
			malzeme[9] -= yemekler[16].malzemeler[9].adedi * adet;
			malzeme[6] -= yemekler[16].malzemeler[6].adedi * adet;
			malzeme[7] -= yemekler[16].malzemeler[7].adedi * adet;
			malzeme[1] -= yemekler[16].malzemeler[1].adedi * adet;
			malzeme[23] -= yemekler[16].malzemeler[23].adedi * adet;
			malzeme[17] -= yemekler[16].malzemeler[17].adedi * adet;
			yemekler[16].adet -= adet;
			break;
		case 18:
			malzeme[24] -= yemekler[17].malzemeler[24].adedi * adet;
			malzeme[25] -= yemekler[17].malzemeler[25].adedi * adet;
			malzeme[12] -= yemekler[17].malzemeler[12].adedi * adet;
			malzeme[27] -= yemekler[17].malzemeler[27].adedi * adet;
			yemekler[17].adet -= adet;
			break;
		case 19:
			malzeme[26] -= yemekler[18].malzemeler[26].adedi * adet;
			malzeme[12] -= yemekler[18].malzemeler[12].adedi * adet;
			malzeme[28] -= yemekler[18].malzemeler[28].adedi * adet;
			malzeme[27] -= yemekler[18].malzemeler[27].adedi * adet;
			malzeme[29] -= yemekler[18].malzemeler[29].adedi * adet;
			yemekler[18].adet -= adet;
			break;
		case 20:
			malzeme[27] -= yemekler[19].malzemeler[27].adedi * adet;
			malzeme[6] -= yemekler[19].malzemeler[6].adedi * adet;
			malzeme[30] -= yemekler[19].malzemeler[30].adedi * adet;
			malzeme[0] -= yemekler[19].malzemeler[0].adedi * adet;
			malzeme[12] -= yemekler[19].malzemeler[12].adedi * adet;
			yemekler[19].adet -= adet;
			break;
		default:
			cout << "Yanlis secim yaptiniz!.." << endl;
			break;
		}
		cout << "Devam etmek istiyor musunuz? (e/h)" << endl;
		cin >> sec;
	} while (sec == 'e' || sec == 'E');

	return *malzeme;
}

int siparisEkle(int* malzeme) // Se�ilen yeme�e g�re ekleme i�lemini yapar. Malzemelerinin kullan�m�na g�re malzemeleri artt�r�r.
{
	int secim, adet;
	char sec;
	do {
		cout << "Hangi yemekten ekleme yapaca��n�z� se�iniz: " << endl << "1-Bruschetta 2-Risotto 3-Tortellini 4-Bolonez Soslu Spagetti 5-Pesto Soslu Linguine 6-Fettucine Alfredo 7-Lazanya 8-Kremal� Mantar Soslu Penne 9-Penne Arabiatta 10-Napoliten soslu Spagetti 11-Margarita Pizza 12-Kar���k Pizza 13-�� Peynirli Pizza 14-Vejetaryen Pizza 15-Barbek� Soslu Pizza 16-Pepperoni Pizza 17-D�nerli Pizza 18-Tiramisu 19-B���rtlenli Panna Cotta 20-Cannoli" << endl;
		cin >> secim;
		cout << "Ka� tane eklemek istiyorsunuz?" << endl;
		cin >> adet;
		switch (secim) { // Se�ilen yemek numaras�na g�re switch case �al���r.
		case 1:
			malzeme[1] += yemekler[0].malzemeler[1].adedi * adet;
			malzeme[2] += yemekler[0].malzemeler[2].adedi * adet;
			malzeme[3] += yemekler[0].malzemeler[3].adedi * adet;
			malzeme[4] += yemekler[0].malzemeler[4].adedi * adet;
			malzeme[5] += yemekler[0].malzemeler[5].adedi * adet;
			malzeme[6] += yemekler[0].malzemeler[6].adedi * adet;
			malzeme[7] += yemekler[0].malzemeler[7].adedi * adet;
			malzeme[8] += yemekler[0].malzemeler[8].adedi * adet;
			malzeme[0] += yemekler[0].malzemeler[0].adedi * adet;
			malzeme[9] += yemekler[0].malzemeler[9].adedi * adet;
			yemekler[0].adet += adet;
			break;
		case 2:
			malzeme[2] += yemekler[1].malzemeler[2].adedi * adet;
			malzeme[6] += yemekler[1].malzemeler[6].adedi * adet;
			malzeme[10] += yemekler[1].malzemeler[10].adedi * adet;
			malzeme[11] += yemekler[1].malzemeler[11].adedi * adet;
			malzeme[13] += yemekler[1].malzemeler[13].adedi * adet;
			malzeme[7] += yemekler[1].malzemeler[7].adedi * adet;
			yemekler[1].adet += adet;
			break;
		case 3:
			malzeme[0] += yemekler[2].malzemeler[0].adedi * adet;
			malzeme[9] += yemekler[2].malzemeler[9].adedi * adet;
			malzeme[12] += yemekler[2].malzemeler[12].adedi * adet;
			malzeme[7] += yemekler[2].malzemeler[7].adedi * adet;
			malzeme[6] += yemekler[2].malzemeler[6].adedi * adet;
			malzeme[4] += yemekler[2].malzemeler[4].adedi * adet;
			yemekler[2].adet += adet;
			break;
		case 4:
			malzeme[0] += yemekler[3].malzemeler[0].adedi * adet;
			malzeme[9] += yemekler[3].malzemeler[9].adedi * adet;
			malzeme[7] += yemekler[3].malzemeler[7].adedi * adet;
			malzeme[1] += yemekler[3].malzemeler[1].adedi * adet;
			malzeme[19] += yemekler[3].malzemeler[19].adedi * adet;
			malzeme[2] += yemekler[3].malzemeler[2].adedi * adet;
			malzeme[6] += yemekler[3].malzemeler[6].adedi * adet;
			yemekler[3].adet += adet;
			break;
		case 5:
			malzeme[0] += yemekler[4].malzemeler[0].adedi * adet;
			malzeme[9] += yemekler[4].malzemeler[9].adedi * adet;
			malzeme[3] += yemekler[4].malzemeler[3].adedi * adet;
			malzeme[13] += yemekler[4].malzemeler[13].adedi * adet;
			malzeme[6] += yemekler[4].malzemeler[6].adedi * adet;
			malzeme[7] += yemekler[4].malzemeler[7].adedi * adet;
			yemekler[4].adet += adet;
			break;
		case 6:
			malzeme[0] += yemekler[5].malzemeler[0].adedi * adet;
			malzeme[9] += yemekler[5].malzemeler[9].adedi * adet;
			malzeme[6] += yemekler[5].malzemeler[6].adedi * adet;
			malzeme[7] += yemekler[5].malzemeler[7].adedi * adet;
			malzeme[16] += yemekler[5].malzemeler[16].adedi * adet;
			malzeme[11] += yemekler[5].malzemeler[11].adedi * adet;
			malzeme[12] += yemekler[5].malzemeler[12].adedi * adet;
			yemekler[5].adet += adet;
			break;
		case 7:
			malzeme[0] += yemekler[6].malzemeler[0].adedi * adet;
			malzeme[9] += yemekler[6].malzemeler[9].adedi * adet;
			malzeme[6] += yemekler[6].malzemeler[6].adedi * adet;
			malzeme[7] += yemekler[6].malzemeler[7].adedi * adet;
			malzeme[12] += yemekler[6].malzemeler[12].adedi * adet;
			malzeme[19] += yemekler[6].malzemeler[19].adedi * adet;
			malzeme[17] += yemekler[6].malzemeler[17].adedi * adet;
			yemekler[6].adet += adet;
			break;
		case 8:
			malzeme[0] += yemekler[7].malzemeler[0].adedi * adet;
			malzeme[9] += yemekler[7].malzemeler[9].adedi * adet;
			malzeme[6] += yemekler[7].malzemeler[6].adedi * adet;
			malzeme[7] += yemekler[7].malzemeler[7].adedi * adet;
			malzeme[16] += yemekler[7].malzemeler[16].adedi * adet;
			malzeme[12] += yemekler[7].malzemeler[12].adedi * adet;
			yemekler[7].adet += adet;
			break;
		case 9:
			malzeme[0] += yemekler[8].malzemeler[0].adedi * adet;
			malzeme[9] += yemekler[8].malzemeler[9].adedi * adet;
			malzeme[6] += yemekler[8].malzemeler[6].adedi * adet;
			malzeme[7] += yemekler[8].malzemeler[7].adedi * adet;
			malzeme[1] += yemekler[8].malzemeler[1].adedi * adet;
			malzeme[15] += yemekler[8].malzemeler[15].adedi * adet;
			malzeme[2] += yemekler[8].malzemeler[2].adedi * adet;
			yemekler[8].adet += adet;
			break;
		case 10:
			malzeme[0] += yemekler[9].malzemeler[0].adedi * adet;
			malzeme[9] += yemekler[9].malzemeler[9].adedi * adet;
			malzeme[6] += yemekler[9].malzemeler[6].adedi * adet;
			malzeme[7] += yemekler[9].malzemeler[7].adedi * adet;
			malzeme[1] += yemekler[9].malzemeler[1].adedi * adet;
			malzeme[15] += yemekler[9].malzemeler[15].adedi * adet;
			yemekler[9].adet += adet;
			break;
		case 11:
			malzeme[0] += yemekler[10].malzemeler[0].adedi * adet;
			malzeme[9] += yemekler[10].malzemeler[9].adedi * adet;
			malzeme[6] += yemekler[10].malzemeler[6].adedi * adet;
			malzeme[7] += yemekler[10].malzemeler[7].adedi * adet;
			malzeme[1] += yemekler[10].malzemeler[1].adedi * adet;
			malzeme[4] += yemekler[10].malzemeler[4].adedi * adet;
			yemekler[10].adet += adet;
			break;
		case 12:
			malzeme[0] += yemekler[11].malzemeler[0].adedi * adet;
			malzeme[9] += yemekler[11].malzemeler[9].adedi * adet;
			malzeme[6] += yemekler[11].malzemeler[6].adedi * adet;
			malzeme[7] += yemekler[11].malzemeler[7].adedi * adet;
			malzeme[1] += yemekler[11].malzemeler[1].adedi * adet;
			malzeme[17] += yemekler[11].malzemeler[17].adedi * adet;
			malzeme[14] += yemekler[11].malzemeler[14].adedi * adet;
			malzeme[18] += yemekler[11].malzemeler[18].adedi * adet;
			yemekler[11].adet += adet;
			break;
		case 13:
			malzeme[0] += yemekler[12].malzemeler[0].adedi * adet;
			malzeme[9] += yemekler[12].malzemeler[9].adedi * adet;
			malzeme[6] += yemekler[12].malzemeler[6].adedi * adet;
			malzeme[7] += yemekler[12].malzemeler[7].adedi * adet;
			malzeme[4] += yemekler[12].malzemeler[4].adedi * adet;
			malzeme[17] += yemekler[12].malzemeler[17].adedi * adet;
			malzeme[13] += yemekler[12].malzemeler[13].adedi * adet;
			malzeme[1] += yemekler[12].malzemeler[1].adedi * adet;
			yemekler[12].adet += adet;
			break;
		case 14:
			malzeme[0] += yemekler[13].malzemeler[0].adedi * adet;
			malzeme[9] += yemekler[13].malzemeler[9].adedi * adet;
			malzeme[6] += yemekler[13].malzemeler[6].adedi * adet;
			malzeme[7] += yemekler[13].malzemeler[7].adedi * adet;
			malzeme[1] += yemekler[13].malzemeler[1].adedi * adet;
			malzeme[20] += yemekler[13].malzemeler[20].adedi * adet;
			malzeme[21] += yemekler[13].malzemeler[21].adedi * adet;
			malzeme[17] += yemekler[13].malzemeler[17].adedi * adet;
			yemekler[13].adet += adet;
			break;
		case 15:
			malzeme[0] += yemekler[14].malzemeler[0].adedi * adet;
			malzeme[9] += yemekler[14].malzemeler[9].adedi * adet;
			malzeme[6] += yemekler[14].malzemeler[6].adedi * adet;
			malzeme[7] += yemekler[14].malzemeler[7].adedi * adet;
			malzeme[1] += yemekler[14].malzemeler[1].adedi * adet;
			malzeme[22] += yemekler[14].malzemeler[22].adedi * adet;
			malzeme[11] += yemekler[14].malzemeler[11].adedi * adet;
			yemekler[14].adet += adet;
			break;
		case 16:
			malzeme[0] += yemekler[15].malzemeler[0].adedi * adet;
			malzeme[9] += yemekler[15].malzemeler[9].adedi * adet;
			malzeme[6] += yemekler[15].malzemeler[6].adedi * adet;
			malzeme[7] += yemekler[15].malzemeler[7].adedi * adet;
			malzeme[1] += yemekler[15].malzemeler[1].adedi * adet;
			malzeme[14] += yemekler[15].malzemeler[14].adedi * adet;
			malzeme[4] += yemekler[15].malzemeler[4].adedi * adet;
			yemekler[15].adet += adet;
			break;
		case 17:
			malzeme[0] += yemekler[16].malzemeler[0].adedi * adet;
			malzeme[9] += yemekler[16].malzemeler[9].adedi * adet;
			malzeme[6] += yemekler[16].malzemeler[6].adedi * adet;
			malzeme[7] += yemekler[16].malzemeler[7].adedi * adet;
			malzeme[1] += yemekler[16].malzemeler[1].adedi * adet;
			malzeme[23] += yemekler[16].malzemeler[23].adedi * adet;
			malzeme[17] += yemekler[16].malzemeler[17].adedi * adet;
			yemekler[16].adet += adet;
			break;
		case 18:
			malzeme[24] += yemekler[17].malzemeler[24].adedi * adet;
			malzeme[25] += yemekler[17].malzemeler[25].adedi * adet;
			malzeme[12] += yemekler[17].malzemeler[12].adedi * adet;
			malzeme[27] += yemekler[17].malzemeler[27].adedi * adet;
			yemekler[17].adet += adet;
			break;
		case 19:
			malzeme[26] += yemekler[18].malzemeler[26].adedi * adet;
			malzeme[12] += yemekler[18].malzemeler[12].adedi * adet;
			malzeme[28] += yemekler[18].malzemeler[28].adedi * adet;
			malzeme[27] += yemekler[18].malzemeler[27].adedi * adet;
			malzeme[29] += yemekler[18].malzemeler[29].adedi * adet;
			yemekler[18].adet += adet;
			break;
		case 20:
			malzeme[27] += yemekler[19].malzemeler[27].adedi * adet;
			malzeme[6] += yemekler[19].malzemeler[6].adedi * adet;
			malzeme[30] += yemekler[19].malzemeler[30].adedi * adet;
			malzeme[0] += yemekler[19].malzemeler[0].adedi * adet;
			malzeme[12] += yemekler[19].malzemeler[12].adedi * adet;
			yemekler[19].adet += adet;
			break;
		default:
			cout << "Yanl�� se�im yapt�n�z!.." << endl;
		}
		cout << "Devam etmek istiyor musunuz? (e/h)" << endl;
		cin >> sec;
	} while (sec == 'e' || sec == 'E'); // kullan�c�dan ald��� devam edip etmemek karar�na g�re tekrar ayn� i�lemi yapar.
	int malzeme1[32];
	for (int i = 0; i < 33; i++)
	{
		malzeme1[i] = malzeme[i];
	}
	return *malzeme;
}

int alisverisOlustur(int* malzeme, int* alisveris) // Yap�lacak yeme�in �r�nlerini depo ile kar��la�t�r�r, eksik malzemeler i�in sipari� listesi olu�turur ve oraya kaydeder.
{
	remove("alisverisListesi.txt");
	ofstream alisverisListesi;
	alisverisListesi.open("AlisverisListesi.txt");
	for (int i = 0; i < 33; i++) // d�ng� 33 defa �al���r.
	{
		if (urun[i].stokAdedi < malzeme[i]) // e�er �r�n stok adedi sipari�te verilen malzemeden az ise al��veri� listesine eksik olan miktar� ekler.
		{
			alisveris[i] = malzeme[i] - urun[i].stokAdedi;
			urun[i].stokAdedi = 0;
		}
		else
		{
			urun[i].stokAdedi -= malzeme[i]; // e�er �r�n stok adedi yeterli ise sipari�te kullan�lan malzemeyi depodan siler.
		}
	}
	for (int i = 0; i < 33; i++) // d�ng� 33 defa �al���r ve al��veri� listesine �r�nler yazd�r�l�r.
	{
		if (urun[i].�r�nAdi != "NULL") {
			alisverisListesi << "Al�nacak " << urun[i].�r�nAdi << ": " << alisveris[i] << endl;
			cout << "Al�nacak" << urun[i].�r�nAdi << ": " << alisveris[i] << endl;
		}
	}
	return *alisveris;


}

void yemekOlu�tur() //Yemek �e�itlerinde hangi yemekte hangi malzemenin ne kadar oldu�u, yemek ad� ile manuel atan�r. Yemek �e�idi dosyas�na bu veriler yaz�l�r.
{
	ofstream yemek;
	yemek.open("yemekcesit.txt", ios::in | ios::app);
	yemekler[0].�r�nAdi = "Bruschetta";
	yemekler[0].malzemeler[1].adedi = 75;
	yemekler[0].malzemeler[2].adedi = 50;
	yemekler[0].malzemeler[3].adedi = 25;
	yemekler[0].malzemeler[5].adedi = 5;
	yemekler[0].malzemeler[6].adedi = 20;
	yemekler[0].malzemeler[7].adedi = 5;
	yemekler[0].malzemeler[8].adedi = 75;
	yemekler[0].malzemeler[9].adedi = 150;
	yemekler[0].malzemeler[0].adedi = 150;

	yemekler[1].�r�nAdi = "Risotto";
	yemekler[1].malzemeler[2].adedi = 50;
	yemekler[1].malzemeler[6].adedi = 50;
	yemekler[1].malzemeler[10].adedi = 200;
	yemekler[1].malzemeler[11].adedi = 200;
	yemekler[1].malzemeler[13].adedi = 50;
	yemekler[1].malzemeler[7].adedi = 5;

	yemekler[2].�r�nAdi = "Tortellini";
	yemekler[2].malzemeler[0].adedi = 200;
	yemekler[2].malzemeler[9].adedi = 100;
	yemekler[2].malzemeler[12].adedi = 100;
	yemekler[2].malzemeler[7].adedi = 5;
	yemekler[2].malzemeler[6].adedi = 10;
	yemekler[2].malzemeler[4].adedi = 70;

	yemekler[3].�r�nAdi = "Bolonez Soslu Spagetti";
	yemekler[3].malzemeler[0].adedi = 200;
	yemekler[3].malzemeler[9].adedi = 100;
	yemekler[3].malzemeler[7].adedi = 5;
	yemekler[3].malzemeler[1].adedi = 100;
	yemekler[3].malzemeler[19].adedi = 100;
	yemekler[3].malzemeler[2].adedi = 50;
	yemekler[3].malzemeler[6].adedi = 20;

	yemekler[4].�r�nAdi = "Pesto Soslu Lnguine";
	yemekler[4].malzemeler[0].adedi = 200;
	yemekler[4].malzemeler[9].adedi = 100;
	yemekler[4].malzemeler[3].adedi = 50;
	yemekler[4].malzemeler[13].adedi = 50;
	yemekler[4].malzemeler[6].adedi = 20;
	yemekler[4].malzemeler[7].adedi = 5;

	yemekler[5].�r�nAdi = "Fettucine Alfredo";
	yemekler[5].malzemeler[0].adedi = 200;
	yemekler[5].malzemeler[9].adedi = 100;
	yemekler[5].malzemeler[6].adedi = 20;
	yemekler[5].malzemeler[7].adedi = 5;
	yemekler[5].malzemeler[16].adedi = 50;
	yemekler[5].malzemeler[11].adedi = 70;
	yemekler[5].malzemeler[12].adedi = 50;

	yemekler[6].�r�nAdi = "Lazanya";
	yemekler[6].malzemeler[0].adedi = 200;
	yemekler[6].malzemeler[9].adedi = 100;
	yemekler[6].malzemeler[6].adedi = 20;
	yemekler[6].malzemeler[7].adedi = 5;
	yemekler[6].malzemeler[12].adedi = 50;
	yemekler[6].malzemeler[19].adedi = 100;
	yemekler[6].malzemeler[17].adedi = 70;

	yemekler[7].�r�nAdi = "Kremali Mantar Soslu Penne";
	yemekler[7].malzemeler[0].adedi = 200;
	yemekler[7].malzemeler[9].adedi = 100;
	yemekler[7].malzemeler[6].adedi = 20;
	yemekler[7].malzemeler[7].adedi = 5;
	yemekler[7].malzemeler[16].adedi = 50;
	yemekler[7].malzemeler[12].adedi = 50;

	yemekler[8].�r�nAdi = "Penne Arabiatta";
	yemekler[8].malzemeler[0].adedi = 200;
	yemekler[8].malzemeler[9].adedi = 100;
	yemekler[8].malzemeler[6].adedi = 20;
	yemekler[8].malzemeler[7].adedi = 5;
	yemekler[8].malzemeler[1].adedi = 100;
	yemekler[8].malzemeler[15].adedi = 50;
	yemekler[2].malzemeler[12].adedi = 50;

	yemekler[9].�r�nAdi = "Napoliten Soslu Spagetti";
	yemekler[9].malzemeler[0].adedi = 200;
	yemekler[9].malzemeler[9].adedi = 100;
	yemekler[9].malzemeler[6].adedi = 20;
	yemekler[9].malzemeler[7].adedi = 5;
	yemekler[9].malzemeler[1].adedi = 100;
	yemekler[9].malzemeler[15].adedi = 30;

	yemekler[10].�r�nAdi = "Margarita Pizza";
	yemekler[10].malzemeler[0].adedi = 200;
	yemekler[10].malzemeler[9].adedi = 100;
	yemekler[10].malzemeler[6].adedi = 20;
	yemekler[10].malzemeler[7].adedi = 5;
	yemekler[10].malzemeler[1].adedi = 100;
	yemekler[10].malzemeler[4].adedi = 100;

	yemekler[11].�r�nAdi = "Karisik Pizza";
	yemekler[11].malzemeler[0].adedi = 200;
	yemekler[11].malzemeler[9].adedi = 100;
	yemekler[11].malzemeler[6].adedi = 20;
	yemekler[11].malzemeler[7].adedi = 5;
	yemekler[11].malzemeler[1].adedi = 100;
	yemekler[11].malzemeler[17].adedi = 100;
	yemekler[11].malzemeler[14].adedi = 80;
	yemekler[11].malzemeler[18].adedi = 30;

	yemekler[12].�r�nAdi = "Uc Peynirli Pizza";
	yemekler[12].malzemeler[0].adedi = 200;
	yemekler[12].malzemeler[9].adedi = 100;
	yemekler[12].malzemeler[6].adedi = 20;
	yemekler[12].malzemeler[7].adedi = 5;
	yemekler[12].malzemeler[1].adedi = 100;
	yemekler[12].malzemeler[4].adedi = 75;
	yemekler[12].malzemeler[17].adedi = 75;
	yemekler[12].malzemeler[13].adedi = 75;

	yemekler[13].�r�nAdi = "Vejetaryen Pizza";
	yemekler[13].malzemeler[0].adedi = 200;
	yemekler[13].malzemeler[9].adedi = 100;
	yemekler[13].malzemeler[6].adedi = 20;
	yemekler[13].malzemeler[7].adedi = 5;
	yemekler[13].malzemeler[1].adedi = 100;
	yemekler[13].malzemeler[20].adedi = 50;
	yemekler[13].malzemeler[21].adedi = 40;
	yemekler[13].malzemeler[17].adedi = 75;

	yemekler[14].�r�nAdi = "Barbeku Soslu Tavuklu Pizza";
	yemekler[14].malzemeler[0].adedi = 200;
	yemekler[14].malzemeler[9].adedi = 100;
	yemekler[14].malzemeler[6].adedi = 20;
	yemekler[14].malzemeler[7].adedi = 5;
	yemekler[14].malzemeler[1].adedi = 100;
	yemekler[14].malzemeler[22].adedi = 50;
	yemekler[14].malzemeler[11].adedi = 150;

	yemekler[15].�r�nAdi = "Pepperoni Pizza";
	yemekler[15].malzemeler[0].adedi = 200;
	yemekler[15].malzemeler[9].adedi = 100;
	yemekler[15].malzemeler[6].adedi = 20;
	yemekler[15].malzemeler[7].adedi = 5;
	yemekler[15].malzemeler[1].adedi = 100;
	yemekler[15].malzemeler[14].adedi = 75;
	yemekler[15].malzemeler[4].adedi = 80;

	yemekler[16].�r�nAdi = "Donerli Pizza";
	yemekler[16].malzemeler[0].adedi = 200;
	yemekler[16].malzemeler[9].adedi = 100;
	yemekler[16].malzemeler[6].adedi = 20;
	yemekler[16].malzemeler[7].adedi = 5;
	yemekler[16].malzemeler[1].adedi = 100;
	yemekler[16].malzemeler[17].adedi = 100;
	yemekler[16].malzemeler[23].adedi = 100;

	yemekler[17].�r�nAdi = "Tiramisu";
	yemekler[17].malzemeler[24].adedi = 150;
	yemekler[17].malzemeler[25].adedi = 50;
	yemekler[17].malzemeler[12].adedi = 150;
	yemekler[17].malzemeler[27].adedi = 100;

	yemekler[18].�r�nAdi = "Bogurtlen Soslu Panna Cotta";
	yemekler[18].malzemeler[12].adedi = 150;
	yemekler[18].malzemeler[26].adedi = 100;
	yemekler[18].malzemeler[28].adedi = 50;
	yemekler[18].malzemeler[27].adedi = 100;
	yemekler[18].malzemeler[29].adedi = 50;

	yemekler[19].�r�nAdi = "Cannoli";
	yemekler[19].malzemeler[27].adedi = 50;
	yemekler[19].malzemeler[6].adedi = 50;
	yemekler[19].malzemeler[30].adedi = 50;
	yemekler[19].malzemeler[0].adedi = 300;
	yemekler[19].malzemeler[12].adedi = 150;
	for (int i = 0; i < 22; i++) // d�ng� 22 defa �al���r ve yemek dosyas�na verileri yazar.
	{
		yemek << yemekler[i].�r�nAdi << endl;
	}
}
void setYemekKar()// Restorantta yap�lan yeme�in sat���na da bakarak kar-zarar hesab� yapar.
{
	yemekler[0].maliyet = yemekler[0].malzemeler[1].adedi * urun[1].fiyat / 100 + yemekler[0].malzemeler[2].adedi * urun[2].fiyat / 100 + yemekler[0].malzemeler[3].adedi * urun[3].fiyat / 100 + yemekler[0].malzemeler[4].adedi * urun[4].fiyat / 100 + yemekler[0].malzemeler[5].adedi * urun[5].fiyat / 100 + yemekler[0].malzemeler[6].adedi * urun[6].fiyat / 100 + yemekler[0].malzemeler[7].adedi * urun[7].fiyat / 100 + yemekler[0].malzemeler[8].adedi * urun[8].fiyat / 100 + yemekler[0].malzemeler[9].adedi * urun[9].fiyat / 100 + yemekler[0].malzemeler[0].adedi * urun[0].fiyat / 100;
	yemekler[0].satis = 125;
	yemekler[0].kar = yemekler[0].satis * yemekler[0].satisAdet - yemekler[0].maliyet * yemekler[0].adet;

	yemekler[1].maliyet = yemekler[1].malzemeler[2].adedi * urun[2].fiyat / 100 + yemekler[1].malzemeler[6].adedi * urun[6].fiyat / 100 + yemekler[1].malzemeler[10].adedi * urun[10].fiyat / 100 + yemekler[1].malzemeler[11].adedi * urun[11].fiyat / 100 + yemekler[1].malzemeler[13].adedi * urun[13].fiyat / 100 + yemekler[1].malzemeler[7].adedi * urun[7].fiyat / 100;
	yemekler[1].satis = 135;
	yemekler[1].kar = yemekler[1].satis * yemekler[1].satisAdet - yemekler[0].maliyet * yemekler[0].adet;

	yemekler[2].maliyet = yemekler[2].malzemeler[0].adedi * urun[0].fiyat / 100 + yemekler[2].malzemeler[9].adedi * urun[9].fiyat / 100 + yemekler[2].malzemeler[12].adedi * urun[12].fiyat / 100 + yemekler[2].malzemeler[7].adedi * urun[7].fiyat / 100 + yemekler[2].malzemeler[6].adedi * urun[6].fiyat / 100 + yemekler[2].malzemeler[4].adedi * urun[4].fiyat / 100;
	yemekler[2].satis = 75;
	yemekler[2].kar = yemekler[2].satis * yemekler[2].satisAdet - yemekler[2].maliyet * yemekler[2].adet;

	yemekler[3].maliyet = yemekler[3].malzemeler[0].adedi * urun[0].fiyat / 100 + yemekler[3].malzemeler[9].adedi * urun[9].fiyat / 100 + yemekler[3].malzemeler[7].adedi * urun[7].fiyat / 100 + yemekler[3].malzemeler[1].adedi * urun[1].fiyat / 100 + yemekler[3].malzemeler[19].adedi * urun[19].fiyat / 100 + yemekler[3].malzemeler[2].adedi * urun[2].fiyat / 100 + yemekler[3].malzemeler[6].adedi * urun[6].fiyat / 100;
	yemekler[3].satis = 90;
	yemekler[3].kar = yemekler[3].satis * yemekler[3].satisAdet - yemekler[3].maliyet * yemekler[3].adet;

	yemekler[4].maliyet = yemekler[4].malzemeler[0].adedi * urun[0].fiyat / 100 + yemekler[4].malzemeler[9].adedi * urun[9].fiyat / 100 + yemekler[4].malzemeler[3].adedi * urun[3].fiyat / 100 + yemekler[4].malzemeler[13].adedi * urun[13].fiyat / 100 + yemekler[4].malzemeler[6].adedi * urun[6].fiyat / 100 + yemekler[4].malzemeler[7].adedi * urun[7].fiyat / 100;
	yemekler[4].satis = 67.5;
	yemekler[4].kar = yemekler[4].satis * yemekler[4].satisAdet - yemekler[4].maliyet * yemekler[4].adet;

	yemekler[5].maliyet = yemekler[5].malzemeler[0].adedi * urun[0].fiyat / 100 + yemekler[5].malzemeler[9].adedi * urun[9].fiyat / 100 + yemekler[5].malzemeler[6].adedi * urun[6].fiyat / 100 + yemekler[5].malzemeler[7].adedi * urun[7].fiyat / 100 + yemekler[5].malzemeler[16].adedi * urun[16].fiyat / 100 + yemekler[5].malzemeler[11].adedi * urun[11].fiyat / 100 + yemekler[5].malzemeler[12].adedi * urun[12].fiyat / 100;
	yemekler[5].satis = 75;
	yemekler[5].kar = yemekler[5].satis * yemekler[5].satisAdet - yemekler[5].maliyet * yemekler[5].adet;

	yemekler[6].maliyet = yemekler[6].malzemeler[0].adedi * urun[0].fiyat / 100 + yemekler[6].malzemeler[9].adedi * urun[9].fiyat / 100 + yemekler[6].malzemeler[6].adedi * urun[6].fiyat / 100 + yemekler[6].malzemeler[7].adedi * urun[7].fiyat / 100 + yemekler[6].malzemeler[12].adedi * urun[12].fiyat / 100 + yemekler[6].malzemeler[19].adedi * urun[19].fiyat / 100 + yemekler[6].malzemeler[17].adedi * urun[17].fiyat / 100;
	yemekler[6].satis = 92.75;
	yemekler[6].kar = yemekler[6].satis * yemekler[6].satisAdet - yemekler[6].maliyet * yemekler[6].adet;

	yemekler[7].maliyet = yemekler[7].malzemeler[0].adedi * urun[0].fiyat / 100 + yemekler[7].malzemeler[9].adedi * urun[9].fiyat / 100 + yemekler[7].malzemeler[6].adedi * urun[6].fiyat / 100 + yemekler[7].malzemeler[7].adedi * urun[7].fiyat / 100 + yemekler[7].malzemeler[16].adedi * urun[16].fiyat / 100 + yemekler[7].malzemeler[12].adedi * urun[12].fiyat / 100;
	yemekler[7].satis = 59.99;
	yemekler[7].kar = yemekler[7].satis * yemekler[7].satisAdet - yemekler[7].maliyet * yemekler[7].adet;

	yemekler[8].maliyet = yemekler[8].malzemeler[0].adedi * urun[0].fiyat / 100 + yemekler[8].malzemeler[9].adedi * urun[9].fiyat / 100 + yemekler[8].malzemeler[6].adedi * urun[6].fiyat / 100 + yemekler[8].malzemeler[7].adedi * urun[7].fiyat / 100 + yemekler[8].malzemeler[1].adedi * urun[1].fiyat / 100 + yemekler[8].malzemeler[15].adedi * urun[15].fiyat / 100 + yemekler[8].malzemeler[2].adedi * urun[2].fiyat / 100;
	yemekler[8].satis = 80;
	yemekler[8].kar = yemekler[8].satis * yemekler[8].satisAdet - yemekler[8].maliyet * yemekler[8].adet;

	yemekler[9].maliyet = yemekler[9].malzemeler[0].adedi * urun[0].fiyat / 100 + yemekler[9].malzemeler[9].adedi * urun[9].fiyat / 100 + yemekler[9].malzemeler[6].adedi * urun[6].fiyat / 100 + yemekler[9].malzemeler[7].adedi * urun[7].fiyat / 100 + yemekler[9].malzemeler[1].adedi * urun[1].fiyat / 100 + yemekler[9].malzemeler[15].adedi * urun[15].fiyat / 100;
	yemekler[9].satis = 67.15;
	yemekler[9].kar = yemekler[9].satis * yemekler[9].satisAdet - yemekler[9].maliyet * yemekler[9].adet;

	yemekler[10].maliyet = yemekler[10].malzemeler[0].adedi * urun[0].fiyat / 100 + yemekler[10].malzemeler[9].adedi * urun[9].fiyat / 100 + yemekler[10].malzemeler[6].adedi * urun[6].fiyat / 100 + yemekler[10].malzemeler[7].adedi * urun[7].fiyat / 100 + yemekler[10].malzemeler[1].adedi * urun[1].fiyat / 100 + yemekler[10].malzemeler[4].adedi * urun[4].fiyat / 100;
	yemekler[10].satis = 82.45;
	yemekler[10].kar = yemekler[10].satis * yemekler[10].satisAdet - yemekler[10].maliyet * yemekler[10].adet;

	yemekler[11].maliyet = yemekler[11].malzemeler[0].adedi * urun[0].fiyat / 100 + yemekler[11].malzemeler[9].adedi * urun[9].fiyat / 100 + yemekler[11].malzemeler[6].adedi * urun[6].fiyat / 100 + yemekler[11].malzemeler[7].adedi * urun[7].fiyat / 100 + yemekler[11].malzemeler[1].adedi * urun[1].fiyat / 100 + yemekler[11].malzemeler[17].adedi * urun[17].fiyat / 100 + yemekler[11].malzemeler[14].adedi * urun[14].fiyat / 100 + yemekler[11].malzemeler[18].adedi * urun[18].fiyat / 100;
	yemekler[11].satis = 80.75;
	yemekler[11].kar = yemekler[11].satis * yemekler[11].satisAdet - yemekler[11].maliyet * yemekler[11].adet;

	yemekler[12].maliyet = yemekler[12].malzemeler[0].adedi * urun[0].fiyat / 100 + yemekler[12].malzemeler[9].adedi * urun[9].fiyat / 100 + yemekler[12].malzemeler[6].adedi * urun[6].fiyat / 100 + yemekler[12].malzemeler[7].adedi * urun[7].fiyat / 100 + yemekler[12].malzemeler[4].adedi * urun[4].fiyat / 100 + yemekler[12].malzemeler[17].adedi * urun[17].fiyat / 100 + yemekler[12].malzemeler[13].adedi * urun[13].fiyat / 100 + yemekler[12].malzemeler[1].adedi * urun[1].fiyat / 100;
	yemekler[12].satis = 125;
	yemekler[12].kar = yemekler[12].satis * yemekler[12].satisAdet - yemekler[12].maliyet * yemekler[12].adet;

	yemekler[13].maliyet = yemekler[13].malzemeler[0].adedi * urun[0].fiyat / 100 + yemekler[13].malzemeler[9].adedi * urun[9].fiyat / 100 + yemekler[13].malzemeler[6].adedi * urun[6].fiyat / 100 + yemekler[13].malzemeler[7].adedi * urun[7].fiyat / 100 + yemekler[13].malzemeler[20].adedi * urun[20].fiyat / 100 + yemekler[13].malzemeler[21].adedi * urun[21].fiyat / 100 + yemekler[13].malzemeler[1].adedi * urun[1].fiyat / 100 + yemekler[13].malzemeler[17].adedi * urun[17].fiyat / 100;
	yemekler[13].satis = 92;
	yemekler[13].kar = yemekler[13].satis * yemekler[13].satisAdet - yemekler[13].maliyet * yemekler[13].adet;

	yemekler[14].maliyet = yemekler[14].malzemeler[0].adedi * urun[0].fiyat / 100 + yemekler[14].malzemeler[9].adedi * urun[9].fiyat / 100 + yemekler[14].malzemeler[6].adedi * urun[6].fiyat / 100 + yemekler[14].malzemeler[7].adedi * urun[7].fiyat / 100 + yemekler[14].malzemeler[1].adedi * urun[1].fiyat / 100 + yemekler[14].malzemeler[22].adedi * urun[22].fiyat / 100 + yemekler[14].malzemeler[11].adedi * urun[11].fiyat / 100;
	yemekler[14].satis = 114;
	yemekler[14].kar = yemekler[14].satis * yemekler[14].satisAdet - yemekler[14].maliyet * yemekler[14].adet;

	yemekler[15].maliyet = yemekler[15].malzemeler[0].adedi * urun[0].fiyat / 100 + yemekler[15].malzemeler[9].adedi * urun[9].fiyat / 100 + yemekler[15].malzemeler[6].adedi * urun[6].fiyat / 100 + yemekler[15].malzemeler[7].adedi * urun[7].fiyat / 100 + yemekler[15].malzemeler[1].adedi * urun[1].fiyat / 100 + yemekler[15].malzemeler[14].adedi * urun[14].fiyat / 100 + yemekler[15].malzemeler[4].adedi * urun[4].fiyat / 100;
	yemekler[15].satis = 82.45;
	yemekler[15].kar = yemekler[15].satis * yemekler[15].satisAdet - yemekler[15].maliyet * yemekler[15].adet;

	yemekler[16].maliyet = yemekler[16].malzemeler[0].adedi * urun[0].fiyat / 100 + yemekler[16].malzemeler[9].adedi * urun[9].fiyat / 100 + yemekler[16].malzemeler[6].adedi * urun[6].fiyat / 100 + yemekler[16].malzemeler[7].adedi * urun[7].fiyat / 100 + yemekler[16].malzemeler[1].adedi * urun[1].fiyat / 100 + yemekler[16].malzemeler[23].adedi * urun[23].fiyat / 100 + yemekler[16].malzemeler[17].adedi * urun[17].fiyat / 100;
	yemekler[16].satis = 92;
	yemekler[16].kar = yemekler[16].satis * yemekler[16].satisAdet - yemekler[16].maliyet * yemekler[16].adet;

	yemekler[17].maliyet = yemekler[17].malzemeler[24].adedi * urun[24].fiyat / 100 + yemekler[17].malzemeler[25].adedi * urun[25].fiyat / 100 + yemekler[17].malzemeler[12].adedi * urun[12].fiyat / 100 + yemekler[17].malzemeler[27].adedi * urun[27].fiyat / 100;
	yemekler[17].satis = 78.24;
	yemekler[17].kar = yemekler[17].satis * yemekler[17].satisAdet - yemekler[17].maliyet * yemekler[17].adet;

	yemekler[18].maliyet = yemekler[18].malzemeler[26].adedi * urun[26].fiyat / 100 + yemekler[18].malzemeler[12].adedi * urun[12].fiyat / 100 + yemekler[18].malzemeler[28].adedi * urun[28].fiyat / 100 + yemekler[18].malzemeler[27].adedi * urun[27].fiyat / 100 + yemekler[18].malzemeler[29].adedi * urun[29].fiyat / 100;
	yemekler[18].satis = 80;
	yemekler[18].kar = yemekler[18].satis * yemekler[18].satisAdet - yemekler[18].maliyet * yemekler[18].adet;

	yemekler[19].maliyet = yemekler[19].malzemeler[27].adedi * urun[27].fiyat / 100 + yemekler[19].malzemeler[6].adedi * urun[6].fiyat / 100 + yemekler[19].malzemeler[30].adedi * urun[30].fiyat / 100 + yemekler[19].malzemeler[0].adedi * urun[0].fiyat / 100 + yemekler[19].malzemeler[12].adedi * urun[12].fiyat / 100;
	yemekler[19].satis = 95;
	yemekler[19].kar = yemekler[19].satis * yemekler[19].satisAdet - yemekler[19].maliyet * yemekler[19].adet;
}


void setDepoBilgi()								//Urun dizisinin elemanlar�na malzeme isimleri,malzeme fiyatlar�,kalorisi, son t�ketim ve �retim tarihleri atan�yor.
{
	urun[0].�r�nAdi = "Un";
	urun[1].�r�nAdi = "Domates";
	urun[2].�r�nAdi = "Sogan";
	urun[3].�r�nAdi = "Feslegen";
	urun[4].�r�nAdi = "Mozarella";
	urun[5].�r�nAdi = "Sar�msak";
	urun[6].�r�nAdi = "Yag";
	urun[7].�r�nAdi = "Tuz";
	urun[8].�r�nAdi = "Somon";
	urun[9].�r�nAdi = "Su";
	urun[10].�r�nAdi = "Pirinc";
	urun[11].�r�nAdi = "Tavuk";
	urun[12].�r�nAdi = "Krema";
	urun[13].�r�nAdi = "Parmesan";
	urun[14].�r�nAdi = "Sucuk";
	urun[15].�r�nAdi = "Biber";
	urun[16].�r�nAdi = "Mantar";
	urun[17].�r�nAdi = "Kasar";
	urun[18].�r�nAdi = "Misir";
	urun[19].�r�nAdi = "Kiyma";
	urun[20].�r�nAdi = "Kabak";
	urun[21].�r�nAdi = "Patlican";
	urun[22].�r�nAdi = "Barbeku sosu";
	urun[23].�r�nAdi = "Doner";
	urun[24].�r�nAdi = "Kedi dili";
	urun[25].�r�nAdi = "Kahve";
	urun[26].�r�nAdi = "Bogurtlen";
	urun[27].�r�nAdi = "Seker";
	urun[28].�r�nAdi = "Jelatin";
	urun[29].�r�nAdi = "Nisasta";
	urun[30].�r�nAdi = "Yumurta";
	urun[31].�r�nAdi = "NULL";
	urun[32].�r�nAdi = "NULL";
	urun[33].�r�nAdi = "NULL";

	urun[0].fiyat = 15;
	urun[1].fiyat = 12;
	urun[2].fiyat = 14;
	urun[3].fiyat = 8;
	urun[4].fiyat = 28;
	urun[5].fiyat = 4;
	urun[6].fiyat = 9;
	urun[7].fiyat = 5;
	urun[8].fiyat = 35;
	urun[9].fiyat = 5;
	urun[10].fiyat = 18;
	urun[11].fiyat = 28;
	urun[12].fiyat = 14;
	urun[13].fiyat = 24;
	urun[14].fiyat = 11;
	urun[15].fiyat = 14;
	urun[16].fiyat = 18;
	urun[17].fiyat = 17;
	urun[18].fiyat = 14;
	urun[19].fiyat = 29;
	urun[20].fiyat = 14;
	urun[21].fiyat = 16;
	urun[22].fiyat = 22;
	urun[23].fiyat = 11;
	urun[24].fiyat = 13;
	urun[25].fiyat = 15;
	urun[26].fiyat = 19;
	urun[27].fiyat = 17;
	urun[28].fiyat = 15;
	urun[29].fiyat = 16;
	urun[30].fiyat = 12;

	urun[0].kalori = 364;
	urun[1].kalori = 18;
	urun[2].kalori = 40;
	urun[3].kalori = 22;
	urun[4].kalori = 280;
	urun[5].kalori = 149;
	urun[6].kalori = 884;
	urun[7].kalori = 0;
	urun[8].kalori = 208;
	urun[9].kalori = 0;
	urun[10].kalori = 130;
	urun[11].kalori = 239;
	urun[12].kalori = 196;
	urun[13].kalori = 431;
	urun[14].kalori = 330;
	urun[15].kalori = 40;
	urun[16].kalori = 22;
	urun[17].kalori = 353;
	urun[18].kalori = 96;
	urun[19].kalori = 332;
	urun[20].kalori = 17;
	urun[21].kalori = 25;
	urun[22].kalori = 172;
	urun[23].kalori = 128;
	urun[24].kalori = 365;
	urun[25].kalori = 0;
	urun[26].kalori = 43;
	urun[27].kalori = 387;
	urun[28].kalori = 62;
	urun[29].kalori = 370;
	urun[30].kalori = 155;

	urun[0].sonkullanim = "12 / 08 / 2024";
	urun[1].sonkullanim = "28 / 11 / 2026";
	urun[2].sonkullanim = "07 / 02 / 2023";
	urun[3].sonkullanim = "05 / 06 / 2024";
	urun[4].sonkullanim = "12 / 07 / 2022";
	urun[5].sonkullanim = "08 / 02 / 2025";
	urun[6].sonkullanim = "05 / 01 / 2023";
	urun[7].sonkullanim = "06 / 04 / 2028";
	urun[8].sonkullanim = "12 / 12 / 2022";
	urun[9].sonkullanim = "21 / 04 / 2029";
	urun[10].sonkullanim = "24 / 03 / 2023";
	urun[11].sonkullanim = "17 / 05 / 2024";
	urun[12].sonkullanim = "15 / 04 / 2023";
	urun[13].sonkullanim = "16 / 06 / 2024";
	urun[14].sonkullanim = "04 / 09 / 2025";
	urun[15].sonkullanim = "09 / 07 / 2023";
	urun[16].sonkullanim = "26 / 12 / 2023";
	urun[17].sonkullanim = "24 / 01 / 2025";
	urun[18].sonkullanim = "17 / 02 / 2024";
	urun[19].sonkullanim = "19 / 04 / 2025";
	urun[20].sonkullanim = "24 / 08 / 2022";
	urun[21].sonkullanim = "03 / 07 / 2023";
	urun[22].sonkullanim = "01 / 03 / 2024";
	urun[23].sonkullanim = "06 / 06 / 2022";
	urun[24].sonkullanim = "09 / 07 / 2023";
	urun[25].sonkullanim = "12 / 11 / 2028";
	urun[26].sonkullanim = "13 / 06 / 2026";
	urun[27].sonkullanim = "29 / 02 / 2023";
	urun[28].sonkullanim = "15 / 07 / 2025";
	urun[29].sonkullanim = "16 / 01 / 2024";
	urun[30].sonkullanim = "12 / 12 / 2022";

	urun[0].�retim = "21 / 01 / 2021";
	urun[1].�retim = "12 / 02 / 2022";
	urun[2].�retim = "29 / 09 / 2022";
	urun[3].�retim = "21 / 04 / 2022";
	urun[4].�retim = "04 / 11 / 2021";
	urun[5].�retim = "06 / 12 / 2022";
	urun[6].�retim = "14 / 07 / 2020";
	urun[7].�retim = "26 / 06 / 2022";
	urun[8].�retim = "09 / 03 / 2021";
	urun[9].�retim = "07 / 05 / 2022";
	urun[10].�retim = "12 / 01 / 2020";
	urun[11].�retim = "16 / 06 / 2022";
	urun[12].�retim = "24 / 07 / 2021";
	urun[13].�retim = "28 / 09 / 2022";
	urun[14].�retim = "21 / 06 / 2022";
	urun[15].�retim = "29 / 01 / 2021";
	urun[16].�retim = "11 / 02 / 2022";
	urun[17].�retim = "19 / 05 / 2022";
	urun[18].�retim = "29 / 07 / 2021";
	urun[19].�retim = "27 / 08 / 2020";
	urun[20].�retim = "01 / 09 / 2021";
	urun[21].�retim = "03 / 12 / 2022";
	urun[22].�retim = "09 / 11 / 2021";
	urun[23].�retim = "17 / 05 / 2022";
	urun[24].�retim = "19 / 04 / 2021";
	urun[25].�retim = "23 / 06 / 2021";
	urun[26].�retim = "29 / 05 / 2022";
	urun[27].�retim = "02 / 03 / 2020";
	urun[28].�retim = "25 / 04 / 2022";
	urun[29].�retim = "29 / 06 / 2022";
	urun[30].�retim = "27 / 07 / 2021";
}

void setDepo()
{
	for (int i = 0; i < 33; i++) // d�ng� 33 defa �al���r 
	{
		urun[i].stokAdedi = 750 + rand() % 1251;		//Her bir malzeme i�in depo stok adetleri rastgele 750 ila 2000 olacak �ekilde atan�r.
	}
}

void malzemeBilgisiGoruntule() // Malzeme hakk�nda rapor almaya yarayan fonksiyondur. Kullan�c�dan g�r�nt�lemek istedi�i �r�n�n ismini al�p �r�n hakk�ndaki verileri yazar.
{
	string malzemeIsim;
	cout << "G�r�nt�lemek istedi�iniz �r�n�n ad�n� yaz�n�z: " << endl;
	cin.ignore();
	getline(cin, malzemeIsim);
	transform(malzemeIsim.begin(), malzemeIsim.end(), malzemeIsim.begin(), ::tolower);
	malzemeIsim[0] = toupper(malzemeIsim[0]);
	for (int i = 0; i < 33; i++) // d�ng� 33 defa �al���r 
	{
		if (urun[i].�r�nAdi == malzemeIsim)  //kullan�c�dan al�nan malzeme ile �r�n ismi e�it olursa ko�ul �al���r.
		{
			cout << left << "\t�r�n ad�: " << urun[i].�r�nAdi << endl;
			cout << left << "\t�r�n�n fiyat�: " << urun[i].fiyat << endl;
			cout << left << "\t�r�n�n stok adedi: " << urun[i].stokAdedi << endl;
			cout << left << "\t�r�n�n 100 gramda kalori de�eri: " << urun[i].kalori << endl;
			cout << left << "\t�r�n�n �retim tarihi: " << urun[i].�retim << endl;
			cout << left << "\t�r�n�n son kullanma tarihi: " << urun[i].sonkullanim << endl;

		}
	}
}

void depoGuncelleme() //Depodaki se�ilen malzemenin stok adedini g�ncellemeyi sa�lar.
{
	string malzemeIsim;
	int guncelStok;
	remove("depo.txt");
	cout << "Hangi malzemeyi g�ncellemek istiyorsunuz? (�r�n ad� yazarken T�rk�e karakter kullanmay�n!.." << endl;
	cin.ignore();
	getline(cin, malzemeIsim);
	transform(malzemeIsim.begin(), malzemeIsim.end(), malzemeIsim.begin(), ::tolower);
	malzemeIsim[0] = toupper(malzemeIsim[0]);
	for (int i = 0; i < 33; i++) // d�ng� 33 defa d�ner.
	{
		if (urun[i].�r�nAdi == malzemeIsim)  //kullan�c�dan al�nan malzeme ile �r�n ismi e�it olursa ko�ul �al���r.
		{
			urun[i].kay�tg�ncelleme();
		}
		urun[i].setKay�tEkleme();
	}
}

void yemeklistesig�ncelle() // Se�ilen yemekte kullan�lan malzemelerin miktar�n� artt�r�p azaltmaya yarar.
{
	string yemekismi;
	int sayi;
	int secim;
	double artis;
	double azalis;
	cout << "G�ncellemek istedi�iniz yeme�in ismini giriniz" << endl;
	cin.ignore();
	getline(cin, yemekismi);
	transform(yemekismi.begin(), yemekismi.end(), yemekismi.begin(), ::tolower);
	yemekismi[0] = toupper(yemekismi[0]);

	for (int i = 0; i < 22; i++) // d�ng� 22 defa d�ner
	{
		if (yemekler[i].�r�nAdi == yemekismi) //kullan�c�dan al�nan yemek ismi, yemek ismi ile uyu�ursa ko�ul sa�lan�r.
		{
			cout << "Hangi malzemeyi de�i�tirmek istersiniz?" << endl << "un-0 domates-1 so�an-2 fesle�en-3" << endl << "mozerella-4 sar�msak-5 ya�-6 tuz-7" << endl << "somon-8 su-9 pirin�-10 tavuk-11" << endl << "krema-12 parmesan-13 sucuk-14 biber-15" << endl << "mantar-16 ka�ar-17 m�s�r-18 k�yma-19" << endl << "kabak-20 patl�can-21 barbek� sosu-22 d�ner-23" << endl << "kedi dili-24 kahve-25 b���rtlen-26 �eker-27" << endl << "jelatin-28 ni�asta-29 yumurta-30" << endl;
			cin >> sayi;
			cout << "Azaltmak m� artt�rmak m� istersiniz? artt�rmak i�in 1, azaltmak i�in 2yi tu�lay�n�z" << endl;
			cin >> secim;
			switch (secim)
			{
			case 1:
				cout << "Ne kadar artt�rmak istersiniz?" << endl;
				cin >> artis;
				yemekler[i].malzemeler[sayi].adedi += artis; // yemekteki malzemelerin miktar�na kullan�c�dan al�nan art�� de�erini ekler
				break;

			case 2:
				cout << "Ne kadar azaltmak istersiniz?" << endl;// yemekteki malzemelerin miktar�na kullan�c�dan al�nan azal�� de�erini ��kar�r.
				cin >> azalis;
				yemekler[i].malzemeler[sayi].adedi -= azalis;
				break;
			}
		}

	}
	cout << "G�ncelleme bitmi�tir.." << endl << "se�ilen yemegin g�ncellenmis hali:" << endl; //g�ncellenmi� yemek ve malzemelerini yazd�r�r.
	for (int i = 0; i < 22; i++) { // d�ng� 22 defa �al���r 
		if (yemekler[i].�r�nAdi == yemekismi) // kullan�c�dan al�nan yemek ismi ile yemek ismi uyu�ursa ko�ul �al���r.
		{
			cout << yemekler[i].�r�nAdi << endl;
			for (int j = 0; j < 32; j++) { // d�ng� 32 defa �al���r.
				if (yemekler[i].malzemeler[j].adedi != 0) { // e�er malzeme adedi s�f�rdan farkl� ise ko�ul sa�lan�r.
					cout << urun[j].�r�nAdi << endl << yemekler[i].malzemeler[j].adedi << endl;
				}
			}
		}
	}
}

void depoSil()
{
	string malzemeIsmi;
	cout << "Silmek istedi�iniz malzemenin ad�n� T�rk�e karakter kullanmadan giriniz: " << endl;
	cin.ignore();
	getline(cin, malzemeIsmi);
	transform(malzemeIsmi.begin(), malzemeIsmi.end(), malzemeIsmi.begin(), ::tolower);
	malzemeIsmi[0] = toupper(malzemeIsmi[0]);
	for (int i = 0; i < 33; i++)// d�ng� 33 defa d�ner.
	{
		if (urun[i].�r�nAdi == malzemeIsmi)  //kullan�c�dan al�nan isim ve malzeme ismi ayn� ise null atan�r.
		{
			urun[i].�r�nAdi = "NULL";
			urun[i].kalori = 0;
			urun[i].stokAdedi = 0;
			urun[i].fiyat = 0;
			urun[i].sonkullanim = "";
			urun[i].�retim = "";
		}
	}
}

void yemeksil() {
	string yemekismii;

	cout << "Hangi yeme�i silmek istersiniz?" << endl;
	cin.ignore();
	getline(cin, yemekismii);
	transform(yemekismii.begin(), yemekismii.end(), yemekismii.begin(), ::tolower);
	yemekismii[0] = toupper(yemekismii[0]);

	for (int i = 0; i < 22; i++) // d�ng� 22 defa d�ner
	{
		if (yemekler[i].�r�nAdi == yemekismii) { //Silmek istenen yemek ismi, yemek ismi ile ayn� ise ko�ul �al���r. Ona null atan�r.
			yemekler[i].�r�nAdi = "NULL";

		}
		for (int j = 0; j < 33; j++) {//d�ng� 33 defa d�ner ve malzemelerine s�f�r de�eri atan�r.
			if (yemekler[i].malzemeler[j].adedi != 0) {
				yemekler[i].malzemeler[j].adedi = 0;
			}
		}
	}
	cout << "Silme i�lemi ger�ekle�mi�tir." << endl;
}

void depoyaEkle()
{
	int sayac = 0;
	string isim, sonkullanim, �retim;
	float kalori, stok, fiyat;

	while (urun[sayac].�r�nAdi != "NULL") //Depoya yeni �r�n eklerken bo� nesne bulur ve verileri ona yazar.
	{
		sayac++;
	}

	cout << "Eklemek istedi�iniz malzemenin ad�n� T�rk�e karakter olmadan giriniz: " << endl;
	cin.ignore();
	getline(cin, isim);
	transform(isim.begin(), isim.end(), isim.begin(), ::tolower);
	isim[0] = toupper(isim[0]);
	cout << "Eklemek istedi�iniz malzemenin stok adedini giriniz: " << endl;
	cin >> stok;
	cout << "Eklemek istedi�iniz malzemenin fiyat�n� giriniz: " << endl;
	cin >> fiyat;
	cout << "Eklemek istedi�iniz malzemenin kalorisini giriniz: " << endl;
	cin >> kalori;
	cout << "Eklemek istedi�iniz malzemenin �retim tarihini giriniz (DD / MM / YYYY format� ile):  " << endl;
	cin.ignore();
	getline(cin, �retim);
	cout << "Eklemek istedi�iniz malzemenin son t�ketim tarihini giriniz (DD / MM / YYYY format� ile): " << endl;
	cin.ignore();
	getline(cin, sonkullanim);

	urun[sayac].�r�nAdi = isim;
	urun[sayac].stokAdedi = stok;
	urun[sayac].kalori = kalori;
	urun[sayac].sonkullanim = sonkullanim;
	urun[sayac].�retim = �retim;
	urun[sayac].fiyat = fiyat;
}

void yemek�e�itiekle() { // yeni yemek �e�iti eklemeyi sa�lar.
	string yemekismi;
	int secim;
	int adet;
	char cevap;

	cout << "eklemek istedi�iniz yemek ismi nedir?" << endl;
	cin >> yemekismi;
	for (int i = 0; i < 22; i++) { // d�ng� 22 kere �al���r.

		if (yemekler[i].�r�nAdi == "NULL") { // e�er �r�n ismi null ise ko�ul sa�lan�r ve eklenen �r�n ismi ve de�erleri atan�r.

			yemekler[i].�r�nAdi = yemekismi;
		}
		do {
			cout << "Hangi malzemeden eklemek istersiniz?" << "un-0 domates-1 so�an-2 fesle�en-3" << endl << "mozerella-4 sar�msak-5 ya�-6 tuz-7" << endl << "somon-8 su-9 pirin�-10 tavuk-11" << endl << "krema-12 parmesan-13 sucuk-14 biber-15" << endl << "mantar-16 ka�ar-17 m�s�r-18 k�yma-19" << endl << "kabak-20 patl�can-21 barbek� sosu-22 d�ner-23" << endl << "kedi dili-24 kahve-25 b���rtlen-26 �eker-27" << endl << "jelatin-28 ni�asta-29 yumurta-30" << endl;
			cin >> secim;
			cout << "Malzemeden ne kadar kullan�l�yor?" << endl;
			cin >> adet;
			yemekler[i].malzemeler[secim].adedi = adet;
			cout << "devam etmek ister misiniz e/h" << endl;
			cin >> cevap;
		} while (!(cevap == 'h'));
	}
}


int main()
{
	setlocale(LC_ALL, "Turkish");
	srand(time(0));
	remove("depo.txt");
	remove("yemekcesit.txt");
	remove("malzeme.txt");

	int malzeme[32] = { 0 };
	int secim;
	char sec;

	setDepoBilgi();
	setDepo();
	yemekOlu�tur();

	for (int i = 0; i < 33; i++) //d�ng� 33 kere �al���r ve kay�tlar yap�l�r.
	{
		urun[i].setKay�tEkleme();
	}


	do {
		system("CLS");
		cout << "Yapmak istedi�iniz i�lemi se�in: " << endl << left << "1 - Sipari� Ekleme" << "\t\t  2 - Sipari� Silme" << endl << setw(30) << "3 - Depo Malzeme G�ncelleme\t" << "4 - Depo Malzeme Bilgisi G�r�nt�leme\n" << "5 - Yemek Malzeme G�ncelleme\t" << "  6 - Yemek Bilgisi G�r�nt�leme\n" << "7 - Malzeme �e�idi Ekleme\t" << "  8 - Malzeme �e�idi Silme\n" << "9 - Yemek �e�idi Ekleme\t\t" << "  10 - Yemek �e�idi Silme\t\t" << "11-Sipari� listesi g�r�nt�leme" << endl;
		cin >> secim;

		switch (secim) {
		case 1:
			siparisEkle(malzeme);
			break;

		case 2:
			siparisSil(malzeme);
			break;

		case 3:
			depoGuncelleme();
			break;

		case 4:
			malzemeBilgisiGoruntule();
			break;

		case 5:
			yemeklistesig�ncelle();
			break;

		case 6:
			yemekRaporAl();
			break;

		case 7:
			depoyaEkle();
			break;

		case 8:
			depoSil();
			break;

		case 9:
			yemek�e�itiekle();
			break;

		case 10:
			yemeksil();
			break;
		case 11:
			alisverisOlustur(malzeme, alisveris);
			break;

		default:
			cout << "Yanl�� se�im!" << endl;
			break;
		}

		cout << "\nTekrar i�lem yapmak istiyor musunuz? (e/h)" << endl;
		cin >> sec;

	} while (sec == 'e' || sec == 'E'); // tekrar i�lemini kullan�c�dan al�p ona g�re tekrar men�y� ekrana getirir.


	yemekSatis();
	setYemekKar();
	malzemeDosya(malzeme);

	int toplamKar = 0;
	for (int i = 0; i < 30; i++)//d�ng� 30 defa �al���r ve yemeklerdeki kar� toplar,totel bir kar de�eri yapar. en sonda bu de�er g�sterilir.
	{
		toplamKar += yemekler[i].kar;
	}
	cout << "G�n sonu kar-zarar durumu: " << toplamKar << endl;


}