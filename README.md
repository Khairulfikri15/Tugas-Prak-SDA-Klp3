TUGAS STRUKTUR DATA: implementasi Linked list, Stack, dan Queue
Anggota Kelompok 3:
1.	Muhammad Isra Aulia 2408107010006
2.	Andre Alfaridzi 2408107010011
3.	Khairul Fikri 2408107010032
4.	Annisa Rahma Fathia 2408107010027
5.	Illiza Khairamisa 2408107010017
   
DESKRIPSI SINGKAT PROGRAM:
Program ini merupakan program Sistem Antrean Bank Sederhana yang mengkombinasikan tiga struktur data yaitu Linked List, Queue, dan Stack agar system antrean nasabah berjalan lebih efisien. Queue digunakan untuk mengelola antrean nasabah. Stack digunakan untuk mencatat Riwayat transaksi dan fitur pembatalan. Fitur utama yang terdapat di dalam program ini mencakup fitur menambahkan nasabah ke antrean, memproses layanan nasabah, menampilkan antrean saat ini, menampilkan Riwayat layanan, membatalkan transaksi terakhir, serta fitur keluar untuk mengakhiri program.

INSTRUKSI KOMPILASI DAN CARA MENJALANKAN PROGRAM:
1.	Kompilasi program dengan menggunakan perintah gcc main.c -o main 
2.	Setelah dikompilasi, jalankan program dengan menggunakan perintah ./main 
3.	Saat program dijalankan, akan muncul tampilan menu yang tersedia. Kemudian pengguna diminta untuk memasukkan angka sesuai menu yang ingin dipilih.
4.	Jika pengguna memilih pilihan 1, program akan meminta pengguna untuk memasukkan nama nasabah dan memilih salah satu diantara tiga jenis layanan yang tersedia. Kemudian program akan menampilkan pesan konfirmasi.
5.	Jika pengguna memilih pilihan 2, program akan memproses nasabah pertama dalam antrean lalu dipindahkan ke Riwayat layanan.
6.	Jika pengguna memilih pilihan 3, program akan menampilkan daftar antrean nasabah saat ini dan layanan yang dipilih oleh nasabah.
7.	Jika pengguna memilih pilihan 4, program akan menampilkan daftar nasabah yang sudah dilayani dan waktu pelayanannya.
8.	Jika pengguna memilih pilihan 5, program akan membatalkan transaksi terakhir dan mengembalikannya ke antrean.
9.	Jika pengguna memilih pilihan 6, program akan berhenti dan menampilkan pesan penutup.

PENJELASAN STRUKTUR PROGRAM DAN IMPLEMENTASI STRUKTUR DATA:
Program ini memanfaatkan tiga struktur data utama, yaitu Linked List, Queue, dan Stack, untuk mengelola antrean dan mencatat riwayat layanan nasabah. Linked List digunakan sebagai dasar implementasi Queue dan Stack, di mana setiap nasabah direpresentasikan sebagai sebuah node yang memiliki atribut nama, jenis layanan, waktu layanan, serta pointer ke node berikutnya.
Queue digunakan untuk mengelola nasabah yang sedang menunggu layanan di bank. Implementasinya menggunakan linked list, dengan dua pointer utama, yaitu front (nasabah pertama) dan rear (nasabah terakhir). Untuk mengelola antrean, program menyediakan beberapa fungsi, seperti initQueue() untuk menginisialisasi antrean kosong, enqueue() untuk menambahkan nasabah ke antrean, dequeue() untuk menghapus nasabah yang sudah dilayani, serta displayQueue() untuk menampilkan antrean saat ini.
Selain antrean, program juga memiliki fitur Stack yang digunakan untuk mencatat riwayat layanan nasabah. Stack ini menyimpan nasabah yang telah diproses beserta waktu pelayanannya, menggunakan sistem Last In, First Out (LIFO). Struktur stack memiliki pointer top yang menunjuk ke transaksi terakhir yang masuk. Terdapat beberapa fungsi di dalamnya yaitu initStack() untuk inisialisasi, push() untuk menyimpan nasabah ke dalam riwayat layanan, serta pop() untuk mengambil kembali transaksi terakhir jika diperlukan.
Program ini juga menyediakan fitur Undo, yang memungkinkan transaksi terakhir dibatalkan dan nasabah dikembalikan ke antrean. Fitur ini dijalankan dengan kombinasi pop() dari stack untuk mengambil transaksi terakhir, lalu enqueue() untuk memasukkan nasabah tersebut kembali ke antrean. Dengan menggabungkan struktur data ini, program mampu mensimulasikan sistem antrean bank secara lebih nyata, di mana nasabah masuk secara berurutan, dilayani satu per satu, serta riwayat layanan dapat direkam atau dibatalkan jika diperlukan.
 
SCREENSHOT HASIL EKSEKUSI PROGRAM:

![Image](https://github.com/user-attachments/assets/167044ae-e088-48c7-a031-ddeb380e39f3)

![Image](https://github.com/user-attachments/assets/de531853-8ac5-4cfc-9d3a-8e6ca9a3194c)

![Image](https://github.com/user-attachments/assets/a34a58d6-5ed6-4b37-ae0f-75fe8ed05efe)

![Image](https://github.com/user-attachments/assets/6c6e145a-c5be-4229-8351-de75e5bda807)

![Image](https://github.com/user-attachments/assets/1d568617-bb61-4cb5-b397-504eebd15a9e)

![Image](https://github.com/user-attachments/assets/28a2a2bd-b085-47b1-8756-bda93035e14a)

![Image](https://github.com/user-attachments/assets/df954393-fbbb-4f77-8561-a1b02ffe78c5)

![Image](https://github.com/user-attachments/assets/2d160676-e2fe-45f8-a481-dae316a38c80)

KENDALA DAN SOLUSI SELAMA PENGEMBANGAN:
Kendala yang kami dapatkan selama pengembangan ialah kemungkinan adanya memory Leak (Kebocoran Memori). Penyebabnya karena saat melakukan malloc(), program mengalokasikan memori untuk struct Nasabah, tetapi tidak pernah melakukan free() setelah pengguna selesai diproses. Solusi untuk kendala tersebut adalah dengan membuat fungsi baru untuk membebaskan memori yang didalamnya terdapat fungsi free().
