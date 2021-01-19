
///<reference path="VObjectView.ts"/>

interface ViewFactory {
    create (type: string, parent?: VObjectView, name?: string): VObjectView;
}	
    
    
    