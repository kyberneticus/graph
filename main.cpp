#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

const int MAX_VERTICES = 10;
const string BORDER(42, '=');
const string DIVIDER(42, '-');

const string judulSoal[] = {"Graf Teratur", "Graf Berderajat Sama",
                            "Euler dan Hamilton", "DFS dan BFS",
                            "Paritas dan Havel-Hakimi"};
const string teksSoal[] = {
    "Apakah graf teratur dengan n simpul dan derajat r dapat dibuat?",
    "Berapakah jumlah simpul graf berderajat sama dari jumlah sisi dan derajat setiap simpul?",
    "Apakah graf pada adjacency matrix yang dimasukkan merupakan graf Euler dan Hamiltonian?",
    "Bagaimana hasil penelusuran adjacency matrix graf dari simpul awal dengan DFS dan BFS?",
    "Apakah barisan derajat yang dimasukkan dapat membentuk graf sederhana? (uji paritas dan Havel-Hakimi)",
};
const string gambarSoal[] = {"", "", "questions/question-3.jpeg",
                             "questions/question-3.jpeg", ""};
const int jumlahSoal = 5;

void dfs(int u, int v, int adj[][MAX_VERTICES], bool visited[]) {
  visited[u] = true;
  cout << u + 1 << " ";

  for (int n = 0; n < v; n++) {
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

    for (int n = 0; n < v; n++) {
      if (adj[cur][n] > 0 && !visited[n]) {
        visited[n] = true;
        queue[back++] = n;
      }
    }
  }
}

bool cariSiklus(int now, int awal, int jumlah, int v,
                int adj[][MAX_VERTICES], bool visited[]) {
  bool hasil;

  if (jumlah == v) {
    hasil = adj[now][awal] > 0;
  } else {
    hasil = false;
    for (int n = 0; n < v; n++) {
      if (adj[now][n] > 0 && visited[n] == false) {
        visited[n] = true;
        hasil = cariSiklus(n, awal, jumlah + 1, v, adj, visited);
        if (hasil)
          break;
        visited[n] = false;
      }
    }
  }
  return hasil;
}

bool cariLintasan(int now, int jumlah, int v, int adj[][MAX_VERTICES],
                  bool visited[]) {
  bool hasil;

  if (jumlah == v) {
    hasil = true;
  } else {
    hasil = false;
    for (int n = 0; n < v; n++) {
      if (adj[now][n] > 0 && visited[n] == false) {
        visited[n] = true;
        hasil = cariLintasan(n, jumlah + 1, v, adj, visited);
        if (hasil)
          break;
        visited[n] = false;
      }
    }
  }
  return hasil;
}

void cekEuler(int jenisGraf, int v, int adj[][MAX_VERTICES]) {
  int masuk[MAX_VERTICES] = {};
  int keluar[MAX_VERTICES] = {};

  for (int i = 0; i < v; i++) {
    for (int j = 0; j < v; j++) {
      keluar[i] += adj[i][j];
      masuk[i] += adj[j][i];
    }
  }

  int awal = -1;
  for (int i = 0; i < v && awal == -1; i++) {
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
      for (int j = 0; j < v; j++) {
        if ((adj[u][j] > 0 || adj[j][u] > 0) && !visited[j]) {
          visited[j] = true;
          queue[back++] = j;
        }
      }
    }

    for (int i = 0; i < v; i++) {
      if ((keluar[i] > 0 || masuk[i] > 0) && !visited[i]) {
        cout << "Graf tidak terhubung" << endl;
        return;
      }
    }
  }

  if (jenisGraf == 1) {
    int ganjil = 0;
    for (int i = 0; i < v; i++) {
      int derajat = keluar[i] + adj[i][i]; // loop dua ujung: +2
      if (derajat % 2 != 0)
        ganjil++;
    }

    if (ganjil == 0)
      cout << "Graf Euler" << endl;
    else if (ganjil == 2)
      cout << "Graf Semi Euler" << endl;
    else
      cout << "Bukan Graf Euler atau Semi Euler" << endl;
  } else {
    int plus = 0, minus = 0, lain = 0;
    for (int i = 0; i < v; i++) {
      int selisih = keluar[i] - masuk[i];
      if (selisih == 1)
        plus++;
      else if (selisih == -1)
        minus++;
      else if (selisih != 0)
        lain++;
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
    cout << "Input v (jumlah simpul, 1-10): ";
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
    cout << "M = matrix\n" << endl;
    cout << "Isi jumlah sisi dari simpul baris ke simpul kolom." << endl;
    cout << "Diagonal = loop; nilai lebih dari 1 = sisi ganda." << endl;

    bool matriksValid = true;
    for (int i = 0; i < v && matriksValid; i++) {
      cout << "\nBaris " << i + 1 << ':' << endl;
      for (int j = 0; j < v; j++) {
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
      for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
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
      for (int i = 0; i < v; i++) {
        for (int j = i + 1; j < v; j++) {
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
  for (int j = 0; j < v; j++)
    cout << setw(4) << j + 1;
  cout << "\n" << string(5 + 4 * v, '-') << endl;
  for (int i = 0; i < v; i++) {
    cout << setw(3) << i + 1 << " |";
    for (int j = 0; j < v; j++)
      cout << setw(4) << adj[i][j];
    cout << endl;
  }
}

void cekEulerAtauHamilton() {
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
    for (int i = 0; i < v; i++) {
      for (int j = 0; j < v; j++)
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
}

void cekDfsAtauBfs() {
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

    for (int i = 0; i < v; i++)
      visited[i] = false;
    cout << "BFS: ";
    bfs(u, v, adj, visited);
    cout << endl;
  } else {
    cout << "Simpul awal tidak valid" << endl;
  }
}

void cekParitasDanHavelHakimi() {
  cout << "\nSOLVER 5 - PARITAS DAN HAVEL-HAKIMI\n" << BORDER << endl;
  int n;
  while (true) {
    cout << "Input n (1-10): ";
    if (!(cin >> n)) {
      cin.clear();
      cin.ignore(1000, '\n');
      cout << "Jumlah simpul tidak valid" << endl;
      continue;
    }
    cin.ignore(1000, '\n');
    if (n >= 1 && n <= MAX_VERTICES)
      break;
    cout << "Jumlah simpul tidak valid" << endl;
  }

  int d[MAX_VERTICES] = {};
  while (true) {
    cout << "\nInput derajat tiap simpul:" << endl;
    bool derajatValid = true;
    for (int i = 0; i < n; i++) {
      cout << "  d[" << i + 1 << "] = ";
      if (!(cin >> d[i])) {
        cin.clear();
        cin.ignore(1000, '\n');
        d[i] = -1;
      }
      if (d[i] < 0)
        derajatValid = false;
    }
    cin.ignore(1000, '\n');
    if (derajatValid)
      break;
    cout << "Nilai derajat tidak valid" << endl;
  }

  int jumlahDerajat = 0;
  for (int i = 0; i < n; i++)
    jumlahDerajat += d[i];
  cout << "\njumlahDerajat = " << jumlahDerajat << endl;

  if (jumlahDerajat % 2 != 0) {
    cout << "Tidak dapat digambar, karena jumlah derajat semua "
            "simpulnya ganjil"
         << endl;
  } else {
    int sisa = n;
    bool bisaDigambar = true;

    while (true) {
      for (int i = 0; i < sisa; i++)
        for (int j = i + 1; j < sisa; j++)
          if (d[j] > d[i]) {
            int tukar = d[i];
            d[i] = d[j];
            d[j] = tukar;
          }

      cout << "Barisan:";
      for (int i = 0; i < sisa; i++)
        cout << " " << d[i];
      cout << endl;

      if (sisa == 0 || d[0] == 0)
        break;

      int k = d[0];
      for (int i = 0; i < sisa - 1; i++)
        d[i] = d[i + 1];
      sisa--;

      if (k > sisa) {
        bisaDigambar = false;
        cout << "Tidak dapat digambar sebagai graf sederhana, karena "
                "derajat melebihi jumlah simpul lain"
             << endl;
        break;
      }

      for (int i = 0; i < k; i++)
        d[i]--;

      bool adaNegatif = false;
      for (int i = 0; i < sisa; i++)
        if (d[i] < 0)
          adaNegatif = true;
      if (adaNegatif) {
        bisaDigambar = false;
        cout << "Tidak dapat digambar sebagai graf sederhana, karena "
                "derajat melebihi jumlah simpul lain"
             << endl;
        break;
      }
    }

    if (bisaDigambar)
      cout << "Dapat digambar sebagai graf sederhana" << endl;
  }
}

int main() {
  auto bacaTeksSoal = []() {
    string teks, line;
    while (getline(cin, line)) {
      if (line.find_first_not_of(" \t") == string::npos)
        break;
      teks += (teks.empty() ? "" : "\n") + line;
    }
    return teks;
  };
  auto pilihJenisSoal = []() {
    while (true) {
      cout << "\nJenis penyelesaian:" << endl;
      for (int i = 0; i < jumlahSoal; i++)
        cout << "  " << i + 1 << ". " << judulSoal[i] << endl;
      cout << "Input jenisSoal (1-5): ";

      int jenisSoal;
      if (!(cin >> jenisSoal)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Input harus berupa angka." << endl;
        continue;
      }
      cin.ignore(1000, '\n');
      if (jenisSoal >= 1 && jenisSoal <= jumlahSoal)
        return jenisSoal;
      cout << "Jenis soal tidak tersedia" << endl;
    }
  };
  auto tampilkanGambar = [](const string &path) {
    if (path.empty())
      return;
    cout << endl << "Gambar referensi:" << endl;
    if (system(("chafa --size=45x14 " + path).c_str()) != 0)
      cout << "Gambar tidak dapat ditampilkan. Install Chafa dengan: sudo apt "
              "install chafa"
           << endl;
  };
  string teksSoalAktif;
  int soalAktif = 0;

  while (true) {
    // ---------- INPUT SOAL ----------
    while (true) {
      cout << "\nINPUT SOAL\n" << BORDER << endl;
      cout << "Paste teks soal, akhiri dengan baris kosong:" << endl;

      string teks = bacaTeksSoal();
      if (teks.empty()) {
        cout << "Soal masih kosong, coba lagi." << endl;
        continue;
      }

      teksSoalAktif = teks;
      break;
    }

    // ---------- MAIN MENU ----------
    while (true) {
      cout << "\nMAIN MENU\n" << DIVIDER << endl;
      if (soalAktif > 0)
        cout << "Soal aktif : " << soalAktif << ". " << judulSoal[soalAktif - 1]
             << endl;
      else if (!teksSoalAktif.empty())
        cout << "Soal aktif : "
             << teksSoalAktif.substr(0, teksSoalAktif.find('\n')) << endl;
      else
        cout << "Soal aktif : Belum dipilih" << endl;
      cout << DIVIDER << endl;
      cout << "  1. Pecahkan Soal" << endl;
      cout << "  2. Daftar Soal" << endl;
      cout << "  3. Input Soal Baru" << endl;
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
      if (choice == 2) { // lihatSoal(soalAktif)
        while (true) {
          cout << "\nDAFTAR SOAL\n" << BORDER << endl;
          for (int i = 0; i < jumlahSoal; i++)
            cout << "  " << i + 1 << ". " << judulSoal[i]
                 << endl;
          cout << "\n  6. Input soal sendiri" << endl;
          cout << "  0. Kembali" << endl << DIVIDER << endl;
          cout << "Pilih soal [0-6]: ";

          int pilihan;
          if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Input harus berupa angka." << endl;
            continue;
          }
          cin.ignore(1000, '\n');

          if (pilihan == 0)
            break;
          if (pilihan == 6) {
            cout << "\nPaste teks soal, akhiri dengan baris kosong:" << endl;
            string teks = bacaTeksSoal();
            if (teks.empty()) {
              cout << "Soal masih kosong, coba lagi." << endl;
              continue;
            }
            teksSoalAktif = teks;
            soalAktif = pilihJenisSoal();
          } else if (pilihan >= 1 && pilihan <= jumlahSoal) {
            soalAktif = pilihan;
            teksSoalAktif = teksSoal[pilihan - 1];
          } else {
            cout << "Nomor soal tidak tersedia" << endl;
            continue;
          }

          cout << "\nSoal aktif: " << teksSoalAktif << endl;
          tampilkanGambar(gambarSoal[soalAktif - 1]);
          break;
        }
        continue;
      }
      if (choice == 3) { // Input Soal
        cout << "\nPaste teks soal, akhiri dengan baris kosong:" << endl;
        string teks = bacaTeksSoal();
        if (teks.empty()) {
          cout << "Soal masih kosong, coba lagi." << endl;
          continue;
        }
        teksSoalAktif = teks;
        soalAktif = 0;
        cout << "\nSoal aktif: " << teksSoalAktif << endl;
        continue;
      }
      if (choice != 1) {
        cout << "Pilihan tidak tersedia." << endl;
        continue;
      }

      // ---------- INPUT SOLVERNUMBER ----------
      while (true) {
        cout << "\nPECAHKAN SOAL\n" << BORDER << endl;
        for (int i = 0; i < jumlahSoal; i++)
          cout << "  " << i + 1 << ". " << judulSoal[i] << endl;
        cout << "\n  0. Kembali" << endl << DIVIDER << endl;
        cout << "Input solverNumber [0-5]: ";

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
        if (solverNumber < 1 || solverNumber > jumlahSoal) {
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
              cout << "Input n (jumlah simpul): ";
              while (!(cin >> n)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Input harus berupa angka." << endl
                     << "Input n (jumlah simpul): ";
              }
              cout << "Input r (derajat tiap simpul): ";
              while (!(cin >> r)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Input harus berupa angka." << endl << "Input r (derajat tiap simpul): ";
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
              cout << "Input e (jumlah sisi): ";
              while (!(cin >> e)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Input harus berupa angka." << endl << "Input e (jumlah sisi): ";
              }
              cout << "Input r (derajat tiap simpul): ";
              while (!(cin >> r)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Input harus berupa angka." << endl << "Input r (derajat tiap simpul): ";
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
            cekEulerAtauHamilton();
          } else if (solverNumber == 4) {
            cekDfsAtauBfs();
          } else {
            cekParitasDanHavelHakimi();
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
