# 📚 C Kütüphane Otomasyonu

Bu proje, C dili kullanılarak geliştirilmiş basit bir Kütüphane Otomasyonu örneğidir.  
Kullanıcılar kitap ekleyebilir, listeleyebilir, güncelleyebilir veya silebilir; üyeler ekleyebilir ve ödünç alma işlemleri gerçekleştirebilir.

## Özellikler
- Kitap İşlemleri: Ekle, Listele
- Üye İşlemleri: Ekle, Listele
- Ödünç Alma İşlemleri: Kitap al, geri ver, listele

## Dosyalar
- `main.c` : Projenin ana C dosyası
- `Kitaplar.dat` : Kitap verilerini kaydeden dosya (program çalıştıkça oluşturulur)
- `Uyeler.dat` : Üye verilerini kaydeden dosya (program çalıştıkça oluşturulur)
- `Odunc.dat` : Ödünç alma işlemleri verilerini kaydeden dosya (program çalıştıkça oluşturulur)

## Çalıştırma
1. Projeyi bilgisayarına indir.
2. Terminal veya CMD’den proje klasörüne git.
3. Aşağıdaki komutlarla derle ve çalıştır:

```bash
gcc main.c -o Kutuphane
./Kutuphane    # Windows'ta: Kutuphane.exe

