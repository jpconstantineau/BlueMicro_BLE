int row1 = 26;
int row2 = 27;
int row3 = 28;
int row4 = 21;
int val;

byte rows[] { 26, 27, 28, 21 };
byte columns[] { 15, 16, 17, 18, 5, 6 };

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
   pinMode(LED_BUILTIN, OUTPUT);

   //inits all the columns as INPUT
   for (auto& column : columns) {
      Serial.print("column ");
      Serial.print(column);
      Serial.println(" set to INPUT");
      pinMode(column, INPUT);
    }

   //inits all the rows as INPUT_PULLUP
   for (auto& row : rows) {
      Serial.print("row ");
      Serial.print(row);
      Serial.println(" set to INPUT_PULLUP");
    pinMode(row, INPUT_PULLUP);
    }
}

void readMatrix() {
  for(auto& row : rows) {

    //set the current row as OUPUT and LOW
    pinMode(row, OUTPUT);
    digitalWrite(row, LOW);

    //loops thru all of the columns
    for (auto& column : columns) {
      pinMode(column, INPUT_PULLUP);

      //just a testing to see if a button was pressed
      if (digitalRead(column) == HIGH) {
        Serial.print("HIGH: "); Serial.print(column); Serial.print(", "); Serial.println(row);
        delay(2000);
      }

      //'disables' the column that just got looped thru
      pinMode(column, INPUT);
      }

    //'disables' the row that was just pressed
    pinMode(row, INPUT);
    }  
}

void loop() {
  // put your main code here, to run repeatedly:
  readMatrix(); 
}
