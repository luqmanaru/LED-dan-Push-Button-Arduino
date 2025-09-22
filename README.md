# LED-dan-Push-Button-Arduino

![License](https://img.shields.io/badge/License-MIT-green.svg)
![Arduino](https://img.shields.io/badge/Arduino-00979D?style=flat&logo=arduino&logoColor=white)
![IoT](https://img.shields.io/badge/IoT-Project-blue)

Proyek inovasi pengendalian LED dengan push button menggunakan Arduino Uno yang mengimplementasikan 8 mode LED berbeda dengan kontrol kecerahan.

## 🎯 Fitur Utama
- **8 Mode LED Berbeda**: Dari mode tunggal hingga kombinasi semua LED
- **Kontrol Kecerahan**: Menggunakan PWM untuk mengatur intensitas cahaya
- **2 Push Button**: Satu untuk mengubah mode, satu untuk mengubah kecerahan
- **Debouncing**: Mencegah pembacaan ganda saat tombol ditekan
- **Serial Monitor**: Menampilkan status mode dan kecerahan saat ini

## 🛠️ Komponen yang Dibutuhkan
| Komponen | Jumlah | Keterangan |
|----------|--------|------------|
| Arduino Uno | 1 | Mikrokontroler utama |
| LED Merah | 1 | Untuk output visual |
| LED Hijau | 1 | Untuk output visual |
| LED Biru | 1 | Untuk output visual |
| Push Button | 2 | Untuk input kontrol |
| Resistor 220Ω | 3 | Pembatas arus untuk LED |
| Kabel Jumper | 10 | Untuk koneksi |
| Breadboard | 1 | Tempat memasang komponen |

## 🔌 Skema Koneksi
| Komponen | Pin Arduino | Keterangan |
|----------|-------------|------------|
| LED Merah | Pin 9 (PWM) | Output dengan kontrol kecerahan |
| LED Hijau | Pin 10 (PWM) | Output dengan kontrol kecerahan |
| LED Biru | Pin 11 (PWM) | Output dengan kontrol kecerahan |
| Push Button Mode | Pin 2 | Input dengan pull-up internal |
| Push Button Brightness | Pin 3 | Input dengan pull-up internal |
| Semua Katoda LED | GND | Ground |

**Catatan**: 
- Hubungkan kaki panjang (anoda) LED ke pin Arduino melalui resistor
- Hubungkan kaki pendek (katoda) LED ke GND
- Push button menggunakan pull-up internal, sehingga tidak perlu resistor eksternal

## 📝 Kode Program
Kode program terdiri dari beberapa fungsi utama:

### Fungsi Setup
```cpp
void setup() {
  // Inisialisasi pin LED sebagai output
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  
  // Inisialisasi pin button sebagai input dengan pull-up internal
  pinMode(modeButton, INPUT_PULLUP);
  pinMode(brightnessButton, INPUT_PULLUP);
  
  // Inisialisasi serial monitor
  Serial.begin(9600);
  Serial.println("Sistem Kontrol LED dengan Push Button");
  Serial.println("Tombol 1: Ganti Mode | Tombol 2: Ganti Kecerahan");
}
```

### Fungsi Loop
```cpp
void loop() {
  // Baca status tombol
  int modeButtonState = digitalRead(modeButton);
  int brightnessButtonState = digitalRead(brightnessButton);
  
  // Cek tombol mode
  if (modeButtonState == LOW) {
    if ((millis() - lastDebounceTime) > debounceDelay) {
      changeMode();
    }
    lastDebounceTime = millis();
  }
  
  // Cek tombol kecerahan
  if (brightnessButtonState == LOW) {
    if ((millis() - lastDebounceTime) > debounceDelay) {
      changeBrightness();
    }
    lastDebounceTime = millis();
  }
  
  // Terapkan mode LED saat ini
  applyMode();
}
```

### Fungsi Perubahan Mode
```cpp
void changeMode() {
  currentMode = (currentMode + 1) % 8; // Mode 0-7
  Serial.print("Mode berubah ke: ");
  Serial.println(currentMode);
}
```

### Fungsi Perubahan Kecerahan
```cpp
void changeBrightness() {
  brightness += 32; // Tambah kecerahan (langkah 32)
  if (brightness > 255) {
    brightness = 0; // Reset ke 0 jika melebihi 255
  }
  Serial.print("Kecerahan berubah ke: ");
  Serial.println(brightness);
}
```

## 📊 Mode LED yang Tersedia
| Mode | Kombinasi LED | Deskripsi |
|------|--------------|-----------|
| Mode 0 | LED Merah | Hanya LED merah yang menyala |
| Mode 1 | LED Hijau | Hanya LED hijau yang menyala |
| Mode 2 | LED Biru | Hanya LED biru yang menyala |
| Mode 3 | LED Merah + Hijau | Kombinasi merah dan hijau (kuning) |
| Mode 4 | LED Merah + Biru | Kombinasi merah dan biru (ungu) |
| Mode 5 | LED Hijau + Biru | Kombinasi hijau dan biru (cyan) |
| Mode 6 | Semua LED | Semua LED menyala (putih) |
| Mode 7 | Mode Berkedip | Semua LED berkedip bersama |

## 📹 Video Demo
Lihat video demonstrasi proyek di: [https://youtu.be/8BTtadSQTd8](https://youtu.be/8BTtadSQTd8)

## 🔗 Link Project
Akses simulasi online di: [Wokwi Simulator](https://wokwi.com/projects/411802647797809153)

## 👨‍💻 Tim Pengembang
Proyek ini dikembangkan oleh **Kelompok 5** sebagai tugas kelompok mata kuliah Internet of Things:

| Nama | NIM | Peran |
|------|-----|------|
| Hanif Luqmanul Hakim | 2022310035 | Ketua, Programmer |
| Bagas Aditya | 2022310063 | Programmer |
| Dedy Wijaya | 2022310052 | Hardware Specialist |
| Muhammad Iqbal | 2022310089 | Documentation |
| Rayan Ikmal Amala | 2022310043 | Testing |

---
**luqmanaru**

Proyek ini dikembangkan sebagai tugas kelompok mata kuliah Internet of Things 1. Semua komponen dan kode dirancang untuk simulasi kontrol LED dengan push button menggunakan Arduino Uno.
