/*
  SOLUTION 2 - PROJET RUCHE >> DELBART Julien & PATIN Mathéo - BTS CIEL - 2024/2025

  Ce fichier est le fichier principal de l'arduino MKR WAN 1310.
  Il contient les fonctions setup et loop qui sont executés de base par la carte arduino.
*/

//------------------------------------------------------------------------------
//Ajout des bibliothèques

#include "libraries.h"  //Ajout de la bibliothèque-ception


//------------------------------------------------------------------------------
//Code Setup

void setup() {
  Serial.begin(115200);
  Wire.begin();  // Initialisation du bus I2C
  demarrage();
}

//------------------------------------------------------------------------------
//Code principal "loop"

void loop() {

  recup_donnees();
  delay(1000);
  lora_sender();

  delay(30000);  //Délai de 15 minutes avant la nouvelle boucle du programme
}
