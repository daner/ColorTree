import {Component} from 'angular2/core';
import {ColorPicker} from './colorpicker'

@Component({
    selector: 'app',
    templateUrl: 'app.html',
    directives: [ColorPicker]
})

export class App { }
