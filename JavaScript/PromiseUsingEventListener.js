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

        const defaultOnResolveFn = (response) => {
            this.responseObj = response;
            this.currentStatus = this.statuses.RESOLVED;
            this.settledEventEmitter.emit('settled');
        }
        const defaultOnRejectFn = (response) => {
            this.responseObj = response;
            this.currentStatus = this.statuses.REJECTED;
            this.settledEventEmitter.emit('settled');
        }
        setImmediate(promiseFn, defaultOnResolveFn, defaultOnRejectFn);
    }
    processSettledPromise(onResolveFn, onRejectFn) {
        const retObj = {};
        try {
            let retVal;
            if (this.currentStatus === this.statuses.RESOLVED) {
                retVal = onResolveFn(this.responseObj);
                retObj.retVal = retVal;
                retObj.resolved = true;
            }
            else if (this.currentStatus === this.statuses.REJECTED) {
                if (onRejectFn) {
                    retVal = onRejectFn(this.responseObj);
                    retObj.retVal = retVal;
                    retObj.resolved = true;
                } else {
                    retObj.retVal = this.responseObj;
                    retObj.resolved = false;
                }
            }
        } catch (exception) {
            retObj.retVal = exception;
            retObj.resolved = false;
        }
        return retObj;
    }
    processRejectedPromise(onRejectFn) {
        const retObj = {};
        try {
            let retVal;
            if (this.currentStatus === this.statuses.RESOLVED) {
                retObj.retVal = this.responseObj;
                retObj.resolved = false;
            }
            else if (this.currentStatus === this.statuses.REJECTED) {
                retVal = onRejectFn(this.responseObj);
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
            const promiseSettledHandler = () => {
                const retObj = this.processSettledPromise(onResolveFn, onRejectFn);
                if (retObj.resolved) {
                    resolve(retObj.retVal);
                } else {
                    reject(retObj.retVal);
                }
            }
            if (this.currentStatus === this.statuses.PENDING) {
                this.settledEventEmitter.on('settled', promiseSettledHandler);
            } else {
                promiseSettledHandler();
            }
        });
        return thenPromise;
    }
    catch(onRejectFn) {
        const catchPromise = new PavanPromise((resolve, reject) => {
            if (!onRejectFn)
                reject('Rejection call back absent');
            const promiseSettledHandler = () => {
                const retObj = this.processRejectedPromise(onRejectFn);
                if (retObj.resolved) {
                    resolve(retObj.retVal)
                } else {
                    reject(retObj.retVal);
                }
            };
            if (this.currentStatus === this.statuses.PENDING) {
                this.settledEventEmitter.on('settled', promiseSettledHandler);
            } else {
                promiseSettledHandler();
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
        setTimeout(resolve, 000, 'promise settled');
    });

    dummy
        .then(response => {
            const str = 'Promise Resolved 1: ';
            console.log('Promise Resolved 1: ', response);
            a.b;
            return "From" + str;
        }, response => {
            const str = 'Promise Rejected 1: ';
            console.log('Promise Rejected 1: ', response);
            return "From" + str;
        })
        .then(response => {
            const str = 'Promise Resolved 2: ';
            console.log('Promise Resolved 2: ', response);
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