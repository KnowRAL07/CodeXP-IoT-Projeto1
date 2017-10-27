// Inclusão da biblioteca do sensor
// Essa biblioteca não vem por padrão com o arduino e 
// precisa ser instalada pelo gerenciador de bibliotecas
#include <Ultrasonic.h>
#include <LiquidCrystal.h>

const int rs = 8, en = 10, d4 = 6, d5 = 7, d6 = 5, d7 = 2;
const int ledvermelho = 11;
const int alerta = 3;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// Inicializa o objeto do sensor ultrasônico
// Usando as portas 12 e 13 para trigger e echo
Ultrasonic ultrasonic(12, 13);

void bebida_que_pisca_perto (){
  
  noTone(alerta);
  digitalWrite(ledvermelho, LOW);  
  delay(100);
  lcd.noDisplay();
  //delay(100);
  tone(alerta,1000);
  digitalWrite(ledvermelho, HIGH);
  delay(100);
  lcd.display();
 // delay(100);
  lcd.clear();
  lcd.print("esta perto!");

}

void bebida_que_pisca_muito_perto (){
    noTone(alerta);
    digitalWrite(ledvermelho, LOW); 
    delay(10);
    lcd.noDisplay();
   // delay(50);
    tone(alerta,2000);
    digitalWrite(ledvermelho, HIGH);
    delay(10);
    lcd.display();
    //delay(50);
    lcd.clear();
    lcd.print("esta muito perto!"); 
}

void bebida_que_pisca_fudeu (){
  
  tone(alerta,3000);
  digitalWrite(ledvermelho, HIGH); 
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Vaga ocupada");
  lcd.setCursor(4,1);
  lcd.print("fudeu!!!");
  //lcd.scrollDisplayRight();
  lcd.noDisplay();
  delay(299);
  lcd.display();
  delay(299);   
}

void setup() {
  // Inicializa a porta Serial
  Serial.begin(9600);
  pinMode(ledvermelho, OUTPUT);
  pinMode(alerta, OUTPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Sistema de Vaga!");
  lcd.print(line2.substring("TESTE"));
}

void loop() {
  // Lê o valor do sensor
  int distancia = ultrasonic.distanceRead();

  // Escreve o valor da distância no painel Serial
 Serial.print("Distance in CM: ");
  Serial.println(distancia);
  delay(1000);
  
  if (distancia < 10 && distancia >= 7) {
      bebida_que_pisca_perto();
    }
    else 
       if (distancia < 7 && distancia >=4 ){
       bebida_que_pisca_muito_perto();
       }
       else
       if (distancia < 4 ) {        
            bebida_que_pisca_fudeu();
        } 
       else {
   digitalWrite(ledvermelho, LOW);
   noTone(alerta);
   lcd.clear();
   for (int posicao = 0 ; posicao < 20 ; posicao++) { 
   lcd.setCursor(2,0);
   lcd.print("Vaga livre");
   lcd.setCursor(0,1);
   lcd.print("Pode Estacionar!");
   lcd.scrollDisplayRight();
   delay(299);
   }
     }
     
}
