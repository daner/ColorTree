
function HSV_RGB(h: number, s: number, v: number): number[] {
    var u = 255 * (v / 100);

    if (h === null) {
        return [u, u, u];
    }

    h /= 60;
    s /= 100;

    var i = Math.floor(h);
    var f = i % 2 ? h - i : 1 - (h - i);
    var m = u * (1 - s);
    var n = u * (1 - s * f);
    switch (i) {
        case 6:
        case 0: return [u, n, m];
        case 1: return [n, u, m];
        case 2: return [m, u, n];
        case 3: return [m, n, u];
        case 4: return [n, m, u];
        case 5: return [u, m, n];
    }
}

function RGB_HSV(r: number, g: number, b: number): number[] {
    r /= 255;
    g /= 255;
    b /= 255;
    var n = Math.min(Math.min(r, g), b);
    var v = Math.max(Math.max(r, g), b);
    var m = v - n;
    if (m === 0) { return [0, 0, 100 * v]; }
    var h = r === n ? 3 + (b - g) / m : (g === n ? 5 + (r - b) / m : 1 + (g - r) / m);
    return [
        60 * (h === 6 ? 0 : h),
        100 * (m / v),
        100 * v
    ];
}

export class Color {

    public static ColorFromHSV(h: number, s: number, v: number): Color {
        var rgbArray = HSV_RGB(h, s, v);
        return new Color(rgbArray[0], rgbArray[1], rgbArray[2], h, s, v);
    }

    public static ColorFromRGB(r, g, b): Color {
        var hsvArray = RGB_HSV(r, g, b);
        return new Color(r, g, b, hsvArray[0], hsvArray[1], hsvArray[2]);
    }

    constructor(public r: number, public g: number, public b: number,
                public h: number, public s: number, public v: number) {
    }

    public toString(): string {
        return (0x100 | Math.round(this.r)).toString(16).substr(1) + (0x100 | Math.round(this.g)).toString(16).substr(1) + (0x100 | Math.round(this.b)).toString(16).substr(1);
    }

    public toHexString(): string {
        return '#' + this.toString().toUpperCase();
    }

    public toRGBString(): string {
        return 'rgb(' + Math.round(this.r) + ',' + Math.round(this.g) + ',' + Math.round(this.b) + ')';
    }

    public isLight(): boolean {
        return (0.213 * this.r + 0.715 * this.g + 0.072 * this.b) > (255 / 2);
    }
}