// ========================================
// ESP32 Vehicle Control - Main JavaScript
// ========================================

// Global Variables
const video = document.getElementById('video');
let streamActive = false;
let hasControl = false;
const currentUUID = generateUUID();

// DOM Elements
const controlStatus = document.getElementById('control-status');
const angleDisplay = document.getElementById('angle-display');
const distanceDisplay = document.getElementById('distance-display');
const rotationDisplay = document.getElementById('rotation-display');
const requestBtn = document.getElementById('request-btn');
const releaseBtn = document.getElementById('release-btn');

// ========================================
// Utility Functions
// ========================================

function generateUUID() {
  return 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function (c) {
    const r = Math.random() * 16 | 0;
    const v = c === 'x' ? r : (r & 0x3 | 0x8);
    return v.toString(16);
  });
}

function updateStatus(status, color = '#667eea') {
  controlStatus.textContent = status;
  controlStatus.style.color = color;
}

// ========================================
// Control Management
// ========================================

function requestControl() {
  fetch('/control/request', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ uuid: currentUUID })
  })
    .then(response => response.json())
    .then(data => {
      if (data.granted) {
        hasControl = true;
        updateStatus('Control Granted', '#28a745');
        requestBtn.disabled = true;
        releaseBtn.disabled = false;
        console.log('Control granted:', currentUUID);
      } else {
        hasControl = false;
        updateStatus('Control Denied (In Use)', '#dc3545');
        console.log('Control denied, current owner:', data.current_owner);
      }
    })
    .catch(err => {
      console.error('Failed to request control:', err);
      updateStatus('Connection Error', '#dc3545');
    });
}

function releaseControl() {
  fetch('/control/release', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ uuid: currentUUID })
  })
    .then(response => response.json())
    .then(data => {
      if (data.released) {
        hasControl = false;
        updateStatus('Control Released', '#6c757d');
        requestBtn.disabled = false;
        releaseBtn.disabled = true;
        resetJoystick();
        resetRotation();
        console.log('Control released');
      }
    })
    .catch(err => {
      console.error('Failed to release control:', err);
    });
}

// ========================================
// Joystick Control
// ========================================

const joystickBase = document.getElementById('joystick-base');
const joystickKnob = document.getElementById('joystick-knob');
const baseRadius = 100; // Half of joystick-base width (200px / 2)
const knobRadius = 30;  // Half of joystick-knob width (60px / 2)
const maxDistance = baseRadius - knobRadius;

// Rotation dial elements
const rotationBase = document.getElementById('rotation-base');
const rotationKnob = document.getElementById('rotation-knob');
const rotationRadius = 90; // Half of rotation-base width (180px / 2)
const rotationKnobRadius = 24; // Half of rotation-knob width (48px / 2)
const rotationMaxDistance = rotationRadius - rotationKnobRadius;

function updateJoystick(clientX, clientY) {
  if (!hasControl) return;

  const rect = joystickBase.getBoundingClientRect();
  const centerX = rect.left + baseRadius;
  const centerY = rect.top + baseRadius;

  // Calculate relative position from center
  let dx = clientX - centerX;
  let dy = clientY - centerY;

  // Calculate distance and angle
  let distance = Math.sqrt(dx * dx + dy * dy);
  const angle = Math.atan2(dy, dx);

  // Limit distance to max radius
  if (distance > maxDistance) {
    distance = maxDistance;
    dx = maxDistance * Math.cos(angle);
    dy = maxDistance * Math.sin(angle);
  }

  // Position knob
  const knobX = baseRadius + dx - knobRadius;
  const knobY = baseRadius + dy - knobRadius;
  joystickKnob.style.left = `${knobX}px`;
  joystickKnob.style.top = `${knobY}px`;

  // Calculate angle in degrees (0-360)
  let angleDeg = Math.round((angle * 180 / Math.PI));
  if (angleDeg < 0) angleDeg += 360;

  // Calculate distance as percentage
  const distancePercent = Math.round((distance / maxDistance) * 100);

  // Update display
  angleDisplay.textContent = `${angleDeg}°`;
  distanceDisplay.textContent = `${distancePercent}%`;

  // Send to ESP32
  sendJoystickData(angleDeg, distancePercent);
}

function resetJoystick() {
  // Center the knob
  joystickKnob.style.left = `${baseRadius - knobRadius}px`;
  joystickKnob.style.top = `${baseRadius - knobRadius}px`;

  // Reset displays
  angleDisplay.textContent = '0°';
  distanceDisplay.textContent = '0%';
  rotationDisplay.textContent = '0°';

  // Send stop command
  if (hasControl) {
    sendJoystickData(0, 0);
  }
}

// Rotation Dial Control
function updateRotation(clientX, clientY) {
  if (!hasControl) return;

  const rect = rotationBase.getBoundingClientRect();
  const centerX = rect.left + rotationRadius;
  const centerY = rect.top + rotationRadius;

  let dx = clientX - centerX;
  let dy = clientY - centerY;

  const angle = Math.atan2(dy, dx);

  // Force knob to remain on the circle perimeter like a scroll
  dx = rotationMaxDistance * Math.cos(angle);
  dy = rotationMaxDistance * Math.sin(angle);

  const knobX = rotationRadius + dx - rotationKnobRadius;
  const knobY = rotationRadius + dy - rotationKnobRadius;
  rotationKnob.style.left = `${knobX}px`;
  rotationKnob.style.top = `${knobY}px`;

  // Convert angle to -180..180 range
  let angleDeg = Math.round(angle * 180 / Math.PI);
  if (angleDeg > 180) angleDeg -= 360;
  if (angleDeg < -180) angleDeg += 360;
  angleDeg = Math.max(-180, Math.min(180, angleDeg));

  const degrees = Math.abs(angleDeg);
  const direction = angleDeg > 0 ? 'cw' : (angleDeg < 0 ? 'ccw' : 'stop');

  rotationDisplay.textContent = `${angleDeg}°`;

  sendRotationData(direction, degrees);
}

function resetRotation() {
  // Place knob on perimeter at 0° (right side)
  const dx = rotationMaxDistance;
  const dy = 0;
  rotationKnob.style.left = `${rotationRadius + dx - rotationKnobRadius}px`;
  rotationKnob.style.top = `${rotationRadius + dy - rotationKnobRadius}px`;
  rotationDisplay.textContent = '0°';
  if (hasControl) {
    sendRotationData('stop', 0);
  }
}

function sendRotationData(direction, degrees) {
  if (!hasControl) return;

  fetch('/rotate', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({
      uuid: currentUUID,
      direction: direction,
      degrees: degrees
    })
  }).catch(err => {
    console.error('Failed to send rotation data:', err);
  });
}

function sendJoystickData(angle, distance) {
  fetch('/joystick', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({
      uuid: currentUUID,
      angle: angle,
      distance: distance
    })
  }).catch(err => {
    console.error('Failed to send joystick data:', err);
  });
}

// Mouse Events
joystickKnob.addEventListener('mousedown', function (e) {
  if (!hasControl) {
    alert('Please request control first!');
    return;
  }
  e.preventDefault();

  function onMouseMove(event) {
    updateJoystick(event.clientX, event.clientY);
  }

  function onMouseUp() {
    document.removeEventListener('mousemove', onMouseMove);
    document.removeEventListener('mouseup', onMouseUp);
    resetJoystick();
  }

  document.addEventListener('mousemove', onMouseMove);
  document.addEventListener('mouseup', onMouseUp);
});

// Touch Events
joystickKnob.addEventListener('touchstart', function (e) {
  if (!hasControl) {
    alert('Please request control first!');
    return;
  }
  e.preventDefault();
}, { passive: false });

joystickKnob.addEventListener('touchmove', function (e) {
  if (!hasControl) return;
  e.preventDefault();
  const touch = e.touches[0];
  updateJoystick(touch.clientX, touch.clientY);
}, { passive: false });

joystickKnob.addEventListener('touchend', function (e) {
  if (!hasControl) return;
  e.preventDefault();
  resetJoystick();
}, { passive: false });

// Rotation Dial Events
rotationKnob.addEventListener('mousedown', function (e) {
  if (!hasControl) {
    alert('Please request control first!');
    return;
  }
  e.preventDefault();

  function onMouseMove(event) {
    updateRotation(event.clientX, event.clientY);
  }

  function onMouseUp() {
    document.removeEventListener('mousemove', onMouseMove);
    document.removeEventListener('mouseup', onMouseUp);
    resetRotation();
  }

  document.addEventListener('mousemove', onMouseMove);
  document.addEventListener('mouseup', onMouseUp);
});

rotationKnob.addEventListener('touchstart', function (e) {
  if (!hasControl) {
    alert('Please request control first!');
    return;
  }
  e.preventDefault();
}, { passive: false });

rotationKnob.addEventListener('touchmove', function (e) {
  if (!hasControl) return;
  e.preventDefault();
  const touch = e.touches[0];
  updateRotation(touch.clientX, touch.clientY);
}, { passive: false });

rotationKnob.addEventListener('touchend', function (e) {
  if (!hasControl) return;
  e.preventDefault();
  resetRotation();
}, { passive: false });

// ========================================
// Camera Stream Functions
// ========================================

function startStream() {
  fetch('/start')
    .then(() => {
      video.src = '/stream';
      streamActive = true;
      console.log('Camera stream started');
    })
    .catch(err => {
      console.error('Failed to start stream:', err);
      alert('Failed to start camera stream');
    });
}

function stopStream() {
  fetch('/stop')
    .then(() => {
      video.src = '';
      streamActive = false;
      console.log('Camera stream stopped');
    })
    .catch(err => {
      console.error('Failed to stop stream:', err);
    });
}

// ========================================
// Initialization
// ========================================

console.log('ESP32 Vehicle Control initialized');
console.log('Client UUID:', currentUUID);

// Initialize control positions on load
resetJoystick();
resetRotation();