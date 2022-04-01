#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Alumno
{
  char codigo [5]; //no se esta tomando como una c-string
  char nombre [11];//es decir, codigo[4] puede ser un 
  char apellidos [20];//caracter diferente de '\0'
  char carrera [15];

  Alumno(){}

  Alumno(string a,string b,string c,string d){
    for(int i = 0; i < 5;++i){
      if(i < a.size()){
	codigo[i] = a[i];
      }else{
	codigo[i] = ' ';
      }

    }

    for(int i = 0; i < 11;++i){
      if(i < b.size()){
	nombre[i] = b[i];
      }else{
	nombre[i] = ' ';
      }

    }
    for(int i = 0; i < 20;++i){
      if(i < c.size()){
	apellidos[i] = c[i];
      }else{
	apellidos[i] = ' ';
      }

    }
    for(int i = 0; i < 15;++i){
      if(i < d.size()){
	carrera[i] = d[i];
      }else{
	carrera[i] = ' ';
      }

    }

  }

  void display(){

    for(int i = 0; i < sizeof(Alumno::codigo); ++i){
      cout<<codigo[i];
    }
    for(int i = 0; i < sizeof(Alumno::nombre); ++i){
      cout<<nombre[i];
    }
    for(int i = 0; i < sizeof(Alumno::apellidos); ++i){
      cout<<apellidos[i];
    }
    for(int i = 0; i < sizeof(Alumno::carrera); ++i){
      cout<<carrera[i];
    }
    cout<<'\n';


  }
};

class FixedRecord{
  string nombre_archivo;

  public:

  FixedRecord(string _nombre_archivo): nombre_archivo{_nombre_archivo}{}

  vector<Alumno> load(){
    ifstream ayuda;
    Alumno temp;
    vector<Alumno> retorno;

    ayuda.open(nombre_archivo,ios::in);
    int pos = 0;

    while(!ayuda.eof()){
      ayuda.seekg(pos*sizeof(Alumno) + pos);
      ayuda.read((char*)& temp, sizeof(Alumno));

      ayuda.get();
      ayuda.get();
      ++pos;
      retorno.push_back(temp);
    }

    ayuda.close();

    return retorno;

  }


  void add(Alumno& record){
    ofstream ayuda;
    ayuda.open(nombre_archivo,ios::out| ios::app);


    ayuda.write((char*)& record, sizeof(Alumno));
    ayuda.write("\n",1);

    ayuda.close();
  }

  Alumno readRecord(int pos){
    Alumno retorno;
    int go_in = sizeof(Alumno)*(pos) + pos;
    ifstream ayuda;
    ayuda.open(nombre_archivo);
    ayuda.seekg(go_in);

    ayuda.read((char*) &retorno,sizeof(Alumno));

    ayuda.close();


    return retorno;
  }


  int s(){
    ifstream ayuda;
    ayuda.open(nombre_archivo,ios::in|ios::out|ios::ate);

    int retorno = ayuda.tellg()/sizeof(Alumno);
    ayuda.close();
    return retorno;
  }


};

void inicializar_archivo(){
  fstream ayuda;
  ayuda.open("datos1.txt",ios::out);

  ayuda.close();

}

int main(){
  inicializar_archivo();

  FixedRecord relacion("datos1.txt");


  Alumno temp;

  temp = Alumno{"0001", "Howard","Paredes Zegarra","Computacion"};
  relacion.add(temp);
  temp = Alumno{"0002", "Penny","Vargas Cordero","Industrial"};
  relacion.add(temp);
  temp = Alumno{"0003", "Sheldon","Cooper Vega","Mecatronica"};
  relacion.add(temp);
  temp = Alumno{"0004", "Pamela","Vargas Cordero","Industrial"};
  relacion.add(temp);
  temp = Alumno{"0005", "Vanesa","Cooper Quizpe","Mecatronica"};
  relacion.add(temp);
  temp = Alumno{"0006", "Jesus", "Vega Cordero", "Industrial"};
  relacion.add(temp);
  temp = Alumno{"0007", "Heider", "Sanchez Quizpe", "Mecatronica"};
  relacion.add(temp);
  temp = Alumno{"0008", "Eric","Bracamonte" ,"CS" };
  relacion.add(temp);
  temp = Alumno{"0009", "Jose", "Lopez", "CS",  };
  relacion.add(temp);
  temp = Alumno{ "0010" ,"Juan" ,"Del Pino" , "CS"    };
  relacion.add(temp);
  temp = Alumno{  "0011", "Maria", "Castillo", "Veterinaria" };
  relacion.add(temp);
  temp = Alumno{  "0012", "Juan","Suarez", "Derecho" };
  relacion.add(temp);

  temp = Alumno{  "0013", "Pepe","Guitierrez", "Medicina" };
  relacion.add(temp);
  temp = Alumno{  "0014", "Jose","Ugarte", "Ing. Software" };
  relacion.add(temp);
  temp = Alumno{  "0015", "Jose","Ugarte", "Ing. Software" };
  relacion.add(temp);

  auto v = relacion.load();

  for(auto& a : v){
    a.display();
  }

  cout<<endl<<endl;



  relacion.readRecord(10).display();
  relacion.readRecord(5).display();
  relacion.readRecord(12).display();



  return 0;
}
