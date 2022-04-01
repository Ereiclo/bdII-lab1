#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
using namespace std;

struct Alumno
{
  char codigo [5];
  char nombre [11];
  char apellidos [20];
  char carrera [15];

  int ciclo;
  float mensualidad;

  Alumno(){}
  Alumno(string a,string b,string c,string d,int x,float y){
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

    ciclo = x;
    mensualidad = y;
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
    cout<<ciclo<<" "<<mensualidad;

    cout<<'\n';


  }

};

class FixedRecord{
  string nombre_archivo;

  public:

  FixedRecord(string _nombre_archivo):
    nombre_archivo{_nombre_archivo}{ }

  vector<Alumno> load(){
    ifstream ayuda;
    vector<Alumno> retorno;
    Alumno temp;

    ayuda.open(nombre_archivo,ios::in | ios::binary);


    int pos = 0;
    int del_pos;

    while(!ayuda.eof()){
      ayuda.seekg((sizeof(Alumno) + 4 )*(pos+1) );

      ayuda.read((char*) &temp, sizeof(Alumno));
      ayuda.read((char*)&del_pos,4);

      if(del_pos == 0)
	retorno.push_back(temp);

      ayuda.get();
      ++pos;

    }

    ayuda.close();

    return retorno;

  }


  void add(Alumno& record){
    fstream ayuda;
    ayuda.open(nombre_archivo,ios::in | ios::binary);
    ayuda.seekp(sizeof(Alumno));
    int del_pos;
    int del_pos2 = 0;

    ayuda.read((char*) & del_pos,4);
    ayuda.close();


    if(del_pos == -1)
      ayuda.open(nombre_archivo,ios::app | ios::binary);
    else{
      ayuda.open(nombre_archivo,ios::out|ios::in|ios::binary);
      ayuda.seekg((sizeof(Alumno) + sizeof(int))*(del_pos+1) + sizeof(Alumno));
      int nuevo_del_pos;
      ayuda.read((char*)&nuevo_del_pos,sizeof(int));
      ayuda.seekp(sizeof(Alumno));
      ayuda.write((char*)&nuevo_del_pos,sizeof(int));
      ayuda.seekp((sizeof(Alumno) + sizeof(int))*(del_pos+1));
    }

    ayuda.write((char*) & record, sizeof(Alumno));
    ayuda.write((char*) &del_pos2,sizeof(int));


    ayuda.close();



  }

  Alumno readRecord(int pos){
    Alumno retorno;
    int go_in = (sizeof(Alumno) + sizeof(int))*(pos+1);
    ifstream ayuda;
    ayuda.open(nombre_archivo,ios::binary | ios::in);
    ayuda.seekg(go_in);

    ayuda.read((char*) &retorno, sizeof(Alumno));

    ayuda.close();


    return retorno;
  }

  void del(int pos){
    fstream ayuda;
    ayuda.open(nombre_archivo,ios::binary | ios::in | ios::out);
    int tope_del_stack;
    char entrada_nueva[sizeof(Alumno) - sizeof(int)- sizeof(float)];

    for(int i = 0;i < sizeof(Alumno) - sizeof(int) -sizeof(float);++i)
      entrada_nueva[i] = ' ';

    int nuevo_int = 0;
    float nuevo_float = 0;

    ayuda.seekg(sizeof(Alumno));
    ayuda.read((char*) & tope_del_stack, sizeof(int));

    ayuda.seekp((sizeof(Alumno) + 4)*(pos+1));
    ayuda.write(entrada_nueva,sizeof(Alumno)-sizeof(int) -sizeof(float));
    ayuda.write((char*)&nuevo_int,sizeof(int));
    ayuda.write((char*)&nuevo_float,sizeof(float));

    ayuda.write((char*)&tope_del_stack,sizeof(int));

    ayuda.seekp(sizeof(Alumno));
    ayuda.write((char*)&pos,sizeof(int));


    ayuda.close();




  }
  int s(){
    ifstream ayuda;
    ayuda.open(nombre_archivo,ios::in|ios::out|ios::ate|ios::binary);

    int retorno = ayuda.tellg()/sizeof(Alumno);
    ayuda.close();
    return retorno;
  }


};

void inicializar_archivo(){
  fstream ayuda;
  ayuda.open("datos2.dat",ios::out|ios::binary);


  for(int i = 0; i < sizeof(Alumno);++i){
    ayuda.write(" ",1);

  }
  int x = -1;
  ayuda.write((char*) &x,4);


  ayuda.close();

}

int main(){
  inicializar_archivo();

  FixedRecord relacion("datos2.dat");


  Alumno temp;

  temp = Alumno{"0001", "Howard","Paredes Zegarra","Computacion",1,134.5};
  relacion.add(temp);
  temp = Alumno{"0002", "Penny","Vargas Cordero","Industrial",4,134.5};
  relacion.add(temp);
  temp = Alumno{"0003", "Sheldon","Cooper Vega","Mecatronica",3,134.5};
  relacion.add(temp);
  temp = Alumno{"0004", "Pamela","Vargas Cordero","Industrial",7,134.5};
  relacion.add(temp);
  temp = Alumno{"0005", "Vanesa","Cooper Quizpe","Mecatronica",7,12134.151};
  relacion.add(temp);
  temp = Alumno{"0006", "Jesus", "Vega Cordero", "Industrial",4, 3124.13 };
  relacion.add(temp);
  temp = Alumno{"0007", "Heider", "Sanchez Quizpe", "Mecatronica",8,134.12};
  relacion.add(temp);
  temp = Alumno{"0008", "Eric","Bracamonte" ,"CS" ,4,314.1324 };
  relacion.add(temp);
  temp = Alumno{"0009", "Jose", "Lopez", "CS", 11,1341.1234 };
  relacion.add(temp);
  temp = Alumno{ "0010" ,"Juan" ,"Del Pino" , "CS" ,10,1341.11   };
  relacion.add(temp);
  temp = Alumno{  "0011", "Maria", "Castillo", "Veterinaria",7,2000 };
  relacion.add(temp);
  temp = Alumno{  "0012", "Juan","Suarez", "Derecho",8,1400.99 };
  relacion.add(temp);

  relacion.del(10);
  relacion.del(5);

  temp = Alumno{  "0013", "Pepe","Guitierrez", "Medicina",7,2100 };
  relacion.add(temp);
  temp = Alumno{  "0014", "Jose","Ugarte", "Ing. Software",5,1500 };
  relacion.add(temp);
  temp = Alumno{  "0015", "Jose","Ugarte", "Ing. Software",1,1500 };
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
