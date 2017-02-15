
///<reference path="lib/TEnums.ts"/>
///<reference path="controller/IMessage.ts"/>
///<reference path="model/IObject.ts"/>

abstract class INScoreInterface {
	abstract version () : number;
	abstract getRoot() : IObject;
	abstract start (scene?: string) : void;
	abstract checkStatus (status: msgStatus, msg: IMessage) : void;
	abstract postMessage (address: string, params: Array<any>) : void;
	abstract load (data: any): void;

}
