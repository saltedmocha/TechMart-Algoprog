#include <cmath>
#include <cstddef>
#include <iostream>
#include <limits>
#include <ostream>
#include <string>

const int MAX_SIZE = 50;

struct Product {
	std::string productCode;
	std::string name;
	std::string category;
	double price;
	int stock;

	bool is_empty()
	{
		if (productCode.empty() && name.empty() && category.empty()
		    && price == 0 && stock == 0) {
			return true;
		}

		return false;
	}
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

std::string getStringInput(const std::string &prompt)
{
	std::string input;

	while (true) {
		std::cout << prompt;
		std::cin >> input;
		if (!input.empty()) {
			return input;
		}

		std::cout << "Error: Nama tidak boleh kosong." << "\n";
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
	Product *productsData[MAX_SIZE] = {};

      public:
	Inventaris()
	{
		for (size_t i = 0; i < MAX_SIZE; i++) {
			productsData[i] = productInit;
		}
	}

	std::string inputCode()
	{
		std::string input;
		bool isUnique = false;

		while (isUnique == false) {
			isUnique = true;
			std::cout << "Kode produk: ";
			std::cin >> input;

			for (const Product *data : productsData) {
				if (input == data->productCode) {
					std::cout
						<< "Error: Kode produk telah digunakan"
						<< "\n";
					isUnique = false;
				}
			}
		}

		return input;
	}

	double TotalValue(int n)
	{
		double price = 0;
		double stock = 0;

		if (!productsData[n]->is_empty()) {
			price = productsData[n]->price;
			stock = static_cast<double>(productsData[n]->stock);
		}

		if (n == 0 && !productsData[0]->is_empty()) {
			return (price * stock);
		}

		return (price * stock) + TotalValue(n - 1);
	}

	void searchByName(std::string name)
	{
	}

	void searchByID(std::string id)
	{
	}

	void menu1_AddProduct()
	{
		clrscrn();
		std::cout << "===== Tambah Produk Baru =====" << "\n";

		Product *productData = new Product{};

		productData->productCode = inputCode();
		productData->name = getStringInput("Nama produk: ");
		productData->category = getStringInput("Kategori produk: ");
		productData->price = getValidInput<double>(
			"Harga produk: ", 0,
			std::numeric_limits<double>::max());
		productData->stock = getValidInput<int>(
			"Stock produk: ", 0, std::numeric_limits<int>::max());

		for (size_t i = 0; i < MAX_SIZE; i++) {
			if (productsData[i]->is_empty()) {
				productsData[i] = productData;
				std::cout << "Data berhasil ditambahkan."
					  << "\n";

				return;
				break;
			}
		}
	}

	void menu2_tampilkanProduk()
	{
		clrscrn();

		std::cout << "===== Produk TechMart =====" << "\n";
		int counter = 1;
		for (Product *data : productsData) {
			if (!data->is_empty()) {
				std::cout
					<< "Kode produk: " << data->productCode
					<< "\n"
					<< "Nama produk: " << data->name << "\n"
					<< "Kategori produk: " << data->category
					<< "\n"
					<< "Harga produk: " << data->price
					<< "\n"
					<< "Stock produk: " << data->stock
					<< "\n\n";
				if (counter == 10) {
					std::cout << "Lanjutkan / Keluar"
						  << "\n"
						  << "1. Lanjutkan (10 items)"
						  << "\n"
						  << "2. Keluar"
						  << "\n";
					int select = getValidInput<int>(
						"Pilihan: ", 1, 2);
					switch (select) {
					case 1:
						counter = 1;
						continue;
					case 2:
						std::cout.flush();
						resetInput();
						return;
					}
				}
				counter++;
			}
		}
	}

	void menu3_SearchProduct()
	{
	}

	void menu4_TotalInventaris()
	{
		std::cout << "===== Total Nilai Inventory =====" << "\n";

		// Jika kosong berikan peringatan lalu keluar
		if (productsData[0] == productInit) {
			std::cout
				<< "Data produk kosong, tolong tambahkan data terlebih dahulu"
				<< std::endl;
			return;
		}

		int array_length = 0;
		for (Product *data : productsData) {
			if (!data->is_empty()) {
				array_length++;
			}
		}

		std::cout << "Nilai total inventory adalah: Rp. "
			  << TotalValue(array_length) << std::endl;
	}
};

int main(int argc, char *argv[])
{
	Inventaris *inventarisPtr = new Inventaris;

	while (true) {
		clrscrn();
		std::cout << "SISTEM MANAJEMEN INVENTARIS TECHMART" << "\n"
			  << "====================================" << "\n"
			  << "1. Tambah produk baru" << "\n"
			  << "2. Tampilkan semua produk" << "\n"
			  << "3. Cari produk" << "\n"
			  << "4. Hitung total nilai inventaris" << "\n"
			  << "5. Tampilkan produk dengan stock < 5" << "\n"
			  << "6. Urutkan produk berdasarkan stock" << "\n"
			  << "7. Edit stock produk" << "\n"
			  << "8. Hapus produk" << "\n"
			  << "9. Keluar" << std::endl;

		int menuInput = getValidInput<int>("Pilih menu: ", 1, 9);
		// Karena nilai input sudah divalidasi maka default tidak
		// diperlukan
		switch (menuInput) {
		case 1:
			inventarisPtr->menu1_AddProduct();
			break;
		case 2:
			inventarisPtr->menu2_tampilkanProduk();
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

		std::cout.flush();
		std::cout << "\n[Enter] Kembali ke menu...";
		resetInput();
		std::cin.get();
		clrscrn();
	}

	return 0;
}
