const lodash = require('lodash');
const EventEmitter = require('events');
class PavanPromise {
    constructor(promiseFn) {
        this.statuses = {
            PENDING: 0,
            RESOLVED: 1,
            REJECTED: 2
        }
        this.currentStatus = this.statuses.PENDING;
        this.responseObj = {};
        this.settledEventEmitter = new EventEmitter();
        let handleResolveFunc = lodash.partialRight(this.defaultOnResolveFn, this);
        let handleRejectFunc = lodash.partialRight(this.defaultOnRejectFn, this);
        setImmediate(promiseFn, handleResolveFunc, handleRejectFunc);
    }
    defaultOnResolveFn(responseObj, obj) {
        obj.responseObj = responseObj;
        obj.currentStatus = obj.statuses.RESOLVED;
        obj.settledEventEmitter.emit('settled');
    }
    defaultOnRejectFn(responseObj, obj) {
        obj.responseObj = responseObj;
        obj.currentStatus = obj.statuses.REJECTED;
        obj.settledEventEmitter.emit('settled');
    }
    processSettledPromise(onResolveFn, onRejectFn, obj) {
        const retObj = {};
        try {
            let retVal;
            if (obj.currentStatus === obj.statuses.RESOLVED) {
                retVal = onResolveFn(obj.responseObj);
                retObj.retVal = retVal;
                retObj.resolved = true;
            }
            else if (obj.currentStatus === obj.statuses.REJECTED) {
                if (onRejectFn) {
                    retVal = onRejectFn(obj.responseObj);
                    retObj.retVal = retVal;
                    retObj.resolved = true;
                } else {
                    retObj.retVal = obj.responseObj;
                    retObj.resolved = false;
                }
            }
        } catch (exception) {
            retObj.retVal = exception;
            retObj.resolved = false;
        }
        return retObj;
    }
    processRejectedPromise(onRejectFn, obj) {
        const retObj = {};
        try {
            let retVal;
            if (obj.currentStatus === obj.statuses.RESOLVED) {
                retObj.retVal = obj.responseObj;
                retObj.resolved = false;
            }
            else if (obj.currentStatus === obj.statuses.REJECTED) {
                retVal = onRejectFn(obj.responseObj);
                retObj.retVal = retVal;
                retObj.resolved = true;
            }
        } catch (exception) {
            retObj.retVal = exception;
            retObj.resolved = false;
        }
        return retObj;
    }
    then(onResolveFn, onRejectFn) {
        const thenPromise = new PavanPromise((resolve, reject) => {
            if (!onResolveFn)
                reject('Resolution call back absent');
            if (this.currentStatus === this.statuses.PENDING) {
                const loadedFn = lodash.partial(this.processSettledPromise, onResolveFn, onRejectFn, this);
                const promiseSettledHandler = () => {
                    const retObj = loadedFn();
                    if (retObj.resolved) {
                        resolve(retObj.retVal);
                    } else {
                        reject(retObj.retVal);
                    }
                }
                this.settledEventEmitter.on('settled', promiseSettledHandler);
            } else {
                const retObj = this.processSettledPromise(onResolveFn, onRejectFn, this)
                if (retObj.resolved) {
                    resolve(retObj.retVal);
                } else {
                    reject(retObj.retVal);
                }
            }
        });
        return thenPromise;
    }
    catch(onRejectFn) {
        const catchPromise = new PavanPromise((resolve, reject) => {
            if (!onRejectFn)
                reject('Rejection call back absent');
            if (this.currentStatus === this.statuses.PENDING) {
                const handleRejectedPromise = lodash.partial(this.processRejectedPromise, onRejectFn, this);
                const promiseSettledHandler = () => {
                    const retObj = handleRejectedPromise();
                    if (retObj.resolved) {
                        resolve(retObj.retVal)
                    } else {
                        reject(retObj.retVal);
                    }
                };
                this.settledEventEmitter.on('settled', promiseSettledHandler);
            } else {
                const retObj = this.processRejectedPromise(onRejectFn, this);
                if (retObj.resolved) {
                    resolve(retObj.retVal);
                } else {
                    reject(retObj.retVal);
                }
            }
        });
        return catchPromise;
    }
}


function testCode() {
    console.log('Inside test code')
    const promise = (A => {
        console.log(A);
    });

    let dummy = new PavanPromise((resolve, reject) => {
        promise('Executes Inside the Promise');
        setTimeout(resolve, 5000, 'promise settled');
    });

    dummy
        .then(response => {
            const str = 'Promise Resolved 1: ';
            console.log('Promise Resolved 1: ', response);
            return "From" + str;
        }, response => {
            const str = 'Promise Rejected 1: ';
            console.log('Promise Rejected 1: ', response);
            return "From" + str;
        })
        .then(response => {
            const str = 'Promise Resolved 2: ';
            console.log('Promise Resolved 2: ', response);
            a.b;
            return "From" + str;
        }, response => {
            const str = 'Promise Rejected 2: ';
            console.log(str, response);
            return "From" + str;
        })
        .then(response => {
            console.log('Promise Resolved 3: ', response);
            return "From Promise Resolved 3";
        })
        .catch(response => {
            console.log('Promise Rejected 3: ', response);
            return "From Rejected Promise 3";
        })
    console.log('-----------------------------------------------');


}
testCode();


exports.modules = {
    PavanPromise
}