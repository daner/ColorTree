"use strict";

var gulp = require('gulp');
var typescript = require('gulp-typescript');
var sourcemaps = require('gulp-sourcemaps');

var webroot = "./wwwroot/";

var config = {
    libBase: 'node_modules',
    lib: [
        require.resolve("es6-shim/es6-shim.min.js"),
        require.resolve("systemjs/dist/system-polyfills.js"),
        require.resolve("angular2/es6/dev/src/testing/shims_for_IE.js"),
        require.resolve("angular2/bundles/angular2-polyfills.js"),
        require.resolve("systemjs/dist/system.src.js"),
        require.resolve("rxjs/bundles/Rx.js"),
        require.resolve("angular2/bundles/angular2.dev.js")
    ]
};

gulp.task('copy', function () {
    return gulp.src(config.lib, { base: config.libBase })
        .pipe(gulp.dest(webroot + 'lib'));
});

gulp.task('default', ['copy']);