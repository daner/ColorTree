import {Injectable} from 'angular2/core';
import {Http, HTTP_BINDINGS} from 'angular2/http';

@Injectable()
export class ColorService {
    constructor(private http: Http) {      
    }
    
    public sendColor(): void {
        console.log("Send color");
    }
}