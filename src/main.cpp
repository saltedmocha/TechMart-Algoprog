#include <iostream>
#include <limits>
#include <string>

const int MAX_SIZE = 50;

struct Product {
	std::string productCode;
	std::string name;
	std::string category;
	double price;
	int stock;
};

void resetInput()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template <typename T> T getValidInput(const std::string &prompt, T min, T max)
{
	T value;
	while (true) {
		std::cout << prompt;
		if (std::cin >> value) {
			if (value >= min && value <= max) {
				return value;
			} else {
				std::cout << "Error: Input harus antara " << min
					  << " dan " << max << ".\n";
				resetInput();
				continue;
			}
		} else {
			std::cout
				<< "Error: Tipe data salah. Masukkan angka yang valid.\n";
			resetInput();
			continue;
		}
	}
}

// Pembersih console / cmd tanpa bergantung
// Ke tipe atau jenis sistem operasi
void clrscrn()
{
	std::cout << "\033[2J\033[1;1H";
}

class Inventaris
{
      private:
	Product *productInit = new Product{};
	Product *productsData[MAX_SIZE] = {productInit};

      public:
	double TotalValue(int n)
	{
		if (n == 0) {
			return 0;
		}

		double price = productsData[n]->price;
		double stock = static_cast<double>(productsData[n]->stock);

		return (price * stock) + TotalValue(n - 1);
	}

	void menu1_AddProduct()
	{
		clrscrn();
		std::cout << "=== Tambah Produk Baru ===" << "\n";

		Product productData = Product{};
	}

	void menu4_TotalInventaris()
	{
		// Jika kosong berikan peringatan lalu keluar
		if (productsData[0] == productInit) {
			std::cout
				<< "Data produk kosong, tolong tambahkan data terlebih dahulu"
				<< std::endl;
			return;
		}

		int array_length = 0;
		for (const Product *_ : productsData) {
			array_length++;
		}

		std::cout << "Nilai total inventory adalah: Rp. "
			  << TotalValue(array_length) << std::endl;
	}
};

int main(int argc, char *argv[])
{
	Inventaris *inventarisPtr = new Inventaris;

	while (true) {
		std::cout << "SISTEM MANAJEMEN INVENTARIS TECHMART" << "\n"
			  << "====================================" << "\n"
			  << "1. Tambah produk baru" << "\n"
			  << "2. Tampilkan semua produk" << "\n"
			  << "3. Cari produk (berdasarkan kode)" << "\n"
			  << "4. Hitung total nilai inventaris" << "\n"
			  << "5. Tampilkan produk dengan stok menipis" << "\n"
			  << "6. Urutkan produk berdasarkan stok" << "\n"
			  << "7. Edit stok produk" << "\n"
			  << "8. Hapus produk" << "\n"
			  << "9. Keluar" << std::endl;

		int menuInput = getValidInput<int>("Pilih menu: ", 1, 9);
		// Karena nilai input sudah divalidasi maka default tidak
		// diperlukan
		switch (menuInput) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			inventarisPtr->menu4_TotalInventaris();
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			return 0;
		}

		std::cout << "\n[Enter] Kembali ke menu...";
		resetInput();
		std::cin.get();
	}

	inventarisPtr->test_array();

	return 0;
}
