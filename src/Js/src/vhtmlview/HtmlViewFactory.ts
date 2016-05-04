
///<reference path="../view/ViewFactory.ts"/>
///<reference path="VHtmlView.ts"/>
///<reference path="VHtmlEllipseView.ts"/>
///<reference path="VHtmlSceneView.ts"/>
///<reference path="VHtmlRectView.ts"/>
///<reference path="VHtmlCurveView.ts"/>
///<reference path="VHtmlLineView.ts"/>
///<reference path="VHtmlTextView.ts"/>

class HtmlViewFactory implements ViewFactory {
    
    create (type: string, parent?: VHtmlView): VObjectView {   
        switch (type) {
            case "ellipse":
                return new VHtmlEllipseView (parent);
                            
            case "rect":
                return new VHtmlRectView (parent);
                
            case "curve":
                return new VHtmlCurveView (parent);
                
            case "line":
                return new VHtmlLineView (parent);

            case "txt":
                return new VHtmlTextView (parent);
            
            case "scene":
                return new VHtmlSceneView ();
                
            default:
                return null;
        }
    }  
}	
    
    
    