# P2S3
Le projet de la S3 est un projet de générateur d'électricité.
Le projet que nous dévelopons est un vélo électrique qui va recharger un batterie.
## ESP32 Application
## Qt Application
### Setup Guide
* 1 - Installer Qt 5.15.1 via leur site web: https://www.qt.io/download-qt-installer. Une fois dans l'installer, ouvrez le dropdown "5.15.1" et sélectionnez seulement "MinGW 8.1.0 32-bit"

* 2 - Vous inscrire sur le site de JetBrains pour obtenir une license académique pour leur IDEs: https://www.jetbrains.com/shop/eform/students.
Vous pourrez ensuite installer CLion à cette adresse: https://www.jetbrains.com/fr-fr/clion/download/#section=windows

* 3 - Créez vous un dossier nommé workspace ou git (si ce n'est pas déjà fait), et clonez le repos P2S3.

* 4 - Dans CLion, ouvrir le projet Qt via File>Open et sélectionnez le dossier P2S3\QtApp

* 5 - Configurer le compilateur:
  * File>Settings>Build, Execution, Deployment>Toolchains
  * Dans la case "Environment", sélectionner le dossier Qt/Tools/mingw810_32
  * Assurez-vous que l'auto-détection fonctionne (des crochets verts devraient apparaitre)
  
* 6 - Configurer CMake:
  * File>Settings>Build, Execution, Deployment>CMake
  * Pour les profils Debug et Release, dans "CMake options", ajoutez ceci:  
  `-DCMAKE_PREFIX_PATH=C:/Qt/5.15.1/mingw81_32` (assurez-vous que le path corresponde à votre installation de Qt)

Vous pouvez maintenant build et lancer l'application. À noter que pour qu'il faut lancer l'application avec le bouton "Debug" pour utiliser les breakpoints et la console.
