#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

int ind;

char* hamming(char *argv) {
	
	FILE *file;
    file = fopen(argv, "r");

    if (file == NULL){
        printf("Error opening the file in hamming.\n");
        fclose(file);
        return 0;
    }
    
	vector<string> codes;

    string s = "";
    char z = fgetc(file);
    ind = 0;
    
    while(z != EOF){
        
		if(ind < 4){
        	s.push_back(z);
		}else{
			ind = 0;
			codes.push_back(s);
			s = "";
			s.push_back(z);
		}
    
    	ind++;
        z = fgetc(file);
    }
    fclose(file);
    
    if(ind < 4){
    	string aux = "";
    	for(int i = ind; i < 4;i++){
    		aux.push_back('0');
		}
		aux.append(s);
		codes.push_back(aux);
	}
	
	ofstream hamm;
  hamm.open("hamming-file.bin");
	
	for(int i = 0; i < codes.size() ; i++){
		
		string cod = codes.at(i);
		
		int* data = (int*) malloc(cod.length() * sizeof(int));
		for(int j = 0; j < cod.length(); j++){
			s = cod.at(j);
			data[j] = stoi(s);
		}
		
		bool p1 = data[0] ^ data[2] ^ data[3];
		bool p2 = data[0] ^ data[1] ^ data[3];
		bool p3 = data[0] ^ data[1] ^ data[2];
		
		string aux = "";
		aux.append(to_string(data[0])); aux.append(to_string(data[1])), aux.append(to_string(data[2])); aux.append(to_string(p3)); aux.append(to_string(data[3])); aux.append(to_string(p2)); aux.append(to_string(p1));
		
		hamm << aux;
	}
	
	hamm.close();
	
	return result;
}
