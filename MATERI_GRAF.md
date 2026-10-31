# Materi Graf

Dokumen ini merangkum materi yang dipakai oleh program. Semua penjelasan berasal dari folder `material/`.

> **Catatan sumber:** file PowerPoint tidak memiliki nomor halaman; lokasi ditulis sebagai **slide**. Untuk PDF, lokasi ditulis sebagai nomor halaman cetak pada dokumen.

## 1. Graf

Graf `G = (V, E)` adalah struktur yang terdiri dari himpunan simpul (*vertex*) `V` dan himpunan sisi (*edge*) `E`. Sisi menghubungkan pasangan simpul.

**Sumber:** `material/10 Graph(1).pptx`, slide 7.

## 2. Jenis graf

- **Graf sederhana** tidak memiliki loop dan sisi ganda.
- **Graf tak-sederhana** memiliki loop dan/atau sisi ganda.
- **Graf tak-berarah** tidak memberi orientasi pada sisi.
- **Graf berarah** memberi arah pada setiap sisi.

**Sumber:** `material/10 Graph(1).pptx`, slide 12–19.

## 3. Ketetanggaan, insidensi, dan simpul khusus

Dua simpul bertetangga jika keduanya dihubungkan langsung oleh sisi. Sebuah sisi bersisian dengan simpul pada kedua ujungnya. Simpul terpencil tidak memiliki sisi bersisian, sedangkan simpul pendant berderajat satu.

**Sumber:** `material/10 Graph(1).pptx`, slide 24–29.

## 4. Derajat simpul dan lemma jabat tangan

Derajat simpul adalah jumlah sisi yang bersisian dengannya. Pada graf berarah terdapat derajat masuk (*in-degree*) dan derajat keluar (*out-degree*). Pada graf tak-berarah berlaku:

`jumlah semua derajat simpul = 2 × jumlah sisi`

**Sumber:** `material/10 Graph(1).pptx`, slide 28–35.

## 5. Lintasan, sirkuit, dan keterhubungan

Lintasan adalah urutan simpul dan sisi yang menghubungkan simpul awal ke simpul tujuan. Sirkuit adalah lintasan yang dimulai dan diakhiri pada simpul yang sama. Graf disebut terhubung jika setiap pasangan simpul mempunyai lintasan.

Pada graf berarah, dua simpul disebut terhubung kuat jika terdapat lintasan berarah dari simpul pertama ke simpul kedua dan sebaliknya.

**Sumber:** `material/10 Graph(1).pptx`, slide 36–43.

## 6. Subgraf, komponen, dan cut-set

Subgraf adalah graf yang simpul dan sisinya merupakan bagian dari graf asal. Komponen terhubung adalah subgraf terhubung yang maksimal. *Cut-set* adalah himpunan sisi yang jika dihapus menyebabkan graf terhubung menjadi tidak terhubung.

**Sumber:** `material/10 Graph(1).pptx`, slide 44–50.

## 7. Graf khusus

- **Graf lengkap**: setiap pasangan simpul dihubungkan oleh sisi; graf lengkap dengan `n` simpul ditulis `K_n` dan mempunyai `n(n-1)/2` sisi.
- **Graf lingkaran**: setiap simpul berderajat dua; ditulis `C_n`.
- **Graf teratur**: semua simpul memiliki derajat sama.
- **Graf bipartit**: simpul dapat dipisah menjadi dua himpunan, dan setiap sisi menghubungkan simpul dari himpunan berbeda.

**Sumber:** `material/10 Graph(1).pptx`, slide 51–57.

## 8. Representasi graf

Graf dapat direpresentasikan dalam tiga bentuk:

1. **Matriks ketetanggaan** (*adjacency matrix*), untuk mencatat hubungan antar simpul.
2. **Matriks insidensi** (*incidence matrix*), untuk mencatat hubungan simpul dengan sisi.
3. **Senarai ketetanggaan** (*adjacency list*), untuk mencatat tetangga setiap simpul.

**Sumber:** `material/11 Representasi Graph(1).pptx`, slide 2–15.

## 9. BFS dan DFS

- **Breadth-First Search (BFS)** menelusuri graf per tingkat, dari simpul terdekat terlebih dahulu.
- **Depth-First Search (DFS)** menelusuri graf sedalam mungkin sebelum kembali ke simpul sebelumnya.

**Sumber:** `material/11 Representasi Graph(1).pptx`, slide 16.

## 10. Topological sort

*Topological sort* adalah pengurutan linear simpul pada graf berarah tanpa siklus (*Directed Acyclic Graph* atau DAG). Jika ada sisi dari `u` ke `v`, maka `u` harus muncul sebelum `v` dalam urutan.

**Sumber:** `material/11 Representasi Graph(1).pptx`, slide 17–20.

## 11. Graf isomorfik

Dua graf disebut isomorfik jika terdapat korespondensi satu-satu antara simpul dan sisi kedua graf, serta hubungan kebersisiannya tetap sama. Graf dapat terlihat berbeda, tetapi tetap isomorfik jika strukturnya sama.

**Sumber:** `material/11 Representasi Graph(1).pptx`, slide 21–28.

## 12. Graf planar

Graf planar dapat digambar pada bidang datar tanpa sisi saling berpotongan. Sisi pada graf planar membagi bidang menjadi sejumlah wilayah atau *face*. Untuk graf planar terhubung berlaku rumus Euler:

`jumlah simpul - jumlah sisi + jumlah wilayah = 2`

**Sumber:** `material/11 Representasi Graph(1).pptx`, slide 29–35.

## 13. Lintasan dan sirkuit Euler

Lintasan Euler melewati setiap sisi tepat satu kali. Sirkuit Euler juga melewati setiap sisi tepat satu kali, tetapi kembali ke simpul awal.

Untuk graf tak-berarah yang terhubung:

- terdapat sirkuit Euler jika setiap simpul berderajat genap;
- terdapat lintasan Euler jika jumlah simpul berderajat ganjil adalah nol atau dua.

**Sumber:** `material/11 Representasi Graph(1).pptx`, slide 36–43.

## 14. Lintasan dan sirkuit Hamilton

Lintasan Hamilton mengunjungi setiap simpul tepat satu kali. Sirkuit Hamilton mengunjungi setiap simpul tepat satu kali lalu kembali ke simpul awal.

Materi memberi syarat cukup: graf sederhana dengan `n ≥ 3` simpul adalah graf Hamilton jika setiap simpul memiliki derajat minimal `n/2`.

**Sumber:** `material/11 Representasi Graph(1).pptx`, slide 45–51.

## 15. Lintasan terpendek dan Dijkstra

Lintasan terpendek pada graf berbobot adalah lintasan dengan total bobot minimum. Algoritma Dijkstra digunakan untuk mencari lintasan terpendek dari satu simpul asal ke simpul tujuan atau simpul lain, selama tidak ada bobot sisi negatif.

**Sumber:** `material/12 Aplikasi Graph(1).pptx`, slide 2–12.

## 16. Travelling Salesperson Problem (TSP)

TSP mencari sirkuit dengan total bobot minimum: seorang pedagang berangkat dari kota asal, mengunjungi setiap kota tepat satu kali, lalu kembali ke kota awal. Masalah ini mencari sirkuit Hamilton berbobot minimum.

Untuk graf lengkap tak-berarah dengan `n` simpul, jumlah sirkuit Hamilton adalah `(n - 1)! / 2`.

**Sumber:** `material/12 Aplikasi Graph(1).pptx`, slide 13–16.

## 17. Chinese Postman Problem

Persoalan Tukang Pos Cina mencari rute berbiaya minimum yang melewati setiap sisi atau jalan dan kembali ke titik awal. Materi menghubungkannya dengan pencarian sirkuit Euler.

**Sumber:** `material/12 Aplikasi Graph(1).pptx`, slide 17–18.

## 18. Pewarnaan graf dan Welch-Powell

Pewarnaan graf memberi warna pada simpul sehingga dua simpul yang bertetangga memiliki warna berbeda. Bilangan kromatik `χ(G)` adalah jumlah warna minimum yang diperlukan.

Algoritma Welch-Powell mengurutkan simpul berdasarkan derajat menurun, lalu memberi warna yang sama pada simpul-simpul yang tidak bertetangga sampai seluruh simpul berwarna.

**Sumber:** `material/12 Aplikasi Graph(1).pptx`, slide 19–27.

## Referensi latihan

Soal latihan terkait graf terdapat di `material/Matematika Diskrit - Bab 8 Graf.pdf`, halaman cetak **437–442** (halaman PDF **85–90**). Soal meliputi jabat tangan, graf turnamen, graf teratur, isomorfik, planar, Euler, Hamilton, pewarnaan graf, TSP, dan persoalan tukang pos.
