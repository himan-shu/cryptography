//Himanshu Rawat
#include<bits/stdc++.h>

using namespace std;
char keyMatrix[5][5];

void createKeyMatrix(const string& key){
	bool flag[26];
	memset(flag,false,sizeof(flag));
	flag['j'-'a']=true;
	int row=0,col=0;
	for(int i =0 ; i < (int)key.size() ; ++i){
		if( flag[ key[i] - 'a' ] == 0 ){
			flag[ key[i] - 'a' ] = 1;
			keyMatrix[ row ][ col++ ]=key[ i ];
			if(col == 5){
				row++ ; col = 0;
			}
		}
	}
	for(int i = 0 ; i < 26 ; ++i){
		if(flag[i]==false){
			keyMatrix[row][col++] = (char)('a'+i);
			if(col == 5){
				row++ ; col = 0;
			}
		}
	}
	// to print keyMatrix
	// for(int i = 0 ; i < 5 ; ++i){
	// 	for(int j = 0 ; j < 5 ; ++j){
	// 		cout<<keyMatrix[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }
}

void preprocess(string& key, string& plainText){
	for(int i = 0 ; i < key.size() ; ++i){
		if( key[ i ] == 'j' ){
			key[ i ]= 'i';
		}
	}
	for(int i = 0 ; i < plainText.size() ; ++i){
		if( plainText[ i ] == 'j' ){
			plainText[ i ]= 'i';
		}
	}
}

pair< char , char > encryptedChar(char a,char b){
	int aRow,aCol,bRow,bCol;
	for(int i = 0 ; i < 5 ; ++i ){
		for(int j = 0 ; j < 5 ; ++ j){
			if(keyMatrix[i][j]==a){
				aRow=i;
				aCol=j;
			}
			if(keyMatrix[i][j]==b){
				bRow=i;
				bCol=j;
			}
		}
	}
	pair< char , char > newValue;
	if(aCol==bCol){
		newValue.first = keyMatrix[ ( aRow + 1 ) % 5 ][ aCol ];
		newValue.second = keyMatrix[ ( bRow + 1 ) % 5 ][ bCol ];
	}
	else if (aRow==bRow) {
		newValue.first = keyMatrix[ aRow ][ ( aCol + 1 ) % 5 ];
		newValue.second = keyMatrix[ bRow ][ ( bCol + 1 ) % 5 ];
	}
	else {
		newValue.first = keyMatrix[ aRow ][ bCol ];
		newValue.second = keyMatrix[ bRow ][ aCol ];		
	}
	return newValue;
}

string encrypt(const string& plainText){
	string encrypt="";
	for(int i = 0 ; i < (int)plainText.size() ; i=i+2){
		pair<char,char> val = encryptedChar(plainText[i],plainText[i+1]);
		encrypt = encrypt + val.first + val.second;
	}
	return encrypt;
}


pair< char , char > decryptedChar(char a,char b){
	int aRow,aCol,bRow,bCol;
	for(int i = 0 ; i < 5 ; ++i ){
		for(int j = 0 ; j < 5 ; ++ j){
			if(keyMatrix[i][j]==a){
				aRow=i;
				aCol=j;
			}
			if(keyMatrix[i][j]==b){
				bRow=i;
				bCol=j;
			}
		}
	}
	pair< char , char > newValue;
	if(aCol==bCol){
		newValue.first = keyMatrix[ ( aRow + 4 ) % 5 ][ aCol ];
		newValue.second = keyMatrix[ ( bRow + 4 ) % 5 ][ bCol ];
	}
	else if (aRow==bRow) {
		newValue.first = keyMatrix[ aRow ][ ( aCol + 4 ) % 5 ];
		newValue.second = keyMatrix[ bRow ][ ( bCol + 4 ) % 5 ];
	}
	else {
		newValue.first = keyMatrix[ aRow ][ bCol ];
		newValue.second = keyMatrix[ bRow ][ aCol ];	
	}
	return newValue;
}

string decrypt(const string& encryptedText){
	string decrypt="";
	for(int i = 0 ; i < (int)encryptedText.size() ; i=i+2){
		pair<char,char> val = decryptedChar(encryptedText[i],encryptedText[i+1]);
		decrypt = decrypt + val.first + val.second;
	}
	return decrypt;
}

int main() 
{ 
	string plainText, key;
	cin>>plainText>>key;

	preprocess( key , plainText );
	
	// cout<<key<<" "<<plainText<<endl;
	
	createKeyMatrix( key ); 
	
	if(plainText.size()%2==1){
		plainText+='z';
	}
	
	string encryptedText = encrypt(plainText);

	cout<<"plain text --->"<<plainText<<endl;
	cout<<"key --->"<<key<<endl;
	cout<<"encypted text ---> "<<encryptedText<<endl;

	cout<<"plain text after decryption ---> "<<decrypt(encryptedText)<<endl;


	return 0; 
}