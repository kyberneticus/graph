# Graph

Program C++ sederhana untuk mempelajari materi graf, melihat soal latihan, menjalankan beberapa pemecahan soal, dan menggambar graf dengan Graphviz.

## Jalankan program

Jalankan perintah ini dari folder proyek agar program dapat menemukan folder `questions/`:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o main
./main
```

## Instal Chafa dan Graphviz

- **Chafa** menampilkan gambar soal dan graf di terminal.
- **Graphviz** membuat file `graphviz-output.dot` dan `graphviz-output.png` dari graf yang dimasukkan pada menu `3 -> 6`.

### Fedora

```bash
sudo dnf install chafa graphviz
```

### Ubuntu / Debian

```bash
sudo apt update
sudo apt install chafa graphviz
```

### Arch Linux

```bash
sudo pacman -S chafa graphviz
```

### macOS

Dengan [Homebrew](https://brew.sh/):

```bash
brew install chafa graphviz
```

### Windows

Gunakan Windows Terminal dan jalankan PowerShell sebagai Administrator:

```powershell
winget install --id hpjansson.Chafa --exact
winget install graphviz
```

Tutup dan buka kembali terminal, lalu periksa instalasi:

```powershell
chafa --version
dot -V
```

Jika perintah `dot` belum ditemukan, tambahkan folder `bin` Graphviz ke environment variable `PATH`, lalu buka terminal baru.

## Catatan

- Saat Chafa tidak tersedia, program tetap dapat membuat PNG melalui Graphviz, tetapi tidak dapat menampilkannya di terminal.
- Hasil Graphviz dibuat di folder proyek sebagai `graphviz-output.dot` dan `graphviz-output.png`.
- Gambar soal berada di folder `questions/`.
