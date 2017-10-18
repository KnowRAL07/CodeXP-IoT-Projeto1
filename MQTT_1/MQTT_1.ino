#include <Servo.h> //Este comando inclui a biblioteca Servo neste código 
#include <SPI.h>
#include <UIPEthernet.h>
#include <utility/logging.h>
#include <PubSubClient.h>

Servo Servo1; //Identifica um objeto do tipo Servo chamado Servo1 
int Recebido; //Variável que armazenará o valor recebido pela serial
int posicao; //Variável que armazenará as posições do servo 

// Atualizar ultimo valor para ID do seu Kit para evitar duplicatas
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF
};

// Endereço do Cloud MQTT
char* server = "m12.cloudmqtt.com";

// Valor da porta do servidor MQTT
int port = 19724;


void whenMessageReceived(char* topic, byte* payload, unsigned int length) {
  // Converter pointer do tipo `byte` para typo `char`
  char* payloadAsChar = payload;

  // Converter em tipo String para conveniência
  String msg = String(payloadAsChar);
  Serial.print("Topic received: "); Serial.println(topic);
  Serial.print("Message: "); Serial.println(msg);

  // Dentro do callback da biblioteca MQTT, 
  // devemos usar Serial.flush() para garantir que as mensagens serão enviadas
  Serial.flush();

  int msgComoNumero = msg.toInt();
  
  Serial.print("Numero lido: "); Serial.println(msgComoNumero);
  Serial.flush();

      if (msgComoNumero == 1){ //se receber o sinal de O pela serial faça: 
      posicao = 0; //movimento para posição 0
      Serial.println(posicao); //mostra no Monitor Serial o valor da posiçã
      }
      if (msgComoNumero == 2){ //se receber o sinal de C pela serial faça: 
         posicao = 180; //movimento para posição 90
         Serial.println(posicao); //mostra no Monitor Serial o valor da posição 
      }
      Servo1.write(posicao); //Escreve a posição no servo
      }
EthernetClient ethClient;
PubSubClient client(server, port, whenMessageReceived, ethClient);

void setup()
{
  Servo1.attach(3); //Pino onde o servo deve estar colocado
  Serial.begin(9600);
  while (!Serial) {}
  if (!Ethernet.begin(mac)) {
    Serial.println("DHCP Failed");
  } else {
    Serial.println(Ethernet.localIP());
  }

  Serial.println("Connecting...");
  // Conectando com informações de cliente e senha criados através da interface web do serviço
                        //nome qualquer, user, senha
  //if (client.connect("arduinoClient", "xfzgyees", "f_AZeW9aQVI3")) {
  if (client.connect("arduino1", "xfzgyees", "f_AZeW9aQVI3")) {
    Serial.println("Connected");
  //client.publish("outTopic", "hello world");
  //Serial.println("outTopic sent");
    client.publish("temperatura", "hello world");
    Serial.println("temperatura sent");
    //client.subscribe("inTopic");
    client.subscribe("temperatura");
  } else {
    Serial.println("Failed to connect to MQTT server");
  }
}
void loop()
{
  // A biblioteca PubSubClient precisa que este método seja chamado em cada iteração de `loop()`
  // para manter a conexão MQTT e processar mensagens recebidas (via a função callback) 
  client.loop();
}

