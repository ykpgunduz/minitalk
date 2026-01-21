*This project has been created as part of the 42 curriculum by yagunduz.*

# Minitalk


## Açıklama

`minitalk` UNIX sinyalleri (`SIGUSR1`, `SIGUSR2`) kullanarak basit bir client-server haberleşmesi uygular. `client` gönderilen metni bit-bit `server`'a iletir; `server` gelen bitleri birleştirerek karakterleri oluşturur ve mesajı yazdırır.

Projede temel gereksinimler ve bonus örnekleri mevcuttur.

## Özellikler

- `server` ve `client` programları.
- Karakterleri bit bazında sinyallerle gönderme ve alma.
- Basit hata kontrolü ve isteğe bağlı onay (ack) mekanizması.
- `bonus/` klasöründe gelişmiş veya alternatif uygulamalar.

## Derleme

```bash
make
```

Bu komut `server` ve `client` ikililerini oluşturur.

## Talimatlar

- Projeyi `make` ile derleyin.
- `server` programını başlatmak için bir terminalde `./server` çalıştırın (PID ekrana yazdırılır).
- Başka bir terminalde `./client <server_pid> "mesajınız"` komutunu kullanarak mesaj gönderin.

Örnek:

```bash
make
./server
# diğer terminalde
./client 12345 "Merhaba from client"
```

## Kullanım

1. `server`'ı başlatın; PID konsola yazdırılır:

```bash
./server
```

2. Başka bir terminalde `client` ile mesaj gönderin (ilk argüman server PID, ikinci argüman mesaj):

```bash
./client 12345 "Merhaba Ben Yakup!"
```

`server` gelen mesajı aldıktan sonra konsola yazdırır.

## Dosya Yapısı

- `server.c`       : Sinyal yakalama ve mesaj birleştirme.
- `client.c`       : PID'ye sinyaller göndererek mesaj iletme.
- `utils.c`        : Ortak yardımcı fonksiyonlar.
- `minitalk.h`     : Proje başlıkları ve prototipler.
- `Makefile`       : Derleme kuralları.
- `bonus/`         : Bonus versiyonları (`client_bonus.c`, `server_bonus.c`, vs.).

## Kaynaklar

- Linux sinyalleri belgeleri: https://man7.org/linux/man-pages/man7/signal.7.html
- Sinyaller (IPC) hakkında genel bakış: https://en.wikipedia.org/wiki/Signal_(IPC)
- Minitalk proje konusu (42 intra): https://cdn.intra.42.fr/pdf/pdf/193350/en.subject.pdf — Proje gereksinimleri, kurallar ve değerlendirme kriterleri (resmi konu dokümanı).
- Bit işlemleri ve bit maskeleme rehberi: https://medium.com/@muhsin.kulbak/bitsel-i%CC%87%C5%9Flemler-ve-bit-maskeleme-0a7be61a86ef — Bit manipülasyonu, maskeler ve örnekler; sinyallerle bit bazlı iletişim mantığını anlamak için faydalı.

### AI Kullanımı

AI araçları aşağıdaki konularda yardımcı araç olarak kullanılmıştır:
- Bu `README.md` metninin taslağının hazırlanması ve iyileştirilmesi.
- Geliştirme sırasında hata ayıklama önerileri ve zamanlama/yarış durumlarıyla ilgili rehberlik.

Tüm temel proje kodu, algoritmalar ve mantık kendi tarafımca yazılmıştır.
