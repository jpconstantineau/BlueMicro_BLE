int row1 = 26;
int row2 = 27;
int row3 = 28;
int row4 = 21;
int val;

byte rows[] { 12, 13, 14, 16 };
byte columns[] { 2, 3, 4, 5, 28, 29};

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

      delay(1);
      
      //just a testing to see if a button was pressed
      if (digitalRead(column) == LOW) {
        Serial.print("LOW: "); Serial.print(column); Serial.print(", "); Serial.println(row);
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
