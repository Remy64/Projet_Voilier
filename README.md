# Projet_Voilier

##Structure du Projet

Les fichiers sources sont divisés entre deux répertoires et un programme main:

* Un répertoire "MyDrivers" contient l'implémentation de fonction bas-niveau générique pour la gestion du microcontrôleur, comme la gestion de PWM ou la récupératon d'une conversion par ADC.

* Un répertoire "Components" contient des fonctions dédiées plus spéciciquement au voilier, s'appuyant sur les fonctions Drivers. Elles permettent par exemple de convertir les valeurs lues dans un registre sachant les caractéristiques du voilier.

* Un fichier main s'appuyant sur les fonctions Components pour gérer en continue la navigation du voilier.

Les fonctionnalités implémentées dans les fichiers Drivers sont:

* PWM en sortie (PWM_Driver), avec possibilité de choisir fréquence et duty cycle.

* PWM en entrée (PWM_IN_Driver), permettant d'obtenir période et duty cycle.

* Conversion ADC (ADC_Driver), captant en continu les valeurs lues sur 3 pins différents.

* Codeur incrémental (codeur_inc)

* Une module d'émission UART permettant d'envoyer des données via un démodulateur

Les fonctionnalités haut-niveau s'appuyant sur ces drivers sont : 

* La gestion du plateau (Plate), qui utilise une PWM en sortie pour répondre aux instructions de rotation (direction/puissance)

* La gestion de l'écoute (Ecoute), qui utilise une PWM en sortie pour tendre le servo-moteur de l'écoute entre deux extremas d'angle.

* La gestion de l'accéléromètre (Accel), qui utilise un ADC configuré pour capter et convertir en m.s-2 la valeur d'accélération en Y.

* La gestion de la girouette n'a pas de fonctionnalité plus haut niveau dédiée, l'angle est directement lue via le driver.

* La réception des instructions de la télécommande (Rx_Rcv), qui utilise une PWM en entrée pour obtenir les informations de direction et de puissance de la télécommande.

* L'avertissement via l'USART du niveau de batterie du voilier

Le main initialise dans un premier temps chacun des composants matériels utilisés. Puis, une tâche est configuré via un timer pour gérer en interruption la tension de l'écoute selon l'angle au vent du voilier et son roulis(calculé directement à partir de la valeur d'accélération en Y). 
La boucle principale du main gère la réception en continue des instructions de la télécommande et impose la rotation correspondante au plateau.


