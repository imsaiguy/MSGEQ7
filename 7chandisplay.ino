// MSGEQ7 7 band equalizer
// ImsaiGuy 2024

// using TTGO T-Display   esp32

#include <TFT_eSPI.h> // Include the TFT library

TFT_eSPI tft; // Create an instance of the TFT screen

const int matrixSize = 7; // Size of the matrix
int matrix[matrixSize]; // Array to store random data

// Define the pins connected to the MSGEQ7
#define ANALOG_PIN 13  // Connected to the OUT pin of the MSGEQ7
#define STROBE_PIN 15   // Connected to the STROBE pin of the MSGEQ7
#define RESET_PIN 12    // Connected to the RESET pin of the MSGEQ7

void setup() {
// Set the pins as inputs or outputs
  pinMode(ANALOG_PIN, INPUT);
  pinMode(STROBE_PIN, OUTPUT);
  pinMode(RESET_PIN, OUTPUT);

  digitalWrite(RESET_PIN, LOW);
  digitalWrite(STROBE_PIN, LOW);
  

  // Reset the MSGEQ7
  digitalWrite(RESET_PIN, HIGH);
  delayMicroseconds(1); 
  digitalWrite(RESET_PIN, LOW);

  // Wait for the chip to settle
  delayMicroseconds(100);

  tft.init(); // Initialize the screen
  tft.setRotation(3); // Set screen orientation (adjust if needed)

  // Set up the screen
  tft.fillScreen(TFT_BLACK); // Clear the screen
  tft.setTextColor(TFT_WHITE); // Set text color to white
  tft.setTextSize(1); // Set text size

while (1==1) {
  
  // Read values from the MSGEQ7 and store them in the matrix
  for (int band = 0; band < 7; band++) {

    digitalWrite(STROBE_PIN, HIGH);
    delayMicroseconds(30);              // ts  18uS min
    digitalWrite(STROBE_PIN, LOW);
    delayMicroseconds(40);              // to settling time 36uS min
    // Read the analog value from the selected band
    int value = analogRead(ANALOG_PIN);

    // Store the value in the matrix
    matrix[band] = value / 40; // scale 
  }

  // Display the bar graph
  drawBarGraph();
  delay (300);
  tft.fillScreen(TFT_BLACK); // Clear the screen
  }
}

void drawBarGraph() {
  int barWidth = tft.width() / matrixSize; // Calculate width of each bar
  int maxHeight = tft.height(); // Maximum height of bars

  for (int i = 0; i < matrixSize; i++) {
    int barHeight = map(matrix[i], 0, maxHeight, 0, maxHeight); // Map the data to screen height
    int xPos = i * barWidth; // Calculate x position of the bar
    int yPos = maxHeight - barHeight; // Calculate y position of the bar

    // Draw the bar
    tft.fillRect(xPos, yPos, barWidth - 1, barHeight, TFT_BLUE); // Draw a filled rectangle

    // Optional: Display the value above the bar
    tft.setCursor(xPos + barWidth / 2 - 3, yPos - 10); // Set cursor position
    tft.print(matrix[i]); // Print the value
  }
}

void loop() {
  // Your main code here (if needed)
}