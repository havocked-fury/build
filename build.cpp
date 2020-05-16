#include <iostream>
#include <fstream>
#include <string>

const char newline = '\n';

std::fstream buildList, buildScript;
std::string fileName;

int main(){
	std::ios_base::sync_with_stdio(0);

	/*initBuildScript*/{
		system("rm buildScript");
		system("touch buildScript");
	}

	/*openBuildScript*/{
		buildScript.open("./buildScript");

		/*script write: compile files*/{
			buildList.open("./buildList");

			while(buildList>> fileName){
				buildScript<< "g++ -c ../src/" << fileName << ".cpp" << newline;
			}

			buildList.close(); // "./buildList"
		} 

		buildList.open("./buildList");

		/*script write: link files*/{
			buildScript<< "g++ -o run";
			while(buildList>> fileName){
				buildScript<< " ./" <<  fileName << ".o ";
			}
			buildScript<<newline;
		}
		/*
		/*script write: organise files*/{

			buildScript<< "mv *.o ../obj" << newline;
			buildScript<< "mv run ../ " << newline;
			buildScript<< "cp ../run ../test/" << newline;
			buildScript<< "touch ../test/testOutput.txt" << newline;
		}

		buildList.close(); // buildList

		buildScript.close(); // "./buildScript"

		/*build project*/{

			system("bash ./buildScript");
		}
	}
	
	return 0;
}