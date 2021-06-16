# **[FR]** FilDeSoi
## Description
Fil de soi est une piece mixte pour guitare et électronique en temps réel composées par Alain Bonardi et interprétées par Amèlia Mazarico. Créé le 17 septembre 2016

Inscore permet à cette partition d'embarquer le DSP audio de la composition et de connecter les differentes entrées à ce DSP.

## InscoreWeb

La librairie INScoreJS permet d'embarquer le moteur [INScore](https://inscore.grame.fr) dans une page web et de designer des partition augmentés, dynamiques et interactives pouvant êtres publiées sur le web.

## Faust

[Faust](https://faust.grame.fr/) (Functional Audio Stream) est un langage de programmation fonctionnel pour la synthèse audio et le traitement du signal audio avec un gros accent pour le design de synthetiseurs, d'instruments de musiques, d'effets audio, ect.
Faust se focalise sur les application necéssitant de grosses performances concernant le traitement du signal audio et les plugin pour de nombreuses plateformes et standards.


## Details
- `index.html` : Partition client web, elle embarque le DSP faust.
- `fildesoi.inscore` : Partition native, elle sert à controler les client grâce au forwarding de messages.
- `packages.json` : Definition du package pour l'installation.
- `rsrc/` : toutes les ressources utiles sont situés ici (DSP, Audio, images)

## Installation
```
npm install
```

## Test Local
```
python -m http.server <port>
```
## Compatibilité Inscore

INScoreJS est toujours en version alpha. Le moteur à été testé sur ces plateformes et navigateurs:

|         | Chrome  | Firefox  | Safari  | Opera | Edge | Internet Explorer |
|---------|---------|----------|---------|-------|------|-------------------|
| MacOS   |   OK   |   OK     |    OK   |   OK  |  -   |   -   |
| Ubuntu  | -      |   OK     |   -     |   -   |  -   |   -   |
| Windows | OK     |   OK     |   -     |   -   | OK   | non supporté |
| Android |  OK    |   OK     |   -     |   -   |  -   |   -   |


# **[EN]** FilDeSoi
## Description
Fil de soi is a mixed piece for acoustic and electronic guitar in real time. Composed by Alain Bonardi and performed by Amèlia Mazarico.
Created the 17th september 2016.

Inscore allow this score to embed the audio DSP of the composition and connect the different inputs to this DSP.

## InscoreWeb
The INScoreJS library allows to embed the [INScore](https://inscore.grame.fr) engine services in a web page and to design augmented, dynamic and interactive musical scores that can be published on the Internet.

## Faust
[Faust](https://faust.grame.fr/) (Functional Audio Stream) is a functional programming language for sound synthesis and audio processing with a strong focus on the design of synthesizers, musical instruments, audio effects, etc. Faust targets high-performance signal processing applications and audio plug-ins for a variety of platforms and standards.

With INScore we can embeded a Faust DSP allowing real time signal processing inside the augmented score.

## Details
- `index.html` : Score Client web, a faust DSP is embeded.
- `fildesoi.inscore` : Native Score, it'll controls clients by sending message to them.
- `packages.json` : Package definition for installation.
- `rsrc/` : All usefull ressources (audio, DSP, images).

## Installation
```
npm install
```

## Local test
```
python -m http.server <port>
```

## Inscore Compatibility

INScoreJS is still in alpha version. The engine has been tested on the following platforms and browsers:

|         | Chrome  | Firefox  | Safari  | Opera | Edge | Internet Explorer |
|---------|---------|----------|---------|-------|------|-------------------|
| MacOS   |   OK   |   OK     |    OK   |   OK  |  -   |   -   |
| Ubuntu  | -      |   OK     |   -     |   -   |  -   |   -   |
| Windows | OK     |   OK     |   -     |   -   | OK   | unsupported |
| Android |  OK    |   OK     |   -     |   -   |  -   |   -   |