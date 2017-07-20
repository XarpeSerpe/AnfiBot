/*EmisorAnfibot
  Autores:
  Ruben Fernandez Sotelo
  Daniel Moreno Acea
*/

#define DEBUG //Esta lina debe ser comentada en cuanto el programa esta testado
#define VERSION 0.1
#include <VirtualWire.h>

//Pensar cambiar int por byte para ahorrar espacio
const int potIzq       = A4;  //Control motor izquierdo
const int potDer       = A5;  //Control motor derecho
const int motorHelice  = A1;  //Cambio de estado motor helice
const int potTimon     = A2;  //Control del servo motor helice  
const int tomaMuestras =  4;  //Control motor jeringuilla de muestras
const int capturaRed   =  5;  //Control motor de recogida por arrastre
const int humbral  = 1024/3;  //Para fijar los valores de cambio de comportamiento
const int medio    = 1024/2;
const int transmit_pin = 12; //Pin de la antena emisora
  
void setup()
{
  pinMode(tomaMuestras,INPUT_PULLUP); //Pulsador que conecta directamente 5V a GND...
  pinMode(capturaRed,INPUT_PULLUP);   //...precisa una resistencia interna 
  
  #ifdef DEBUG
   Serial.begin(9600);
   Serial.print("Version ");
   Serial.println(VERSION);
  #endif
  vw_set_tx_pin(transmit_pin);
  vw_setup(2000);
}

void loop()
{
  //Muestreo del estado de la base de radio control
  int marchaIzq = media(potIzq,500);
  int marchaDer = media(potDer,500);
  int posicionTimon = analogRead(potTimon);
  int helice = analogRead(motorHelice);
  int muestras = digitalRead(tomaMuestras);
  int red = digitalRead(capturaRed);
  
  char mensaje[]= "000000"; //Mensaje por defecto, todos los motores parados
  
  //Motor izquierda
  if(medio-humbral < marchaIzq && marchaIzq < medio+humbral) mensaje[0]='0'; //Parado
  else if(marchaIzq > medio+humbral) mensaje[0]='F';//Marcha adelante
  else mensaje[0]='B';//Marcha atras
    
  //Motor derecha
  if(medio-humbral < marchaDer && marchaDer < medio+humbral) mensaje[1]='0';
  else if(marchaDer > medio+humbral) mensaje[1]='F';
  else mensaje[1]='B';

  //Posicion del servo timon
  mensaje[2] = posicionTimon;

  //Estado del motor helice
  if(medio-humbral < marchaIzq && marchaIzq < medio+humbral) mensaje[3]='0'; //Parado
  else if(marchaIzq > medio+humbral) mensaje[3]='F';//Marcha adelante
  else mensaje[3]='B';//Marcha atras
  
  //Muestra
  if(muestras == true) mensaje[4]='0';
  else mensaje[4]='1';
   
  //Red
  if(red == true) mensaje[5]='0';
  else mensaje[5]='1';

  //Mensaje de test
  #ifdef DEBUG
    Serial.print(marchaDer);
    Serial.print("\t");
    Serial.print(marchaIzq);
    Serial.print("\t");
    Serial.print(posicionTimon);
    Serial.print("\t");
    Serial.print(helice);
    Serial.print("\t");
    Serial.print(red);
    Serial.print("\t");
    Serial.print(muestras);
    Serial.print("\t");
    Serial.println(mensaje);
  #endif
    
  vw_send((uint8_t *)mensaje, strlen(mensaje));
  vw_wait_tx();  
}

int media(int pin,int medidas)
{
  unsigned long sum = 0;
  for(int i = 0; i < medidas; i++) sum += analogRead(pin);
  return sum/medidas;
}
