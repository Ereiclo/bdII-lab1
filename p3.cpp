#include <iostream>
#include <vector>
#include <fstream>
#define max_string 255

using namespace std;

struct Alumno
{
  string Nombre;
  string Apellidos;
  string Carrera;
  float mensualidad;

  void display(){
    cout<<Nombre<<' '<<Apellidos<<' '<<Carrera<<' '<<mensualidad<<'\n';
  }
};


class VariableRecord{
  string nombre_archivo;
  public:

  VariableRecord(string _nombre_archivo): nombre_archivo{_nombre_archivo}{}

  void add(Alumno& a){
    fstream ayuda;
    ayuda.open(nombre_archivo,ios::app);

    ayuda.write(a.Nombre.c_str(),a.Nombre.size());
    ayuda.write("|",1);
    ayuda.write(a.Apellidos.c_str(),a.Apellidos.size());
    ayuda.write("|",1);
    ayuda.write(a.Carrera.c_str(),a.Carrera.size());
    ayuda.write("|",1);
    ayuda.write((char*)&a.mensualidad,sizeof(float));
    ayuda.write("\n",1);

    ayuda.close();




  }



  vector<Alumno> load(){

    fstream ayuda;

    //el buffer almacena toda una fila 
    //max_string*3 es por la cantidad de bytes maxima para cada string
    //sizeof(float) es para el float almacenado en la fila
    //3 es por las veces que se va repetir '|' en una fila
    //1 es por el '\0' que va a poner el getline
    char buffer[max_string*3 + sizeof(float) + 3 + 1];
    ayuda.open(nombre_archivo,ios::in);


    ayuda.getline(buffer,sizeof(buffer));


    int actual_pos = ayuda.tellg();
    int iter;
    string temp("");
    Alumno temp2;
    vector<Alumno> retorno;

    while(!ayuda.eof()){
      iter = 0;
      ayuda.seekg(actual_pos);
      ayuda.getline(buffer,sizeof(buffer));
      actual_pos = ayuda.tellg();
      ayuda.get();


      while(buffer[iter] != '|') temp.push_back(buffer[iter++]);
      iter++;
      temp2.Nombre = temp; 
      temp.clear();

      while(buffer[iter] != '|') temp.push_back(buffer[iter++]);
      iter++;
      temp2.Apellidos = temp; 
      temp.clear();

      while(buffer[iter] != '|') temp.push_back(buffer[iter++]);
      iter++;
      temp2.Carrera = temp; 
      temp.clear();


      char* temp3 = buffer;
      temp2.mensualidad = *(float*) (temp3 + iter);
      retorno.push_back(temp2);


      
    }

    ayuda.close();
    return retorno;


  }


  Alumno readRecord(int pos){
    fstream ayuda;

    char buffer[max_string*3 + sizeof(float) + 3 + 1];
    ayuda.open(nombre_archivo,ios::in);


    ayuda.getline(buffer,sizeof(buffer));

    int n = 0;
    while(pos-- > -1) ayuda.getline(buffer,sizeof(buffer));


    int iter = 0;
    string temp("");
    Alumno retorno;

    while(buffer[iter] != '|') temp.push_back(buffer[iter++]);
    iter++;
    retorno.Nombre = temp; 
    temp.clear();

    while(buffer[iter] != '|') temp.push_back(buffer[iter++]);
    iter++;
    retorno.Apellidos = temp; 
    temp.clear();

    while(buffer[iter] != '|') temp.push_back(buffer[iter++]);
    iter++;
    retorno.Carrera = temp; 
    temp.clear();


    char* temp3 = buffer;
    retorno.mensualidad = *(float*) (temp3 + iter);

    

    ayuda.close();
    return retorno;


  }



};

void inicializar_archivo(){
  fstream ayuda;
  ayuda.open("datos3.txt",ios::out);


  char x[] = "Nombre|Apellidos|Carrera|Mensualidad";
  ayuda.write(x,sizeof(x)-1);
  ayuda.write("\n",1);


  ayuda.close();

}

int main(){
  inicializar_archivo();
  VariableRecord relacion("datos3.txt");
  Alumno temp;

  temp = Alumno{"Howard","Paredes Zegarra","Computacion",134.5};
  relacion.add(temp);
  temp = Alumno{ "Penny","Vargas Cordero","Industrial",134.5};
  relacion.add(temp);
  temp = Alumno{ "Sheldon","Cooper Vega","Mecatronica",134.5};
  relacion.add(temp);
  temp = Alumno{ "Pamela","Vargas Cordero","Industrial",134.5};
  relacion.add(temp);
  temp = Alumno{ "Vanesa","Cooper Quizpe","Mecatronica",12134.151};
  relacion.add(temp);
  temp = Alumno{ "Jesus", "Vega Cordero", "Industrial", 3124.13 };
  relacion.add(temp);
  temp = Alumno{ "Heider", "Sanchez Quizpe", "Mecatronica",134.12};
  relacion.add(temp);
  temp = Alumno{ "Eric","Bracamonte" ,"CS" ,314.1324 };
  relacion.add(temp);
  temp = Alumno{ "Jose", "Lopez", "CS", 1341.1234 };
  relacion.add(temp);
  temp = Alumno{"Juan" ,"Del Pino" , "CS" ,1341.11   };
  relacion.add(temp);
  temp = Alumno{"Maria", "Castillo", "Veterinaria",2000 };
  relacion.add(temp);
  temp = Alumno{"Juan","Suarez", "Derecho",1400.99 };
  relacion.add(temp);


  auto v = relacion.load();
  for(auto&a : v){
    a.display();
  }

  cout<<endl<<endl;


  relacion.readRecord(3).display();
  relacion.readRecord(7).display();


  return 0;
}
