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

    public randomizeColors(): void {
        this.http.post("/randomize", "").subscribe(result => { console.log(result); })
    }

    public loadFile(file: any): void {
        this.makeFileRequest("/load", file).then((result) => { console.log(result); });
    }

    private makeFileRequest(url: string, file: File): Promise<any> {
        return new Promise((resolve, reject) => {
            var formData: any = new FormData();
            formData.append("treeFile", file, file.name);
            var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = () => {
                if (xhr.readyState == 4) {
                    if (xhr.status == 200) {
                        resolve(JSON.parse(xhr.response));
                    } else {
                        reject(xhr.response);
                    }
                }
            }
            xhr.open("POST", url, true);
            xhr.send(formData);
        });
    }
}