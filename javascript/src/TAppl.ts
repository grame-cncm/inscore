
///<reference path="lib/libINScore.d.ts"/>
///<reference path="inscore.ts"/>
///<reference path="TFileLoader.ts"/>

class TAppl {

	static load (file: string ) {
		TFileLoader.load (document.body, file, "text/plain").then ( (content) => {
			if (content) {
				if (!inscore.loadInscore (content))
					console.log ("Failed to load ", file );
			}
		});
	}
}
