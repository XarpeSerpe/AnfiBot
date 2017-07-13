#define DEBUG //Comentar esta linea tras hacer el test
//Incluye biblioteca de comunicación por ondas electromagnéticas
#include <VirtualWire.h> 

//Definición de pines
#define pinAdelanteDerecha   3
#define pinAtrasDerecha      5
#define pinAdelanteIzquierda 6
#define pinAtrasIzquierda    9
//#define pinMuestra         4
#define led_pin             13
#define receive_pin         12
#define pinHelice           10 //Sin opcion a reversa
#define pinServo            11

boolean muestraTomada = false;

//Configuración de estado de los pines
void setup()
{
  pinMode(pinAdelanteDerecha,   OUTPUT);
  pinMode(pinAtrasDerecha,      OUTPUT);
  pinMode(pinAdelanteIzquierda, OUTPUT);
  pinMode(pinAtrasIzquierda,    OUTPUT);
  pinMode(pinHelice,            OUTPUT);
  pinMode(pinServo,             OUTPUT);
  //pinMode(pinMuestra,           OUTPUT);
  //digitalWrite(pinMuestra, LOW);
  
  //Configura el pin de recepción
  vw_set_rx_pin(receive_pin);
  //Establece los Bits por segundo de la comunicación
  vw_setup(2000);
  //Inicia la capacidad de recepción de datos
  vw_rx_start();
#ifdef DEBUG  
  Serial.begin(9600);
#endif
}

//Giro de los motores
void loop()
{
  //Preparación de buffer de almacenamiento
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  //Lee el buffer si hay mensaje
  if(vw_get_message(buf, &buflen))
  {//Compara el buffer con las opciones de movimiento
    
  #ifdef DEBUG 
    Serial.print(char(buf[0]));
    Serial.print("\t");
    Serial.print(char(buf[1]));
    Serial.print("\t");
    Serial.print(char(buf[2]));
    Serial.print("\t");
    Serial.print(char(buf[3]));
    Serial.print("\t");
    Serial.print(char(buf[4]));
    Serial.print("\t");
    Serial.println(char(buf[5]));
  #endif
    if(buf[0] == '0' && buf[1]== '0') apaga();
    else if(buf[0] == '0' && buf[1]== 'F') derechaAdelante();
    else if(buf[0] == '0' && buf[1]== 'B') derechaAtras();
    else if(buf[0] == 'F' && buf[1]== '0') izquierdaAdelante();
    else if(buf[0] == 'F' && buf[1]== 'F') adelante();
    else if(buf[0] == 'F' && buf[1]== 'B') giraDerecha();
    else if(buf[0] == 'B' && buf[1]== '0') izquierdaAtras();
    else if(buf[0] == 'B' && buf[1]== 'F') giraIzquierda();
    else if(buf[0] == 'B' && buf[1]== 'B') retrocede();
    analogWrite(pinServo, buf[2]);
    if(buf[3] == '0' || buf[3] == 'B') digitalWrite(pinHelice, LOW);
    else if(buf[3] == 'F') digitalWrite(pinHelice, HIGH);
    /* if (muestraTomada == false)
      {
        if(buf[2] == '1')
        {
          digitalWrite(pinMuestra, HIGH);
          delay(1000); //debe ser sustituido por un final de carrera
          digitalWrite(pinMuestra, LOW);
          muestraTomada = true;
        }
      }*/
  }

}

void apaga()
{
  digitalWrite(pinAdelanteDerecha,   LOW);
  digitalWrite(pinAtrasDerecha,      LOW);
  digitalWrite(pinAdelanteIzquierda, LOW);
  digitalWrite(pinAtrasIzquierda,    LOW);
}

void derechaAdelante()
{
  digitalWrite(pinAdelanteDerecha,   HIGH);
  digitalWrite(pinAtrasDerecha,      LOW);
  digitalWrite(pinAdelanteIzquierda, LOW);
  digitalWrite(pinAtrasIzquierda,    LOW);
}
void derechaAtras()
{
  digitalWrite(pinAdelanteDerecha,   LOW);
  digitalWrite(pinAtrasDerecha,      HIGH);
  digitalWrite(pinAdelanteIzquierda, LOW);
  digitalWrite(pinAtrasIzquierda,    LOW);
}

void izquierdaAdelante()
{
  digitalWrite(pinAdelanteDerecha,   LOW);
  digitalWrite(pinAtrasDerecha,      LOW);
  digitalWrite(pinAdelanteIzquierda, HIGH);
  digitalWrite(pinAtrasIzquierda,    LOW);
}

void adelante()
{
  digitalWrite(pinAdelanteDerecha,   HIGH);
  digitalWrite(pinAtrasDerecha,      LOW);
  digitalWrite(pinAdelanteIzquierda, HIGH);
  digitalWrite(pinAtrasIzquierda,    LOW);
}

void giraDerecha()
{
  digitalWrite(pinAdelanteDerecha,   LOW);
  digitalWrite(pinAtrasDerecha,      HIGH);
  digitalWrite(pinAdelanteIzquierda, HIGH);
  digitalWrite(pinAtrasIzquierda,    LOW);
}

void izquierdaAtras()
{
  digitalWrite(pinAdelanteDerecha,   LOW);
  digitalWrite(pinAtrasDerecha,      LOW);
  digitalWrite(pinAdelanteIzquierda, LOW);
  digitalWrite(pinAtrasIzquierda,    HIGH);
}

void giraIzquierda()
{
  digitalWrite(pinAdelanteDerecha,   HIGH);
  digitalWrite(pinAtrasDerecha,      LOW);
  digitalWrite(pinAdelanteIzquierda, LOW);
  digitalWrite(pinAtrasIzquierda,    HIGH);
}

void retrocede()
{
  digitalWrite(pinAdelanteDerecha,   LOW);
  digitalWrite(pinAtrasDerecha,      HIGH);
  digitalWrite(pinAdelanteIzquierda, LOW);
  digitalWrite(pinAtrasIzquierda,    HIGH);
}
