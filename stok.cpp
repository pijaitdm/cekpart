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
      std::string folder = "bulan";
          if (!std::filesystem::exists(folder)) {
              std::cout << "Berhasil membuat -> " << folder << std::endl;
              std::filesystem::create_directories(folder);
          }
      folder.clear();
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
      const std::vector<std::string> daftar_bulan = {
          "januari", "februari", "maret", "april", "mei", "juni",
          "juli", "agustus", "september", "oktober", "november", "desember"
      };
      
      //std::string path_file;
      while (true) {
          std::string cekbulan = input_string("Buka stok bulan: ");
          std::transform(cekbulan.begin(), cekbulan.end(), cekbulan.begin(), ::tolower); // merubah ke huruf kecil semua      
          if(cekbulan == "exit"){
            return "";
            }
      
          for (const auto &isi : daftar_bulan) {
              if (cekbulan == isi) {
                  const std::string path_file = "bulan/" + cekbulan + ".csv";
                  std::cout << "Membuka -> " << path_file << std::endl;
                  return path_file;
                  }
              }
               std::cout << "File tidak ditemukan\n\n";
          }
        }
        
    
    //logika proses pencarian
    bool cari_part(){
    std::string datacsv = cek_file();
       if (datacsv.empty()) {
        std::cout << "keluar\n";
        return 0;
       }
       
       
    std::ifstream file(datacsv);
    if (!file.is_open()) {
        std::cerr << "Gagal membuka file -> " << datacsv << std::endl;
        return 0;
    }
    datacsv.clear();
      
    std::string cari;
    do {
        std::cout << "\nKetik kode/nama Part : ";
        std::getline(std::cin, cari);
        std::transform(cari.begin(), cari.end(), cari.begin(), ::toupper);
          std::cout<< "-\n";
        
        if (cari == "EXIT") {
            return 0;
        }

        std::string line;
        bool ditemukan = false;
        file.clear(); // Bersihkan flag EOF
        file.seekg(0); // Kembali ke awal file

        while (std::getline(file, line)) {
            // Periksa baris saat ini untuk menemukan string
            if (line.find(cari) != std::string::npos) {
                std::cout << line << std::endl;
                ditemukan = true;
            }
        }
        
        if (!ditemukan) {
            std::cout << "-\nPart tidak ada\n";
        }
        
    } while (true);
    return 0;
  }    
      
int main() {
    buat_folder();
    std::cout << "        - CEK STOK PART -\n";
    std::cout << "-----------------------------------\n";
    std::cout << "      ketik exit untuk keluar !!\n";
    std::cout << "-----------------------------------\n";
    cari_part();
        
    return 0;
}
