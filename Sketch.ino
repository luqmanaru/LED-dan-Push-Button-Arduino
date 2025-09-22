// Pin untuk LED
const int redLED = 9;
const int greenLED = 10;
const int blueLED = 11;

// Pin untuk push button
const int modeButton = 2;
const int brightnessButton = 3;

// Variabel untuk mode dan kecerahan
int currentMode = 0;
int brightness = 128; // Nilai default (0-255)

// Variabel untuk debouncing
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

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

void changeMode() {
  currentMode = (currentMode + 1) % 8; // Mode 0-7
  Serial.print("Mode berubah ke: ");
  Serial.println(currentMode);
}

void changeBrightness() {
  brightness += 32; // Tambah kecerahan (langkah 32)
  if (brightness > 255) {
    brightness = 0; // Reset ke 0 jika melebihi 255
  }
  Serial.print("Kecerahan berubah ke: ");
  Serial.println(brightness);
}

void applyMode() {
  // Matikan semua LED terlebih dahulu
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  
  // Terapkan mode sesuai dengan currentMode
  switch (currentMode) {
    case 0: // Mode 0: LED Merah
      analogWrite(redLED, brightness);
      break;
    case 1: // Mode 1: LED Hijau
      analogWrite(greenLED, brightness);
      break;
    case 2: // Mode 2: LED Biru
      analogWrite(blueLED, brightness);
      break;
    case 3: // Mode 3: LED Merah dan Hijau
      analogWrite(redLED, brightness);
      analogWrite(greenLED, brightness);
      break;
    case 4: // Mode 4: LED Merah dan Biru
      analogWrite(redLED, brightness);
      analogWrite(blueLED, brightness);
      break;
    case 5: // Mode 5: LED Hijau dan Biru
      analogWrite(greenLED, brightness);
      analogWrite(blueLED, brightness);
      break;
    case 6: // Mode 6: Semua LED
      analogWrite(redLED, brightness);
      analogWrite(greenLED, brightness);
      analogWrite(blueLED, brightness);
      break;
    case 7: // Mode 7: Mode Berkedip
      static unsigned long lastBlinkTime = 0;
      static bool blinkState = false;
      
      if (millis() - lastBlinkTime > 500) { // Kedip setiap 500ms
        blinkState = !blinkState;
        lastBlinkTime = millis();
        
        if (blinkState) {
          analogWrite(redLED, brightness);
          analogWrite(greenLED, brightness);
          analogWrite(blueLED, brightness);
        } else {
          digitalWrite(redLED, LOW);
          digitalWrite(greenLED, LOW);
          digitalWrite(blueLED, LOW);
        }
      }
      break;
  }
}
