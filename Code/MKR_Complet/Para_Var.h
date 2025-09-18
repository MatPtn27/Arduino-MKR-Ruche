/* 
  SOLUTION 2 - PROJET RUCHE >> DELBART Julien & PATIN Mathéo - BTS CIEL - 2024/2025

  Ce fichier est une bibliothèque permettant de rendre le code "principal" plus léger.
  Il inclut toutes les fonctions nécessaires aux définitions de paramètres pour les capteurs ou pour le module LoRa.
  Il sert également à définir toutes les variables nécessaires sans surcharger le code.
*/

//------------------------------------------------------------------------------
//Définition des données et des paramètres requis pour la connexion LoRa

String appEui = SECRET_APP_EUI;
String appKey = SECRET_APP_KEY;

//------------------------------------------------------------------------------
//Ouverture des classes

LoRaModem modem;
Adafruit_BME280 bme;
HX711 scale;

//------------------------------------------------------------------------------
//Définition des paramètres nécessaires pour le DHT22

#define DHTTYPE DHT22 //Définition du modèle du capteur
#define DHTPIN 6 //Attribution au pin 6
DHT dht(DHTPIN, DHTTYPE);

//------------------------------------------------------------------------------
//Définition des paramètres nécessaires pour le HX711 (Balance)

#define calibration_factor -7050.0 //On obtient ce facteur de calibration en pesant un objet de poids connu

#define DOUT  5
#define CLK  4

//------------------------------------------------------------------------------
//Création des variables globales

float he = 0;   //Humidité extérieure
float hi = 0;   //Humidité intérieure

float te = 0;   //Température extérieure
float ti = 0;   //Température intérieure

float pr = 0;   //Pression
int mapLux(int sensorValue) {
  if (sensorValue < 100) return 0; // Très sombre
  else if (sensorValue < 250) return 1; // Faible lumière
  else if (sensorValue < 400) return 2; // Lumière moyenne
  else if (sensorValue < 575) return 3; // Lumière forte
  else return 4;  // Lumière intense
}
int lux = 0;  //Intensité lumineuse en lux 

float pds = 0;  //Poids

//------------------------------------------------------------------------------
//Création des variables "textes" pour la transmission

String msg_he;
String msg_hi;

String msg_te;
String msg_ti;

String msg_pr;
String msg_lux;

String msg_pds;

