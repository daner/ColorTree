import {bootstrap}    from 'angular2/platform/browser';
import {App} from './app';
import {ColorService} from './colorservice'
import {HTTP_BINDINGS} from 'angular2/http';

bootstrap(App, [ColorService, HTTP_BINDINGS]);