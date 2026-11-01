# Graph

Program C++ untuk mempelajari empat soal graf. Pilih soal terlebih dahulu, lalu gunakan **Pecahkan Soal Terpilih** untuk menjalankan solver yang sesuai.

## Jalankan program

Jalankan dari folder proyek agar gambar soal dapat ditemukan:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o main
./main
```

## Alur penggunaan

1. Pilih **Lihat Soal**, lalu pilih salah satu dari empat soal. Soal tersebut dipin dan program kembali ke menu utama.
2. Pilih **Pecahkan Soal Terpilih**.
3. Program menjalankan solver untuk soal yang dipin.

Jika belum memilih soal, menu solver meminta pengguna untuk memilih soal terlebih dahulu.

## Solver

| Soal | Solver |
| --- | --- |
| 1 | Menghitung jumlah derajat `7 × 3` untuk menentukan kemungkinan graf 3-teratur dengan 7 simpul. |
| 2 | Menggunakan lemma jabat tangan untuk menghitung jumlah simpul dari 13 sisi dan derajat 2. |
| 3 | Menghitung derajat dari matriks ketetanggaan, lalu memeriksa sifat Euler dan mencari sirkuit Hamilton. |
| 4 | Menjalankan DFS dan BFS pada matriks ketetanggaan yang sama dengan Soal 3, mulai dari simpul 1 dan memilih tetangga bernomor terkecil terlebih dahulu. |

Graf pada Soal 3 dan Soal 4 direpresentasikan sebagai adjacency matrix enam simpul di `main.cpp`.

## Menampilkan gambar soal

Soal 3 dan 4 memakai `questions/question-3.jpeg`. Program memakai [Chafa](https://hpjansson.org/chafa/) untuk menampilkannya di terminal. Jika Chafa tidak tersedia, soal dan solver tetap dapat digunakan.

### Fedora

```bash
sudo dnf install chafa
```

### Ubuntu / Debian

```bash
sudo apt update
sudo apt install chafa
```

### Arch Linux

```bash
sudo pacman -S chafa
```

### macOS

```bash
brew install chafa
```
