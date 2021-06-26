
//----------------------------------------------------------------------------
// a download function
//----------------------------------------------------------------------------
class Download {
	static text (filename : string, text: string) : void {
		Download.file (filename, encodeURIComponent(text), "text/plain;charset=utf-8,");
	}
	static wasm (filename : string, data: Uint8Array) : void {
		let blob = new Blob([data], {type: "octet/stream"});
		let url = window.URL.createObjectURL(blob);
		var a = document.createElement('a');
		a.style.display = 'none';
		a.href = url;
		a.download = filename;
		document.body.appendChild(a);
		a.click();
		document.body.removeChild(a);
		window.URL.revokeObjectURL(url);

		// Download.file (filename, data, "application/octet-stream");
	}

	private static file (filename : string, data: string | Uint8Array, type: string) : void {
		var element = document.createElement('a');
		element.setAttribute('href', 'data:'+type + data);
		element.setAttribute('download', filename);

		element.style.display = 'none';
		document.body.appendChild(element);
		element.click();
		document.body.removeChild(element);
	}
}