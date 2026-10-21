const byte botonPin = 2;
const unsigned long retardoTarea = 1000; // simula tarea larga

unsigned int contadorPulsaciones = 0;
int estadoAnterior = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(botonPin, INPUT); // pull-up externa
}

void loop() {
  int estado = digitalRead(botonPin);

  // Flanco de bajada: el pin pasa de HIGH a LOW
  if (estadoAnterior == HIGH && estado == LOW) {
    contadorPulsaciones++;
    Serial.print("Pulsaciones detectadas: ");
    Serial.println(contadorPulsaciones);
  }

  
  estadoAnterior = estado;

  delay(retardoTarea);
}
