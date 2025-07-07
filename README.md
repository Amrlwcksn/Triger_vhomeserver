# ⏰ Arduino Wake-Up Server Timer

Proyek ini adalah sistem otomatis untuk menyalakan server (misalnya Proxmox, NAS, atau home server) setiap hari **pukul 06:30** menggunakan **Arduino**, **RTC DS3231**, **OLED Display**, dan **relay**. Cukup sekali setting, dan server kamu akan bangun sendiri tiap pagi — no manual button needed 😎

## 🧠 Fitur
- ⏱️ Real-time clock (RTC) dengan DS3231
- ⚡ Relay aktif otomatis pada pukul 06:30:00
- 🔁 Trigger hanya sekali per hari, reset jam 06:31
- 🖥️ Tampilan jam dan status relay di OLED

## 🧰 Komponen yang Dibutuhkan
- Arduino Nano / Uno
- RTC DS3231 (I2C)
- OLED 128x64 (I2C, alamat 0x3C)
- Modul Relay (1 channel)
- Kabel jumper
- Server (yang bisa dinyalakan via tombol power eksternal)

## 📦 Wiring
| Komponen     | Arduino Pin |
|--------------|-------------|
| RTC SDA      | A4          |
| RTC SCL      | A5          |
| OLED SDA     | A4          |
| OLED SCL     | A5          |
| Relay IN     | D8          |
| Relay VCC    | 5V          |
| Relay GND    | GND         |

> 🧠 **Catatan**: Relay aktif LOW — aktif saat `digitalWrite(relayPin, LOW)`

+---------------------+
|   Wake Up Server!   |
|                     |
|      06:30:00       |
|                     |
| Relay: Triggered    |
+---------------------+
