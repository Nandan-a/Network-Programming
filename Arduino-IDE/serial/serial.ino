void setup() {
 Serial.begin(115200);
 Serial.println("Setup started");
}


void loop()
{
  // put your main code here, to run repeatedly:
    log_e("test - error");
    log_w("test - warning");
    log_i("test - info");
    log_d("test - debug");

    log_v("test-verbose");
    
    Serial.println("Testing serial output");
    Serial.println();

    delay(1000);
    }
