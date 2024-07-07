#include "Arduino.h"
#include <WiFi.h>
#include <HTTPClient.h>

// Configurações sensor de turbidez
#define TURBIDITY_PIN 34 // Pino ADC onde o sensor de turbidez está conectado

// Configurações WiFi
const char* ssid = "XXX";
const char* password = "XXX";

void setup() {
  Serial.begin(9600);

  // Conecta ao WiFi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println(" Conectado ao WiFi");

  // Verifica e imprime o endereço IP atribuído ao ESP32
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.println("Iniciando leitura do sensor de turbidez...");

  // Lê o valor analógico do sensor de turbidez
  int sensorValue = analogRead(TURBIDITY_PIN);
  float voltage = sensorValue * (3.3 / 4095.0); // Converte o valor para tensão

  // Exibe o valor lido no Serial Monitor
  Serial.print("Valor do sensor de turbidez: ");
  Serial.print(sensorValue);
  Serial.print(" - Tensão: ");
  Serial.print(voltage);
  Serial.println(" V");

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi conectado. Enviando dados para a API...");

    HTTPClient http;

    // Inicia a conexão com a URL da API
    http.begin("http://iot.ipt.br:8000/adaptor/resources");
    
    // Define o cabeçalho da requisição
    http.addHeader("Content-Type", "application/json");
    
    // Autenticação
    http.setAuthorization("xxx", "xxxx");

    // Cria o JSON com os dados de turbidez
    String json = "{}";
    
    // Exibe o JSON no Serial Monitor
    Serial.print("JSON enviado: ");
    Serial.println(json);

    // Envia a requisição POST
    int httpResponseCode = http.POST(json);

    // Verifica o código de resposta HTTP
    if (httpResponseCode > 0) {
      // Exibe a resposta do servidor
      String response = http.getString();
      Serial.println("Código de resposta da API: ");
      Serial.println(httpResponseCode);
      Serial.println("Resposta da API: ");
      Serial.println(response);
    } else {
      // Exibe erro na requisição HTTP
      Serial.print("Erro na requisição HTTP: ");
      Serial.println(httpResponseCode);
    }
    
    // Finaliza a conexão HTTP
    http.end();
  } else {
    Serial.println("WiFi desconectado. Não foi possível enviar dados para a API.");
  }

  // Aguarda 3 segundos antes de fazer a próxima leitura
  delay(3000);
}
