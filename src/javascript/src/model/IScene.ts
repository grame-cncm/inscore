///<reference path="Methods.ts"/>
///<reference path="MethodsJS.ts"/>
///<reference path="IRectShape.ts"/>
///<reference path="../lib/TEnums.ts"/>

class IScene extends IRectShape {
    
        fPositionType         : ePosition;
        fPositionTypeModified : boolean;

    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.fTypeString = kSceneType;        
        this.fPositionType = ePosition.kRelatif;

        this.fPosition.setWidth (1);
        this.fPosition.setHeight (1);
        this.fMsgHandlerMap[knew_SetMethod] = new TMsgHandlerVoid(this._newScene());
        this.fMsgHandlerMap["redraw"]	= new TMsgHandlerVoid(this._redraw());
        this.fMsgHandlerMap[kposition_GetSetMethod] = new TMsgHandlerText(this._setPositionType());
        this.fGetMsgHandlerMap[kposition_GetSetMethod]  = new TGetMsgHandlerText(this._getPositionType());
    }

    static positionStr2Num(str: string): { correct: boolean, val: number } {
        switch (str) {
        	case "relatif": 	return { correct: true, val: ePosition.kRelatif }
        	case "absolute": 	return { correct: true, val: ePosition.kAbsolute }
        } 
        return { correct: false, val: 0 };
    }

    static positionNum2Str(n: number): { correct: boolean, val: string } {
        switch (n) {
        	case ePosition.kRelatif: 	return { correct: true, val: "relatif"  }
        	case ePosition.kAbsolute: 	return { correct: true, val: "absolute" }
        } 
        return { correct: false, val: "" };
    }

        // MODIFIED STATUS
        //--------------------------------------------------------------
    cleanup()             : void 		{ this.fPositionTypeModified = false; }
    positionTypeModified(): boolean 	{ return this.fPositionTypeModified;  }
    modify()              : void 		{ this.fPositionTypeModified = true;  }

   getPositionType()   : ePosition 				{ return this.fPositionType;}
    _getPositionType() : GetStringMethod 		{ return () => IScene.positionNum2Str(this.getPositionType()).val; }

    setPositionType (position : string): void 	{
        let type = IScene.positionStr2Num(position);
        if (!type.correct) { ITLError.badParameter("position", position);}
        else { this.fPositionType = type.val; this.modify();}}
    _setPositionType(): SetStringMethod 		{ return (type : string) => this.setPositionType(type) }

    getRScale(): number 		{ return this.fPosition.getScale(); }    
    getRSizeAsScale(): number 	{ return Math.min(this.fPosition.getWidth(), this.fPosition.getHeight()) / 2; }
    timeAble(): void 			{ }

    redraw(): void 				{ this.posPropagate(); }
    _redraw(): SetVoidMethod 	{ return () => this.redraw(); };

    newScene(): void 			{ }
    _newScene(): SetVoidMethod 	{ return () => this.newScene(); };
    
    getScene(): IObject 		{ return this; }
    getSet(): IMessage			{ return new IMessage(this.getOSCAddress(), knew_SetMethod); }
}