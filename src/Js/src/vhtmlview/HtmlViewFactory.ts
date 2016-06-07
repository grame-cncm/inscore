
///<reference path="../view/ViewFactory.ts"/>
///<reference path="VHtmlCurveView.ts"/>
///<reference path="VHtmlEllipseView.ts"/>
///<reference path="VHtmlHtmlView.ts"/>
///<reference path="VHtmlImageView.ts"/>
///<reference path="VHtmlLineView.ts"/>
///<reference path="VHtmlRectView.ts"/>
///<reference path="VHtmlSceneView.ts"/>
///<reference path="VHtmlTextView.ts"/>
///<reference path="VHtmlGMNView.ts"/>
///<reference path="VHtmlSvgView.ts"/>
///<reference path="VHtmlView.ts"/>

class HtmlViewFactory implements ViewFactory {
    
    create (type: string, parent?: VHtmlView, name?: string): VObjectView {   
        switch (type) {
            case kEllipseType:
                return new VHtmlEllipseView (parent);
                            
            case kRectType:
                return new VHtmlRectView (parent);
                
            case kCurveType:
                return new VHtmlCurveView (parent);
                
            case kLineType:
                return new VHtmlLineView (parent);

            case kTextType:
            case kTextfType:
                return new VHtmlTextView (parent);

            case kHtmlType:
                return new VHtmlHtmlView (parent);
            
            case kSceneType:
                return new VHtmlSceneView (name);
            
            case kImgType:
                return new VHtmlImageView (parent);
                
            case kGuidoCodeType:
                    return new VHtmlGMNView (parent);

            case kSvgType:
                    return new VHtmlSvgView (parent);
                                    
            default:
                return null;
        }
    }  
}	
    
    
    