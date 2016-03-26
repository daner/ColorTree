import {Injectable} from 'angular2/core';
import {Http, Headers} from 'angular2/http';
import {Color} from './color';

@Injectable()
export class ColorService {
    constructor(private http: Http) {
    }

    public sendColor(color: Color): void {
        this.http.post("/color", JSON.stringify(color)).subscribe(result => { console.log(result); })
    }
}