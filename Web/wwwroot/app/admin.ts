import {Component} from 'angular2/core';
import {ColorService} from './colorservice';

@Component({
    selector: 'admin',
    templateUrl: 'admin.html'
})
export class Admin {

    private filesToUpload: Array<File>;

    constructor(private colorservice: ColorService) {
        this.filesToUpload = [];
    }

    public fileChanged(fileInput: any): void {
        this.filesToUpload = <Array<File>>fileInput.target.files;
    }

    public upload(): void {
        if (this.filesToUpload.length > 0) {
            this.colorservice.loadFile(this.filesToUpload[0]);
        }
    }

    public randomize(): void {
        this.colorservice.randomizeColors();
    }
}