import {Component} from 'angular2/core';
import {ColorService} from './colorservice';

@Component({
    selector: 'colorpicker',
    templateUrl: 'colorpicker.html'
})
export class ColorPicker { 
       
    public constructor(private colorService: ColorService) {
      
    }
     
    public ngAfterViewInit(): void {
        var test = document.getElementById("colorCanvas");
        console.log(test);
        
        this.colorService.sendColor();
    } 
}