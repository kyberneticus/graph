# Flowchart Program Graf

Dokumen ini menggambarkan **alur kode `main.cpp` saat ini**. Diagram dipecah menjadi halaman/subproses agar tetap mudah dibaca dan tidak memiliki garis yang saling berpotongan.

Konvensi yang dipakai mengikuti [Flowchart Drawing Specifications dari ProcessOn](https://www.processon.io/blog/flowchart-drawing-specifications): alur dari atas ke bawah, satu titik mulai pada diagram utama, teks ringkas, proses ber-input/output tunggal, serta setiap keputusan memiliki cabang berlabel.

Salin blok Mermaid ke [Mermaid AI](https://mermaid.ai/) bila ingin merender diagramnya.

## Halaman 1 — Alur utama `main()`

```mermaid
flowchart TD
    Start([Mulai]) --> Init{{Persiapan: systemRunning = true; choice = 0}}
    Init --> MainLoop((Ulangi menu))
    MainLoop --> Running{systemRunning bernilai true?}

    Running -- Tidak --> ExitMessage[/Output: tampilkan pesan terima kasih/]
    ExitMessage --> End([Selesai])

    Running -- Ya --> Header[/Output: tampilkan header/]
    Header --> Menu[/Output: tampilkan Main Menu/]
    Menu --> InputChoice[/Input: masukkan pilihan 1 sampai 4/]
    InputChoice --> IsNumber{Input berupa angka?}

    IsNumber -- Tidak --> InputError[/Output: "Input harus berupa angka"/]
    InputError --> ClearInput[Proses: cin.clear dan cin.ignore]
    ClearInput --> MainLoop

    IsNumber -- Ya --> IgnoreNewline[Proses: cin.ignore newline]
    IgnoreNewline --> Choice{Nilai choice?}

    Choice -- "1: Definisi" --> Definition[[Subproses: showDefinition]]
    Definition --> PauseMain[/Input: tekan Enter/]
    PauseMain --> MainLoop

    Choice -- "2: Soal" --> Questions[[Subproses: showQuestion; lihat Halaman 2]]
    Questions --> MainLoop

    Choice -- "3: Pecahkan Soal" --> Solver[[Subproses: solveQuestion; lihat Halaman 3]]
    Solver --> MainLoop

    Choice -- "4: Keluar" --> StopProgram[Proses: systemRunning = false]
    StopProgram --> MainLoop

    Choice -- "Selain 1 sampai 4" --> ChoiceError[/Output: "Pilihan tidak tersedia"/]
    ChoiceError --> PauseMain

    classDef terminator fill:#D5F5E3,stroke:#1E8449,color:#000,stroke-width:2px;
    classDef preparation fill:#E8DAEF,stroke:#7D3C98,color:#000,stroke-width:2px;
    classDef process fill:#D6EAF8,stroke:#2874A6,color:#000,stroke-width:2px;
    classDef io fill:#FDEBD0,stroke:#CA6F1E,color:#000,stroke-width:2px;
    classDef decision fill:#F9E79F,stroke:#B7950B,color:#000,stroke-width:2px;
    classDef subprocess fill:#D4E6F1,stroke:#2471A3,color:#000,stroke-width:2px;
    classDef connector fill:#FFFFFF,stroke:#555555,color:#000,stroke-width:2px;

    class Start,End terminator;
    class MainLoop connector;
    class Init preparation;
    class ClearInput,IgnoreNewline,StopProgram process;
    class Header,Menu,InputChoice,InputError,ExitMessage,PauseMain,ChoiceError io;
    class Running,IsNumber,Choice decision;
    class Definition,Questions,Solver subprocess;
```

## Halaman 2 — Subproses `showQuestion()`

```mermaid
flowchart TD
    SQEntry((Dipanggil oleh main)) --> ListQuestions[/Output: tampilkan 31 soal dan pilihan 0/]
    ListQuestions --> InputQuestion[/Input: masukkan nomor soal/]
    InputQuestion --> QuestionIsNumber{Input berupa angka?}

    QuestionIsNumber -- Tidak --> NumberError[/Output: "Input harus berupa angka"/]
    NumberError --> ClearQuestionInput[Proses: cin.clear dan cin.ignore]
    ClearQuestionInput --> ListQuestions

    QuestionIsNumber -- Ya --> IgnoreQuestionNewline[Proses: cin.ignore newline]
    IgnoreQuestionNewline --> BackToMain{Nomor soal = 0?}
    BackToMain -- Ya --> SQReturn((Kembali ke main))

    BackToMain -- Tidak --> FindQuestion[Proses: cari nomor soal pada array questions]
    FindQuestion --> QuestionExists{Soal ditemukan?}
    QuestionExists -- Tidak --> MissingQuestion[/Output: "Nomor soal tidak tersedia"/]
    MissingQuestion --> ListQuestions

    QuestionExists -- Ya --> ShowText[/Output: tampilkan judul dan teks soal/]
    ShowText --> HasImage{Soal memiliki imagePath?}

    HasImage -- Tidak --> PauseQuestion[/Input: tekan Enter/]
    HasImage -- Ya --> RunChafa[Proses: jalankan Chafa untuk gambar soal]
    RunChafa --> ChafaSuccess{Chafa berhasil?}
    ChafaSuccess -- Ya --> ShowImage[/Output: gambar tampil di terminal/]
    ChafaSuccess -- Tidak --> ChafaError[/Output: tampilkan pesan instalasi Chafa/]
    ShowImage --> PauseQuestion
    ChafaError --> PauseQuestion
    PauseQuestion --> ListQuestions

    classDef connector fill:#FFFFFF,stroke:#555555,color:#000,stroke-width:2px;
    classDef process fill:#D6EAF8,stroke:#2874A6,color:#000,stroke-width:2px;
    classDef io fill:#FDEBD0,stroke:#CA6F1E,color:#000,stroke-width:2px;
    classDef decision fill:#F9E79F,stroke:#B7950B,color:#000,stroke-width:2px;

    class SQEntry,SQReturn connector;
    class ClearQuestionInput,IgnoreQuestionNewline,FindQuestion,RunChafa process;
    class ListQuestions,InputQuestion,NumberError,MissingQuestion,ShowText,ShowImage,ChafaError,PauseQuestion io;
    class QuestionIsNumber,BackToMain,QuestionExists,HasImage,ChafaSuccess decision;
```

## Halaman 3 — Subproses `solveQuestion()`

```mermaid
flowchart TD
    SSQEntry((Dipanggil oleh main)) --> SolverMenu[/Output: tampilkan menu pemecahan soal/]
    SolverMenu --> SolverInput[/Input: pilih topik solver atau 0/]
    SolverInput --> BackSolver{Pilihan = 0?}
    BackSolver -- Ya --> SSQReturn((Kembali ke main))

    BackSolver -- Tidak --> SolverChoice{Nilai pilihan solver?}
    SolverChoice -- "1" --> Regular[/Output: 7 x 3 = 21, jadi tidak mungkin/]
    SolverChoice -- "2" --> DegreeTwo[/Output: 2n = 2 x 13, jadi n = 13/]
    SolverChoice -- "3" --> EulerHamilton[/Output: bukan Euler; sirkuit Hamilton ditampilkan/]
    SolverChoice -- "4" --> Traversal[/Output: DFS dan BFS dari simpul 1/]
    SolverChoice -- "Selain 1 sampai 4" --> SolverError[/Output: "Pilihan tidak tersedia"/]

    Regular --> SolverPause[/Input: tekan Enter/]
    DegreeTwo --> SolverPause
    EulerHamilton --> SolverPause
    Traversal --> SolverPause
    SolverError --> SolverPause
    SolverPause --> SolverMenu

    classDef connector fill:#FFFFFF,stroke:#555555,color:#000,stroke-width:2px;
    classDef io fill:#FDEBD0,stroke:#CA6F1E,color:#000,stroke-width:2px;
    classDef decision fill:#F9E79F,stroke:#B7950B,color:#000,stroke-width:2px;
    classDef subprocess fill:#D4E6F1,stroke:#2471A3,color:#000,stroke-width:2px;

    class SSQEntry,SSQReturn connector;
    class SolverMenu,SolverInput,SolverError,SolverPause io;
    class BackSolver,SolverChoice decision;
    class Regular,DegreeTwo,EulerHamilton,Traversal io;
```

## Shape convention

| Symbol | Mermaid form | Meaning |
|---|---|---|
| Terminator | `([ ... ])` | Only the main program start/end |
| Preparation | `{{ ... }}` | Variable or matrix initialization |
| Process | `[ ... ]` | Calculation or state-changing operation |
| Input/Output | `[/ ... /]` | Read input or write terminal output |
| Decision | `{ ... }` | One input, multiple labelled output branches |
| Subprocess | `[[ ... ]]` | A function detailed on another page |
| Connector | `(( ... ))` | Cross-page call/return point for a subprocess |

## Verification checklist

- The main diagram has one start symbol and one end symbol.
- Every decision has all of its outcomes labelled.
- All non-terminal paths return to the menu or to the calling process.
- Complex logic is split into subprocess pages instead of using crossed arrows.
- Every diagram flows from top to bottom with concise labels.

## References

- [ProcessOn — Flowchart Drawing Specifications](https://www.processon.io/blog/flowchart-drawing-specifications)
- `main.cpp` — source of the actual program flow
