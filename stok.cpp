/**
 * create by @Pijai
 **/

#include <iostream>
#include <string>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <vector>


std::string input_string(const std::string &pesan){
std::string input;
while(true){
        std::cout << pesan;
	std::getline(std::cin,input);
	if(!input.empty()){
	return input;
	}
}
}

std::string folder_bulan(){
std::vector<std::string> daftar_bulan =
{"januari","februari","maret","april","mei","juni","juli","agustus","september","oktober","november","desember"
};
bool valid = false;
while(true){
    std::string cekbulan = input_string("buka stok bulan : ");
    for(const auto &isi : daftar_bulan){
      if(cekbulan == isi){
        valid = true;
        return cekbulan;
      }
    }
    if(!valid){
        std::cout<<"tidak ditemukan\n";
      }
}

}

void buat_folder(){

	std::vector<std::string> folder_arr = {"bulan","pesanan"};
		for(const auto &cetak : folder_arr){
			if(!std::filesystem::exists(cetak)){
				std::cout << "Berhasil membuat -> " << cetak << std::endl;
				std::filesystem::create_directories(cetak);
			}
		}
}


//membuat pencarian nama file dengan user input
std::string cek_file(){

while(true){
std::string namafile = folder_bulan();

const std::string path_file = "bulan/" + namafile + ".csv";

    if(std::filesystem::exists(path_file)){
        std::cout << "membuka -> " << path_file << std::endl;
        return path_file;
    }
    else{std::cout << "file tidak ditemukan \n";}
}
}


int main(){
buat_folder();

std::vector<std::string> data;

	        std::string data_csv = cek_file();
	        
		std::ifstream file(data_csv);
		if(!file.is_open()){
		  std::cerr << "gagal membuka file -> " << data_csv << std::endl;
		  return 1;
		}
		std::string line;
		while(std::getline(file, line)){
			data.push_back(line);
		}

	        
		bool ketemu = false;
		while(!ketemu){
		std::string cari = input_string("Masukan kode : ");
		    for(const auto &kode : data){
			if(kode.find(cari) != std::string::npos){ // mencari sebagian
				std::cout << kode << std::endl;		
				ketemu = true;
			}
		    }
		        if(!ketemu){
		          std::cout << "part tidak ada\n";
		        }
		}


return 0;
}
