#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

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
    {1, "Graf teratur berderajat 3",
     "Apakah memungkinkan untuk sebuah graf teratur berderajat 3 memiliki 7 "
     "simpul?",
     nullptr},
    {2, "Graf sederhana berderajat 2",
     "Tentukan jumlah simpul pada graf sederhana bila memiliki 13 sisi dan "
     "setiap simpul berderajat 2.",
     nullptr},
    {3, "Graf Euler dan Hamilton",
     "Tentukan apakah graf di atas merupakan graf Euler dan tentukan juga "
     "apakah graf tersebut merupakan graf Hamiltonian!",
     "questions/question-3.jpeg"},
    {4, "DFS dan BFS",
     "Telusuri graf pada Soal 3 dengan menggunakan DFS dan BFS.",
     "questions/question-3.jpeg"},
};

const int questionCount = sizeof(questions) / sizeof(questions[0]);

// Menampilkan isi soal dan gambar terkait bila tersedia.
void showQuestionDetails(const Question &question) {
  cout << endl << "======================= SOAL " << question.number
       << " =======================" << endl;
  cout << question.title << endl << endl;
  cout << question.text << endl;

  if (question.imagePath != nullptr) {
    cout << endl << "Gambar graf:" << endl;
    string command = "chafa --size=45x14 " + string(question.imagePath);
    if (system(command.c_str()) != 0) {
      cout << "Gambar tidak dapat ditampilkan. Install Chafa dengan:" << endl;
      cout << "sudo apt install chafa" << endl;
    }
  }
}

// Menampilkan daftar soal latihan dan menyimpan soal terakhir yang dipilih.
void showQuestion(const Question *&pinnedQuestion) {
  while (true) {
    cout << "===================== DAFTAR SOAL =====================" << endl
         << endl;
    for (const Question &question : questions)
      cout << question.number << ". " << question.title << endl;

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

    pinnedQuestion = selectedQuestion;
    showQuestionDetails(*pinnedQuestion);
    cout << endl << "Tekan Enter untuk kembali ke daftar soal...";
    cin.get();
    cout << endl;
  }
}

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

void solveRegularGraph() {
  cout << "Jumlah derajat = 7 x 3 = 21." << endl;
  cout << "Jumlah derajat graf harus genap, jadi graf 3-teratur dengan 7 "
          "simpul tidak mungkin dibuat."
       << endl;
}

void solveDegreeTwoGraph() {
  cout << "Jumlah derajat = 2e = 2 x 13 = 26." << endl;
  cout << "Karena setiap simpul berderajat 2, 2n = 26 sehingga n = 13 "
          "simpul."
       << endl;
}

void solveEulerAndHamilton() {
  cout << "Derajat simpul 1 sampai 6: 5, 5, 4, 4, 3, 5." << endl;
  cout << "Graf bukan graf Euler karena simpul 1, 2, 5, dan 6 berderajat "
          "ganjil."
       << endl;
  cout << "Graf juga tidak memiliki lintasan Euler karena ada empat simpul "
          "berderajat ganjil."
       << endl;
  cout << "Graf Hamiltonian: 1 -> 5 -> 6 -> 3 -> 4 -> 2 -> 1." << endl;
}

void solveDfsAndBfs() {
  cout << "Mulai dari simpul 1 dan memilih tetangga bernomor terkecil terlebih "
          "dahulu:"
       << endl;
  cout << "DFS: 1 -> 2 -> 3 -> 4 -> 6 -> 5" << endl;
  cout << "BFS: 1 -> 2 -> 3 -> 4 -> 5 -> 6" << endl;
}

// Menampilkan solver yang sesuai dengan empat soal latihan.
void solveQuestion(const Question *pinnedQuestion) {
  while (true) {
    if (pinnedQuestion != nullptr)
      showQuestionDetails(*pinnedQuestion);

    cout << endl
         << "=================== PECAHKAN SOAL ====================" << endl;
    cout << "1. Graf teratur berderajat 3 (Soal 1)" << endl;
    cout << "2. Graf sederhana berderajat 2 (Soal 2)" << endl;
    cout << "3. Graf Euler dan Hamilton (Soal 3)" << endl;
    cout << "4. DFS dan BFS (Soal 4)" << endl;
    cout << "0. Kembali ke Main Menu" << endl;

    int choice = readInteger("Pilih solver: ");
    if (choice == 0)
      return;

    switch (choice) {
    case 1:
      solveRegularGraph();
      break;
    case 2:
      solveDegreeTwoGraph();
      break;
    case 3:
      solveEulerAndHamilton();
      break;
    case 4:
      solveDfsAndBfs();
      break;
    default:
      cout << "Pilihan tidak tersedia." << endl;
    }

    cout << endl << "Tekan Enter untuk kembali ke menu pemecahan...";
    cin.get();
  }
}

void mainMenu() {
  printSeparator();
  cout << "     Main Menu     " << endl;
  printSeparator();
  cout << "1. Lihat Soal" << endl;
  cout << "2. Pecahkan Soal" << endl;
  cout << "3. Keluar" << endl << endl;
}

int main() {
  const Question *pinnedQuestion = nullptr;

  while (true) {
    printHeader();
    mainMenu();
    int choice = readInteger("Pilih menu (1-3): ");

    switch (choice) {
    case 1:
      showQuestion(pinnedQuestion);
      break;
    case 2:
      solveQuestion(pinnedQuestion);
      break;
    case 3:
      cout << "Program berhenti. Terima kasih!" << endl;
      return 0;
    default:
      cout << "Pilihan tidak tersedia." << endl;
    }
  }
}
