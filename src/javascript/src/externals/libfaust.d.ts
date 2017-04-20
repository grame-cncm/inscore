

declare var Module: any;

type TFaustFactory = any;

interface TFaustUIItem {
	type	: string;
	label	: string;
	address	: string;
	init	: number;
	min		: number;
	max		: number;
	step	: number;
}

interface TFaustUIElement {
	type	: string;
	label	: string;
	items	: Array<TFaustUIItem>;
}

interface TFaustJSONDesc {
	name 	: string;
	inputs	: number;
	outputs	: number;
	ui	: Array<TFaustUIElement>;
}


interface TAudioContext {
	destination: any;
	connect(dest: any): void;
	disconnect(dest: any): void;
}

interface TFaustDSP	extends TAudioContext { 
	setParamValue(address: string, val: number);
	json () : string;
	getNumInputs()	: number;
	getNumOutputs()	: number;
}

interface TFaustFactoryCallback		{ (factory: TFaustFactory): void; }
interface TFaustInstanceCallback	{ (dsp: TFaustDSP): void; }

interface TFaustLib {
	getErrorMessage() : string;
	createDSPFactory 	(dspcode: string, args: Array<string>, next: TFaustFactoryCallback) : void;
	createDSPInstance 	(factory: TFaustFactory, audio: TAudioContext, bufsize: number, next: TFaustInstanceCallback) : void;

	deleteDSPFactory	(factory: TFaustFactory) : void;
	deleteDSPInstance	(dsp: TFaustDSP) : void;
}

declare var faust: TFaustLib;
