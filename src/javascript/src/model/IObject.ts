
///<reference path="../controller/TGetMessageHandlers.ts"/>
///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="../controller/TSetMessageHandlers.ts"/>
///<reference path="../externals/fraction.ts"/>
///<reference path="../scripting/TEnv.ts"/>
///<reference path="../inscore-interface.ts"/>
///<reference path="../lib/OSCAddress.ts"/>
///<reference path="../lib/OSCRegexp.ts"/>
///<reference path="../lib/Tools.ts"/>
///<reference path="../lib/TTypes.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="../lib/ITLOut.ts"/>
///<reference path="../mapping/TTime2GraphicMap.ts"/>
///<reference path="../view/VObjectView.ts"/>
///<reference path="../globals.ts"/>

///<reference path="Constants.ts"/>
///<reference path="IBrushStyle.ts"/>
///<reference path="IColor.ts"/>
///<reference path="IDate.ts"/>
///<reference path="IEffect.ts"/>
///<reference path="IEventAble.ts"/>
///<reference path="IObjectFactory-interface.ts"/>
///<reference path="IPenControl.ts"/>
///<reference path="IPosition.ts"/>
///<reference path="IProxyInterface.ts"/>
///<reference path="Methods.ts"/>
///<reference path="MethodsJS.ts"/>


class TMsgHandler<T> 			{ [index: string]: T; }
class TGetMsgHandler<T> 		{ [index: string]: T; }
interface Tree<T>				{ getSubNodes() : Array<Tree<T> >; } 
interface TApplyFunction<T> 	{ (arg: T) : void; }
interface TreeApply<T>			{ apply (f: TApplyFunction<T>, t: Tree<T>) : void; } 
interface IObjectTreeApply extends TreeApply<IObject> {}


//-------------------------------------------------------------- 
// IObject - the base class of inscore model
//-------------------------------------------------------------- 
class IObject implements Tree<IObject> {
    
// ATTRIBUTES
//-------------------------------------------------------------- 
    private   fState: 		eObjState;
    protected fTypeString:	string;
    protected fName: 		string;
    protected fNewData: 	boolean;
    protected fDelete: 		boolean;
    protected fLock: 		boolean;
    protected fParent: 		IObject;
    protected fObjectView:	VObjectView;
    protected fSubNodes: Array<IObject> = new Array;
    
    protected fMsgHandlerMap : 		TMsgHandler<TSetHandler>; 
    protected fGetMsgHandlerMap : 	TGetMsgHandler<TGetHandler>; 
    protected fGetMsgsHandlerMap : 	TGetMsgHandler<TGetMultiHandler>; 
    
    fPosition: 	 IPosition;
    fDate: 		 IDate;
    fColor: 	 IColor;
    fPenControl: IPenControl;
    fBrushStyle: IBrushStyle;
    fEffect:     IEffect;
    fEvents:	 IEventAble;
    fMapping:	 TTime2GraphicMap;
    fDebug:	 	 IObject;

// CONSTRUCTOR
//--------------------------------------------------------------       
    constructor(name: string, parent?: IObject) {
        this.fName = name;
        this.fTypeString = 'obj'; 
        
        this.fDelete = false;
        this.fLock = false;
        this.fState = eObjState.kNewObject;
        this.fNewData = true;        
        this.fParent = parent; 

        this.fPosition = new IPosition;
        this.fDate = new IDate;
		this.fColor = new IColor([0,0,0]);
        
        this.fPenControl = new IPenControl(kObjType);
        this.fBrushStyle = new IBrushStyle();
        this.fEffect     = new IEffect();
        this.fEvents     = new IEventAble();

        this.fMsgHandlerMap 	= new TMsgHandler<TSetHandler>();
		this.fGetMsgHandlerMap	= new TGetMsgHandler<TGetHandler>();
		this.fGetMsgsHandlerMap = new TGetMsgHandler<TGetMultiHandler>();
		this.fMsgHandlerMap["watch"] = null;			// !!! firefox hack
		this.fGetMsgHandlerMap["watch"] = null;			// !!! firefox hack
		this.fGetMsgsHandlerMap["watch"] = null;		// !!! firefox hack

        this.setHandlers();
        this.createStaticNodes();
        this.fEvents.attributes (this.fMsgHandlerMap);

        this.fMapping = new TTime2GraphicMap();
        let defaultTimeSegment = new TimeInterval (new Fraction(0,1), this.fDate.getDuration());
        let defaultGraphicSegment = new TGraphicSegment (new NumberInterval(0,1), new NumberInterval(0,1));
		this.fMapping.addElt ( new TTime2GraphicRelation(defaultTimeSegment, defaultGraphicSegment));
    }
    
    createStaticNodes() : void {
    	this.fDebug = IObjectFactory.createObj ("debug", kDebugType, this);
    	if (this.fDebug) this.addChild (this.fDebug);
    }

// HANDLERS
//--------------------------------------------------------------  
    setHandlers(): void {
        this.fMsgHandlerMap[kset_SetMethod] = new TMethodHandler( (msg: IMessage): eMsgStatus => { return this.set(msg); } );
        this.fMsgHandlerMap[kget_SetMethod] = new TMethodHandler( (msg: IMessage): eMsgStatus => { return this.get(msg); } );
        this.fMsgHandlerMap[ksave_SetMethod]= new TMethodHandler( (msg: IMessage): eMsgStatus => { return this.save(msg); } );
        this.fMsgHandlerMap[kdel_SetMethod] = new TMsgHandlerVoid( (): void => { this.del(); } );

 	    this.eventAble();
 	    this.colorAble();
	    this.positionAble();
	    this.timeAble();
        this.penControlAble();
        this.effectAble();
    }

    // intended for ILine : the target is always the pen color
    getColorTarget(): IColor 				{ return this.fColor; };
    
    eventAble(): void {
        this.fMsgHandlerMap[kwatch_GetSetMethod] 	= new TMethodHandler( (msg: IMessage): eMsgStatus => { return this.fEvents.watch (msg); } );
        this.fMsgHandlerMap[kevent_SetMethod] 		= new TMethodHandler( (msg: IMessage): eMsgStatus => { return this.fEvents.event (msg); } );
        this.fMsgHandlerMap[kpush_SetMethod] 		= new TMsgHandlerVoid( (): void => { this.fEvents.push (); } );
        this.fMsgHandlerMap[kpop_SetMethod] 		= new TMsgHandlerVoid( (): void => { this.fEvents.pop (); } );

        this.fGetMsgsHandlerMap[kwatch_GetSetMethod] = new TGetMsgsHandler( (): IMessageList => { let osc= this.getOSCAddress(); return this.fEvents.getWatch(osc); } );
    }
    
    colorAble(): void {
        let target = this.getColorTarget();
        this.fMsgHandlerMap[kcolor_GetSetMethod] 		= new TMsgHandlerColor( (a: Array<number>): void => { target.setRGB(a); } );
        this.fMsgHandlerMap[khsb_SetMethod] 			= new TMsgHandlerColor( (a: Array<number>): void => { target.setHSB(a); } );
        this.fMsgHandlerMap[kred_GetSetMethod] 			= new TMsgHandlerNum( (n: number): void => { target.setR(n); } );
	    this.fMsgHandlerMap[kgreen_GetSetMethod] 		= new TMsgHandlerNum( (n: number): void => { target.setG(n); } );
	    this.fMsgHandlerMap[kblue_GetSetMethod]			= new TMsgHandlerNum( (n: number): void => { target.setB(n); } );
        this.fMsgHandlerMap[kalpha_GetSetMethod] 		= new TMsgHandlerNum( (n: number): void => { target.setA(n); } );
	    this.fMsgHandlerMap[khue_GetSetMethod] 			= new TMsgHandlerNum( (n: number): void => { target.setH(n); } );
	    this.fMsgHandlerMap[ksaturation_GetSetMethod]	= new TMsgHandlerNum( (n: number): void => { target.setS(n); } );
        this.fMsgHandlerMap[kbrightness_GetSetMethod]	= new TMsgHandlerNum( (n: number): void => { target.setV(n); } );

        this.fMsgHandlerMap[kdred_SetMethod] 			= new TMsgHandlerNum( (n: number): void => { target.dR(n); } );
	    this.fMsgHandlerMap[kdgreen_SetMethod] 			= new TMsgHandlerNum( (n: number): void => { target.dG(n); } );
	    this.fMsgHandlerMap[kdblue_SetMethod]			= new TMsgHandlerNum( (n: number): void => { target.dB(n); } );
        this.fMsgHandlerMap[kdalpha_SetMethod] 			= new TMsgHandlerNum( (n: number): void => { target.dA(n); } );
	    this.fMsgHandlerMap[kdhue_SetMethod] 			= new TMsgHandlerNum( (n: number): void => { target.dH(n); } );
	    this.fMsgHandlerMap[kdsaturation_SetMethod]		= new TMsgHandlerNum( (n: number): void => { target.dS(n); } );
        this.fMsgHandlerMap[kdbrightness_SetMethod]		= new TMsgHandlerNum( (n: number): void => { target.dV(n); } );

        this.fGetMsgHandlerMap[kcolor_GetSetMethod] 	= new TGetMsgHandlerArray( (): Array<number> => { return target.getRGB(); } );
        this.fGetMsgHandlerMap[khsb_SetMethod] 			= new TGetMsgHandlerArray( (): Array<number> => { return target.getHSB(); } );
        this.fGetMsgHandlerMap[kred_GetSetMethod] 		= new TGetMsgHandlerNum( (): number => { return target.getR(); } );
        this.fGetMsgHandlerMap[kgreen_GetSetMethod] 	= new TGetMsgHandlerNum( (): number => { return target.getG(); } );
	    this.fGetMsgHandlerMap[kblue_GetSetMethod] 		= new TGetMsgHandlerNum( (): number => { return target.getB(); } );
        this.fGetMsgHandlerMap[kalpha_GetSetMethod] 	= new TGetMsgHandlerNum( (): number => { return target.getA(); } );
        this.fGetMsgHandlerMap[khue_GetSetMethod] 		= new TGetMsgHandlerNum( (): number => { return target.getH(); } );
	    this.fGetMsgHandlerMap[ksaturation_GetSetMethod] = new TGetMsgHandlerNum( (): number => { return target.getS(); } );
	    this.fGetMsgHandlerMap[kbrightness_GetSetMethod] = new TGetMsgHandlerNum( (): number => { return target.getV(); } );    
    }
    
    positionAble() {
        this.fMsgHandlerMap[kx_GetSetMethod] 		= new TMsgHandlerNum( (n: number): void => { this.fPosition.setXPos(n); });
        this.fMsgHandlerMap[ky_GetSetMethod] 		= new TMsgHandlerNum( (n: number): void => { this.fPosition.setYPos(n); });
        this.fMsgHandlerMap[kxorigin_GetSetMethod] 	= new TMsgHandlerNum( (n: number): void => { this.fPosition.setXOrigin(n); });
        this.fMsgHandlerMap[kyorigin_GetSetMethod] 	= new TMsgHandlerNum( (n: number): void => { this.fPosition.setYOrigin(n); });
        this.fMsgHandlerMap[kz_GetSetMethod] 		= new TMsgHandlerNum( (n: number): void => { this.fPosition.setZOrder(n); });
        this.fMsgHandlerMap[kangle_GetSetMethod] 	= new TMsgHandlerNum( (n: number): void => { this.fPosition.setRotateZ(n); });
        this.fMsgHandlerMap[kscale_GetSetMethod] 	= new TMsgHandlerNum( (n: number): void => { this.setScale(n); });
        this.fMsgHandlerMap[krotatex_GetSetMethod] 	= new TMsgHandlerNum( (n: number): void => { this.fPosition.setRotateX(n); }); 
        this.fMsgHandlerMap[krotatey_GetSetMethod] 	= new TMsgHandlerNum( (n: number): void => { this.fPosition.setRotateY(n); }); 
        this.fMsgHandlerMap[krotatez_GetSetMethod] 	= new TMsgHandlerNum( (n: number): void => { this.fPosition.setRotateZ(n); }); 
        this.fMsgHandlerMap[kshear_GetSetMethod] 	= new TMsgHandlerNumArray( (a: Array<number>): eMsgStatus => { return this.fPosition.setShear(a); });

        this.fMsgHandlerMap[kdx_SetMethod] 			= new TMsgHandlerNum( (n: number): void => { this.fPosition.addXPos(n); });
        this.fMsgHandlerMap[kdy_SetMethod] 			= new TMsgHandlerNum( (n: number): void => { this.fPosition.addYPos(n); });
        this.fMsgHandlerMap[kdxorigin_SetMethod] 	= new TMsgHandlerNum( (n: number): void => { this.fPosition.addXOrigin(n); });
        this.fMsgHandlerMap[kdyorigin_SetMethod] 	= new TMsgHandlerNum( (n: number): void => { this.fPosition.addYOrigin(n); });
        this.fMsgHandlerMap[kdz_SetMethod] 			= new TMsgHandlerNum( (n: number): void => { this.fPosition.addZOrder(n); });
        this.fMsgHandlerMap[kdangle_SetMethod] 		= new TMsgHandlerNum( (n: number): void => { this.fPosition.addAngle(n); });
        this.fMsgHandlerMap[kdscale_SetMethod] 		= new TMsgHandlerNum( (n: number): void => { this.fPosition.multScale(n); });
        this.fMsgHandlerMap[kdrotatex_SetMethod]    = new TMsgHandlerNum( (n: number): void => { this.fPosition.addXAngle(n); });
        this.fMsgHandlerMap[kdrotatey_SetMethod]    = new TMsgHandlerNum( (n: number): void => { this.fPosition.addYAngle(n); });
        this.fMsgHandlerMap[kdrotatez_SetMethod]    = new TMsgHandlerNum( (n: number): void => { this.fPosition.addAngle(n); });
        this.fMsgHandlerMap[kshow_GetSetMethod]		= new TMsgHandlerNum( (n: number): void => { this.fPosition.setVisible(n); });

        this.fGetMsgHandlerMap[kx_GetSetMethod]			= new TGetMsgHandlerNum( (): number => { return this.fPosition.getXPos(); });
        this.fGetMsgHandlerMap[ky_GetSetMethod]			= new TGetMsgHandlerNum( (): number => { return this.fPosition.getYPos(); });
        this.fGetMsgHandlerMap[kxorigin_GetSetMethod]	= new TGetMsgHandlerNum( (): number => { return this.fPosition.getXOrigin(); });
        this.fGetMsgHandlerMap[kyorigin_GetSetMethod]	= new TGetMsgHandlerNum( (): number => { return this.fPosition.getYOrigin(); });
        this.fGetMsgHandlerMap[kz_GetSetMethod]			= new TGetMsgHandlerNum( (): number => { return this.fPosition.getZOrder(); });
        this.fGetMsgHandlerMap[kangle_GetSetMethod]		= new TGetMsgHandlerNum( (): number => { return this.fPosition.getRotateZ(); });
        this.fGetMsgHandlerMap[kscale_GetSetMethod]		= new TGetMsgHandlerNum( (): number => { return this.fPosition.getScale(); });
        this.fGetMsgHandlerMap[kshow_GetSetMethod]		= new TGetMsgHandlerNum( (): number => { return this.fPosition.getVisible(); });
        this.fGetMsgHandlerMap[kwidth_GetSetMethod]		= new TGetMsgHandlerNum( (): number => { return this.fPosition.getWidth(); });
        this.fGetMsgHandlerMap[kheight_GetSetMethod] 	= new TGetMsgHandlerNum( (): number => { return this.fPosition.getHeight(); });
        this.fGetMsgHandlerMap[krotatex_GetSetMethod]	= new TGetMsgHandlerNum( (): number => { return this.fPosition.getRotateX(); });
        this.fGetMsgHandlerMap[krotatey_GetSetMethod]	= new TGetMsgHandlerNum( (): number => { return this.fPosition.getRotateY(); });
        this.fGetMsgHandlerMap[krotatez_GetSetMethod]	= new TGetMsgHandlerNum( (): number => { return this.fPosition.getRotateZ(); });
        this.fGetMsgHandlerMap[kshear_GetSetMethod]	 	= new TGetMsgHandlerArray( (): Array<number> => { return this.fPosition.getShear(); });
    }
    
    timeAble() {
        this.fMsgHandlerMap[kdate_GetSetMethod] 	= new TMsgHandlerTime( (d: Fraction): void => { this.setDate(d); });
        this.fMsgHandlerMap[kduration_GetSetMethod]	= new TMsgHandlerTime( (d: Fraction): void => { this.setDuration(d); });
        this.fMsgHandlerMap[kddate_SetMethod] 		= new TMsgHandlerTime( (d: Fraction): void => { this.addDate(d); });
        this.fMsgHandlerMap[kdduration_SetMethod] 	= new TMsgHandlerTime( (d: Fraction): void => { this.addDuration(d); });        
        this.fMsgHandlerMap[kclock_SetMethod] 		= new TMsgHandlerVoid( (): void => { this.clock(); });
        this.fMsgHandlerMap[kdurClock_SetMethod] 	= new TMsgHandlerVoid( (): void => { this.durclock(); });
        this.fMsgHandlerMap[ktempo_GetSetMethod] 	= new TMsgHandlerNum ( (n: number): void => { this.fDate.setTempo(n); });
        this.fMsgHandlerMap[kdtempo_SetMethod] 	    = new TMsgHandlerNum ( (n: number): void => { this.fDate.addTempo(n); });

        this.fGetMsgHandlerMap[ktempo_GetSetMethod] 	= new TGetMsgHandlerNum ( (): number =>   { return this.fDate.getTempo(); });
        this.fGetMsgHandlerMap[kduration_GetSetMethod] 	= new TGetMsgHandlerTime( (): Fraction => { return this.fDate.getDuration(); });
        this.fGetMsgHandlerMap[kdate_GetSetMethod] 		= new TGetMsgHandlerTime( (): Fraction => { return this.fDate.getDate(); });
    }

    penControlAble() {
        this.fMsgHandlerMap[kpenWidth_GetSetMethod]     = new TMsgHandlerNum  ( (n: number): void => { this.fPenControl.setPenWidth(n); });
        this.fMsgHandlerMap[kpenColor_GetSetMethod] 	= new TMsgHandlerColor( (c: Array<number>): void => { this.fPenControl.setPenColor(new IColor(c)); });
        this.fMsgHandlerMap[kpenStyle_GetSetMethod] 	= new TMsgHandlerText ( (s: string): void => { this.fPenControl.setPenStyle(s); });
        this.fMsgHandlerMap[kpenAlpha_GetSetMethod] 	= new TMsgHandlerNum  ( (n: number): void => { this.fPenControl.setPenAlpha(n); });

        this.fGetMsgHandlerMap[kpenWidth_GetSetMethod] 	= new TGetMsgHandlerNum  ( (): number 		=> { return this.fPenControl.getPenWidth(); });
        this.fGetMsgHandlerMap[kpenColor_GetSetMethod] 	= new TGetMsgHandlerArray( (): Array<number> => { return this.fPenControl.getPenColor().getRGB(); });
        this.fGetMsgHandlerMap[kpenStyle_GetSetMethod] 	= new TGetMsgHandlerText ( (): string 		=> { return this.fPenControl.getPenStyle(); });
        this.fGetMsgHandlerMap[kpenAlpha_GetSetMethod]  = new TGetMsgHandlerNum  ( (): number 		=> { return this.fPenControl.getPenAlpha(); });
    }
    
    brushAble() {
        this.fGetMsgHandlerMap[kbrushStyle_GetSetMethod] = new TGetMsgHandlerText( (): string 		=> { return this.fBrushStyle.getBrushStyleStr(); });
        this.fMsgHandlerMap[kbrushStyle_GetSetMethod]    = new TMsgHandlerText	 ( (s: string): void => { this.fBrushStyle.setBrushStyle(s); } );
	}

	effectAble(){
        this.fGetMsgHandlerMap[keffect_GetSetMethod]     = new TGetMsgHandlerArray( () : Array<any> => { return this.fEffect.getEffect(); } );
        this.fMsgHandlerMap[keffect_GetSetMethod]        = new TMsgHandlerAnyArray( (e: Array<any>) : eMsgStatus => { return this.fEffect.setEffect(e); } )
    }
    
//--------------------------------------------------------------  
// Special handlers
//--------------------------------------------------------------  
// size change requires the modification state to be 
// recursively propagated to all subnodes
//--------------------------------------------------------------  
	setWidth (width: number) : void { this.fPosition.setWidth( width ); this.posPropagate(); }
	setHeight(height:number): void 	{ this.fPosition.setHeight( height); this.posPropagate(); }
    setScale (scale:number): void 	{ this.fPosition.setScale( scale); this.posPropagate(); }
	posPropagate() : void 			{ let a = new IObjectTreeApply(); a.applyPosModified(this); }
	posModified() : void 			{ this.fPosition.modify(); this.addState (eObjState.kModified + eObjState.kSubModified); }
//-------------------------------------------------------------- 
// decorate date and duration messages to handle time events
//--------------------------------------------------------------  
	setDate(d: Fraction) : void 	{ let previous = this.fDate.getDate(); this.fDate.setDate(d); this.fEvents.handleTimeChange(previous, this.fDate.getDate()); }
	addDate(d: Fraction) : void 	{ let previous = this.fDate.getDate(); this.fDate.addDate(d); this.fEvents.handleTimeChange(previous, this.fDate.getDate());  }
	clock() : void					{ let previous = this.fDate.getDate(); this.fDate.clock(); this.fEvents.handleTimeChange(previous, this.fDate.getDate()); }
	setDuration(d: Fraction) : void { let previous = this.fDate.getDuration(); this.fDate.setDuration(d); this.fEvents.handleDurChange(previous, this.fDate.getDuration()); }
	addDuration(d: Fraction) : void { let previous = this.fDate.getDuration(); this.fDate.addDuration(d); this.fEvents.handleDurChange(previous, this.fDate.getDuration()); }
	durclock() : void				{ let previous = this.fDate.getDuration(); this.fDate.durclock(); this.fEvents.handleDurChange(previous, this.fDate.getDuration()); }   

//-------------------------------------------------------------- 
// UI events management
//--------------------------------------------------------------  
	hasUIEvents (): number 										{ return this.fEvents.hasUIEvents(); }
	handleMouseEvent (type: eUIEvents, mouse: TMouseEnv, date: Fraction) : void	{ 
		let env = new TEnv (this.getOSCAddress(), mouse, this.fDate.getDate(), date);
		this.fEvents.handleMouseEvent (type, env); 
	}
	mapPoint2Date (point: TPosition) : Fraction				{ return this.fMapping.mapPoint2Date (point); }
    
// METHODS
//--------------------------------------------------------------  
    addChild(obj: IObject): void { 
        this.fSubNodes.push(obj);
        this.addState(eObjState.kSubModified);
    } 
    
    setParent(parent: IObject): void { this.fParent = parent; }    
    getParent(): IObject 			{ return this.fParent; }    
    getSubNodes(): Array<IObject> 	{ return this.fSubNodes }
    getSubNodesCount(): number 		{ return this.fSubNodes.length; }
    getAppl() : IObject				{ return this.fParent.getAppl(); }
    getScene(): IObject 			{ return this.fParent.getScene(); }
	// get the object scale recursively
    getRScale(): number 			{ return this.fPosition.getScale() * this.fParent.getRScale(); }
	// get the object size as scale recursively - takes account of the smallest dimension
    getRSizeAsScale(): number 		{ 
    	let size = Math.min(this.fPosition.getWidth(), this.fPosition.getHeight()); 
    	return size / 2 * this.fParent.getRSizeAsScale(); 
    }

    getPosition(): {x: number, y: number } 		     { return { x: this.fPosition.getXPos(), y: this.fPosition.getYPos() }; }
    getSize():     {w: number, h: number } 			 { return { w: this.fPosition.getWidth(), h: this.fPosition.getHeight() }; }
    getRotate():   {x: number, y: number, z: number} { return { x: this.fPosition.getRotateX(), y: this.fPosition.getRotateY(), z: this.fPosition.getRotateZ() }; }

    toString(): string 				{ 
    	let n=this.fSubNodes.length; 
    	let substr = ""; 
    	if (n) substr= " [" + this.fSubNodes + "] "; 
    	return this.fName + substr; 
    }
   
    //-----------------------------    
    getName(): string 				{ return this.fName; }
    getTypeString(): string 		{ return this.fTypeString; }        
    
    
    //-----------------------------
    match(address: string): boolean  {
        let re = new OSCRegexp(address);
        return re.match (this.fName);
    }

    find(expr: string): Array<IObject> {
        if (!Tools.regexp(expr))
            return this.exactfind(expr);

		let re = new OSCRegexp(expr);
		let out: Array<IObject> = [];
		this.fSubNodes.forEach ( function (obj: IObject) 
			{ if (!obj.getDeleted() && re.match(obj.fName)) out.push(obj); } );
        return out;
    }
    
    //-----------------------------
    exactfind(name:string): Array<IObject> {
        let out: Array<IObject> = [];
        this.fSubNodes.forEach ( function (obj: IObject) 
        	{ if (!obj.getDeleted() && (obj.fName == name)) out.push(obj); } );
        return out;
    }
    
    //-----------------------------    
    newData     (state: boolean): void  { this.fNewData = state; /*triggerEvent(kNewData, true)*/; }
    isNewData   (): boolean             { return this.fNewData; }
    
    setState (s: eObjState): void 	{ this.fState = s; }
    addState (s: eObjState): void 	{ this.fState |= s; }
    getState(): eObjState 			{ return this.fState; }
    
    getPos(): IPosition 		{ return this.fPosition; }
    getColor(): IColor 			{ return this.fColor; }
    getOSCAddress(): string 	{ return this.fParent.getOSCAddress() + "/" + this.fName; }

    transferAttributes(dest: IObject): IObject {
        dest.fPosition.set	( this.fPosition );
        dest.fColor.set 	( this.fColor );
        dest.fDate.set 		( this.fDate );

        //dest.fPosition.setPenWidth(getPenWidth());
        //dest.fPosition.setPenColor(getPenColor());
        //dest.fPosition.setPenStyle(getPenStyle());
        return dest;
    }   

    // View
    //-----------------------------    
    setView(view: VObjectView): void 	{ this.fObjectView = view }
    getView(): VObjectView 				{ return this.fObjectView }
    
    //-----------------------------
    execute (msg: IMessage): eMsgStatus {
    	if (msg.size() == 0) return eMsgStatus.kBadParameters;
    	let method = msg.message();
    	if (method.correct) {
       		let handler = this.messageHandler(method.value);
        	if (handler) { 
        		let status = handler.handle(msg);
        		if (status & (eMsgStatus.kProcessed | eMsgStatus.kProcessedNoChange))
        			this.fEvents.handleAttributeChange (method.value);
				return status;
        	}

	        //handler = this.messageHandler(msg.message(), true);
	        //if (handler) return ;

	        //handler = this.messageHandler("*");
	        //if (handler) return ;
	        //return eMsgStatus.kBadParameters;		
    	}
    	else {			// sig handler 
    	}
		return eMsgStatus.kBadParameters;
    }
    
    //-----------------------------
    messageHandler(msg: string, match?: boolean): TSetHandler {
        let handler: TSetHandler;
        if (!match) {
            return this.fMsgHandlerMap[msg]; 
        }
        
        /*else {
            msgMatchPredicat p(msg);
            map<string, SMsgHandler>::const_iterator h = find_if(this.fMsgHandlerMap.begin(), this.fMsgHandlerMap.end(), p);
            if (h != this.fMsgHandlerMap.end()) handler = h.second;
        }*/       
        return handler;
    }
    
// MESSAGES PROCESSING
//--------------------------------------------------------------     
// get objects by OSC address
//--------------------------------------------------------------     
	// find objects that match an osc address
	// the address is provide as a head and a tail
	// tail is shifted to the left for subnodes
    //-----------------------------
	getTargetObjects (osc: TPair<string>): Array<IObject> {

		let out: Array<IObject> = [];
		if ( this.match(osc.first) ) {			// is the address on my branch ?
			osc = OSCAddress.shift (osc.second);
			if (osc.second.length) {			// tail is not empty
				this.fSubNodes.forEach ( function (obj: IObject) 
					{ out = out.concat (obj.getTargetObjects (osc)); } );
			}
			else out = out.concat (this.find (osc.first));
		}
		return out;
	}

//--------------------------------------------------------------     
    process (msg: IMessage): eMsgStatus {
		let osc = OSCAddress.shift (msg.address());
		return this.processMsg(osc.first, osc.second, msg);
    }

    processMsg (head: string, tail: string , msg: IMessage): eMsgStatus {

        let result: number = eMsgStatus.kBadAddress;
        if (this.match(head)) {
            let osc = OSCAddress.shift (tail);
            if (osc.second.length)
                this.fSubNodes.forEach ( function (obj: IObject) { result |= obj.processMsg (osc.first, osc.second, msg);} );
            else {										
                let targets = this.find (osc.first);
                let n = targets.length;
                if (n) {
                	targets.forEach( function (obj: IObject) { 
                			result |= obj.execute(msg); 
                			if (result & eMsgStatus.kProcessed) obj.addState(eObjState.kModified);
                		} );
                }               
                else if (Tools.regexp(osc.first)) { result = eMsgStatus.kProcessedNoChange; }                    
                else  { result = this.proxy_create (msg, osc.first, this).status; }
            }
        }
            
        if (result & (eMsgStatus.kProcessed + eObjState.kSubModified)) { this.addState(eObjState.kSubModified); }
    	return result;     
    }

    //-------------------------------------------------------------
    // the basic 'set' handler
    //-------------------------------------------------------------
    set(msg: IMessage): eMsgStatus	{
        let type = msg.paramStr(1);
        if (!type.correct) { return eMsgStatus.kBadParameters; }

        if (type.value != this.getTypeString()) {
			let out = this.proxy_create (msg, this.fName, this.getParent());
            if (out.status & eMsgStatus.kProcessed) {
	            // todo: transfer this attributes to new object
	            this.transferAttributes (out.obj);
//				this.fParent.cleanupSync();
            	this.del();
                return out.status;		
            }
            
            return eMsgStatus.kProcessedNoChange;
        }
        return eMsgStatus.kBadParameters;
    }
    
    //-------------------------------------------------------------
    // internal 'get' : gives a messagelist as output
    //-------------------------------------------------------------
    getCall(msg: IMessage): IMessageList {
    	let out: IMessageList = [];

        let n = msg.size();
        if ( n == 1 ) {
	    	let msg =  this.getSet ();			// get without param should give a 'set' msg	    
        	if (msg) out.push (msg);
        }
        else for (let i=1; i< n; i++) {
        	let attribute = msg.paramStr(i);
        	if (attribute.correct)
        		out = out.concat (this.get1AttributeMsg (attribute.value));
        	else ITLError.badParameter (msg.toString(), msg.param(i));
        }
        return out;
    }

    //-------------------------------------------------------------
    // the basic 'get' handler
    //-------------------------------------------------------------
     get(msg: IMessage): eMsgStatus {
        let msgs = this.getCall (msg);
        msgs.forEach ( function(msg: IMessage) { ITLOut.write (msg.toString() + ";" ); } );
        return eMsgStatus.kProcessedNoChange;
    }
    
    //-------------------------------------------------------------
    // the 'save' handler
    //-------------------------------------------------------------
    save(msg: IMessage): eMsgStatus {
    	let msgs = this.getSetRecurse();
     	msgs.forEach ( function(msg: IMessage) { ITLOut.write (msg.toString() + ";" ); } );
    	return eMsgStatus.kProcessedNoChange;
    }

    //-------------------------------------------------------------
    // the specific 'get' methods - must be implemented by inherited objects
    //-------------------------------------------------------------
    getSet(): IMessage		{ return null; };
      
    //-------------------------------------------------------------
    // get 1 message for 1 attribute
    get1AttributeMsg(attribute: string): IMessageList {
        let h = this.fGetMsgHandlerMap[attribute];
        if (h) { 
        	let msg = new IMessage (this.getOSCAddress(), attribute);
        	h.fill (msg);
        	return [msg];
        }
    	let hm = this.fGetMsgsHandlerMap[attribute];
        if (hm) return hm.getMsgs ();
        return [];
    }

    //-------------------------------------------------------------
    // get a message for all attributes
    getAttributesMsg(): IMessageList {
    	let out = new IMessageList();
		for (let key in this.fMsgHandlerMap) {
			let msg = this.get1AttributeMsg(key);
	    	if (msg) out = out.concat (msg);
		}
		return out;
    }

    //-------------------------------------------------------------
    // get objects state messages recursively
    getSetRecurse(): IMessageList {
    	let out = new IMessageList();
    	let msg =  this.getSet ();			// get the 'set' msg first
    	if (msg) out.push (msg);			// and push to the output list
    	let p = this.getAttributesMsg();	// next all the messages for the object attributes
	    for (let i=0; i < p.length; i++)
		    out.push (p[i]);
    	
        let n 	 = this.getSubNodesCount();	
		for (let i = 0; i < n; i++) {		// and propagate to the subnodes
	    	let subout = this.fSubNodes[i].getSetRecurse ();
	    	for (let i=0; i < subout.length; i++)
		    	out.push (subout[i]);
		}
		return out;
    }
 
    //-----------------------------    
    protected proxy_create (msg: IMessage, name: string, parent: IObject): { status: eMsgStatus, obj?: IObject } 
    				{ return IProxy.execute (msg, name, parent); }         
    
    //-----------------------------    
    getDeleted(): boolean 	{ return this.fDelete; }
    del(): void {
    	this.fDelete = true;
        if (this.getView()) this.getView().remove();
        let array = this.fParent.getSubNodes();
        array.splice(array.indexOf(this), 1);
    }

	//-----------------------------    
	cleanup() : void { 
		this.fPosition.cleanup(); 
		this.fDate.cleanup(); 
		this.fColor.cleanup();
		this.fPenControl.cleanup();
		this.setState(eObjState.kClean);
        this.fBrushStyle.cleanup();
        this.fEffect.cleanup();
		if (this.fDate.getTempo()) this.move();
    }

	//-----------------------------    
	move(): void {  INScore.postMessage (this.getOSCAddress(), [kddate_SetMethod, gINScoreRealRate * this.fDate.getTempo(), 60000 * 4]); }


	//-----------------------------    
	static timeTaskCleanup(obj: IObject) : void { 
		let state = obj.getState();
		if (state & (eObjState.kNewObject + eObjState.kModified)) obj.cleanup();		
		if (state & eObjState.kSubModified) {
			obj.setState (eObjState.kClean);
			let nodes = obj.getSubNodes();
			for (let i=0; i<nodes.length; i++) {
				IObject.timeTaskCleanup(nodes[i]);
			}
		}
	}
}

class IObjectTreeApply implements TreeApply<IObject> {
	apply (f: TApplyFunction<IObject>, t: IObject) {
		f (t);
		let sub = t.getSubNodes();
		for (let i=0; i<sub.length; i++)
			this.apply (f, sub[i]);
	}
	cleanup (t: IObject) : void 			{ t.cleanup(); }
	applyCleanup (t: IObject): void 		{ this.apply ((o) => this.cleanup (o), t); }
	posModified (t: IObject) : void 		{ t.posModified(); }
	applyPosModified (t: IObject): void 	{ this.apply ((o) => this.posModified (o), t); }
}
