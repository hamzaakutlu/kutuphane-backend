#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



typedef struct Kitap {
	int barkod;
	char kitapAdi[30];
	char yazarAdi[30];
	char sayfasayisi[30];
	char temintarihi[30];
	} kitap ;

typedef struct Uye {
	int numara;
	char kullanicinumarasi[30];
	char adsoyad[30];
	char KullaniciDogumTarihi[30];
} uye ;

typedef struct Odunc {
    char AliciNumarasi[30];
    int kitapbarkod;
    time_t AlisTarihi;
    time_t Bitistarihi;
    int kullandigiGunSayisi;
} odunc;




void KitapEkle()
{
	
	printf("-----Kitap Ekleme Ekrani-----\n\n");

	kitap k1;


	 srand((unsigned int)time(NULL));
	k1.barkod = rand() % 1001;

    printf("Barkod: %d\n", k1.barkod);
	printf("\nKitap Adi: ");    scanf(" %[^\n]", k1.kitapAdi);
	printf("Yazar Adi: ");    scanf(" %[^\n]", k1.yazarAdi);
	printf("Sayfa Sayisi: "); scanf("%d", &k1.sayfasayisi);
	printf("Yayinlanma"""""""""""" Tarihi: ");  scanf(" %[^\n]", k1.temintarihi);

	FILE * ptr = fopen("Kitap Ýþlemleri.dat","a+b");
	fwrite( &k1, sizeof(kitap), 1, ptr);
	fclose(ptr);
}
void KitapListeleme()
{
		
	printf("-----Kitap Listeleme Ekrani-----\n\n");

	kitap k1;
	int kitapsayisi=0;

	FILE * ptr = fopen("Kitap Ýþlemleri.dat","r+b");

	printf("%-20s%-30s%-30s%-30s%-30s\n", "BARKOD","KITAP-ADI","YAZAR-ADI","SAYFA-SAYISI","TEMIN-TARIHI");

	while(	fread( &k1, sizeof(kitap), 1, ptr) !=NULL ) // okuma iþemi baþarýlýysa devam eder 
	{
		printf("%-30d%-30s%-30s%-30d%-30s\n", k1.barkod, k1.kitapAdi, k1.yazarAdi, k1.sayfasayisi, k1.temintarihi );
		kitapsayisi++;
	}


	fclose(ptr);
	printf("\n 	toplam Kitap Sayisi : %d \n", kitapsayisi);

}
void KitapGuncelleme()
{
    
    printf("-----Kitap Guncelleme Ekrani-----\n\n");

    kitap k1;
    int barkod, sonuc = 0;

    printf("Barkod :   ");
    scanf("%d", &barkod);

    FILE *ptr = fopen("Kitap Ýþlemleri.dat", "r+b");
    FILE *yptr = fopen("Yedek Kitap Ýþlemleri.dat", "w+b");

    while (fread(&k1, sizeof(kitap), 1, ptr) != NULL) // kitaplar okunur baþarýlýysa devam eder
    {
        if (barkod != k1.barkod)
            fwrite(&k1, sizeof(kitap), 1, yptr); // eðer eþleþmiyorsa yptre yazdýrýr
        else
        {
            sonuc = 1; // eðer eþleþme varsa deðiþkennini 1 yapar ve yeni bilgileri ister

            printf("\nYeni Bilgileri Giriniz:\n");
            printf("Kitap Adi: ");
            scanf(" %[^\n]", k1.kitapAdi);
            printf("Yazar Adi: ");
            scanf(" %[^\n]", k1.yazarAdi);
            printf("Sayfa Sayisi: ");
            scanf("%d", &k1.sayfasayisi);
            printf("Yayinlanma Tarihi: ");
            scanf(" %[^\n]", k1.temintarihi);
            fwrite(&k1, sizeof(kitap), 1, yptr);
        }
    }

    fclose(ptr);
    fclose(yptr);

    if (sonuc == 0)
    {
        printf("%d Barkod Numarali Kitap Bulunamadi \n", barkod);
    }
    else
    {
        remove("Kitap Ýþlemleri.dat");
        rename("Yedek Kitap Ýþlemleri.dat", "Kitap Ýþlemleri.dat");
        printf("%d Barkod Numarali Kitap Guncellendi. \n", barkod);
    }
}

void KitapSilme()
{

	
	printf("-----Kitap Silme Ekrani-----\n\n");

	kitap k1;
	int barkod,sonuc=0;

	printf("Barkod :   "); 	scanf("%d", &barkod);

	FILE * ptr = fopen("Kitap Ýþlemleri.dat","r+b");
	FILE * yptr = fopen("Yedek Kitap Ýþlemleri.dat","w+b");

	while(	fread( &k1, sizeof(kitap), 1, ptr) !=NULL ) // ilgili kitabýn olup olmadýðýný kontrol eder
	{
		if( barkod != k1.barkod)
		fwrite( &k1, sizeof(kitap), 1, yptr); // eþleþen kitaplarý yptr yazar
		else
		sonuc= 1;
	}

	fclose(ptr);
	fclose(yptr);
	if( sonuc == 0)
	{
		printf("%d Barkod Numarali Kitap Bulunamadi \n", barkod);
	}
	else
	{
		remove("Kitap Ýþlemleri.dat");
		rename("Yedek Kitap Ýþlemleri.dat","Kitap Ýþlemleri.dat");
		printf("%d Barkod Numarali Kitap Silindi. \n",barkod);
	}

}
void KitapArama() {
    
    printf("-----Kitap Arama Ekrani-----\n\n");

    char aramaKelimesi[30];
    printf("Aranacak kelimeyi veya harfi giriniz: ");
    scanf(" %[^\n]", aramaKelimesi);

    kitap k1;
    int bulunanKitap = 0;

    FILE *ptr = fopen("Kitap Ýþlemleri.dat", "rb");
    if (ptr == NULL) {
        printf("Dosya açýlamadý!\n");
        return;
    }

    printf("%-30s%-30s%-30s%-30s%-30s\n", "BARKOD", "KITAP-ADI", "YAZAR-ADI", "SAYFA-SAYISI", "TEMIN-TARIHI");

    while (fread(&k1, sizeof(kitap), 1, ptr) == 1) // kitaplarý kontrol et
	{
        if (strstr(k1.kitapAdi, aramaKelimesi) != NULL || strstr(k1.yazarAdi, aramaKelimesi) != NULL) //  girilen harfin kitaplarda bulunup bulunmaduýðýna bakar
		{
            printf("%-30d%-30s%-30s%-30d%-30s\n",
                   k1.barkod, k1.kitapAdi, k1.yazarAdi, k1.sayfasayisi, k1.temintarihi);
            bulunanKitap = 1; // kaydýn bulunduðunu belrtir
        }
    }

    fclose(ptr);

    if (!bulunanKitap) {
        printf("Aranan kelimeye veya harfe uygun kitap bulunamadi.\n");
    }
}



void KitapIslemleri()
{
	
	int secim;
	printf("------------------------------------------\n");
    printf("*                                        *\n");
	printf("*         Kitap Islemleri Ekrani         *\n");
	printf("*                                        *\n");
	printf("*  1-Kitap Ekle                          *\n");
    printf("*  2-Kitap Listeleme                     *\n");
    printf("*  3-Kitap Guncelleme                    *\n");
    printf("*  4-Kitap Silme                         *\n");
	printf("*  5-Kitap Arama                         *\n");
    printf("*  0-Ana Menuye Don                      *\n");
    printf("------------------------------------------\n");
    printf("\n\nSeciminiz : ");   scanf("%d",&secim);

    switch(secim)
    {
    	case 1:KitapEkle(); break;
    	case 2:KitapListeleme(); break;
    	case 3:KitapGuncelleme(); break;
    	case 4:KitapSilme(); break;
    	case 5:KitapArama(); break;
    	case 0:break;
		default: printf("Hatali Secim Yatiniz Ana Menuye Geri Yönlendirirliyorsunuz!!! \n"); break;
	}


}

void KullaniciEkle()
{
	
	printf("-----Kullanici Ekleme Ekrani-----\n\n");

	uye u1;

	 srand((unsigned int)time(NULL));
	u1.numara = rand() % 1001;

	printf("Kullanici Numarasi : %d\n", u1.numara);
	printf("Ad-Soyad           : ");    scanf(" %[^\n]", u1.adsoyad);
	printf("Dogum Tarihi       : "); scanf(" %[^\n]", u1.KullaniciDogumTarihi);

	FILE * ptr = fopen("Kullanici Ýþlemleri.dat","a+b");
	fwrite( &u1, sizeof(uye), 1, ptr);
	fclose(ptr);
}
void KullaniciListeleme()
{
	
	printf("-----Kullanici Listeleme Ekrani-----\n\n");

	uye u1;
	int kullanicisayisi=0;

	FILE * ptr = fopen("Kullanici Ýþlemleri.dat","r+b");

	printf("%-20s%-30s%-30s\n", "KULLANICI NUMARASI","KULLANICI AD-SOYAD","DOGUM TARIHI");

	while(	fread( &u1, sizeof(uye), 1, ptr) !=NULL ) // okuma iþlemi baþarýlýysa devam eder
	{
		printf("%-20d%-30s%-30s\n", u1.numara, u1.adsoyad, u1.KullaniciDogumTarihi);
		kullanicisayisi++;
	}


	fclose(ptr);
	printf("\n 	toplam Kullanici Sayisi : %d \n", kullanicisayisi);
}
void KullaniciGuncelleme()
{
    
    printf("-----Kullanici Guncelleme Ekrani-----\n\n");

    uye u1;
    int numara;
    int sonuc = 0;

    printf("Kullanici Numarasi :   ");
    scanf("%d", &numara);

    FILE *ptr = fopen("Kullanici Ýþlemleri.dat", "r+b");
    FILE *yptr = fopen("Yedek Kullanici Ýþlemleri.dat", "w+b");

    if (ptr == NULL || yptr == NULL) // ptr kontrol edilir 
    {
        printf("Dosya açýlamadý!\n");
        return;
    }

    while (fread(&u1, sizeof(uye), 1, ptr) == 1) // uye yapýsý okunur baþarýlýysa devam eder
    {
        if (numara != u1.numara)
        {
            fwrite(&u1, sizeof(uye), 1, yptr); // eðer eþleþmiyora yptr yazdýrýr
        }
        else
        {
            sonuc = 1; // eðer eþleþme varsa deðiþkenini 1 yapar ve  yeni bilgileri ister

            printf("\nYeni Bilgileri Giriniz:\n");
            printf("Ad-Soyad: ");
            scanf(" %[^\n]", u1.adsoyad);
            printf("Dogum Tarihi: ");
            scanf(" %[^\n]", u1.KullaniciDogumTarihi);
            fwrite(&u1, sizeof(uye), 1, yptr);
        }
    }

    fclose(ptr);
    fclose(yptr);

    if (sonuc == 0)
    {
        printf("%d Numaralý Kullanici Bulunamadi \n", numara);
    }
    else
    {
        remove("Kullanici Ýþlemleri.dat");
        rename("Yedek Kullanici Ýþlemleri.dat", "Kullanici Ýþlemleri.dat");
        printf("%d Numaralý Kullanici Güncellendi. \n", numara);
    }
}




void KullaniciArama() {
    
    printf("-----Kullanici Arama Ekrani-----\n\n");

    char aramaKelimesi[30];
    printf("Aranacak kelimeyi veya harfi giriniz: ");
    scanf(" %[^\n]", aramaKelimesi);

    uye u1;
    int bulunanKullanici = 0;

    FILE *ptr = fopen("Kullanici Ýþlemleri.dat", "rb");
    if (ptr == NULL) {
        printf("Dosya açýlamadý!\n");
        return;
    }

    printf("%-20s%-30s%-30s\n", "KULLANICI NUMARASI", "KULLANICI AD-SOYAD", "DOGUM TARIHI");

    while (fread(&u1, sizeof(uye), 1, ptr) == 1) // uyeleri kontrol eder
	{
        if (strstr(u1.adsoyad, aramaKelimesi) != NULL || strstr(u1.KullaniciDogumTarihi, aramaKelimesi) != NULL) //  girilen harfin uyelerde bulunup bulunmaduýðýna bakar
		{
            printf("%-20d%-30s%-30s\n", u1.numara, u1.adsoyad, u1.KullaniciDogumTarihi);
            bulunanKullanici = 1; // kaydýn bulunduðunu belrtir 
        }
    }

    fclose(ptr);

    if (!bulunanKullanici) {
        printf("Aranan kelimeye veya harfe uygun kullanici bulunamadi.\n");
    }
}

void KullaniciSilme()
{
    
    printf("-----Kullanici Silme Ekrani-----\n\n");

    uye u1;
    int numara;
    int sonuc = 0;

    printf("Kullanici Numarasi :   ");
    scanf("%d", &numara);

    FILE *ptr = fopen("Kullanici Ýþlemleri.dat", "r+b");
    FILE *yptr = fopen("Yedek Kullanici Ýþlemleri.dat", "w+b");

    if (ptr == NULL || yptr == NULL) // ilgili dosyanýn olup olmadýðýný kontrol eder
    
    {
        printf("Dosya açýlamadý!\n");
        return;
    }

    while (fread(&u1, sizeof(uye), 1, ptr) == 1) // uye yapýsýndaki girdiler okunur
    {
        if (numara != u1.numara) // numara girdisi karþýlaþtýrýlýr eðer yoksa kayýtlarý yedek dosyayý yazar 
        {
            fwrite(&u1, sizeof(uye), 1, yptr);
        }
        else
        {
            sonuc = 1; // eþleþen bir kayýt bulunduðunu belirtir 
        }
    }

    fclose(ptr);
    fclose(yptr);

    if (sonuc == 0)
    {
        printf("%d Numaralý Kullanici Bulunamadi \n", numara);
    }
    else
    {
        remove("Kullanici Ýþlemleri.dat");
        rename("Yedek Kullanici Ýþlemleri.dat", "Kullanici Ýþlemleri.dat");
        printf("%d Numaralý Kullanici Kaydi Silindi. \n", numara);
    }
}


void KullaniciIslemleri()
{
	
	int secim1;
	printf("------------------------------------------\n");
    printf("*                                        *\n");
	printf("*       Kullanici Islemleri Ekrani       *\n");
	printf("*                                        *\n");
	printf("*  1-Kullanici Ekle                      *\n");
    printf("*  2-Kullanici Listeleme                 *\n");
    printf("*  3-Kullanici Guncelleme                *\n");
    printf("*  4-Kullanici Silme                     *\n");
	printf("*  5-Kullanici Arama                     *\n");
    printf("*  0-Ana Menuye Don                      *\n");
    printf("*                                        *\n");
    printf("------------------------------------------\n");
    printf("\n\nSeciminiz : ");   scanf("%d",&secim1);

    switch(secim1)
    {
    	case 1:KullaniciEkle(); break;
    	case 2:KullaniciListeleme(); break;
    	case 3:KullaniciGuncelleme(); break;
    	case 4:KullaniciSilme(); break;
    	case 5:KullaniciArama(); break;
    	case 0:break;
		default: printf("Hatali Secim Yatiniz Ana Menuye Geri Yönlendirirliyorsunuz!!! \n"); break;
	}
}



void OduncKitapAlma()
{
    
    printf("-----Odunc Kitap Alma Ekrani-----\n\n");

    odunc od1;
    uye u1;
    kitap k1;
    int kullaniciNumarasi, kitapBarkodu;

    printf("Kullanici Numarasi: ");
    scanf("%d", &kullaniciNumarasi);

	//kullanýcý numarasýna ait bilgileri bulur
    FILE *kullaniciPtr = fopen("Kullanici Ýþlemleri.dat", "r");
    int kullaniciBulundu = 0;

    while (fread(&u1, sizeof(uye), 1, kullaniciPtr) == 1)
    {
        if (u1.numara == kullaniciNumarasi)
        {
            kullaniciBulundu = 1;
            break;
        }
    }

    fclose(kullaniciPtr);

    if (!kullaniciBulundu)
    {
        printf("Kullanici bulunamadi.\n");
        return;
    }

    printf("Kitap Barkodu: ");
    scanf("%d", &kitapBarkodu);

    //kitap numarasýna ait bilgileri bulur
    FILE *kitapPtr = fopen("Kitap Ýþlemleri.dat", "r");
    int kitapBulundu = 0;

    //kitabýn daha önce ödünç alýnýp alýnmadýðýný kontrol eder
    FILE *oduncPtr = fopen("Odunc Ýslemleri.dat", "rb");
    while (fread(&od1, sizeof(odunc), 1, oduncPtr) == 1)
    {
        if (od1.kitapbarkod == kitapBarkodu)
        {
            printf("Bu kitap zaten daha once odunc alinmis.\n");
            fclose(oduncPtr);
            fclose(kitapPtr);
            return;
        }
    }
    fclose(oduncPtr);

    // kitap bilgilerini bulur
    fseek(kitapPtr, 0, SEEK_SET);
    while (fread(&k1, sizeof(kitap), 1, kitapPtr) == 1)
    {
        if (k1.barkod == kitapBarkodu)
        {
            kitapBulundu = 1;
            break;
        }
    }

    fclose(kitapPtr);

    if (!kitapBulundu)
    {
        printf("Kitap bulunamadi.\n");
        return;
    }
	
	//ödünç alma iþlemlerini kaydet 
    od1.kitapbarkod = kitapBarkodu;
    strcpy(od1.AliciNumarasi, u1.kullanicinumarasi);
    time(&od1.AlisTarihi);

    od1.kullandigiGunSayisi = 0;

	//kullanýcýdan alýnan tarihi struct tm  çevirir
    struct tm alisTarihiStruct;
    printf("Odunc alma tarihini giriniz (GG.AA.YYYY): ");
    scanf("%d.%d.%d", &alisTarihiStruct.tm_mday, &alisTarihiStruct.tm_mon, &alisTarihiStruct.tm_year); // alýnan bilgileri struct tm yapýsýna kaydeder 
    alisTarihiStruct.tm_mon -= 1; // AY 0-11 arasýnda olduðu için kullanýcýdan alýnan deðeri düzeltmek için 1 eksiltir
    alisTarihiStruct.tm_year -= 1900; // yýl için kullanýcýndan alýnan deðeri düzeltmek için alýnan deðeri 1900 den çýkarýr

    od1.AlisTarihi = mktime(&alisTarihiStruct); // struct tm i time_tm dönüþtürüp odunc yapýsýna kaydediyor

    oduncPtr = fopen("Odunc Ýslemleri.dat", "a+b");
    fwrite(&od1, sizeof(odunc), 1, oduncPtr);
    fclose(oduncPtr);

    printf("Odunc kitap alma islemi basarili.\n");
}


void OduncKitapGeriGetirme()
{
    odunc od1;
    int bulunan = 0;
    int alinanKitapBarkod;

    printf("Kitap barkod numarasini giriniz: ");
    scanf("%d", &alinanKitapBarkod);
    
    struct tm alisTarihiStruct;
    printf("Odunc alma tarihini giriniz (GG.AA.YYYY): ");
    scanf("%d.%d.%d", &alisTarihiStruct.tm_mday, &alisTarihiStruct.tm_mon, &alisTarihiStruct.tm_year); // alýnan bilgileri struct tm yapýsýna kaydeder 
    alisTarihiStruct.tm_mon -= 1; // AY 0-11 arasýnda olduðu için kullanýcýdan alýnan deðeri düzeltmek için 1 eksiltir
    alisTarihiStruct.tm_year -= 1900; // yýl için kullanýcýndan alýnan deðeri düzeltmek için alýnan deðeri 1900 den çýkarýr

    od1.AlisTarihi = mktime(&alisTarihiStruct); // struct tm i time_tm dönüþtürüp odunc yapýsýna kaydeder

    FILE *ptr = fopen("Odunc Ýslemleri.dat", "r+b");
    FILE *yedekPtr = fopen("Yedek Odunc Ýslemleri.dat", "w+b");

    while (fread(&od1, sizeof(odunc), 1, ptr) == 1) // veriyi okur ve baþarýlý ise devam ettirir
    {
        if (od1.kitapbarkod == alinanKitapBarkod)
        {
            bulunan = 1; // deðerler eþleþiyorse kitap bulunuyordur
            

            printf("Kitap geri alindi ve bilgiler guncellendi.\n");
        }
        else
        {
            fwrite(&od1, sizeof(odunc), 1, yedekPtr); 
        }
    }

    fclose(ptr);
    fclose(yedekPtr);

    if (!bulunan)
    {
        printf("Kitap bulunamadi!\n"); // eþleþme bulunmadýysa kitap bulunamadý yazdýr 
    }
    else
    {
        remove("Odunc Ýslemleri.dat");
        rename("Yedek Odunc Ýslemleri.dat", "Odunc Ýslemleri.dat");
    }
}
void OduncKitapListeleme()
{
    odunc od1;
    int barkod;
    int bulunan = 0;

    printf("Listelemek istediginiz kitap barkod numarasini giriniz: ");
    scanf("%d", &barkod);

    FILE *ptr = fopen("Odunc Ýslemleri.dat", "rb");
    if (ptr == NULL)
    {
        printf("Dosya acilamadi!\n");
        return;
    }

    printf("\n%-20s %-15s %-15s %-15s %-10s\n", "ALICI NUMARASI", "KITAP BARKOD", "ALIS TARIHI", "BITIS TARIHI", "GUN SAYISI");

    while (fread(&od1, sizeof(odunc), 1, ptr) == 1)
    {
        if (od1.kitapbarkod == barkod)
        {
            bulunan = 1;

            struct tm *alisTarih = localtime(&od1.AlisTarihi);
            struct tm *bitisTarih = localtime(&od1.Bitistarihi);

            char alisTarihStr[20];
            char bitisTarihStr[20];

            strftime(alisTarihStr, sizeof(alisTarihStr), "%d.%m.%Y", alisTarih);

            if (od1.Bitistarihi != 0)
                strftime(bitisTarihStr, sizeof(bitisTarihStr), "%d.%m.%Y", bitisTarih);
            else
                strcpy(bitisTarihStr, "Teslim edilmedi");

            printf("%-20s %-15d %-15s %-15s %-10d\n",
                   od1.AliciNumarasi,
                   od1.kitapbarkod,
                   alisTarihStr,
                   bitisTarihStr,
                   od1.kullandigiGunSayisi);
        }
    }

    if (!bulunan)
    {
        printf("Bu barkoda ait odunc kaydi bulunamadi.\n");
    }

    fclose(ptr);
}


int menu ()
{
	int secim;
	system("COLOR 3"	);
	printf("----------------------------------------\n");
	printf("*                                      *\n");
	printf("*               ANA MENU               *\n");
    printf("*                                      *\n");
	printf("*        1.Kitap Islemleri             *\n");
    printf("*        2.Kullanici Islemleri         *\n");
    printf("*        0.Programi Kapat              *\n");
    printf("*                                      *\n");
	printf("----------------------------------------\n");

 printf("\nSeciminizi yapin : ");
    scanf("%d", &secim);
    return secim;
}

int main() {

	int secim = menu();

	while( secim != 0 )
	{
		switch(secim)
		{
			case 1: KitapIslemleri(); break;
			case 2: KullaniciIslemleri(); break;
			case 0: break;
			default : printf("\nHatali Secim Yaptiniz....!	\n\n"); break;
		}
		secim = menu();
	}


	printf("!! Programi Kapattiniz !!");




	return 0;
}


