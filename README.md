# Projet_Voilier

##Structure du Projet

Les fichiers sources sont divisés entre deux répertoires auxiliaires et le programme main:

* Un répertoire "__MyDrivers__" contient l'implémentation de fonction bas-niveau générique pour la gestion du microcontrôleur, comme la gestion de PWM ou la récupératon d'une conversion par ADC.

* Un répertoire "__Components__" contient des fonctions dédiées plus spéciciquement au voilier, s'appuyant sur les fonctions Drivers. Elles permettent par exemple de convertir les valeurs lues dans un registre sachant les caractéristiques du voilier.

* Un fichier main s'appuyant sur les fonctions Components pour gérer en continue la navigation du voilier.

Les fonctionnalités implémentées dans les fichiers Drivers sont:

* (_PWM_Driver_) PWM en sortie, avec possibilité de choisir fréquence et duty cycle.

* (_PWM_IN_Driver_) PWM en entrée, permettant d'obtenir période et duty cycle.

* (_ADC_Driver_) Conversion ADC, captant en continu les valeurs lues sur 3 pins différents.

* (_UART_) Un module d'émission UART permettant d'envoyer des données captées ensuite via un démodulateur.

* (_codeur_inc_) Codeur incrémental permettant de mesurer l'angle du composant girouette fixé au sommet du mât. 

Les fonctionnalités plus "haut-niveau" s'appuyant sur ces drivers sont : 

* (_Plate_) Gestion du plateau , qui utilise une PWM en sortie pour répondre aux instructions de rotation (direction/puissance)

* (_Ecoute_) Gestion de l'écoute , qui utilise une PWM en sortie pour tendre le servo-moteur de l'écoute entre deux extremas d'angle.

* (_Accel_) Gestion de l'accéléromètre , qui utilise un ADC configuré pour capter et convertir en m.s-2 la valeur d'accélération en Y.

* (_Rx_Rcv_) Réception des instructions de la télécommande, utilise une PWM en entrée pour obtenir les informations de direction et de puissance de la télécommande.

* (_Battery_) Mesure du niveau de batterie via un ADC.

* La gestion de la girouette n'a pas de fonctionnalité plus haut niveau dédiée, l'angle est directement lu via le driver.

Chacun des fichiers sources composants contient une fonction permettant d'initialiser les périphériques nécessaires à son utilisation.

Le main se divise en deux tâches exécutées "en parallèle".

* (_sail_management(void)_)
Une tâche gérant les actions automatiques de navigation, indépendates du pilote "sail_management". On y capte la valeur d'accélération sur l'axe Y(et donc l'angle de roulis correspondant), l'angle du voilier au vent et le niveau de batterie. On gère ensuite l'éventuel relâchement de l'écoute nécessaire passé un angle de roulis critique, ou sa tension en fonctionde l'angle au vent. Un message d'alerte est envoyé via UART en cas de batterie faible.

* (_while(true)_)
Dans une boucle infinie, on gère la réception des instructions de la télécommande, et on fait pivoter le plateau en conséquence. 
