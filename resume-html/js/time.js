var today = new Date();
var hours = today.getHours();
var minutes = today.getMinutes();
if(minutes<10){minutes ='0'+minutes};
var element = document.getElementById('time');
element.textContent = 'Current time: ' + hours + ':' + minutes;