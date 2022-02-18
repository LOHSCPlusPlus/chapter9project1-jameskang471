#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Cars{
    enum {MAX_CHAR_LEN=100};
    char carName[MAX_CHAR_LEN];
    double MPG;
    int Cylinders;
    double Displacement;
    double Horsepower;
    double Weight;
    double Acceleration;
    int Model;
    char Origin[MAX_CHAR_LEN];
    bool ValidEntry;
    Cars();
    
};

Cars::Cars() {
  for (int num = 0; num <MAX_CHAR_LEN; num++) {
    carName[num] = '\0';
    Origin[num] = '\0';
  }
  MPG = 0.0;
  Cylinders = 0;
  Displacement = 0.0;
  Horsepower = 0.0;
  Weight = 0.0;
  Acceleration = 0.0;
  ValidEntry = false;
}
const int MAX_CARS=500;
Cars readCarData(ifstream &inFile){
    Cars cars; 
    inFile.get(cars.carName, Cars::MAX_CHAR_LEN, ';');
    inFile.ignore(100,';');
    inFile >> cars.MPG;
    inFile.ignore(100,';');
    inFile >> cars.Cylinders;
    inFile.ignore(100,';');
    inFile >> cars.Displacement;
    inFile.ignore(100,';');
    inFile >> cars.Horsepower;
    inFile.ignore(100,';');
    inFile >> cars.Weight;
    inFile.ignore(100,';');
    inFile >> cars.Acceleration;
    inFile.ignore(100,';');
    inFile >> cars.Model;
    inFile.ignore(100,';');
    inFile.get(cars.Origin, Cars::MAX_CHAR_LEN, '\n');
    // If we reached the end of the file while reading, then the entry is not valid
    cars.ValidEntry = !inFile.eof();
    return cars;
}

void printCars(Cars carList, int num) {
  if(carList.ValidEntry == true) { // idk 
  cout << "Index " << num << ":  " << endl;
  cout << "Car Name " << carList.carName << ";" << endl;
  cout << "MPG " << carList.MPG << ";" << endl;
  cout << "Cylinders " <<carList.Cylinders << ";" << endl;
  cout << "Displacement " <<carList.Displacement << ";" << endl;
  cout << "Horsepower " << carList.Horsepower << ";" << endl;
  cout << "Weight " << carList.Weight << ";" << endl;
  cout << "Acceleration " << carList.Acceleration << ";" << endl;
  cout << "Model " << carList.Model << ";" << endl;
  cout << "Origin " << carList.Origin << ";" << endl;
  cout << endl;
    }
  }

void printCarsByOrigin(Cars cars[], char userOrigin[]) {
  for (int num = 0; num < 500; num++) {
    if(strcmp(cars[num].Origin, userOrigin) == 0) {
      printCars(cars[num], num);
    }
  }
}
int readInt(const char prompt[]) {
    int temp = 0;
    cout << prompt;
    cin >> temp;
    while (!cin) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Invalid Data!" << endl;
        cout << prompt;
        cin >> temp;
    }
    return temp;
}
double readDouble(const char prompt[]) {
      int temp = 0.0;
    cout << prompt;
    cin >> temp;
    while (!cin) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Invalid Data!" << endl;
        cout << prompt;
        cin >> temp;
    }
    return temp;
}


void removeCar(Cars cars[]) { // doesnt make sense
int number = 0;
  number = readInt("what index of car do u want to remove(number)");
  cout << endl;
  cars[number].ValidEntry = false;
}

void addCar(Cars cars[], int carSize) {
  bool isCarAdded = false;
  for (int num = 0; num < 500; num++) {
    int tempInt = 0;
    double tempDouble = 0.0;
    if (cars[num].ValidEntry == false) {
      cout << "You are going to modify car #" << num << endl;
      cout << "Name: ";
      cin.ignore(100, '\n');
      cin.getline(cars[num].carName,carSize);

      tempDouble = readDouble("\nMPG: ");
      cars[num].MPG = tempDouble;
      tempInt = readInt("\nCylinders: ");
      cars[num].Cylinders = tempInt;
      tempDouble = readDouble("\nDisplacement: ");
      cars[num].Displacement = tempDouble;
      tempDouble = readDouble("\nHorespower: ");
      cars[num].Horsepower = tempDouble;
      tempDouble = readDouble("\nWeight: ");
      cars[num].Weight = tempDouble;
      tempDouble = readDouble("\nAcceleration: ");
      cars[num].Acceleration = tempDouble;
      tempInt = readInt("\nModel: ");
      cars[num].Model = tempInt;    
      cout << "\nOrigin: "; 
      cin.ignore(100, '\n');
      cin.getline(cars[num].Origin,carSize);
    
      cars[num].ValidEntry = true;
      isCarAdded = true;
      break;
    }
  }
      if (isCarAdded == false) {
      cout << "The array is full" << endl;
    }
}


int Menu() {
  int menuChoice = 0;
  cout << "Welcome to the car selector" << endl;
  cout << "Choose one option by entering a number below" << endl;
  cout << "1. Display the car list" << endl;
  cout << "2. Display cars by origin " << endl;
  cout << "3. Add a car to the list" << endl;
  cout << "4. Remove a car from the list" << endl;
  cout << "5. Quit" << endl;
  cout << "Input: ";
  cin >> menuChoice;
  cout << endl;
  return menuChoice;
}

int main() {
   ifstream carsFile("cars.txt");
  Cars carList[500];
  int menuChoice = 0;
  int carChoice = 0;
  int count = 0;
  char userOrigin[100];

while (carsFile.peek() != EOF) {
  carList[count] = readCarData(carsFile);
  count++;
}

  //count = readCarData(carList);
  

  menuChoice = Menu();

  while(menuChoice != 5) {
    switch (menuChoice) {

      case 1:
      cout << "car Number? (0-499): ";
      cin >> carChoice;
      cout << endl;
      printCars(carList[carChoice], carChoice);
      break;
    
      case 2:
      cout << "Origin? (Japan, US, Europe)";
      cin >> userOrigin;
      cout << endl;
      printCarsByOrigin(carList, userOrigin);
      break;
    
      case 3:
      addCar(carList, count);
      break;
      
      case 4: 
      removeCar(carList);
      break;

      case 5:
      break;

      default :
      cout << "Invalid. Try again" << endl;
      break;
}
menuChoice = Menu();
}
}

