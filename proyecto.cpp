#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cstdlib>
#include <algorithm>
#include <bitset>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <pthread.h>
#include <sstream>

using namespace std;

//Permutación inicial.
char table_ip[] = {
    58,50,42,34,26,18,10,2,
    60,52,44,36,28,20,12,4,
    62,54,46,38,30,22,14,6,
    64,56,48,40,32,24,16,8,
    57,49,41,33,25,17,9,1,
    59,51,43,35,27,19,11,3,
    61,53,45,37,29,21,13,5,
    63,55,47,39,31,23,15,7
};

//Permutación final.
char table_ip_reverse[] = {
    40,8,48,16,56,24,64,32,
    39,7,47,15,55,23,63,31,
    38,6,46,14,54,22,62,30,
    37,5,45,13,53,21,61,29,
    36,4,44,12,52,20,60,28,
    35,3,43,11,51,19,59,27,
    34,2,42,10,50,18,58,26,
    33,1,41,9,49,17,57,25
};

//Tablas para S.
char table_s[8][4][16] = {
    {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
    {
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },
    {
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },
    {
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },
    {
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },
    {
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },
    {
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },
    {
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};

char table_pc_1[] = {
    57,49,41,33,25,17,9,
    1,58,50,42,34,26,18,
    10,2,59,51,43,35,27,
    19,11,3,60,52,44,36,
    63,55,47,39,31,23,15,
    7,62,54,46,38,30,22,
    14,6,61,53,45,37,29,
    21,13,5,28,20,12,4
};

char table_pc_2[]{
    14,17,11,24,1,5,
    3,28,15,6,21,10,
    23,19,12,4,26,8,
    16,7,27,20,13,2,
    41,52,31,37,47,55,
    30,40,51,45,33,48,
    44,49,39,56,34,53,
    46,42,50,36,29,32
};

//Tabla para función E.
char table_e[] = {
    32,1,2,3,4,5,
    4,5,6,7,8,9,
    8,9,10,11,12,13,
    12,13,14,15,16,17,
    16,17,18,19,20,21,
    20,21,22,23,24,25,
    24,25,26,27,28,29,
    28,29,30,31,32,1
};

char table_p[] = {
    16,7,20,21,
    29,12,28,17,
    1,15,23,26,
    5,18,31,10,
    2,8,24,14,
    32,27,3,9,
    19,13,30,6,
    22,11,4,25
};

//Función para convertir de Hex a Bin.
string HexToBin(string hexdec)
{
    long int i = 0;
    string binString = "";
    
    while (hexdec[i]) {
        
        switch (hexdec[i]) {
            case '0':
                binString += "0000";
                break;
            case '1':
                binString += "0001";
                break;
            case '2':
                binString += "0010";
                break;
            case '3':
                binString += "0011";
                break;
            case '4':
                binString += "0100";
                break;
            case '5':
                binString += "0101";
                break;
            case '6':
                binString += "0110";
                break;
            case '7':
                binString += "0111";
                break;
            case '8':
                binString += "1000";
                break;
            case '9':
                binString += "1001";
                break;
            case 'A':
            case 'a':
                binString += "1010";
                break;
            case 'B':
                binString += "1011";
                break;
            case 'C':
                binString += "1100";
                break;
            case 'D':
                binString += "1101";
                break;
            case 'E':
                binString += "1110";
                break;
            case 'F':
                binString += "1111";
                break;
            default:
                cout << "\nInvalid hexadecimal digit "
                << hexdec[i];
        }
        i++;
    }
    return binString;
}

//Función para convertir el texto a un string a bits.
string TextToBinaryString (string text){
    string binaryString = "";
    for (char& _char : text){
        binaryString += bitset<8>(_char).to_string();
    }
    return binaryString;
}
//Función para convertir string de bits a texto.
string BinaryStringToText(string binaryString) {
    string text = "";
    stringstream sstream(binaryString);
    while (sstream.good())
    {
        bitset<8> bits;
        sstream >> bits;
        text += char(bits.to_ulong());
    }
    return text;
}

//TODO: Función de generación de llaves.

//Función de permutación inicial.
void permutation(char* arr){
	char temp[64];
    
	for(int i=0; i<64 ; i++){
		temp[i] = arr[table_ip[i]-1];
	} 
    memcpy(arr, temp, 64);
}

//Función de permutación final.
void permutation_inverse(char* arr){
    char temp[64];
    
    for(int i=0; i<64 ; i++){
        temp[i] = arr[table_ip_reverse[i]-1];
    }
    memcpy(arr, temp, 64);
}

// Funcion XOR
char * xorBINARY(char * first, char * second, int len){
  char * res = new char[len];
  for(int i=0;i<len;i++){
    res[i] = first[i]^second[i];
  }
  return res;
}

//Funcion que transforma de 32 a 48 bits para poder operar con llave.
char* E(char* arr){
    char* res = new char[48];
    for(int i=0; i<48; i++){
        res[i] = arr[table_e[i]-1];
    }
}

//Función S que se encarga de convertir de 48 a 32 bits con las tablas.
char* S(char* arr){
    char* res = new char[32];
    int j = 0;
    int k = 0;
    
    for (int i=0; i<48; i+=6){
        int row = 2*arr[i] + arr[i+5];
        int column = 8*arr[i+1] + 4*arr[i+2] + 2*arr[i+3] + arr[i+4];
        
        int val = table_s[j][row][column];
        j++;
        
        for (int x=8; x>0; x>>= 1){
            res[k] = ((val & x) == x) ? 1:0;
            k++;
        }
    }
    return res;
}

char* P (char* sRes){
    char* res = new char[32];
    
    for (int i=0; i<32; i++){
        res[i] = sRes[table_p[i] - 1];
    }
    
    return res;
}

//Función entre R y llave K.
char* F(char* R, char* K){
    char* resE = E(R);
    char* resXOR = xorBINARY(resE, K, 48);
    char* resS = S(resXOR);
    char* resP = P(resS);
    
    return resP;
}

void iterate(char * binaryBlock , char * subKey){
    char L_OLD[32];
    char R_OLD[32];
    
    memcpy(L_OLD,binaryBlock,32);
    memcpy(R_OLD,&binaryBlock[32],32);
    
    //Aplicar función F con Ri-1 y llave Ki
    char* resF = F(R_OLD,subKey);
    //TODO: Revisar si esta parte es necesaria***
    char* R_NEW = xorBINARY(L_OLD,resF,32);
    
    // Cambiar orden entre R y L.
    memcpy(binaryBlock,R_OLD,32);
    memcpy(&binaryBlock[32],R_NEW,32);
}

//Función que se encarga de cambiar el orden de R y L entre cada ronda Feistel.
void swap(char * arr, int bits){
  int halfLen = bits/2;
  char temp[halfLen];
  memcpy(temp, arr, halfLen);
  memcpy(arr, &arr[halfLen], halfLen);
  memcpy(&arr[halfLen], temp, halfLen);
}

void PC_1(char* arr, char* C0D0){
    for(int i=0; i<56; i++){
        C0D0[i] = arr[table_pc_1[i]-1];
    }
}

void PC_2(char* CiDi, char* keys){
    for(int i=0; i<48; i++){
        keys[i] = CiDi[table_pc_2[i]-1];
    }
}

void LS(char * CiDi,int round){
  //i == round
  if(round == 1 || round == 2 || round == 9 || round == 16){
    char first;

    //LEFT - Ci
    first = CiDi[0];
    for(int i=0;i<27;i++){
      CiDi[i] = CiDi[i+1];
    }
    CiDi[27] = first;

    //RIGHT - Di
    first = CiDi[28];
    for(int i=28;i<55;i++){
      CiDi[i] = CiDi[i+1];
    }
    CiDi[55] = first;
  } else {
    char first;
    char second;

    //LEFT - Ci
    first = CiDi[0];
    second = CiDi[1];
    for(int i=0;i<26;i++){
      CiDi[i] = CiDi[i+2];
    }
    CiDi[26] = first;
    CiDi[27] = second;

    //RIGHT - Di
    first = CiDi[28];
    second = CiDi[29];
    for(int i=28;i<54;i++){
      CiDi[i] = CiDi[i+2];
    }
    CiDi[54] = first;
    CiDi[55] = second;
  }
}

// Función encriptación
void encryptDES(char * plainTextHexString, char * keyHexString){

  //--------------------------------------------------------
  //SETUP PROCESS

  printf("------------------------------------------------\n");
  printf("SETUP Process\n\n");

  //setup plaintext block
  char plainTextBlock[8];
  unsigned long plainTextHexValue = std::strtoul(plainTextHexString, 0, 16);
  memcpy(plainTextBlock,&plainTextHexValue,8);
  std::reverse(plainTextBlock, plainTextBlock+8);

  //setup key
  char key[8];
  unsigned long keyHexValue = std::strtoul(keyHexString, 0, 16);
  memcpy(key,&keyHexValue,8);
  std::reverse(key, key+8);

  char ptbBinary[64]; //plain text block binary
  char keyBinary[64]; //key in binary

  //--------------------------------------------------------
  //GENERATE ALL SUBKEYS

  printf("------------------------------------------------\n");
  printf("SUBKEYS Generation Process\n\n");

  char subkeysBinary[16][48];

  char CiDi[56];

  PC_1(keyBinary,CiDi);
  for(int round=1;round<=16;round++){
    printf("K%d:\n",round);
    LS(CiDi,round);
    PC_2(CiDi,subkeysBinary[round-1]);

    printf("\n");
  }
  printf("\n");

}

int main(){
    string plainText;
    char keyHEX[17];
    
    //Pedir ingreso de texto (string).
    printf("Ingrese el texto que desea encriptar: \n");
    getline(cin, plainText);
    
    //Pedir ingreso de llave.
    printf("Ingrese la llave DES (16 dígitos HEX): \n");
    scanf("%16s", keyHEX);
    
    //Pasar la llave a mayúsculas todo a mayúsculas.
    for (auto & c: keyHEX) c = toupper(c);
    printf("keyHEX: %s\n", keyHEX);
    
    cout<< "keyHEX en binario: " << HexToBin(keyHEX) << endl;
    
    //Calcular número de veces que se tendrá que usar el algoritmo dependiendo del largo del texto.
    int des_num = (TextToBinaryString(plainText).length())%8;
    
    while ((plainText.length()%8) != 0){
        plainText += " ";
    }
    
    string binary = TextToBinaryString(plainText);
    
    char plainTextBinary[des_num][64];
    
    //Obtener cada char en un string.
    for (int i = 0; i < des_num; i++){
        for (int j =0; j<64; j++){
            plainTextBinary[i][j] = binary.at(64*i + j);
        }
    }
    
}
