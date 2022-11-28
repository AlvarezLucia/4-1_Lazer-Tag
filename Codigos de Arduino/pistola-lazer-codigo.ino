int shoot;
int reload;
int bullets = 7;
int sw1 = 5;
int sw2 = 13;
int piezo = 9;
int laser = 11;

void setup()
{
  pinMode(laser, OUTPUT);
  pinMode(piezo, OUTPUT);
  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  Serial.begin(9600);
}

void loop()
{
  shoot = digitalRead(sw1);
  reload = digitalRead(sw2);
  Serial.print("shoot: ");
  Serial.println(shoot);
  Serial.print("reload: ");
  Serial.println(reload);
  if (bullets > 0)
  {
    if (shoot == LOW)
    {
      tone(piezo, 5000);
      delay(100);
      digitalWrite(laser, HIGH);
      delay(50);
      digitalWrite(laser, LOW);
      bullets--;
      delay(100);
    }
  }
  if (bullets <= 0);
  {
    if (shoot == LOW)
    {
      tone(piezo, 2500, 30);
      delay(100);
      tone(piezo, 450, 30);
    }
  }


  if (reload == LOW)
  {
    delay(2000);
    bullets = 7;
    tone(piezo, 100, 100);
    delay(100);
    tone(piezo, 150, 100);
    delay(100);
    tone(piezo, 190, 100);
    delay(100);
    tone(piezo, 250, 100);
  }
}
