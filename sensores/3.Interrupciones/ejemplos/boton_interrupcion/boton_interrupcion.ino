const byte botonPin = 2;
volatile unsigned int contadorInterrupciones = 0;
unsigned int ultimaLectura = 0;

// Variables para el antirrebote (Debounce) dentro de la ISR
volatile unsigned long tiempoUltimaInterrupcion = 0;
const unsigned long rebot_time = 250; // 150 ms suele ser ideal para rebotes

void setup() {
  Serial.begin(9600);
  pinMode(botonPin, INPUT); // Resistencia pull-up externa

  // Se activa al caer la señal (FALLING)
  attachInterrupt(digitalPinToInterrupt(botonPin), interrupcionBoton, FALLING);
}

void loop() {
  unsigned int lectura;

  // Copiamos la variable de forma segura
  noInterrupts();
  lectura = contadorInterrupciones;
  interrupts();

  // Mostramos el valor solo cuando haya cambiado de verdad
  if (lectura != ultimaLectura) {
    Serial.print("Interrupciones detectadas: ");
    Serial.println(lectura);
    ultimaLectura = lectura;
  }

  // Nota: Si mantienes tareas largas o delays aquí, la impresión se retrasará,
  // pero el contador ahora SÍ será exacto porque el antirrebote protege la ISR.
  delay(1000); 
}

// Rutina de servicio de interrupción (ISR) optimizada con antirrebote
void interrupcionBoton() {
  unsigned long tiempoActual = millis();

  // Si el tiempo actual menos el último registro es mayor al filtro, es un pulso real
  if (tiempoActual - tiempoUltimaInterrupcion > rebot_time) {
    contadorInterrupciones++;
    tiempoUltimaInterrupcion = tiempoActual; // Actualiza el tiempo del pulso válido
  }
}
