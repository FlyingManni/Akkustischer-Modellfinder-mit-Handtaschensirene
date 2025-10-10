# Modellfinder (Ansteuerung eines Taschenalarms)

Um verloren gegangene Modelle leichter wiederzufinden (besonders im Maisfeld), kam die Idee,  
einen Taschenalarm zu verwenden. Um diesen gezielt auszulösen, benötigt man eine entsprechende  
Ansteuerung — hier kommt der **Tiny45 Modellfinder** zum Einsatz.

---

## 🧭 Tiny45 Steuerung

Der Modellfinder wird über einen freien Empfängerkanal gesteuert.  
Hierbei gibt es vier mögliche Zustände:

1. **Empfängersignal kleiner 1,4 ms**  
   → Schaltet den Alarm scharf und ist ausgeschaltet.  
   Solange nicht mindestens einmalig ein Signal unter 1,4 ms anlag, ist keine Alarmierung möglich.  
   Wenn der Alarm *scharf* und ausgeschaltet ist, leuchtet die **Status-LED dauerhaft**.

2. **Signal zwischen 1,4 und 1,7 ms**  
   → Das sollte auch die *Failsafe-Einstellung* sein.  
   Liegt dieses Signal an, startet ein **1-minütiger Timer**.  
   Nach Ablauf von 1 Minute wird der Alarm ausgelöst.  
   Während der Timer läuft, **blinkt die Status-LED schnell**.

3. **Signal über 1,7 ms**  
   → Es wird **sofort Alarm ausgelöst**.  
   Die **Status-LED blinkt langsam**.

4. **Kein Signal mehr vom Empfänger**  
   (z. B. wenn der Flugakku vom Modell getrennt wurde)  
   → Ablauf wie bei Zustand 2.

> 🧩 **Anmerkung:**  
> Zustände 2 bis 4 sind erst möglich, wenn zuvor einmal Zustand 1 hergestellt wurde  
> (also ein Empfängersignal unter 1,4 ms anlag).

---

## 🔌 Anschlussübersicht

| Pin        | Funktion / Anschlussbeschreibung |
|-------------|---------------------------------|
| **RC-Signal** | An einen Empfängerausgang (Signal) anschließen |
| **RC-GND**    | Masse des Empfängerausgangs |
| **+UB**       | Betriebsspannung des Alarmgebers **max. 5V'' (nicht direkt an Batterie-Plus anschließen, sondern an die Buchse, über die der Alarm ursprünglich ausgelöst wird – sonst ist die Steuerung ständig aktiv und die Batterie bald leer) |
| **Alarm**     | Schaltet gegen Masse – hier wird die vorhandene Alarmschaltung angeschlossen |
| **GND**       | Direkt an den Minuspol der Batterie anschließen |

---

## 📦 Tiny45 Steuerung

![Beispiel-Alarmgeber] (https://github.com/FlyingManni/Akkustischer-Modellfinder-mit-Handtaschensirene/blob/main/beispiel_alarmgeber.jpg)

---

## 🎬 Demo-Video

<video src="https://github.com/FlyingManni/Akkustischer-Modellfinder-mit-Handtaschensirene/blob/main/Test.mp4" controls width="600"></video>


---

## 📘 Lizenz & Hinweise

Dieses Projekt ist für den privaten Gebrauch gedacht.  
Verwendung auf eigene Verantwortung.
