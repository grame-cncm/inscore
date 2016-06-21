///<reference path="../globals.ts"/>
///<reference path="../vhtmlview/HtmlViewFactory.ts"/>
///<reference path="ICurve.ts"/>
///<reference path="IEllipse.ts"/>
///<reference path="IHtml.ts"/>
///<reference path="IImage.ts"/>
///<reference path="ILine.ts"/>
///<reference path="IPolygon.ts"/>
///<reference path="IRect.ts"/>
///<reference path="IScene.ts"/>
///<reference path="IText.ts"/>
///<reference path="ITextf.ts"/>
///<reference path="IGuidoCode.ts"/>
///<reference path="IGuidoPianoRoll.ts"/>
///<reference path="ISVG.ts"/>
///<reference path="Methods.ts"/>


class IObjectFactory {	
	static fViewFactory = new HtmlViewFactory();
    
	static createView(obj: IObject, parent?: VObjectView): void {
		if (gCreateView) {
			let view = this.fViewFactory.create (obj.getTypeString(), <VHtmlView>parent, obj.getName());
			obj.setView (view);
		}
    }
        
    static createObj (name: string , type: string, parent: IObject): IObject {
        let obj: IObject;
        switch (type) {
            case kEllipseType:
                obj = new IEllipse(name, parent);
                this.createView(obj, parent.getView());  
                break;
            
            case kRectType:
                obj = new IRect(name, parent);                
                this.createView(obj, parent.getView());    
                break;
                
            case kCurveType:
                obj = new ICurve(name, parent);                
                this.createView(obj, parent.getView());    
                break;
                
            case kLineType:
                obj = new ILine(name, parent);                
                this.createView(obj, parent.getView());    
                break;
                
            case kGuidoCodeType:
                obj = new IGuidoCode(name, parent); 
                this.createView(obj, parent.getView());    
                break;   
                
            case kGuidoPianoRollType:
                obj = new IGuidoPianoRoll(name, parent); 
                this.createView(obj, parent.getView());    
                break;                              
                   
            case kSceneType:
                obj = new IScene(name, parent);
                this.createView(obj);  
                break;
                
            case kPolygonType:
                obj = new IPolygon(name, parent);
                this.createView(obj, parent.getView());  
                break;
                
            case kTextType:
                obj = new IText(name, parent);
                this.createView(obj, parent.getView());  
                break;    
                
            case kTextfType:
                obj = new ITextf(name, parent);
                this.createView(obj, parent.getView());  
                break;    
                
            case kHtmlType:
                obj = new IHtml(name, parent);
                this.createView(obj, parent.getView());  
                break;    
                
            case kImgType:
                obj = new IImage(name, parent);
                this.createView(obj, parent.getView());  
                break;  

            case kVideoType:
                obj = new IVideo(name, parent);
                this.createView(obj, parent.getView());  
                break;    
                                  
            case kSvgType:
                obj = new ISVG(name, parent);
                this.createView(obj, parent.getView());  
                break;       
                          
            default:
                break;
        }


        /*else
            ITLErr << "unknown object type: " << type << ITLEndl;

        if (obj) {
            obj.setHandlers();
            obj.createVirtualNodes();
            obj.setVisible(IAppl.fDefaultShow);
        } */
        
        return obj; 
    }
}