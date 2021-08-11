#include "Map.h"
Map::Map()
{
	cont=1;
	levelMax=3;
	rows=14,columns=17;
	map=new int*[rows];
	for(int i=0;i<rows;i++)
		map[i]=new int[columns];
	for(int i=0;i<rows;i++)
		for(int j=0;j<columns;j++)
			map[i][j]=0;
}
void Map::loadLevel()
{
    ifstream cin;
	string out_string;
	stringstream ss;
	ss << cont;
	out_string = ss.str();
	string s = "Mappa"+out_string+".txt";
	cin.open(s.c_str());
	if(cin.good())
	{
		for(int i=0;i<rows;i++)
		{
 		    for(int j=0;j<columns;j++)
				cin>>map[i][j];
		}
	} 
	else
	{
		cin.close();						//GAME OVER
		exit(1);
	}
	cin.close();
}
void Map::printMap()
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<columns;j++)
        {
            if(map[i][j]!=0)
                cout<<map[i][j]<<" ";
            else
                cout << "  ";
        }
        cout<<endl;
    }
}


