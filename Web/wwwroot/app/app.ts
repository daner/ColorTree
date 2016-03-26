import {Component} from 'angular2/core';
import {Router, RouteConfig, RouterOutlet, ROUTER_DIRECTIVES} from 'angular2/router';
import {ColorPicker} from './colorpicker';
import {Admin} from './admin';

@Component({
    selector: 'app',
    templateUrl: 'app.html',
    directives: [RouterOutlet, ROUTER_DIRECTIVES]
})
@RouteConfig([
    { path: '/', name: 'ColorPicker', component: ColorPicker, useAsDefault: true },
    { path: '/admin', name: 'Admin', component: Admin }
])
export class App {
    constructor(public router: Router) {
    }

    public isActive(instruction: any[]): boolean {
        return this.router.isRouteActive(this.router.generate(instruction));
    }
}
