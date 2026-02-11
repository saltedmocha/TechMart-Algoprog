#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <ostream>
#include <string>

const int MAX_SIZE = 50;

struct Product {
    std::string product_code;
    std::string name;
    std::string category;
    double price;
    int stock;

    // Fungsi ini memastikan bahwa nilai pada struct
    // Adalah nilai defaultnya yaitu "" dan 0
    // Jika iya maka akhiri fungsi dan kemblikan true
    // Jika tidak false
    bool is_empty()
    {
	if (product_code.empty() && name.empty() && category.empty()
	    && price == 0 && stock == 0) {
	    return true;
	}

	return false;
    }
};

// Fungi ini digunakan untuk membersihkan / flushing cin
// Agar input selanjutnya tidak memiliki kesalahan / masalah
void reset_input()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


std::string to_lower_case(const std::string &str)
{
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(), tolower);
    return lower;
}

int get_int_input(const std::string &prompt, int min, int max)
{
    int value;
    while (true) {
	std::cout << prompt;
	if (std::cin >> value) {
	    if (value >= min && value <= max) {
		return value;
	    } else {
		std::cout << "Error: Input harus antara " << min << " dan "
			  << max << ".\n";
		reset_input();
		continue;
	    }
	} else {
	    std::cout << "Error: Tipe data salah. Masukkan angka yang valid.\n";
	    reset_input();
	    continue;
	}
    }
}

double get_double_input(const std::string &prompt, double min, double max)
{
    double value;
    while (true) {
	std::cout << prompt;
	if (std::cin >> value) {
	    if (value >= min && value <= max) {
		return value;
	    } else {
		std::cout << "Error: Input harus antara " << min << " dan "
			  << max << ".\n";
		reset_input();
		continue;
	    }
	} else {
	    std::cout << "Error: Tipe data salah. Masukkan angka yang valid.\n";
	    reset_input();
	    continue;
	}
    }
}

std::string get_text_input(const std::string &prompt)
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

// Pada kedua fungsi ini tidak perlu dilakukan cek data kosong atau tidak
// Semua data yang "kosong" akan memiliki nilai "" untuk string
// Dan 0 untuk int / double
// Saat dilakukan print / cout data yang kosong akan secara otomatis di filter
bool comp_stock_asc(Product *stock_a, Product *stock_b)
{
    return stock_a->stock < stock_b->stock;
}

bool comp_stock_des(Product *stock_a, Product *stock_b)
{
    return stock_a->stock > stock_b->stock;
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
    Product *m_product_init = new Product{};
    Product *m_products_data[MAX_SIZE] = {};

    std::string input_product_code()
    {
	std::string input;
	bool is_unique = false;

	while (is_unique == false) {
	    is_unique = true;
	    std::cout << "Kode produk: ";
	    std::cin >> input;

	    for (const Product *data : m_products_data) {
		if (input == data->product_code) {
		    std::cout << "Error: Kode produk telah digunakan"
			      << "\n";
		    is_unique = false;
		}
	    }
	}

	return input;
    }

    double total_value(int n)
    {
	double price = 0;
	double stock = 0;

	if (n == 0 && m_products_data[0]->is_empty()) {
	    return (price * stock);
	}

	if (n == 0 && !m_products_data[0]->is_empty()) {
	    price = m_products_data[n]->price;
	    stock = static_cast<double>(m_products_data[n]->stock);

	    return (price * stock);
	}

	if (!m_products_data[n]->is_empty()) {
	    price = m_products_data[n]->price;
	    stock = static_cast<double>(m_products_data[n]->stock);
	}


	return (price * stock) + total_value(n - 1);
    }

    bool is_fully_empty()
    {
	for (Product *data : m_products_data) {
	    if (!data->is_empty()) {
		return false;
	    }
	}

	return true;
    }

    void search_by_name(std::string name)
    {
	std::string name_lower = to_lower_case(name);
	bool is_found = false;

	std::cout << "Hasil pencarian: " << "\n";
	for (const Product *data : m_products_data) {
	    if (to_lower_case(data->name).find(name_lower)
		!= std::string::npos) {
		std::cout << "\n"
			  << "=============================================="
			  << "\n"
			  << "Kode produk: " << data->product_code << "\n"
			  << "Nama produk: " << data->name << "\n"
			  << "Kategori: " << data->category << "\n"
			  << "Harga: " << data->price << "\n"
			  << "Stock: " << data->stock << "\n"
			  << "=============================================="
			  << "\n";

		is_found = true;
	    }
	}

	if (!is_found) {
	    std::cout << "Data tidak ditemukan..." << "\n";
	    return;
	}
    }

    void search_by_id(std::string id)
    {
	std::string id_lower = to_lower_case(id);
	bool is_found = false;

	std::cout << "Hasil pencarian: " << "\n";
	for (const Product *data : m_products_data) {
	    if (to_lower_case(data->product_code).find(id_lower)
		!= std::string::npos) {
		std::cout << "\n"
			  << "=============================================="
			  << "\n"
			  << "Kode produk: " << data->product_code << "\n"
			  << "Nama produk: " << data->name << "\n"
			  << "Kategori: " << data->category << "\n"
			  << "Harga: " << data->price << "\n"
			  << "Stock: " << data->stock << "\n"
			  << "=============================================="
			  << "\n";

		is_found = true;
	    }
	}

	if (!is_found) {
	    std::cout << "Data tidak ditemukan..." << "\n";
	    return;
	}
    }

    void print_data(Product **arr_products_data)
    {
	int counter = 1;

	for (int i = 0; i < MAX_SIZE; i++) {
	    if (!arr_products_data[i]->is_empty()) {
		std::cout << "\n"
			  << "=============================================="
			  << "\n"
			  << "Kode produk: "
			  << arr_products_data[i]->product_code << "\n"
			  << "Nama produk: " << arr_products_data[i]->name
			  << "\n"
			  << "Kategori produk: "
			  << arr_products_data[i]->category << "\n"
			  << "Harga produk: " << arr_products_data[i]->price
			  << "\n"
			  << "Stock produk: " << arr_products_data[i]->stock
			  << "\n"
			  << "=============================================="
			  << "\n";
		if (counter == 10) {
		    std::cout << "Lanjutkan / Keluar"
			      << "\n"
			      << "1. Lanjutkan (10 items)"
			      << "\n"
			      << "2. Keluar"
			      << "\n";
		    int select = get_int_input("Pilihan: ", 1, 2);
		    switch (select) {
		    case 1: {
			counter = 1;
			continue;
		    }
		    case 2: {
			std::cout.flush();
			reset_input();
			return;
		    }
		    }
		}
		counter++;
	    }
	}
    }

  public:
    Inventaris()
    {
	for (int i = 0; i < MAX_SIZE; i++) {
	    m_products_data[i] = m_product_init;
	}
    }

    ~Inventaris()
    {
	delete m_product_init;
    }

    void menu1_add_product()
    {
	clrscrn();
	std::cout << "===== Tambah Produk Baru =====" << "\n";

	Product *product_data = new Product{};

	product_data->product_code = input_product_code();
	product_data->name = get_text_input("Nama produk: ");
	product_data->category = get_text_input("Kategori produk: ");
	product_data->price = get_double_input(
		"Harga produk: ", 0, std::numeric_limits<double>::max());
	product_data->stock = get_int_input("Stock produk: ", 0,
					    std::numeric_limits<int>::max());

	for (int i = 0; i < MAX_SIZE; i++) {
	    if (m_products_data[i]->is_empty()) {
		m_products_data[i] = product_data;
		std::cout << "Data berhasil ditambahkan."
			  << "\n";

		return;
	    }
	}
    }

    void menu2_view_product()
    {
	clrscrn();
	std::cout << "===== Produk TechMart =====" << "\n";
	// Jika kosong berikan peringatan lalu keluar
	if (is_fully_empty()) {
	    std::cout
		    << "Data produk kosong, tolong tambahkan data terlebih dahulu"
		    << std::endl;
	    return;
	}

	print_data(m_products_data);
    }

    void menu3_search_product()
    {
	clrscrn();
	std::cout << "===== Cari Produk =====" << "\n";

	// Jika kosong berikan peringatan lalu keluar
	if (is_fully_empty()) {
	    std::cout
		    << "Data produk kosong, tolong tambahkan data terlebih dahulu"
		    << std::endl;
	    return;
	}

	std::cout << "1. Menggunakan kode produk" << "\n"
		  << "2. Menggunakan nama" << "\n"
		  << "3. Keluar" << std::endl;
	int select = get_int_input("Pilihan: ", 1, 3);
	switch (select) {
	case 1: {
	    std::string name = get_text_input("Kode produk: ");
	    search_by_id(name);
	    break;
	}
	case 2: {
	    std::string id = get_text_input("Nama produk: ");
	    search_by_name(id);
	    break;
	}
	case 3: {
	    return;
	}
	}
    }

    void menu4_inventory_total()
    {
	clrscrn();
	std::cout << "===== Total Nilai Inventory =====" << "\n";

	// Jika kosong berikan peringatan lalu keluar
	if (is_fully_empty()) {
	    std::cout
		    << "Data produk kosong, tolong tambahkan data terlebih dahulu"
		    << std::endl;
	    return;
	}

	std::cout << "Nilai total inventory adalah: Rp. "
		  << total_value(MAX_SIZE - 1) << std::endl;
    }

    void menu5_low_in_stock()
    {
	clrscrn();
	std::cout << "===== Jumlah Produk Dengan Stock Sedikit ====="
		  << "\n";

	// Jika kosong berikan peringatan lalu keluar
	if (is_fully_empty()) {
	    std::cout
		    << "Data produk kosong, tolong tambahkan data terlebih dahulu"
		    << std::endl;
	    return;
	}

	for (Product *data : m_products_data) {
	    if (data->is_empty()) {
		continue;
	    }

	    if (data->stock <= 5) {
		std::cout << "\n"
			  << "=============================================="
			  << "\n"
			  << "Kode produk: " << data->product_code << "\n"
			  << "Nama produk: " << data->name << "\n"
			  << "Kategori: " << data->category << "\n"
			  << "Harga: " << data->price << "\n"
			  << "Stock: " << data->stock << "\n"
			  << "=============================================="
			  << "\n";
	    }
	}
    }

    void menu6_sort_by_stock()
    {
	clrscrn();
	std::cout << "===== Tampilkan Produk Berdasarkan Stock ====="
		  << "\n";

	// Jika kosong berikan peringatan lalu keluar
	if (is_fully_empty()) {
	    std::cout
		    << "Data produk kosong, tolong tambahkan data terlebih dahulu"
		    << std::endl;
	    return;
	}

	std::cout << "Pilih metode pengurutan" << "\n"
		  << "1. Urutkan dari kecil ke besar" << "\n"
		  << "2. Urutkan dari besar ke kecil" << "\n";
	int select = get_int_input("Pilihan: ", 1, 2);
	switch (select) {
	case 1: {
	    std::sort(std::begin(m_products_data), std::end(m_products_data),
		      comp_stock_asc);
	    print_data(m_products_data);
	}
	    return;
	case 2: {
	    std::sort(std::begin(m_products_data), std::end(m_products_data),
		      comp_stock_des);
	    print_data(m_products_data);
	}
	    return;
	}
    }

    void menu7_edit_product()
    {
	std::cout << "===== Edit Data Produk TechMart =====" << "\n";
	// Jika kosong berikan peringatan lalu keluar
	if (is_fully_empty()) {
	    std::cout
		    << "Data produk kosong, tolong tambahkan data terlebih dahulu"
		    << std::endl;
	    return;
	}

	std::string id = get_text_input("Masukan id produk: ");

	std::string id_lower = to_lower_case(id);
	bool is_found = false;

	for (Product *data : m_products_data) {
	    if (to_lower_case(data->product_code).find(id_lower)
		!= std::string::npos) {
		std::cout << "Data ditemukan." << "\n";
		is_found = true;
		Product *product_data = new Product{};

		product_data->name = get_text_input("Nama produk: ");
		product_data->category = get_text_input("Kategori produk: ");
		product_data->price =
			get_double_input("Harga produk: ", 0,
					 std::numeric_limits<double>::max());
		product_data->stock = get_int_input(
			"Stock produk: ", 0, std::numeric_limits<int>::max());

		data->name = product_data->name;
		data->category = product_data->category;
		data->price = product_data->price;
		data->stock = product_data->stock;

		std::cout << "Data berhasil diperbarui." << std::endl;
		return;
	    }
	}

	if (!is_found) {
	    std::cout << "Data tidak ditemukan..." << "\n";
	    return;
	}
    }

    void menu8_delete_data()
    {
	std::cout << "===== Edit Data Produk TechMart =====" << "\n";
	// Jika kosong berikan peringatan lalu keluar
	if (is_fully_empty()) {
	    std::cout
		    << "Data produk kosong, tolong tambahkan data terlebih dahulu"
		    << std::endl;
	    return;
	}

	std::string id = get_text_input("Masukan id produk: ");

	std::string id_lower = to_lower_case(id);
	bool is_found = false;

	for (Product *data : m_products_data) {
	    if (to_lower_case(data->product_code).find(id_lower)
		!= std::string::npos) {
		is_found = true;
		data->product_code = "";
		data->name = "";
		data->category = "";
		data->price = 0;
		data->stock = 0;

		std::cout << "Data berhasil dihapus." << std::endl;
		return;
	    }
	}

	if (!is_found) {
	    std::cout << "Data tidak ditemukan..." << "\n";
	    return;
	}
    }
};

int main(int argc, char *argv[])
{
    Inventaris *inventarisPtr = new Inventaris;

    while (true) {
	clrscrn();
	std::cout << "SISTEM MANAJEMEN INVENTARIS TECHMART"
		  << "\n"
		  << "===================================="
		  << "\n"
		  << "1. Tambah produk baru" << "\n"
		  << "2. Tampilkan semua produk" << "\n"
		  << "3. Cari produk" << "\n"
		  << "4. Hitung total nilai inventaris" << "\n"
		  << "5. Tampilkan produk dengan stock < 5"
		  << "\n"
		  << "6. Urutkan produk berdasarkan stock"
		  << "\n"
		  << "7. Edit stock produk" << "\n"
		  << "8. Hapus produk" << "\n"
		  << "9. Keluar" << std::endl;

	int menuInput = get_int_input("Pilih menu: ", 1, 9);
	// Karena nilai input sudah divalidasi maka default
	// tidak diperlukan
	switch (menuInput) {
	case 1: {
	    inventarisPtr->menu1_add_product();
	    break;
	}
	case 2: {
	    inventarisPtr->menu2_view_product();
	    break;
	}
	case 3: {
	    inventarisPtr->menu3_search_product();
	    break;
	}
	case 4: {
	    inventarisPtr->menu4_inventory_total();
	    break;
	}
	case 5: {
	    inventarisPtr->menu5_low_in_stock();
	    break;
	}
	case 6: {
	    inventarisPtr->menu6_sort_by_stock();
	    break;
	}
	case 7: {
	    inventarisPtr->menu7_edit_product();
	    break;
	}
	case 8: {
	    inventarisPtr->menu8_delete_data();
	    break;
	}
	case 9: {
	    delete inventarisPtr;
	    return 0;
	}
	}

	std::cout.flush();
	std::cout << "\n[Enter] Kembali ke menu...";
	reset_input();
	std::cin.get();
	clrscrn();
    }

    return 0;
}
