
///<reference path="lib/TEnums.ts"/>
///<reference path="controller/IMessage.ts"/>

var INScore : INScoreInterface;

abstract class INScoreInterface {
	abstract version () : number;
	abstract start (scene?: string) : void;
	abstract checkStatus (status: eMsgStatus, msg: IMessage) : void;
	abstract postMessage (address: string, params: Array<any>) : void;
	abstract load (data: any): void;
	abstract register (elt : string): void;

}
