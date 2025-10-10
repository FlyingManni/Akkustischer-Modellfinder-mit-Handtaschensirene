Modellfinder (Ansteuerung eines Taschenalarms)

Um verloren gegangene Modelle leichter wieder zu finden (besonders im Maisfeld), kam die Idee einen Taschenalarm zu verwenden. 
Um diesen gezielt auszulösen benötigt man eine entsprechende Ansteuerung, hier kommt der Tiny45 Modellfinder zum Zug.

Die Modellfinder wird über einen freien Empfängerkanal gesteuert. Hierbei gibt es 4 mögliche Zustände:

1.
Empfängersignal kleiner 1,4 ms -> schaltet den Alarm scharf und ist ausgeschaltet. Solange nicht mindestens einmalig ein Signal unter 1,4 ms
angelegen hat ist keine Alarmierung möglich. Wenn der Alarm „scharf“ und ausgeschaltet ist leuchtet die Status-LED dauerhaft.

2.
Signal zwischen 1,4 und 1,7 ms -> das sollte auch die Failsafe-Einstellung sein. Liegt dieses Signal an startet ein 1 minütiger Timer. Nach
Ablauf von 1 Minute wird Alarm ausgelöst. Während der Timer läuft blinkt die Status-LED schnell.

3.
Signal über 1,7 ms -> es wird sofort Alarm ausgelöst. Die Status-LED blinkt langsam.

4.
Kein Signal mehr vom Empfänger (Flugakku wurde vom Modell getrennt) -> Ablauf wie bei 2.

Anmerkung: Zustände 2 bis 4 sind erst möglich wenn zuvor einmal Zustand 1 hergestellt wurde, also ein Empfängersignal unter 1,4 ms.
