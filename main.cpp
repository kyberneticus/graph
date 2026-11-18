#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

const int MAX_VERTICES = 10;
const string BORDER(42, '=');
const string DIVIDER(42, '-');

void dfs(int u, int v, int adj[][MAX_VERTICES], bool visited[]) {
  visited[u] = true;
  cout << u + 1 << " ";

  for (int n = 0; n < v; ++n) {
    if (adj[u][n] > 0 && !visited[n])
      dfs(n, v, adj, visited);
  }
}

void bfs(int u, int v, int adj[][MAX_VERTICES], bool visited[]) {
  int queue[MAX_VERTICES];
  int front = 0, back = 0;
  visited[u] = true;
  queue[back++] = u;

  while (front < back) {
    int cur = queue[front++];
    cout << cur + 1 << " ";

    for (int n = 0; n < v; ++n) {
      if (adj[cur][n] > 0 && !visited[n]) {
        visited[n] = true;
        queue[back++] = n;
      }
    }
  }
}

bool cariSiklus(int now, int awal, int jumlah, int v,
                int adj[][MAX_VERTICES], bool visited[]) {
  if (jumlah == v)
    return adj[now][awal] > 0;

  for (int n = 0; n < v; ++n) {
    if (adj[now][n] > 0 && visited[n] == false) {
      visited[n] = true;
      if (cariSiklus(n, awal, jumlah + 1, v, adj, visited))
        return true;
      visited[n] = false;
    }
  }
  return false;
}

bool cariLintasan(int now, int jumlah, int v, int adj[][MAX_VERTICES],
                  bool visited[]) {
  if (jumlah == v)
    return true;

  for (int n = 0; n < v; ++n) {
    if (adj[now][n] > 0 && visited[n] == false) {
      visited[n] = true;
      if (cariLintasan(n, jumlah + 1, v, adj, visited))
        return true;
      visited[n] = false;
    }
  }
  return false;
}

void cekEuler(int jenisGraf, int v, int adj[][MAX_VERTICES]) {
  int masuk[MAX_VERTICES] = {};
  int keluar[MAX_VERTICES] = {};

  for (int i = 0; i < v; ++i) {
    for (int j = 0; j < v; ++j) {
      keluar[i] += adj[i][j];
      masuk[i] += adj[j][i];
    }
  }

  int awal = -1;
  for (int i = 0; i < v && awal == -1; ++i) {
    if (keluar[i] > 0 || masuk[i] > 0)
      awal = i;
  }

  if (awal != -1) {
    bool visited[MAX_VERTICES] = {};
    int queue[MAX_VERTICES];
    int front = 0, back = 0;
    visited[awal] = true;
    queue[back++] = awal;

    while (front < back) {
      int u = queue[front++];
      for (int j = 0; j < v; ++j) {
        if ((adj[u][j] > 0 || adj[j][u] > 0) && !visited[j]) {
          visited[j] = true;
          queue[back++] = j;
        }
      }
    }

    for (int i = 0; i < v; ++i) {
      if ((keluar[i] > 0 || masuk[i] > 0) && !visited[i]) {
        cout << "Graf tidak terhubung" << endl;
        return;
      }
    }
  }

  if (jenisGraf == 1) {
    int ganjil = 0;
    for (int i = 0; i < v; ++i) {
      if (keluar[i] % 2 != 0)
        ++ganjil;
    }

    if (ganjil == 0)
      cout << "Graf Euler" << endl;
    else if (ganjil == 2)
      cout << "Graf Semi Euler" << endl;
    else
      cout << "Bukan Graf Euler atau Semi Euler" << endl;
  } else {
    int plus = 0, minus = 0, lain = 0;
    for (int i = 0; i < v; ++i) {
      int selisih = keluar[i] - masuk[i];
      if (selisih == 1)
        ++plus;
      else if (selisih == -1)
        ++minus;
      else if (selisih != 0)
        ++lain;
    }

    if (lain == 0 && plus == 0 && minus == 0)
      cout << "Graf Euler" << endl;
    else if (lain == 0 && plus == 1 && minus == 1)
      cout << "Graf Semi Euler" << endl;
    else
      cout << "Bukan Graf Euler atau Semi Euler" << endl;
  }
}

void bacaGraf(int jenisGraf, int &v, int adj[][MAX_VERTICES]) {
  while (true) {
    cout << "Input v (1-10): ";
    if (!(cin >> v)) {
      cin.clear();
      cin.ignore(1000, '\n');
      cout << "Jumlah simpul tidak valid" << endl;
      continue;
    }
    cin.ignore(1000, '\n');
    if (v < 1 || v > MAX_VERTICES) {
      cout << "Jumlah simpul tidak valid" << endl;
      continue;
    }
    break;
  }

  while (true) {
    cout << "\nADJACENCY MATRIX\n" << BORDER << endl;
    cout << "Isi jumlah sisi dari simpul baris ke simpul kolom." << endl;
    cout << "Diagonal = loop; nilai lebih dari 1 = sisi ganda." << endl;

    bool matriksValid = true;
    for (int i = 0; i < v && matriksValid; ++i) {
      cout << "\nBaris " << i + 1 << ':' << endl;
      for (int j = 0; j < v; ++j) {
        cout << "  M[" << i + 1 << "][" << j + 1 << "] = ";
        if (!(cin >> adj[i][j])) {
          cin.clear();
          cin.ignore(1000, '\n');
          matriksValid = false;
          break;
        }
      }
    }
    cin.ignore(1000, '\n');

    if (matriksValid) {
      for (int i = 0; i < v; ++i) {
        for (int j = 0; j < v; ++j) {
          if (adj[i][j] < 0)
            matriksValid = false;
        }
      }
    }
    if (!matriksValid) {
      cout << "Nilai matriks tidak valid" << endl;
      continue;
    }

    if (jenisGraf == 1) {
      for (int i = 0; i < v; ++i) {
        for (int j = i + 1; j < v; ++j) {
          if (adj[i][j] != adj[j][i])
            matriksValid = false;
        }
      }
      if (!matriksValid) {
        cout << "Matriks harus simetris" << endl;
        continue;
      }
    }
    break;
  }

  cout << "\nADJACENCY MATRIX\n" << BORDER << endl;
  cout << setw(5) << "";
  for (int j = 0; j < v; ++j)
    cout << setw(4) << j + 1;
  cout << "\n" << string(5 + 4 * v, '-') << endl;
  for (int i = 0; i < v; ++i) {
    cout << setw(3) << i + 1 << " |";
    for (int j = 0; j < v; ++j)
      cout << setw(4) << adj[i][j];
    cout << endl;
  }
}

int main() {
  const char *solvers[] = {"Graf Teratur", "Graf Berderajat Sama",
                           "Euler dan Hamilton", "DFS dan BFS"};
  string soal;

  while (true) {
    // ---------- INPUT SOAL (paste, boleh banyak baris) ----------
    cout << "\nINPUT SOAL\n" << BORDER << endl;
    cout << "Paste soal, akhiri dengan baris kosong:" << endl;

    string soalBaru, line;
    while (getline(cin, line)) {
      if (line.find_first_not_of(" \t") == string::npos)
        break;
      soalBaru += (soalBaru.empty() ? "" : "\n") + line;
    }

    if (!soalBaru.empty())
      soal = soalBaru;
    if (soal.empty()) {
      cout << "Soal masih kosong, coba lagi." << endl;
      continue;
    }

    // ---------- MAIN MENU ----------
    bool pilihSoalLain = false;
    while (!pilihSoalLain) {
      cout << "\nMAIN MENU\n" << DIVIDER << endl;
      cout << "Soal aktif : " << soal.substr(0, soal.find('\n')) << endl;
      cout << DIVIDER << endl;
      cout << "  1. Pecahkan Soal" << endl;
      cout << "  2. Lihat Soal" << endl;
      cout << "  3. Paste Soal Lain" << endl;
      cout << "  4. Keluar" << endl;
      cout << DIVIDER << endl << "Input choice: ";

      int choice;
      if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Input harus berupa angka." << endl;
        continue;
      }
      cin.ignore(1000, '\n');

      if (choice == 4) {
        cout << "Program berhenti. Terima kasih!" << endl;
        return 0;
      }
      if (choice == 2) {
        cout << "\nSOAL AKTIF\n" << BORDER << "\n\n" << soal << endl;
        continue;
      }
      if (choice == 3) {
        pilihSoalLain = true;
        continue;
      }
      if (choice != 1) {
        cout << "Pilihan tidak tersedia." << endl;
        continue;
      }

      // ---------- INPUT SOLVERNUMBER ----------
      while (true) {
        cout << "\nPECAHKAN SOAL\n" << BORDER << endl;
        for (int i = 0; i < 4; ++i)
          cout << "  " << i + 1 << ". " << solvers[i] << endl;
        cout << "\n  0. Kembali" << endl << DIVIDER << endl;
        cout << "Input solverNumber [0-4]: ";

        int solverNumber;
        if (!(cin >> solverNumber)) {
          cin.clear();
          cin.ignore(1000, '\n');
          cout << "Input harus berupa angka." << endl;
          continue;
        }
        cin.ignore(1000, '\n');

        if (solverNumber == 0)
          break;
        if (solverNumber < 1 || solverNumber > 4) {
          cout << "Nomor solver tidak tersedia." << endl;
          continue;
        }

        bool tryAgain = false;
        do {
          tryAgain = false;
          char tryAgainInput;

          if (solverNumber == 1) {
            cout << "\nSOLVER 1 - GRAF TERATUR\n" << BORDER << endl;
            int n, r;
            while (true) {
              cout << "Input n: ";
              while (!(cin >> n)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Input harus berupa angka." << endl << "Input n: ";
              }
              cout << "Input r: ";
              while (!(cin >> r)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Input harus berupa angka." << endl << "Input r: ";
              }
              cin.ignore(1000, '\n');
              if (n < 0 || r < 0)
                cout << "n dan r tidak boleh negatif." << endl;
              else
                break;
            }

            const int jumlahDerajat = n * r;
            cout << "\njumlahDerajat = n * r = " << n << " * " << r << " = "
                 << jumlahDerajat << endl;
            if (jumlahDerajat % 2 == 0) {
              const int jumlahSisi = (n * r) / 2;
              cout << "jumlahSisi = (n * r) / 2 = " << jumlahSisi << endl;
              cout << "Dapat digambar, jumlah sisi = " << jumlahSisi << endl;
            } else {
              cout << "Tidak dapat digambar, karena jumlah derajat semua "
                      "simpulnya ganjil"
                   << endl;
            }
          } else if (solverNumber == 2) {
            cout << "\nSOLVER 2 - GRAF BERDERAJAT SAMA\n" << BORDER << endl;
            int e, r;
            while (true) {
              cout << "Input e: ";
              while (!(cin >> e)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Input harus berupa angka." << endl << "Input e: ";
              }
              cout << "Input r: ";
              while (!(cin >> r)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Input harus berupa angka." << endl << "Input r: ";
              }
              cin.ignore(1000, '\n');
              if (r > 0)
                break;
              cout << "r harus lebih dari 0." << endl;
            }

            const int jumlahDerajat = 2 * e;
            cout << "\njumlahDerajat = 2 * e = 2 * " << e << " = " << jumlahDerajat
                 << endl;
            if (jumlahDerajat % r == 0) {
              cout << "n = jumlahDerajat / r = " << jumlahDerajat << " / " << r
                   << " = " << jumlahDerajat / r << endl;
              cout << "Jumlah simpul graf = " << jumlahDerajat / r << endl;
            } else {
              cout << "Graf tidak dapat dibentuk, karena jumlah simpul bukan "
                      "bilangan bulat"
                   << endl;
            }
          } else if (solverNumber == 3) {
            cout << "\nSOLVER 3 - EULER DAN HAMILTON\n" << BORDER << endl;
            int jenisGraf;
            while (true) {
              cout << "Input jenisGraf (1 = tidak berarah, 2 = berarah): ";
              if (!(cin >> jenisGraf)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Input harus berupa angka." << endl;
                continue;
              }
              cin.ignore(1000, '\n');
              if (jenisGraf == 1 || jenisGraf == 2)
                break;
            }

            int v = 0;
            int adj[MAX_VERTICES][MAX_VERTICES] = {};
            bacaGraf(jenisGraf, v, adj);
            cekEuler(jenisGraf, v, adj);

            bool adaSiklus = false;
            bool visited[MAX_VERTICES] = {};
            if (v >= 3) {
              visited[0] = true;
              adaSiklus = cariSiklus(0, 0, 1, v, adj, visited);
            }

            if (adaSiklus) {
              cout << "Graf Hamilton" << endl;
            } else {
              bool adaLintasan = false;
              for (int i = 0; i < v; ++i) {
                for (int j = 0; j < v; ++j)
                  visited[j] = false;
                visited[i] = true;
                if (cariLintasan(i, 1, v, adj, visited))
                  adaLintasan = true;
              }

              if (adaLintasan)
                cout << "Graf Semi Hamilton" << endl;
              else
                cout << "Bukan Graf Hamilton atau Semi Hamilton" << endl;
            }
          } else {
            cout << "\nSOLVER 4 - DFS DAN BFS\n" << BORDER << endl;
            int v = 0;
            int adj[MAX_VERTICES][MAX_VERTICES] = {};
            bacaGraf(1, v, adj);

            int u;
            cout << "Input u (1 sampai " << v << "): ";
            if (!(cin >> u)) {
              cin.clear();
              cin.ignore(1000, '\n');
              u = 0;
            }
            cin.ignore(1000, '\n');

            if (u >= 1 && u <= v) {
              --u;
              bool visited[MAX_VERTICES] = {};
              cout << "\nDFS: ";
              dfs(u, v, adj, visited);
              cout << endl;

              for (int i = 0; i < v; ++i)
                visited[i] = false;
              cout << "BFS: ";
              bfs(u, v, adj, visited);
              cout << endl;
            } else {
              cout << "Simpul awal tidak valid" << endl;
            }
          }

          cout << "\nInput tryAgain ( Y / n ): ";
          cin >> tryAgainInput;
          cin.ignore(1000, '\n');
          tryAgain = tryAgainInput == 'Y' || tryAgainInput == 'y';
        } while (tryAgain);
        break;
      }
    }
  }
}
