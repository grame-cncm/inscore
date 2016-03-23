class SvgFactory {
    
    //EllIPSE    
    static createEllipse(): HTMLDivElement {
        var scene: HTMLDivElement = document.createElement('div');
        
        var svg = document.createElementNS('http://www.w3.org/2000/svg','svg');
        svg.setAttribute('xmlns', "http://www.w3.org/2000/svg");
        svg.setAttribute('xmlns:xlink', "http://www.w3.org/1999/xlink");
        svg.setAttribute('version', "1.1");
        svg.setAttribute('width', '200px');
        svg.setAttribute('height', '200px');
        
        var ellipse = document.createElementNS('http://www.w3.org/2000/svg','ellipse');
        ellipse.setAttribute('cx', '60');
        ellipse.setAttribute('cy', '60');
        ellipse.setAttribute('rx', '50');
        ellipse.setAttribute('ry', '20');
        ellipse.setAttribute("stroke", "black");
              
        svg.appendChild(ellipse);
        scene.appendChild(svg);

        return scene;    
    }
    
    // RECT
    static createRect(): HTMLDivElement {    
        var scene: HTMLDivElement = document.createElement('div');
       
        var svg = document.createElementNS('http://www.w3.org/2000/svg','svg');
        svg.setAttribute('xmlns', "http://www.w3.org/2000/svg");
        svg.setAttribute('xmlns:xlink', "http://www.w3.org/1999/xlink")
        svg.setAttribute('version', "1.1");
        svg.setAttribute('width', '200px');
        svg.setAttribute('height', '200px');
        
        var rect = document.createElementNS('http://www.w3.org/2000/svg','rect');
        rect.setAttribute('x', '10');
        rect.setAttribute('y', '10');
        rect.setAttribute('height', '200');
        rect.setAttribute('width', '200');
        rect.setAttribute("stroke", "black");
        
        svg.appendChild(rect);
        scene.appendChild(svg);   
        
        return scene;  
    }
    
    
    
}


        
       
