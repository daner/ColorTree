import {Component} from 'angular2/core';
import {ColorService} from './colorservice';
import {Color} from './color';

@Component({
    selector: 'colorpicker',
    templateUrl: 'colorpicker.html'
})
export class ColorPicker {

    public selectedColor: Color;

    public constructor(private colorService: ColorService) {
        this.selectedColor = Color.ColorFromRGB(255, 255, 255);
    }

    private drawPallette(): void {
        var canvas = <HTMLCanvasElement>document.getElementById("paletteCanvas");
        var ctx = canvas.getContext('2d');

        ctx.clearRect(0, 0, canvas.width, canvas.height);

        var hGrad = ctx.createLinearGradient(0, 0, canvas.width, 0);
        hGrad.addColorStop(0 / 6, '#F00');
        hGrad.addColorStop(1 / 6, '#FF0');
        hGrad.addColorStop(2 / 6, '#0F0');
        hGrad.addColorStop(3 / 6, '#0FF');
        hGrad.addColorStop(4 / 6, '#00F');
        hGrad.addColorStop(5 / 6, '#F0F');
        hGrad.addColorStop(6 / 6, '#F00');
        ctx.fillStyle = hGrad;
        ctx.fillRect(0, 0, canvas.width, canvas.height);

        var vGrad = ctx.createLinearGradient(0, 0, 0, canvas.height);
        vGrad.addColorStop(0, 'rgba(255,255,255,0)');
        vGrad.addColorStop(1, 'rgba(255,255,255,1)');
        ctx.fillStyle = vGrad;
        ctx.fillRect(0, 0, canvas.width, canvas.height);
    }

    private drawSlider(selectedColor: Color): void {
        var canvas = <HTMLCanvasElement>document.getElementById('sliderCanvas');
        var ctx = canvas.getContext('2d');

        ctx.clearRect(0, 0, canvas.width, canvas.height);

        var grad = ctx.createLinearGradient(0, 0, 0, canvas.height);

        var color1 = Color.ColorFromHSV(selectedColor.h, selectedColor.s, 100);
        var color2 = Color.ColorFromHSV(selectedColor.h, selectedColor.s, 0);

        grad.addColorStop(0, color1.toRGBString());
        grad.addColorStop(1, color2.toRGBString());

        ctx.fillStyle = grad;
        ctx.fillRect(0, 0, canvas.width, canvas.height);
    }

    private UpdateColorFromPaletteEvent(event: MouseEvent): void {
        var h = Math.round((event.layerX / (<HTMLCanvasElement>event.target).clientWidth) * 360);
        var s = Math.round((1 - (event.layerY / (<HTMLCanvasElement>event.target).clientHeight)) * 100);
        this.selectedColor = Color.ColorFromHSV(h, s, this.selectedColor.v);
        this.drawSlider(this.selectedColor);
    }

    public paletteClicked(event: MouseEvent): void {
        this.UpdateColorFromPaletteEvent(event);
    }

    public paletteMove(event: MouseEvent): void {
        if (event.buttons === 1) {
            this.UpdateColorFromPaletteEvent(event);
        }
    }

    private UpdateColorFromSliderEvent(event: MouseEvent): void {
        var v = Math.round((1 - (event.layerY / (<HTMLCanvasElement>event.target).clientHeight)) * 100);
        this.selectedColor = Color.ColorFromHSV(this.selectedColor.h, this.selectedColor.s, v);
    }

    public sliderClicked(event: MouseEvent): void {
        this.UpdateColorFromSliderEvent(event);
    }

    public sliderMove(event: MouseEvent): void {
        if (event.buttons === 1) {
            this.UpdateColorFromSliderEvent(event);
        }
    }

    public sendColor(): void {
        this.colorService.sendColor(this.selectedColor);
    }

    public ngAfterViewInit(): void {
        this.drawPallette();
        this.drawSlider(this.selectedColor);
    }
}