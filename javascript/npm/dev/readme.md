# INScoreJS - Developing a custom application

## Content of this folder

- inscoreview.js: a library providing the INScore view
- inscoreglue.js: a library providing application dependent features
- src: the typescript source code of the inscoreglue library


## General architecture

INScore is designed as a Model - View - Controller [MVC] architecture. The model is implemented in C++ and compiled in Web Assembly to produce the libINScore.js .wasm library.  
The view is implemented in typescript and corresponds to the inscoreview.js library. It provides a view of the model based on the DOM.  
A third library, inscoreglue.js, implements services that are specific to the application, such as drag and drop support for example.

inscoreview.js and inscoreglue.js are compiled together to produce the INScoreJS.js library. However, to cover the specific needs of an application, the inscoreglue.js library could be replaced by any other library providing equivalent services. 
The `src` folder is provided as an example, it contains the typescript implementation of the current inscoreglue.

## in progress...

This dev kit is currently in progress and not really documented.
It will most probably evolve in the next versions. At this stage, it is therefore premature and not recommended to develop a specific application.

----
[INScore](https://inscore.grame.fr/) is a project developed by [GRAME-CNCM](https://www.grame.fr) Computer Research Lab.

