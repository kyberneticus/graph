#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void printSeparator() { cout << "===================" << endl; }

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

void showQuestion() {
  while (true) {
    cout << "===================== DAFTAR SOAL =====================\n";
    cout << "Sumber: Matematika Diskrit - Bab 8 Graf, halaman 437-442.\n\n";

    for (const Question &question : questions) {
      cout << question.number << ". " << question.title << '\n';
    }
    cout << "0. Kembali ke Main Menu\n\n";
    cout << "Pilih nomor soal: ";

    int selectedNumber;
    if (!(cin >> selectedNumber)) {
      cout << "Input harus berupa angka.\n\n";
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
      cout << "Nomor soal tidak tersedia.\n\n";
      continue;
    }

    cout << "\n======================= SOAL " << selectedQuestion->number
         << " =======================\n";
    cout << selectedQuestion->title << "\n\n";
    cout << selectedQuestion->text << "\n";

    if (selectedQuestion->imagePath != nullptr) {
      cout << "\nGambar graf:\n";
      string command =
          "chafa --size=45x14 " + string(selectedQuestion->imagePath);
      if (system(command.c_str()) != 0) {
        cout << "Gambar tidak dapat ditampilkan. Install Chafa dengan:\n";
        cout << "sudo apt install chafa\n";
      }
    }

    cout << "\nTekan Enter untuk kembali ke daftar soal...";
    cin.get();
    cout << "\n";
  }
}

void showDefinition() {
  cout << "=================== DEFINISI MATERI ===================\n\n";

  cout << "1. GRAF\n";
  cout << "   Graf G = (V, E) terdiri dari himpunan simpul (vertex) V dan\n";
  cout << "   himpunan sisi (edge) E yang menghubungkan pasangan simpul.\n\n";

  cout << "2. JENIS GRAF\n";
  cout << "   Graf sederhana tidak memiliki loop atau sisi ganda. Graf "
          "berarah\n";
  cout << "   memiliki arah pada sisi, sedangkan graf tak berarah tidak.\n\n";

  cout << "3. KETETANGGAAN, INSIDENSI, DAN SIMPUL KHUSUS\n";
  cout << "   Dua simpul bertetangga jika dihubungkan langsung oleh sisi. "
          "Sisi\n";
  cout << "   bersisian dengan simpul pada ujungnya; simpul terpencil tidak\n";
  cout << "   memiliki sisi dan simpul pendant berderajat satu.\n\n";

  cout << "4. DERAJAT SIMPUL DAN LEMMA JABAT TANGAN\n";
  cout << "   Derajat adalah banyak sisi yang bersisian dengan suatu simpul.\n";
  cout << "   Jumlah semua derajat graf tak berarah adalah dua kali jumlah "
          "sisi.\n\n";

  cout << "5. LINTASAN, SIRKUIT, DAN KETERHUBUNGAN\n";
  cout << "   Lintasan adalah urutan simpul yang dihubungkan sisi. Sirkuit\n";
  cout << "   berawal dan berakhir pada simpul yang sama.\n\n";

  cout << "6. SUBGRAF, KOMPONEN, DAN CUT-SET\n";
  cout << "   Subgraf adalah bagian dari graf asal. Komponen adalah subgraf\n";
  cout << "   terhubung maksimal. Cut-set membuat graf tidak terhubung jika "
          "dihapus.\n\n";

  cout << "7. GRAF KHUSUS\n";
  cout << "   Graf lengkap menghubungkan setiap pasangan simpul. Graf "
          "lingkaran\n";
  cout
      << "   berderajat dua, graf teratur berderajat sama, dan graf bipartit\n";
  cout << "   membagi simpul menjadi dua himpunan.\n\n";

  cout << "8. REPRESENTASI GRAF\n";
  cout << "   Graf dapat direpresentasikan dengan matriks ketetanggaan, "
          "matriks\n";
  cout << "   insidensi, atau senarai ketetanggaan.\n\n";

  cout << "9. BFS DAN DFS\n";
  cout
      << "   BFS menelusuri graf per tingkat. DFS menelusuri sedalam mungkin\n";
  cout << "   sebelum kembali ke simpul sebelumnya.\n\n";

  cout << "10. TOPOLOGICAL SORT\n";
  cout
      << "    Pengurutan linear simpul pada graf berarah tanpa siklus (DAG),\n";
  cout << "    sehingga simpul asal suatu sisi berada sebelum simpul "
          "tujuannya.\n\n";

  cout << "11. GRAF ISOMORFIK\n";
  cout << "    Dua graf isomorfik memiliki struktur hubungan yang sama "
          "walaupun\n";
  cout << "    nama atau gambar simpul dan sisinya berbeda.\n\n";

  cout << "12. GRAF PLANAR\n";
  cout << "    Graf planar dapat digambar tanpa sisi saling berpotongan. "
          "Untuk\n";
  cout << "    graf planar terhubung: simpul - sisi + wilayah = 2.\n\n";

  cout << "13. LINTASAN DAN SIRKUIT EULER\n";
  cout << "    Lintasan Euler melewati setiap sisi tepat satu kali. Sirkuit "
          "Euler\n";
  cout << "    juga kembali ke simpul awal.\n\n";

  cout << "14. LINTASAN DAN SIRKUIT HAMILTON\n";
  cout << "    Lintasan Hamilton mengunjungi setiap simpul tepat satu kali.\n";
  cout << "    Sirkuit Hamilton kembali ke simpul awal.\n\n";

  cout << "========================================================\n";
}

int readInteger(const string &prompt) {
  int value;

  while (true) {
    cout << prompt;
    if (cin >> value) {
      cin.ignore(1000, '\n');
      return value;
    }

    cout << "Input harus berupa angka.\n";
    cin.clear();
    cin.ignore(1000, '\n');
  }
}

bool readUndirectedGraph(vector<vector<int>> &graph) {
  int vertexCount = readInteger("Jumlah simpul (1-20): ");
  if (vertexCount < 1 || vertexCount > 20) {
    cout << "Jumlah simpul harus antara 1 sampai 20.\n";
    return false;
  }

  graph.assign(vertexCount, vector<int>(vertexCount, 0));
  cout << "Masukkan 1 jika ada sisi dan 0 jika tidak ada sisi.\n";

  for (int i = 0; i < vertexCount; ++i) {
    for (int j = i + 1; j < vertexCount; ++j) {
      int edge;
      do {
        edge = readInteger("Sisi " + to_string(i + 1) + " - " +
                           to_string(j + 1) + ": ");
        if (edge != 0 && edge != 1) {
          cout << "Masukkan hanya 0 atau 1.\n";
        }
      } while (edge != 0 && edge != 1);

      graph[i][j] = edge;
      graph[j][i] = edge;
    }
  }

  return true;
}

vector<int> graphDegrees(const vector<vector<int>> &graph) {
  vector<int> degrees(graph.size(), 0);

  for (int i = 0; i < static_cast<int>(graph.size()); ++i) {
    for (int j = 0; j < static_cast<int>(graph.size()); ++j) {
      degrees[i] += graph[i][j];
    }
  }

  return degrees;
}

bool isConnectedIgnoringIsolated(const vector<vector<int>> &graph,
                                 const vector<int> &degrees) {
  int start = -1;
  for (int i = 0; i < static_cast<int>(degrees.size()); ++i) {
    if (degrees[i] > 0) {
      start = i;
      break;
    }
  }
  if (start == -1)
    return true;

  vector<bool> visited(graph.size(), false);
  vector<int> stack = {start};
  visited[start] = true;

  while (!stack.empty()) {
    int vertex = stack.back();
    stack.pop_back();

    for (int neighbor = 0; neighbor < static_cast<int>(graph.size());
         ++neighbor) {
      if (graph[vertex][neighbor] == 1 && !visited[neighbor]) {
        visited[neighbor] = true;
        stack.push_back(neighbor);
      }
    }
  }

  for (int i = 0; i < static_cast<int>(degrees.size()); ++i) {
    if (degrees[i] > 0 && !visited[i])
      return false;
  }
  return true;
}

void solveHandshakes() {
  int people;
  do {
    people = readInteger("Jumlah orang: ");
    if (people < 0)
      cout << "Jumlah orang tidak boleh negatif.\n";
  } while (people < 0);

  long long handshakes = 1LL * people * (people - 1) / 2;
  cout << "\nModel: graf lengkap K_" << people << ".\n";
  cout << "Jumlah jabat tangan = n(n-1)/2 = " << people << "(" << people
       << "-1)/2 = " << handshakes << ".\n";
}

void solveSimpleOrRegularGraph() {
  cout << "\n1. Jumlah sisi maksimum graf sederhana\n";
  cout << "2. Validasi graf teratur sederhana\n";
  int choice = readInteger("Pilih (1-2): ");

  if (choice == 1) {
    int vertices = readInteger("Jumlah simpul: ");
    if (vertices < 0) {
      cout << "Jumlah simpul tidak boleh negatif.\n";
      return;
    }
    cout << "Jumlah sisi maksimum = n(n-1)/2 = "
         << 1LL * vertices * (vertices - 1) / 2 << ".\n";
    return;
  }

  if (choice == 2) {
    int vertices = readInteger("Jumlah simpul n: ");
    int degree = readInteger("Derajat setiap simpul r: ");

    if (vertices < 1 || degree < 0 || degree >= vertices ||
        (1LL * vertices * degree) % 2 != 0) {
      cout << "Graf r-teratur sederhana tidak mungkin untuk nilai tersebut.\n";
      return;
    }

    cout << "Graf " << degree << "-teratur dengan " << vertices
         << " simpul mungkin dibuat.\n";
    cout << "Jumlah sisinya = nr/2 = " << vertices << " x " << degree
         << " / 2 = " << 1LL * vertices * degree / 2 << ".\n";
    return;
  }

  cout << "Pilihan tidak tersedia.\n";
}

void solveEuler() {
  vector<vector<int>> graph;
  if (!readUndirectedGraph(graph))
    return;

  vector<int> degrees = graphDegrees(graph);
  int edgeCount = 0;
  int oddCount = 0;
  int start = -1;

  for (int i = 0; i < static_cast<int>(graph.size()); ++i) {
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
    cout << "Graf tidak memiliki sisi untuk dilalui.\n";
    return;
  }
  if (!isConnectedIgnoringIsolated(graph, degrees) || oddCount > 2) {
    cout << "Graf tidak memiliki lintasan Euler.\n";
    return;
  }

  cout << (oddCount == 0
               ? "Graf memiliki sirkuit Euler.\n"
               : "Graf memiliki lintasan Euler, tetapi bukan sirkuit Euler.\n");

  vector<vector<int>> remaining = graph;
  vector<int> stack = {start};
  vector<int> trail;

  while (!stack.empty()) {
    int vertex = stack.back();
    int neighbor = 0;
    while (neighbor < static_cast<int>(remaining.size()) &&
           remaining[vertex][neighbor] == 0) {
      ++neighbor;
    }

    if (neighbor == static_cast<int>(remaining.size())) {
      trail.push_back(vertex);
      stack.pop_back();
    } else {
      remaining[vertex][neighbor] = 0;
      remaining[neighbor][vertex] = 0;
      stack.push_back(neighbor);
    }
  }

  reverse(trail.begin(), trail.end());
  cout << "Rute Euler: ";
  for (int i = 0; i < static_cast<int>(trail.size()); ++i) {
    cout << trail[i] + 1
         << (i + 1 == static_cast<int>(trail.size()) ? "\n" : " -> ");
  }
}

void solvePlanarEulerFormula() {
  int vertices = readInteger("Jumlah simpul n: ");
  int edges = readInteger("Jumlah sisi e: ");

  if (vertices < 3 || edges < 0) {
    cout << "Masukkan n minimal 3 dan jumlah sisi tidak negatif.\n";
    return;
  }

  int maximumPlanarEdges = 3 * vertices - 6;
  cout << "Batas graf planar sederhana: e <= 3n - 6 = " << maximumPlanarEdges
       << ".\n";

  if (edges > maximumPlanarEdges) {
    cout << "Graf pasti tidak planar karena jumlah sisinya melebihi batas.\n";
    return;
  }

  cout << "Graf lulus batas perlu ini, tetapi belum tentu planar.\n";
  cout << "Jika graf terhubung dan planar, jumlah wilayah f = 2 - n + e = "
       << 2 - vertices + edges << ".\n";
}

void solveWelchPowell() {
  vector<vector<int>> graph;
  if (!readUndirectedGraph(graph))
    return;

  vector<int> degrees = graphDegrees(graph);
  vector<int> order(graph.size());
  for (int i = 0; i < static_cast<int>(order.size()); ++i)
    order[i] = i;

  sort(order.begin(), order.end(), [&degrees](int left, int right) {
    if (degrees[left] != degrees[right])
      return degrees[left] > degrees[right];
    return left < right;
  });

  vector<int> colors(graph.size(), -1);
  int colorCount = 0;

  for (int vertex : order) {
    vector<bool> unavailable(graph.size(), false);
    for (int neighbor = 0; neighbor < static_cast<int>(graph.size());
         ++neighbor) {
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

  cout << "\nHasil pewarnaan Welch-Powell:\n";
  for (int vertex = 0; vertex < static_cast<int>(colors.size()); ++vertex) {
    cout << "Simpul " << vertex + 1 << " -> warna " << colors[vertex] + 1
         << '\n';
  }
  cout << "Jumlah warna yang dipakai: " << colorCount << ".\n";
  cout << "Catatan: Welch-Powell menghasilkan pewarnaan valid, tidak selalu "
          "jumlah warna minimum.\n";
}

void renderGraphviz() {
  vector<vector<int>> graph;
  if (!readUndirectedGraph(graph))
    return;

  ofstream dotFile("graphviz-output.dot");
  if (!dotFile) {
    cout << "Gagal membuat file graphviz-output.dot.\n";
    return;
  }

  dotFile << "graph G {\n";
  dotFile << "  layout=neato;\n";
  dotFile << "  node [shape=circle, style=filled, fillcolor=lightblue];\n";

  for (int vertex = 0; vertex < static_cast<int>(graph.size()); ++vertex)
    dotFile << "  " << vertex + 1 << ";\n";

  for (int from = 0; from < static_cast<int>(graph.size()); ++from) {
    for (int to = from + 1; to < static_cast<int>(graph.size()); ++to) {
      if (graph[from][to] == 1)
        dotFile << "  " << from + 1 << " -- " << to + 1 << ";\n";
    }
  }
  dotFile << "}\n";
  dotFile.close();

  if (system("dot -Tpng -Gdpi=300 graphviz-output.dot -o graphviz-output.png") != 0) {
    cout << "Graphviz gagal merender gambar. Pastikan dot sudah terinstall.\n";
    return;
  }

  cout << "File dibuat: graphviz-output.dot dan graphviz-output.png\n";
  if (system("chafa --size=45x14 graphviz-output.png") != 0)
    cout << "PNG berhasil dibuat, tetapi Chafa tidak dapat menampilkannya.\n";
}

void solveQuestion() {
  while (true) {
    cout << "\n=================== PECAHKAN SOAL ====================\n";
    cout << "1. Jabat tangan (graf lengkap)\n";
    cout << "2. Graf sederhana dan graf teratur\n";
    cout << "3. Lintasan atau sirkuit Euler\n";
    cout << "4. Graf planar dan rumus Euler\n";
    cout << "5. Pewarnaan graf Welch-Powell\n";
    cout << "6. Gambar graf dengan Graphviz\n";
    cout << "0. Kembali ke Main Menu\n";

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
      cout << "Pilihan tidak tersedia.\n";
    }

    cout << "\nTekan Enter untuk kembali ke menu pemecahan...";
    cin.get();
  }
}

void mainMenu() {
  printSeparator();
  cout << "     Main Menu     " << endl;
  printSeparator();

  cout << "1. Lihat Definisi Materi\n";
  cout << "2. Lihat Soal\n";
  cout << "3. Peckahkan Soal\n";
  cout << "4. Keluar\n";

  cout << endl;
}

void exit() { cout << "Program berhenti. Terima kasih!\n"; }

int main() {
  bool systemRunning = true;
  int choice = 0;

  while (systemRunning) {
    printHeader();
    mainMenu();
    cout << "Pilih menu (1-4): ";

    if (!(cin >> choice)) {
      cout << "Input harus berupa angka.\n";
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
      cout << "Pilihan tidak tersedia.\n";
    }

    cout << "\nTekan Enter untuk kembali ke menu...";
    cin.get();
  }

  exit();
}
