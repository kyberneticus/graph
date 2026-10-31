# Flowchart Program Graf

Flowchart ini memakai **konvensi standar flowchart** dan menambahkan alur pertanyaan yang lengkap untuk setiap topik. Salin blok Mermaid berikut ke [Mermaid AI](https://mermaid.ai/).

> **Catatan:** bagian alur pertanyaan adalah rancangan lengkap yang perlu diimplementasikan saat `showQuestion()` dikembangkan. Kode saat ini hanya menampilkan Soal 1. Tidak ada cabang yang sengaja dibiarkan tanpa tujuan.

```mermaid
flowchart TD
    Start([Mulai]) --> PrepMain{{Persiapan: systemRunning = true, choice = 0}}
    PrepMain --> Header[/Output: tampilkan header program/]
    Header --> MainMenu[/Output: tampilkan Main Menu/]
    MainMenu --> MainInput[/Input: masukkan pilihan 1 sampai 4/]

    MainInput --> NumberValid{Input berupa angka?}
    NumberValid -- Tidak --> NumberError[/Output: "Input harus berupa angka"/]
    NumberError --> ResetInput[Proses: cin.clear dan cin.ignore]
    ResetInput --> Header

    NumberValid -- Ya --> IgnoreNewline[Proses: cin.ignore newline]
    IgnoreNewline --> MainChoice{Nilai pilihan?}

    MainChoice -- "1. Definisi" --> Definition[[Subprogram: showDefinition]]
    Definition --> DefinitionOutput[/Output: tampilkan seluruh definisi materi/]
    DefinitionOutput --> MainPause[/Input: tekan Enter/]

    MainChoice -- "2. Soal" --> QuestionModule[[Subprogram: showQuestion]]
    QuestionModule --> TopicInit{{Persiapan: topicIndex = 1}}

    TopicInit --> TopicLoop{topicIndex ≤ 18?}
    TopicLoop -- Ya --> ListTopic[/Output: tampilkan topik dan soal terkait topicIndex/]
    ListTopic --> IncreaseTopic[Proses: topicIndex = topicIndex + 1]
    IncreaseTopic --> TopicLoop
    TopicLoop -- Tidak --> TopicMenu[/Output: tampilkan daftar topik 1 sampai 18 dan pilihan 0 untuk kembali/]

    TopicMenu --> TopicInput[/Input: pilih topik atau 0/]
    TopicInput --> BackFromTopic{Pilihan topik = 0?}
    BackFromTopic -- Ya --> Header
    BackFromTopic -- Tidak --> TopicValid{Topik tersedia 1 sampai 18?}
    TopicValid -- Tidak --> TopicError[/Output: "Topik tidak tersedia"/]
    TopicError --> TopicMenu
    TopicValid -- Ya --> LoadQuestions[Proses: ambil daftar soal untuk topik terpilih]

    LoadQuestions --> QuestionMenu[/Output: tampilkan soal topik dan pilihan 0 untuk kembali/]
    QuestionMenu --> QuestionInput[/Input: pilih nomor soal atau 0/]
    QuestionInput --> BackFromQuestion{Pilihan soal = 0?}
    BackFromQuestion -- Ya --> TopicMenu
    BackFromQuestion -- Tidak --> QuestionValid{Nomor soal tersedia?}
    QuestionValid -- Tidak --> QuestionError[/Output: "Soal tidak tersedia"/]
    QuestionError --> QuestionMenu

    QuestionValid -- Ya --> LoadQuestion[Proses: ambil teks dan file gambar soal]
    LoadQuestion --> TextQuestion[/Output: tampilkan teks soal/]
    TextQuestion --> ImageExists{File gambar soal tersedia?}

    ImageExists -- Tidak --> AskAnotherQuestion{Lihat soal lain dalam topik ini?}
    ImageExists -- Ya --> RunChafa[Proses: jalankan Chafa untuk gambar soal]
    RunChafa --> ChafaSuccess{Status Chafa = 0?}
    ChafaSuccess -- Ya --> ImageShown[/Output: gambar soal tampil di terminal/]
    ChafaSuccess -- Tidak --> ChafaError[/Output: tampilkan pesan instalasi atau error Chafa/]
    ImageShown --> AskAnotherQuestion
    ChafaError --> AskAnotherQuestion

    AskAnotherQuestion -- Ya --> LoadQuestions
    AskAnotherQuestion -- Tidak --> AskAnotherTopic{Pilih topik lain?}
    AskAnotherTopic -- Ya --> TopicMenu
    AskAnotherTopic -- Tidak --> Header

    MainChoice -- "3. Pecahkan Soal" --> SolverModule[[Subprogram: solveQuestion]]
    SolverModule --> SolverMenu[/Output: tampilkan topik pemecahan soal/]
    SolverMenu --> SolverInput[/Input: pilih topik solver atau 0/]
    SolverInput --> BackFromSolver{Pilihan = 0?}
    BackFromSolver -- Ya --> Header
    BackFromSolver -- Tidak --> SolverChoice{Topik solver?}
    SolverChoice -- "1" --> Handshake[Proses: hitung jabat tangan]
    SolverChoice -- "2" --> Regular[Proses: hitung atau validasi graf sederhana/teratur]
    SolverChoice -- "3" --> Euler[Proses: cek dan buat rute Euler]
    SolverChoice -- "4" --> Planar[Proses: uji batas planar dan rumus Euler]
    SolverChoice -- "5" --> Coloring[Proses: pewarnaan Welch-Powell]
    SolverChoice -- "6" --> Graphviz[Proses: ekspor DOT dan render PNG dengan Graphviz]
    SolverChoice -- "Selain 1-6" --> SolverError[/Output: "Pilihan tidak tersedia"/]
    Handshake --> SolverPause[/Input: tekan Enter/]
    Regular --> SolverPause
    Euler --> SolverPause
    Planar --> SolverPause
    Coloring --> SolverPause
    Graphviz --> SolverPause
    SolverError --> SolverPause
    SolverPause --> SolverMenu

    MainChoice -- "4. Keluar" --> StopLoop[Proses: systemRunning = false]
    StopLoop --> End([Output: program berhenti dan tampilkan terima kasih])

    MainChoice -- "Selain 1 sampai 4" --> ChoiceError[/Output: "Pilihan tidak tersedia"/]
    ChoiceError --> MainPause

    MainPause --> Header

    classDef terminator fill:#D5F5E3,stroke:#1E8449,color:#000,stroke-width:2px;
    classDef preparation fill:#E8DAEF,stroke:#7D3C98,color:#000,stroke-width:2px;
    classDef process fill:#D6EAF8,stroke:#2874A6,color:#000,stroke-width:2px;
    classDef inputOutput fill:#FDEBD0,stroke:#CA6F1E,color:#000,stroke-width:2px;
    classDef decision fill:#F9E79F,stroke:#B7950B,color:#000,stroke-width:2px;
    classDef subroutine fill:#D4E6F1,stroke:#2471A3,color:#000,stroke-width:2px;

    class Start,End terminator;
    class PrepMain,TopicInit preparation;
    class ResetInput,IgnoreNewline,IncreaseTopic,LoadQuestions,LoadQuestion,RunChafa,StopLoop,Graphviz process;
    class Header,MainMenu,MainInput,NumberError,DefinitionOutput,MainPause,ListTopic,TopicMenu,TopicInput,TopicError,QuestionMenu,QuestionInput,QuestionError,TextQuestion,ImageShown,ChafaError,SolverMenu,SolverInput,SolverError,SolverPause,ChoiceError inputOutput;
    class NumberValid,MainChoice,TopicLoop,BackFromTopic,TopicValid,BackFromQuestion,QuestionValid,ImageExists,ChafaSuccess,AskAnotherQuestion,AskAnotherTopic decision;
    class Definition,QuestionModule,SolverModule subroutine;
```

## Konvensi flowchart

| Simbol | Bentuk Mermaid | Fungsi |
|---|---|---|
| Terminator | `([ ... ])` | Awal atau akhir program |
| **Preparation / initialization** | `{{ ... }}` | Inisialisasi variabel sebelum proses atau loop |
| Process | `[ ... ]` | Perhitungan atau operasi program |
| Input/Output | `[/ ... /]` | Membaca masukan atau menampilkan keluaran |
| Decision | `{ ... }` | Kondisi yang memiliki cabang Ya/Tidak atau beberapa pilihan |
| Subprogram | `[[ ... ]]` | Pemanggilan fungsi |

## Cakupan loop pertanyaan

1. `topicIndex` berjalan dari **1 sampai 18** supaya setiap topik dan soal terkait masuk ke daftar.
2. Pilihan topik yang salah kembali ke daftar topik.
3. Pilihan soal yang salah kembali ke daftar soal topik tersebut.
4. Setelah melihat soal, pengguna dapat melihat soal lain dalam topik yang sama, berpindah topik, atau kembali ke menu utama.
5. Setiap cabang sukses dan gagal pada Chafa kembali ke alur yang sama, sehingga tidak ada *error gap*.

## Referensi

- `example/TugasKelompokKombinasiDariBapakNovridoCharibaldiYangTerhormat.cpp`: struktur menu, validasi input, percabangan, dan loop kembali ke menu.
- `example/kombinasi.drawio`: penggunaan proses, input/output, keputusan, cabang, dan panah kembali.
- `main.cpp`: alur menu Graf saat ini.
