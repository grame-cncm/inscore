

var Safari: boolean = false;
var Explorer: boolean = false;
var Edge: boolean = false;
var Firefox: boolean = false;
var Chrome: boolean = false;

function scanNavigator() : void {
	var ua = window.navigator.userAgent;
	Chrome = (ua.indexOf('Chrome') >= 0);
	Safari = (ua.indexOf('Safari') >= 0) && ! Chrome;
	Explorer = (ua.indexOf('MSIE ') >= 0) || (ua.indexOf('Trident') >= 0);;
	Edge = (ua.indexOf('Edge') >= 0);
	Firefox = (ua.indexOf('Firefox') >= 0);
}
