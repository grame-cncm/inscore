
///<reference path="../lib/TEnums.ts"/>
///<reference path="../controller/IMessage.ts"/>
///<reference path="Methods.ts"/>

class IEventAble {


    
    watch (msg:IMessage): eMsgStatus {
console.log ("IEventAble watch " + msg);
		return eMsgStatus.kProcessedNoChange;
    }

    event (msg:IMessage): eMsgStatus {
console.log ("IEventAble watch " + msg);
		return eMsgStatus.kProcessedNoChange;
    }

}
