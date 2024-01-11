const decrementButton = document.querySelector('.decrement');
const incrementButton = document.querySelector('.increment');
const countElement = document.querySelector('.count');
let count = 0;
decrementButton.addEventListener('click', () => {
    count--;
    updateCount();
});
incrementButton.addEventListener('click', () => {
    count++;
    updateCount();
});
function updateCount() {
    countElement.textContent = count;
    countElement.classList.remove('increasing', 'decreasing');
    if (count < 0) {
    countElement.classList.add('decreasing');
    } else if (count > 0) {
    countElement.classList.add('increasing');
    }
}
