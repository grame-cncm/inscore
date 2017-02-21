
	function initComponent() {
		// Create a prototype for a new element that extends HTMLElement
		var inscoreProto = Object.create(HTMLElement.prototype);

		// Setup our Shadow DOM and clone the template for each element guido-viewer created
		inscoreProto.createdCallback = function() {
			root = this.createShadowRoot();
			processINScore (this.textContent);
		};

		var inscore = document.registerElement('inscore-code', {'prototype': inscoreProto});
	}
	
	function processINScore(text) {
		INScore.load (text);
//		INScore.postMessage ("/ITL/scene", ["redraw"]);
	}
	
	function start_inscore_code() {
		initComponent();
	};
