function getResult(expr, x_var) {
    const promise = axios.get(`/calc`, {
        params: {
            expr: expr,
            x: x_var
        }
    });

    return promise
        .then((response) => { console.log(response); return response.data; });
}

function getGraph(expr, int1, int2) {
    const promise = axios.get(`/graph`, {
        params: {
            expr: expr,
            int1: int1,
            int2: int2
        }
    });

    return promise
        .then((response) => { console.log(response); return response.data; });
}

function calculateCredit(sum, term, interest, type) {
    const promise = axios.get(`/credit`, {
        params: {
            sum: sum,
            term: term,
            interest: interest,
            type: type
        }
    });

    return promise
        .then((response) => { console.log(response); return response.data; });
}

function getPayment() {
    const promise = axios.get(`/credit/payment`);

    return promise
        .then((response) => { console.log(response); return response.data; });
}

function getSumInterest() {
    const promise = axios.get(`/credit/interest`);

    return promise
        .then((response) => { console.log(response); return response.data; });
}

function getSumMain() {
    const promise = axios.get(`/credit/main`);

    return promise
        .then((response) => { console.log(response); return response.data; });
}

function getHistory() {
    const promise = axios.get(`/history/get`);

    return promise
        .then((response) => { console.log(response); return response.data; });
}

function clearHistory() {
    axios.delete(`/history/clear`);
}

function saveHistory(expr) {
    axios.post(`/history/save`, {
        data: expr
    });
}

function saveSetting(type) {
    axios.get(`/setting/save`, {
        params: {
            type: type
        }
    });
}

function loadSetting() {
    const promise = axios.get(`/setting/load`);

    return promise
        .then((response) => { console.log(response); return response.data; });
}
