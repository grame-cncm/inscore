
declare var verovio : any;

// Verovio objects are JSON strings
type VerovioObject 	=	string;
type VerovioOption 	=	{};

interface VerovioToolkit {
    constructor: VerovioToolkit;

	// Experimental method for editing the loaded data. Returns true on success and false otherwise.
	// edit(editorAction) boolean;

	// Returns a JSON object with all the notes that are being played as a certain time. 
	// This can be called only if renderToMidi has been called previously.
	getElementsAtTime(millisec: number) : VerovioObject;

	// Returns a JSON object with all the attributes for the element with the corresponding xmlId.
	getElementAttr(xmlId: string) : VerovioObject;

	// Returns the log message of the last performed operation, for example after having called loadData.
	getLog() : string;

	// Returns the MEI data loaded in the toolkit. 
	// If a page number is provide (i.e. > 0), then only that page is exported. 
	// In score-based MEI, then only the section element will be output. 
	// Set scoreBased to 1 for standard score-based MEI and 0 for the internal page-based MEI.
	getMEI(page: number, scoreBased: number): string;

	// Returns the number of pages. This can be called once the data has been loaded with loadData. 
	// Page numbering is 1-based.
	getPageCount(): number;

	// Returns the page (i.e., the screen) where the element with the passed xmlId currently is. 
	// The will change according to the page height and with when the layout is performed by the toolkit.
	getPageWithElement(xmlId: string): number;

	// Returns the time in millisecond at which a note is being played. 
	// This can be called only if renderToMidi has been called previously
	getTimeForElement(xmlId: string): number;

	// Returns the version of the toolkit (version number and git commit).
	getVersion(): string;

	// Loads the data passed as a parameter. 
	// The data is a string of the music encoding (e.g., the MEI encoding). 
	// The method also performs the layout if necessary or if requested. It does not render the data, 
	// this can be accomplished subsequently by calling renderPage. 
	// The data stays in memory until new data is loaded or until the toolkit instance is deleted.
	loadData(data: string): void;

	// Redo the layout of the entire file.
	// This has to be called for example when the size of the page (i.e., the screen) has changed.
	redoLayout(): void;

	// Loads and the data with the options passed as JSON object and renders the first page. 
	// This methods is a shortcut for loadData and then renderPage and is appropriate for rendering small data snippets. 
	// The data does stay in memory once loaded. Also, up to version 0.9.12, the JSON object had to be stringified.
	renderData(data: string, options?: VerovioOption): string;

	// Renders a page for the data loaded in the toolkit and returns it in SVG. 
	// The page numbering is 1-based. Options for rendering can be passed as JSON objects. 
	// The options affecting the layout (e.g., pageHeight, or ignoreLayout) cannot be modified when rendering a page 
	// and reloading the data if necessary for this. Also, up to version 0.9.12, the JSON object had to be stringified.
	renderPage(pageNumber, options: VerovioOption): string;

	// Renders a page to a base64 encoded MIDI file. There is currently not option to be passed to this method.
	renderToMidi(options: VerovioOption): string;

	// Sets the options as JSON for the toolkit instance. Up to version 0.9.12, the JSON object had to be stringified.
	setOptions(options: VerovioOption): void;
}
