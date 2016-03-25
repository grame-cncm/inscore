class SvgFactory {
    
    static createSvg(type: string): HTMLDivElement {
        var scene: HTMLDivElement = document.createElement('div');
        
        var svg = document.createElementNS('http://www.w3.org/2000/svg','svg');
        svg.setAttribute('xmlns', "http://www.w3.org/2000/svg");
        svg.setAttribute('xmlns:xlink', "http://www.w3.org/1999/xlink");
        svg.setAttribute('version', "1.1");
        svg.setAttribute('width', '200px');
        svg.setAttribute('height', '200px'); 
        
        
        
        switch (type) {
            case 'ellipse':
                var ellipse = document.createElementNS('http://www.w3.org/2000/svg','ellipse');
                ellipse.setAttribute('cx', '60');
                ellipse.setAttribute('cy', '60');
                ellipse.setAttribute('rx', '50');
                ellipse.setAttribute('ry', '20');
                svg.appendChild(ellipse);
                break;
                
            case 'rect':
                var rect = document.createElementNS('http://www.w3.org/2000/svg','rect');
                rect.setAttribute('x', '10');
                rect.setAttribute('y', '10');
                rect.setAttribute('height', '200');
                rect.setAttribute('width', '200');
                svg.appendChild(rect);
                break;
                
            case 'curve':
                var curve = document.createElementNS('http://www.w3.org/2000/svg','path');
                curve.setAttribute('d', 'M50,10 q50,10 50,200 t50,100');
                curve.setAttribute('stroke', '#1F56D2') 
                svg.appendChild(curve);
                break;
                
            case 'line':
                var line = document.createElementNS('http://www.w3.org/2000/svg','line');
                line.setAttribute('x1', '10');
                line.setAttribute('y1', '10');
                line.setAttribute('x2', '100');
                line.setAttribute('y2', '100');
                line.setAttribute('stroke', '#1F56D2') 
                svg.appendChild(line);
                break;
        
            default:
                break;
        }
    
        scene.appendChild(svg);
        return scene
    }    
}


        
       
