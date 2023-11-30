#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int memoria[] = {0, 0, 0, 0, 0, 0, 0, 0};
int acc = 0;

struct position {

  string mem_reference;
  int mem_value;
};

vector<position> positions{{"D1", 1}, {"D2", 2}, {"D3", 3}, {"D4", 4},
                           {"D5", 5}, {"D6", 6}, {"D7", 7}, {"D8", 8}};

int obtenerValor(const string &position) {
  int position_value = 0;
  for (int i = 0; i < 8; ++i) {
    if (position == positions[i].mem_reference) {
      position_value = positions[i].mem_value;
      break;
    }
  }
  return position_value;
}

void limpiarMemoria() {

  for (int &i : memoria) {
    i = 0;
  }
  acc = 0;
};

void set(const string &position, int value, const string &add_arg_three = "",
         const string &add_arg_four = "") {

  int position_value = obtenerValor(position);
  memoria[position_value - 1] = value;
}

void ldr(const string &position, const string &add_arg_two = "",
         const string &add_arg_three = "", const string &add_arg_four = "") {
  int position_value = obtenerValor(position);
  acc = acc + memoria[position_value - 1];
}

void add(const string &position, const string &add_arg_two = "",
         const string &add_arg_three = "", const string &add_arg_four = "") {

  int position_value = obtenerValor(position);
  acc = acc + memoria[position_value - 1];
}

void inc(const string &position, const string &add_arg_two = "",
         const string &add_arg_three = "", const string &add_arg_four = "") {

  int position_value = obtenerValor(position);
  memoria[position_value - 1] = memoria[position_value - 1] + 1;
}

void dec(const string &position, const string &add_arg_two = "",
         const string &add_arg_three = "", const string &add_arg_four = "") {

  int position_value = obtenerValor(position);
  memoria[position_value - 1] = memoria[position_value - 1] - 1;
}

void str(const string &position, const string &add_arg_two = "",
         const string &add_arg_three = "", const string &add_arg_four = "") {

  int position_value = obtenerValor(position);
  memoria[position_value - 1] = acc;
}

void shw(const string &position, const string &add_arg_two = "",
         const string &add_arg_three = "", const string &add_arg_four = "") {

  if (position == "D1" or position == "D2" or position == "D3" or
      position == "D4" or position == "D5" or position == "D6" or
      position == "D7" or position == "D8") {
    int position_value = obtenerValor(position);
    cout << "Show: " << memoria[position_value - 1] << endl;

  } else if (position == "ACC") {
    cout << "ACC: " << acc << endl;
  }
}

void terminar(const string &add_arg_one, const string &add_arg_two = "",
              const string &add_arg_three = "",
              const string &add_arg_four = "") {
  shw("ACC");
  limpiarMemoria();
}

void pausa(const string &add_arg_one, const string &add_arg_two = "",
           const string &add_arg_three = "", const string &add_arg_four = "") {}

void procesos(const string &command, const string &arg1, const string &arg2,
              const string &arg3, const string &arg4) {

  if (command == "SET") {
    set(arg1, stoi(arg2), arg3, arg4);
  }

  else if (command == "LDR") {
    ldr(arg1, arg2, arg3, arg4);
  }

  else if (command == "ADD") {
    add(arg1, arg2, arg3, arg4);
  }

  else if (command == "STR") {
    inc(arg1, arg2, arg3, arg4);
  }

  else if (command == "STR") {
    dec(arg1, arg2, arg3, arg4);
  }

  else if (command == "STR") {
    str(arg1, arg2, arg3, arg4);
  }

  else if (command == "SHW") {
    shw(arg1, arg2, arg3, arg4);
  }

  else if (command == "PAUSE") {
    pausa(arg1, arg2, arg3, arg4);
  }

  else if (command == "END") {
    terminar(arg1, arg2, arg3, arg4);
  }

  else {
    cerr << "Unknown command: " << command << endl;
  }
}

void load_program(const string &txt_file) {
  string file_path = "../Programs/" + txt_file + ".txt";
  ifstream inputFile(file_path);

  if (!inputFile.is_open()) {
    cerr << "Error opening file." << endl;
    return;
  }

  string line;
  while (getline(inputFile, line)) {
    istringstream iss(line);
    string command, arg1, arg2, arg3, arg4;

    if (iss >> command >> arg1 >> arg2 >> arg3) {

      if (arg1 == "NULL")
        arg1 = "";
      if (arg2 == "NULL")
        arg2 = "";
      if (arg3 == "NULL")
        arg3 = "";

      procesos(command, arg1, arg2, arg3, "");
    } else {
      cerr << "Error parsing line: " << line << endl;
    }
  }

  inputFile.close();
}

int main() {

  string txt_file;
  bool execution = true;
  while (execution) {
    int menu_option;
    cout << endl
         << "*======================================================*" << endl;
    cout << "*           Seleccione una opcion            *" << endl;
    cout << "*======================================================*" << endl;
    cout << endl << "      1 > Cargando carpeta" << endl;
    cout << "      0 > Exit" << endl;
    cout << endl
         << "*======================================================*" << endl;
    cin >> menu_option;

    switch (menu_option) {
    case 0:
      cout << "saliendo del programa" << endl;
      execution = false;
      break;
    case 1:
      cout << "Nombre de la carpeta";
      cin >> txt_file;
      load_program(txt_file);
      break;

    default:
      break;
    }
  }
  return 0;
}
