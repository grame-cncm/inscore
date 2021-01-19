
///<reference path="JSGMNView.ts"/>

class JSGMNStreamView extends JSGMNView {

	private fStream: GuidoStream = null;

	constructor(parent: JSObjectView, guido: GuidoEngine) {
		super(parent, guido);
		if (guido)
			this.fStream = guido.openStream();
	}

	clone (parent: JSObjectView) : JSObjectView { return new JSGMNStreamView(parent, this.guido()); }
	delete() : void	{ 
		this.guido().closeStream (this.fStream);
		this.fStream = null;
		super.delete();
	}

	toString() : string		    { return "JSGMNStreamView"; }
	string2Ar (obj: INScoreObject, gmn: string) : ARHandler { return this.guido().stream2AR (this.fParser, this.fStream); }

	updateSpecial(obj: INScoreObject, oid: number)	: boolean {
		if (!this.fStream) return false;

		let gmn = obj.getGuidoStream();
		if (gmn.reset) this.guido().resetStream(this.fStream);
		if (gmn.stream.length) this.guido().writeStream (this.fStream, gmn.stream);
		return super.updateSpecial (obj, oid);
    }

}
