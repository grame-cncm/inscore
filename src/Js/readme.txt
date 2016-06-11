*******************************************
* prérequis pour la compilation du projet *
*******************************************

1) Installation de Visual Studio code : https://code.visualstudio.com/Docs/editor/setup
2) Installation de Node.js (version 5.7.1 stable) : https://nodejs.org/en/      /!\ ajouter dans le path
3) Installation du compilateur : npm install -g typescript@next
4) Créer le fichier tsconfig.json si problème :
		{
		    "compilerOptions": 
		    {
		        "target": "ES5",
		        "module": "amd",
		        "sourceMap": false
		    }
		    "files":["fichier.ts"] // si l’on veut compiler ce fichier en 
		}         					particulier
5) Dans un terminal : tsc fichier.ts pour compiler en javascript

