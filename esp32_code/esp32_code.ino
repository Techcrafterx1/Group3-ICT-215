#include "esp_camera.h"

camer_config_t config = {
  .pin_pwdn = 32,
  .pin_reset = -1,
  .pin_xclk = 0,
  .pin_sscb_sda = 26,
  .pin_sscb_scl = 27,
  .pin_d7 = 35,
  .pin_d6 = 34,
  .pin_d5 = 39,
  .pin_d4 = 36,
  .pin_d3 = 21,
  .pin_d2 = 19,
  .pin_d1 = 18,
  .pin_d0 = 5,
  .pin_vsync = 25,
  .pin_href = 23,
  .pin_pclk = 22,
  .xclk_freq_hz = 20000000,
  .pixel_format = PIXEL_GRAYSCALE,
  .frame_size = FRAMESIZE_QVGA,
  .jpeg_quality = 12,
  .fb_count = 1
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("camera init failed error 0x%x", err);
    return;
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  camera_fb_t * fb = esp_camera_fb_get();
  if (!fb) {
    Serial.printIn("Camera capture failed");
    return;
  }

  processImage(fb);

  esp_camera_fb_return(fb);

  delay(1000)
}

void processImage(camera_fb_t * fb) {
  uint8_t * grayscale = (uint8_t*)malloc(fb -> len);
  esp_camera_fb_to_grayscale(grayscale, fb -> buf, fb -> len);

  uint8_t threshold = 128;
  esp_camera_fb_threshold(grayscale, fb->len, threshold);

  int contours = esp_camera_fb_find_contours(grayscale, fb->len);
  Serial.printf("Contour detected")
}

void recognizeGestures(int contours) {
  int contourPoints[contours][2];
  int centroidX = 0;
  int centroidY = 0;
  for (int i = 0; i < contours; i++) {
    centroidX += contourPoints[i][0];
    centroidY += contourPoints[i][1];
  }
  centriodX /= contours;
  centriodY /= contours;

  static int prevCentroidX = 0;
  static int prevCentroidY = 0;

  int movementX = centroidX - prevCentroidX;
  int movementY = centroidY - prevCentroidY;

  prevCentroidX = centroidX;
  prevCentroidY = centroidY;

  bool fistDetected = false;

  const int fistThreshold = 900;

  if (contours > fistThreshold) {
    fistDetected = true;
  }

  if (fistDetected) {
    prevCentroidX = 0;
    prevCentroidY = 0;

    // stop();
    // delay(1250);
    // start();

    movementX = 0;
    movementY = 0;
  } else {
    if(abs(movementX) > abs(movementY)) {
     if(movementX > 0) {
      Serial.println("Steer Right");
      // steerRight()  
    } else {
      Serial.println("Steer Left");
      // steerLeft()
    }
  } else {
    if(movementY > 0) {
      Serial.println("Move Foreward")
      // goForward()
    } else {
      Serial.println("Move Backward")
      // goBackward()
    }
  } 
}