const int triggerPin = 7; // Pin de señal del sensor ultrasónico
const int ledVerde = 4;
const int ledAmarillo = 3;
const int ledRojo = 2;
const int buzzer = 8;

void setup() {
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600); // Inicializa el monitor serie
}

void loop() {
  // Configuración del pin de señal para emitir el pulso
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(triggerPin, LOW);
  
  // Cambiar el pin a entrada para leer el tiempo de rebote del eco
  pinMode(triggerPin, INPUT);
  long duracion = pulseIn(triggerPin, HIGH);
  
  // --- CAMBIO PEDAGÓGICO ---
  // El Arduino ya no calcula la distancia en el código. 
  // Solo imprime el tiempo de vuelo crudo para que el estudiante lo calcule.
  Serial.print("Tiempo de vuelo (us): ");
  Serial.println(duracion);
  
  // Nota: Para que los LEDs y el buzzer sigan funcionando, 
  // el microcontrolador internamente calcula la distancia, pero no la muestra en pantalla.
  float distanciaCm = (duracion * 0.0343) / 2;
  
  // Lógica de control de umbrales para la alerta de colisión
  if (distanciaCm > 100) {
    // Zona Segura
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarillo, LOW);
    digitalWrite(ledRojo, LOW);
    noTone(buzzer);
  } 
  else if (distanciaCm <= 100 && distanciaCm > 40) {
    // Zona de Precaución
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarillo, HIGH);
    digitalWrite(ledRojo, LOW);
    noTone(buzzer);
  } 
  else {
    // Zona de Peligro / Inminencia de Choque
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarillo, LOW);
    digitalWrite(ledRojo, HIGH);
    tone(buzzer, 1000); // Emite tono de alerta de 1000 Hz
  }
  
  delay(100);
}
