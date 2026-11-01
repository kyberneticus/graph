# Flowchart Program Graf

Dokumen ini menggambarkan alur `main.cpp` saat ini.

## Halaman 1 — Alur utama `main()`

```mermaid
flowchart TD
    Start([Mulai]) --> Init{{Persiapan: pinnedQuestion = nullptr}}
    Init --> MainLoop((Ulangi menu))
    MainLoop --> Header[/Output: tampilkan header dan Main Menu/]
    Header --> InputChoice[/Input: pilih menu 1 sampai 3/]
    InputChoice --> Choice{Nilai pilihan?}

    Choice -- "1: Lihat Soal" --> Questions[[Subproses: showQuestion]]
    Questions --> MainLoop

    Choice -- "2: Pecahkan Soal Terpilih" --> Solver[[Subproses: solveQuestion]]
    Solver --> MainLoop

    Choice -- "3: Keluar" --> ExitMessage[/Output: tampilkan pesan terima kasih/]
    ExitMessage --> End([Selesai])

    Choice -- "Selain 1 sampai 3" --> ChoiceError[/Output: "Pilihan tidak tersedia"/]
    ChoiceError --> MainLoop

    classDef terminator fill:#D5F5E3,stroke:#1E8449,color:#000,stroke-width:2px;
    classDef preparation fill:#E8DAEF,stroke:#7D3C98,color:#000,stroke-width:2px;
    classDef io fill:#FDEBD0,stroke:#CA6F1E,color:#000,stroke-width:2px;
    classDef decision fill:#F9E79F,stroke:#B7950B,color:#000,stroke-width:2px;
    classDef subprocess fill:#D4E6F1,stroke:#2471A3,color:#000,stroke-width:2px;
    classDef connector fill:#FFFFFF,stroke:#555555,color:#000,stroke-width:2px;

    class Start,End terminator;
    class Init preparation;
    class Header,InputChoice,ExitMessage,ChoiceError io;
    class Choice decision;
    class Questions,Solver subprocess;
    class MainLoop connector;
```

## Halaman 2 — Subproses `showQuestion()`

```mermaid
flowchart TD
    Entry((Dipanggil oleh main)) --> List[/Output: tampilkan empat soal dan pilihan 0/]
    List --> Input[/Input: masukkan nomor soal/]
    Input --> Back{Nomor = 0?}

    Back -- Ya --> Return((Kembali ke main))
    Back -- Tidak --> Find[Proses: cari soal pada array]
    Find --> Exists{Soal ditemukan?}

    Exists -- Tidak --> Missing[/Output: "Nomor soal tidak tersedia"/]
    Missing --> List

    Exists -- Ya --> Pin[Proses: simpan alamat soal sebagai pinnedQuestion]
    Pin --> Show[/Output: tampilkan soal dan gambar bila tersedia/]
    Show --> Return

    classDef connector fill:#FFFFFF,stroke:#555555,color:#000,stroke-width:2px;
    classDef process fill:#D6EAF8,stroke:#2874A6,color:#000,stroke-width:2px;
    classDef io fill:#FDEBD0,stroke:#CA6F1E,color:#000,stroke-width:2px;
    classDef decision fill:#F9E79F,stroke:#B7950B,color:#000,stroke-width:2px;

    class Entry,Return connector;
    class Find,Pin process;
    class List,Input,Missing,Show io;
    class Back,Exists decision;
```

## Halaman 3 — Subproses `solveQuestion()`

```mermaid
flowchart TD
    Entry((Dipanggil oleh main)) --> Selected{pinnedQuestion tersedia?}
    Selected -- Tidak --> NeedQuestion[/Output: pilih soal terlebih dahulu/]
    NeedQuestion --> Return((Kembali ke main))

    Selected -- Ya --> Show[/Output: tampilkan soal yang dipin/]
    Show --> Which{Nomor soal?}

    Which -- "1" --> Regular[Proses: hitung 7 x 3 dan cek paritas]
    Regular --> RegularResult[/Output: graf tidak mungkin/]

    Which -- "2" --> DegreeTwo[Proses: hitung 2 x 13 lalu bagi derajat 2]
    DegreeTwo --> DegreeTwoResult[/Output: jumlah simpul = 13/]

    Which -- "3" --> Euler[Proses: hitung derajat dari adjacency matrix dan cek Euler]
    Euler --> Hamilton[Proses: cari sirkuit Hamilton dengan backtracking]
    Hamilton --> EulerHamiltonResult[/Output: hasil Euler dan sirkuit Hamilton/]

    Which -- "4" --> DFS[Proses: telusuri adjacency matrix secara DFS dari simpul 1]
    DFS --> BFS[Proses: telusuri adjacency matrix secara BFS dari simpul 1]
    BFS --> TraversalResult[/Output: urutan DFS dan BFS/]

    RegularResult --> Pause[/Input: tekan Enter/]
    DegreeTwoResult --> Pause
    EulerHamiltonResult --> Pause
    TraversalResult --> Pause
    Pause --> Return

    classDef connector fill:#FFFFFF,stroke:#555555,color:#000,stroke-width:2px;
    classDef process fill:#D6EAF8,stroke:#2874A6,color:#000,stroke-width:2px;
    classDef io fill:#FDEBD0,stroke:#CA6F1E,color:#000,stroke-width:2px;
    classDef decision fill:#F9E79F,stroke:#B7950B,color:#000,stroke-width:2px;

    class Entry,Return connector;
    class Regular,DegreeTwo,Euler,Hamilton,DFS,BFS process;
    class NeedQuestion,Show,RegularResult,DegreeTwoResult,EulerHamiltonResult,TraversalResult,Pause io;
    class Selected,Which decision;
```

## Catatan implementasi

- `questionGraph` adalah adjacency matrix enam simpul yang dipakai bersama oleh Soal 3 dan 4.
- DFS dan BFS memeriksa tetangga dalam urutan nomor simpul menaik.
- `verifyQuestionGraph()` memakai `assert` untuk memeriksa derajat, urutan DFS/BFS, dan keberadaan sirkuit Hamilton saat program dimulai.
