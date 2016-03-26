import {bootstrap}    from 'angular2/platform/browser';
import {App} from './app';
import {ColorService} from './colorservice';
import {provide} from 'angular2/core';
import {HTTP_BINDINGS} from 'angular2/http';
import {ROUTER_PROVIDERS, LocationStrategy, HashLocationStrategy} from 'angular2/router';

bootstrap(App, [ColorService, HTTP_BINDINGS, ROUTER_PROVIDERS, provide(LocationStrategy, {useClass: HashLocationStrategy})]);