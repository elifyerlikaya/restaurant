/********************************************************************************************************************************************
**					                                    SAKARYA ÜNÝVERSÝTESÝ											                   **
**			                                   BÝLGÝSAYAR VE BÝLÝÞÝM BÝLÝMLERÝ FAKÜLTESÝ												   **
**				                                    BÝLGÝSAYAR MÜHENDÝSLÝÐÝ BÖLÜMÜ														   **
**				                                       PROGRAMLAMAYA GÝRÝÞ DERSÝ														   **
**																																		   **
**				                            ÖDEV NUMARASI: 1.Proje																		   **
**				                              ÖÐRENCÝ ADI: Elif YERLÝKAYA																   **
**				                         ÖÐRENCÝ NUMARASI: G221210031																	   **
**				                               DERS GRUBU: Ýkinci Öðretim B Grubu													       **
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
class ürünler
{
public:

	string ürünAdi, sonkullanim, üretim;
	float kalori;
	float stokAdedi;
	float fiyat;
	void setKayýtEkleme()// depodaki ürünleri depo.txt dosyasýna yazar.
	{
		ofstream kayýtEkle;
		kayýtEkle.open("depo.txt", ios::app);
		kayýtEkle << ürünAdi << " kalorisi: " << kalori << endl << ürünAdi << " stok adedi: " << stokAdedi << endl << ürünAdi << " fiyatý: " << fiyat << endl << ürünAdi << " üretim tarihi: " << üretim << endl << ürünAdi << " son kullanma tarihi: " << sonkullanim << endl << endl;
		kayýtEkle.close();
	}

	void kayýtsilme() {// depodan istenen deðeri siler ayný þekilde depo.txt dosyasýndan da siler
		ifstream okuma;
		okuma.open("depo.txt", ios::app);
		ofstream geçicidosya;
		geçicidosya.open("geçici.txt", ios::app | ios::out);
		string satýr;
		while (getline(okuma, satýr)) {
			if (satýr.substr(0, ürünAdi.size()) != ürünAdi) {
				geçicidosya << satýr << endl;
			}
		}
		okuma.close();
		geçicidosya.close();
		remove("depo.txt");
		rename("geçici.txt", "depo.txt");
	}
	void kayýtgüncelleme() //depodaki ürün bilgilerini güncellemeyi saðlar.
	{

		cout << "Ürünün 100gr'daki güncellenmiþ kalorisini giriniz:" << endl;
		cin >> kalori;
		cout << "Ürünün güncellenmiþ stok adedini giriniz:" << endl;
		cin >> stokAdedi;
		cout << "Ürünün güncellenmiþ fiyatýný giriniz:" << endl;
		cin >> fiyat;
		cout << "Ürünün güncellenmiþ üretim tarihini giriniz: " << endl;
		cin >> üretim;
		cout << "Ürünün güncellenmiþ son kullaným tarihini giriniz: " << endl;
		cin >> sonkullanim;

	}
	void raporal() { // depodaki ürünler hakkýnda rapor almayý saðlar.
		ifstream okuma;
		okuma.open("depo.txt", ios::app);
		ofstream geçicidosya;
		geçicidosya.open("geçici.txt", ios::app | ios::out);
		string satýr;
		while (getline(okuma, satýr)) {
			if (satýr.substr(0, ürünAdi.size()) == ürünAdi) {
				geçicidosya << satýr << endl;
			}
		}
		okuma.close();
		geçicidosya.close();
		remove("depo.txt");
		rename("geçici.txt", "depo.txt");
	}
};

ürünler urun[34];
int alisveris[34] = { 0 };

struct malzemeler {
	int adedi;
	malzemeler()
	{
		adedi = 0;
	}
};

struct yemekler {
	string ürünAdi;
	double maliyet, satis, kar;
	int adet, satisAdet;
	malzemeler malzemeler[34];
	yemekler()
	{
		adet = 0;
	}
}yemekler[22];

void malzemeDosya(int* malzeme) //Malzeme dosyasýna malzemeleri yazar.
{
	ofstream malzemeListesi;
	malzemeListesi.open("malzeme.txt");
	for (int i = 0; i < 33; i++) //Döngü 33 kere döner ve malzemeleri sýrayla malzeme listesine yazar.
	{
		malzemeListesi << urun[i].ürünAdi << " " << malzeme[i] << endl;
	}
}

void yemekRaporAl() // Seçilen yemek doðrultusunda satýþ fiyatý,malzemeleri kalorisi gibi raporlarý almaya saðlar.
{
	string yemekismi;
	double kalori = 0;

	cout << "Görüntülemek istediðiniz yemeðin ismini giriniz" << endl;
	cin.ignore();
	getline(cin, yemekismi);
	transform(yemekismi.begin(), yemekismi.end(), yemekismi.begin(), ::tolower);
	yemekismi[0] = toupper(yemekismi[0]);

	for (int i = 0; i < 22; i++) {// Döngü 22 defa döner.
		if (yemekler[i].ürünAdi == yemekismi) // Kullanýcýdan alýnan isim ve yemek ismini karþýlaþtýrýr. Ayný ise koþul çalýþýr.
		{
			cout << endl << yemekler[i].ürünAdi << " ";
			cout << yemekler[i].satis << " TL" << endl << endl;
			for (int j = 0; j < 32; j++) { // Döngü 33 defa çalýþýr.
				if (yemekler[i].malzemeler[j].adedi != 0) { // Yemekteki malzeme adedi sýfýr deðilse koþul çalýþýr.
					kalori += urun[j].kalori; //Koþuldaki ürünlerin kalorini toplar.
					cout << urun[j].ürünAdi << endl << yemekler[i].malzemeler[j].adedi << " gr" << endl;
				}
			}
		}
	}
	cout << "\nKalori: " << kalori << " cal" << endl;
}

void yemekSatis() //restorantýn günlük yemeklerden ne kadar sattýðýný random olarak belirler.
{
	for (int i = 0; i < 22; i++) //Döngü 22 defa çalýþýr.
	{
		if (yemekler[i].adet != 0)//Yemek adedi sýfýrdan farklý ise koþul saðlanýr.
		{
			yemekler[i].satisAdet = rand() % yemekler[i].adet + 1; // satýþ adedi random þekilde atanýr.
		}
	}

}

int siparisSil(int* malzeme)// Seçilen yemeðe göre silme iþlemini yapar. Malzemelerinin kullanýmýna göre malzemeleri azaltýr.
{
	int secim, adet;
	char sec;
	do {
		cout << "Silmek istediðiniz yemeði yazýn" << endl << "1-Bruschetta " << "2-Risotto " << "3-Tortellini " << "4-Bolonez Soslu Spagetti " << "5-Pesto Soslu Linguine " << "6-Fettucine Alfredo " << "7-Lazanya " << "8-Kremalý Mantar Soslu Penne " << "9-Penne Arabiatta " << "10-Napoliten Soslu Spagetti " << "11-Margarita Pizza " << "12-Karýþýk Pizza " << "13-Üç Peynirli Pizza " << "14-Vejetaryen Pizza " << "15-Barbekü Soslu Tavuklu Pizza " << "16-Pepperoni Pizza " << "17-Dönerli Pizza " << "18-Tiramisu " << "19- Böðürtlen Soslu Panna Cotta " << "20-Cannoli " << endl; ;
		cin >> secim;
		cout << "Kaç adet silmek istiyorsunuz: ";
		cin >> adet;
		switch (secim) { // seçilen yemek ismine göre swith case çalýþýr.
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

int siparisEkle(int* malzeme) // Seçilen yemeðe göre ekleme iþlemini yapar. Malzemelerinin kullanýmýna göre malzemeleri arttýrýr.
{
	int secim, adet;
	char sec;
	do {
		cout << "Hangi yemekten ekleme yapacaðýnýzý seçiniz: " << endl << "1-Bruschetta 2-Risotto 3-Tortellini 4-Bolonez Soslu Spagetti 5-Pesto Soslu Linguine 6-Fettucine Alfredo 7-Lazanya 8-Kremalý Mantar Soslu Penne 9-Penne Arabiatta 10-Napoliten soslu Spagetti 11-Margarita Pizza 12-Karýþýk Pizza 13-Üç Peynirli Pizza 14-Vejetaryen Pizza 15-Barbekü Soslu Pizza 16-Pepperoni Pizza 17-Dönerli Pizza 18-Tiramisu 19-Böðürtlenli Panna Cotta 20-Cannoli" << endl;
		cin >> secim;
		cout << "Kaç tane eklemek istiyorsunuz?" << endl;
		cin >> adet;
		switch (secim) { // Seçilen yemek numarasýna göre switch case çalýþýr.
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
			cout << "Yanlýþ seçim yaptýnýz!.." << endl;
		}
		cout << "Devam etmek istiyor musunuz? (e/h)" << endl;
		cin >> sec;
	} while (sec == 'e' || sec == 'E'); // kullanýcýdan aldýðý devam edip etmemek kararýna göre tekrar ayný iþlemi yapar.
	int malzeme1[32];
	for (int i = 0; i < 33; i++)
	{
		malzeme1[i] = malzeme[i];
	}
	return *malzeme;
}

int alisverisOlustur(int* malzeme, int* alisveris) // Yapýlacak yemeðin ürünlerini depo ile karþýlaþtýrýr, eksik malzemeler için sipariþ listesi oluþturur ve oraya kaydeder.
{
	remove("alisverisListesi.txt");
	ofstream alisverisListesi;
	alisverisListesi.open("AlisverisListesi.txt");
	for (int i = 0; i < 33; i++) // döngü 33 defa çalýþýr.
	{
		if (urun[i].stokAdedi < malzeme[i]) // eðer ürün stok adedi sipariþte verilen malzemeden az ise alýþveriþ listesine eksik olan miktarý ekler.
		{
			alisveris[i] = malzeme[i] - urun[i].stokAdedi;
			urun[i].stokAdedi = 0;
		}
		else
		{
			urun[i].stokAdedi -= malzeme[i]; // eðer ürün stok adedi yeterli ise sipariþte kullanýlan malzemeyi depodan siler.
		}
	}
	for (int i = 0; i < 33; i++) // döngü 33 defa çalýþýr ve alýþveriþ listesine ürünler yazdýrýlýr.
	{
		if (urun[i].ürünAdi != "NULL") {
			alisverisListesi << "Alýnacak " << urun[i].ürünAdi << ": " << alisveris[i] << endl;
			cout << "Alýnacak" << urun[i].ürünAdi << ": " << alisveris[i] << endl;
		}
	}
	return *alisveris;


}

void yemekOluþtur() //Yemek çeþitlerinde hangi yemekte hangi malzemenin ne kadar olduðu, yemek adý ile manuel atanýr. Yemek çeþidi dosyasýna bu veriler yazýlýr.
{
	ofstream yemek;
	yemek.open("yemekcesit.txt", ios::in | ios::app);
	yemekler[0].ürünAdi = "Bruschetta";
	yemekler[0].malzemeler[1].adedi = 75;
	yemekler[0].malzemeler[2].adedi = 50;
	yemekler[0].malzemeler[3].adedi = 25;
	yemekler[0].malzemeler[5].adedi = 5;
	yemekler[0].malzemeler[6].adedi = 20;
	yemekler[0].malzemeler[7].adedi = 5;
	yemekler[0].malzemeler[8].adedi = 75;
	yemekler[0].malzemeler[9].adedi = 150;
	yemekler[0].malzemeler[0].adedi = 150;

	yemekler[1].ürünAdi = "Risotto";
	yemekler[1].malzemeler[2].adedi = 50;
	yemekler[1].malzemeler[6].adedi = 50;
	yemekler[1].malzemeler[10].adedi = 200;
	yemekler[1].malzemeler[11].adedi = 200;
	yemekler[1].malzemeler[13].adedi = 50;
	yemekler[1].malzemeler[7].adedi = 5;

	yemekler[2].ürünAdi = "Tortellini";
	yemekler[2].malzemeler[0].adedi = 200;
	yemekler[2].malzemeler[9].adedi = 100;
	yemekler[2].malzemeler[12].adedi = 100;
	yemekler[2].malzemeler[7].adedi = 5;
	yemekler[2].malzemeler[6].adedi = 10;
	yemekler[2].malzemeler[4].adedi = 70;

	yemekler[3].ürünAdi = "Bolonez Soslu Spagetti";
	yemekler[3].malzemeler[0].adedi = 200;
	yemekler[3].malzemeler[9].adedi = 100;
	yemekler[3].malzemeler[7].adedi = 5;
	yemekler[3].malzemeler[1].adedi = 100;
	yemekler[3].malzemeler[19].adedi = 100;
	yemekler[3].malzemeler[2].adedi = 50;
	yemekler[3].malzemeler[6].adedi = 20;

	yemekler[4].ürünAdi = "Pesto Soslu Lnguine";
	yemekler[4].malzemeler[0].adedi = 200;
	yemekler[4].malzemeler[9].adedi = 100;
	yemekler[4].malzemeler[3].adedi = 50;
	yemekler[4].malzemeler[13].adedi = 50;
	yemekler[4].malzemeler[6].adedi = 20;
	yemekler[4].malzemeler[7].adedi = 5;

	yemekler[5].ürünAdi = "Fettucine Alfredo";
	yemekler[5].malzemeler[0].adedi = 200;
	yemekler[5].malzemeler[9].adedi = 100;
	yemekler[5].malzemeler[6].adedi = 20;
	yemekler[5].malzemeler[7].adedi = 5;
	yemekler[5].malzemeler[16].adedi = 50;
	yemekler[5].malzemeler[11].adedi = 70;
	yemekler[5].malzemeler[12].adedi = 50;

	yemekler[6].ürünAdi = "Lazanya";
	yemekler[6].malzemeler[0].adedi = 200;
	yemekler[6].malzemeler[9].adedi = 100;
	yemekler[6].malzemeler[6].adedi = 20;
	yemekler[6].malzemeler[7].adedi = 5;
	yemekler[6].malzemeler[12].adedi = 50;
	yemekler[6].malzemeler[19].adedi = 100;
	yemekler[6].malzemeler[17].adedi = 70;

	yemekler[7].ürünAdi = "Kremali Mantar Soslu Penne";
	yemekler[7].malzemeler[0].adedi = 200;
	yemekler[7].malzemeler[9].adedi = 100;
	yemekler[7].malzemeler[6].adedi = 20;
	yemekler[7].malzemeler[7].adedi = 5;
	yemekler[7].malzemeler[16].adedi = 50;
	yemekler[7].malzemeler[12].adedi = 50;

	yemekler[8].ürünAdi = "Penne Arabiatta";
	yemekler[8].malzemeler[0].adedi = 200;
	yemekler[8].malzemeler[9].adedi = 100;
	yemekler[8].malzemeler[6].adedi = 20;
	yemekler[8].malzemeler[7].adedi = 5;
	yemekler[8].malzemeler[1].adedi = 100;
	yemekler[8].malzemeler[15].adedi = 50;
	yemekler[2].malzemeler[12].adedi = 50;

	yemekler[9].ürünAdi = "Napoliten Soslu Spagetti";
	yemekler[9].malzemeler[0].adedi = 200;
	yemekler[9].malzemeler[9].adedi = 100;
	yemekler[9].malzemeler[6].adedi = 20;
	yemekler[9].malzemeler[7].adedi = 5;
	yemekler[9].malzemeler[1].adedi = 100;
	yemekler[9].malzemeler[15].adedi = 30;

	yemekler[10].ürünAdi = "Margarita Pizza";
	yemekler[10].malzemeler[0].adedi = 200;
	yemekler[10].malzemeler[9].adedi = 100;
	yemekler[10].malzemeler[6].adedi = 20;
	yemekler[10].malzemeler[7].adedi = 5;
	yemekler[10].malzemeler[1].adedi = 100;
	yemekler[10].malzemeler[4].adedi = 100;

	yemekler[11].ürünAdi = "Karisik Pizza";
	yemekler[11].malzemeler[0].adedi = 200;
	yemekler[11].malzemeler[9].adedi = 100;
	yemekler[11].malzemeler[6].adedi = 20;
	yemekler[11].malzemeler[7].adedi = 5;
	yemekler[11].malzemeler[1].adedi = 100;
	yemekler[11].malzemeler[17].adedi = 100;
	yemekler[11].malzemeler[14].adedi = 80;
	yemekler[11].malzemeler[18].adedi = 30;

	yemekler[12].ürünAdi = "Uc Peynirli Pizza";
	yemekler[12].malzemeler[0].adedi = 200;
	yemekler[12].malzemeler[9].adedi = 100;
	yemekler[12].malzemeler[6].adedi = 20;
	yemekler[12].malzemeler[7].adedi = 5;
	yemekler[12].malzemeler[1].adedi = 100;
	yemekler[12].malzemeler[4].adedi = 75;
	yemekler[12].malzemeler[17].adedi = 75;
	yemekler[12].malzemeler[13].adedi = 75;

	yemekler[13].ürünAdi = "Vejetaryen Pizza";
	yemekler[13].malzemeler[0].adedi = 200;
	yemekler[13].malzemeler[9].adedi = 100;
	yemekler[13].malzemeler[6].adedi = 20;
	yemekler[13].malzemeler[7].adedi = 5;
	yemekler[13].malzemeler[1].adedi = 100;
	yemekler[13].malzemeler[20].adedi = 50;
	yemekler[13].malzemeler[21].adedi = 40;
	yemekler[13].malzemeler[17].adedi = 75;

	yemekler[14].ürünAdi = "Barbeku Soslu Tavuklu Pizza";
	yemekler[14].malzemeler[0].adedi = 200;
	yemekler[14].malzemeler[9].adedi = 100;
	yemekler[14].malzemeler[6].adedi = 20;
	yemekler[14].malzemeler[7].adedi = 5;
	yemekler[14].malzemeler[1].adedi = 100;
	yemekler[14].malzemeler[22].adedi = 50;
	yemekler[14].malzemeler[11].adedi = 150;

	yemekler[15].ürünAdi = "Pepperoni Pizza";
	yemekler[15].malzemeler[0].adedi = 200;
	yemekler[15].malzemeler[9].adedi = 100;
	yemekler[15].malzemeler[6].adedi = 20;
	yemekler[15].malzemeler[7].adedi = 5;
	yemekler[15].malzemeler[1].adedi = 100;
	yemekler[15].malzemeler[14].adedi = 75;
	yemekler[15].malzemeler[4].adedi = 80;

	yemekler[16].ürünAdi = "Donerli Pizza";
	yemekler[16].malzemeler[0].adedi = 200;
	yemekler[16].malzemeler[9].adedi = 100;
	yemekler[16].malzemeler[6].adedi = 20;
	yemekler[16].malzemeler[7].adedi = 5;
	yemekler[16].malzemeler[1].adedi = 100;
	yemekler[16].malzemeler[17].adedi = 100;
	yemekler[16].malzemeler[23].adedi = 100;

	yemekler[17].ürünAdi = "Tiramisu";
	yemekler[17].malzemeler[24].adedi = 150;
	yemekler[17].malzemeler[25].adedi = 50;
	yemekler[17].malzemeler[12].adedi = 150;
	yemekler[17].malzemeler[27].adedi = 100;

	yemekler[18].ürünAdi = "Bogurtlen Soslu Panna Cotta";
	yemekler[18].malzemeler[12].adedi = 150;
	yemekler[18].malzemeler[26].adedi = 100;
	yemekler[18].malzemeler[28].adedi = 50;
	yemekler[18].malzemeler[27].adedi = 100;
	yemekler[18].malzemeler[29].adedi = 50;

	yemekler[19].ürünAdi = "Cannoli";
	yemekler[19].malzemeler[27].adedi = 50;
	yemekler[19].malzemeler[6].adedi = 50;
	yemekler[19].malzemeler[30].adedi = 50;
	yemekler[19].malzemeler[0].adedi = 300;
	yemekler[19].malzemeler[12].adedi = 150;
	for (int i = 0; i < 22; i++) // döngü 22 defa çalýþýr ve yemek dosyasýna verileri yazar.
	{
		yemek << yemekler[i].ürünAdi << endl;
	}
}
void setYemekKar()// Restorantta yapýlan yemeðin satýþýna da bakarak kar-zarar hesabý yapar.
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


void setDepoBilgi()								//Urun dizisinin elemanlarýna malzeme isimleri,malzeme fiyatlarý,kalorisi, son tüketim ve üretim tarihleri atanýyor.
{
	urun[0].ürünAdi = "Un";
	urun[1].ürünAdi = "Domates";
	urun[2].ürünAdi = "Sogan";
	urun[3].ürünAdi = "Feslegen";
	urun[4].ürünAdi = "Mozarella";
	urun[5].ürünAdi = "Sarýmsak";
	urun[6].ürünAdi = "Yag";
	urun[7].ürünAdi = "Tuz";
	urun[8].ürünAdi = "Somon";
	urun[9].ürünAdi = "Su";
	urun[10].ürünAdi = "Pirinc";
	urun[11].ürünAdi = "Tavuk";
	urun[12].ürünAdi = "Krema";
	urun[13].ürünAdi = "Parmesan";
	urun[14].ürünAdi = "Sucuk";
	urun[15].ürünAdi = "Biber";
	urun[16].ürünAdi = "Mantar";
	urun[17].ürünAdi = "Kasar";
	urun[18].ürünAdi = "Misir";
	urun[19].ürünAdi = "Kiyma";
	urun[20].ürünAdi = "Kabak";
	urun[21].ürünAdi = "Patlican";
	urun[22].ürünAdi = "Barbeku sosu";
	urun[23].ürünAdi = "Doner";
	urun[24].ürünAdi = "Kedi dili";
	urun[25].ürünAdi = "Kahve";
	urun[26].ürünAdi = "Bogurtlen";
	urun[27].ürünAdi = "Seker";
	urun[28].ürünAdi = "Jelatin";
	urun[29].ürünAdi = "Nisasta";
	urun[30].ürünAdi = "Yumurta";
	urun[31].ürünAdi = "NULL";
	urun[32].ürünAdi = "NULL";
	urun[33].ürünAdi = "NULL";

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

	urun[0].üretim = "21 / 01 / 2021";
	urun[1].üretim = "12 / 02 / 2022";
	urun[2].üretim = "29 / 09 / 2022";
	urun[3].üretim = "21 / 04 / 2022";
	urun[4].üretim = "04 / 11 / 2021";
	urun[5].üretim = "06 / 12 / 2022";
	urun[6].üretim = "14 / 07 / 2020";
	urun[7].üretim = "26 / 06 / 2022";
	urun[8].üretim = "09 / 03 / 2021";
	urun[9].üretim = "07 / 05 / 2022";
	urun[10].üretim = "12 / 01 / 2020";
	urun[11].üretim = "16 / 06 / 2022";
	urun[12].üretim = "24 / 07 / 2021";
	urun[13].üretim = "28 / 09 / 2022";
	urun[14].üretim = "21 / 06 / 2022";
	urun[15].üretim = "29 / 01 / 2021";
	urun[16].üretim = "11 / 02 / 2022";
	urun[17].üretim = "19 / 05 / 2022";
	urun[18].üretim = "29 / 07 / 2021";
	urun[19].üretim = "27 / 08 / 2020";
	urun[20].üretim = "01 / 09 / 2021";
	urun[21].üretim = "03 / 12 / 2022";
	urun[22].üretim = "09 / 11 / 2021";
	urun[23].üretim = "17 / 05 / 2022";
	urun[24].üretim = "19 / 04 / 2021";
	urun[25].üretim = "23 / 06 / 2021";
	urun[26].üretim = "29 / 05 / 2022";
	urun[27].üretim = "02 / 03 / 2020";
	urun[28].üretim = "25 / 04 / 2022";
	urun[29].üretim = "29 / 06 / 2022";
	urun[30].üretim = "27 / 07 / 2021";
}

void setDepo()
{
	for (int i = 0; i < 33; i++) // döngü 33 defa çalýþýr 
	{
		urun[i].stokAdedi = 750 + rand() % 1251;		//Her bir malzeme için depo stok adetleri rastgele 750 ila 2000 olacak þekilde atanýr.
	}
}

void malzemeBilgisiGoruntule() // Malzeme hakkýnda rapor almaya yarayan fonksiyondur. Kullanýcýdan görüntülemek istediði ürünün ismini alýp ürün hakkýndaki verileri yazar.
{
	string malzemeIsim;
	cout << "Görüntülemek istediðiniz ürünün adýný yazýnýz: " << endl;
	cin.ignore();
	getline(cin, malzemeIsim);
	transform(malzemeIsim.begin(), malzemeIsim.end(), malzemeIsim.begin(), ::tolower);
	malzemeIsim[0] = toupper(malzemeIsim[0]);
	for (int i = 0; i < 33; i++) // döngü 33 defa çalýþýr 
	{
		if (urun[i].ürünAdi == malzemeIsim)  //kullanýcýdan alýnan malzeme ile ürün ismi eþit olursa koþul çalýþýr.
		{
			cout << left << "\tÜrün adý: " << urun[i].ürünAdi << endl;
			cout << left << "\tÜrünün fiyatý: " << urun[i].fiyat << endl;
			cout << left << "\tÜrünün stok adedi: " << urun[i].stokAdedi << endl;
			cout << left << "\tÜrünün 100 gramda kalori deðeri: " << urun[i].kalori << endl;
			cout << left << "\tÜrünün üretim tarihi: " << urun[i].üretim << endl;
			cout << left << "\tÜrünün son kullanma tarihi: " << urun[i].sonkullanim << endl;

		}
	}
}

void depoGuncelleme() //Depodaki seçilen malzemenin stok adedini güncellemeyi saðlar.
{
	string malzemeIsim;
	int guncelStok;
	remove("depo.txt");
	cout << "Hangi malzemeyi güncellemek istiyorsunuz? (Ürün adý yazarken Türkçe karakter kullanmayýn!.." << endl;
	cin.ignore();
	getline(cin, malzemeIsim);
	transform(malzemeIsim.begin(), malzemeIsim.end(), malzemeIsim.begin(), ::tolower);
	malzemeIsim[0] = toupper(malzemeIsim[0]);
	for (int i = 0; i < 33; i++) // döngü 33 defa döner.
	{
		if (urun[i].ürünAdi == malzemeIsim)  //kullanýcýdan alýnan malzeme ile ürün ismi eþit olursa koþul çalýþýr.
		{
			urun[i].kayýtgüncelleme();
		}
		urun[i].setKayýtEkleme();
	}
}

void yemeklistesigüncelle() // Seçilen yemekte kullanýlan malzemelerin miktarýný arttýrýp azaltmaya yarar.
{
	string yemekismi;
	int sayi;
	int secim;
	double artis;
	double azalis;
	cout << "Güncellemek istediðiniz yemeðin ismini giriniz" << endl;
	cin.ignore();
	getline(cin, yemekismi);
	transform(yemekismi.begin(), yemekismi.end(), yemekismi.begin(), ::tolower);
	yemekismi[0] = toupper(yemekismi[0]);

	for (int i = 0; i < 22; i++) // döngü 22 defa döner
	{
		if (yemekler[i].ürünAdi == yemekismi) //kullanýcýdan alýnan yemek ismi, yemek ismi ile uyuþursa koþul saðlanýr.
		{
			cout << "Hangi malzemeyi deðiþtirmek istersiniz?" << endl << "un-0 domates-1 soðan-2 fesleðen-3" << endl << "mozerella-4 sarýmsak-5 yað-6 tuz-7" << endl << "somon-8 su-9 pirinç-10 tavuk-11" << endl << "krema-12 parmesan-13 sucuk-14 biber-15" << endl << "mantar-16 kaþar-17 mýsýr-18 kýyma-19" << endl << "kabak-20 patlýcan-21 barbekü sosu-22 döner-23" << endl << "kedi dili-24 kahve-25 böðürtlen-26 þeker-27" << endl << "jelatin-28 niþasta-29 yumurta-30" << endl;
			cin >> sayi;
			cout << "Azaltmak mý arttýrmak mý istersiniz? arttýrmak için 1, azaltmak için 2yi tuþlayýnýz" << endl;
			cin >> secim;
			switch (secim)
			{
			case 1:
				cout << "Ne kadar arttýrmak istersiniz?" << endl;
				cin >> artis;
				yemekler[i].malzemeler[sayi].adedi += artis; // yemekteki malzemelerin miktarýna kullanýcýdan alýnan artýþ deðerini ekler
				break;

			case 2:
				cout << "Ne kadar azaltmak istersiniz?" << endl;// yemekteki malzemelerin miktarýna kullanýcýdan alýnan azalýþ deðerini çýkarýr.
				cin >> azalis;
				yemekler[i].malzemeler[sayi].adedi -= azalis;
				break;
			}
		}

	}
	cout << "Güncelleme bitmiþtir.." << endl << "seçilen yemegin güncellenmis hali:" << endl; //güncellenmiþ yemek ve malzemelerini yazdýrýr.
	for (int i = 0; i < 22; i++) { // döngü 22 defa çalýþýr 
		if (yemekler[i].ürünAdi == yemekismi) // kullanýcýdan alýnan yemek ismi ile yemek ismi uyuþursa koþul çalýþýr.
		{
			cout << yemekler[i].ürünAdi << endl;
			for (int j = 0; j < 32; j++) { // döngü 32 defa çalýþýr.
				if (yemekler[i].malzemeler[j].adedi != 0) { // eðer malzeme adedi sýfýrdan farklý ise koþul saðlanýr.
					cout << urun[j].ürünAdi << endl << yemekler[i].malzemeler[j].adedi << endl;
				}
			}
		}
	}
}

void depoSil()
{
	string malzemeIsmi;
	cout << "Silmek istediðiniz malzemenin adýný Türkçe karakter kullanmadan giriniz: " << endl;
	cin.ignore();
	getline(cin, malzemeIsmi);
	transform(malzemeIsmi.begin(), malzemeIsmi.end(), malzemeIsmi.begin(), ::tolower);
	malzemeIsmi[0] = toupper(malzemeIsmi[0]);
	for (int i = 0; i < 33; i++)// döngü 33 defa döner.
	{
		if (urun[i].ürünAdi == malzemeIsmi)  //kullanýcýdan alýnan isim ve malzeme ismi ayný ise null atanýr.
		{
			urun[i].ürünAdi = "NULL";
			urun[i].kalori = 0;
			urun[i].stokAdedi = 0;
			urun[i].fiyat = 0;
			urun[i].sonkullanim = "";
			urun[i].üretim = "";
		}
	}
}

void yemeksil() {
	string yemekismii;

	cout << "Hangi yemeði silmek istersiniz?" << endl;
	cin.ignore();
	getline(cin, yemekismii);
	transform(yemekismii.begin(), yemekismii.end(), yemekismii.begin(), ::tolower);
	yemekismii[0] = toupper(yemekismii[0]);

	for (int i = 0; i < 22; i++) // döngü 22 defa döner
	{
		if (yemekler[i].ürünAdi == yemekismii) { //Silmek istenen yemek ismi, yemek ismi ile ayný ise koþul çalýþýr. Ona null atanýr.
			yemekler[i].ürünAdi = "NULL";

		}
		for (int j = 0; j < 33; j++) {//döngü 33 defa döner ve malzemelerine sýfýr deðeri atanýr.
			if (yemekler[i].malzemeler[j].adedi != 0) {
				yemekler[i].malzemeler[j].adedi = 0;
			}
		}
	}
	cout << "Silme iþlemi gerçekleþmiþtir." << endl;
}

void depoyaEkle()
{
	int sayac = 0;
	string isim, sonkullanim, üretim;
	float kalori, stok, fiyat;

	while (urun[sayac].ürünAdi != "NULL") //Depoya yeni ürün eklerken boþ nesne bulur ve verileri ona yazar.
	{
		sayac++;
	}

	cout << "Eklemek istediðiniz malzemenin adýný Türkçe karakter olmadan giriniz: " << endl;
	cin.ignore();
	getline(cin, isim);
	transform(isim.begin(), isim.end(), isim.begin(), ::tolower);
	isim[0] = toupper(isim[0]);
	cout << "Eklemek istediðiniz malzemenin stok adedini giriniz: " << endl;
	cin >> stok;
	cout << "Eklemek istediðiniz malzemenin fiyatýný giriniz: " << endl;
	cin >> fiyat;
	cout << "Eklemek istediðiniz malzemenin kalorisini giriniz: " << endl;
	cin >> kalori;
	cout << "Eklemek istediðiniz malzemenin üretim tarihini giriniz (DD / MM / YYYY formatý ile):  " << endl;
	cin.ignore();
	getline(cin, üretim);
	cout << "Eklemek istediðiniz malzemenin son tüketim tarihini giriniz (DD / MM / YYYY formatý ile): " << endl;
	cin.ignore();
	getline(cin, sonkullanim);

	urun[sayac].ürünAdi = isim;
	urun[sayac].stokAdedi = stok;
	urun[sayac].kalori = kalori;
	urun[sayac].sonkullanim = sonkullanim;
	urun[sayac].üretim = üretim;
	urun[sayac].fiyat = fiyat;
}

void yemekçeþitiekle() { // yeni yemek çeþiti eklemeyi saðlar.
	string yemekismi;
	int secim;
	int adet;
	char cevap;

	cout << "eklemek istediðiniz yemek ismi nedir?" << endl;
	cin >> yemekismi;
	for (int i = 0; i < 22; i++) { // döngü 22 kere çalýþýr.

		if (yemekler[i].ürünAdi == "NULL") { // eðer ürün ismi null ise koþul saðlanýr ve eklenen ürün ismi ve deðerleri atanýr.

			yemekler[i].ürünAdi = yemekismi;
		}
		do {
			cout << "Hangi malzemeden eklemek istersiniz?" << "un-0 domates-1 soðan-2 fesleðen-3" << endl << "mozerella-4 sarýmsak-5 yað-6 tuz-7" << endl << "somon-8 su-9 pirinç-10 tavuk-11" << endl << "krema-12 parmesan-13 sucuk-14 biber-15" << endl << "mantar-16 kaþar-17 mýsýr-18 kýyma-19" << endl << "kabak-20 patlýcan-21 barbekü sosu-22 döner-23" << endl << "kedi dili-24 kahve-25 böðürtlen-26 þeker-27" << endl << "jelatin-28 niþasta-29 yumurta-30" << endl;
			cin >> secim;
			cout << "Malzemeden ne kadar kullanýlýyor?" << endl;
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
	yemekOluþtur();

	for (int i = 0; i < 33; i++) //döngü 33 kere çalýþýr ve kayýtlar yapýlýr.
	{
		urun[i].setKayýtEkleme();
	}


	do {
		system("CLS");
		cout << "Yapmak istediðiniz iþlemi seçin: " << endl << left << "1 - Sipariþ Ekleme" << "\t\t  2 - Sipariþ Silme" << endl << setw(30) << "3 - Depo Malzeme Güncelleme\t" << "4 - Depo Malzeme Bilgisi Görüntüleme\n" << "5 - Yemek Malzeme Güncelleme\t" << "  6 - Yemek Bilgisi Görüntüleme\n" << "7 - Malzeme Çeþidi Ekleme\t" << "  8 - Malzeme Çeþidi Silme\n" << "9 - Yemek Çeþidi Ekleme\t\t" << "  10 - Yemek Çeþidi Silme\t\t" << "11-Sipariþ listesi görüntüleme" << endl;
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
			yemeklistesigüncelle();
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
			yemekçeþitiekle();
			break;

		case 10:
			yemeksil();
			break;
		case 11:
			alisverisOlustur(malzeme, alisveris);
			break;

		default:
			cout << "Yanlýþ seçim!" << endl;
			break;
		}

		cout << "\nTekrar iþlem yapmak istiyor musunuz? (e/h)" << endl;
		cin >> sec;

	} while (sec == 'e' || sec == 'E'); // tekrar iþlemini kullanýcýdan alýp ona göre tekrar menüyü ekrana getirir.


	yemekSatis();
	setYemekKar();
	malzemeDosya(malzeme);

	int toplamKar = 0;
	for (int i = 0; i < 30; i++)//döngü 30 defa çalýþýr ve yemeklerdeki karý toplar,totel bir kar deðeri yapar. en sonda bu deðer gösterilir.
	{
		toplamKar += yemekler[i].kar;
	}
	cout << "Gün sonu kar-zarar durumu: " << toplamKar << endl;


}