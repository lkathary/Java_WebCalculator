function setTheme(type) {

    switch (Number(type)) {
        case 0:
            document.documentElement.style.setProperty('--back-container-color', '#EBECF4');
            document.documentElement.style.setProperty('--background-gradient', 'linear-gradient(rgba(35, 41, 62, 50), rgba(35, 61, 102, 50))');
            break;
        case 1:
            document.documentElement.style.setProperty('--back-container-color', '#D5BFBF');
            document.documentElement.style.setProperty('--background-gradient', 'linear-gradient(rgba(35, 41, 62, 50), rgb(117, 28, 33))');
            break;
        case 2:
            document.documentElement.style.setProperty('--back-container-color', '#C5EAC5');
            document.documentElement.style.setProperty('--background-gradient', 'linear-gradient(rgba(35, 41, 62, 50), rgb(66, 101, 55))');
            break;
        case 3:
            document.documentElement.style.setProperty('--back-container-color', '#202020');
            document.documentElement.style.setProperty('--background-gradient', 'linear-gradient(rgba(35, 41, 62, 50), rgb(110, 110, 110))');
            break;
    default:
        alert( "Invalid theme" );
    }
}