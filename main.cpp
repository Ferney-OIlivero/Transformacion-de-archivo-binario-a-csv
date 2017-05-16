#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct registro{
    char nombre[200];
    char apellido[200];
    char fechaNacimiento[11];
    char cedula[12];
    float notas[30];
    char direccion[500];
};

string encomillar(string texto,int tam){
    int bandera=0;
    for (int x=0; x<tam;x++){
        if(texto[x]==','){
            bandera=1;
        }
    }
    if (bandera==1){
        texto="\""+texto+"\"";
    }
    return texto;
}
    

int main(int argc, char *argv[])
{
    registro datos;
    streampos begin,end,size;
    int a=0;
    
    ofstream filecsv("datos.csv",ios::trunc);
    ifstream file("datos.bin",ios::in|ios::binary|ios::ate);
    end = file.tellg();
    file.seekg (0, ios::beg);
    size = file.tellg();
    if (file.is_open()){
        while(size<end){
            
            file.seekg (size);
            file.read (datos.nombre, sizeof(datos.nombre));//
            file.read (datos.apellido, sizeof(datos.apellido));
            file.read (datos.fechaNacimiento, sizeof(datos.fechaNacimiento));
            file.read (datos.cedula, sizeof(datos.cedula));
            for (int i = 0; i < 30; i++){
                file.read((char *)(&datos.notas[i]),sizeof(datos.notas[i]));
            }
            file.read (datos.direccion, sizeof(datos.direccion));
            
            if (filecsv.is_open()){
                filecsv<<datos.nombre<<",";
                filecsv<<datos.apellido<<",";
                filecsv<<datos.fechaNacimiento<<",";
                filecsv<<datos.cedula<<",\"";
                for (int x=0; x<30;x++){
                    if(x!=29){
                        filecsv<<datos.notas[x]<<",";
                    }else{
                        filecsv<<datos.notas[x]<<"\",\"";
                    }
                }
                filecsv<<datos.direccion<<"\"\n";
            }else{
                cout<<"ERROR"<<endl;
            }
            
            size=size+1044;
        }
        file.close();
    }else{
        cout << "No se abrio el archivo";
    }

    cout << "Ha finalizado el proceso";
    cin.get();
    return EXIT_SUCCESS;
}
