// Define pin connections
const int soilMoisturePin = A0; // Analog pin for the soil moisture sensor
const int relayPin = 3;         // Digital pin connected to the relay signal pin

// Define moisture thresholds
// These values are sensor-dependent and need calibration
const int dryValue = 600;  // Value when soil is considered dry (higher number for dry soil on many sensors)
const int wetValue = 300;  // Value when soil is considered adequately wet

void setup() {
  Serial.begin(9600);           // Start serial communication for debugging
  pinMode(relayPin, OUTPUT);    // Set the relay pin as an output
  digitalWrite(relayPin, HIGH); // Initialize the pump as OFF (HIGH is typically OFF for active-LOW relays)
}

void loop() {
  // Read the analog value from the soil moisture sensor
  int soilMoistureValue = analogRead(soilMoisturePin);

  // Print the raw sensor value to the Serial Monitor
  Serial.print("Soil Moisture Value: ");
  Serial.println(soilMoistureValue);

  // Check if the soil is dry (value is greater than the dry threshold)
  if (soilMoistureValue > dryValue) {
    // Soil is dry, turn the pump ON (LOW is typically ON for active-LOW relays)
    digitalWrite(relayPin, LOW);
    Serial.println("--- Soil is DRY, PUMP ON ---");
    
    // Wait for the pump to water the plant for a set duration (e.g., 2 seconds)
    delay(2000); 

    // Turn the pump OFF
    digitalWrite(relayPin, HIGH);
    Serial.println("--- PUMP OFF ---");
  } else {
    // Soil moisture is adequate, ensure pump is OFF
    digitalWrite(relayPin, HIGH);
    Serial.println("Soil is WET enough, PUMP OFF.");
  }

  // Wait a while before taking the next reading (e.g., every 5 minutes = 300000 milliseconds)
  // This prevents continuous pumping and allows the water to soak in.
  delay(300000); 
}