var today = new Date();
var hours = today.getHours();
var minutes = today.getMinutes();
var element = document.getElementById('jstest');

element.textContent = 'current time is' + hours + ':' + minutes;