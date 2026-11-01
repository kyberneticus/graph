#include <cassert>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

const int MAX_VERTICES = 10;

struct Graph {
  bool directed;
  int vertexCount;
  int adjacency[MAX_VERTICES][MAX_VERTICES];
};

struct Question {
  int number;
  const char *title;
  const char *text;
  const char *imagePath;
};

const Question questions[] = {
    {1, "Graf Teratur",
     "Apakah graf teratur dengan n simpul dan derajat r dapat dibuat?",
     nullptr},
    {2, "Graf Berderajat Sama",
     "Berapakah jumlah simpul graf berderajat sama dari jumlah sisi dan "
     "derajat setiap simpul?",
     nullptr},
    {3, "Euler dan Hamilton",
     "Apakah graf pada adjacency matrix yang dimasukkan merupakan graf Euler "
     "dan Hamiltonian?",
     "questions/question-3.jpeg"},
    {4, "DFS dan BFS",
     "Bagaimana hasil penelusuran adjacency matrix graf dari simpul awal "
     "dengan DFS dan BFS?",
     "questions/question-3.jpeg"},
};

const int questionCount = sizeof(questions) / sizeof(questions[0]);

const string BORDER(42, '=');
const string DIVIDER(42, '-');

void printSection(const string &title) {
  cout << '\n' << title << "\n" << BORDER << endl;
}

void printHeader(const Question *pinnedQuestion) {
  cout << '\n' << BORDER << "\n               GRAPH SOLVER\n" << BORDER
       << "\n\nSoal aktif : ";
  if (pinnedQuestion == nullptr)
    cout << "Belum dipilih" << endl;
  else
    cout << pinnedQuestion->number << ". " << pinnedQuestion->title << endl;
}

void waitForEnter(const string &destination) {
  cout << "\n" << DIVIDER << "\n[ Tekan Enter untuk " << destination << " ]";
  cin.get();
  cout << endl;
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

int readNonNegativeInteger(const string &prompt) {
  int value;
  do {
    value = readInteger(prompt);
    if (value < 0)
      cout << "Masukkan bilangan tidak negatif." << endl;
  } while (value < 0);
  return value;
}

void showReferenceImage(const Question &question) {
  if (question.imagePath == nullptr)
    return;

  cout << endl << "Gambar referensi:" << endl;
  string command = "chafa --size=45x14 " + string(question.imagePath);
  if (system(command.c_str()) != 0)
    cout << "Gambar tidak dapat ditampilkan. Install Chafa dengan: sudo apt "
            "install chafa"
         << endl;
}

const Question *findQuestion(int number) {
  for (const Question &question : questions) {
    if (question.number == number)
      return &question;
  }
  return nullptr;
}

void showQuestionDetails(const Question &question) {
  printSection("SOAL " + to_string(question.number) + " - " + question.title);
  cout << '\n' << question.text << endl;
  showReferenceImage(question);
}

void showQuestion(const Question *&pinnedQuestion) {
  while (true) {
    printSection("DAFTAR SOAL");
    for (const Question &question : questions)
      cout << "  " << question.number << ". " << question.title << endl;
    cout << "\n  0. Kembali" << endl;
    cout << DIVIDER << endl;

    int selectedNumber = readInteger("Pilih soal [0-4]: ");
    if (selectedNumber == 0)
      return;

    const Question *selectedQuestion = findQuestion(selectedNumber);
    if (selectedQuestion == nullptr) {
      cout << "Nomor soal tidak tersedia." << endl << endl;
      continue;
    }

    pinnedQuestion = selectedQuestion;
    cout << "[OK] Soal " << pinnedQuestion->number << " berhasil dipilih."
         << endl;
    showQuestionDetails(*pinnedQuestion);
    return;
  }
}

void readGraph(Graph &graph) {
  printSection("INPUT GRAF");
  int type;
  do {
    cout << "  1. Graf tak berarah" << endl;
    cout << "  2. Graf berarah" << endl;
    type = readInteger("\nPilih jenis graf [1-2]: ");
    if (type != 1 && type != 2)
      cout << "Pilih 1 atau 2." << endl;
  } while (type != 1 && type != 2);

  graph.directed = type == 2;
  do {
    graph.vertexCount = readInteger("Jumlah simpul (1-10): ");
    if (graph.vertexCount < 1 || graph.vertexCount > MAX_VERTICES)
      cout << "Jumlah simpul harus antara 1 sampai 10." << endl;
  } while (graph.vertexCount < 1 || graph.vertexCount > MAX_VERTICES);

  printSection("ADJACENCY MATRIX");
  cout << "Isi jumlah sisi dari simpul baris ke simpul kolom." << endl;
  cout << "Diagonal = loop; nilai lebih dari 1 = sisi ganda." << endl;

  while (true) {
    for (int from = 0; from < graph.vertexCount; ++from) {
      cout << "\nBaris " << from + 1 << ':' << endl;
      for (int to = 0; to < graph.vertexCount; ++to) {
        graph.adjacency[from][to] = readNonNegativeInteger(
            "  M[" + to_string(from + 1) + "][" + to_string(to + 1) + "] = ");
      }
    }

    if (graph.directed)
      return;

    bool symmetric = true;
    for (int from = 0; from < graph.vertexCount; ++from) {
      for (int to = from + 1; to < graph.vertexCount; ++to) {
        if (graph.adjacency[from][to] != graph.adjacency[to][from])
          symmetric = false;
      }
    }

    if (symmetric)
      return;

    cout << "Untuk graf tak berarah, matrix harus simetris. Masukkan ulang "
            "matrix."
         << endl;
  }
}

void printMatrix(const Graph &graph) {
  printSection("ADJACENCY MATRIX");
  cout << setw(5) << "";
  for (int vertex = 0; vertex < graph.vertexCount; ++vertex)
    cout << setw(4) << vertex + 1;
  cout << "\n" << string(5 + 4 * graph.vertexCount, '-') << endl;

  for (int from = 0; from < graph.vertexCount; ++from) {
    cout << setw(3) << from + 1 << " |";
    for (int to = 0; to < graph.vertexCount; ++to)
      cout << setw(4) << graph.adjacency[from][to];
    cout << endl;
  }
}

bool hasEdge(const Graph &graph, int from, int to, bool reverse = false) {
  return reverse ? graph.adjacency[to][from] != 0
                 : graph.adjacency[from][to] != 0;
}

void depthFirstSearch(const Graph &graph, int vertex,
                      bool visited[MAX_VERTICES], int order[MAX_VERTICES],
                      int &orderSize, bool reverse = false) {
  visited[vertex] = true;
  order[orderSize++] = vertex;

  for (int neighbor = 0; neighbor < graph.vertexCount; ++neighbor) {
    if (hasEdge(graph, vertex, neighbor, reverse) && !visited[neighbor])
      depthFirstSearch(graph, neighbor, visited, order, orderSize, reverse);
  }
}

void breadthFirstSearch(const Graph &graph, int start, int order[MAX_VERTICES],
                        int &orderSize) {
  bool visited[MAX_VERTICES] = {};
  int queue[MAX_VERTICES];
  int front = 0;
  int back = 0;
  queue[back++] = start;
  visited[start] = true;

  while (front < back) {
    int vertex = queue[front++];
    order[orderSize++] = vertex;

    for (int neighbor = 0; neighbor < graph.vertexCount; ++neighbor) {
      if (hasEdge(graph, vertex, neighbor) && !visited[neighbor]) {
        visited[neighbor] = true;
        queue[back++] = neighbor;
      }
    }
  }
}

bool visitsAllNonIsolatedVertices(const Graph &graph,
                                  bool visited[MAX_VERTICES]) {
  for (int vertex = 0; vertex < graph.vertexCount; ++vertex) {
    bool hasIncidentEdge = false;
    for (int neighbor = 0; neighbor < graph.vertexCount; ++neighbor) {
      hasIncidentEdge = hasIncidentEdge ||
                        graph.adjacency[vertex][neighbor] != 0 ||
                        graph.adjacency[neighbor][vertex] != 0;
    }
    if (hasIncidentEdge && !visited[vertex])
      return false;
  }
  return true;
}

bool isEulerConnected(const Graph &graph) {
  int start = -1;
  for (int vertex = 0; vertex < graph.vertexCount && start == -1; ++vertex) {
    for (int neighbor = 0; neighbor < graph.vertexCount; ++neighbor) {
      if (graph.adjacency[vertex][neighbor] != 0 ||
          graph.adjacency[neighbor][vertex] != 0) {
        start = vertex;
        break;
      }
    }
  }

  if (start == -1)
    return true;

  bool visited[MAX_VERTICES] = {};
  int order[MAX_VERTICES];
  int orderSize = 0;
  depthFirstSearch(graph, start, visited, order, orderSize);
  if (!visitsAllNonIsolatedVertices(graph, visited))
    return false;

  if (!graph.directed)
    return true;

  for (int vertex = 0; vertex < graph.vertexCount; ++vertex)
    visited[vertex] = false;
  orderSize = 0;
  depthFirstSearch(graph, start, visited, order, orderSize, true);
  return visitsAllNonIsolatedVertices(graph, visited);
}

bool findHamiltonianCycle(const Graph &graph, int vertex,
                          bool visited[MAX_VERTICES], int path[MAX_VERTICES],
                          int pathSize) {
  if (pathSize == graph.vertexCount)
    return hasEdge(graph, vertex, path[0]);

  for (int neighbor = 0; neighbor < graph.vertexCount; ++neighbor) {
    if (hasEdge(graph, vertex, neighbor) && !visited[neighbor]) {
      visited[neighbor] = true;
      path[pathSize] = neighbor;
      if (findHamiltonianCycle(graph, neighbor, visited, path, pathSize + 1))
        return true;
      visited[neighbor] = false;
    }
  }
  return false;
}

void printPath(const int path[MAX_VERTICES], int pathSize,
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
  printSection("DATA GRAF");
  const int vertexCount = readNonNegativeInteger("Jumlah simpul (n): ");
  const int degree = readNonNegativeInteger("Derajat (r)      : ");
  const int degreeSum = vertexCount * degree;

  printSection("PENYELESAIAN");
  cout << "Jumlah derajat = n × r" << endl;
  cout << "               = " << vertexCount << " × " << degree << endl;
  cout << "               = " << degreeSum << endl << endl;
  if (degreeSum % 2 != 0)
    cout << "Karena jumlah derajat ganjil, graf tersebut tidak mungkin dibuat."
         << endl;
  else
    cout << "Jumlah derajat genap; syarat paritas terpenuhi." << endl;
}

void solveDegreeTwoGraph() {
  printSection("DATA GRAF");
  const int edgeCount = readNonNegativeInteger("Jumlah sisi (e): ");
  int degree;
  do {
    degree = readNonNegativeInteger("Derajat (r)    : ");
    if (degree == 0)
      cout << "Derajat harus lebih dari 0." << endl;
  } while (degree == 0);

  const int degreeSum = 2 * edgeCount;
  printSection("PENYELESAIAN");
  cout << "Jumlah derajat = 2e" << endl;
  cout << "               = 2 x " << edgeCount << endl;
  cout << "               = " << degreeSum << endl << endl;

  if (degreeSum % degree != 0) {
    cout << "Jumlah simpul = " << degreeSum << " / " << degree
         << " bukan bilangan bulat, jadi graf berderajat sama tidak mungkin "
            "dibuat."
         << endl;
    return;
  }

  cout << "Jumlah simpul = 2e / r" << endl;
  cout << "               = " << degreeSum << " / " << degree << endl;
  cout << "               = " << degreeSum / degree << endl;
}

void solveEulerAndHamilton() {
  Graph graph;
  readGraph(graph);
  printMatrix(graph);

  int inDegree[MAX_VERTICES] = {};
  int outDegree[MAX_VERTICES] = {};
  int degree[MAX_VERTICES] = {};
  for (int vertex = 0; vertex < graph.vertexCount; ++vertex) {
    for (int neighbor = 0; neighbor < graph.vertexCount; ++neighbor) {
      outDegree[vertex] += graph.adjacency[vertex][neighbor];
      inDegree[vertex] += graph.adjacency[neighbor][vertex];
      if (vertex == neighbor)
        degree[vertex] += 2 * graph.adjacency[vertex][neighbor];
      else
        degree[vertex] += graph.adjacency[vertex][neighbor];
    }
  }

  printSection("PENYELESAIAN");
  bool isEulerGraph = isEulerConnected(graph);
  if (graph.directed) {
    cout << "Derajat masuk dan keluar:" << endl;
    for (int vertex = 0; vertex < graph.vertexCount; ++vertex) {
      cout << "Simpul " << vertex + 1 << ": masuk = " << inDegree[vertex]
           << ", keluar = " << outDegree[vertex] << endl;
      isEulerGraph = isEulerGraph && inDegree[vertex] == outDegree[vertex];
    }
  } else {
    cout << "Derajat simpul:" << endl;
    for (int vertex = 0; vertex < graph.vertexCount; ++vertex) {
      cout << "Simpul " << vertex + 1 << ": " << degree[vertex] << endl;
      isEulerGraph = isEulerGraph && degree[vertex] % 2 == 0;
    }
  }

  cout << endl;
  if (isEulerGraph)
    cout << "Graf adalah graf Euler." << endl;
  else
    cout << "Graf bukan graf Euler." << endl;

  bool visited[MAX_VERTICES] = {};
  int cycle[MAX_VERTICES] = {};
  visited[0] = true;
  if (findHamiltonianCycle(graph, 0, visited, cycle, 1)) {
    cout << "Graf Hamiltonian: ";
    printPath(cycle, graph.vertexCount, true);
  } else {
    cout << "Graf bukan graf Hamiltonian." << endl;
  }
}

void solveDfsAndBfs() {
  Graph graph;
  readGraph(graph);
  printMatrix(graph);

  printSection("TITIK AWAL");
  int start;
  do {
    start =
        readInteger("Simpul awal [1-" + to_string(graph.vertexCount) + "]: ");
    if (start < 1 || start > graph.vertexCount)
      cout << "Simpul awal tidak tersedia." << endl;
  } while (start < 1 || start > graph.vertexCount);
  --start;

  int dfsOrder[MAX_VERTICES];
  int bfsOrder[MAX_VERTICES];
  int dfsSize = 0;
  int bfsSize = 0;
  bool visited[MAX_VERTICES] = {};
  depthFirstSearch(graph, start, visited, dfsOrder, dfsSize);
  breadthFirstSearch(graph, start, bfsOrder, bfsSize);

  printSection("PENYELESAIAN");
  cout << "DFS: ";
  printPath(dfsOrder, dfsSize);
  cout << "BFS: ";
  printPath(bfsOrder, bfsSize);
}

void verifyAlgorithms() {
  Graph graph = {false,
                 6,
                 {{0, 1, 1, 1, 1, 1},
                  {1, 0, 1, 1, 1, 1},
                  {1, 1, 0, 1, 0, 1},
                  {1, 1, 1, 0, 0, 1},
                  {1, 1, 0, 0, 0, 1},
                  {1, 1, 1, 1, 1, 0}}};
  const int expectedDfs[] = {0, 1, 2, 3, 5, 4};
  const int expectedBfs[] = {0, 1, 2, 3, 4, 5};
  bool visited[MAX_VERTICES] = {};
  int dfsOrder[MAX_VERTICES];
  int bfsOrder[MAX_VERTICES];
  int cycle[MAX_VERTICES] = {};
  int dfsSize = 0;
  int bfsSize = 0;

  depthFirstSearch(graph, 0, visited, dfsOrder, dfsSize);
  breadthFirstSearch(graph, 0, bfsOrder, bfsSize);
  for (int vertex = 0; vertex < graph.vertexCount; ++vertex) {
    assert(dfsOrder[vertex] == expectedDfs[vertex]);
    assert(bfsOrder[vertex] == expectedBfs[vertex]);
  }

  bool cycleVisited[MAX_VERTICES] = {};
  cycleVisited[0] = true;
  assert(isEulerConnected(graph));
  assert(findHamiltonianCycle(graph, 0, cycleVisited, cycle, 1));
}

void solveQuestion() {
  while (true) {
    printSection("PECAHKAN SOAL");
    for (const Question &question : questions)
      cout << "  " << question.number << ". " << question.title << endl;
    cout << "\n  0. Kembali" << endl;
    cout << DIVIDER << endl;

    int number = readInteger("Pilih solver [0-4]: ");
    if (number == 0)
      return;

    const Question *question = findQuestion(number);
    if (question == nullptr) {
      cout << "Nomor solver tidak tersedia." << endl;
      continue;
    }

    showQuestionDetails(*question);

    switch (question->number) {
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

    waitForEnter("kembali ke daftar solver");
  }
}

void mainMenu() {
  cout << "\nMAIN MENU\n" << DIVIDER << endl;
  cout << "  1. Lihat Soal" << endl;
  cout << "  2. Pecahkan Soal" << endl;
  cout << "  3. Keluar" << endl;
  cout << DIVIDER << endl;
}

int main() {
  const Question *pinnedQuestion = nullptr;
  verifyAlgorithms();

  while (true) {
    printHeader(pinnedQuestion);
    mainMenu();
    int choice = readInteger("Pilih menu [1-3]: ");

    switch (choice) {
    case 1:
      showQuestion(pinnedQuestion);
      break;
    case 2:
      solveQuestion();
      break;
    case 3:
      cout << "Program berhenti. Terima kasih!" << endl;
      return 0;
    default:
      cout << "Pilihan tidak tersedia." << endl;
    }
  }
}
