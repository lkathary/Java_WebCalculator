const canvas = document.getElementById('chart');
const context = canvas.getContext('2d');

let chart = new Chart(context);

function drawGraph(expr, int1, int2) {
    const createLineChart = (xData, yData) => {
        let data = {
            labels: xData,
            datasets: [{
                label: expr,
                data: yData,
                pointStyle: false,
                // fill: true,
                borderColor: 'rgb(220,25,25)',
                borderWidth: 2,
                tension: 0.2
            }]
        }
        let xScaleConfig = {
            ticks: {
                autoSkip: true,
                // maxRotation: 0,
                minRotation: 90,
                color: 'rgba(0, 0, 0, 0.9)'
            },
            border: {
                color: 'rgba(74, 169, 230, 1)'
            },
            grid: {
                color: 'rgba(74, 169, 230, 0.3)'
            }
        }
        let yScaleConfig = {
            ticks: {
                color: 'rgba(0, 0, 0, 0.9)'
            },
            border: {
                color: 'rgba(74, 169, 230, 1)'
            },
            grid: {
                color: 'rgba(74, 169, 230, 0.3)'
            }
        }
        let zoomOptions = {
            pan: {
                enabled: true,
                mode: 'y'
            },
            zoom: {
                mode: 'y',
                pinch: {
                    enabled: true
                },
                wheel: {
                    enabled: true
                }
            }
        }

        let config = {
            type: 'line',
            data: data,
            options: {
                scales: {
                    x: xScaleConfig,
                    y: yScaleConfig
                },
                plugins: {
                    zoom: zoomOptions
                }
            }
        }
        chart = new Chart(context, config);
    }

    let xData = [];
    let yData = [];
    getGraph(expr, int1, int2).then((response) => {
        for(let i = 0; i < response.length; ++i) {
            xData.push(Math.floor(response[i].key * 100) / 100);
            yData.push(response[i].value);
        }
    });

    context.clearRect(0, 0, canvas.width, canvas.height);
    chart.destroy();
    createLineChart(xData, yData);
}
