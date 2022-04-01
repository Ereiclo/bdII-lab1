#include <iostream>
#include <vector>
#include <fstream>
#define max_string 255

using namespace std;

struct Matricula
{
  string codigo;
  int ciclo;
  float mensualidad;
  string observaciones;


  void display(){
    cout<<codigo<<" "<<ciclo<<" "<<mensualidad<<" "<<observaciones<<'\n';
  }
};

struct Metadata{
  int initial_pos;
  int register_size;//se tomo en consideracion guardar el tamaño del
		    //registro, asi se omite ese entero para 
		    //cada registro

};

class VariableRecord{
  string nombre_archivo;
  string nombre_metadata;
  public:

  VariableRecord(string _nombre_archivo,string _nombre_metadata): nombre_archivo{_nombre_archivo},nombre_metadata{_nombre_metadata}{}


  void add(Matricula& m){
    fstream ayuda;
    int temp;

    ayuda.open(nombre_archivo,ios::app|ios::binary);

    Metadata n_entry{(int)ayuda.tellg(),0};

    temp = m.codigo.size();
    ayuda.write((char*)&temp,sizeof(int));
    ayuda.write(m.codigo.c_str(),m.codigo.size());
    n_entry.register_size += sizeof(int) + m.codigo.size();


    temp = sizeof(int);
    ayuda.write((char*)&temp,sizeof(int));
    ayuda.write((char*)&m.ciclo,sizeof(int));
    n_entry.register_size += sizeof(int) + sizeof(int);

    temp = sizeof(float);
    ayuda.write((char*)&temp,sizeof(int));
    ayuda.write((char*)&m.mensualidad,sizeof(float));
    n_entry.register_size += sizeof(int) + sizeof(float);

    temp = m.observaciones.size();
    ayuda.write((char*)&temp,sizeof(int));
    ayuda.write(m.observaciones.c_str(),m.observaciones.size());
    n_entry.register_size += sizeof(int) + m.observaciones.size();


    ayuda.close();

    ayuda.open(nombre_metadata,ios::app|ios::binary);


    ayuda.write((char*)&n_entry.initial_pos,sizeof(int));
    ayuda.write((char*)&n_entry.register_size,sizeof(int));

    ayuda.close();



  }

  vector<Matricula> load(){
    fstream ayuda1;
    fstream ayuda2;
    vector<Matricula> retorno;
    ayuda1.open(nombre_archivo,ios::in|ios::binary);
    ayuda2.open(nombre_metadata,ios::in|ios::binary);
    ayuda2.seekg(0,ios::end);
    int s = ayuda2.tellg()/sizeof(Metadata);
    char buffer[max_string*2 + sizeof(float) + sizeof(int) + 4*sizeof(int)];

    Matricula temp1;
    Metadata temp2;
    char* iter;
    int temp_size;
    for(int i = 0;i < s;++i){
      ayuda2.seekg(sizeof(Metadata)*i);
      ayuda2.read((char*)&temp2,sizeof(Metadata));
      ayuda1.seekg(temp2.initial_pos);
      ayuda1.read(buffer,temp2.register_size);

      iter = buffer;
      temp_size =* (int*) iter;
      iter  = iter + sizeof(int);
      temp1.codigo.clear();
      for(int j = 0;j< temp_size;++j) 
	temp1.codigo.push_back(iter[j]);
      
      iter = iter + temp_size + sizeof(int);

      temp1.ciclo = *(int*) iter;

      iter = iter + sizeof(int) + sizeof(int);

      temp1.mensualidad = *(float*) iter;

      iter = iter + sizeof(float);

      temp_size = *(int*) iter;
      iter = iter + sizeof(int);
      temp1.observaciones.clear();
      for(int j = 0;j< temp_size;++j)
	temp1.observaciones.push_back(iter[j]);
      

      retorno.push_back(temp1);
      
    }


    ayuda1.close();
    ayuda2.close();

    return retorno;

  }


  Matricula readRecord(int pos){
    fstream ayuda1;
    fstream ayuda2;
    Matricula retorno;
    Metadata temp;

    char buffer[max_string*2 + sizeof(float) + sizeof(int) + 4*sizeof(int)];

    ayuda1.open(nombre_archivo,ios::in);
    ayuda2.open(nombre_metadata,ios::in);

    ayuda2.seekg(sizeof(Metadata)*pos);
    ayuda2.read((char*)&temp, sizeof(Metadata));

    ayuda1.seekg(temp.initial_pos);
    ayuda1.read(buffer,temp.register_size);

    char* iter = buffer;
    int temp_size = * (int*) iter;
    iter  = iter + sizeof(int);
    retorno.codigo.clear();
    for(int j = 0;j< temp_size;++j) 
      retorno.codigo.push_back(iter[j]);

    iter = iter + temp_size + sizeof(int);

    retorno.ciclo = *(int*) iter;

    iter = iter + sizeof(int) + sizeof(int);

    retorno.mensualidad = *(float*) iter;

    iter = iter + sizeof(float);

    temp_size = *(int*) iter;
    iter = iter + sizeof(int);
    retorno.observaciones.clear();
    for(int j = 0;j< temp_size;++j)
      retorno.observaciones.push_back(iter[j]);

    ayuda2.close();
    ayuda2.close();

    return retorno;
  }



};

void inicializar_archivo(){
  fstream ayuda;
  ayuda.open("datos4.dat",ios::out|ios::binary);
  ayuda.close();

  ayuda.open("metadata.dat",ios::out|ios::binary);

  ayuda.close();

}

int main(){
  inicializar_archivo();
  VariableRecord relacion("datos4.dat","metadata.dat");

  Matricula temp;

  temp = Matricula{"0001", 1,134.5 , "clase E"};
  relacion.add(temp);
  temp = Matricula{"0002", 4,134.5, "clase E"};
  relacion.add(temp);
  temp = Matricula{"0003",3,134.5, "clase E"};
  relacion.add(temp);
  temp = Matricula{"0004", 7,134.5, "clase E"};
  relacion.add(temp);
  temp = Matricula{"0005", 7,12134.151, "clase A+"};
  relacion.add(temp);
  temp = Matricula{"0006", 4, 3124.13, "clase B" };
  relacion.add(temp);
  temp = Matricula{"0007", 8,134.12, "clase E"};
  relacion.add(temp);
  temp = Matricula{"0008", 4,314.1324, "clase E" };
  relacion.add(temp);
  temp = Matricula{"0009", 11,1341.1234, "clase D" };
  relacion.add(temp);
  temp = Matricula{ "0010",10,1341.11, "clase D" };
  relacion.add(temp);
  temp = Matricula{  "0011",7,2000 , "clase C"};
  relacion.add(temp);
  temp = Matricula{  "0012",8,1400.99, "clase D" };
  relacion.add(temp);


  auto v = relacion.load();
  for(auto&a : v){
    a.display();
  }

  cout<<endl<<endl;


  relacion.readRecord(3).display();
  relacion.readRecord(7).display();

  temp = Matricula{  "0013",8,1400.99, "clase D" };
  relacion.add(temp);
  cout<<endl;
  v = relacion.load();
  for(auto&a : v){
    a.display();
  }

  cout<<endl<<endl;



  relacion.readRecord(12).display();
  relacion.readRecord(9).display();

  return 0;
}
