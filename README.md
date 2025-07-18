# FSM (Finite State Machine) Simulation Program

## Deskripsi Program

Program ini adalah simulasi sederhana Finite State Machine (FSM) menggunakan bahasa C++.  

### State yang Digunakan 

- INIT : State awal saat program dijalankan
- IDLE : State menunggu input dari pengguna 
- MOVEMENT : State simulasi gerak
- SHOOTING : State simulasi menembak
- CALCULATION : State simulasi melakukan perhitungan
- ERROR : State ketika terjadi error
- STOPPED : State ketika sistem berhenti

### Alur Kerja Program

1. **Memulai dari `INIT`**
   - Menampilkan pesan: `Initializing system...`.
   - Delay diset ke 1000 ms.
   - FSM berpindah ke state `IDLE`.

2. **State `IDLE` (Menunggu Input)**
   - Menampilkan pilihan proses:
     1. IDLE.
     2. MOVEMENT.
     3. SHOOTING.
     4. CALCULATION.
   - User memasukkan angka sesuai pilihan.

3. **State `MOVEMENT`**
   - Menampilkan pesan: `Moving...`.
   - Menambah `moveCount`.
   - Jika `moveCount >= 3` → pindah ke `SHOOTING`.
   - Jika belum → kembali ke `IDLE`.

4. **State `SHOOTING`**
   - Menampilkan pesan: `Shooting...`.
   - Mereset `moveCount`.
   - Kembali ke `IDLE`.

5. **State `CALCULATION`**
   - Menampilkan pesan: `Performing calculation...`.
   - Jika `moveCount = 0` → pindah ke `ERROR`.
   - Jika tidak → kembali ke `IDLE`.

6. **State `ERROR`**
   - Menampilkan pesan: `Error occurred, performing error handling...`.
   - Menambah `errorCount`.
   - Jika `errorCount > 3` → pindah ke `STOPPED`.
   - Jika tidak → kembali ke `IDLE`.

7. **State `STOPPED`**
   - Menampilkan pesan: `System stopped, shutting down...`.
   - Menghapus seluruh isi `stateHistory`.
   - Program berhenti.

## Fitur Utama
- Menyimpan riwayat state beserta waktu masuknya.
- Transisi otomatis antar state berdasarkan kondisi tertentu (misalnya: moveCount >= 3 otomatis pindah ke SHOOTING).
- Error handling: jika terjadi error lebih dari 3 kali, FSM akan masuk ke state STOPPED.

## Cara Menjalankan

1. Clone Repositori Ini 

```bash
git clone https://github.com/ValentinoDan/Tubes1_cakrai17.git
```
2. Inisiasi Program Menggunakan g++
```bash
g++ fsm.cpp main.cpp -o run
```
3. Muncul File program.exe Pada Folder Seperti Struktur Berikut
```bash
├── README.md
├── fsm.cpp
├── fsm.hpp
├── main.cpp
└── run.exe
```       
4. Jalankan Program
```bash
.\run.exe
```
