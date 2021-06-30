# FilDeSoi
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

## Remote control with fildesoi.inscore (native version)
Fil de soi is packaged with his native version destined to remote control the score.
The native score forwards messages to clients score acting like a server.

Clients have an input field which can be used to connect to a native score allowing it to control the client version (index.html)