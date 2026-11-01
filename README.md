# Graph

Program C++ interaktif untuk menyelesaikan empat latihan graf. Pilih soal untuk melihat dan memin-nya, atau gunakan **Pecahkan Soal** untuk memilih solver dan memasukkan data.

## Jalankan program

Jalankan dari folder proyek agar gambar referensi dapat ditemukan:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o main
./main
```

## Alur penggunaan

1. Pilih **Lihat Soal** dan pilih salah satu dari empat soal.
2. Program menampilkan `Soal N berhasil dipilih!` dan detail soal, lalu kembali ke menu utama dengan soal tersebut tetap dipin.
3. Pilih **Pecahkan Soal** untuk melihat daftar semua solver.
4. Pilih solver yang diperlukan, lalu masukkan data yang diminta.

Daftar solver selalu tersedia, dengan atau tanpa soal yang dipin.

## Solver interaktif

| Soal | Input | Hasil |
| --- | --- | --- |
| 1. Graf Teratur | Jumlah simpul `n` dan derajat `r` | Menghitung `n × r` dan memeriksa paritas jumlah derajat. |
| 2. Graf Berderajat Sama | Jumlah sisi `e` dan derajat `r` | Menghitung jumlah simpul dengan `n = 2e / r`. |
| 3. Euler dan Hamilton | Jenis graf dan adjacency matrix | Menampilkan matrix, derajat, status Euler, dan sirkuit Hamilton bila ada. |
| 4. DFS dan BFS | Jenis graf, adjacency matrix, dan simpul awal | Menampilkan urutan DFS dan BFS. |

## Input adjacency matrix

Untuk Soal 3 dan 4:

1. Pilih jenis graf: tak berarah atau berarah.
2. Masukkan jumlah simpul dari 1 sampai 10.
3. Isi semua nilai adjacency matrix. Nilai adalah jumlah sisi dari simpul baris ke simpul kolom.

Nilai matrix harus tidak negatif. Nilai diagonal menyatakan jumlah loop, dan nilai lebih dari 1 menyatakan sisi ganda. Untuk graf tak berarah, matrix harus simetris; program meminta matrix diisi ulang bila tidak simetris.

DFS dan BFS memeriksa tetangga menurut nomor simpul menaik. Untuk graf berarah, penelusuran hanya mengikuti arah sisi.

## Gambar referensi

Soal 3 dan 4 menampilkan `questions/question-3.jpeg` sebagai gambar referensi. Program memakai [Chafa](https://hpjansson.org/chafa/) untuk menampilkannya di terminal; jika Chafa tidak tersedia, solver tetap dapat digunakan.

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
