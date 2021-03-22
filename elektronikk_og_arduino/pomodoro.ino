// Importerer biblioteket til LCD-skjermen
#include <LiquidCrystal.h>

// initaliserer biblioteket og forteller hvilke pins som brukes til kommunisering. 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// unsigned long brukes som regel på tidtaking ettersom dette er et tall som fort kan bli stort.
unsigned long startMillis = 0;
const unsigned long period = 1000; // ikke nødvendig å bruke long, men gjør liten forskjell i et så lite prosjekt 

// en status for om det er pause eller jobb
// starter med jobb
int runningState = 1;

// variabler for sekunder og minutter
unsigned int seconds = 0;
unsigned int minutes = 0;

// setter hvor lenge jobb og pause skal være
// under testing sto disse på 1, til vanlig vil de være 25 og 5. 
unsigned int workTime = 1;
unsigned int breakTime = 1;

void setup()
{
    // setter opp antall rader og kolonner på LCD-skjermen
    lcd.begin(16, 2);
    // velger hvilken rad og kolonne det skal skrives på 
    lcd.setCursor(0,0); 
    // starter med arbeid
    lcd.print("Time to work!");
}
void loop()
{
    // Antall millisekunder Arduinoen har kjørt siden oppstart/reset
    unsigned long currentMillis = millis();
    // sjekker om nok tid har passert til at noe skal skje. 
    // i dette tilfelle er en periode eller et intervall 1000 ms = 1s og den går dermed gjennom én gang i sekundet. 
    if (currentMillis - startMillis >= period)    
    {
        /*
        * setter at start-tid er lik gjeldende tid slik at det dermed tar én periode 
        * før neste gang forskjellen mellom disse to er én periode
        * Dersom denne ikke hadde blitt satt til gjeldene tid for hver gang ville 
        * koden bare blitt gjennomført én gang ettersom forskjellen alltid ville vært større enn én periode        
        */
        startMillis = currentMillis;
        // teller som øker hver runde (1000ms)
        seconds += 1;
        // øker minutt og nulstiller sekund for hver gang antall sekunder går til 60
        if (seconds > 59)
        {
            seconds = 0;
            minutes += 1;
        }
            // prints MM:SS
            // begynner å skrive på rad nr 2
            lcd.setCursor(0, 1);
            // setter en null foran dersom tallet er under 10 slik at det alltid 
            // vil skrives MM:SS og ikke vil variere mellom M:SS o.l.
            if (minutes < 10)
            {
                lcd.print("0");
            }
            lcd.print(minutes);
            lcd.print(":");
            if (seconds < 10)
            {
                lcd.print("0");
            }
            lcd.print(seconds);
        /*
         * Hvis (antall minutter overstiger eller er lik lengden det skal arbeides
         * og runningState er pause)
         * {
         *  nullstill minutter og sekunder, 
         *  endre RunningState til arbeid, 
         *  og print ut melding i øverste rad på skjermen
         * }
         */
        if (minutes >= workTime && runningState == 0)
            {
                seconds = 0; 
                minutes = 0;
                runningState = 1;
                lcd.setCursor(0, 0);
                lcd.print("Time to work!   ");
            }
        // samme som over, bare for annet tilfelle
        if (minutes >= breakTime && runningState == 1)
            {
              seconds = 0; 
              minutes = 0;
              runningState = 0;
              lcd.setCursor(0, 0);
              lcd.print("Time for a break");
            }
    }
}
