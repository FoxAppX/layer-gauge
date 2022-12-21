/*  Программа Толщиномер 1.0
 *  Прошивка для микроконтроллера ESP-32
 *  Автор: Иван Чуманов
*/ 

  // Объявление переменных с номерами пинов для фотодиода и светодиода
int DAC = 25;  
int PDIODE = 12;  
  // Объявление вспомогательных переменных
char command;  
String string; 
int diodeValue = 0;

void setup() {
  // Установка скорости обмена данными
Serial.begin(115200);
  // Переключение пина 25 (ЦАП) на вывод
pinMode(DAC, OUTPUT);
}

void loop() {
  // Бесконечный цикл выполнения программы

if (Serial.available() > 0)
{
  string = ""; // Очистка переменной перед записью
}

  // Цикл чтения данных из порта ввода/вывода
while(Serial.available() > 0)
{
  command = ((byte)Serial.read());
  if(command == ':')
  {
    break;
  }
  else
  {
    string += command;
  }
  delay(1);
}

  // Расшифровка прочитанной команды
if(string.substring(0, 2) == "p1")
{
  // Включение светодиода с заданной яркостью через ЦАП
  dacWrite(DAC, string.substring(3, string.length()).toInt());
}
if(string.substring(0, 2) == "p0")
{
  // Отключение светодиода
  dacWrite(DAC, 0);
}

  // Чтение данных с АЦП и отправка в буфер
diodeValue = analogRead(PDIODE);
Serial.println(diodeValue);

delay(500); // небольшая задержка между следующей итерацией
}
