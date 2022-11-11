const empty = document.querySelector('.empty');
const filled = document.querySelector('.filled');

const setState = percent => {
  const flexEmpty = Math.floor(100 - percent * 100);
  const flexFilled = (percent * 100);
  Object.assign(empty.style, { flex: flexEmpty });
  Object.assign(filled.style, { flex: flexFilled });
};

let onmove = false;
document.body.addEventListener('mousedown', e => {
  setState(1 - e.y / innerHeight);
  onmove = true;
});
document.body.addEventListener('mousemove', e => {
  onmove && setState(1 - e.y / innerHeight);
});
document.body.addEventListener('mouseup', e => {
  onmove = false;
});

document.body.addEventListener('touchmove', e => {
  setState(1 - e.touches[0].clientY / innerHeight);
});
