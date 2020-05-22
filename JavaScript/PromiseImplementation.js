const lodash = require('lodash');
class PavanPromise {
    constructor(promiseFn) {
        this.statuses = {
            PENDING: 0,
            RESOLVED: 1,
            REJECTED: 2
        }
        this.currentStatus = this.statuses.PENDING;
        this.responseObj = {};
        let handleResolveFunc = lodash.partialRight(this.defaultOnResolveFn, this);
        let handleRejectFunc = lodash.partialRight(this.defaultOnRejectFn, this);
        setTimeout(promiseFn, 0, handleResolveFunc, handleRejectFunc);
    }
    defaultOnResolveFn(responseObj, obj) {
        obj.responseObj = responseObj;
        obj.currentStatus = obj.statuses.RESOLVED;
    }
    defaultOnRejectFn(responseObj, obj) {
        obj.responseObj = responseObj;
        obj.currentStatus = obj.statuses.REJECTED;
    }
    then(onResolveFn, onRejectFn) {
        return new PavanPromise((resolve, reject) => {

            if (!onResolveFn)
                reject('Resolution call back absent');
            const interval = setInterval(() => {
                try {
                    let retVal;
                    if (this.currentStatus === this.statuses.RESOLVED) {
                        retVal = onResolveFn(this.responseObj);
                        clearInterval(interval);
                        resolve(retVal);
                    }
                    else if (this.currentStatus === this.statuses.REJECTED) {
                        if (onRejectFn) {
                            retVal = onRejectFn(this.responseObj);
                            clearInterval(interval);
                            resolve(retVal);
                        } else {
                            clearInterval(interval);
                            reject(this.responseObj);
                        }
                    }
                } catch (exception) {
                    clearInterval(interval);
                    reject(exception)
                }
            }, 100);
        });
    }
    catch(onRejectFn) {
        return new PavanPromise((resolve, reject) => {
            if (!onRejectFn)
                reject('Rejection call back absent');
            const interval = setInterval(() => {
                try {
                    let retVal;
                    if (this.currentStatus === this.statuses.RESOLVED) {
                        clearInterval(interval);
                        reject(this.responseObj);
                    }
                    else if (this.currentStatus === this.statuses.REJECTED) {
                        retVal = onRejectFn(this.responseObj);
                        clearInterval(interval);
                        resolve(retVal);
                    }
                } catch (exception) {
                    clearInterval(interval);
                    reject(exception)
                }
            }, 0);
        });
    }
}


function testCode() {
    const promise = (A => {
        console.log(A);
    });

    let dummy = new PavanPromise((resolve, reject) => {
        promise('Executes Inside the Promise');
        resolve('Promise Settlement');
    });

    dummy
        .then(response => {
            console.log('Promise Resolved 1: ', response);
            a.b;
        }, response => {
            console.log('Promise Rejected 1: ', response);
        })
        .then(response => {
            console.log('Promise Resolved 2: ', response);
        })
        .catch(response => {
            console.log('Promise Rejected 2: ', response);
        });
}

exports.modules = {
    PavanPromise
}