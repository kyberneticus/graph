# Flowchart Program Graf

Dokumen ini menggambarkan alur `main.cpp` saat ini.

## Halaman 1 — Alur utama

```mermaid
flowchart TD
    Start([Mulai]) --> Init{{Persiapan: pinnedQuestion = nullptr}}
    Init --> MainLoop((Ulangi menu))
    MainLoop --> Header[/Output: header dan Main Menu/]
    Header --> MenuInput[/Input: pilih menu 1 sampai 3/]
    MenuInput --> Choice{Pilihan?}

    Choice -- "1" --> Questions[[showQuestion]]
    Questions --> MainLoop
    Choice -- "2" --> Solver[[solveQuestion]]
    Solver --> MainLoop
    Choice -- "3" --> Exit[/Output: pesan terima kasih/]
    Exit --> End([Selesai])
    Choice -- "Selain 1-3" --> Error[/Output: pilihan tidak tersedia/]
    Error --> MainLoop

    classDef terminator fill:#D5F5E3,stroke:#1E8449,color:#000,stroke-width:2px;
    classDef preparation fill:#E8DAEF,stroke:#7D3C98,color:#000,stroke-width:2px;
    classDef io fill:#FDEBD0,stroke:#CA6F1E,color:#000,stroke-width:2px;
    classDef decision fill:#F9E79F,stroke:#B7950B,color:#000,stroke-width:2px;
    classDef subprocess fill:#D4E6F1,stroke:#2471A3,color:#000,stroke-width:2px;
    classDef connector fill:#FFFFFF,stroke:#555555,color:#000,stroke-width:2px;

    class Start,End terminator;
    class Init preparation;
    class Header,MenuInput,Exit,Error io;
    class Choice decision;
    class Questions,Solver subprocess;
    class MainLoop connector;
```

## Halaman 2 — Pemilihan soal

```mermaid
flowchart TD
    Entry((Dipanggil oleh main)) --> List[/Output: tampilkan empat soal/]
    List --> Input[/Input: masukkan nomor soal atau 0/]
    Input --> Back{Nomor = 0?}
    Back -- Ya --> Return((Kembali ke main))
    Back -- Tidak --> Find[Proses: cari soal pada array]
    Find --> Exists{Soal ditemukan?}
    Exists -- Tidak --> Missing[/Output: nomor soal tidak tersedia/]
    Missing --> List
    Exists -- Ya --> Pin[Proses: simpan soal sebagai pinnedQuestion]
    Pin --> Success[/Output: Soal N berhasil dipilih/]
    Success --> Details[/Output: tampilkan detail soal dan gambar referensi/]
    Details --> Return

    classDef connector fill:#FFFFFF,stroke:#555555,color:#000,stroke-width:2px;
    classDef process fill:#D6EAF8,stroke:#2874A6,color:#000,stroke-width:2px;
    classDef io fill:#FDEBD0,stroke:#CA6F1E,color:#000,stroke-width:2px;
    classDef decision fill:#F9E79F,stroke:#B7950B,color:#000,stroke-width:2px;

    class Entry,Return connector;
    class Find,Pin process;
    class List,Input,Missing,Success,Details io;
    class Back,Exists decision;
```

## Halaman 3 — Daftar solver

```mermaid
flowchart TD
    Entry((Dipanggil oleh main)) --> SolverMenu[/Output: tampilkan semua solver/]
    SolverMenu --> SolverInput[/Input: pilih solver atau 0/]
    SolverInput --> Back{Pilihan = 0?}
    Back -- Ya --> Return((Kembali ke main))
    Back -- Tidak --> Which{Nomor solver?}

    Which -- "1" --> RegularInput[/Input: n dan r/]
    RegularInput --> RegularCalc[Proses: hitung n x r dan cek paritas]
    RegularCalc --> RegularOutput[/Output: hasil graf teratur/]

    Which -- "2" --> SameDegreeInput[/Input: e dan r/]
    SameDegreeInput --> SameDegreeCalc[Proses: hitung 2e / r]
    SameDegreeCalc --> SameDegreeOutput[/Output: jumlah simpul atau gagal/]

    Which -- "3" --> EulerInput[[Input adjacency matrix]]
    EulerInput --> EulerCalc[Proses: hitung derajat dan cek Euler]
    EulerCalc --> HamiltonCalc[Proses: cari sirkuit Hamilton]
    HamiltonCalc --> EulerOutput[/Output: hasil Euler dan Hamilton/]

    Which -- "4" --> TraversalInput[[Input adjacency matrix]]
    TraversalInput --> StartInput[/Input: simpul awal/]
    StartInput --> DFS[Proses: DFS]
    DFS --> BFS[Proses: BFS]
    BFS --> TraversalOutput[/Output: urutan DFS dan BFS/]

    RegularOutput --> Pause[/Input: tekan Enter/]
    SameDegreeOutput --> Pause
    EulerOutput --> Pause
    TraversalOutput --> Pause
    Pause --> Return

    classDef connector fill:#FFFFFF,stroke:#555555,color:#000,stroke-width:2px;
    classDef process fill:#D6EAF8,stroke:#2874A6,color:#000,stroke-width:2px;
    classDef io fill:#FDEBD0,stroke:#CA6F1E,color:#000,stroke-width:2px;
    classDef decision fill:#F9E79F,stroke:#B7950B,color:#000,stroke-width:2px;
    classDef subprocess fill:#D4E6F1,stroke:#2471A3,color:#000,stroke-width:2px;

    class Entry,Return connector;
    class RegularCalc,SameDegreeCalc,EulerCalc,HamiltonCalc,DFS,BFS process;
    class SolverMenu,SolverInput,RegularInput,RegularOutput,SameDegreeInput,SameDegreeOutput,StartInput,EulerOutput,TraversalOutput,Pause io;
    class Back,Which decision;
    class EulerInput,TraversalInput subprocess;
```

## Halaman 4 — Input adjacency matrix

```mermaid
flowchart TD
    Entry((Dipanggil oleh Soal 3 atau 4)) --> Type[/Input: pilih graf tak berarah atau berarah/]
    Type --> Vertices[/Input: jumlah simpul 1 sampai 10/]
    Vertices --> Matrix[/Input: isi semua nilai adjacency matrix/]
    Matrix --> Directed{Graf berarah?}
    Directed -- Ya --> Return((Kembalikan Graph))
    Directed -- Tidak --> Symmetric{Matrix simetris?}
    Symmetric -- Ya --> Return
    Symmetric -- Tidak --> Error[/Output: matrix harus simetris/]
    Error --> Matrix

    classDef connector fill:#FFFFFF,stroke:#555555,color:#000,stroke-width:2px;
    classDef io fill:#FDEBD0,stroke:#CA6F1E,color:#000,stroke-width:2px;
    classDef decision fill:#F9E79F,stroke:#B7950B,color:#000,stroke-width:2px;

    class Entry,Return connector;
    class Type,Vertices,Matrix,Error io;
    class Directed,Symmetric decision;
```

## Catatan

- Matrix menyimpan jumlah sisi; loop adalah nilai diagonal dan sisi ganda diperbolehkan.
- Soal 3 memeriksa sirkuit Euler. Untuk graf berarah, program memeriksa derajat masuk/keluar serta keterhubungan kuat pada simpul yang memiliki sisi.
- Soal 4 mengikuti arah sisi pada graf berarah dan memeriksa tetangga dari nomor terkecil.
- `verifyAlgorithms()` menjalankan `assert` untuk memeriksa DFS, BFS, keterhubungan Euler, dan Hamilton pada graf contoh enam simpul.
