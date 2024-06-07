# SmartPlantMonitoring

## Objectif du Projet
Développer un système automatisé pour surveiller et prendre soin des plantes en fonction des conditions environnementales détectées, telles que la lumière, la température, l'humidité et l'humidité du sol, et permettre une intervention manuelle à travers une interface utilisateur.

## Fonctionnalités du Système
- Surveillance environnementale : Mesure continue de la température, de l'humidité, de la lumière, et de l'humidité du sol.
- Contrôle automatique de l'arrosage : Activation d'un système d'arrosage basé sur le niveau d'humidité du sol détecté.
- Indicateurs de santé de la plante : Utilisation de LED RGB pour afficher l'état de santé de la plante.
- Alertes et notifications : Utilisation d'un buzzer pour les alertes critiques et modification des couleurs de la LED RGB.
- Interface de contrôle manuel : Boutons physiques et télécommande IR pour l'interaction utilisateur.
- Sécurité : Surveillance des niveaux d'eau et alertes pour éviter le dessèchement du réservoir.

## Composants Matériels
- Capteurs :
  - Capteur de température et d'humidité
  - Photorésistance
  - Capteur de niveau d’eau (mesure & pluie)
  - Capteur humidité au sol (ou similaire)
- Actuateurs :
  - Pompe à eau
  - Relais (pour contrôler la pompe à eau)
  - Buzzer (pour les alertes sonores)
- Indicateurs :
  - LED RGB (pour l'indication de l'état de santé)
- Contrôle :
  - Bouton
  - Récepteur IR (pour la télécommande)
- Microcontrôleur :
  - Par exemple, Arduino, ESP32, ou Raspberry Pi (selon la complexité du traitement requis)

## Exigences Logicielles
- Firmware :
  - Lecture et interprétation des données des capteurs
  - Logique de contrôle pour l'activation/désactivation de la pompe
  - Gestion des états des LED RGB selon l'état de santé de la plante
  - Implémentation d'un système d'alerte pour les conditions critiques
- Interface utilisateur :
  - Développement d'une interface simple pour le contrôle manuel
  - Option de contrôle à distance via IR

## Mise en Œuvre
1. Conception et achat : Sélection et achat des composants nécessaires.
2. Assemblage et programmation : Assemblage du prototype et programmation du microcontrôleur.
3. Test : Test en laboratoire pour calibrer les capteurs et vérifier les fonctionnalités.
4. Installation et déploiement : Installation du système sur site et ajustements en conditions réelles.

## Critères de Validation
- Surveillance précise des paramètres environnementaux.
- Fonctionnement automatique de l'arrosage pendant une semaine sans surveillance.
- Alertes et notifications claires et promptes.
- Interface utilisateur intuitive et facile à utiliser.
