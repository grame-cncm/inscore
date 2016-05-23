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
///<reference path="Methods.ts"/>


class IObjectFactory {	
	static fViewFactory = new HtmlViewFactory();
    
	static createView(obj: IObject, parent?: VObjectView): void {
		if (gCreateView) {
			let view = this.fViewFactory.create (obj.getTypeString(), <VHtmlView>parent);
			obj.setView (view);
		}
    }
        
    static createObj (name: string , type: string, parent: IObject): IObject {
        let obj: IObject;
        switch (type) {
            case "ellipse":
                obj = new IEllipse(name, parent);
                this.createView(obj, parent.getView());  
                break;
            
            case "rect":
                obj = new IRect(name, parent);                
                this.createView(obj, parent.getView());    
                break;
                
            case "curve":
                obj = new ICurve(name, parent);                
                this.createView(obj, parent.getView());    
                break;
                
            case "line":
                obj = new ILine(name, parent);                
                this.createView(obj, parent.getView());    
                break;
                
            case "gmn":
                obj = new IGuidoCode(name, parent);                
                this.createView(obj, parent.getView());    
                break;                
                   
            case "scene":
                obj = new IScene(name, parent);
                this.createView(obj);  
                break;
                
            case "polygon":
                obj = new IPolygon(name, parent);
                this.createView(obj, parent.getView());  
                break;
                
            case "txt":
                obj = new IText(name, parent);
                this.createView(obj, parent.getView());  
                break;    
                
            case "txtf":
                obj = new ITextf(name, parent);
                this.createView(obj, parent.getView());  
                break;    
                
            case "html":
                obj = new IHtml(name, parent);
                this.createView(obj, parent.getView());  
                break;    
                
            case "img":
                obj = new IImage(name, parent);
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