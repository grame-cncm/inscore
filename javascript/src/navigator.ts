

var Safari: boolean = false;
var Explorer: boolean = false;
var Edge: boolean = false;
var Firefox: boolean = false;
var Chrome: boolean = false;

var WindowsOS: boolean = false;
var MacOS: boolean = false;
var UnixOS: boolean = false;

function scanNavigator() : void {
	var ua = window.navigator.userAgent;
	Chrome = (ua.indexOf('Chrome') >= 0);
	Safari = (ua.indexOf('Safari') >= 0) && ! Chrome;
	Explorer = (ua.indexOf('MSIE ') >= 0) || (ua.indexOf('Trident') >= 0);
	Edge = (ua.indexOf('Edge') >= 0);
	Firefox = (ua.indexOf('Firefox') >= 0);
}

function scanPlatform() : void {
	var os = window.navigator.appVersion;
console.log ("scanPlatform: " + os);
	WindowsOS = (os.indexOf('Win') >= 0);
	MacOS = (os.indexOf('Mac') >= 0) && ! Chrome;
	UnixOS = (os.indexOf('X11') >= 0) || (os.indexOf('Linux') >= 0);
}
