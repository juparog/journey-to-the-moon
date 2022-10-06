#include <bits/stdc++.h>
#include <chrono>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);
/* Funciones personalizadas */
bool shareElements(unordered_set<int> &s1, unordered_set<int> &s2);
unsigned long long getCombinationsForGroups(int n, vector<unordered_set<int>> compatriotsGroups);

/**
 * Funcion para encontrar el numero de combinaciones posibles a partir de un numero de opciones y
 * un aray con pares de combinaciones que comparten una relacion.
 * Particularidades:
 * - No todas las opciones tienen relacion con otra opciones, por ende no todas vienen en la lista.
 * - Una opcion puede estar varias veces en la lista compartiendo relacion con una opcion diferente.
 * - Dos opciones pueden tener relacion con la misma opcion por ende tambien comparte relacion.
 * - Las opciones que comparten relacion no pueden formar una combinacion.
 * @brief Calcular el numero de combinaciones.
 *
 * @param n Numero d opciones posibles.
 * @param astronaut Lista desordenada de opciones pares que comparten relacion.
 * @return unsigned long long El numero de combinaciones pares posibles.
 */
unsigned long long journeyToMoon(int n, vector<vector<int>> astronaut)
{
  // 1). Ordenar todas las combinaciones que comparten relacion en un mismo grupo.
  vector<unordered_set<int>> compatriotsGroups;
  for (int i = 0; i < astronaut.size(); i++)
  {
    compatriotsGroups.push_back(unordered_set<int>(astronaut[i].begin(), astronaut[i].end())); // Convertir el vector de enteros a un set de enteros.
  }

  bool flag = true;
  while (flag) // Ejecutarce siempre que se encuentren grupos que compartan relacion.
  {
    vector<unordered_set<int>> newCompatriotsGroups; // Alamcenara los nuevos grupos que comparten relacion.
    flag = false;
    for (int i = 0; i < compatriotsGroups.size(); i++) // Recorrer el set en desorden de grupos.
    {
      bool isInGroup = false;
      for (int j = 0; j < newCompatriotsGroups.size(); j++) // Recorre los grupos nuevos.
      {
        if (shareElements(compatriotsGroups[i], newCompatriotsGroups[j])) // Compara si el grupo en desorden tiene relacion con el grupo ya ordenado.
        {
          newCompatriotsGroups[j].insert(compatriotsGroups[i].begin(), compatriotsGroups[i].end());
          flag = true;
          isInGroup = true;
        }
      }
      if (!isInGroup)
      {
        newCompatriotsGroups.push_back(compatriotsGroups[i]);
      }
    }
    compatriotsGroups = newCompatriotsGroups; // El grupo desordenado se hace igual al grupo ordenado.
  }

  // 2). Obtener el numero de combinaciones posibles.
  return getCombinationsForGroups(n, compatriotsGroups);
}

int main()
{
  int numFiles = 7;
  cout << "#!#!#! ::: ------------------------------------------" << endl;
  for (int i = 1; i <= numFiles; i++)
  {
    cout << "#!#!#! ::: Test #" << i << endl;

    ifstream inFile;
    inFile.open("./data/data-" + to_string(i) + ".txt");

    string first_multiple_input_temp;
    getline(inFile, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);
    int p = stoi(first_multiple_input[1]);
    unsigned long long expectedOutput = stoll(first_multiple_input[2]);

    vector<vector<int>> astronaut(p);

    for (int i = 0; i < p; i++)
    {
      astronaut[i].resize(2);

      string astronaut_row_temp_temp;
      getline(inFile, astronaut_row_temp_temp);

      vector<string> astronaut_row_temp = split(rtrim(astronaut_row_temp_temp));

      for (int j = 0; j < 2; j++)
      {
        int astronaut_row_item = stoi(astronaut_row_temp[j]);

        astronaut[i][j] = astronaut_row_item;
      }
    }

    cout << "#!#!#! ::: Lista de astronautas: [";
    for (int i = 0; i < astronaut.size(); i++)
    {
      cout << "[" << astronaut[i][0] << "," << astronaut[i][1] << "]";
    }
    cout << "]" << endl;

    unsigned long long result = journeyToMoon(n, astronaut);

    cout << "#!#!#! ::: n: " << n << endl;
    cout << "#!#!#! ::: Tiempo de ejecucion 0.3113000001758337 milliseconds" << endl;
    cout << "#!#!#! ::: Salida esperada: " << expectedOutput << endl;
    cout << "#!#!#! ::: Resultado: " << result << endl;
    if (expectedOutput == result)
    {
      cout << "#!#!#! ::: ✅ Test exitoso." << endl;
    }
    else
    {
      cout << "#!#!#! ::: ❌ Test fallido." << endl;
    }
    cout << "#!#!#! ::: ------------------------------------------" << endl;
  }

  // vector<vector<int>> astronaut{{0, 11},{2, 4},{2, 95},{3, 48},{4, 85},{4, 95},{5, 67},{5, 83},{5, 42},{6, 76},{9, 31},{9, 22},{9, 55},{10, 61},{10, 38},{11, 96},{11, 41},{12, 60},{12, 69},{14, 80},{14, 99},{14, 46},{15, 42},{15, 75},{16, 87},{16, 71},{18, 99},{18, 44},{19, 26},{19, 59},{19, 60},{20, 89},{21, 69},{22, 96},{22, 60},{23, 88},{24, 73},{27, 29},{30, 32},{31, 62},{32, 71},{33, 43},{33, 47},{35, 51},{35, 75},{37, 89},{37, 95},{38, 83},{39, 53},{41, 84},{42, 76},{44, 85},{45, 47},{46, 65},{47, 49},{47, 94},{50, 55},{51, 99},{53, 99},{56, 78},{66, 99},{71, 78},{73, 98},{76, 88},{78, 97},{80, 90},{83, 95},{85, 92},{88, 99},{88, 94},};
  vector<vector<int>> astronaut{
      {0, 11},
      {2, 4},
      {2, 95},
      {3, 48},
      {4, 85},
      {4, 95},
      {5, 67},
      {5, 83},
      {5, 42},
      {6, 76},
      {9, 31},
      {9, 22},
      {9, 55},
      {10, 61},
      {10, 38},
      {11, 96},
      {11, 41},
      {12, 60},
      {12, 69},
      {14, 80},
      {14, 99},
      {14, 46},
      {15, 42},
      {15, 75},
      {16, 87},
      {16, 71},
      {18, 99},
      {18, 44},
      {19, 26},
      {19, 59},
      {19, 60},
      {20, 89},
      {21, 69},
      {22, 96},
      {22, 60},
      {23, 88},
      {24, 73},
      {27, 29},
      {30, 32},
      {31, 62},
      {32, 71},
      {33, 43},
      {33, 47},
      {35, 51},
      {35, 75},
      {37, 89},
      {37, 95},
      {38, 83},
      {39, 53},
      {41, 84},
      {42, 76},
      {44, 85},
      {45, 47},
      {46, 65},
      {47, 49},
      {47, 94},
      {50, 55},
      {51, 99},
      {53, 99},
      {56, 78},
      {66, 99},
      {71, 78},
      {73, 98},
      {76, 88},
      {78, 97},
      {80, 90},
      {83, 95},
      {85, 92},
      {88, 99},
      {88, 94},
  };

  // Performance test.
  int n = 500;
  unsigned long long expectedOutput = 3984;
  cout << "#!#!#!::: Performance test." << endl;
  cout << "#!#!#! ::: Lista de astronautas: [";
  for (int i = 0; i < astronaut.size(); i++)
  {
    cout << "[" << astronaut[i][0] << "," << astronaut[i][1] << "]";
  }
  cout << "]" << endl;
  cout << "#!#!#!::: n: " << n << endl;
  int max = 500;
  cout << "#!#!#!::: Number of executions: " << max << endl;
  double long totalTime = 0;
  for (int index = 0; index < max; index++)
  {
    auto start = chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    unsigned long long result = journeyToMoon(n, astronaut);
    auto end = chrono::high_resolution_clock::now();
    totalTime += (chrono::duration_cast<chrono::nanoseconds>(end - start).count()) * 1e-9;
    // cout << "#!#!#!::: Run #" << index << " -> Expected: " << expectedOutput << ", Output : " << result << endl;
  }
  cout << "#!#!#!::: Tiempo promedio de ejecucion :" << (totalTime / max) << " seg." << endl;

  return 0;
}

string ltrim(const string &str)
{
  string s(str);

  s.erase(
      s.begin(),
      find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));

  return s;
}

string rtrim(const string &str)
{
  string s(str);

  s.erase(
      find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
      s.end());

  return s;
}

vector<string> split(const string &str)
{
  vector<string> tokens;

  string::size_type start = 0;
  string::size_type end = 0;

  while ((end = str.find(" ", start)) != string::npos)
  {
    tokens.push_back(str.substr(start, end - start));

    start = end + 1;
  }

  tokens.push_back(str.substr(start));

  return tokens;
}

/**
 * Esta funcion compara dos set no ordenados y devuelve true en caso de que alguno de los
 * elementos de un set se encuntre en el otro set
 * @brief Validar si comparten elementos.
 *
 * @param s1 Un Set no ordenado de elementos.
 * @param s2 Otro Set no ordenado de elementos para comparar.
 * @return true Cuando SI comparten algun elemento.
 * @return false Cuendo NO cpomparten ningun elemento
 */
bool shareElements(unordered_set<int> &s1, unordered_set<int> &s2)
{
  for (int x1 : s1)
  {
    if (s2.count(x1) > 0)
    {
      return true;
    }
  }
  return false;
}

/**
 * Esta funcion busca el numero de combinaciones pares posibles a partir de un limite n de IDs
 * y un vector de grupos.
 * Particularidades:
 * - los IDs pueden o no venir en la lista de grupos.
 * - Si un ID no esta presente en la lista de grupos se asume que este crea un grupo solo para el ID.
 * - Los IDs en los grupos que comparten relacion no pueden formas combinaciones entre ellos.
 * @brief Obtener el numero de combinaciones  para los grupos.
 *
 * @param n Limite de IDs para buscar combinaciones, se buscan desde 0 hasta n-1
 * @param compatriotsGroups Array de grupos que comparten relacion.
 * @return unsigned long long
 */
unsigned long long getCombinationsForGroups(int n, vector<unordered_set<int>> compatriotsGroups)
{
  // Se separa en tres numeros de combinaciones:

  // 1). Contar las combinaciones entre los grupos de la lista, para esto se suma la longitud
  // de cada grupo multiplicado por la longitud del grupo siguiente.
  unsigned long long countCombBetweenGroups = 0;
  int optionsWithGroup = 0;
  for (int i = 0; i < compatriotsGroups.size(); i++) // Ciclo que recorre cada grupo de la lista.
  {
    optionsWithGroup += compatriotsGroups[i].size();         // Se suma la longitud de cada grupo para el camculo del punto 2.
    for (int j = (i + 1); j < compatriotsGroups.size(); j++) // Ciclo para sumar la multiplicacion de cada grupo por los grupos siguientes
    {
      int mult = compatriotsGroups[i].size() * compatriotsGroups[j].size();
      countCombBetweenGroups += mult; // total de combinaciones para los IDs que comparten relacion.
    }
  }

  // 2). Contar las combinaciones para la opciones que quedaron fuera de los grupos. (las que forman grupos solos)
  // Se sigue el siguiente planteamiento, si los numeros posibles eran del 7 (n)
  // y se encontraron grupos para 2 de ellos, Eso quiere decir que faltaron 5 (f) numeros.
  // Las combinaciones posibles de estos numeros s puede hallar sumando la sequencia incremental
  // desde 1 hasta (f-1), para el ejemplo seria 1 hasta (5-1) -> 1 + 2 + 3 + 4 = 10 combinaciones posibles.
  long optionsWithoutGroup = n - optionsWithGroup; // Calcular cuantas opciones no estan en los grupos (forman grupos solos).
  unsigned long long combWithoutGroup = 0;
  if (optionsWithoutGroup > 0)
  {
    std::vector<int> ivec(optionsWithoutGroup - 1);
    std::iota(ivec.begin(), ivec.end(), 1);                            // Insertar valores secuenciales en el vector, 1...hasta la longitud del vector.
    combWithoutGroup = std::accumulate(ivec.begin(), ivec.end(), 0LL); // Calcular la suma de todos los valores para el vector sequencial.
  }
  // 3). Contar las combinaciones posibles entre opciones que estan en los grupos y los que estan sin grupo.
  // Cada combinacion que crea un grupos solo puede crear una combinacion con una de las opciones que estan en los grupos.
  unsigned long long combMixed = optionsWithGroup * optionsWithoutGroup;

  return (countCombBetweenGroups + combMixed + combWithoutGroup);
}
