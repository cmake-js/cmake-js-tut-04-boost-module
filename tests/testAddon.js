"use strict";
/* global it,describe */
var addon = require("..");
var assert = require("assert");

describe("Boost Based Addon", function() {
    it("should return Fibonacci sequence", function() {
        var result = addon.fibo();
        assert.equal(result, "1 1 2 3 5 8 13 21 34 55");
    });
});