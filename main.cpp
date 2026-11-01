#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

const int QUESTION_GRAPH_VERTICES = 6;

// Matriks ketetanggaan graf pada Soal 3 dan Soal 4.
const int questionGraph[QUESTION_GRAPH_VERTICES][QUESTION_GRAPH_VERTICES] = {
    {0, 1, 1, 1, 1, 1},
    {1, 0, 1, 1, 1, 1},
    {1, 1, 0, 1, 0, 1},
    {1, 1, 1, 0, 0, 1},
    {1, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 0},
};

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

void showQuestionDetails(const Question &question) {
  cout << endl << "======================= SOAL " << question.number
       << " =======================" << endl;
  cout << question.title << endl << endl;
  cout << question.text << endl;

  if (question.imagePath != nullptr) {
    cout << endl << "Gambar graf:" << endl;
    string command = "chafa --size=45x14 " + string(question.imagePath);
    if (system(command.c_str()) != 0)
      cout << "Gambar tidak dapat ditampilkan. Install Chafa dengan: sudo apt "
              "install chafa"
           << endl;
  }
}

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
    return;
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

void graphDegrees(const int graph[QUESTION_GRAPH_VERTICES]
                                [QUESTION_GRAPH_VERTICES],
                  int degrees[QUESTION_GRAPH_VERTICES]) {
  for (int vertex = 0; vertex < QUESTION_GRAPH_VERTICES; ++vertex) {
    degrees[vertex] = 0;
    for (int neighbor = 0; neighbor < QUESTION_GRAPH_VERTICES; ++neighbor)
      degrees[vertex] += graph[vertex][neighbor];
  }
}

void depthFirstSearch(const int graph[QUESTION_GRAPH_VERTICES]
                                    [QUESTION_GRAPH_VERTICES],
                      int vertex, bool visited[QUESTION_GRAPH_VERTICES],
                      int order[QUESTION_GRAPH_VERTICES], int &orderSize) {
  visited[vertex] = true;
  order[orderSize++] = vertex;

  for (int neighbor = 0; neighbor < QUESTION_GRAPH_VERTICES; ++neighbor) {
    if (graph[vertex][neighbor] != 0 && !visited[neighbor])
      depthFirstSearch(graph, neighbor, visited, order, orderSize);
  }
}

void breadthFirstSearch(const int graph[QUESTION_GRAPH_VERTICES]
                                      [QUESTION_GRAPH_VERTICES],
                        int start, int order[QUESTION_GRAPH_VERTICES],
                        int &orderSize) {
  bool visited[QUESTION_GRAPH_VERTICES] = {};
  int queue[QUESTION_GRAPH_VERTICES];
  int front = 0;
  int back = 0;
  queue[back++] = start;
  visited[start] = true;

  while (front < back) {
    int vertex = queue[front++];
    order[orderSize++] = vertex;

    for (int neighbor = 0; neighbor < QUESTION_GRAPH_VERTICES; ++neighbor) {
      if (graph[vertex][neighbor] != 0 && !visited[neighbor]) {
        visited[neighbor] = true;
        queue[back++] = neighbor;
      }
    }
  }
}

bool isConnected(const int graph[QUESTION_GRAPH_VERTICES]
                               [QUESTION_GRAPH_VERTICES]) {
  bool visited[QUESTION_GRAPH_VERTICES] = {};
  int order[QUESTION_GRAPH_VERTICES];
  int orderSize = 0;
  depthFirstSearch(graph, 0, visited, order, orderSize);
  return orderSize == QUESTION_GRAPH_VERTICES;
}

bool findHamiltonianCycle(const int graph[QUESTION_GRAPH_VERTICES]
                                        [QUESTION_GRAPH_VERTICES],
                          int vertex, bool visited[QUESTION_GRAPH_VERTICES],
                          int path[QUESTION_GRAPH_VERTICES], int pathSize) {
  if (pathSize == QUESTION_GRAPH_VERTICES)
    return graph[vertex][path[0]] != 0;

  for (int neighbor = 0; neighbor < QUESTION_GRAPH_VERTICES; ++neighbor) {
    if (graph[vertex][neighbor] != 0 && !visited[neighbor]) {
      visited[neighbor] = true;
      path[pathSize] = neighbor;
      if (findHamiltonianCycle(graph, neighbor, visited, path, pathSize + 1))
        return true;
      visited[neighbor] = false;
    }
  }
  return false;
}

void printPath(const int path[QUESTION_GRAPH_VERTICES], int pathSize,
               bool closesCycle = false) {
  for (int index = 0; index < pathSize; ++index) {
    cout << path[index] + 1;
    if (index < pathSize - 1 || closesCycle)
      cout << " -> ";
  }
  if (closesCycle)
    cout << path[0] + 1;
  cout << endl;
}

void solveRegularGraph() {
  const int vertexCount = 7;
  const int degree = 3;
  const int degreeSum = vertexCount * degree;

  cout << "Jumlah derajat = " << vertexCount << " x " << degree << " = "
       << degreeSum << "." << endl;
  cout << "Jumlah derajat graf harus genap, jadi graf " << degree
       << "-teratur dengan " << vertexCount << " simpul tidak mungkin dibuat."
       << endl;
}

void solveDegreeTwoGraph() {
  const int edgeCount = 13;
  const int degree = 2;
  const int degreeSum = 2 * edgeCount;
  const int vertexCount = degreeSum / degree;

  cout << "Jumlah derajat = 2e = 2 x " << edgeCount << " = " << degreeSum
       << "." << endl;
  cout << "Karena setiap simpul berderajat " << degree << ", jumlah simpul = "
       << degreeSum << " / " << degree << " = " << vertexCount << "." << endl;
}

void solveEulerAndHamilton() {
  int degrees[QUESTION_GRAPH_VERTICES];
  graphDegrees(questionGraph, degrees);

  cout << "Derajat simpul 1 sampai 6: ";
  for (int vertex = 0; vertex < QUESTION_GRAPH_VERTICES; ++vertex) {
    cout << degrees[vertex];
    if (vertex < QUESTION_GRAPH_VERTICES - 1)
      cout << ", ";
  }
  cout << "." << endl;

  bool isEulerGraph = isConnected(questionGraph);
  for (int degree : degrees)
    isEulerGraph = isEulerGraph && degree % 2 == 0;

  if (isEulerGraph)
    cout << "Graf adalah graf Euler." << endl;
  else
    cout << "Graf bukan graf Euler karena tidak semua derajat simpul genap."
         << endl;

  bool visited[QUESTION_GRAPH_VERTICES] = {};
  int cycle[QUESTION_GRAPH_VERTICES] = {0};
  visited[0] = true;
  if (findHamiltonianCycle(questionGraph, 0, visited, cycle, 1)) {
    cout << "Graf Hamiltonian: ";
    printPath(cycle, QUESTION_GRAPH_VERTICES, true);
  } else {
    cout << "Graf bukan graf Hamiltonian." << endl;
  }
}

void solveDfsAndBfs() {
  const int start = 0;
  int dfsOrder[QUESTION_GRAPH_VERTICES];
  int bfsOrder[QUESTION_GRAPH_VERTICES];
  int dfsSize = 0;
  int bfsSize = 0;
  bool visited[QUESTION_GRAPH_VERTICES] = {};

  depthFirstSearch(questionGraph, start, visited, dfsOrder, dfsSize);
  breadthFirstSearch(questionGraph, start, bfsOrder, bfsSize);

  cout << "Mulai dari simpul " << start + 1
       << " dan memilih tetangga bernomor terkecil terlebih dahulu:" << endl;
  cout << "DFS: ";
  printPath(dfsOrder, dfsSize);
  cout << "BFS: ";
  printPath(bfsOrder, bfsSize);
}

void verifyQuestionGraph() {
  int degrees[QUESTION_GRAPH_VERTICES];
  int dfsOrder[QUESTION_GRAPH_VERTICES];
  int bfsOrder[QUESTION_GRAPH_VERTICES];
  int cycle[QUESTION_GRAPH_VERTICES] = {0};
  int dfsSize = 0;
  int bfsSize = 0;
  bool visited[QUESTION_GRAPH_VERTICES] = {};
  const int expectedDegrees[] = {5, 5, 4, 4, 3, 5};
  const int expectedDfs[] = {0, 1, 2, 3, 5, 4};
  const int expectedBfs[] = {0, 1, 2, 3, 4, 5};

  graphDegrees(questionGraph, degrees);
  depthFirstSearch(questionGraph, 0, visited, dfsOrder, dfsSize);
  breadthFirstSearch(questionGraph, 0, bfsOrder, bfsSize);

  for (int vertex = 0; vertex < QUESTION_GRAPH_VERTICES; ++vertex) {
    assert(degrees[vertex] == expectedDegrees[vertex]);
    assert(dfsOrder[vertex] == expectedDfs[vertex]);
    assert(bfsOrder[vertex] == expectedBfs[vertex]);
  }

  bool cycleVisited[QUESTION_GRAPH_VERTICES] = {};
  cycleVisited[0] = true;
  assert(findHamiltonianCycle(questionGraph, 0, cycleVisited, cycle, 1));
}

// Menjalankan solver yang sesuai dengan soal terakhir yang dipilih.
void solveQuestion(const Question *pinnedQuestion) {
  if (pinnedQuestion == nullptr) {
    cout << "Pilih soal terlebih dahulu melalui menu Lihat Soal." << endl;
    return;
  }

  showQuestionDetails(*pinnedQuestion);
  cout << endl << "=================== PECAHKAN SOAL ====================" << endl;

  switch (pinnedQuestion->number) {
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
  }

  cout << endl << "Tekan Enter untuk kembali ke Main Menu...";
  cin.get();
}

void mainMenu() {
  printSeparator();
  cout << "     Main Menu     " << endl;
  printSeparator();
  cout << "1. Lihat Soal" << endl;
  cout << "2. Pecahkan Soal Terpilih" << endl;
  cout << "3. Keluar" << endl << endl;
}

int main() {
  const Question *pinnedQuestion = nullptr;
  verifyQuestionGraph();

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
