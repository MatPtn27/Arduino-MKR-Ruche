/*
  SOLUTION 2 - PROJET RUCHE >> DELBART Julien & PATIN Mathéo - BTS CIEL - 2024/2025

  Ce fichier est une bibliothèque de bibliothèques, il permet de simplifier la navigation dans les fichiers.
*/

//------------------------------------------------------------------------------
//Importation des bibliothèques "constructeurs"

#include <Arduino.h>
#include <MKRWAN.h> //Bibliothèque nécessaire aux fonctionnalités propres à l'Arduino MKR WAN1310
#include <Wire.h> //Bibliothèque pour la connexion I2C
#include <DHT.h> //Bibliothèque pour le DHT
#include <Adafruit_Sensor.h> //Bibliothèque intégrant les capteurs Adafruit
#include <Adafruit_BME280.h> //Bibliothèque pour les fonctions du BME280
#include "HX711.h" //Bibliothèque pour l'utilisation du HX711 (Balance)
#include <math.h>


//------------------------------------------------------------------------------
//Bibliothèques personnalisées

#include "LoRa_Secrets.h" //Bibliothèque personnalisée pour la sécurité de la connexion LoRa
#include "Para_Var.h" //Ajout de la bibliothèque personnalisée pour les paramètres et les variables