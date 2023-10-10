const table = document.querySelector('.history-table');

function addHistoryRow(expr) {
    const tr = document.createElement('tr');
    const td = document.createElement('td');
    td.addEventListener('click', () => {
        expression.value = td.textContent;
    });
    td.textContent = expr;
    tr.appendChild(td);
    table.appendChild(tr);
}

function fillHistoryTable() {
    getHistory().then((response) => {
        response.forEach((expr) => {
            addHistoryRow(expr);
        });
    });
}

function clearHistoryTable() {
    document.querySelectorAll('.history-table tr')
        .forEach((tr) => {
            tr.remove();
    });
}

fillHistoryTable();
