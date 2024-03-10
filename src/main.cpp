#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Wire.h>

// forward declaration
void draw_idle_face(int x, int y, int width, int height, int radius);
void animate_face();
void draw_mouth();
#define SCREEN_WIDTH 128  // OLED display width,  in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// OLED display with address 0x3C for 128x64
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
int oled_addr = 0x3C;

// face properties
int eye_width = 20;
int eye_height = 30;
int eye_radius = 20;
int left_eye_x = 15;
int left_eye_y = 10;
int right_eye_x = SCREEN_WIDTH - left_eye_x - eye_width;
int right_eye_y = left_eye_y;

void setup() {
    Serial.begin(115200);
    randomSeed(analogRead(0));
    // initialize display
    if (!oled.begin(SSD1306_SWITCHCAPVCC, oled_addr)) {
        Serial.println("SSD1306 allocation failed");
        while (true)
            ;
    }
    // wait for initializing
    delay(2000);

}

void loop() {
    // draw eyes fully open
    draw_idle_face(15, 10, eye_width, eye_height, eye_radius);
    // random blink interval
    int time = random(500, 3000); 
    // wait before animating eyes
    delay(time);
    // draw eyes blinking
    animate_face();
}

// clear screen, draw eyes (fully open) + mouth
void draw_idle_face(int x, int y, int width, int height, int radius) {
    oled.clearDisplay();
    // left eye
    oled.fillRoundRect(x, y, width, height, radius, WHITE);

    // right eye
    oled.fillRoundRect(SCREEN_WIDTH - x - width, y, width, height, radius,
                       WHITE);

    //oled.drawLine(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT, WHITE);
    draw_mouth();
    oled.display();
}

// statically draw mouth
void draw_mouth(){
    int mouth_radius = 25;
    oled.fillRoundRect((SCREEN_WIDTH / 2) - mouth_radius, 53, mouth_radius * 2, 10, 5, WHITE);
    //oled.fillRoundRect(42, 50, 40, 10, 5, WHITE);
}

// animates eyes closing and opening
void animate_face() {
    int animation_speed = 13;
    // close eye
    for (int i = eye_height; i >= 5; i -= animation_speed) {
        oled.clearDisplay();
        oled.fillRoundRect(left_eye_x, left_eye_y, eye_width, i, eye_radius,
                           WHITE);
        oled.fillRoundRect(right_eye_x, right_eye_y, eye_width, i, eye_radius,
                           WHITE);
        draw_mouth();
        oled.display();
    }

    delay(10);

    // open eye
    for (int i = 5; i <= eye_height; i += animation_speed) {
        oled.clearDisplay();
        oled.fillRoundRect(left_eye_x, left_eye_y, eye_width, i, eye_radius,
                           WHITE);
        oled.fillRoundRect(right_eye_x, right_eye_y, eye_width, i, eye_radius,
                           WHITE);
        draw_mouth();
        oled.display();
    }
}