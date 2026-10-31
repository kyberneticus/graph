#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

const int MAX_VERTICES = 20;
const int MAX_TRAIL = MAX_VERTICES * (MAX_VERTICES - 1) / 2 + 1;

// Menampilkan garis pemisah untuk membatasi bagian keluaran terminal.
void printSeparator() { cout << "===================" << endl; }

// Menampilkan judul program pada bagian atas.
void printHeader() {
  printSeparator();
  cout << "       Graph       " << endl;
  printSeparator();

  cout << endl;
}

struct Question {
  int number;
  const char *title;
  const char *text;
  const char *imagePath;
};

const Question questions[] = {
    {1, "Jabat tangan",
     "Dalam sebuah pesta, sepuluh orang saling berjabat tangan. Tiap orang "
     "hanya berjabat tangan satu kali dengan orang lainnya. Hitung jumlah "
     "jabat tangan yang terjadi. Petunjuk: modelkan persoalan ini ke dalam "
     "graf.",
     nullptr},
    {2, "Penyeberangan sungai",
     "Tiga pasang suami istri hendak menyeberang sungai dengan perahu "
     "berkapasitas maksimal dua orang. Para suami tidak mau meninggalkan istri "
     "mereka bersama lelaki lain. Buatlah graf yang menunjukkan cara "
     "penyeberangan dapat dilakukan.",
     nullptr},
    {3, "Graf turnamen",
     "Empat tim bola basket A, B, C, dan D bermain round-robin; setiap tim "
     "bertemu tim lain satu kali. Gambarkan graf berarah yang menyatakan satu "
     "set pertandingan tersebut.",
     nullptr},
    {4, "Graf sederhana dengan 25 sisi",
     "Sebuah graf akan dibentuk dari 25 sisi. Berapa jumlah maksimum simpul "
     "dalam graf sederhana yang dapat dibuat dari 25 sisi?",
     nullptr},
    {6, "Jaringan komputer",
     "Ada n komputer yang akan dihubungkan dengan sejumlah kabel, baik secara "
     "langsung atau melalui komputer lain. Berapa jumlah minimum kabel yang "
     "dibutuhkan?",
     nullptr},
    {7, "Derajat dua",
     "Tentukan jumlah simpul pada graf sederhana yang mempunyai 12 sisi dan "
     "tiap simpul berderajat dua.",
     nullptr},
    {8, "Graf berderajat sama",
     "Tentukan jumlah simpul pada graf sederhana yang mempunyai 20 sisi dan "
     "tiap simpul berderajat sama.",
     nullptr},
    {9, "Derajat maksimum",
     "Tunjukkan bahwa derajat maksimum sembarang simpul pada sembarang graf "
     "sederhana dengan n simpul adalah n - 1.",
     nullptr},
    {10, "Batas simpul",
     "Berapa jumlah maksimum dan jumlah minimum simpul pada graf sederhana "
     "yang mempunyai 12 sisi dan tiap simpul berderajat minimal 3?",
     nullptr},
    {11, "Graf teratur",
     "Gambarkan dua buah graf teratur berderajat 3 dengan 6 simpul.", nullptr},
    {12, "Graf teratur 7 simpul",
     "Dapatkah kita menggambar graf teratur derajat 3 dengan 7 simpul?",
     nullptr},
    {13, "Keterhubungan kota",
     "Ada n kota yang dihubungkan oleh k jalan raya. Tunjukkan bahwa jika k > "
     "(n - 1)(n - 2)/2, selalu terdapat perjalanan antara sembarang dua kota "
     "melalui jalan penghubungnya.",
     nullptr},
    {14, "Delapan simpul",
     "Dapatkah graf tidak berarah sederhana dengan 8 simpul memiliki 40 sisi?",
     nullptr},
    {15, "Graf isomorfik",
     "Gambarkan dua buah graf dengan lima simpul yang isomorfik.", nullptr},
    {16, "Matriks ketetanggaan",
     "Diketahui matriks ketetanggaan graf tidak berarah:\n0 1 0 0 1\n1 0 1 1 "
     "1\n0 1 1 1 0\n0 1 1 0 1\n1 1 0 1 0",
     nullptr},
    {17, "Graf dari matriks",
     "Gambarkan dua buah graf yang isomorfik sesuai dengan matriks "
     "ketetanggaan pada Soal 16.",
     nullptr},
    {18, "Karakter isomorfik",
     "Manakah di antara sepuluh graf karakter pada gambar yang isomorfik "
     "dengan huruf M?",
     "questions/question-18.png"},
    {19, "Kuratowski",
     "Perlihatkan dengan Teorema Kuratowski bahwa dua graf pada gambar tidak "
     "planar.",
     "questions/question-19.png"},
    {20, "Graf lengkap Euler",
     "Untuk nilai n berapakah graf lengkap K_n merupakan graf Euler?", nullptr},
    {21, "Jembatan Konigsberg",
     "Tambahkan satu jembatan di Konigsberg sehingga terdapat lintasan Euler "
     "yang melalui setiap jembatan. Tentukan tempat jembatan tambahan tersebut "
     "dan gambarkan grafnya.",
     nullptr},
    {22, "Menggambar tanpa mengangkat pensil",
     "Manakah di antara graf pada gambar yang dapat dilukis tanpa mengangkat "
     "pensil sekalipun?",
     "questions/question-22.png"},
    {23, "Lintasan Hamilton",
     "Gambarkan graf yang mempunyai lintasan Hamilton tetapi tidak memiliki "
     "sirkuit Hamilton.",
     nullptr},
    {24, "Euler dan Hamilton",
     "a. Gambarkan graf lima simpul dengan lintasan Euler dan sirkuit "
     "Hamilton.\nb. Gambarkan graf lima simpul dengan sirkuit Euler tetapi "
     "tanpa sirkuit Hamilton.\nc. Gambarkan graf lima simpul tanpa sirkuit "
     "Euler tetapi dengan sirkuit Hamilton.\nd. Gambarkan graf lima simpul "
     "tanpa sirkuit Euler maupun sirkuit Hamilton.",
     nullptr},
    {25, "Rumah tua",
     "Dalam rumah tua besar, setiap kamar berhantu memiliki jumlah pintu "
     "genap. Jika hanya ada satu pintu masuk dari luar, buktikan bahwa orang "
     "yang masuk dari luar selalu dapat mencapai kamar yang tidak berhantu.",
     nullptr},
    {26, "Pernyataan graf tidak planar",
     "Misalkan G adalah graf dengan 11 simpul atau lebih. Tunjukkan bahwa G "
     "tidak planar. Catatan: teks sumber tampak tidak lengkap, karena "
     "pernyataan ini tidak benar untuk semua graf dengan 11 simpul.",
     nullptr},
    {27, "Region graf planar",
     "Tunjukkan bahwa graf planar terhubung dengan 6 simpul dan 12 sisi, "
     "setiap wilayahnya dibatasi oleh 3 sisi.",
     nullptr},
    {28, "Kubus-n dan kode Gray",
     "Kubus-n adalah graf tak berarah dengan 2^n simpul berlabel bilangan "
     "biner n-bit; dua simpul terhubung jika labelnya berbeda pada satu bit. "
     "Tunjukkan bahwa kubus-n mempunyai sirkuit Hamilton untuk n >= 1.",
     nullptr},
    {29, "Pewarnaan zat kimia",
     "Teks sumber menyebut enam zat, tetapi daftar memuat A sampai G. Pasangan "
     "yang tidak dapat disimpan bersama: A-B,D; B-A,D,E,F,G; C-E,G; D-A,B,F; "
     "E-B,C,G; F-B,D; G-C,E. Gambarkan grafnya, jelaskan arti simpul dan sisi, "
     "lalu tentukan jumlah minimum ruang penyimpanan.",
     nullptr},
    {30, "Travelling Salesperson Problem",
     "Tinjau graf berbobot pada gambar. Simpul menyatakan kota dan sisi "
     "menyatakan sarana transportasi dengan bobot ongkos perjalanan. Pedagang "
     "berangkat dari kota a, mengunjungi setiap kota lain tepat sekali, lalu "
     "kembali ke a. Gambarkan semua lintasan dan tentukan rute termurah.",
     "questions/question-30.png"},
    {31, "Kompetisi sepak bola",
     "Dalam kompetisi penuh, setiap tim bertanding dengan setiap tim lain dua "
     "kali. Jika ada 20 tim, berapa banyak pertandingan yang diadakan dan graf "
     "apa yang terbentuk?",
     nullptr},
    {32, "Rute Pak Pos",
     "Tiga peta jalan perumahan ditampilkan pada gambar. Tentukan peta yang "
     "dapat dilalui Pak Pos sehingga setiap ruas jalan dilewati tepat sekali "
     "dan kembali ke titik awal. Jelaskan alasan matematisnya.",
     "questions/question-32.png"},
};

const int questionCount = sizeof(questions) / sizeof(questions[0]);

// Menampilkan daftar soal latihan dan menerima nomor soal dari pengguna.
// Gambar graf terkait ditampilkan dengan Chafa bila file gambarnya tersedia.
void showQuestion() {
  while (true) {
    cout << "===================== DAFTAR SOAL =====================" << endl;
    cout << "Sumber: Matematika Diskrit - Bab 8 Graf, halaman 437-442." << endl
         << endl;

    for (const Question &question : questions) {
      cout << question.number << ". " << question.title << endl;
    }
    cout << "0. Kembali ke Main Menu" << endl << endl;
    cout << "Pilih nomor soal: ";

    int selectedNumber;
    if (!(cin >> selectedNumber)) {
      cout << "Input harus berupa angka." << endl << endl;
      cin.clear();
      cin.ignore(1000, '\n');
      continue;
    }
    cin.ignore(1000, '\n');

    if (selectedNumber == 0)
      return;

    const Question *selectedQuestion = nullptr;
    for (const Question &question : questions) {
      if (question.number == selectedNumber) {
        selectedQuestion = &question;
        break;
      }
    }

    if (selectedQuestion == nullptr) {
      cout << "Nomor soal tidak tersedia." << endl << endl;
      continue;
    }

    cout << endl
         << "======================= SOAL " << selectedQuestion->number
         << " =======================" << endl;
    cout << selectedQuestion->title << endl << endl;
    cout << selectedQuestion->text << endl;

    if (selectedQuestion->imagePath != nullptr) {
      cout << endl << "Gambar graf:" << endl;
      string command =
          "chafa --size=45x14 " + string(selectedQuestion->imagePath);
      if (system(command.c_str()) != 0) {
        cout << "Gambar tidak dapat ditampilkan. Install Chafa dengan:" << endl;
        cout << "sudo apt install chafa" << endl;
      }
    }

    cout << endl << "Tekan Enter untuk kembali ke daftar soal...";
    cin.get();
    cout << endl;
  }
}

// Menampilkan ringkasan definisi materi graf dalam bahasa Indonesia.
// Isi definisi sesuai dengan materi yang dicatat pada proyek ini.
void showDefinition() {
  cout << "=================== DEFINISI MATERI ===================" << endl
       << endl;

  cout << "1. GRAF" << endl;
  cout << "   Graf G = (V, E) terdiri dari himpunan simpul (vertex) V dan"
       << endl;
  cout << "   himpunan sisi (edge) E yang menghubungkan pasangan simpul."
       << endl
       << endl;

  cout << "2. JENIS GRAF" << endl;
  cout << "   Graf sederhana tidak memiliki loop atau sisi ganda. Graf berarah"
       << endl;
  cout << "   memiliki arah pada sisi, sedangkan graf tak berarah tidak."
       << endl
       << endl;

  cout << "3. KETETANGGAAN, INSIDENSI, DAN SIMPUL KHUSUS" << endl;
  cout << "   Dua simpul bertetangga jika dihubungkan langsung oleh sisi. Sisi"
       << endl;
  cout << "   bersisian dengan simpul pada ujungnya; simpul terpencil tidak"
       << endl;
  cout << "   memiliki sisi dan simpul pendant berderajat satu." << endl
       << endl;

  cout << "4. DERAJAT SIMPUL DAN LEMMA JABAT TANGAN" << endl;
  cout << "   Derajat adalah banyak sisi yang bersisian dengan suatu simpul."
       << endl;
  cout
      << "   Jumlah semua derajat graf tak berarah adalah dua kali jumlah sisi."
      << endl
      << endl;

  cout << "5. LINTASAN, SIRKUIT, DAN KETERHUBUNGAN" << endl;
  cout << "   Lintasan adalah urutan simpul yang dihubungkan sisi. Sirkuit"
       << endl;
  cout << "   berawal dan berakhir pada simpul yang sama." << endl << endl;

  cout << "6. SUBGRAF, KOMPONEN, DAN CUT-SET" << endl;
  cout << "   Subgraf adalah bagian dari graf asal. Komponen adalah subgraf"
       << endl;
  cout << "   terhubung maksimal. Cut-set membuat graf tidak terhubung jika"
       << endl;
  cout << "   dihapus." << endl << endl;

  cout << "7. GRAF KHUSUS" << endl;
  cout << "   Graf lengkap menghubungkan setiap pasangan simpul. Graf lingkaran"
       << endl;
  cout << "   berderajat dua, graf teratur berderajat sama, dan graf bipartit"
       << endl;
  cout << "   membagi simpul menjadi dua himpunan." << endl << endl;

  cout << "8. REPRESENTASI GRAF" << endl;
  cout << "   Graf dapat direpresentasikan dengan matriks ketetanggaan, matriks"
       << endl;
  cout << "   insidensi, atau senarai ketetanggaan." << endl << endl;

  cout << "9. BFS DAN DFS" << endl;
  cout << "   BFS menelusuri graf per tingkat. DFS menelusuri sedalam mungkin"
       << endl;
  cout << "   sebelum kembali ke simpul sebelumnya." << endl << endl;

  cout << "10. TOPOLOGICAL SORT" << endl;
  cout << "    Pengurutan linear simpul pada graf berarah tanpa siklus (DAG),"
       << endl;
  cout << "    sehingga simpul asal suatu sisi berada sebelum simpul tujuannya."
       << endl
       << endl;

  cout << "11. GRAF ISOMORFIK" << endl;
  cout << "    Dua graf isomorfik memiliki struktur hubungan yang sama walaupun"
       << endl;
  cout << "    nama atau gambar simpul dan sisinya berbeda." << endl << endl;

  cout << "12. GRAF PLANAR" << endl;
  cout << "    Graf planar dapat digambar tanpa sisi saling berpotongan. Untuk"
       << endl;
  cout << "    graf planar terhubung: simpul - sisi + wilayah = 2." << endl
       << endl;

  cout << "13. LINTASAN DAN SIRKUIT EULER" << endl;
  cout << "    Lintasan Euler melewati setiap sisi tepat satu kali. Sirkuit "
          "Euler"
       << endl;
  cout << "    juga kembali ke simpul awal." << endl << endl;

  cout << "14. LINTASAN DAN SIRKUIT HAMILTON" << endl;
  cout << "    Lintasan Hamilton mengunjungi setiap simpul tepat satu kali."
       << endl;
  cout << "    Sirkuit Hamilton kembali ke simpul awal." << endl << endl;

  cout << "========================================================" << endl;
}

// Membaca satu bilangan bulat sambil menampilkan pesan input yang diberikan.
// Input selain angka dibersihkan agar pengguna dapat mencoba kembali.
int readInteger(const string &prompt) {
  int value;

  while (true) {
    cout << prompt;
    if (cin >> value) {
      cin.ignore(1000, '\n');
      return value;
    }

    cout << "Input harus berupa angka." << endl;
    cin.clear();
    cin.ignore(1000, '\n');
  }
}

// Membaca graf sederhana tak berarah sebagai matriks ketetanggaan 0 atau 1.
// Matriks memakai array tetap karena program membatasi graf hingga 20 simpul.
bool readUndirectedGraph(int graph[MAX_VERTICES][MAX_VERTICES],
                         int &vertexCount) {
  vertexCount = readInteger("Jumlah simpul (1-20): ");
  if (vertexCount < 1 || vertexCount > MAX_VERTICES) {
    cout << "Jumlah simpul harus antara 1 sampai 20." << endl;
    return false;
  }

  for (int i = 0; i < MAX_VERTICES; ++i) {
    for (int j = 0; j < MAX_VERTICES; ++j) {
      graph[i][j] = 0;
    }
  }

  cout << "Masukkan 1 jika ada sisi dan 0 jika tidak ada sisi." << endl;
  for (int i = 0; i < vertexCount; ++i) {
    for (int j = i + 1; j < vertexCount; ++j) {
      int edge;
      do {
        edge = readInteger("Sisi " + to_string(i + 1) + " - " +
                           to_string(j + 1) + ": ");
        if (edge != 0 && edge != 1)
          cout << "Masukkan hanya 0 atau 1." << endl;
      } while (edge != 0 && edge != 1);

      graph[i][j] = edge;
      graph[j][i] = edge;
    }
  }

  return true;
}

// Menghitung derajat setiap simpul dari matriks ketetanggaan graf.
// Nilai hasil pada indeks i adalah derajat simpul i + 1.
void graphDegrees(const int graph[MAX_VERTICES][MAX_VERTICES], int vertexCount,
                  int degrees[MAX_VERTICES]) {
  for (int i = 0; i < vertexCount; ++i) {
    degrees[i] = 0;
    for (int j = 0; j < vertexCount; ++j) {
      degrees[i] += graph[i][j];
    }
  }
}

// Memeriksa keterhubungan semua simpul yang mempunyai setidaknya satu sisi.
// Simpul terpencil diabaikan karena tidak memengaruhi syarat lintasan Euler.
bool isConnectedIgnoringIsolated(const int graph[MAX_VERTICES][MAX_VERTICES],
                                 int vertexCount,
                                 const int degrees[MAX_VERTICES]) {
  int start = -1;
  for (int i = 0; i < vertexCount; ++i) {
    if (degrees[i] > 0) {
      start = i;
      break;
    }
  }
  if (start == -1)
    return true;

  bool visited[MAX_VERTICES] = {};
  int stack[MAX_VERTICES];
  int stackSize = 0;
  stack[stackSize++] = start;
  visited[start] = true;

  while (stackSize > 0) {
    int vertex = stack[--stackSize];

    for (int neighbor = 0; neighbor < vertexCount; ++neighbor) {
      if (graph[vertex][neighbor] == 1 && !visited[neighbor]) {
        visited[neighbor] = true;
        stack[stackSize++] = neighbor;
      }
    }
  }

  for (int i = 0; i < vertexCount; ++i) {
    if (degrees[i] > 0 && !visited[i])
      return false;
  }
  return true;
}

// Menyelesaikan soal jabat tangan dengan model graf lengkap K_n.
// Hasil dihitung menggunakan rumus n(n - 1) / 2.
void solveHandshakes() {
  int people;
  do {
    people = readInteger("Jumlah orang: ");
    if (people < 0)
      cout << "Jumlah orang tidak boleh negatif." << endl;
  } while (people < 0);

  long long handshakes = 1LL * people * (people - 1) / 2;
  cout << endl << "Model: graf lengkap K_" << people << "." << endl;
  cout << "Jumlah jabat tangan = n(n-1)/2 = " << people << "(" << people
       << "-1)/2 = " << handshakes << "." << endl;
}

// Menghitung sisi maksimum graf sederhana atau memvalidasi graf teratur.
// Pengguna memilih jenis perhitungan yang ingin dijalankan dari submenu.
void solveSimpleOrRegularGraph() {
  cout << endl << "1. Jumlah sisi maksimum graf sederhana" << endl;
  cout << "2. Validasi graf teratur sederhana" << endl;
  int choice = readInteger("Pilih (1-2): ");

  if (choice == 1) {
    int vertices = readInteger("Jumlah simpul: ");
    if (vertices < 0) {
      cout << "Jumlah simpul tidak boleh negatif." << endl;
      return;
    }
    cout << "Jumlah sisi maksimum = n(n-1)/2 = "
         << 1LL * vertices * (vertices - 1) / 2 << "." << endl;
    return;
  }

  if (choice == 2) {
    int vertices = readInteger("Jumlah simpul n: ");
    int degree = readInteger("Derajat setiap simpul r: ");

    if (vertices < 1 || degree < 0 || degree >= vertices ||
        (1LL * vertices * degree) % 2 != 0) {
      cout << "Graf r-teratur sederhana tidak mungkin untuk nilai tersebut."
           << endl;
      return;
    }

    cout << "Graf " << degree << "-teratur dengan " << vertices
         << " simpul mungkin dibuat." << endl;
    cout << "Jumlah sisinya = nr/2 = " << vertices << " x " << degree
         << " / 2 = " << 1LL * vertices * degree / 2 << "." << endl;
    return;
  }

  cout << "Pilihan tidak tersedia." << endl;
}

// Memeriksa apakah graf mempunyai lintasan atau sirkuit Euler.
// Jika ada, fungsi membentuk dan menampilkan rute Euler dengan algoritma
// Hierholzer.
void solveEuler() {
  int graph[MAX_VERTICES][MAX_VERTICES];
  int vertexCount;
  if (!readUndirectedGraph(graph, vertexCount))
    return;

  int degrees[MAX_VERTICES];
  graphDegrees(graph, vertexCount, degrees);
  int edgeCount = 0;
  int oddCount = 0;
  int start = -1;

  for (int i = 0; i < vertexCount; ++i) {
    edgeCount += degrees[i];
    if (degrees[i] % 2 != 0) {
      ++oddCount;
      start = i;
    }
    if (start == -1 && degrees[i] > 0)
      start = i;
  }
  edgeCount /= 2;

  if (edgeCount == 0) {
    cout << "Graf tidak memiliki sisi untuk dilalui." << endl;
    return;
  }
  if (!isConnectedIgnoringIsolated(graph, vertexCount, degrees) ||
      oddCount > 2) {
    cout << "Graf tidak memiliki lintasan Euler." << endl;
    return;
  }

  if (oddCount == 0)
    cout << "Graf memiliki sirkuit Euler." << endl;
  else
    cout << "Graf memiliki lintasan Euler, tetapi bukan sirkuit Euler." << endl;

  int remaining[MAX_VERTICES][MAX_VERTICES];
  for (int i = 0; i < vertexCount; ++i) {
    for (int j = 0; j < vertexCount; ++j) {
      remaining[i][j] = graph[i][j];
    }
  }

  int stack[MAX_TRAIL];
  int trail[MAX_TRAIL];
  int stackSize = 0;
  int trailSize = 0;
  stack[stackSize++] = start;

  while (stackSize > 0) {
    int vertex = stack[stackSize - 1];
    int neighbor = 0;
    while (neighbor < vertexCount && remaining[vertex][neighbor] == 0)
      ++neighbor;

    if (neighbor == vertexCount) {
      trail[trailSize++] = vertex;
      --stackSize;
    } else {
      remaining[vertex][neighbor] = 0;
      remaining[neighbor][vertex] = 0;
      stack[stackSize++] = neighbor;
    }
  }

  cout << "Rute Euler: ";
  for (int i = trailSize - 1; i >= 0; --i) {
    cout << trail[i] + 1;
    if (i == 0)
      cout << endl;
    else
      cout << " -> ";
  }
}

// Memeriksa batas jumlah sisi untuk graf planar sederhana.
// Fungsi juga menghitung jumlah wilayah jika graf tersebut planar dan
// terhubung.
void solvePlanarEulerFormula() {
  int vertices = readInteger("Jumlah simpul n: ");
  int edges = readInteger("Jumlah sisi e: ");

  if (vertices < 3 || edges < 0) {
    cout << "Masukkan n minimal 3 dan jumlah sisi tidak negatif." << endl;
    return;
  }

  int maximumPlanarEdges = 3 * vertices - 6;
  cout << "Batas graf planar sederhana: e <= 3n - 6 = " << maximumPlanarEdges
       << "." << endl;

  if (edges > maximumPlanarEdges) {
    cout << "Graf pasti tidak planar karena jumlah sisinya melebihi batas."
         << endl;
    return;
  }

  cout << "Graf lulus batas perlu ini, tetapi belum tentu planar." << endl;
  cout << "Jika graf terhubung dan planar, jumlah wilayah f = 2 - n + e = "
       << 2 - vertices + edges << "." << endl;
}

// Mewarnai graf tak berarah menggunakan urutan derajat Welch-Powell.
// Warna yang dihasilkan valid, tetapi belum tentu merupakan jumlah warna
// minimum.
void solveWelchPowell() {
  int graph[MAX_VERTICES][MAX_VERTICES];
  int vertexCount;
  if (!readUndirectedGraph(graph, vertexCount))
    return;

  int degrees[MAX_VERTICES];
  int order[MAX_VERTICES];
  int colors[MAX_VERTICES];
  graphDegrees(graph, vertexCount, degrees);

  for (int i = 0; i < vertexCount; ++i) {
    order[i] = i;
    colors[i] = -1;
  }

  for (int i = 0; i < vertexCount - 1; ++i) {
    for (int j = i + 1; j < vertexCount; ++j) {
      if (degrees[order[j]] > degrees[order[i]]) {
        int temporary = order[i];
        order[i] = order[j];
        order[j] = temporary;
      }
    }
  }

  int colorCount = 0;
  for (int i = 0; i < vertexCount; ++i) {
    int vertex = order[i];
    bool unavailable[MAX_VERTICES] = {};

    for (int neighbor = 0; neighbor < vertexCount; ++neighbor) {
      if (graph[vertex][neighbor] == 1 && colors[neighbor] != -1) {
        unavailable[colors[neighbor]] = true;
      }
    }

    int color = 0;
    while (unavailable[color])
      ++color;
    colors[vertex] = color;
    if (color + 1 > colorCount)
      colorCount = color + 1;
  }

  cout << endl << "Hasil pewarnaan Welch-Powell:" << endl;
  for (int vertex = 0; vertex < vertexCount; ++vertex) {
    cout << "Simpul " << vertex + 1 << " -> warna " << colors[vertex] + 1
         << endl;
  }
  cout << "Jumlah warna yang dipakai: " << colorCount << "." << endl;
  cout << "Catatan: Welch-Powell menghasilkan pewarnaan valid, tidak selalu "
          "jumlah warna minimum."
       << endl;
}

// Mengekspor graf masukan ke file DOT dan merendernya dengan Graphviz.
// PNG hasil render disimpan lalu ditampilkan di terminal menggunakan Chafa.
void renderGraphviz() {
  int graph[MAX_VERTICES][MAX_VERTICES];
  int vertexCount;
  if (!readUndirectedGraph(graph, vertexCount))
    return;

  ofstream dotFile("graphviz-output.dot");
  if (!dotFile) {
    cout << "Gagal membuat file graphviz-output.dot." << endl;
    return;
  }

  dotFile << "graph G {" << endl;
  dotFile << "  layout=neato;" << endl;
  dotFile << "  node [shape=circle, style=filled, fillcolor=lightblue];"
          << endl;

  for (int vertex = 0; vertex < vertexCount; ++vertex)
    dotFile << "  " << vertex + 1 << ";" << endl;

  for (int from = 0; from < vertexCount; ++from) {
    for (int to = from + 1; to < vertexCount; ++to) {
      if (graph[from][to] == 1)
        dotFile << "  " << from + 1 << " -- " << to + 1 << ";" << endl;
    }
  }
  dotFile << "}" << endl;
  dotFile.close();

  if (system(
          "dot -Tpng -Gdpi=300 graphviz-output.dot -o graphviz-output.png") !=
      0) {
    cout << "Graphviz gagal merender gambar. Pastikan dot sudah terinstall."
         << endl;
    return;
  }

  cout << "File dibuat: graphviz-output.dot dan graphviz-output.png" << endl;
  if (system("chafa --size=45x14 graphviz-output.png") != 0)
    cout << "PNG berhasil dibuat, tetapi Chafa tidak dapat menampilkannya."
         << endl;
}

// Menampilkan submenu pemecahan soal berdasarkan topik graf yang didukung.
// Setiap pilihan menjalankan solver interaktif lalu kembali ke submenu ini.
void solveQuestion() {
  while (true) {
    cout << endl
         << "=================== PECAHKAN SOAL ====================" << endl;
    cout << "1. Jabat tangan (graf lengkap)" << endl;
    cout << "2. Graf sederhana dan graf teratur" << endl;
    cout << "3. Lintasan atau sirkuit Euler" << endl;
    cout << "4. Graf planar dan rumus Euler" << endl;
    cout << "5. Pewarnaan graf Welch-Powell" << endl;
    cout << "6. Gambar graf dengan Graphviz" << endl;
    cout << "0. Kembali ke Main Menu" << endl;

    int choice = readInteger("Pilih topik: ");
    if (choice == 0)
      return;

    switch (choice) {
    case 1:
      solveHandshakes();
      break;
    case 2:
      solveSimpleOrRegularGraph();
      break;
    case 3:
      solveEuler();
      break;
    case 4:
      solvePlanarEulerFormula();
      break;
    case 5:
      solveWelchPowell();
      break;
    case 6:
      renderGraphviz();
      break;
    default:
      cout << "Pilihan tidak tersedia." << endl;
    }

    cout << endl << "Tekan Enter untuk kembali ke menu pemecahan...";
    cin.get();
  }
}

// Menampilkan pilihan utama program untuk materi, soal, solver, dan keluar.
// Pemrosesan pilihan pengguna dilakukan di fungsi main().
void mainMenu() {
  printSeparator();
  cout << "     Main Menu     " << endl;
  printSeparator();

  cout << "1. Lihat Definisi Materi" << endl;
  cout << "2. Lihat Soal" << endl;
  cout << "3. Pecahkan Soal" << endl;
  cout << "4. Keluar" << endl;

  cout << endl;
}

// Menampilkan pesan penutup saat pengguna memilih keluar dari program.
// Fungsi ini dipanggil sekali setelah perulangan menu utama selesai.
void exit() { cout << "Program berhenti. Terima kasih!" << endl; }

// Menjalankan perulangan menu utama sampai pengguna memilih opsi keluar.
// Fungsi mengarahkan setiap pilihan ke fitur program yang sesuai.
int main() {
  bool systemRunning = true;
  int choice = 0;

  while (systemRunning) {
    printHeader();
    mainMenu();
    cout << "Pilih menu (1-4): ";

    if (!(cin >> choice)) {
      cout << "Input harus berupa angka." << endl;
      cin.clear();
      cin.ignore(1000, '\n');
      continue;
    }

    cin.ignore(1000, '\n');

    switch (choice) {
    case 1:
      showDefinition();
      break;
    case 2:
      showQuestion();
      continue;
    case 3:
      solveQuestion();
      continue;
    case 4:
      systemRunning = false;
      continue;
    default:
      cout << "Pilihan tidak tersedia." << endl;
    }

    cout << endl << "Tekan Enter untuk kembali ke menu...";
    cin.get();
  }

  exit();
}
