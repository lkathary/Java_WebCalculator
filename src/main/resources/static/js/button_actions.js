const expression = document.getElementById('expression');
const x_var = document.getElementById('x_var');
const interval1 = document.getElementById('interval1');
const interval2 = document.getElementById('interval2');
const graph_sw = document.getElementById('graph');
const info_sw = document.getElementById('info');
const history_sw = document.getElementById('history');


document.querySelectorAll('.key').forEach((button) => {
    button.addEventListener('click', () => {
        if (expression.value === "0" && button.textContent !== ".") {
            expression.value = button.textContent;
        } else {
            expression.value += button.textContent;
        }
    });
});

document.querySelector('.clear').addEventListener('click', () => {
    expression.value = "0"
    x_var.value = 0;
    interval1.value = -10;
    interval2.value = 10;
});

document.querySelector('.undo').addEventListener('click', () => {
    if (expression.value.length !== 0) {
        expression.value = expression.value.substring(0, expression.value.length - 1);
    }
    if (expression.value === "") {
        expression.value = "0"
    }
});

document.querySelector('.eq').addEventListener('click', () => {
    getResult(expression.value, x_var.value).then((response) => {
        saveHistory(expression.value);
        addHistoryRow(expression.value);
        expression.value = response;
    });
});

document.querySelector('.graph').addEventListener('click', () => {
    if (graph_sw.checked === false) {
        info_sw.checked = false;
        history_sw.checked = false;
        graph_sw.checked = true;
        drawGraph(expression.value, interval1.value, interval2.value);
    }
});

document.querySelector('.close-graph').addEventListener('click', () => {
    graph_sw.checked = false;
});

document.querySelector('.info').addEventListener('click', () => {
    graph_sw.checked = false;
    history_sw.checked = false;
    info_sw.checked = true;
});

document.querySelector('.close-info').addEventListener('click', () => {
    info_sw.checked = false;
});

document.querySelector('.history').addEventListener('click', () => {
    graph_sw.checked = false;
    info_sw.checked = false;
    history_sw.checked = true;
    getHistory();
});

document.querySelector('.close-history').addEventListener('click', () => {
    history_sw.checked = false;
});

document.querySelector('.clear-history').addEventListener('click', () => {
    clearHistory();
    clearHistoryTable();
});

document.querySelectorAll('.history-expr').forEach((button) => {
    button.addEventListener('click', () => {
            expression.value = button.textContent;
    });
});

function closeWebCalc() {
    graph_sw.checked = false;
    info_sw.checked = false;
    history_sw.checked = false;
}


// Credit calculator

const credit_sum = document.getElementById('credit-sum');
const credit_term = document.getElementById('credit-term');
const credit_interest = document.getElementById('credit-interest');
const diff = document.getElementById('diff');

const credit_payment = document.getElementById('credit-payment');
const interest_sum = document.getElementById('interest-sum');
const total_sum = document.getElementById('total-sum');

document.querySelector('.calc-credit').addEventListener('click', () => {
    let sumOk = true, termOk = true, interestOk = true;
    if (credit_sum.value >= 0.01 && credit_sum.value <= 1e10) {
        credit_sum.value = Math.round(credit_sum.value * 100.0) / 100.0;
    } else {
        credit_sum.value = "";
        credit_sum.placeholder = "0.01 <= sum <= 1e10";
        sumOk = false;
    }
    if (credit_term.value >= 1 && credit_term.value <= 600) {
        credit_term.value = Math.round(credit_term.value);
    } else {
        credit_term.value = "";
        credit_term.placeholder = "1 <= term <= 600";
        termOk = false;
    }
    if (credit_interest.value >= 0.01 && credit_interest.value <= 999.99) {
        credit_interest.value = Math.round(credit_interest.value * 100.0) / 100.0;
    } else {
        credit_interest.value = "";
        credit_interest.placeholder = "0.01 <= % < 1000";
        interestOk = false;
    }

    if (sumOk && termOk && interestOk) {
        calculateCredit(credit_sum.value, credit_term.value, credit_interest .value / 100, diff.checked)
            .then((response) => {

                let interest;
                getPayment().then((response) => {
                    credit_payment.value = response;
                });

                getSumInterest().then((response) => {
                    interest_sum.value = response.toFixed(2);
                    interest = response;

                    getSumMain().then((response) => {
                        total_sum.value = (response + interest).toFixed(2);
                    });
                });
            });
    }
});

document.querySelector('.clear-credit').addEventListener('click', () => {
    credit_sum.value = "0.00";
    credit_term.value = "1";
    credit_interest.value = "0.00";
    diff.checked = true;
    credit_payment.value = "";
    interest_sum.value = "";
    total_sum.value = "";
});

document.querySelectorAll('.theme').forEach((button) => {
    button.addEventListener('click', () => {
        saveSetting(button.value);
        setTheme(button.value);
    });
});
