/**
   * Created by @Pijai
   */

  #include <iostream>
  #include <string>
  #include <filesystem>
  #include <sstream>
  #include <fstream>
  #include <vector>
  #include <algorithm> //untuk  mengubah huruf tolower atau toupper untuk menjadi huruf besar

  // Membuat folder "bulan" dan "pesanan" jika belum ada
  void buat_folder() {
      std::vector<std::string> folder_arr = {"bulan", "pesanan"};
      for (const auto &cetak : folder_arr) {
          if (!std::filesystem::exists(cetak)) {
              std::cout << "Berhasil membuat -> " << cetak << std::endl;
              std::filesystem::create_directories(cetak);
          }
      }
  }

  // Input string dengan validasi minimal 3 karakter
  std::string input_string(const std::string &pesan) {
      std::string input;
      do {
          std::cout << pesan;
          std::getline(std::cin, input);
          if (input.length() > 2) {
              return input;
          }
          std::cout << "Inputan tidak valid\n\n";
      } while (true);
  }

  // Mengecek file CSV berdasarkan input nama bulan
  std::string cek_file() {
      std::vector<std::string> daftar_bulan = {
          "januari", "februari", "maret", "april", "mei", "juni",
          "juli", "agustus", "september", "oktober", "november", "desember"
      };

      while (true) {
          std::string cekbulan = input_string("Buka stok bulan: ");
          std::transform(cekbulan.begin(), cekbulan.end(), cekbulan.begin(), ::tolower); // merubah ke huruf kecil semua
          for (const auto &isi : daftar_bulan) {
              if (cekbulan == isi) {
                  const std::string path_file = "bulan/" + cekbulan + ".csv";
                  if (std::filesystem::exists(path_file)) {
                      std::cout << "Membuka -> " << path_file << std::endl;
                      return path_file;
                  }
              }
          }
          std::cout << "File tidak ditemukan\n\n";
      }
  }


  int main() {
      buat_folder();

      std::vector<std::string> data;
      std::string data_csv = cek_file();

      std::ifstream file(data_csv);
      if (!file.is_open()) {
          std::cerr << "Gagal membuka file -> " << data_csv << std::endl;
          return 1;
      }

      std::string line;
      while (std::getline(file, line)) {
          data.push_back(line);
      }

      std::string cari;
      bool valid;

      do {
          cari = input_string("\nKetik kode/nama Part atau  'exit' untuk keluar\n input: ");
          std::transform(cari.begin(), cari.end(), cari.begin(), ::toupper);
          std::cout << "\n";
          if (cari =="EXIT") {
              std::cout << "Keluar\n";
              break;
          }
          
          valid = false;
          for (const auto &kode : data) {
              if (kode.find(cari) != std::string::npos) {
                  std::cout << kode << std::endl;
                  valid = true;
              }
          }

          if (!valid) {
              std::cout << "-\nPart tidak ada\n";
          }

      } while (true);

      return 0;
  }
