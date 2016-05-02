
///<reference path="IObject.ts"/>

class IRectShape extends IObject {

    constructor(name: string, parent: IObject) {
        super(name, parent);
    }

    create(name: string, parent: IObject): IRectShape { return new IRectShape(name, parent); }
    setHandlers() {  super.setHandlers(); }
   
    set(msg: IMessage): msgStatus {
        let status = super.set(msg);
       
        // Cas ou le type est différent, le proxy est utilisé dans super.set()
        if (status & (msgStatus.kProcessed + msgStatus.kProcessedNoChange)) return status; 

        // Vérification des paramêtres du message "set"
        if (msg.size() == 4) {
            let width = msg.paramNum(2), height = msg.paramNum(3);
            if (!width.correct || !height.correct) { return msgStatus.kBadParameters; }

            // Si les valeurs des attributs ne sont pas les mêmes
            if ( (width.value != this.fPosition.getWidth()) || (height.value != this.fPosition.getHeight()) ) {
                this.fPosition.setWidth(width.value);
                this.fPosition.setHeight(height.value);
                this.newData(true);
                status = msgStatus.kProcessed;
            }
            else status = msgStatus.kProcessedNoChange;
        }
        else status = msgStatus.kBadParameters;
        return status;
    }  

    getSet(): IMessage	{ 
    	return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, this.fPosition.getWidth(), this.fPosition.getHeight()]); 
    }
   
    //accept (Updater*): void
    // virtual MsgHandler::msgStatus set (const IMessage* msg);		
}