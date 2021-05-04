# Welcome to INScoreJS


The INScoreJS library allows to embed the [INScore](https://inscore.grame.fr) engine services in a web page and to design augmented, dynamic and interactive musical scores that can be published on the Internet.

## Content of the package

- INScoreJS.js: the INScore javascript library
- libINScore.js .wasm: the INScore engine compiled as a web assembly library
- dev: intended to web developers who want to develop a custom application (see the [dev/readme](dev/readme.md) file)
- inscore.d.ts: a typescript interface for web development
- examples: contains examples of html pages
- fonts: contains fonts used by INScoreJS

## Dependencies

The INScore package depends on several libraries, only necessary if you're using specific objects:

- [guidolib](https://www.npmjs.com/package/@grame/guidolib): required for symbolic music notation and piano roll representation.
- [libmusicxml](https://www.npmjs.com/package/@grame/libmusicxml): required to import MusicXML files (assumes that the `guidolib` is also present).
- [libfaust](https://www.npmjs.com/package/@grame/libfaust): required to use `faust` objects.

<!-- All these libraries should automatically come with this package. -->

## Examples

To display any of the provided examples, you must first launch a web server from the root of this package.
Python provides such services. Using python 3:
~~~~~~~~~~
$ python -m http.server [optionnal port number (default is 8000)]
~~~~~~~~~~
Http servers are also available from [npm](https://www.npmjs.com/package/http-server).

Once the server is running, you can redirect a browser to [http://localhost:8000/examples](http://localhost:8000/examples) and open any of the examples.

### Note 
Drag and drop works with the javascript version in a similar way to the native version: you can drop an inscore file (or a script in textual form) to any inscore 'div'.

## Designing a musical score

You can start from the template provided in the example folder.  
INScoreJS do not support all the messages of the native version and provides specific messages. See the [INScore Web documentation](https://inscoredoc.grame.fr) for more details.




### Important notes

INScoreJS is still a project under development. The compatibility of the graphic rendering is not yet guaranteed for future versions.
In particular, improvements should be made for a rendering closer to the native version.
If you develop your own pages, it is therefore recommended to save the libraries used for preservation reasons.

Note also that the content of an inscore div is interpreted by browsers as html code. Thus avoid using `<` (opening tag character) and replace it with the textual form `&lt;`. Comments should also be expressed using the html form `<!-- commented section -->` and not using inscore comments (#). This is valid for inline code only and does not apply to inscore files that you could drop on an inscore div.



## Compatibility

INScoreJS is still in alpha version. The engine has been tested on the following platforms and browsers:

|         | Chrome  | Firefox  | Safari  | Opera | Edge | Internet Explorer |
|---------|---------|----------|---------|-------|------|-------------------|
| MacOS   |   OK   |   OK     |    OK   |   OK  |  -   |   -   |
| Ubuntu  | -      |   OK     |   -     |   -   |  -   |   -   |
| Windows | OK     |   OK     |   -     |   -   | OK   | unsupported |
| Android |  OK    |   OK     |   -     |   -   |  -   |   -   |


----
[INScore](https://inscore.grame.fr/) is a project developed by [GRAME-CNCM](https://www.grame.fr) Computer Research Lab.

