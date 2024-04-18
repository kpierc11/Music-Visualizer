import * as THREE from "three";
import { OrbitControls } from "three/addons/controls/OrbitControls.js";

const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(
  75,
  window.innerWidth / window.innerHeight,
  0.1,
  1000
);
const canvas = document.querySelector("#canvas");

const renderer = new THREE.WebGLRenderer({ canvas: canvas });
renderer.setSize(window.innerWidth, window.innerHeight);
let playButton = document.querySelector(".play-button");
let stopButton = document.querySelector(".stop-button");
const controls = new OrbitControls(camera, renderer.domElement);

window.addEventListener("resize", () => {
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(window.innerWidth, window.innerHeight);
});

const objects = [];

for (let i = 0; i < 50; i++) {
  const x = i * 10;
  const y = -5;
  const z = 0;

  const geometry = new THREE.BoxGeometry(1, 1, 1);
  const material = new THREE.MeshBasicMaterial({ color: 0x00ff00 });
  const cube = new THREE.Mesh(geometry, material);
  cube.position.set(x, y, z);
  objects.push(cube);
}

objects.forEach((point) => {
  scene.add(point);
});

const listener = new THREE.AudioListener();
camera.add(listener);

// create a global audio source
const sound = new THREE.Audio(listener);

// load a sound and set it as the Audio object's buffer
const audioLoader = new THREE.AudioLoader();
audioLoader.load("/sounds/dragon-boy.mp3", function (buffer) {
  sound.setBuffer(buffer);
  sound.setLoop(true);
  sound.setVolume(0.5);
});

playButton.addEventListener("click", () => {
  sound.play();
});

stopButton.addEventListener("click", () => {
  sound.stop();
});

const analyser = new THREE.AudioAnalyser(sound, 32);
camera.position.z = 20;

controls.update();

function animate() {
  requestAnimationFrame(animate);
  controls.update();
  const data = analyser.getFrequencyData();
  for (let i = 0; i < objects.length; i++) {
    if (sound.isPlaying) {
      let newPos = data[i] / 100 * 2;
      console.log(newPos);
      objects[i].scale.set(newPos, newPos, newPos);
      if (i == 1) {
        objects[i].material.color.setHex(0x483d8b);
      }
    }
  }

  renderer.render(scene, camera);
}

animate();
