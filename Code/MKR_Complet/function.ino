/*
  SOLUTION 2 - PROJET RUCHE >> DELBART Julien & PATIN Mathéo - BTS CIEL - 2024/2025

  Ce fichier contient les différentes classes et fonctions nécessaires au bon fonctionnement du code et à l'allègement du code principal.
*/

//------------------------------------------------------------------------------
//Classe start et ses fonctions

class start {
public:

  //Démarrage du module lora et configuration nécessaire
  void lora() {
    if (!modem.begin(EU868)) {
      Serial.println("Problème de démarrage du module");
      while (1) {}
    };
    delay(1000);
    Serial.println("Module démarré");
    delay(500);
    Serial.print("Version du module: ");
    Serial.println(modem.version());
    Serial.print("EUI de l'appareil (DevEUI): ");
    Serial.println(modem.deviceEUI());
    delay(500);
    Serial.println("Connexion...");

    int connected = modem.joinOTAA(appEui, appKey);
    if (!connected) {
      Serial.println("Un problème est survenu lors de la connexion. Ressayer !");
      while (1) {}
    }
    Serial.println("Connexion au serveur The Things Network réussie");

    // Set poll interval to 60 secs.
    modem.minPollInterval(60);
  }

  //Démarrage et configuration du DHT22
  void dht22() {
    pinMode(DHTPIN, DHTTYPE);
    Serial.println("Démarrage DHT22");
    delay(500);
    dht.begin();
    Serial.println("Capteur DHT22 initialisé avec succés !");
  }


  //Démarrage du BME280
  void bme280() {
    delay(500);
    Serial.println("Démarrage BME280");
    delay(500);
    if (!bme.begin(0x76)) {  // Adresse I2C du BME280 (par défaut souvent 0x76 ou 0x77)
      Serial.println("Erreur : Capteur BME280 introuvable ! Vérifiez les connexions.");
      while (1)
        ;  // Boucle infinie si le capteur n'est pas détecté
    }

    Serial.println("Capteur BME280 détecté avec succès !");
  }

  //Démarrage et initialisation du HX711
  void hx711() {
    Serial.println("Démarrage HX711");

    scale.begin(DOUT, CLK);               //Addressage du HX711
    scale.set_scale(calibration_factor);  //Calibrage
    scale.tare();                         //Tare de la balance
    delay(500);

    Serial.println("HX711 démarré avec succès");
  }

  void res() {
    //Il n'y a absolument rien à initialiser pour la LDR
  }
};

start start;

//------------------------------------------------------------------------------
//Fonction de démarrage des modules et capteurs

void demarrage() {
  start.lora();    //Démarrage LoRa
  start.dht22();   //Démarrage DHT22
  start.bme280();  //Démarrage BME280
  //start.hx711();   //Démarrage HX711
  start.res();  //Démarrage LDR
}

//------------------------------------------------------------------------------
//Classe recup et ses fonctions - Servant à récupérer les données des capteurs

class recup {
public:

  //Module de fonction pour la température et l'humidité extérieure
  void dht22_int() {
    he = dht.readHumidity();
    te = dht.readTemperature();
  }

  //Module de fonction pour la température, l'humidité et la pression intérieure
  void bme280_ext() {
    hi = bme.readHumidity();
    ti = bme.readTemperature();
    pr = bme.readPressure() / 100.0F;
  }

  //Module de fonction pour le poids
  void hx711_pds() {
    scale.power_up();
    delay(500);
    pds = scale.get_units(5);
    delay(500);
  }

  //Module de fonction pour la luminosité
  void res_lux() {
    lux = mapLux(analogRead(A1));
    delay(500);
  }
};

//------------------------------------------------------------------------------
//Classe
recup recup;  //Ouverture de la classe

//------------------------------------------------------------------------------
//Fonction transform() : Fonction servant à convertir les variables de données des capteurs de float à string afin de permettre la transmission

void transform() {
  msg_he = String(he);
  msg_hi = String(hi);

  msg_te = String(te);
  msg_ti = String(ti);

  msg_pr = String(pr);
  msg_lux = String(lux);

  msg_pds = String(pds);
}

//------------------------------------------------------------------------------
//Fonction recup_donnees() : Fonction servant à récupérer les données des capteurs et à les stocker dans les variables de type float

void recup_donnees() {
  Serial.println("");
  Serial.println("Récupération des données des capteurs");
  delay(1000);

  recup.dht22_int();
  recup.bme280_ext();
  //recup.hx711_pds();
  recup.res_lux();

  transform();

  Serial.println("");
  Serial.println("DHT22 :");
  Serial.println("Température : " + msg_te + " | Humidité : " + msg_he);
  delay(500);

  Serial.println("");
  Serial.println("BME 280 :");
  Serial.println("Température intérieure : " + msg_ti + " | Humidité intérieure : " + msg_hi + " | Pression : " + msg_pr);
  delay(500);

  Serial.println("");
  Serial.println("HX711 :");
  Serial.println("Poids : " + msg_pds);
  delay(500);

  Serial.println("");
  Serial.println("Panneau Solaire : ");
  Serial.println("Luminosité : " + msg_lux);
  delay(500);
}


//------------------------------------------------------------------------------
//Fonction lora_sender() : Fonction servant à envoyer les données récupérées en LoRa

void lora_sender() {
  int err;

  Serial.println("");
  Serial.println("Envoi du paquet...");

  modem.beginPacket();  //Début de la trame du message

  Serial.println("Trame du message >> Température extérieure, Humidité extérieure, Température intérieure, Humidité intérieure, Luminosité, Pression, Poids");
  Serial.println(msg_te + "," + msg_he + "," + msg_ti + "," + msg_hi + "," + msg_lux + "," + msg_pr + "," + msg_pds);
  modem.print(msg_te + "," + msg_he + "," + msg_ti + "," + msg_hi + "," + msg_lux + "," + msg_pr + "," + msg_pds);

  err = modem.endPacket(true);  //Fin de la trame du message

  if (err > 0) {  //Vérification de l'envoi 
    Serial.println("Message envoyé!");
  } else {
    Serial.println("");
    Serial.println("Erreur ! Envoi impossible. Réessayez :(");
    Serial.println("(Vous ne pouvez envoyer qu'un nombre limité de message par minute, cela dépend de la force du signal.");
    Serial.println("Cela peut varier de 1 message chaque secondes à 1 message par minute. Faites attention !)");
  }

  Serial.println("");
  Serial.println("Délai d'une minute de précaution");

  delay(60000);  //Délai obligatoire pour la certitude de la disponibilité du canal (à cause de la distance)

  Serial.println("Canal prêt : Vous pouvez à nouveau envoyer un message.");
}