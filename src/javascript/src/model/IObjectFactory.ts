///<reference path="../globals.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="../vhtmlview/HtmlViewFactory.ts"/>
///<reference path="IArc.ts"/>
///<reference path="ICurve.ts"/>
///<reference path="IDebug.ts"/>
///<reference path="IEllipse.ts"/>
///<reference path="IGuidoCode.ts"/>
///<reference path="IGuidoPianoRoll.ts"/>
///<reference path="IHtml.ts"/>
///<reference path="IImage.ts"/>
///<reference path="ILine.ts"/>
///<reference path="IPolygon.ts"/>
///<reference path="IRect.ts"/>
///<reference path="IScene.ts"/>
///<reference path="ISVG.ts"/>
///<reference path="ISVGf.ts"/>
///<reference path="ISync.ts"/>
///<reference path="IText.ts"/>
///<reference path="ITextf.ts"/>
///<reference path="IWebSocket.ts"/>
///<reference path="Methods.ts"/>

///<reference path="IObjectFactory-interface.ts"/>

class IObjectFactoryImpl extends IObjectFactoryInterface {	
	fViewFactory = new HtmlViewFactory();
    
	createView(obj: IObject): VObjectView {		// this is for the scene only
		let view = this.fViewFactory.create (obj.getTypeString(), null, obj.getName());
		view.setPositionHandler ( () : TPosition => { return obj.getPosition() });
		return view;
    }
	createViews(obj: IObject, parent: Array<VObjectView>): Array<VObjectView> {
		let out: Array<VObjectView> = []
		if (gCreateView) {
			for (var i=0; i < parent.length; i++) {
				let view = this.fViewFactory.create (obj.getTypeString(), <VHtmlView>parent[i], obj.getName());
				view.setPositionHandler ( () : TPosition => { return obj.getPosition() });
				out.push (view);
			}
//			obj.setView (view);
		}
		return out;
    }
        
    createObj (name: string , type: string, parent: IObject): IObject {
//        console.log("IObjetFactory createObj " + type);

        let obj: IObject;
        switch (type) {
        	case kDebugType:	return new IDebug(name, parent);
        	case kSyncType:		return new ISync(name, parent);
                      
            case kSceneType:	obj = new IScene(name, parent);
               					obj.setView (this.createView(obj));
               					return obj;
     		
            case kEllipseType:		obj = new IEllipse(name, parent);
                break;
            case kRectType:			obj = new IRect(name, parent);
                break;
            case kCurveType:		obj = new ICurve(name, parent);                
                break;
            case kLineType:			obj = new ILine(name, parent);                
                break;
            case kGuidoCodeType:	obj = new IGuidoCode(name, parent); 
                break;   
            case kGuidoPianoRollType:	obj = new IGuidoPianoRoll(name, parent); 
                break;                              
            case kPolygonType:		obj = new IPolygon(name, parent);
                break;
            case kTextType:			obj = new IText(name, parent);
                break;    
            case kTextfType:		obj = new ITextf(name, parent);
                break;    
            case kHtmlType:			obj = new IHtml(name, parent);
                break;                
            case kImgType:			obj = new IImage(name, parent);
                break;
            case kArcType:			obj = new IArc(name, parent);
                break;
            case kVideoType:		obj = new IVideo(name, parent);
                break;                                      
            case kSvgType:			obj = new ISVG(name, parent);
                break;  
            case kSvgfType:			obj = new ISVGf(name, parent);
                break;
            case kWebSocketType:	obj = new IWebSocket(name, parent);
                break;                        
                          
            default:
	            ITLError.write ( "IObjectFactory: unknown object type: " + type);
                return null;
        }

//        parent.getViews().forEach ( (pview: VObjectView): void => { obj.addView (this.createView (obj, pview)); } );
//        this.createView(obj, parent.getViews()); 
		obj.addViews (this.createViews (obj,  parent.getViews())); 
        return obj; 
    }
}

IObjectFactory = new IObjectFactoryImpl();
