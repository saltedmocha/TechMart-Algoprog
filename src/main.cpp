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

// Karena std::string tidak memiliki to_lower
// Maka transform digunakan dengan menagaplikasikan
// fungsi + iterasi pada setiap character di string yang kemudian
// Akan disimpan kembali pada string awal
std::string to_lower_case(const std::string &str)
{
	std::string lower = str;
	std::transform(lower.begin(), lower.end(), lower.begin(), tolower);
	return lower;
}

// Lakukan looping hingga mendapatkan nilai yang sesuai
// Validasi dilakukan dengan cara memberi batas awal dan akhir
// Untuk memastikan bahwa input tidak keluar batas atau kosong
// Dengan ini input yang tidak sesuai akan terdeteksi
// Jika semua kriteria terpenuhi nilai akan direturn / kembalikan
//
// Prompt digunakan untuk memberikan penanda tempat menulis input sebagai
// berikut Pilihan: <input data>
int get_int_input(const std::string &prompt, int min, int max)
{
	int value;
	while (true) {
		std::cout << prompt;
		if (std::cin >> value) {
			if (value >= min && value <= max) {
				return value;
			} else {
				std::cout << "Error: Input harus antara " << min
					  << " dan " << max << ".\n";
				reset_input();
				continue;
			}
		} else {
			std::cout
				<< "Error: Tipe data salah. Masukkan angka yang valid.\n";
			reset_input();
			continue;
		}
	}
}

// Fungsi ini memiliki cara kerja dan logika yang sama dengan get_int_input
// Perbedaan hanya pada tipe yang diterima dan keluarkan
double get_double_input(const std::string &prompt, double min, double max)
{
	double value;
	while (true) {
		std::cout << prompt;
		if (std::cin >> value) {
			if (value >= min && value <= max) {
				return value;
			} else {
				std::cout << "Error: Input harus antara " << min
					  << " dan " << max << ".\n";
				reset_input();
				continue;
			}
		} else {
			std::cout
				<< "Error: Tipe data salah. Masukkan angka yang valid.\n";
			reset_input();
			continue;
		}
	}
}

// Fungsi ini memiliki logika yang hampir sama dengan get_int_input /
// get_double_input Perbedaannya adalah pada fungsi ini hanya validasi
// memastikan bahwa input tidak kosong
std::string get_text_input(const std::string &prompt)
{
	std::string input;

	while (true) {
		std::cout << prompt;
		getline(std::cin, input);
		if (!input.empty()) {
			return input;
		}

		std::cout << "Error: Text tidak boleh kosong." << "\n";
	}
}

// Pada kedua fungsi ini tidak perlu dilakukan cek data kosong atau tidak
// Semua data yang "kosong" akan memiliki nilai "" untuk string
// Dan 0 untuk int / double
// Saat dilakukan print / cout data yang kosong akan secara otomatis di filter
//
// Fungsi ini digunakan sebagai comparator / pembanding untuk sorting
// Dimana nilai dari pointer yang dibandingkkan akan diambil kemudian
// Nilai boolean akan dikembalikan / return
// Ascending: kecil -> besar
bool comp_stock_asc(Product *stock_a, Product *stock_b)
{
	return stock_a->stock < stock_b->stock;
}
// Descending: besar -> kecil
bool comp_stock_des(Product *stock_a, Product *stock_b)
{
	return stock_a->stock > stock_b->stock;
}

// Pembersih console / cmd tanpa bergantung
// Ke tipe atau jenis sistem operasi
// Pembersih console ini menggunakan ASCII escape code
// Untuk membersihkan layar console tanpa harus bergantung
// Pada command / library os specific seperti
// cls pada windows / clrscr yang merupakan bagian dari conio.h
// Dan clear pada unix/linux
// \033[2J akan membersihkan layar dari atas (J) ke bawah (2)
// \033[1;1H akan mengatur posisi cursor / pointer cmd ke posisi 1 / awal prompt
void clrscrn()
{
	std::cout << "\033[2J\033[1;1H";
}

class Inventaris
{
	// Fungsi dan properti yang tidak seharusnya diakses diluar namespace
	// Inventaris Akan disimpan pada private
      private:
	// m_product_init digunakan sebagai nilai initializer kepada
	// m_products_data Yang memiliki nilai default untuk setiap tipe yang
	// ada
	Product *m_product_init = new Product{};
	Product *m_products_data[MAX_SIZE] = {};

	bool is_exist(std::string input)
	{
		for (const Product *data : m_products_data) {
			if (input == data->product_code) {
				std::cout
					<< "Error: Kode produk telah digunakan"
					<< "\n";
				return true;
			}
		}
		return false;
	}

	// Fungsi ini berbeda dengan get_text_input
	// Karena fungsi ini memiliki tanggung jawab tambahan
	// Yaitu memastikan bahwa id pasti unik dan tidak dipakai ulang
	//
	// Sama seperti get_text_input loop akan dilakukan sampai hasil yang
	// diterima dikembalikan Tetapi akan ada nested loop yang bertugas untuk
	// mencari semua elemen non-default di m_products_data Dan menggunakan
	// if untuk memastikan bahwa nilai id belum digunakan
	std::string input_product_code()
	{
		std::string input;

		reset_input();
		while (true) {
			std::cout << "Kode produk: ";
			getline(std::cin, input);
			if (!input.empty() && !is_exist(input)) {
				return input;
			}

			std::cout << "Error: Kode produk tidak oleh kosong"
				  << "\n";
		}

		return input;
	}

	// Fungsi recursive ini dibuat dengan early exit
	// Ini memastikan bahwa jika nilai kosong maka akan langsung dikirimkan
	// 0 Ini ditujukan untuk menghindari segfault karena indexing
	//
	// Fungsi dimulai dari akhir array yaitu [MAX_SIZE - 1]
	// Kemudian jika pada index [0] memiliki nilai maka nilai tersebut akan
	// ditambahkan kemudian dikembalikan
	// Sedangkan bagian recursive terletak pada return utama dimana
	// nilai dari harga dan stock akan dikalikan kemudian ditambahkan nilai
	// hasil recursive dengan index - 1 hingga index mencapai 0 dimana
	// recursive akan diakhiri
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

	// Untuk memastikan bahwa tidak ada kesalahan karena sorting
	// Maka fungsi ini digunakan untuk mencari semua element array
	// Jika ada element yang tidak memiliki nilai default
	// Maka 'false' akan dikembalikan untuk menandakan bahwa ada nilai dan
	// array tidak kosong, jika kosong maka 'true' akan dikembalikan
	bool is_fully_empty()
	{
		for (Product *data : m_products_data) {
			if (!data->is_empty()) {
				return false;
			}
		}

		return true;
	}

	// Pencarian dimulai dengan membuat string menjadi lowercase
	// Kemudian method string find digunakan untuk mencari substring pada
	// string Jika tidak ditemukan maka std::stirng::npos akan dikembalikan
	// Oleh karena itu if menggunakan != std::string::npos
	//
	// std::string::npos adalah sebuah nilai constant yang digunakan method
	// string seperti find dimana jika tidak ditemukan maka
	// std::string::npos akan dikembalikan untuk menjadi penanda bahwa
	// string tidak ditemukan
	//
	// Jika string ditemukan maka data akan dipilih kemudian diprint / cout
	// dan flag is_found diset menjadi true untuk memberitahukan bahwa nilai
	// ditemukan
	void search_by_name(std::string name)
	{
		std::string name_lower = to_lower_case(name);
		bool is_found = false;

		std::cout << "Hasil pencarian: " << "\n";
		for (const Product *data : m_products_data) {
			if (to_lower_case(data->name).find(name_lower)
			    != std::string::npos) {
				std::cout
					<< "\n"
					<< "=============================================="
					<< "\n"
					<< "Kode produk: " << data->product_code
					<< "\n"
					<< "Nama produk: " << data->name << "\n"
					<< "Kategori: " << data->category
					<< "\n"
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

	// Fungsi ini memiliki tujuan dan logika yang sama dengan
	// 'search_by_name' Perbedaannya hanyalah fungsi ini menggunakan id
	void search_by_id(std::string id)
	{
		std::string id_lower = to_lower_case(id);
		bool is_found = false;

		std::cout << "Hasil pencarian: " << "\n";
		for (const Product *data : m_products_data) {
			if (to_lower_case(data->product_code).find(id_lower)
			    != std::string::npos) {
				std::cout
					<< "\n"
					<< "=============================================="
					<< "\n"
					<< "Kode produk: " << data->product_code
					<< "\n"
					<< "Nama produk: " << data->name << "\n"
					<< "Kategori: " << data->category
					<< "\n"
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

	// Fungsi ini digunakan untuk mempermudah printing / cout data
	// Fungsi ini akan menerima paremeter Array *Product
	// Yang kemudian akan dilakukan looping dan is_empty check dilakukan
	// untuk Melewati nilai default
	//
	// Looping akan memiliki counter hingga 10 dimana pada nilai ke 10
	// Looping akan dihentikan sementara untuk menanyakan apakah pengguna
	// ingin melanjutkan Ini ditujukan untuk menghindari printing yang
	// berlebihan
	void print_data(Product **arr_products_data)
	{
		int counter = 1;

		for (int i = 0; i < MAX_SIZE; i++) {
			if (!arr_products_data[i]->is_empty()) {
				std::cout
					<< "\n"
					<< "=============================================="
					<< "\n"
					<< "Kode produk: "
					<< arr_products_data[i]->product_code
					<< "\n"
					<< "Nama produk: "
					<< arr_products_data[i]->name << "\n"
					<< "Kategori produk: "
					<< arr_products_data[i]->category
					<< "\n"
					<< "Harga produk: "
					<< arr_products_data[i]->price << "\n"
					<< "Stock produk: "
					<< arr_products_data[i]->stock << "\n"
					<< "=============================================="
					<< "\n";
				if (counter == 10) {
					std::cout << "Lanjutkan / Keluar"
						  << "\n"
						  << "1. Lanjutkan (10 items)"
						  << "\n"
						  << "2. Keluar"
						  << "\n";
					int select = get_int_input(
						"Pilihan: ", 1, 2);
					switch (select) {
					case 1: {
						counter = 1;
						continue;
					}
					case 2: {
						std::cout.flush();
						return;
					}
					}
				}
				counter++;
			}
		}
	}

	// Pada bagian public akan disediakan constructor dan deconstructor
	// Pada public fungsi untuk menampilkan dan memproses menu akan
	// diberikan
      public:
	// Constructor dari class
	Inventaris()
	{
		// Initialisasi semua element pada 'm_products_data' menggunakan
		// nilai default
		for (int i = 0; i < MAX_SIZE; i++) {
			m_products_data[i] = m_product_init;
		}
	}

	// Deconstructor dari class
	// Pertama proses dealokasi akan dimulai dari struct yang memiliki nilai
	// Kemudian default value atau 'm_product_init' akan di dialokasi
	// Jika sudah keluar dari fungsi
	~Inventaris()
	{
		for (Product *data : m_products_data) {
			if (!data->is_empty())
				delete data;
		}

		delete m_product_init;
		return;
	}

	// Pada fungsi ini pointer untuk data produk akan diinisialisasi
	// Karena pointer ini akan disimpan pada array maka tidak dilakukan
	// delete Pada akhir fungsi, ini ditujukan untuk menghindari error
	// karena penghapusan pointer
	//
	// Input akan dilakukan untuk setiap input
	// Kemudian for loop akan mencari element yang memiliki nilai default
	// untuk di reassign / dipasangkan nlai
	void menu1_add_product()
	{
		clrscrn();
		std::cout << "===== Tambah Produk Baru =====" << "\n";

		Product *product_data = new Product{};

		product_data->product_code = input_product_code();
		product_data->name = get_text_input("Nama produk: ");
		product_data->category = get_text_input("Kategori produk: ");
		product_data->price =
			get_double_input("Harga produk: ", 0,
					 std::numeric_limits<double>::max());
		product_data->stock = get_int_input(
			"Stock produk: ", 0, std::numeric_limits<int>::max());

		for (int i = 0; i < MAX_SIZE; i++) {
			if (m_products_data[i]->is_empty()) {
				m_products_data[i] = product_data;
				std::cout << "Data berhasil ditambahkan."
					  << "\n";
				return;
			}
		}
	}

	// Fungsi ini akan mencari apakah nilai sudah di inisialisasi
	// atau memiliki nilai non-default
	// Jika iya maka akan dilakukan printing menggunakan 'print_data'
	// Jika tidak akan diberikan peringatan lalu keluar dari fungsi
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

	// Pada fungsi ini akan dilakukan check apakah ada nilai
	// Kemudian pengguna diberikan pilihan metode pencarian
	// Setelah dipilih pengguna akan diminta untuk memasukan data id atau
	// nama Yang kemudian akan dikirim ke fungsi 'search_by_id' /
	// 'search_by_name' Sesuai dengan pilihan Pengguna juga diberikan
	// pilihan untuk keluar jika ragu atau ingin mencari nilai data terlebih
	// dahulu
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
			reset_input();
			std::string name = get_text_input("Kode produk: ");
			search_by_id(name);
			break;
		}
		case 2: {
			reset_input();
			std::string id = get_text_input("Nama produk: ");
			search_by_name(id);
			break;
		}
		case 3: {
			return;
		}
		}
	}

	// Sama seperti fungsi menu lainnya cek nilai akan dilakukan terlebih
	// dahulu Kemudian jika ada nilai fungsi recursive akan dijalankan
	// dengan index MAX_SIZE - 1, ini untuk memastikan bahwa index tidak
	// keluar dari batas Karena index array dimulai dari 0
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

		std::cout << std::fixed << "Nilai total inventory adalah: Rp. "
			  << total_value(MAX_SIZE - 1) << std::endl;
	}

	// Fungsi ini bekerja dengan flow sebagai berikut
	// mulai -> check apakah ada nilai -> mulai looping
	// Jika ada nilai yang kosong / default maka nilai tersebut akan
	// dilewati Jika ditemukan nilai non-default maka nilai stock akan
	// dicheck Untuk mencari apakah stock sudah masuk ke <= 5 atau tidak
	// Jika iya maka nilai tersebut akan di print untuk memberitahukan
	// pengguna
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
				std::cout
					<< "\n"
					<< "=============================================="
					<< "\n"
					<< "Kode produk: " << data->product_code
					<< "\n"
					<< "Nama produk: " << data->name << "\n"
					<< "Kategori: " << data->category
					<< "\n"
					<< "Harga: " << data->price << "\n"
					<< "Stock: " << data->stock << "\n"
					<< "=============================================="
					<< "\n";
			}
		}
	}

	// Pertama dilakukan cek apakah nilai kosong, kemudian pengguna
	// diberikan pilihan untuk menggunan metode ascending(Kecil -> Besar)
	// dan Descending(Besar -> Kecil)
	// Kemudian akan dilakukan printing data setelah sorting
	// Fungsi ini memiliki efek samping pada ascending dimana nilai default
	// akan Berada di depan array, ini dikarenakan bagaimana cara nilai
	// kosong struct bekerja dimana nilai default dari stock adalah 0 yang
	// membuat nilai default Selalu menjadi nilai paling kecil
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
			std::sort(std::begin(m_products_data),
				  std::end(m_products_data), comp_stock_asc);
			print_data(m_products_data);
		}
			return;
		case 2: {
			std::sort(std::begin(m_products_data),
				  std::end(m_products_data), comp_stock_des);
			print_data(m_products_data);
		}
			return;
		}
	}

	// Fungsi ini adalah kombinasi dari menu tambah nilai dan cari dengan id
	// Pertama dilakukan cek inisialisasi, kemudian pengguna akan dimintai
	// id Jika sudah maka akan dilakukan pencarian jika nilai ditemukan maka
	// akan dimintai nilai baru Nilai yang bisa diperbarui hanyalah nama,
	// kategori, harga, dan stock Setelah itu akan dilakukan reassign pada
	// pointer data sesuai dengan field masing - masing Jika tidak ada maka
	// pengguna akan diberikan peringatan sebelum keluar dari fungsi
	//
	// Pointer product_data akan dihapus sebelum keluar dari fungsi
	// Ini dikarenakan pointer tersebut hanya bertugas sebagai temp variable
	// Jika tidak maka akan terjadi memory leak
	void menu7_edit_product()
	{
		clrscrn();
		std::cout << "===== Edit Data Produk TechMart =====" << "\n";
		// Jika kosong berikan peringatan lalu keluar
		if (is_fully_empty()) {
			std::cout
				<< "Data produk kosong, tolong tambahkan data terlebih dahulu"
				<< std::endl;
			return;
		}

		reset_input();
		std::string id = get_text_input("Masukan id produk: ");

		std::string id_lower = to_lower_case(id);
		bool is_found = false;
		Product *product_data = new Product{};

		for (Product *data : m_products_data) {
			if (to_lower_case(data->product_code).find(id_lower)
			    != std::string::npos) {
				std::cout << "Data ditemukan." << "\n";
				is_found = true;

				product_data->name =
					get_text_input("Nama produk: ");
				product_data->category =
					get_text_input("Kategori produk: ");
				product_data->price = get_double_input(
					"Harga produk: ", 0,
					std::numeric_limits<double>::max());
				product_data->stock = get_int_input(
					"Stock produk: ", 0,
					std::numeric_limits<int>::max());

				data->name = product_data->name;
				data->category = product_data->category;
				data->price = product_data->price;
				data->stock = product_data->stock;

				std::cout << "Data berhasil diperbarui."
					  << std::endl;
				delete product_data;
				return;
			}
		}

		if (!is_found) {
			std::cout << "Data tidak ditemukan..." << "\n";
			return;
		}
	}

	// Fungsi ini memiliki logika yang hampir sama dengan menu edit data
	// Perbedaan utama adalah pada fungsi ini pointer data akan diisi dengan
	// nilai default
	// Nilai ini akan menjadi penanda is_empty == true dan
	// akan dilewati jika dilakukan pencarian / pembacaan nilai
	void menu8_delete_data()
	{
		clrscrn();
		std::cout << "===== Edit Data Produk TechMart =====" << "\n";
		// Jika kosong berikan peringatan lalu keluar
		if (is_fully_empty()) {
			std::cout
				<< "Data produk kosong, tolong tambahkan data terlebih dahulu"
				<< std::endl;
			return;
		}

		reset_input();
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

				std::cout << "Data berhasil dihapus."
					  << std::endl;
				return;
			}
		}

		if (!is_found) {
			std::cout << "Data tidak ditemukan..." << "\n";
			return;
		}
	}
};

// Fungsi main bekerja dengan cara melakukan inisialisasi enum class
// Kemudian dengan constructor nilai array akan diinisialisasi
// Setelah itu looping akan dilakukan,
// pengguna akan dimintai pilihan menu yang ingin diakses
// Loop hanya bisa diakhiri menggunakan return pada pilihan ke 9
// Selain itu setelah keluar dari fungsi lainnya input dan output
// Akan dibersihkan untuk persiapan menu selanjutnya
int main()
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
		std::cin.get();
		reset_input();
		clrscrn();
	}

	return 0;
}
