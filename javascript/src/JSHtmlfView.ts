
///<reference path="JSHtmlView.ts"/>
///<reference path="TFileBased.ts"/>

class JSHtmlfView extends JSHtmlView {

	fContent = new TFileBased;

	toString() : string					{ return "JSHtmlfView"; }

	updateSpecial(obj: INScoreObject, oid: number)	: boolean {
        let address = obj.getOSCAddress();
        let pending = (): void => { inscore.postMessageStr (address, "refresh"); };
		if (this.fContent.getData (obj.getFile(), this.getElement(), pending)) 
			return super.updateSpecial (obj, oid);
		return false;
	}

	getText (infos: OTextInfo) : string {
		return this.fContent.get();
	}

}