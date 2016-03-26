import {Component} from 'angular2/core';

@Component({
    selector: 'admin',
    templateUrl: 'admin.html'
})
export class Admin {

    private filesToUpload: Array<File>;

    constructor() {
        this.filesToUpload = [];
    }

    public fileChanged(fileInput: any): void {
        this.filesToUpload = <Array<File>>fileInput.target.files;
    }

    public upload(): void {
        this.makeFileRequest("/load", [], this.filesToUpload).then((result) => {
            console.log(result);
        }, (error) => {
            console.error(error);
        });
    }

    private makeFileRequest(url: string, params: Array<string>, files: Array<File>): Promise<any> {
        return new Promise((resolve, reject) => {
            var formData: any = new FormData();
            var xhr = new XMLHttpRequest();
            for (var i = 0; i < files.length; i++) {
                formData.append("uploads[]", files[i], files[i].name);
            }
            xhr.onreadystatechange = function() {
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