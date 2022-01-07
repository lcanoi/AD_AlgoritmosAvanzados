#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Guarda un archivo .txt en una string
string fileToString(ifstream &file) {
    string txt="";
    string st;
    if(file.is_open())
        while (!file.eof()){
            getline(file, st);
            txt+=st;
        }
    return txt;
}

// Inicializa 'lps' para un patrón de tamaño N
void computeLPSArray(string pat, int M, vector<int>& lps)
{
    // variable que guarda el tamaño del último prefijo que
    // también es sufijo más largo
    int len = 0;
  
    lps[0] = 0; // lps[0] siempre es 0
  
    // el ciclo calcula lps[i] de i = 1 a M-1
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            if (len != 0) {
                len = lps[len - 1];
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Regresa el índice de la ocurrencia de pat en txt
int KMPSearch(string pat, string txt)
{
    int M = pat.length();
    int N = txt.length();
  
    // crea lps que contendrá los mayores valores de
    // prefijo sufijo para el patrón
    vector<int> lps(M,0);
  
    // Preprocesar el patrón (calcular la matriz lps)
    computeLPSArray(pat, M, lps);
  
    int i = 0; // index de txt
    int j = 0; // index de pat
    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
  
        if (j == M) {
            return i-j;
        }
        // cuando un caracter no coincide
        else if (i < N && pat[j] != txt[i]) {
            // los caracteres lps[0..lps[j-1]] coinciden
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return -1;
}

// Longest Common Substring
// Regresa los índices (inicio, fin) iniciando en 1 
// del substring común más largo de t1 y t2
pair<int, int> LCSubStr(string t1, string t2)
{
    
    int M = t1.length();
    int N = t2.length();

    // Crea matriz para almacenar las longitudes
    // de los sufijos de substrings más largos.
    // Tamaño de la matriz: [M + 1][N + 1]
    // LCSuff[i][j] contiene la longitud del sufijo
    // más largo de t1[0..i-1] y t2[0..j-1]
    vector< vector<int> > LCSuff;
    for(int i=0;i<=M;i++){
        LCSuff.push_back(vector<int>(N+1,0));
    }

    int result = 0; // Para guardar la longitud del
                    // substring común mayor
    
    int pos=0;

    // Construye LCSuff[M+1][N+1] de manera bottom up
    for (int i = 0; i <= M; i++)
    {
        for (int j = 0; j <= N; j++)
        {
            // Las entradas de la primer fila y columna
            // no tienen significado lógico, se utilizan
            // solo para simplificar el programa
            if (i == 0 || j == 0)
                LCSuff[i][j] = 0;
 
            else if (t1[i - 1] == t2[j - 1]) {
                LCSuff[i][j] = LCSuff[i - 1][j - 1] + 1;
                if(LCSuff[i][j]>result){
                    result = LCSuff[i][j];
                    pos=i-result+1;
                }            

            }
            else
                LCSuff[i][j] = 0;
        }
    }
    return make_pair(pos, pos+result-1);
}

// Implementacion de Manacher para longest palindromic substring
vector <int> createLPS(string s)
{
	int n = s.size();
    // arreglo con los tamaños de los palíndromos
	vector <int> p(n, 1);
	int l = 0;
	int r = -1;
	int k, j;
	for(int i=1; i<n-1; i++)
	{
		// se arreglan las fronteras para el palíndromo
        if (i > r) 
		{
			k = 0;
		}
		else 
		{
			j = l + r - i;
			k = min(p[j], r-i);
		}
        // expandir el palíndromo si es posible
		while (i-k >= 0 && i+k < n && s[i-k] == s[i+k])
			k++;
        // casos en los extremos del ciclo
		if ((i-k) < 0 || s[i-k] != s[i+k])
			k--;
        // asignar el tamaño del palíndromo al
        // centro actual (i)
		p[i] = k;
        
        // ajustar a l y r al inicio y final del
        // palíndromo
		if (i + k > r)
		{
			l = i - k;
			r = i + k;
		}
	}
	return p;
}

pair<int, int> lps(string transmission) {
    
    // Agrega un símbolo entre cada carácter para arreglar
    // el punto de simetría en palíndromos de tamaño par
    string s = "$";
    for(int i =0; i < transmission.size(); i++)
	{
		s.push_back(transmission[i]);
		s.push_back('$');
	}

    // Creamos el arreglo auxiliar de longitudes máximas
    // de palíndromo
    vector<int> lpsr = createLPS(s);
    
    // Buscamos a max, la longitud del palíndromo
    // y a index, el centro del palíndromo
    int max = 0;
    int index = 1;
    for(int i=0;i<lpsr.size();i++){
        if(lpsr[i] > max) {
            max = lpsr[i];
            index = i;
        }
    }

    // Se arregla index para desconsiderar a los
    // símbolos de "$" agregados al inicio
    index = (index+1) / 2;
    
    // index es el centro del palíndromo
    // regresamos el inicio y el fin de él
    return make_pair(index-(max%2?max/2:max/2-1),index+max/2);
}

int main()
{
    // Archivos predeterminados de entrada
    ifstream transmission1, transmission2, mcode1, mcode2, mcode3;
    transmission1.open("transmission1.txt");
    transmission2.open("transmission2.txt");
    mcode1.open("mcode1.txt");
    mcode2.open("mcode2.txt");
    mcode3.open("mcode3.txt");

    // ifstream test1, test2;
    // test1.open("test1.txt");
    // test2.open("test2.txt");
    // string tt1 = fileToString(test1);
    // string tt2 = fileToString(test2);
    
    // Almacenar todos los archivos en strings
    string t1, t2, m1, m2, m3;
    t1 = fileToString(transmission1);
    t2 = fileToString(transmission2);
    m1 = fileToString(mcode1);
    m2 = fileToString(mcode2);
    m3 = fileToString(mcode3);

    string ts[2] = {t1, t2};
    string ms[3] = {m1, m2, m3};

    // Parte 1
    /* Analiza si el contenido de m1, m2 y m3 está
       contenido en el texto de t1 y t2, desplegando
       true o false. En caso de haberlo encontrado, 
       adicionalmente desplega la posición en el archivo
       de transmission en dónde se encontro el mcode */
    int result;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            result = KMPSearch(ms[j], ts[i]);
            if (result != -1)
                cout << "true" << " " << result << endl;
            else
                cout << "false" << endl;
        }
    }

    //Parte 2
    /* Busca el palíndromo más largo para t1 y t2,
       desplegando los índices iniciando en 1 en dónde
       inicia y termina el palíndromo mayor de cada uno */
    pair<int, int> res1 = lps(t1);
    pair<int, int> res2 = lps(t2);
    cout << res1.first << " " << res1.second << endl;
    cout << res2.first << " " << res2.second << endl;
    
    // Parte 3
    /* Obtiene el substring más largo entre t1 y t2
       (Los archivos de transmisión) e imprime la
       posición inicial y final iniciando en 1 del
       substring en el primer archivo */
    pair<int, int> lcsResult = LCSubStr(t1, t2);
    cout << lcsResult.first << " " << lcsResult.second << endl;
        
    return 0;
}

// Output:
// false
// true 7550
// false
// false
// false
// true 4933
// 5516 6728
// 847 1015
// 5517 6122