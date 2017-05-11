
///<reference path="../controller/IMessage.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="IObject.ts"/>


var IProxy : IProxyInterface;

abstract class IProxyInterface {
	abstract execute (msg: IMessage, objName: string, parent: IObject): { status: eMsgStatus, obj?: IObject };
}
